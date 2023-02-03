//=============================================================================
//
// Xファイルモーション [set_model.cpp]
// Author : SHUGO KURODA
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <stdio.h>
#include "set_model.h"

#include "renderer.h"
#include "manager.h"

// 追加
#include "model.h"
#include "model_obstacle.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_CHAR (256)			//一行の最大読み取り文字数

//=============================================================================
// 構造体
//=============================================================================
struct Model
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 回転
	char cName[MAX_CHAR];		// 種類
	int8_t nCollision;			// 当たり判定の有無
	D3DXVECTOR2 shadowSize;		// 影のサイズ
	int8_t nShadow;				// 影を配置
};

//=============================================================================
// コンストラクタ
//=============================================================================
CSetModel::CSetModel()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSetModel::~CSetModel()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CSetModel::Init(HWND hWnd)
{
	// ファイルを開く
	FILE *pFile = fopen("data/TEXT/model_pas.ini", "r");

	if (pFile == NULL)
	{//開けなかった時用
		MessageBox(hWnd, "モデル配置INIファイルを開けませんでした", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	char cBff[MAX_CHAR];			// 一行分読み取るための変数
	char cBffHead[MAX_CHAR];		// 頭の文字を読み取るための変数
	int nNum = 0;

	//文字列の読み取りループ処理
	while (fgets(cBff, MAX_CHAR, pFile) != NULL)
	{
		//文字列の分析
		sscanf(cBff, "%s", &cBffHead);

		// 文字列の中にTEX_NUMがあったら
		if (strcmp(&cBffHead[0], "MODEL_NUM") == 0)
		{
			// モデルモーション最大数読み込み
			sscanf(cBff, "%s = %d", &cBffHead, &m_nNumMotion);
		}
		if (strcmp(&cBffHead[0], "MODELSET") == 0)
		{// モデルモーション読み込みを開始

			// 一行ずつ保存
			while (fgets(cBff, MAX_CHAR, pFile) != NULL)
			{
				//文字列の分析
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "SCRIPT_FILENAME") == 0)
				{//モーションテキストの相対パス用

					//相対パス保存用
					char sPath[MAX_CHAR];

					//一行の文字列から相対パスの読み取り
					sscanf(cBff, "%s = %s", &cBffHead, &sPath[0]);
					m_aPas.push_back(&sPath[0]);
				}
				else if (strcmp(&cBffHead[0], "NAME") == 0)
				{// 名前の取得
					sscanf(cBff, "%s = %s", &cBffHead, &cBff[0]);
					// 名前と数の割り当て
					m_texType[cBff] = nNum;
					nNum++;
				}
				else if (strcmp(&cBffHead[0], "END_MODELSET") == 0)
				{// モデルモーション読み込み終了
					break;
				}
			}
		}
		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
		{//読み込み終了
			break;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CSetModel::Uninit()
{
}

//-----------------------------------------------------------------------------
// モーション情報の読み込み
//-----------------------------------------------------------------------------
bool CSetModel::LoadModel(std::string name)
{
	// ファイルを開く
	FILE *pFile = fopen(m_aPas[m_texType[name]].c_str(), "r");
	
	if (pFile == NULL)
	{// ファイルを開けなかった場合
		return false;
	}

	char cBff[MAX_CHAR];			// 一行分読み取る変数
	char cBffHead[MAX_CHAR];		// 頭の文字を読み取る変数
	bool bReadScript = false;		// スクリプトを読み込むかどうか

	// 文字列の読み取りループ処理
	while (fgets(cBff, MAX_CHAR, pFile) != NULL)
	{
		// 文字列の分析
		sscanf(cBff, "%s", &cBffHead);

		if (!bReadScript && strcmp(&cBffHead[0], "SCRIPT") == 0)
		{// スクリプトの読み込みを開始
			bReadScript = true;
		}
		else if (bReadScript)
		{// SCRIPT読み込みを開始したら

			if (strcmp(&cBffHead[0], "MODELSET") == 0)
			{//モデルの配置用

				// モデル配置情報の保存用
				Model model;
				// 文字読み込み用変数の初期化
				memset(&model, 0, sizeof(Model));

				// モデル配置に必要な情報読み取りループ処理
				while (fgets(cBff, MAX_CHAR, pFile) != NULL)
				{
					// 文字列の分析
					sscanf(cBff, "%s", &cBffHead);

					if (strcmp(&cBffHead[0], "TYPE") == 0)
					{// モデルの種類用
						sscanf(cBff, "%s = %s", &cBffHead, &model.cName[0]);
					}
					else if (strcmp(&cBffHead[0], "POS") == 0)
					{// 位置
						sscanf(cBff, "%s = %f%f%f", &cBffHead, &model.pos.x, &model.pos.y, &model.pos.z);
					}
					else if (strcmp(&cBffHead[0], "ROT") == 0)
					{// 角度
						sscanf(cBff, "%s = %f%f%f", &cBffHead, &model.rot.x, &model.rot.y, &model.rot.z);
					}
					else if (strcmp(&cBffHead[0], "COLLISION") == 0)
					{// 当たり判定
						sscanf(cBff, "%s = %hhd", &cBffHead, &model.nCollision);
					}
					else if (strcmp(&cBffHead[0], "SHADOW") == 0)
					{// 影のセット
						sscanf(cBff, "%s = %hhd%f%f", &cBffHead, &model.nShadow, &model.shadowSize.x, &model.shadowSize.y);
					}
					else if (strcmp(&cBffHead[0], "END_MODELSET") == 0)
					{// モデルのセットに必要な情報を読み切った時

						//if (Model.bShadow == true)
						//{//nCheckが1以上の場合、影を設定する
						//	Model.nIdxShadow = SetShadow(D3DXVECTOR3(Model.pos.x, 0.1f, Model.pos.z), Model.rot, fShadowX, fShadowZ);

						// モデル配置
						CObstacle::Create(model.pos, model.rot, &model.cName[0])->SetCont(-1);

						break;
					}
				}
			}
			else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
			{//テキストファイルを読み切った時
				break;
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);

	return true;
}

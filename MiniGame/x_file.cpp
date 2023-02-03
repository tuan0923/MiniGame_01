//=============================================================================
//
// Xファイルマネージャー [x_file.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include <stdio.h>

#include "x_file.h"
#include "renderer.h"
#include "manager.h"

//================================================
// マクロ定義
//================================================
#define MAX_CHAR		(128)		// 最大読み取り文字数

//================================================
// 静的メンバ変数宣言
//================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CXFile::CXFile()
{
	// 変数の初期化
	m_texType.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CXFile::~CXFile()
{
}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CXFile::Init()
{
	//ファイル読み込み
	FILE *pFile = fopen("data/TEXT/x_file_pas.txt", "r");

	if (pFile == NULL)
	{// ファイルを開けなかった場合
		return;
	}

	char cScanf[MAX_CHAR];		//一行分読み取るための変数
	char cScanfHead[MAX_CHAR];	//頭の文字を読み取るための変数
	bool bReadScript = false;	//スクリプトを読み込むかどうか
	int nNum = 0;

	//一行ずつ保存
	while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
	{
		// 文字列の分析
		sscanf(cScanf, "%s", &cScanfHead);

		if (!bReadScript && strcmp(&cScanfHead[0], "SCRIPT") == 0)
		{// スクリプトの読み込みを開始
			bReadScript = true;
		}
		else if (bReadScript)
		{// SCRIPT読み込みを開始したら

			//文字列の中にTEX_NUMがあったら
			if (strcmp(&cScanfHead[0], "XFILE_NUM") == 0)
			{
				// テクスチャ最大数読み込み
				sscanf(cScanf, "%s = %d", &cScanfHead, &m_nNumXFile);
			}
			if (strcmp(&cScanfHead[0], "XFILESET") == 0)
			{// テクスチャ読み込みを開始

				//一行ずつ保存
				while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
				{
					// 文字列の分析
					sscanf(cScanf, "%s", &cScanfHead);

					// 文字列の中にPASがあったら
					if (strcmp(&cScanfHead[0], "PAS") == 0)
					{
						// パスの取得
						sscanf(cScanf, "%s = %s", &cScanfHead, &cScanf[0]);
						m_aPas.push_back(&cScanf[0]);
					}
					else if (strcmp(&cScanfHead[0], "NAME") == 0)
					{// 名前の取得
						//名前の取得
						sscanf(cScanf, "%s = %s", &cScanfHead, &cScanf[0]);
						// 名前と数の割り当て
						m_texType[cScanf] = nNum;
						nNum++;
					}
					else if (strcmp(&cScanfHead[0], "END_XFILESET") == 0)
					{// テクスチャ読み込み終了
						break;
					}
				}
			}
			else if (strcmp(&cScanfHead[0], "END_SCRIPT") == 0)
			{// テキストファイルを読み切った時
				break;
			}
		}
	}

	// ファイルを閉じる
	fclose(pFile);

	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	for (int nCntXFile = 0; nCntXFile < m_nNumXFile; nCntXFile++)
	{
		// テクスチャ保存用
		SModelInfo xFile;

		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_aPas[nCntXFile].c_str(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&xFile.pBuffMat,
			NULL,
			&xFile.nNumMat,
			&xFile.pMesh);

		// テクスチャの読み込み処理
		LoadXFileTexture(&xFile);

		// Xファイル情報の保存
		m_aXFile.push_back(xFile);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CXFile::Uninit()
{
	for (int nCnt = 0; nCnt < m_nNumXFile; nCnt++)
	{
		//メッシュの破棄
		if (m_aXFile[nCnt].pMesh != NULL)
		{
			m_aXFile[nCnt].pMesh->Release();
			m_aXFile[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (m_aXFile[nCnt].pBuffMat != NULL)
		{
			m_aXFile[nCnt].pBuffMat->Release();
			m_aXFile[nCnt].pBuffMat = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// テクスチャ読み込み
//-----------------------------------------------------------------------------
void CXFile::LoadXFileTexture(SModelInfo* pXFile)
{
	//マテリアルデータへのポインタを取得
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)pXFile->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXFile->nNumMat; nCntMat++)
	{
		//デバイスを取得する
		LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャがあった場合
		if ((pMat[nCntMat].pTextureFilename != NULL) && (strcmp(pMat[nCntMat].pTextureFilename, "") != 0))
		{//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &pXFile->pTexture[nCntMat]);
		}
	}
}

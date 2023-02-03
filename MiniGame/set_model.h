//=============================================================================
//
// Xファイルモーション [set_model.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _SET_MODEL_
#define _SET_MODEL_

#include "motion_data.h"
#include <vector>
#include <string>
#include <map>

//using namespace std;

//=============================================================================
// クラス定義
//=============================================================================
class CSetModel
{
	// メンバ関数
public:
	CSetModel();				//コンストラクタ
	~CSetModel();				//デストラクタ

	// 初期化
	HRESULT Init(HWND hWnd);
	// 終了
	void Uninit();
	// モーション情報の読み込み
	bool LoadModel(std::string name);
	// Xファイル情報の取得(名前指定)
	std::string GetPas(std::string texType) { return m_aPas[m_texType[texType]]; }
	// Xファイル情報の取得(番号指定)
	std::string GetPas(int nCnt) { return m_aPas[nCnt]; }

	// メンバ変数
private:
	std::vector<std::string> m_aPas;		// Xファイルのパス
	std::map<std::string, int> m_texType;	// Xファイルの種類
	int m_nNumMotion;						// Xファイルの総数
};

#endif	//_SET_MODEL_

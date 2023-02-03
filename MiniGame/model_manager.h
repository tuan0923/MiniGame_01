//===================================================================
//
//	モデルのマネージャー処理[model_manager.h]
//	Author : SHUGO KURODA
//
//===================================================================
#ifndef _MODEL_MANAGER_H_
#define _MODEL_MANAGER_H_

#include "object.h"

//*******************************************************************
//	モデルのマネージャークラスの定義
//*******************************************************************
class CModelManager :public CObject
{
public:
	//メンバ関数
	CModelManager();
	~CModelManager();

	static CModelManager *Create();		//インスタンス生成処理

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	int m_nCounter;			// カウンター
	int m_nCounterCreate;	// オブジェクト生成までの数値
	int m_nNumCreate;		// 1回に生成するオブジェクト数
	int m_nCreateInterval;	// オブジェクトを生成する間隔
	int m_nNumModel;
	int m_nNumCreateModel;
};

#endif	// _MODEL_MANAGER_H_

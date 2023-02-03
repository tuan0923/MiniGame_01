//===================================================================
//
//	ポリゴン処理のヘッダー[tutorial.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _TUTORIAL_H_			//このマクロ定義がされなかったら
#define _TUTORIAL_H_			//2重インクルード防止のマクロ定義

#include "object3D.h"

//======================================================
//	マクロ定義
//======================================================
//#define POLYGON_SIZE	(2000.0f)	//ポリゴンのサイズ

//======================================================
//	クラス宣言
//======================================================
class CTutorial : public CObject3D
{
public:
	CTutorial();
	~CTutorial() override;

	static CTutorial *Create(const D3DXVECTOR3& pos);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	// 表示しているかどうか
	bool m_bDis;
	CObject3D* m_pObj;
};

#endif
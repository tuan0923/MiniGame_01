//===================================================================
//
//	障害物処理[model_obstacle.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "model.h"

//*******************************************************************
//	前方宣言
//*******************************************************************
class CPlayer;

//*******************************************************************
//	障害物クラスの定義
//*******************************************************************
class CObstacle : public CModel
{
public:
	//メンバ関数
	CObstacle();
	~CObstacle() override;

	static CObstacle *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);		//インスタンス生成処理

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetCollision(bool bCol) { m_bCollision = bCol; }

	static void CollisionAll(D3DXVECTOR3* pPosIn, int nNumPlayer);
	bool Collision(D3DXVECTOR3* pPosIn, int nNumPlayer);

private:
	D3DXVECTOR3 m_PosOld;	//前回の位置
	int m_nDel;
	bool m_bCollision;		// 当たり判定の有無
};

#endif	// _OBSTACLE_H_

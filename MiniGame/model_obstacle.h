//===================================================================
//
//	��Q������[model_obstacle.h]
//	Author:�e���A��
//
//===================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "model.h"

//*******************************************************************
//	�O���錾
//*******************************************************************
class CPlayer;

//*******************************************************************
//	��Q���N���X�̒�`
//*******************************************************************
class CObstacle : public CModel
{
public:
	//�����o�֐�
	CObstacle();
	~CObstacle() override;

	static CObstacle *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);		//�C���X�^���X��������

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetCollision(bool bCol) { m_bCollision = bCol; }

	static void CollisionAll(D3DXVECTOR3* pPosIn, int nNumPlayer);
	bool Collision(D3DXVECTOR3* pPosIn, int nNumPlayer);

private:
	D3DXVECTOR3 m_PosOld;	//�O��̈ʒu
	int m_nDel;
	bool m_bCollision;		// �����蔻��̗L��
};

#endif	// _OBSTACLE_H_

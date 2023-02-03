//===================================================================
//
//	�N���o�X(�n�ʂ̋T��)�̏���[model_crevasse.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _CREVASSE_H_
#define _CREVASSE_H_

#include "model.h"

//*******************************************************************
//	��Q���N���X�̒�`
//*******************************************************************
class CCrevasse : public CModel
{
public:
	//�����o�֐�
	CCrevasse();
	~CCrevasse() override;

	// ��������
	static CCrevasse *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static void CollisionAll(D3DXVECTOR3* pPosPlayer, D3DXVECTOR3* pPosPlayerOld, D3DXVECTOR3* pSizePlayer);
	bool Collision(D3DXVECTOR3* pPosPlayer, D3DXVECTOR3* pPosPlayerOld, D3DXVECTOR3* pSizePlayer);

private:
	D3DXVECTOR3 m_PosOld;	//�O��̈ʒu
};

#endif	// _OBSTACLE_H_

//===================================================================
//
//		���C�g�����̃w�b�_�[[light.h]
//		Author:���c ����
//
//===================================================================
#ifndef _LIGHT_H_			//���̃}�N����`������Ȃ�������
#define _LIGHT_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

//======================================================
//	�v���g�^�C�v�錾
//======================================================
class CLight : public CObject
{
public:
	CLight();
	~CLight() override;

	static CLight *Create(const D3DXVECTOR3& vecDir, const D3DXCOLOR& diffuse);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	D3DLIGHT9 m_aLight;			//���C�g���
	D3DXVECTOR3 m_vecDir;		//���C�g�̕����x�N�g��
	D3DXCOLOR m_Diffuse;		//���C�g�̊g�U��
	static int m_nNumLight;		//���C�g�̐�
};

#endif
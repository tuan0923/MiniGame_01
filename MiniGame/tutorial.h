//===================================================================
//
//	�|���S�������̃w�b�_�[[tutorial.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _TUTORIAL_H_			//���̃}�N����`������Ȃ�������
#define _TUTORIAL_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "object3D.h"

//======================================================
//	�}�N����`
//======================================================
//#define POLYGON_SIZE	(2000.0f)	//�|���S���̃T�C�Y

//======================================================
//	�N���X�錾
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
	// �\�����Ă��邩�ǂ���
	bool m_bDis;
	CObject3D* m_pObj;
};

#endif
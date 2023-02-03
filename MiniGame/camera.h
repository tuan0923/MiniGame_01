//===================================================================
//
//		�J���������̃w�b�_�[[camera.h]
//		Author:SHUGO KURODA
//
//===================================================================
#ifndef _CAMERA_H_			//���̃}�N����`������Ȃ�������
#define _CAMERA_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

//======================================================
//	�J�����̍\����
//======================================================
class CCamera : public CObject
{
public:
	CCamera();
	~CCamera() override;

	static CCamera *Create(const D3DXVECTOR3& posV, const D3DXVECTOR3& posR, const D3DXVECTOR3& rot, float fNear);	//�C���X�^���X��������

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// ���_�ʒu�̐ݒ�
	void SetPosV(D3DXVECTOR3 posV)
	{
		m_posV = posV;
		m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�����_�܂ł̋���
		D3DXVECTOR3 Distance = D3DXVECTOR3((m_posV.x + m_posR.x), (m_posV.y + m_posR.y), (m_posV.z + m_posR.z));

		//���_���璍���_�܂ł̋���������������
		m_fDistance = sqrtf(Distance.x * Distance.x + Distance.z * Distance.z);
		m_fDistance = sqrtf(Distance.y * Distance.y + m_fDistance * m_fDistance);
	}

	// ���_�ʒu�̐ݒ�
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }

	void SetTrackingSize(D3DXVECTOR2 size) { m_pTrackingSize = size; }

	void SetDistance(float fDistance) { m_fDistance = fDistance; }
		
	// ���_�ʒu�̎擾
	D3DXVECTOR3 GetPosV() { return m_posV; }
	// �����_�ʒu�̎擾
	D3DXVECTOR3 GetPosR() { return m_posR; }
	// �p�x�̎擾
	D3DXVECTOR3 GetRotation() { return m_rot; }

	// �Ǐ]�Ώۂ̐ݒ�
	void SetPosTracking(D3DXVECTOR3 *pPosDest) { m_pPosTracking = pPosDest; }

private:
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_posV;				// ���_
	D3DXVECTOR3 m_posR;				// �����_
	D3DXVECTOR3 m_vecU;				// ������x�N�g��
	D3DXVECTOR3 m_rot;				// ����
	D3DXVECTOR3 *m_pPosTracking;	// �Ǐ]�Ώۂ̈ʒu
	D3DXVECTOR2 m_pTrackingSize;	// 
	D3DXVECTOR3 m_posVDest;			// �ړI�̎��_
	D3DXVECTOR3 m_posRDest;			// �ړI�̒����_
	float m_fDistance;				// ���_���璍���_�܂ł̋���
	float m_fNear;					// ����p
	D3DXMATRIX m_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X
};

#endif

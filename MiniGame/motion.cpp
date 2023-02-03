//===================================================================
//
//	���f������[motion.cpp]
//	Author:SHUGO KURODA
//
//===================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "manager.h"
#include "renderer.h"
#include "motion.h"

#include "input.h"
#include "camera.h"
//#include "shadow.h"
#include "bullet.h"
#include "load.h"
#include "enemy.h"

// �ǉ�
#include "x_file_motion.h"
#include "debugproc.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define BLEND_NUM		(5)		// ���[�V�����u�����h�ɂ�����t���[����

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CMotion::CMotion() :
	m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f), m_rotDest(0.0f, 0.0f, 0.0f), m_bChange(false),
	m_vtxMax(0.0f, 0.0f, 0.0f), m_vtxMin(0.0f, 0.0f, 0.0f), m_col(0.0f, 0.0f, 0.0f, 0.0f), m_fLength(0.0f)
{
	//������
	memset(&m_animIdx, 0, sizeof(AnimIdx));

	//���[�V�������̏�����
	//memset(&m_motion, 0, sizeof(ModelMotion));
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CMotion::~CMotion()
{
}

//-----------------------------------------------------------------------------
// ����
// const D3DXVECTOR3& pos �� ��������ʒu
// const D3DXVECTOR3& rot �� ��������p�x
// const char* name �� �������閼�O(���)
//-----------------------------------------------------------------------------
CMotion* CMotion::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// �C���X�^���X����
	CMotion *pMotion = new CMotion;

	// �ʒu�ݒ�
	pMotion->SetPosition(pos);

	// �p�x�ݒ�
	pMotion->SetRotation(rot);

	// ���[�V�������̊���3����
	pMotion->BindMotion(CManager::GetManager()->GetMotion()->GetMotion(name));

	// ������
	pMotion->Init();

	return pMotion;
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
HRESULT CMotion::Init()
{
	// ���[�V�������̏�����
	Change(0, 0);

	// �����x�̐ݒ�
	m_col.a = 1.0f;

	// �L�[�ԍ��̏�����
	m_animIdx.nKeySetIdx = 1;

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------
void CMotion::Uninit()
{
	Release();
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void CMotion::Update()
{
	//for (int nCntVtx = 0; nCntVtx < MAX_MODEL_TYPE; nCntVtx++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	//	{
	//		//�O��̈ʒu��ۑ�
	//		g_aModel[nCnt].posOld = g_aModel[nCnt].pos;

	//		//�����蔻��
	//		//CollisionPlayer(&g_aModel[nCnt].pos, &g_aModel[nCnt].posOld, &g_aModel[nCnt].Airmove, g_aModel[nCnt].fWidth, g_aModel[nCnt].fHeight);
	//	}
	//}
}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void CMotion::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�̃��[���h�}�g���b�N�X
	D3DXMATRIX mtxWorldParent;
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏������i�e�j
	D3DXMatrixIdentity(&mtxWorldParent);

	// �v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&mtxWorldParent, &mtxWorldParent, &mtxRot);

	// �v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&mtxWorldParent, &mtxWorldParent, &mtxTrans);

	for (int nCntParts = 0; nCntParts < m_motion.nNumParts; nCntParts++)
	{
		D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
		D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

		// ���[���h�}�g���b�N�X�̏������i�q�j
		D3DXMatrixIdentity(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_motion.aParts[nCntParts].rot.y, m_motion.aParts[nCntParts].rot.x, m_motion.aParts[nCntParts].rot.z);

		D3DXMatrixMultiply(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			m_motion.aParts[nCntParts].pos.x, m_motion.aParts[nCntParts].pos.y, m_motion.aParts[nCntParts].pos.z);

		D3DXMatrixMultiply(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &mtxTrans);

		// �����̐e���f���̃}�g���b�N�X�Ƃ̊|���Z
		if (m_motion.aParts[nCntParts].nParent < 0)
		{
			// ���f���̃}�g���b�N�X �� �e�̃��[���h�}�g���b�N�X
			D3DXMatrixMultiply(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &mtxWorldParent);
		}
		else
		{
			// ���f���̃}�g���b�N�X �� �e�̃��[���h�}�g���b�N�X
			D3DXMatrixMultiply(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nParent].mtxWorld);
		}

		if (m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.pMesh == NULL)
		{// �p�[�c�̃��f����NULL��������
			continue;		// for���̍ŏ��ɖ߂�
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld);

		// ���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.nNumMat; nCntMat++)
		{
			// �F�ۑ��p
			D3DCOLORVALUE diffuse = pMat[nCntMat].MatD3D.Diffuse;

			// �F������������
			if (pMat[nCntMat].MatD3D.Diffuse.r <= 0.0f &&
				pMat[nCntMat].MatD3D.Diffuse.g <= 0.0f &&
				pMat[nCntMat].MatD3D.Diffuse.b <= 0.0f)
			{// ����̐F��ݒ�
				pMat[nCntMat].MatD3D.Diffuse = (D3DCOLORVALUE)m_col;
			}

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.pTexture[nCntMat]);

			// ���f���p�[�c�̕`��
			m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.pMesh->DrawSubset(nCntMat);

			// �e�N�X�`���̐ݒ�����ɖ߂�
			pDevice->SetTexture(0, NULL);

			// �F�����ɖ߂�
			pMat[nCntMat].MatD3D.Diffuse = diffuse;
		}

		// �ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//-----------------------------------------------------------------------------
// �p�x�̐��K��
//-----------------------------------------------------------------------------
void CMotion::NormalizeRot()
{
	//�p�x�̍X�V
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2;
	}
	if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2;
	}

	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	//�p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//-----------------------------------------------------------------------------
// ���[�V�����Đ�
//-----------------------------------------------------------------------------
bool CMotion::Motion()
{
	// �f�o�b�N�\��
	//CManager::GetManager()->GetDebugProc()->Print("%f%f%f", m_motion.aParts[0].pos.x, m_motion.aParts[0].pos.y, m_motion.aParts[0].pos.z);

	// ���[�V�����؂�ւ����̓��[�V�����Đ����s��Ȃ�
	if (m_bChange == true)
	{
		return false;
	}

	int nMotion = m_animIdx.nMotionIdx;
	int nKey = m_animIdx.nKeySetIdx;
	int nFrame = m_motion.aMotion[nMotion].aKeyInfo[nKey].nFrame;
	int nNumKey = m_motion.aMotion[nMotion].nNumKey;

	if (nFrame <= 0)
	{// �e�L�X�g�Őݒ肳�ꂽ�t���[������0�ȉ��������ꍇ
		nFrame = 1;
	}

	// ���[�V�����Đ�����
	for (int nCntParts = 0; nCntParts < m_motion.nNumParts; nCntParts++)
	{
		// �ʒu�X�V�i���[�J�����W�j
		m_motion.aParts[nCntParts].pos += (m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[nCntParts].pos - m_motion.aMotion[nMotion].aKeyInfo[((nKey - 1) + nNumKey) % nNumKey].aKey[nCntParts].pos) / (float)nFrame;

		// �p�x�X�V
		m_motion.aParts[nCntParts].rot += (m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[nCntParts].rot - m_motion.aMotion[nMotion].aKeyInfo[((nKey - 1) + nNumKey) % nNumKey].aKey[nCntParts].rot) / (float)nFrame;
	}

	// �t���[���̉��Z
	m_animIdx.nFrame++;

	if (m_motion.aMotion[nMotion].aKeyInfo[nKey].nFrame <= m_animIdx.nFrame)
	{// �t���[�������ݒ�̒l�𒴂�����

		// �Đ����̃L�[���̉��Z
		m_animIdx.nKeySetIdx++;

		// �t���[���̏�����
		m_animIdx.nFrame = 0;

		if (m_motion.aMotion[nMotion].nNumKey <= m_animIdx.nKeySetIdx)
		{// �Đ����̃L�[�����ݒ�̒l�𒴂�����
			if (m_motion.aMotion[nMotion].nLoop == 1)
			{
				m_animIdx.nKeySetIdx = 0;
			}
			else
			{// ���ݍĐ����̃��[�V��������j���[�g�������[�V�����ɕύX
				m_animIdx.nKeySetIdx = 0;
				m_animIdx.nMotionIdx = 0;

				// �Đ��I��
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
// ���[�V�����ݒ�(�؂�ւ�)
// const int& nNum �� �Đ����郂�[�V�����ԍ�
//-----------------------------------------------------------------------------
void CMotion::Set(const int& nNum)
{
	if (m_bChange == true && m_animIdx.nMotionIdx == nNum)
	{
		// ���[�V�����̏�����
		Change(nNum, 0);
		m_bChange = false;
	}
	// ���݂̃��[�V�������Đ����郂�[�V�����ȊO
	else if (m_animIdx.nMotionIdx != nNum)
	{// ���[�V�����̐ݒ�

		// �t���[�����̏�����
		if (m_bChange == false)
		{
			int nMotion = m_animIdx.nMotionIdx;
			int nKey = m_animIdx.nKeySetIdx;
			int nFrame = m_motion.aMotion[nMotion].aKeyInfo[nKey].nFrame;
			int nNumKey = m_motion.aMotion[nMotion].nNumKey;

			// ��(�e�p�[�c)�̃��[�J�����W��߂�
			m_motion.aParts[0].pos = m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[0].pos + m_motion.posParent;

			// �e�p�[�c�̃��[�J�����W��ۑ�
			for (int nCntParts = 0; nCntParts < m_motion.nNumParts; nCntParts++)
			{
				m_motion.aParts[nCntParts].changeRot = m_motion.aParts[nCntParts].rot;
			}

			// �t���[�����̏�����
			m_animIdx.nFrame = 0;

			// ���[�V�����؂�ւ���
			m_bChange = true;

			//// �U�����[�V�����Ȃ�
			//if (nNum == 2)
			//{
			//	// ���[�V�����̏�����
			//	Change(nNum, 0);
			//	m_animIdx.nMotionIdx = nNum;
			//	m_animIdx.nKeySetIdx = 1;
			//	m_animIdx.nFrame = 0;
			//	m_bChange = false;
			//}
		}

		// ���[�V�����Đ�����
		for (int nCntParts = 0; nCntParts < m_motion.nNumParts; nCntParts++)
		{
			// �p�x�X�V
			m_motion.aParts[nCntParts].rot += (m_motion.aMotion[nNum].aKeyInfo[0].aKey[nCntParts].rot - m_motion.aParts[nCntParts].changeRot) / (float)BLEND_NUM;
		}

		// �t���[�����̏�����
		m_animIdx.nFrame++;

		if (BLEND_NUM <= m_animIdx.nFrame)
		{
			m_animIdx.nMotionIdx = nNum;
			m_animIdx.nKeySetIdx = 1;
			m_animIdx.nFrame = 0;

			// ���[�V�����؂�ւ��I��
			m_bChange = false;
		}
	}
}

//-----------------------------------------------------------------------------
// ���[�V�����ύX(������)
//-----------------------------------------------------------------------------
void CMotion::Change(const int& nMotion, const int& nKey)
{
	// ��(�e�p�[�c)�̃��[�J�����W��߂�
	m_motion.aParts[0].pos = m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[0].pos + m_motion.posParent;

	for (int nCntParts = 0; nCntParts < m_motion.nNumParts; nCntParts++)
	{
		m_motion.aParts[nCntParts].rot = m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[nCntParts].rot;
	}
}

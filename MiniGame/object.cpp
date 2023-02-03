//=============================================================================
//
// �I�u�W�F�N�g����[object.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "object.h"
#include "manager.h"
#include "renderer.h"

#include "object2D.h"
#include "library.h"
#include "game.h"

//*****************************************************************************
//	�ÓI�����o�ϐ�
//*****************************************************************************
CObject* CObject::m_apObject[MAX_OBJECT] = { nullptr };
int CObject::m_nNumAll = 0;
int CObject::m_nShakeInterval = 0;
bool CObject::m_bShake = false;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CObject::CObject() :m_nType(OBJ_NONE), m_nID(0)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == nullptr)
		{
			// �I�u�W�F�N�g�����i�[
			m_apObject[nCntObject] = this;
			// �I�u�W�F�N�g�ԍ��̕ۑ�
			m_nID = nCntObject;
			// ���v�I�u�W�F�N�g�������Z
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
//	�����[�X����
//=============================================================================
void CObject::ReleaseAll()
{
	for (int nCntUninit = 0; nCntUninit < MAX_OBJECT; nCntUninit++)
	{
		// �I�u�W�F�N�g�C���X�^���X�̔j��
		if (m_apObject[nCntUninit] != nullptr)
		{
			// �I�u�W�F�N�g�̏I������
			m_apObject[nCntUninit]->Uninit();

			// �������̊J��
			delete m_apObject[nCntUninit];
			m_apObject[nCntUninit] = nullptr;
		}
	}
}

//=============================================================================
//	�X�V����
//=============================================================================
void CObject::UpdateAll()
{
	// �|�[�Y���̎擾
	bool bPause = CManager::GetManager()->GetPause();

	// �|�[�Y���łȂ��Ȃ�
	if (bPause == false)
	{
		for (int nCntUpdate = 0; nCntUpdate < MAX_OBJECT; nCntUpdate++)
		{
			if (m_apObject[nCntUpdate] != nullptr)
			{
				// �|���S���̍X�V����
				m_apObject[nCntUpdate]->Update();
			}
		}

		// ��ʃV�F�C�N�t���O�������Ă���Ȃ�
		if (m_bShake == true)
		{//��ʃV�F�C�N����
			ShakeAll();
		}
	}
	// �|�[�Y���Ȃ�
	else if (bPause == true)
	{
		for (int nCntUpdate = 0; nCntUpdate < MAX_OBJECT; nCntUpdate++)
		{
			if (m_apObject[nCntUpdate] != nullptr)
			{
				//�|�[�Y��ʂ̂ݍX�V
				if (m_apObject[nCntUpdate]->m_nType == OBJ_PAUSE || m_apObject[nCntUpdate]->m_nType == OBJ_PAUSE_MENU)
				{
					// �X�V����
					m_apObject[nCntUpdate]->Update();
				}
			}
		}
	}
}

//=============================================================================
//	�`�揈��
//=============================================================================
void CObject::DrawAll()
{
	//�I�u�W�F�N�g���̕ۑ��p
	CObject *apObject[MAX_OBJECT];
	CObject *pObject;

	// �I�u�W�F�N�g����ۑ�
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		apObject[nCntObject] = m_apObject[nCntObject];
	}

	// �I���\�[�g�ŕ`�揇�̕��ёւ�(����)
	for (int nNum01 = 0; nNum01 < MAX_OBJECT - 1; nNum01++)
	{
		for (int nNum02 = nNum01 + 1; nNum02 < MAX_OBJECT; nNum02++)
		{
			// ��r�ΏۂɃI�u�W�F�N�g��񂪂�������
			if (apObject[nNum01] != nullptr && apObject[nNum02] != nullptr)
			{
				// �I�u�W�F�N�g��D�揇�ɕ��ёւ�
				if (apObject[nNum01]->m_nType > apObject[nNum02]->m_nType)
				{
					pObject = apObject[nNum01];
					apObject[nNum01] = apObject[nNum02];
					apObject[nNum02] = pObject;
				}
			}
		}
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �`��
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (apObject[nCntObject] != nullptr)
		{
			if (apObject[nCntObject]->m_nType == OBJ_BG)
			{
				//�J�����O��OFF�ɂ���
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

				// �`�揈��
				apObject[nCntObject]->Draw();

				//�J�����O��ON�ɖ߂�
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			}
			else
			{
				// �`�揈��
				apObject[nCntObject]->Draw();
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g��h�炷
//=============================================================================
void CObject::ShakeAll()
{
	//if (m_nShakeInterval < 0)
	//{//�V�F�C�N���I����
	//	m_bShake = false;
	//	return;
	//}

	//// �ːi����p�x�����߂�
	//float fRot = LibrarySpace::GetRandFloat(3, 0, 100);

	//// �V�F�C�N(�ړ�)�ʂ̐ݒ�
	//D3DXVECTOR3 move = D3DXVECTOR3(sinf(fRot) * m_nShakeInterval, cosf(fRot) * m_nShakeInterval, 0);

	//for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	//{
	//	if (m_apObject[nCntObject] != nullptr)
	//	{
	//		if (m_apObject[nCntObject]->m_nType != OBJ_PLAYER &&
	//			m_apObject[nCntObject]->m_nType != OBJ_BG_MOVE&&
	//			m_apObject[nCntObject]->m_nType != OBJ_PAUSE)
	//		{
	//			//�I�u�W�F�N�g�|�C���^��G�ɃL���X�g
	//			CObject2D *pObject2D = (CObject2D*)m_apObject[nCntObject];

	//			// �V�F�C�N(�ړ�)�ʂ̉��Z
	//			pObject2D->SetMove(D3DXVECTOR3(sinf(fRot) * m_nShakeInterval,
	//				cosf(fRot) * m_nShakeInterval, 0));
	//		}
	//	}
	//}

	//// �{�X��w�i���̎擾
	//CMeshField* pMeshField = CGame::GetMeshField();

	//// �V�F�C�N(�ړ�)�ʂ̉��Z
	//pMeshField->SetMove(D3DXVECTOR3(sinf(fRot) * m_nShakeInterval,
	//	cosf(fRot) * m_nShakeInterval, 0));

	//// �V�F�C�N����b��(�U�ꕝ)�����炷
	//m_nShakeInterval--;
}

void CObject::SetShake(int nShakeNum)
{
	m_bShake = true;
	m_nShakeInterval = nShakeNum;
}

//=============================================================================
// ����̃I�u�W�F�N�g�j��
//=============================================================================
void CObject::Release()
{
	// �I�u�W�F�N�g�C���X�^���X�̔j��
	if (m_apObject[m_nID] != nullptr)
	{
		// �I������
 		int nID = m_nID;
		delete m_apObject[nID];
		m_apObject[nID] = nullptr;
		m_nNumAll--;
	}
}

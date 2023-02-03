//===================================================================
//
//	3D�|���S������ [object3D.cpp]
//	Author:SHUGO KURODA
//
//===================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include "tutorial.h"

#include "input_keyboard.h"

#include "title.h"
#include "player.h"
#include "library.h"

//======================================================
//	�}�N����`
//======================================================
#define SIZE		(50.0f)

//======================================================
//	�R���X�g���N�^
//======================================================
CTutorial::CTutorial() :m_bDis(false), m_pObj(nullptr)
{
}

//======================================================
//	�f�X�g���N�^
//======================================================
CTutorial::~CTutorial()
{
}

//======================================================
//	��������
//======================================================
CTutorial *CTutorial::Create(const D3DXVECTOR3& pos)
{
	//�C���X�^���X����
	CTutorial *pObject3D = new CTutorial;

	// �ʒu�ݒ�
	pObject3D->SetPosition(pos);

	// ������
	pObject3D->Init();

	// �e�N�X�`���̊��蓖��
	pObject3D->BindTexture(CManager::GetManager()->GetTexture()->GetTexture("TEX_TYPE_TUTORIAL_BUTTON"));

	return pObject3D;
}

//======================================================
//	����������
//======================================================
HRESULT CTutorial::Init()
{
	// �T�C�Y�̐ݒ�
	SetSize(D3DXVECTOR2(SIZE, SIZE));

	// ������
	CObject3D::Init();

	return S_OK;
}

//======================================================
//	�I������
//======================================================
void CTutorial::Uninit()
{
	CObject3D::Uninit();
}

//======================================================
//	�X�V����
//======================================================
void CTutorial::Update()
{
	bool bPush = false;

	if (CManager::GetManager()->GetTitle() != nullptr)
	{
		int nMax = CManager::GetManager()->GetTitle()->GetEntry();

		for (int nCnt = 0; nCnt <= nMax; nCnt++)
		{
			CPlayer* pPlayer = CManager::GetManager()->GetTitle()->GetPlayer(nCnt);

			if (pPlayer != nullptr)
			{
				if (LibrarySpace::SphereCollision(D3DXVECTOR3(GetPosition().x, GetPosition().y, GetPosition().z - 50.0f),
					pPlayer->GetPosition(), 0.0f, SIZE / 2) == true)
				{
					if (m_pObj == nullptr)
					{
						m_pObj = CObject3D::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR2(150.0f, 60.0f));
						m_pObj->BindTexture(CManager::GetManager()->GetTexture()->GetTexture("TEX_TYPE_TUTORIAL_IMAGE"));
						m_pObj->SetRotation(D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f));
					}
					break;
				}
				else if (nCnt == nMax - 1)
				{
					if (m_pObj != nullptr)
					{
						m_pObj->Uninit();
						m_pObj = nullptr;
					}
				}
			}
		}
	}
}

//======================================================
//	�`�揈��
//======================================================
void CTutorial::Draw()
{
	CObject3D::Draw();
}

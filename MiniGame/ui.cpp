//-----------------------------------------------------------------------------------------------
//
// ���S����[logo.cpp]
// Author : SHUGO KURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "ui.h"
#include "manager.h"	// �A�v���P�[�V����
#include "renderer.h"	// �����_�����O
#include "base.h"

#include "game.h"
#include "player.h"

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CUi::m_pTexture[TYPE_MAX] = {};

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CUi::CUi() :m_nCountUninit(0), m_AnimType(ANIM_NONE)
{
	SetType(EObject::OBJ_UI);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CUi::~CUi()
{

}

//-----------------------------------------------------------------------------------------------
// ����
// const D3DXVECTOR3& pos �� ��������ʒu
// const D3DXVECTOR2& size �� ��������T�C�Y
// const LOGOTYPE& type �� ����������
// const ANIMTYPE& AnimType �� �A�j���[�V�����̎��
// const PARENT& parent ��	�ǂ̃v���C���[��UI��
//-----------------------------------------------------------------------------------------------
CUi* CUi::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const TYPE& type, const ANIMTYPE& AnimType, const PARENT& parent)
{
	// �|�C���^�N���X��錾
	CUi* pUi = new CUi;

	if (pUi != nullptr)
	{// ����nullptr�ł͂Ȃ�������

		// �ʒu�ݒ�
		pUi->SetPosition(pos);

		// �T�C�Y�ݒ�
		pUi->SetSize(size);

		// �A�j���[�V�����̎�ނ�ݒ�
		pUi->m_AnimType = AnimType;

		// �e�̐ݒ�
		pUi->m_parent = parent;

		// ������
		pUi->Init();

		// �e�N�X�`���̐ݒ�
		pUi->BindTexture(m_pTexture[type]);
	}

	return pUi;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CUi::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI000.png",
		&m_pTexture[TYPE_AREA_A]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI001.png",
		&m_pTexture[TYPE_PLAYER1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI002.png",
		&m_pTexture[TYPE_PLAYER2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI003.png",
		&m_pTexture[TYPE_PRESS_ANY_BUTTON]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI004.png",
		&m_pTexture[TYPE_TO_START]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI005.png",
		&m_pTexture[TYPE_LIFE1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI006.png",
		&m_pTexture[TYPE_LIFE2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI007.png",
		&m_pTexture[TYPE_BULLET]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI008.png",
		&m_pTexture[TYPE_BULLET_OPTION]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI009.png",
		&m_pTexture[TYPE_BARRIER]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI011.png",
		&m_pTexture[TYPE_OK]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/UI012.png",
		&m_pTexture[TYPE_CONTINUE]);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̍폜
//-----------------------------------------------------------------------------------------------
void CUi::Unload()
{
	for (int nCnt = 0; nCnt >= TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CUi::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CUi::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CUi::Update()
{
	// �e�v���C���[���Q�����Ă��Ȃ����
	if (m_parent == PLAYER_1_NOT_ENTRY || m_parent == PLAYER_2_NOT_ENTRY)
	{
		//// �v���C���[���̎擾
		//bool bEntry = CManager::GetManager()->GetEntry(m_parent - 2);

		//// �e�v���C���[���Q��������
		//if (bEntry == true)
		//{// �j��
		//	Uninit();
		//	return;
		//}
	}
	// �e�v���C���[�������
	else if (m_parent != PLAYER_NONE)
	{
		// �v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(m_parent);

		// �e�v���C���[���j������Ă�����
		if (pPlayer == nullptr)
		{// �j��
			Uninit();
			return;
		}
	}

	switch (m_AnimType)
	{
	case CUi::ANIM_FLASHING:

		// �J�E���g�𑝂₷
		m_nCountUninit++;

		if (m_nCountUninit >= 120)
		{
			m_nCountUninit = 0;
		}
		else if (m_nCountUninit >= 60)
		{
			CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		else if (m_nCountUninit >= 0)
		{
			CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;

	default:
		break;
	}

	//���_���W�̐ݒ�
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CUi::Draw()
{
	CObject2D::Draw();
}
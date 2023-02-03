//-----------------------------------------------------------------------------------------------
//
// �Q�[�W����[gaugev.cpp]
// Author : SHUGO KURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "gauge.h"
#include "manager.h"	// �A�v���P�[�V����
#include "renderer.h"	// �����_�����O

#include "game.h"
#include "player.h"

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// �T�C�YX
const float CGauge::SIZE_X = 75.0f;
// �T�C�YY
const float CGauge::SIZE_Y = 30.0f;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CGauge::m_pTexture = {};

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CGauge::CGauge() :m_type(TYPE_NONE), m_parent(PLAYER_1)
{
	SetType(EObject::OBJ_UI);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CGauge::~CGauge()
{
}

//-----------------------------------------------------------------------------------------------
// ����
// const D3DXVECTOR3& pos �� ��������ʒu
// const TYPE& type �� ����������
// const PARENT& parent ��	�ǂ̃v���C���[�̃Q�[�W��
//-----------------------------------------------------------------------------------------------
CGauge* CGauge::Create(const D3DXVECTOR3& pos, const TYPE& type, const PARENT& parent)
{
	// �|�C���^�N���X��錾
	CGauge* pGauge = new CGauge;

	if (pGauge != nullptr)
	{// ����nullptr�ł͂Ȃ�������

		 // �ʒu�ݒ�
		pGauge->SetPosition(pos);

		// ��ނ�ݒ�
		pGauge->m_type = type;

		// �e�̐ݒ�
		pGauge->m_parent = parent;

		// ������
		pGauge->Init();

		// �e�N�X�`���̐ݒ�
		pGauge->BindTexture(m_pTexture);
	}

	return pGauge;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CGauge::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui010.png",
		&m_pTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̍폜
//-----------------------------------------------------------------------------------------------
void CGauge::Unload()
{
	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CGauge::Init()
{
	//�T�C�Y�̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2(SIZE_X, SIZE_Y));

	//������
	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CGauge::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CGauge::Update()
{
	//// �v���C���[���̎擾
	//CPlayer *pPlayer = CGame::GetPlayer(m_parent);

	//// �e�v���C���[���j������Ă�����
	//if (pPlayer == nullptr)
	//{// �j��
	//	Uninit();
	//	return;
	//}

	//// �ϐ��錾
	//D3DXVECTOR2 size = GetSize();
	//int nPlayerLevel = 0;

	//switch (m_type)
	//{
	//	// ���C���e
	//case CGauge::TYPE_BULLET:
	//	// ���C���e�̋����i�K�̎擾
	//	nPlayerLevel = pPlayer->GetBulletLevel();

	//	// ���T�C�Y����
	//	size.x = SIZE_X / ((float)MAX_LEVEL / ((float)nPlayerLevel + 1.0f));

	//	// �摜�̕`��͈͂𒲐�
	//	CObject2D::SetTextureRange(nPlayerLevel + 1, MAX_LEVEL);
	//	break;

	//	// �I�v�V�����e
	//case CGauge::TYPE_BULLET_OPTION:

	//	// �I�v�V�����e�̋����i�K�̎擾
	//	nPlayerLevel = pPlayer->GetOptionLevel();

	//	// ���T�C�Y����
	//	size.x = SIZE_X / ((float)MAX_LEVEL / ((float)nPlayerLevel));

	//	// �摜�̕`��͈͂𒲐�
	//	CObject2D::SetTextureRange(nPlayerLevel, MAX_LEVEL);
	//	break;

	//	// �o���A
	//case CGauge::TYPE_BARRIER:
	//	// �o���A�̋����i�K�̎擾
	//	nPlayerLevel = pPlayer->GetBarrierLevel();

	//	// ���T�C�Y����
	//	size.x = SIZE_X / ((float)MAX_LEVEL / ((float)nPlayerLevel));

	//	// �摜�̕`��͈͂𒲐�
	//	CObject2D::SetTextureRange(nPlayerLevel, MAX_LEVEL);
	//	break;
	//default:
	//	break;
	//}

	////�T�C�Y�̐ݒ�
	//CObject2D::SetSize(size);

	////���_���W�̐ݒ�
	//CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CGauge::Draw()
{
	CObject2D::Draw();
}
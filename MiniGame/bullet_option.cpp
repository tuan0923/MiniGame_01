//-----------------------------------------------------------------------------------------------
//
// �e�̏���[bullet.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "bullet_option.h"
#include "bullet.h"
#include "manager.h"
#include "renderer.h"

#include "library.h"
#include "game.h"

#include "enemy.h"
#include "explosion.h"

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CBulletOption::m_apTexture = { nullptr };

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CBulletOption::CBulletOption() :m_fRad(0.0f), m_col(FADE_NONE), m_nCounterAttack(0)
{
	SetType(EObject::OBJ_BULLET);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CBulletOption::~CBulletOption()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CBulletOption* CBulletOption::Create(const float& fRot, const PARENT& parent)
{
	// �|�C���^�N���X��錾
	CBulletOption* pOption = new CBulletOption;

	if (pOption != nullptr)
	{// ����nullptr�ł͂Ȃ�������

		// �p�x�̐ݒ�
		pOption->m_fRad = fRot;

		//�e�̐ݒ�(���L����v���C���[)
		pOption->m_parent = parent;

		// ������
		pOption->Init();

		// �e�N�X�`���̐ݒ�
		pOption->BindTexture(m_apTexture);
	}

	return pOption;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CBulletOption::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/option000.png",
		&m_apTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̍폜
//-----------------------------------------------------------------------------------------------
void CBulletOption::Unload()
{
	// �e�N�X�`���̔j��
	if (m_apTexture != nullptr)
	{
		m_apTexture->Release();
		m_apTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CBulletOption::Init()
{
	// �v���C���[�ʒu�̎擾
	D3DXVECTOR3 posPlayer = CManager::GetManager()->GetGame()->GetPlayer(m_parent)->GetPosition();

	// �ʒu�ݒ�
	CObject2D::SetPosition(D3DXVECTOR3(posPlayer.x - sinf(m_fRad) * 100,
		posPlayer.y - cosf(m_fRad) * 100,
		0.0f));

	// �F��Ԃ̏�����
	m_col = FADE_GREEN;

	//�T�C�Y�̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2((float)SIZE, (float)SIZE));

	// ������
	CObject2D::Init();

	// �F�ݒ�
	CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CBulletOption::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CBulletOption::Update()
{
	// �F�̎擾
	D3DXCOLOR col = GetColor();

	//�F����ɕω�������
	if (m_col == FADE_RED)
	{
		col.r += 0.01f;
		col.b -= 0.01f;
		if (col.r >= 1.0f)
		{
			m_col = FADE_GREEN;
		}
	}
	else if (m_col == FADE_GREEN)
	{
		col.g += 0.01f;
		col.r -= 0.01f;
		if (col.g >= 1.0f)
		{
			m_col = FADE_BLUE;
		}
	}
	else if (m_col == FADE_BLUE)
	{
		col.b += 0.01f;
		col.g -= 0.01f;
		if (col.b >= 1.0f)
		{
			m_col = FADE_RED;
		}
	}

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// �v���C���[�ʒu�̎擾
	D3DXVECTOR3 posPlayer;

	CPlayer* pPlayer = CManager::GetManager()->GetGame()->GetPlayer(m_parent);
	if (pPlayer != nullptr)
	{
		posPlayer = CManager::GetManager()->GetGame()->GetPlayer(m_parent)->GetPosition();

		// �ʒu�̍X�V(�v���C���[�𒆐S�ɉ�]������)
		pos = D3DXVECTOR3(posPlayer.x - sinf(m_fRad) * 100,
			posPlayer.y - cosf(m_fRad) * 100,
			0.0f);
	}
	else
	{
		Uninit();
		return;
	}

	// ��]�ʂ̉��Z
	m_fRad += 0.1f;
	if (m_fRad >= D3DX_PI * 2)
	{
		m_fRad = 0.0f;
	}

	// �ʒu�̍X�V
	CObject2D::SetPosition(pos);

	// �F�̐ݒ�
	SetColor(col);

	//���_���W�̐ݒ�
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CBulletOption::Draw()
{
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------------------------
// �U������
//-----------------------------------------------------------------------------------------------
void CBulletOption::Attack()
{
	// �J�E���^�[���Z
	m_nCounterAttack++;

	// �J�E���^�[����萔�ȏ�
	if (m_nCounterAttack >= 5)
	{
		//�J�E���^�[������
		m_nCounterAttack = 0;

		// �ʒu�̎擾
		D3DXVECTOR3 pos = GetPosition();

		//�e�̐ݒ�
		CBullet::Create(pos, D3DXVECTOR3(15.0f, 0.0f, 0.0f),
			DAMAGE, CBullet::TYPE_PLAYER_GREEN)->SetParent((CBullet::EParent)m_parent);
	}
}

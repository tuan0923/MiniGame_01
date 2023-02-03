//-----------------------------------------------------------------------------------------------
//
// ���S����[logo_extend.cpp]
// Author : SHUGO KURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "logo_extend.h"
#include "manager.h"		// �A�v���P�[�V����
#include "renderer.h"		// �����_�����O
#include "fade.h"
#include "game.h"

#include "texture.h"

#include "camera.h"

//-----------------------------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------------------------
#define EXTEND_SPEED		(20.0f)		// �A�j���[�V�����̑��x

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CLogoExtend::CLogoExtend() :m_DefaultSize(0.0f, 0.0f), m_anim(ANIM_NONE), m_bSceneChange(false)
{
	SetType(EObject::OBJ_LOGO);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CLogoExtend::~CLogoExtend()
{
}

//-----------------------------------------------------------------------------------------------
// ����
// const D3DXVECTOR3& pos �� ��������ʒu
// const D3DXVECTOR2& size �� ��������T�C�Y
// const char* name �� ��������e�N�X�`��
// const int& nCount �� �j������܂ł̎���
//-----------------------------------------------------------------------------------------------
CLogoExtend* CLogoExtend::Create(const D3DXVECTOR2& size, const char* name, const int& nCount)
{
	// �|�C���^�N���X��錾
	CLogoExtend* pLogoExtend = new CLogoExtend;

	if (pLogoExtend != nullptr)
	{// ����nullptr�ł͂Ȃ�������

		// �T�C�Y�̕ۑ�
		pLogoExtend->m_DefaultSize = size;

		// �j���J�E���^�[��ݒ�
		pLogoExtend->SetCountUninit(nCount);

		// ������
		pLogoExtend->Init();

		// �e�N�X�`���̐ݒ�
		pLogoExtend->BindTexture(CManager::GetManager()->GetTexture()->GetTexture(name));
	}

	return pLogoExtend;
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CLogoExtend::Init()
{
	// �ʒu�ݒ�
	SetPosition(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
	// �������̐ݒ�
	m_anim = ANIM_Y_EXPAND;
	// �T�C�Y�̐ݒ�
	SetSize(D3DXVECTOR2(m_DefaultSize.x, 0.0f));
	//������
	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CLogoExtend::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CLogoExtend::Update()
{
	// �j���J�E���^�[�̎擾
	int nCountUninit = GetCountUninit();

	// �J�E���g�����炷
	nCountUninit--;

	// �\���J�E���^�[��0�ȉ�
	if (nCountUninit <= 0)
	{
		// ��ʑJ�ڔ��肪ON�Ȃ�
		if (m_bSceneChange == true)
		{
			// ���[�h�̐ݒ�
			CManager::GetManager()->GetGame()->SetCameraPlayer(true);
		}

		// �j��
		Uninit();
		return;
	}

	// �j���J�E���^�[�̐ݒ�
	SetCountUninit(nCountUninit);

	// �������̐ݒ�
	Pattern();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CLogoExtend::Draw()
{
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------------------------
// �������̐ݒ�
//-----------------------------------------------------------------------------------------------
void CLogoExtend::Pattern()
{
	// �T�C�Y�̎擾
	D3DXVECTOR2 size = GetSize();

	// �������̐ݒ�
	switch (m_anim)
	{
		// �c�ɍL����
	case CLogoExtend::ANIM_Y_EXPAND:

		// �T�C�Y�̉��Z
		size.y += EXTEND_SPEED;
		// �w��̃T�C�Y�ɒB������
		if (size.y >= m_DefaultSize.y * 2.0f)
		{
			m_anim = ANIM_Y_SHORTEN;
		}

		break;

		// �c�ɏk��
	case CLogoExtend::ANIM_Y_SHORTEN:

		// �T�C�Y�̉��Z
		size.y -= EXTEND_SPEED;
		// �w��̃T�C�Y�ɒB������
		if (size.y <= m_DefaultSize.y)
		{
			m_anim = ANIM_X_EXPAND;
		}

		break;

		// ���ɍL����
	case CLogoExtend::ANIM_X_EXPAND:

		// �T�C�Y�̉��Z
		size.x += EXTEND_SPEED;
		// �w��̃T�C�Y�ɒB������
		if (size.x >= m_DefaultSize.x * 1.5f)
		{
			m_anim = ANIM_X_SHORTEN;
		}
		break;

		// ���ɏk��
	case CLogoExtend::ANIM_X_SHORTEN:

		// �T�C�Y�̉��Z
		size.x -= EXTEND_SPEED;
		// �w��̃T�C�Y�ɒB������
		if (size.x <= m_DefaultSize.x)
		{
			m_anim = ANIM_NONE;
		}
		break;

	default:
		break;
	}

	if (m_anim != ANIM_NONE)
	{
		// �T�C�Y�̐ݒ�
		SetSize(size);

		// ���_���W�̐ݒ�
		SetVertex();
	}
}

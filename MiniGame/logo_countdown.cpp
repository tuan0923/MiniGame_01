//=============================================================================
//
// �J�E���g�_�E�����S����[logo_countdown.cpp]
// Author : SHUGO KURODA
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "game.h"
#include "boss.h"
#include "logo_countdown.h"
#include "number.h"
#include "renderer.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COUNT_SIZE		(100.0f)
#define COUNT_UNINIT	(60)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLogoCountDown::CLogoCountDown() :m_nNum(0)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLogoCountDown::~CLogoCountDown()
{
}

//=============================================================================
// ����
//=============================================================================
CLogoCountDown *CLogoCountDown::Create(const int &nCountStart)
{
	CLogoCountDown *pLogo = new CLogoCountDown;

	if (pLogo != nullptr)
	{
		// �����̐ݒ�
		pLogo->m_nNum = nCountStart;

		// �����|���S������
		pLogo->m_apNumber = new CNumber("TEX_TYPE_SCORE_UI");

		if (pLogo->m_apNumber != nullptr)
		{
			// �ʒu�ݒ�
			pLogo->m_apNumber->SetPosition(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
			// �T�C�Y�ݒ�
			pLogo->m_apNumber->SetSize(D3DXVECTOR2(COUNT_SIZE, COUNT_SIZE));
			// ������
			pLogo->m_apNumber->Init();
		}

		// ������
		pLogo->Init();
	}

	return pLogo;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CLogoCountDown::Init()
{
	// �F�̐ݒ�
	//m_apNumber->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// �j���܂ł̃J�E���^�[�ݒ�
	SetCountUninit(COUNT_UNINIT);
	// ���l�̐ݒ�
	Set();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CLogoCountDown::Uninit()
{
	// ���g������Ȃ�
	if (m_apNumber != nullptr)
	{
		// �������̏I������
		m_apNumber->Uninit();
		m_apNumber = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CLogoCountDown::Update()
{
	int nCounter = GetCountUninit();

	nCounter--;

	// �j���J�E���^�[����萔�ȉ�
	if (nCounter <= 0)
	{
		if (m_nNum > 1)
		{
			Create(m_nNum - 1);

			// ���ʉ�
			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);
		}
		else if (m_nNum == 1)
		{
			// �Q�[���J�n���S�̒ǉ�
			CLogo::Create(m_apNumber->GetPosition(), D3DXVECTOR2(200.0f, 80.0f), "TEX_TYPE_START_UI", 90);

			// ���ʉ�
			CSound::Play(CSound::SOUND_LABEL_SE_START);

			// ���ʉ�
			CSound::Play(CSound::SOUND_LABEL_GAME);

			// �Q�[���̊J�n�t���O�𗧂Ă�
			CManager::GetManager()->GetGame()->SetStart(true);
		}

		// �j��
		Uninit();
		return;
	}

	SetCountUninit(nCounter);

	D3DXVECTOR2 size = m_apNumber->GetSize();

	size.x -= 1.0f;
	size.y -= 1.0f;

	m_apNumber->SetSize(size);

	m_apNumber->SetVertex();
}

//=============================================================================
// �`��
//=============================================================================
void CLogoCountDown::Draw()
{
}

//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
void CLogoCountDown::Set()
{
	//���l���i�[
	int nPosTexU = m_nNum % 10;

	// �e�N�X�`�����W�̍X�V
	m_apNumber->SetAnimation(nPosTexU, 0, CNumber::DIVISION_U, CNumber::DIVISION_V);
}

//=============================================================================
//
// �R���e�B�j���[����[continue.cpp]
// Author : SHUGO KURODA
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"
#include "manager.h"
#include "continue.h"
#include "number.h"
#include "ui.h"
#include "logo.h"
#include "player.h"

#include "input_keyboard.h"
#include "input_joypad.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CContinue::m_pTexture = nullptr;
bool CContinue::m_bContinue = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CContinue::CContinue() :m_nContinue(0), m_pVtxBuff(nullptr), m_apNumber{ nullptr }, m_pUi{ nullptr }, m_nCountDown(0), m_pFade(nullptr)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CContinue::~CContinue()
{
}

//=============================================================================
// ����
//=============================================================================
CContinue *CContinue::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size)
{
	CContinue *pContinue = new CContinue;

	for (int nCntScore = 0; nCntScore < MAX_CONTINUE; nCntScore++)
	{
		// �����|���S������
		pContinue->m_apNumber[nCntScore] = new CNumber("TEX_TYPE_SCORE_UI");

		if (pContinue->m_apNumber[nCntScore] != nullptr)
		{
			// �ʒu�ݒ�
			pContinue->m_apNumber[nCntScore]->SetPosition(D3DXVECTOR3(pos.x + (nCntScore * 30.0f), pos.y, pos.z));
			// �T�C�Y�ݒ�
			pContinue->m_apNumber[nCntScore]->SetSize(size);
			// ������
			pContinue->m_apNumber[nCntScore]->Init();
			// �I�u�W�F�N�g�^�C�v�̐ݒ�
			pContinue->m_apNumber[nCntScore]->SetType(OBJ_PAUSE);
		}
	}

	// ������
	pContinue->Init();

	return pContinue;
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CContinue::Init()
{
	// �R���e�B�j���[���o��Ԃɂ���
	m_bContinue = true;

	// �|�[�Y��Ԃɂ���
	CManager::GetManager()->SetPause(true);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetType(EObject::OBJ_PAUSE);

	// �R���e�B�j���[�H��UI
	m_pUi[0] = CUi::Create(D3DXVECTOR3(550.0f, 300.0f, 0.0f), D3DXVECTOR2(300.0f, 50.0f),
		CUi::TYPE_CONTINUE, CUi::ANIM_NONE, CUi::PLAYER_NONE);
	m_pUi[0]->SetType(OBJ_PAUSE);
	// �G���g���[�҂�UI�𐶐�
	m_pUi[1] = CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
		CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_NONE);
	m_pUi[1]->SetType(OBJ_PAUSE);

	// �t�F�[�h
	m_pFade = new CObject2D;
	m_pFade->SetPosition(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
	m_pFade->SetSize(D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT));
	m_pFade->Init();
	m_pFade->SetType(OBJ_CONTINUE_FADE);
	m_pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CContinue::Uninit()
{
	for (int nCntNumber = 0; nCntNumber < MAX_CONTINUE; nCntNumber++)
	{
		// ���g������Ȃ�
		if (m_apNumber[nCntNumber] != nullptr)
		{
			// �������̏I������
			m_apNumber[nCntNumber]->Uninit();
			m_apNumber[nCntNumber] = nullptr;
		}
	}

	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		// ���g������Ȃ�
		if (m_pUi[nCntUi] != nullptr)
		{
			// UI���̏I������
			m_pUi[nCntUi]->Uninit();
			m_pUi[nCntUi] = nullptr;
		}
	}

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CContinue::Update()
{
	m_nCountDown++;

	if (m_nCountDown >= 60)
	{// ��b�u���ɃJ�E���g�_�E����i�߂�
		m_nCountDown = 0;
		Add(-1);
	}

	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	// �W���C�p�b�h���̎擾
	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	//// �v���C���[�̃G���g���[����
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// �v���C���[ENTRY���̎擾
	//	bool bEntry = CManager::GetManager()->GetEntry(nCntPlayer);

	//	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, nCntPlayer) == true && bEntry == false)
	//	{// �J�E���g�_�E���𑁂߂�
	//		m_nCountDown = 0;
	//		Add(-1);
	//		break;
	//	}
	//	else if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_ATTACK) == true && bEntry == false)
	//	{// �J�E���g�_�E���𑁂߂�
	//		m_nCountDown = 0;
	//		Add(-1);
	//		break;
	//	}
	//	// �v���C���[�̂ǂ��炩���Q��������
	//	else if (bEntry == true)
	//	{// �j��
	//		Uninit();
	//		SetContinue(false);
	//		// �|�[�Y��Ԃ�����
	//		CManager::GetManager()->SetPause(false);
	//		return;
	//	}
	//}

	// �J�E���g�_�E���I��
	if (m_nContinue < 0)
	{// �j��
		Uninit();
		
		//// �Q�[���I�[�o�[���S�̐���
		//CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(300.0f, 50.0f),
		//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_GAMEOVER, CLogo::ANIM_LENGTHWISE, 300)->SetType(OBJ_PAUSE);
	}
}

//=============================================================================
// �`��
//=============================================================================
void CContinue::Draw()
{
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CContinue::Add(const int& nScore)
{
	m_nContinue += nScore;
	Set();
}

//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
void CContinue::Set()
{
	//�e���̐��l���i�[(pPostexU[�����Ƃ̐��l])
	int aPosTexU[MAX_CONTINUE];

	aPosTexU[0] = (m_nContinue % 100) / 10;
	aPosTexU[1] = m_nContinue % 10;

	//�e�N�X�`�����X�V����
	for (int nCntScore = 0; nCntScore < MAX_CONTINUE; nCntScore++)
	{
		m_apNumber[nCntScore]->SetAnimation(aPosTexU[nCntScore], 0, CNumber::DIVISION_U, CNumber::DIVISION_V);
	}
}
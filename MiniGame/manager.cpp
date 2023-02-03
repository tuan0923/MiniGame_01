//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "base.h"
#include "fade.h"
#include "sound.h"
#include "load.h"

// �ǉ�
#include "texture.h"
#include "x_file.h"
#include "x_file_motion.h"
#include "set_model.h"
#include "debugproc.h"
/**/

#include "input_keyboard.h"
#include "input_joypad.h"
#include "input_mouse.h"

#include "object.h"
#include "title.h"
#include "game.h"
#include "result.h"

#include "continue.h"

#include <time.h>

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CManager *CManager::m_pManager = nullptr;		// �}�l�[�W���[�̃|�C���^

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CManager::CManager()
	:m_pTitle(), m_pGame(), m_pResult(), m_pRenderer(), m_pInputKeyboard(), m_pInputJoypad(), m_pInputMouse(), m_pSound(), m_pTexture(),
	m_pXFile(), m_pMotion(), m_pSetModel(), m_pFade(), m_pDebugProc(), m_bPause(false), m_mode(MODE_TITLE), m_nCounter(0)
{
	// ������
	ZeroMemory(&m_EntryInfo, sizeof(m_EntryInfo));
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CManager::~CManager()
{
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// ���ݎ����ɂ���ă����_���ɐݒ肷��
	srand((unsigned)time(NULL));

	// �����_���[�̏���������
	m_pRenderer = new CRenderer;

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	// �L�[�{�[�h�̏���������
	m_pInputKeyboard = new CInputKeyboard;

	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}

	// �W���C�p�b�h���̏���������
	m_pInputJoypad = new CInputJoypad;

	if (m_pInputJoypad != nullptr)
	{
		m_pInputJoypad->Init();
	}

	// �}�E�X���̏���������
	m_pInputMouse = new CInputMouse;

	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Init(hInstance, hWnd);
	}

	//�e�N�X�`�����̏���������
	m_pTexture = new CTexture;

	if (m_pTexture != nullptr)
	{
		m_pTexture->Init();
	}
	
	//X�t�@�C�����X�̏���������
	m_pXFile = new CXFile;

	if (m_pXFile != nullptr)
	{
		m_pXFile->Init();
	}

	//���[�V�������̏���������
	m_pMotion = new CXFileMotion;

	if (m_pMotion != nullptr)
	{
		m_pMotion->Init(hWnd);
	}

	//���f���z�u���̏���������
	m_pSetModel = new CSetModel;

	if (m_pSetModel != nullptr)
	{
		m_pSetModel->Init(hWnd);
	}

	// �f�o�b�N�\���̐���
	m_pDebugProc = new CDebugProc;

	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Init();
	}

	// �T�E���h�̏���������
	m_pSound = new CSound;

	if (m_pSound != nullptr)
	{
		m_pSound->Init(hWnd);
	}

	// �t�F�[�h�̐���
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(m_mode);
	}

	//�G�z�u���̃��[�h
	//LoadSpace::LoadEnemy(hWnd);

	// ���[�h�̐ݒ�
	SetMode(MODE_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CManager::Uninit()
{
	// �T�E���h�̏I������
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	// �����_���̏I������
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// �t�F�[�h�̔j��
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	// �I�u�W�F�N�g�̏I������
	CObject::ReleaseAll();

	// �S�ẴV�[����j��
	UninitSceneAll();

	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//X�t�@�C���̔j��
	if (m_pXFile != nullptr)
	{
		m_pXFile->Uninit();
		delete m_pXFile;
		m_pXFile = nullptr;
	}

	//���f�����[�V�������̔j��
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//���f���z�u���̔j��
	if (m_pSetModel != nullptr)
	{
		m_pSetModel->Uninit();
		delete m_pSetModel;
		m_pSetModel = nullptr;
	}

	// �f�o�b�N�\�����̔j��
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	// �L�[�{�[�h�̏I������
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	// �W���C�p�b�h�̏I������
	if (m_pInputJoypad != nullptr)
	{
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = nullptr;
	}

	// �}�E�X�̏I������
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CManager::Update()
{
	// �L�[�{�[�h�̍X�V����(���ŏ��ɍs��)
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	// �W���C�p�b�h�̍X�V����
	if (m_pInputJoypad != nullptr)
	{
		m_pInputJoypad->Update();
	}

	// �}�E�X�̍X�V����
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Update();
	}

//#ifdef _DEBUG
//
//	if (m_pInputKeyboard != nullptr)
//	{
//		if (m_pInputKeyboard->GetTrigger(CInputKeyboard::KEYINFO_3)
//		{
//
//		}
//	}
//
//#endif // _DEBUG

	// �t�F�[�h�̍X�V
	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	//�|�[�Y���łȂ��Ȃ�
	if (m_bPause == false)
	{
		// �^�C�g���̍X�V����
		if (m_pTitle != nullptr)
		{
			m_pTitle->Update();
		}

		// �Q�[���̍X�V����
		if (m_pGame != nullptr)
		{
			m_pGame->Update();
		}

		// ���U���g�̍X�V����
		if (m_pResult != nullptr)
		{
			m_pResult->Update();
		}
	}

	// �����_���̍X�V����
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CManager::Draw()
{
	// �t�F�[�h�̍X�V
	if (m_pFade != nullptr)
	{
		m_pFade->Draw();
	}

	// �����_���̕`�揈��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

//-----------------------------------------------------------------------------
// �S�ẴV�[����j��
//-----------------------------------------------------------------------------
void CManager::UninitSceneAll()
{
	// �^�C�g���̔j��
	if (m_pTitle != nullptr)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = nullptr;
	}

	// �Q�[���̔j��
	if (m_pGame != nullptr)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = nullptr;
	}

	// ���U���g�̔j��
	if (m_pResult != nullptr)
	{
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = nullptr;
	}
}

//-----------------------------------------------------------------------------
// ���[�h�̐ݒ�
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	// �S�ẴV�[����j��
	UninitSceneAll();

	// �I�u�W�F�N�g�̍폜
	CObject::ReleaseAll();

	// ���[�h�̐ݒ�
	m_mode = mode;

	// ���[�h�̊m��
	switch (m_mode)
	{
	case MODE_TITLE:
		// �^�C�g�����̐���
		m_pTitle = new CTitle;
		// ����������
		m_pTitle->Init();
		break;

	case MODE_GAME:
		// �Q�[�����̐���
		m_pGame = new CGame;
		// ����������
		m_pGame->Init();
		break;

	case MODE_RESULT:
		// ���U���g���̐���
		m_pResult = new CResult;
		// ����������
		m_pResult->Init();
		break;
	}
}

//-----------------------------------------------------------------------------------------------
// �S�Ẵv���C���[�̎Q�������m�F
//-----------------------------------------------------------------------------------------------
bool CManager::GetEntryAll()
{
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		// 1�l�ł��G���g���[���Ă����
		if (m_EntryInfo[nCntPlayer].bEntry == true)
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// �Q�����̐ݒ�
//-----------------------------------------------------------------------------------------------
void CManager::SetEntryAll(SEntryInfo *pEntry)
{
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		m_EntryInfo[nCntPlayer] = pEntry[nCntPlayer];
	}
}

void CManager::ResetEntry()
{
	// ������
	ZeroMemory(&m_EntryInfo, sizeof(m_EntryInfo));
}

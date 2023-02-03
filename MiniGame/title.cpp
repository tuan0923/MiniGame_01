//===============================================================================================
//
// �Q�[����ʏ��� [title.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "title.h"
#include "sound.h"

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "object.h"
#include "object2D.h"

#include "library.h"
#include "fade.h"

#include "cloud.h"
#include "fade_scene.h"
#include "library.h"
#include "ui.h"

// �ǉ�
#include "object3D.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "boss.h"
#include "item.h"
#include "model_obstacle.h"
#include "model_manager.h"
#include "mesh_sphere.h"
#include "logo.h"
#include "logo_flash.h"
//#include "avalanche.h"

#include "set_model.h"

#include "motion.h"

#include "tutorial.h"

//-----------------------------------------------------------------------------------------------
// using�錾
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[OBJ_MAX] = { nullptr };

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CTitle::CTitle() :m_bPush(false), m_move(0.0f, 0.0f, 0.0f), m_nCounter(0), m_bPlay(false), m_PlayerEnt{false},
m_pPlayer{}, m_pCamera(), m_bEntryKeyboard(false), m_nEntryNum(0), m_pLogo{ nullptr }, m_bLogoMove(false), m_bUi(false)
{
	for (int nCnt = 0; nCnt < OBJ_MAX - 1; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CTitle::~CTitle()
{
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CTitle::Init()
{
	// ���艹
	CSound::Play(CSound::SOUND_LABEL_TITLE);

	// �`���[�g���A���{�^��
	CTutorial::Create(D3DXVECTOR3(0.0f, 2.0f, -50.0f));

	// �J��������
	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 60.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),50.0f);

	// ���̃��b�V���̔z�u
	CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2(3000.0f, 3000.0f), 10, 10, "TEX_TYPE_GAME_BG");

	// �|������
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(2000.0f, 2000.0f));

	// ���C�g����
	CLight::Create(D3DXVECTOR3(-0.2f, -0.8f, 0.4f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create(D3DXVECTOR3(0.2f, -0.1f, -0.8f), D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
	//CLight::Create(D3DXVECTOR3(0.2f, 1.0f, -0.0f), D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));

	// �G���g���[���̃��Z�b�g
	CManager::GetManager()->ResetEntry();
	// �v���C���[�Q�����̎擾
	CManager::SEntryInfo *pEntry = CManager::GetManager()->GetEntry();

	//// �v���C���[����
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// ���݂̔ԍ����Q�����Ă���Ȃ�
	//	if (pEntry[nCntPlayer].bEntry == true)
	//	{
	//		// �L�[�{�[�h�ŎQ�����Ă���Ȃ�
	//		if (pEntry[nCntPlayer].bEntryKeyboard == true)
	//		{
	//			// �v���C���[����
	//			m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "MODEL_PINGU", nCntPlayer);
	//			m_pPlayer[nCntPlayer]->SetKeyboard(pEntry[nCntPlayer].bEntryKeyboard);

	//			// �G���g���[�\��������𒴂���܂�
	//			if (m_nEntryNum < CPlayer::PLAYER_MAX)
	//			{// �G���g���[�ԍ��̉��Z
	//				m_nEntryNum++;
	//			}
	//		}
	//		else
	//		{
	//			// �v���C���[����
	//			m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "MODEL_PINGU", nCntPlayer);
	//			m_pPlayer[nCntPlayer]->SetGamePadNum(pEntry[nCntPlayer].nGamePadNum);

	//			// �G���g���[�\��������𒴂���܂�
	//			if (m_nEntryNum < CPlayer::PLAYER_MAX)
	//			{// �G���g���[�ԍ��̉��Z
	//				m_nEntryNum++;
	//			}
	//		}
	//	}
	//}
	
	// ���f���̔z�u
	CManager::GetManager()->GetModelSet()->LoadModel("MODEL_TITLE");

	// �^�C�g�����S�̐���
	m_pLogo = CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, -250.0f, 0.0f),
		D3DXVECTOR2(CRenderer::SCREEN_WIDTH - 300.0f, 400.0f), "TEX_TYPE_LOGO_TITLE", -1);

	//// �e�N�X�`���̃��[�h
	//CTitle::Load();
	//// �_
	//CCloud::Load();

	//// �X�N���[���T�C�Y�̕ۑ�
	//D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	//for (int nCnt = 0; nCnt < OBJ_MAX - 1; nCnt++)
	//{// ����
	//	m_apObject2D[nCnt] = new CObject2D;
	//}

	//// ��
	//m_apObject2D[BG_SKY]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, -ScreenSize.y / 2, 0.0f));
	//m_apObject2D[BG_SKY]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y * 3));
	//// �^�C�g�����S
	//m_apObject2D[LOGO_TITLE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y - 450.0f, 0.0f));
	//m_apObject2D[LOGO_TITLE]->SetSize(D3DXVECTOR2(ScreenSize.x - 550.0f, ScreenSize.y / 2.5f));
	//// �v���C���[���S
	//m_apObject2D[LOGO_PLAYER]->SetPosition(D3DXVECTOR3(-ScreenSize.x, 160.0f, 0.0f));
	//m_apObject2D[LOGO_PLAYER]->SetSize(D3DXVECTOR2(300.0f, 150.0f));
	//// Press���S
	//m_apObject2D[LOGO_PRESS]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y - 150.0f, 0.0f));
	//m_apObject2D[LOGO_PRESS]->SetSize(D3DXVECTOR2(ScreenSize.x - 550.0f, 90.0f));
	//// �t�F�[�h
	//m_apObject2D[BG_FADE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	//m_apObject2D[BG_FADE]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	//// �`���[�g���A��
	//m_apObject2D[LOGO_TUTORIAL]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	//m_apObject2D[LOGO_TUTORIAL]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));

	//for (int nCnt = 0; nCnt < OBJ_MAX - 1; nCnt++)
	//{// �������ƃe�N�X�`���̐ݒ�
	//	m_apObject2D[nCnt]->Init();
	//	m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	//}

	////�w�i�ƃv���C���[���S�ȊO��O�ɕ`�悷��(�^�C�v��ݒ肷��)
	//for (int nCnt = LOGO_TITLE; nCnt < OBJ_MAX - 1; nCnt++)
	//{
	//	m_apObject2D[nCnt]->SetObjType(CObject::OBJ_TITLE);
	//}
	////�v���C���[���S��w�i�̎��ɕ`�悷��
	//m_apObject2D[LOGO_PLAYER]->SetObjType(CObject::OBJ_TITLE_LOGO);
	//m_apObject2D[BG_FADE]->SetObjType(CObject::OBJ_BLACK);
	//m_apObject2D[LOGO_TUTORIAL]->SetObjType(CObject::OBJ_LOGO);

	////�^�C�g����Press���S�𓧖��ɂ���
	//m_apObject2D[LOGO_TITLE]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//m_apObject2D[LOGO_PRESS]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//m_apObject2D[BG_FADE]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	//m_apObject2D[LOGO_TUTORIAL]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//// �_�𕡐��A�����z�u����
	//for (int nCntCloud = 0; nCntCloud < 25; nCntCloud++)
	//{
	//	// �ʒu��ݒ�
	//	D3DXVECTOR3 pos;
	//	pos.x = (float)GetRandNum(CRenderer::SCREEN_WIDTH, 0);
	//	pos.y = (float)GetRandNum(CRenderer::SCREEN_HEIGHT - 300, CRenderer::SCREEN_HEIGHT * -4);
	//	pos.z = 0.0f;

	//	// �_�̐���
	//	CCloud::Create(pos);
	//}

	//// �^�C�g��BGM
	//CSound::Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CTitle::Uninit()
{
	// �|�C���^�̔j��
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt] = nullptr;
		}
	}

	// �^�C�g��BGM
	CSound::Stop();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CTitle::Update()
{
	//if (GetEntryAll() == false)
	//{

	//}

	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	// �W���C�p�b�h���̎擾
	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	// �v���C���[�Q�����̎擾
	CManager::SEntryInfo *pEntry = CManager::GetManager()->GetEntry();

	// �v���C���[����
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		// ���݂̔ԍ����Q�����Ă��Ȃ��Ȃ�
		if (pEntry[m_nEntryNum].bEntry == false)
		{
			if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, nCntPlayer) == true)
			{// �X�^�[�g�{�^������
				if (m_PlayerEnt[nCntPlayer] == false)
				{
					m_pPlayer[m_nEntryNum] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "MODEL_PINGU", m_nEntryNum);
					m_pPlayer[m_nEntryNum]->SetGamePadNum(nCntPlayer);
					pEntry[m_nEntryNum].nGamePadNum = nCntPlayer;
					pEntry[m_nEntryNum].bEntry = true;
					m_PlayerEnt[nCntPlayer] = true;

					// �G���g���[�\��������𒴂���܂�
					if (m_nEntryNum < CPlayer::PLAYER_MAX)
					{// �G���g���[�ԍ��̉��Z
						m_nEntryNum++;
					}

					if (m_pLogo != nullptr)
					{
						m_pLogo->Uninit();
						m_pLogo = nullptr;
						m_bLogoMove = true;
					}

					if (m_pLogoFlash != nullptr)
					{
						m_pLogoFlash->Uninit();
						m_pLogoFlash = nullptr;
					}

					break;
				}
			}
			if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_OK) == true && m_bEntryKeyboard == false)
			{// �G���^�[�L�[���� && �L�[�{�[�h�ŎQ�����Ă��Ȃ����
				m_pPlayer[m_nEntryNum] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "MODEL_PINGU", m_nEntryNum);
				m_pPlayer[m_nEntryNum]->SetKeyboard(true);
				m_bEntryKeyboard = true;
				pEntry[m_nEntryNum].bEntryKeyboard = true;
				pEntry[m_nEntryNum].bEntry = true;
				
				// �G���g���[�\��������𒴂���܂�
				if (m_nEntryNum < CPlayer::PLAYER_MAX)
				{// �G���g���[�ԍ��̉��Z
					m_nEntryNum++;
				}

				if (m_pLogo != nullptr)
				{
					m_pLogo->Uninit();
					m_pLogo = nullptr;
					m_bLogoMove = true;
				}

				if (m_pLogoFlash != nullptr)
				{
					m_pLogoFlash->Uninit();
					m_pLogoFlash = nullptr;
				}

				break;
			}
		}

		//// �Q�[���J�n�̌J��Ԃ��h�~
		//if (m_bPush == false)
		//{
		//	//�L�[�������ꂽ��
		//	if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_1) == true)
		//	{
		//		// ���艹
		//		CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

		//		// ���[�h�̐ݒ�
		//		CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);
		//		m_bPush = true;

		//		return;
		//	}
		//}
	}

	if (m_bUi == false)
	{
		if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_OK) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, 0))
		{
			CLogo::Create(D3DXVECTOR3(150.0f, CRenderer::SCREEN_HEIGHT - 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_1", -1);
			CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 110.0f, CRenderer::SCREEN_HEIGHT - 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_2", -1);
			m_bUi = true;
		}
	}

	if (m_pLogo == nullptr)
	{
		// ����
		Ready();
	}
	// �^�C�g���̓���
	LogoMove();

	//m_nCounter++;
}

void CTitle::LogoMove()
{
	if (m_bLogoMove == false)
	{
		// �ʒu�擾
		D3DXVECTOR3 posLogo = m_pLogo->GetPosition();

		if (posLogo.y >= 250.0f)
		{
			m_bLogoMove = true;

			m_pLogoFlash = CLogoFlash::Create(D3DXVECTOR2(CRenderer::SCREEN_WIDTH / 3, 80.0f), "TEX_TYPE_LOGO_TITLEPUSH", -1);
		}
		else
		{
			posLogo.y += 3.0f;
		}

		m_pLogo->SetPosition(posLogo);
		m_pLogo->SetVertex();
	}
}

void CTitle::Ready()
{
	if (m_bPlay == false)
	{
		// �v���C���[�̎��S��
		int nNumReady = 0;

		// �v���C���[����
		for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
		{
			// ���݂̃v���C���[���Q�����Ă���Ȃ�
			if (m_pPlayer[nCntPlayer] != nullptr)
			{
				// ���S���Ă�����
				if (m_pPlayer[nCntPlayer]->GetReady() == true)
				{// �v���C���[�̎��S�������Z
					nNumReady++;
				}
			}
			else
			{// �v���C���[�̎��S�������Z
				nNumReady++;
			}
		}

		// �v���C���[���S�����S���Ă�����
		if (CPlayer::PLAYER_MAX <= nNumReady)
		{
			// �Q�[���I���t���O�𗧂Ă�
			m_bPlay = true;

			// ���艹
			CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

			// ���[�h�̐ݒ�
			CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);
		}
	}
}

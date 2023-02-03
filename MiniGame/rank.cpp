//=============================================================================
//
// �����N���� [rank.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "rank.h"

#include "manager.h"
#include "renderer.h"
#include "load.h"

#include "score.h"
#include "input_joypad.h"
#include "input_keyboard.h"
#include "sound.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define SCORE_POS				(D3DXVECTOR3(70.0f,CRenderer::SCREEN_HEIGHT - 30.0f,0.0f))
#define PLAYER_SCORE_POS		(D3DXVECTOR3(220.0f,CRenderer::SCREEN_HEIGHT - 50.0f,0.0f))
#define SCORE_SIZE				(D3DXVECTOR2(30.0f,30.0f))
#define PLAYER_SCORE_SIZE		(D3DXVECTOR2(50.0f,60.0f))
#define SCORE_SPACE				(20)
#define PLAYER_SCORE_SPACE		(40)

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------

//=============================================================================
// CRank�̃R���X�g���N�^
//=============================================================================
CRank::CRank() :m_pScore{ nullptr }
{
	SetType(CObject::OBJ_UI);
}

//=============================================================================
// CRank�̃f�X�g���N�^
//=============================================================================
CRank::~CRank()
{
}

//=============================================================================
// ��������
//=============================================================================
CRank *CRank::Create()
{
	// �|�C���^�ϐ��̐���
	CRank *pRank = new CRank;

	// ����������
	pRank->Init();

	return pRank;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRank::Init()
{
	m_pScore = CScore::Create(SCORE_POS, SCORE_SIZE, SCORE_SPACE);

	//// �v���C���[�X�R�A�̐���
	//for (int nCnt = 0; nCnt < MAX_PLAYER_SCORE; nCnt++)
	//{
	//	// �v���C���[ENTRY���̎擾
	//	bool bEntry = CManager::GetManager()->GetEntry(nCnt);

	//	// �G���g���[���Ă����
	//	if (bEntry == true)
	//	{// �v���C���[�X�R�A����
	//		m_pScore[nCnt + MAX_RANKING] = CScore::Create(D3DXVECTOR3(PLAYER_SCORE_POS.x + (nCnt * 650.0f), PLAYER_SCORE_POS.y, SCORE_POS.z),
	//			PLAYER_SCORE_SIZE, PLAYER_SCORE_SPACE);

	//		// �X�R�A�̐ݒ�
	//		m_aScore[nCnt + MAX_RANKING] = m_nScorePlayer[nCnt];

	//		// UI�̐���
	//		m_apObject2D[nCnt] = new CObject2D;
	//		m_apObject2D[nCnt]->SetType(EObject::OBJ_UI);
	//		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(100.0f + (nCnt * 650.0f), CRenderer::SCREEN_HEIGHT - 50.0f, 0.0f));
	//		m_apObject2D[nCnt]->SetSize(D3DXVECTOR2(200.0f, 100.0f));
	//		m_apObject2D[nCnt]->Init();
	//		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	//	}
	//}

	// �e�L�X�g����X�R�A�����[�h
	m_pScore->Set(LoadSpace::LoadScore());

	// Top3�̃X�R�A�F��ݒ�
	m_pScore->SetColor(D3DXCOLOR(0.1f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRank::Uninit()
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRank::Update()
{
	//// �e�N�X�`���̒��_���W��ύX
	//m_apObject2D[TYPE_BG]->SetAnimBgLeftUp(1, 400, true);

	//// �L�[�{�[�h���̎擾
	//CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	//// �Q�[���p�b�h���̎擾
	//CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	//for (int nCnt = CInputKeyboard::KEYINFO_OK; nCnt < CInputKeyboard::KEYINFO_MAX; nCnt++)
	//{
	//	// �L�[�{�[�h��ENTRY����
	//	if (pKeyboard->GetTrigger(nCnt))
	//	{
	//		for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
	//		{
	//			if (m_pScore[nCnt] != nullptr)
	//			{// �X�R�A�ݒ�
	//				if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
	//				{
	//					m_pScore[nCnt]->Set(m_aScore[nCnt]);
	//				}
	//			}
	//		}

	//		if (m_bNextMode == true)
	//		{
	//			// ���艹
	//			CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

	//			// ���[�h�̐ݒ�
	//			CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);
	//			return;
	//		}

	//		m_bNextMode = true;
	//		break;
	//	}
	//}

	//// �v���C���[�̃G���g���[����
	//for (int nCntController = 0; nCntController < CPlayer::PLAYER_MAX; nCntController++)
	//{
	//	for (int nCnt = CInputJoypad::JOYKEY_UP; nCnt < CInputJoypad::JOYKEY_MAX; nCnt++)
	//	{
	//		if (pJoypad->GetTrigger((CInputJoypad::JOYKEY)nCnt, nCntController))
	//		{
	//			// ���艹
	//			CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

	//			for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
	//			{
	//				if (m_pScore[nCnt] != nullptr)
	//				{// �X�R�A�ݒ�
	//					if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
	//					{
	//						m_pScore[nCnt]->Set(m_aScore[nCnt]);
	//					}
	//				}
	//			}

	//			if (m_bNextMode == true)
	//			{
	//				// ���[�h�̐ݒ�
	//				CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);
	//				return;
	//			}

	//			m_bNextMode = true;
	//			break;
	//		}
	//	}
	//}

	//// �X�R�A�����i�[
	//for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
	//{
	//	if (m_pScore[nCnt] != nullptr)
	//	{// ���b�X�R�A���Z
	//		if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
	//		{
	//			m_pScore[nCnt]->Add(200);
	//		}
	//		else if (m_nScorePlayer[0] == m_pScore[nCnt]->GetScore() ||
	//			m_nScorePlayer[1] == m_pScore[nCnt]->GetScore())
	//		{
	//			// PRESS���S�̐F���擾
	//			D3DXCOLOR col = m_pScore[nCnt]->GetColor();

	//			// PRESS���S��_�ł�����
	//			if (m_bMyScoreFade[nCnt] == false)
	//			{
	//				// a�l�����Z
	//				col.a += 0.02f;
	//				// a�l�̉��Z���I�������
	//				if (col.a >= 1.0f)
	//				{// a�l�̌��Z���n�߂�
	//					m_bMyScoreFade[nCnt] = true;
	//				}
	//			}
	//			else if (m_bMyScoreFade[nCnt] == true)
	//			{
	//				// a�l�����Z
	//				col.a -= 0.02f;
	//				// a�l�̌��Z���I�������
	//				if (col.a <= 0.0f)
	//				{// a�l�̉��Z���n�߂�
	//					m_bMyScoreFade[nCnt] = false;
	//				}
	//			}

	//			// �F�̐ݒ�
	//			m_pScore[nCnt]->SetColor(col);
	//		}
	//	}
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRank::Draw()
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRank::Save(int nHiScore)
{
	m_pScore->Set(nHiScore);

	// �e�L�X�g�ɃX�R�A���Z�[�u
	LoadSpace::SaveScore(nHiScore);
}

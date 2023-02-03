//=============================================================================
//
//	�v���C���[����[player.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"
#include "renderer.h"

#include "library.h"

#include "bg.h"
#include "spray.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "ui.h"
#include "gauge.h"
#include "life.h"
#include "score.h"

#include "rank.h"

// �ǉ�
#include "model_obstacle.h"
#include "title.h"
#include "game.h"
#include "camera.h"
#include "x_file_motion.h"
#include "billboard_player.h"
#include "logo.h"
#include "texture.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define PLAYER_UI_SIZE				(D3DXVECTOR2(200.0f, 50.0f))
#define LIFE_UI_SIZE				(D3DXVECTOR2(120.0f, 30.0f))
#define LEVEL_UI_SIZE				(D3DXVECTOR2(50.0f, 50.0f))
#define ATTACK_INTERVAL				(7)
#define JOYKEY_LEFT_STICK_UP		(-0.2f)
#define JOYKEY_LEFT_STICK_DOWN		(0.2f)

#define FIELD_SIZE_WIDTH			(280.0f)
#define FIELD_SIZE_HEIGHT			(250.0f)
#define FIELD_SIZE_HEIGHT_CAMERA	(200.0f)

// �d��
#define GRAVITY			(0.1f)
// �W�����v��
#define JUMP_POWER		(2.0f)
// �����蔻��͈̔�
#define ATTACK_LENGTH	(50.0f)

//-----------------------------------------------------------------------------
// using�錾
//-----------------------------------------------------------------------------
using namespace LibrarySpace;

//*****************************************************************************
// �萔�錾
//*****************************************************************************
const float CPlayer::SIZE_X = 90.0f;
const float CPlayer::SIZE_Y = 40.0f;
const float CPlayer::MOVE_DEFAULT = 0.35f;
// �A�j���[�V�����Ԋu
const int CPlayer::ANIM_INTERVAL = 5;
// �A�j���[�V�����ő吔
const int CPlayer::MAX_ANIM = 2;
// U���W�̍ő啪����
const int CPlayer::DIVISION_U = 2;
// V���W�̍ő啪����
const int CPlayer::DIVISION_V = 4;
// �v���C���[�̃f�t�H���g�J���[
const D3DXCOLOR CPlayer::DEFAULT_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
// �f�t�H���g�c�@
const int CPlayer::DEFAULT_LIFE = 2;

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::CPlayer() :
	m_move(0.0f, 0.0f, 0.0f), m_posOld(0.0f, 0.0f, 0.0f), m_state(STATE_NORMAL), m_nCntState(0), m_nCntAttack(0), m_nCntAnim(0),
	m_nPatternAnim(0), m_nCntAnimMove(0), m_bControlKeyboard(false), m_nGamePadNum(0), m_nTexRotType(TYPE_NEUTRAL), m_nPlayerNum(0),
	m_bIsJumping(false), m_bControl(false), m_bInSea(false), m_pLife(nullptr), m_pScore(nullptr), m_bDie(false), m_bStart(false),
	m_knockBack(0.0f, 0.0f, 0.0f), m_nDamageCnt(0), m_nAttackCnt(0), m_pLogo(nullptr), m_bReady(0)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetType(EObject::OBJ_PLAYER);
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-----------------------------------------------------------------------------
// �C���X�^���X��������
//-----------------------------------------------------------------------------
CPlayer *CPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name, int nPlayerNum)
{
	//�C���X�^���X����
	CPlayer *pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		// �ʒu�ݒ�
		pPlayer->SetPosition(pos);
		// �p�x�ݒ�
		pPlayer->SetRotation(rot);
		// X�t�@�C���̐ݒ�
		pPlayer->BindMotion(CManager::GetManager()->GetMotion()->GetMotion(name));
		// �v���C���[�ԍ��̐ݒ�
		pPlayer->m_nPlayerNum = nPlayerNum;
		// ��������
		pPlayer->Init();
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// �^�C�g�����
	if (CManager::GetManager()->GetTitle() != nullptr)
	{
		// �J�����ʒu�̎擾
		D3DXVECTOR3 rotCamera = CManager::GetManager()->GetTitle()->GetCamera()->GetRotation();
		// �ړI�̊p�x�ݒ�
		CMotion::SetRotation(D3DXVECTOR3(0.0f, rotCamera.y, 0.0f));
		// �ړI�̊p�x�ݒ�
		CMotion::SetRotDest(rotCamera);

		// ���ʉ�
		CSound::Play(CSound::SOUND_LABEL_SE_ENTRY);
	}

	// �F�̐ݒ�
	switch (m_nPlayerNum)
	{
		// 1P
	case 0:

		// �Q�[�����Ȃ�
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			// �X�R�A�̐���
			m_pScore = CScore::Create(D3DXVECTOR3(150.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);
			// �F�̐ݒ�
			m_pScore->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
		}
		// �^�C�g����ʂȂ�
		else if (CManager::GetManager()->GetTitle() != nullptr)
		{
			m_pLogo = CLogo::Create(D3DXVECTOR3(150.0f, 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_SET", -1);

			// ����\��Ԃɂ���
			m_bControl = true;
		}

		// �F�̐ݒ�
		CMotion::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));

		// �v���C���[�\�L�̐���
		CBillboardPlayer::Create(GetpPosition(), "TEX_TYPE_BILLBOARD_1P");

		break;

		// 2P
	case 1:

		// �Q�[�����Ȃ�
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			// �X�R�A�̐���
			m_pScore = CScore::Create(D3DXVECTOR3(450.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);
			// �F�̐ݒ�
			m_pScore->SetColor(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));
		}
		// �^�C�g����ʂȂ�
		else if (CManager::GetManager()->GetTitle() != nullptr)
		{
			m_pLogo = CLogo::Create(D3DXVECTOR3(450.0f, 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_SET", -1);

			// ����\��Ԃɂ���
			m_bControl = true;
		}

		// �F�̐ݒ�
		CMotion::SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f));

		// �v���C���[�\�L�̐���
		CBillboardPlayer::Create(&GetPosition(), "TEX_TYPE_BILLBOARD_2P");
		break;

		// 3P
	case 2:

		// �Q�[�����Ȃ�
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			// �X�R�A�̐���
			m_pScore = CScore::Create(D3DXVECTOR3(750.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);
			// �F�̐ݒ�
			m_pScore->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
		}
		// �^�C�g����ʂȂ�
		else if (CManager::GetManager()->GetTitle() != nullptr)
		{
			m_pLogo = CLogo::Create(D3DXVECTOR3(750.0f, 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_SET", -1);

			// ����\��Ԃɂ���
			m_bControl = true;
		}

		// �F�̐ݒ�
		CMotion::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));

		// �v���C���[�\�L�̐���
		CBillboardPlayer::Create(&GetPosition(), "TEX_TYPE_BILLBOARD_3P");
		break;

		// 4P
	case 3:

		// �Q�[�����Ȃ�
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			// �X�R�A�̐���
			m_pScore = CScore::Create(D3DXVECTOR3(1050.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);
			// �F�̐ݒ�
			m_pScore->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f));
		}
		// �^�C�g����ʂȂ�
		else if (CManager::GetManager()->GetTitle() != nullptr)
		{
			m_pLogo = CLogo::Create(D3DXVECTOR3(1050.0f, 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_SET", -1);

			// ����\��Ԃɂ���
			m_bControl = true;
		}

		// �F�̐ݒ�
		CMotion::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));

		// �v���C���[�\�L�̐���
		CBillboardPlayer::Create(&GetPosition(), "TEX_TYPE_BILLBOARD_3P");
		break;
	default:
		break;
	}

	// ������
	CMotion::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CMotion::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CPlayer::Update()
{
	if (CManager::GetManager()->GetGame() != nullptr)
	{
		if (CManager::GetManager()->GetGame()->GetStart() == true && CManager::GetManager()->GetGame()->GetEnd() == false)
		{
			if (m_state != STATE_DAMAGE)
			{
				m_bControl = true;
			}
		}
	}

	// �O��̈ʒu��ۑ�
	m_posOld = GetPosition();

	// �ʒu�����擾
	D3DXVECTOR3 pos = CMotion::GetPosition();
	// �T�C�Y�̎擾
	D3DXVECTOR3 size = CMotion::GetSizeMax();

	// ����ł����ԂȂ� && ���S���Ă��Ȃ��Ȃ�
	if (m_bControl == true && m_state != STATE_DIE)
	{
		// �ړ����Ă��Ȃ����
		if (Move() == false)
		{
			m_state = STATE_NORMAL;
		}

		// �W�����v
		Jump();

		// �U��
		Attack();
	}

	if (m_state == STATE_DAMAGE)
	{
		// ��e����
		Damage();
	}

	// �d�͕��ׂ�������
	m_move.y -= GRAVITY;
	
	////�v���C���[������Ɋ������܂�Ă�����
	//if (m_state == STATE_INAVALANCHE)
	//{
	//	// �L�[�{�[�h���̎擾
	//	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	//	// �W���C�p�b�h���̎擾
	//	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	//	//�v���C���[����ނ�����
	//	m_move.z -= 1.0f;

	//	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_OK))
	//	{
	//		m_nPushButton++;
	//		if (m_nPushButton >= 1/*���񉟂��������𔲂��邩*/)
	//		{
	//			m_state = STATE_NORMAL;
	//		}
	//	}
	//}

	// �ړ��ʂ̉��Z
	pos += m_move;

	// ��Q���̓����蔻��
	CObstacle::CollisionAll(&pos, m_nPlayerNum);

	// �ړ��ʂ̌���
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;

	//�ǁE���̓����蔻�菈��
	if (pos.x - (size.x / 2) <= -FIELD_SIZE_WIDTH / 2)
	{// ����
		pos.x = (-FIELD_SIZE_WIDTH / 2) + (size.x / 2);
	}
	else if (pos.x + (size.x / 2) >= FIELD_SIZE_WIDTH / 2)
	{// �E��
		pos.x = (FIELD_SIZE_WIDTH / 2) - (size.x / 2);
	}
	//if (g_Player.pos.z + (PLAYER_WIDTH / 2) >= 400.0f / 2)
	//{//����
	//	g_Player.pos.z = (400.0f / 2) - (PLAYER_WIDTH / 2);
	//}

	// �Q�[���Q�����ł����
	if (m_bStart == true)
	{
		if (CManager::GetManager()->GetGame()->GetEnd() == false)
		{
			// �Q�[�����n�܂�����
			if (CManager::GetManager()->GetGame()->GetStart() == true && m_bDie == false)
			{
				m_pScore->Add(1);
			}

			// �J�����ʒu�̎擾
			D3DXVECTOR3 posCamera = CManager::GetManager()->GetGame()->GetCamera()->GetPosV();

			if (pos.z - (size.z / 2) <= posCamera.z + FIELD_SIZE_HEIGHT_CAMERA)
			{// ��O��
				pos.z = (posCamera.z + FIELD_SIZE_HEIGHT_CAMERA) + (size.z / 2);
			}
		}
	}
	// ���r�[�ҋ@���ł����
	else
	{
		if (pos.z - (size.z / 2) <= -FIELD_SIZE_HEIGHT / 2)
		{// ��O��
			pos.z = (-FIELD_SIZE_HEIGHT / 2) + (size.z / 2);
		}

		// �L�[�{�[�h���̎擾
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
		// �W���C�p�b�h���̎擾
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		// �L�[�{�[�h����̏ꍇ
		if (m_bControlKeyboard == true &&
			pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_1) == true)
		{// SPACE�L�[����
			m_bReady = m_bReady ? false : true;

			// ��e��
			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);
		}
		// �Q�[���p�b�h����̏ꍇ
		else if (m_bControlKeyboard == false &&
			pJoypad->GetTrigger(CInputJoypad::JOYKEY_X, m_nGamePadNum) == true)
		{// A�{�^������
			m_bReady = m_bReady ? false : true;

			// ��e��
			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);
		}

		if (m_bReady == true)
		{
			m_pLogo->BindTexture(CManager::GetManager()->GetTexture()->GetTexture("TEX_TYPE_UI_OK"));
		}
		else
		{
			m_pLogo->BindTexture(CManager::GetManager()->GetTexture()->GetTexture("TEX_TYPE_UI_SET"));
		}
	}

	if (pos.y <= 0.0f)
	{// ��
		pos.y = 0.0f;
		m_bIsJumping = false;
		// �ړ���Y�̏�����
		m_move.y = 0.0f;
	}

	// �ʒu���X�V
	CMotion::SetPosition(pos);

	// �p�x�̐��K��
	CMotion::NormalizeRot();

	// �v���C���[���I�����Ă��Ȃ����
	if (m_state != STATE_END)
	{
		// ��ԊǗ�
		State();

		// ���[�V�����Đ�
		if (CMotion::Motion() == true && m_state == STATE_DIE)
		{
			m_state = STATE_END;
		}
	}
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CPlayer::Draw()
{
	//�`��
	CMotion::Draw();
}

//-----------------------------------------------------------------------------
// �ړ�����
//-----------------------------------------------------------------------------
bool CPlayer::Move()
{
	// �ړ����Ă��邩�ǂ���
	bool bMove = false;
	// �ړI�̊p�x
	D3DXVECTOR3 rotDest = { 0,0,0 };
	// �J�����ʒu�̎擾
	D3DXVECTOR3 rotCamera = { 0,0,0 };

	// �ړ��͂��擾
	float fMove = CMotion::GetMotion().fMove;

	if (m_bStart == false)
	{
		// �J�����ʒu�̎擾
		rotCamera = CManager::GetManager()->GetTitle()->GetCamera()->GetRotation();
	}

	// �L�[�{�[�h�ő��삵�Ă���Ȃ�
	if (m_bControlKeyboard == true)
	{
		// �L�[�{�[�h���̎擾
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();

		if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_LEFT) == true)
		{// ���L�[����
			if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
			{// ���L�[����
				// �ړ��ʉ��Z
				m_move.x += -GetSinVec(-4.0f, rotCamera.y, fMove);
				m_move.z += -GetCosVec(-4.0f, rotCamera.y, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = (D3DX_PI / 4.0f) + rotCamera.y;
			}
			else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
			{// ��L�[����
				m_move.x += -GetSinVec(-1.5f, rotCamera.y, fMove);
				m_move.z += -GetCosVec(-1.5f, rotCamera.y, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = (D3DX_PI / 1.5f) + rotCamera.y;
			}
			else
			{// ���ړ�
				m_move.x += GetSinVec(2.0f, rotCamera.y, fMove);
				m_move.z += GetCosVec(2.0f, rotCamera.y, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = (D3DX_PI / 2.0f) + rotCamera.y;
			}

			// �ړ��t���O�𗧂Ă�
			bMove = true;
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_RIGHT) == true)
		{// �E�L�[����
			if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
			{// ��L�[����
				m_move.x += -GetSinVec(4.0f, rotCamera.y, fMove);
				m_move.z += -GetCosVec(4.0f, rotCamera.y, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = (-D3DX_PI / 4) + rotCamera.y;
			}
			else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
			{// ���L�[����
				m_move.x += -GetSinVec(1.5f, rotCamera.y, fMove);
				m_move.z += -GetCosVec(1.5f, rotCamera.y, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = (-D3DX_PI / 1.5f) + rotCamera.y;
			}
			else
			{
				m_move.x += GetSinVec(-2.0f, rotCamera.y, fMove);
				m_move.z += GetCosVec(-2.0f, rotCamera.y, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = (-D3DX_PI / 2.0f) + rotCamera.y;
			}

			// �ړ��t���O�𗧂Ă�
			bMove = true;
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
		{// ��L�[����
			m_move.x += -GetSinVec(1.0f, rotCamera.y, fMove);
			m_move.z += -GetCosVec(1.0f, rotCamera.y, fMove);
			// �ړI�̊p�x�ݒ�
			rotDest.y = D3DX_PI + rotCamera.y;

			// �ړ��t���O�𗧂Ă�
			bMove = true;
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
		{// ���L�[����
			m_move.x += GetSinVec(1.0f, rotCamera.y, fMove);
			m_move.z += GetCosVec(1.0f, rotCamera.y, fMove);
			// �ړI�̊p�x�ݒ�
			rotDest.y = 0.0f + rotCamera.y;

			// �ړ��t���O�𗧂Ă�
			bMove = true;
		}
	}
	// �Q�[���p�b�h����Ȃ�
	else
	{
		// �W���C�p�b�h���̎擾
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		if (pJoypad->GetPress(CInputJoypad::JOYKEY_LEFT, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).x <= -0.2f)
		{// ���L�[����
			if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
			{// ��L�[����
				// �ړ��ʉ��Z
				m_move.x += GetSinVec(-0.75f, fMove);
				m_move.z += GetCosVec(-0.75f, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = D3DX_PI / 4;
			}
			else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
			{// ���L�[����
				m_move.x += GetSinVec(-0.25f, fMove);
				m_move.z += GetCosVec(-0.25f, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = D3DX_PI / 1.5f;
			}
			else
			{
				m_move.x += GetSinVec(-0.5f, fMove);
				m_move.z += GetCosVec(-0.5f, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = D3DX_PI / 2;
			}

			// �ړ��t���O�𗧂Ă�
			bMove = true;
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_RIGHT, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).x >= 0.2f)
		{// �E�L�[����
			if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
			{// ��L�[����
				m_move.x += GetSinVec(0.75f, fMove);
				m_move.z += GetCosVec(0.75f, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = -D3DX_PI / 4;
			}
			else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
			{// ���L�[����
				m_move.x += GetSinVec(0.25f, fMove);
				m_move.z += GetCosVec(0.25f, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = -D3DX_PI / 1.5f;
			}
			else
			{
				m_move.x += GetSinVec(0.5f, fMove);
				m_move.z += GetCosVec(0.5f, fMove);
				// �ړI�̊p�x�ݒ�
				rotDest.y = -D3DX_PI / 2;
			}

			// �ړ��t���O�𗧂Ă�
			bMove = true;
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
		{// ��L�[����
			m_move.x += GetSinVec(1.0f, fMove);
			m_move.z += GetCosVec(1.0f, fMove);
			// �ړI�̊p�x�ݒ�
			rotDest.y = 0.0f;

			// �ړ��t���O�𗧂Ă�
			bMove = true;
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
		{// ���L�[����
			m_move.x += GetSinVec(0.0f, fMove);
			m_move.z += GetCosVec(0.0f, fMove);
			// �ړI�̊p�x�ݒ�
			rotDest.y = D3DX_PI;

			// �ړ��t���O�𗧂Ă�
			bMove = true;
		}
	}

	// �ړ����Ă��
	if (bMove == true)
	{
		// �p�x�ݒ�
		CMotion::SetRotDest(rotDest);
		// ��Ԃ̐ݒ�
		m_state = STATE_RUN;
	}

	return bMove;
}

//-----------------------------------------------------------------------------
// �W�����v
//-----------------------------------------------------------------------------
void CPlayer::Jump()
{
	// �W�����v���Ă����
	if (m_bIsJumping == true)
	{
		m_state = STATE_JUMP;
	}
	// �W�����v���Ă��Ȃ����
	else if (m_bIsJumping == false)
	{
		// �L�[�{�[�h���̎擾
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
		// �W���C�p�b�h���̎擾
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		// �W�����v�͂��擾
		float fJump = CMotion::GetMotion().fJump;

		// �L�[�{�[�h����̏ꍇ
		if (m_bControlKeyboard == true &&
			pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_JUMP) == true)
		{// SPACE�L�[����

			// �W�����v�͂̐ݒ�
			m_move.y = fJump;

			// �W�����v�t���O�̐ݒ�
			m_bIsJumping = true;

			// ���ʉ�
			CSound::Play(CSound::SOUND_LABEL_SE_JUMP);
		}
		// �Q�[���p�b�h����̏ꍇ
		else if (m_bControlKeyboard == false &&
			pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, m_nGamePadNum) == true)
		{// A�{�^������

			// �W�����v�͂̐ݒ�
			m_move.y = fJump;

			// �W�����v�t���O�̐ݒ�
			m_bIsJumping = true;

			// ���ʉ�
			CSound::Play(CSound::SOUND_LABEL_SE_JUMP);
		}
	}
}

//-----------------------------------------------------------------------------
// �U������
//-----------------------------------------------------------------------------
void CPlayer::Attack()
{
	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	// �W���C�p�b�h���̎擾
	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	if (m_bAttack)
	{
		m_state = STATE_ATTACK;

		//�r��̈ʒu�����擾(���[���h�}�g���b�N�X���烏�[���h���W���擾)
		D3DXVECTOR3 AttackPos = D3DXVECTOR3(
			CMotion::GetMotion().aParts[6].mtxWorld._41,
			CMotion::GetMotion().aParts[6].mtxWorld._42,
			CMotion::GetMotion().aParts[6].mtxWorld._43);

		for (int nCntPlayer = 0; nCntPlayer < PLAYER_MAX; nCntPlayer++)
		{
			// �U���Ώۂ��������g�Ȃ�
			if (nCntPlayer == m_nPlayerNum)
			{
				continue;
			}

			CTitle *pTitle = CManager::GetManager()->GetTitle();
			CGame *pGame = CManager::GetManager()->GetGame();

			// �^�C�g����null�`�F�b�N
			if (pTitle != nullptr)
			{
				CPlayer *pPlayer = pTitle->GetPlayer(nCntPlayer);

				// �v���C���[��null�`�F�b�N
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 OutPos = pPlayer->GetPosition();

					if (pPlayer->GetState() != STATE_DAMAGE && LibrarySpace::SphereCollision(AttackPos,
						D3DXVECTOR3(OutPos.x, OutPos.y + 50.0f, OutPos.z), ATTACK_LENGTH, pPlayer->GetSizeMax().x))
					{//�e�Ɠ���������(���̂̓����蔻��)

						// ��e��
						CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE);

						//�G�ƃv���C���[�̋���������ۑ�(�ړI�̈ʒu - ���݂̈ʒu)
						D3DXVECTOR3 vecToPlayer = pPlayer->GetPosition() - AttackPos;

						//�G����v���C���[�ւ̃x�N�g��(�ړ���)�ɕϊ�����
						D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

						// �_���[�W��Ԃɂ���
						pPlayer->SetState(STATE_DAMAGE);

						pPlayer->SetControl(false);

						// �x�N�g����ۑ�
						pPlayer->SetVec(vecToPlayer);

						//return true;	//��������
					}
				}
			}
			// �^�C�g����null�`�F�b�N
			if (pGame != nullptr)
			{
				CPlayer *pPlayer = pGame->GetPlayer(nCntPlayer);

				// �v���C���[��null�`�F�b�N
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 OutPos = pPlayer->GetPosition();

					if (pPlayer->GetState() != STATE_DAMAGE && LibrarySpace::SphereCollision(AttackPos,
						D3DXVECTOR3(OutPos.x, OutPos.y + 50.0f, OutPos.z), ATTACK_LENGTH, pPlayer->GetSizeMax().x))
					{//�e�Ɠ���������(���̂̓����蔻��)

						// ��e��
						CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE);

						//�G�ƃv���C���[�̋���������ۑ�(�ړI�̈ʒu - ���݂̈ʒu)
						D3DXVECTOR3 vecToPlayer = pPlayer->GetPosition() - AttackPos;

						//�G����v���C���[�ւ̃x�N�g��(�ړ���)�ɕϊ�����
						D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

						// �_���[�W��Ԃɂ���
						pPlayer->SetState(STATE_DAMAGE);

						pPlayer->SetControl(false);

						// �x�N�g����ۑ�
						pPlayer->SetVec(vecToPlayer);

						//return true;	//��������
					}
				}
			}
		}
		
		// �U���J�E���^�[���Z
		m_nAttackCnt++;

		// �U���I��
		if (m_nAttackCnt >= 55)
		{
			m_bAttack = false;
			m_nAttackCnt = 0;
		}
	}
	else if (GetChange() == false)
	{
		// �L�[�{�[�h����̏ꍇ
		if (m_bControlKeyboard == true && pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_ATTACK) == true ||
			m_bControlKeyboard == false && pJoypad->GetTrigger(CInputJoypad::JOYKEY_B, m_nGamePadNum) == true)
		{// SPACE�L�[����

			// ���ʉ�
			CSound::Play(CSound::SOUND_LABEL_SE_ATTACK);

			m_bAttack = true;
		}
	}
}

//-----------------------------------------------------------------------------
// ��ԊǗ�
//-----------------------------------------------------------------------------
void CPlayer::State()
{
	switch (m_state)
	{
		// �ʏ�
	case CPlayer::STATE_NORMAL:

		// �ҋ@���[�V����
		CMotion::Set(0);

		break;

		// ����
	case CPlayer::STATE_RUN:

		// �ړ����[�V����
		CMotion::Set(1);

		break;

		// �U��
	case CPlayer::STATE_ATTACK:

		// �ړ����[�V����
		CMotion::Set(2);

		break;

		// �W�����v
	case CPlayer::STATE_JUMP:

		// �W�����v���[�V����
		CMotion::Set(3);

		break;

		// ��e
	case CPlayer::STATE_DAMAGE:

		// ����s�\��Ԃɂ���
		m_bControl = false;

		// ��e���[�V����
		CMotion::Set(7);

		//�_���[�W����
		Damage();

		break;

		// ���S
	case CPlayer::STATE_DIE:

		// ���S���[�V����
		CMotion::Set(8);

		break;

		// ����Ɋ������܂�Ă�
	case CPlayer::STATE_INAVALANCHE:
		break;

		// �I��
	case CPlayer::STATE_END:
		break;

	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// �_���[�W����
//-----------------------------------------------------------------------------
void CPlayer::Damage()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	// ��e�x�N�g���̉��Z
	pos += m_knockBack;

	// �ʒu�̐ݒ�
	SetPosition(pos);

	m_nDamageCnt++;

	if (m_nDamageCnt >= 30)
	{
		m_state = STATE_NORMAL;
		m_nDamageCnt = 0;
		m_bControl = true;
	}

	//if (m_BarrierLevel == CBarrier::LEVEL_NONE)
	//{

	// ���S����
	//Die();

	// �v���C���[���S��
	//CSound::Play(CSound::SOUND_LABEL_SE_DIE_PLAYER);

	//}
	//else
	//{
	//	m_BarrierLevel = (CBarrier::LEVEL)(m_BarrierLevel - 1);

	//	if (m_BarrierLevel == CBarrier::LEVEL_NONE)
	//	{
	//		if (m_pBarrier != nullptr)
	//		{
	//			m_pBarrier->Uninit();
	//			m_pBarrier = nullptr;
	//		}
	//	}
	//	else
	//	{
	//		m_pBarrier->SetBarrier(m_BarrierLevel);
	//	}
	//	m_state = STATE_RESPAWN;
	//	m_nCntState = 150;
	//}
}

//-----------------------------------------------------------------------------
// ���S����
//-----------------------------------------------------------------------------
void CPlayer::Die()
{
	//CModel::Uninit();

	// ����s�\�ɂ���
	m_bControl = false;
	// �v���C���[�����S��Ԃɂ���
	m_bDie = true;
	m_state = STATE_DIE;

	if (m_pScore != nullptr)
	{
		// �X�R�A�̐F��ς���
		m_pScore->SetColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	}

	// ���ʉ�
	CSound::Play(CSound::SOUND_LABEL_SE_DIE);

	//// ���C�t���j������Ă��Ȃ����
	//if (m_pLife != nullptr)
	//{
	//	// ���C�t�����炷
	//	m_pLife->Add(-1);

	//	// ���C�t��0����
	//	if (m_pLife->GetLife() < 0)
	//	{
	//		// �X�R�A�̔j��
	//		if (m_pScore != nullptr)
	//		{
	//			m_pScore->Uninit();
	//			m_pScore = nullptr;
	//		}

	//		// ���C�t�̔j��
	//		m_pLife->Uninit();
	//		m_pLife = nullptr;

	//		// �v���C���[�����S��Ԃɂ���
	//		m_bDie = true;

	//		// �T�C�Y�̎擾
	//		D3DXVECTOR2 size = GetSize();
	//		// �����̐���
	//		CExplosion::Create(CObject2D::GetPosition(), D3DXVECTOR2(size.x, size.y * 2));

	//		return;
	//	}

	//	// ����s�\�ɂ���
	//	m_bControl = false;
	//	// ���X�|�[����Ԃɂ���
	//	m_state = STATE_DIE;
	//	m_nCntState = 60;

	//	// �ϐ��̃��Z�b�g
	//	m_nTexRotType = TYPE_NEUTRAL;		//�A�j���[�V�����ԍ������Z�b�g����

	//										// �o���A�̔j��
	//	if (m_pBarrier != nullptr)
	//	{
	//		m_pBarrier->Uninit();
	//		m_pBarrier = nullptr;
	//	}

	//	// �I�v�V�����̔j��
	//	for (int nCnt = 0; nCnt < MAX_OPTION; nCnt++)
	//	{
	//		if (m_pOption[nCnt] != nullptr)
	//		{
	//			m_pOption[nCnt]->Uninit();
	//			m_pOption[nCnt] = nullptr;
	//		}
	//	}

	//	// �e������Ԃ�����������
	//	m_OptionLevel = CBulletOption::LEVEL_NONE;
	//	m_BarrierLevel = CBarrier::LEVEL_NONE;
	//	m_BulletLevel = CPlayer::LEVEL_1;

	//	// �T�C�Y�̎擾
	//	D3DXVECTOR2 size = GetSize();
	//	// �����̐���
	//	CExplosion::Create(CObject2D::GetPosition(), D3DXVECTOR2(size.x, size.y * 2));

	//	//�v���C���[�̈ʒu�����[�ɐݒ肷��
	//	if (m_nPlayerNum == PLAYER_1)
	//	{// 1P�̏ꍇ
	//		CObject2D::SetPosition(D3DXVECTOR3(-SIZE_X, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
	//	}
	//	else
	//	{// 2P�̏ꍇ
	//		CObject2D::SetPosition(D3DXVECTOR3(-SIZE_X, CRenderer::SCREEN_HEIGHT / 2 + SIZE_Y, 0.0f));
	//	}

	//}
}

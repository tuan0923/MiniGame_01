//-----------------------------------------------------------------------------------------------
//
// �G�{�X�̏���[boss.cpp]
// Author :�e���A��
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "boss.h"
#include "manager.h"
#include "renderer.h"

#include "load.h"
#include "sound.h"

#include "game.h"
#include "library.h"
#include "effect.h"
#include "logo.h"
#include "score.h"
#include "fade_scene.h"

#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "logo.h"

// �ǉ�
#include "x_file_motion.h"
#include "motion_data.h"

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// �̗�
const int CBoss::LIFE = 2000;
// ��
const float CBoss::SIZE_WIDTH = 300.0f;
// ����
const float CBoss::SIZE_HEIGHT = 270.0f;
// U���W�̍ő啪����
const int CBoss::DIVISION_U = 4;
// V���W�̍ő啪����
const int CBoss::DIVISION_V = 1;
// �U���O�̗\������Ԋu
const int CBoss::RUSH_OPERATION = 60;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CBoss::CBoss()
	:m_move(0.0f, 0.0f, 0.0f), m_pattern(PATTERN_ENTRY), m_nCounter(0), m_fAttackRot(0.0f),
	m_bSizeChange(false), m_nCountObject(0), m_fAdd(0.0f)
{
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CBoss::~CBoss()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CBoss *CBoss::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// �|�C���^�N���X��錾
	CBoss* pEnemy = new CBoss;

	if (pEnemy != nullptr)
	{
		//�ʒu�ݒ�
		pEnemy->SetPosition(pos);
		// �p�x�ݒ�
		pEnemy->SetRotation(rot);
		// X�t�@�C���̐ݒ�
		pEnemy->BindMotion(CManager::GetManager()->GetMotion()->GetMotion(name));
		// ������
		pEnemy->Init();
	}

	return pEnemy;
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CBoss::Init()
{
	// ��ނ�ݒ�
	SetType(EObject::OBJ_ENEMYBOSS);
	// ������
	CMotion::Init();

	// �U���O�̗\������Ԋu��ݒ�
	m_nCountOperation = RUSH_OPERATION;

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CBoss::Uninit()
{
	CMotion::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CBoss::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CMotion::GetPosition();

	// �e�s��
	Pattern(pos);

	// �ړ�����
	if (m_pattern == PATTERN_NORMAL)
	{// �ړ����[�V����
		
	}
	else
	{
	}

	// �ړ��ʂ̉��Z
	pos += m_move;

	// �ړ��ʂ̌���
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;
	
	// �����蔻��
	Collision(pos);

	// �ʒu���X�V
	CMotion::SetPosition(pos);

	// �p�x�̐��K��
	CMotion::NormalizeRot();

	//}
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CBoss::Draw()
{
	//�`�揈��
	CMotion::Draw();
}

//-----------------------------------------------------------------------------------------------
// �����蔻��
//-----------------------------------------------------------------------------------------------
bool CBoss::Collision(D3DXVECTOR3 posStart)
{
	// �v���C���[����
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		//�v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(nCntPlayer);

		if (pPlayer != nullptr)
		{
			// �v���C���[���ʏ��Ԃ�������
			if (pPlayer->GetState() != CPlayer::STATE_DIE && pPlayer->GetState() != CPlayer::STATE_END)
			{
				// �v���C���[���W�̎擾
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

				//�G�Ɠ���������(���̂̓����蔻��)
				if (LibrarySpace::PlaneCollision(posPlayer.z, posStart.z - 50.0f))
				{//�_���[�W����
					pPlayer->Die();

					return true;	//��������
				}
			}
		}
	}

	return false;	//�������ĂȂ�
}

//-----------------------------------------------------------------------------------------------
// �s���p�^�[���Ǘ�
//-----------------------------------------------------------------------------------------------
bool CBoss::Pattern(D3DXVECTOR3& pos)
{
	//�G���G�������̎擾
	//ParentEnemyInfo *pBossInfo = LoadSpace::GetParentEnemy();

	// ���[�V�����Đ�
	bool bEnd = CMotion::Motion();

	switch (m_pattern)
	{
		//=================================
		// �o��
		//=================================
	case CBoss::PATTERN_ENTRY:

		// �Q�[�����n�܂�����
		if (CManager::GetManager()->GetGame()->GetStart())
		{// �ʏ��Ԃɂ���
			m_pattern = PATTERN_RUN;
		}

		if (bEnd == true)
		{
			m_pattern = PATTERN_NORMAL;
			break;
		}

		CMotion::Set(0);

		break;

		//=================================
		// �ʏ�
		//=================================
	case CBoss::PATTERN_NORMAL:

		// �Q�[�����n�܂�����
		if (CManager::GetManager()->GetGame()->GetStart())
		{// �ʏ��Ԃɂ���
			m_pattern = PATTERN_RUN;
		}

		CMotion::Set(1);

		break;

		//=================================
		// �ʏ�
		//=================================
	case CBoss::PATTERN_RUN:

		if (m_fAdd > 0.9f)
		{
			m_fAdd = 0.9f;
		}

		// �ړ��ʂ̉��Z
		m_move.z -= GetMotion().fMove + m_fAdd;

		CMotion::Set(2);

		m_nCounter++;

		if (m_nCounter >= 300)
		{
			//�J�E���^�[���Z�b�g
			m_nCounter = 0;
			//���̍s���������_���Ō��߂�
			m_pattern = (PATTERN)LibrarySpace::GetRandNum(PATTERN_BARRAGE, PATTERN_SNOWBALL);
		}

		break;

		//=================================
		// �A���ːi�U��
		//=================================
	//case CEnemyBoss::PATTERN_RUSH:

	//	if (m_nCountOperation <= 0)
	//	{
	//		m_nCountOperation--;

	//		// ��ʂ̒��S���W��ۑ�
	//		D3DXVECTOR2 ScreenCenter = D3DXVECTOR2(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2);

	//		if (m_nCounter >= 5)
	//		{
	//			//�ʒu�̕ۑ�
	//			D3DXVECTOR3 vec = m_PosOld - pos;
	//			//�G����v���C���[�ւ̃x�N�g��(�ړ���)�ɕϊ�����
	//			D3DXVec3Normalize(&vec, &vec);
	//			//�ړ��ʂɔ{�����|����
	//			vec.x *= 4.0f;
	//			vec.y *= 4.0f;
	//			//�ړ��ʂ̉��Z
	//			pos += vec;

	//			//�O��̈ʒu�Ɉړ����I������
	//			if (pos.x <= m_PosOld.x)
	//			{
	//				// �ʏ��Ԃɖ߂�(�ϐ��̃��Z�b�g)
	//				StateReset();
	//			}
	//		}
	//		else if (m_nCountOperation == -120)
	//		{
	//			// �ːi����p�x�����߂�
	//			m_fAttackRot = LibrarySpace::GetRandFloat(3, 0, 100);

	//			// �x����
	//			CSound::Play(CSound::SOUND_LABEL_SE_WARNING2);

	//			// �G�̗\���O���͈̓��S
	//			CLogo::Create(D3DXVECTOR3(ScreenCenter.x, ScreenCenter.y, 0.0f), D3DXVECTOR2(ScreenCenter.x * 2.5f, SIZE_HEIGHT),
	//				D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f), m_fAttackRot, CLogo::TYPE_NONE, CLogo::ANIM_NONE, 60);

	//			// ���ӊ��N�W���̃��S
	//			CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(200.0f, 200.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_REMINDER, CLogo::ANIM_FLASHING, 60);

	//			pos = D3DXVECTOR3(ScreenCenter.x, ScreenCenter.y, 0.0f);
	//			float fLenght = sqrtf((ScreenCenter.x * ScreenCenter.x) + (ScreenCenter.y * ScreenCenter.y));
	//			pos += D3DXVECTOR3(cosf(m_fAttackRot) * (fLenght + SIZE_WIDTH), -sinf(m_fAttackRot) * (fLenght + SIZE_HEIGHT), 0);
	//		}
	//		else if (m_nCountOperation <= -180)
	//		{
	//			if (m_nCountOperation == -180)
	//			{
	//				// �ːi��
	//				CSound::Play(CSound::SOUND_LABEL_SE_RUSH);

	//				// �x�����̃X�g�b�v
	//				CSound::Stop(CSound::SOUND_LABEL_SE_WARNING2);
	//			}

	//			// �G�t�F�N�g����
	//			CEffect::Create(pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT), CEffect::TYPE_AFTERIMAGE, CEffect::TEX_BOSS);
	//			D3DXVECTOR3 vec = D3DXVECTOR3((cosf(m_fAttackRot) * 30.0f), -(sinf(m_fAttackRot) * 30.0f), 0);
	//			pos -= vec;
	//			if (LibrarySpace::OutScreen2D(&pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT)) && m_nCountOperation <= -200)
	//			{
	//				m_nCountOperation = -90;
	//				m_nCounter++;

	//				// 5��ːi������
	//				if (m_nCounter >= 5)
	//				{
	//					pos = D3DXVECTOR3((ScreenCenter.x * 2) + (SIZE_WIDTH / 2), ScreenCenter.y - 110.0f, 0.0f);
	//				}
	//			}
	//		}
	//		else if (!LibrarySpace::OutScreen2D(&pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT)))
	//		{
	//			// �G�t�F�N�g����
	//			CEffect::Create(pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT), CEffect::TYPE_AFTERIMAGE, CEffect::TEX_BOSS);
	//			// ���ɓːi����
	//			pos.x += -30.0f;
	//		}
	//	}
	//	else
	//	{
	//		//�g�k������
	//		ChangeSize(&size, 2.0f);

	//		if (m_nCountOperation == RUSH_OPERATION)
	//		{// �ŏ��݈̂ʒu��ۑ�
	//			m_PosOld = pos;
	//		}

	//		m_nCountOperation--;
	//		pos.x += m_nCountOperation * 0.1f;

	//		if(m_nCountOperation==1)
	//		{
	//			// �ːi��
	//			CSound::Play(CSound::SOUND_LABEL_SE_RUSH);
	//		}
	//	}

	//	break;
	//	//=================================
	//	// �G���G�̐����U��
	//	//=================================
	//case CEnemyBoss::PATTERN_CREATE:

	//	//�g�k������
	//	ChangeSize(&size, 3.0f);

	//	//�U���J�E���^�[�����Z
	//	m_nCounter++;

	//	if (m_nCounter >= 60)
	//	{
	//		m_nCountOperation--;

	//		if (m_nCountOperation <= RUSH_OPERATION - pBossInfo->nInterval)
	//		{
	//			m_nCountOperation = RUSH_OPERATION;
	//			CEnemy::Create(pos, (CEnemy::TYPE)pBossInfo->nType, pBossInfo->nLife, pBossInfo->move);
	//			m_nCountObject++;
	//			if (m_nCountObject >= pBossInfo->nNum)
	//			{
	//				// �ʏ��Ԃɖ߂�(�ϐ��̃��Z�b�g)
	//				StateReset();
	//			}
	//		}
	//	}

	//	break;
	//case CEnemyBoss::PATTERN_BARRAGE:

	//	//�g�k������
	//	ChangeSize(&size, 3.0f);

	//	//�U���J�E���^�[�����Z
	//	m_nCounter++;
	//	//��ɉ�]������
	//	m_fAttackRot += 0.05f;

	//	if (m_nCounter >= 60)
	//	{
	//		//�A���U���J�E���^�[�����Z
	//		m_nCountOperation--;

	//		if (m_nCountOperation <= RUSH_OPERATION - 3)
	//		{
	//			m_nCountOperation = RUSH_OPERATION;
	//			m_nCountObject++;
	//			float fDeg = 0.0f;

	//			while (fDeg <= 330.0f)
	//			{
	//				// �e���~��ɔz�u
	//				float fRad = (fDeg * (D3DX_PI / 180)) + m_fAttackRot;
	//				D3DXVECTOR3 vec = D3DXVECTOR3(sinf(fRad) * 10.0f, cosf(fRad) * 10.0f, 0);
	//				CBullet* pBullet = CBullet::Create(pos, vec, 1, CBullet::TYPE_ENEMY_RED);
	//				pBullet->SetParent(CBullet::PARENT_ENEMY);
	//				pBullet->SetRot(fRad);
	//				fDeg += 60.0f;
	//			}

	//			if (m_nCountObject >= 40)
	//			{
	//				// �ʏ��Ԃɖ߂�(�ϐ��̃��Z�b�g)
	//				StateReset();
	//			}

	//			// �e���ˉ�
	//			CSound::Play(CSound::SOUND_LABEL_SE_SHOT2);
	//		}
	//	}
	//	break;

	//	//=================================
	//	// ���S
	//	//=================================
	//case CEnemyBoss::PATTERN_DIE:
	//	// ���S�J�E���^�[�����Z
	//	m_nCounter++;

	//	if (m_nCounter == 1)
	//	{
	//		// ���t�F�[�h�̐���
	//		CFadeScene::Create(CFadeScene::TYPE_WHITE);

	//		// �G�̎��S�t���O�𗧂Ă�
	//		CGame::SetDieBoss(true);

	//		// �{�X���S��
	//		CSound::Play(CSound::SOUND_LABEL_SE_DIE_BOSS);

	//		// �{�XBGM���~�߂�
	//		CSound::Stop(CSound::SOUND_LABEL_BOSS);
	//	}
	//	else if (m_nCounter == 40)
	//	{
	//		// �|�[�Y����
	//		CManager::SetPause(false);
	//	}
	//	else if (m_nCounter >= 40)
	//	{
	//		// �ʒu�������ɉ�����
	//		pos += D3DXVECTOR3(-1.0f, 2.0f, 0.0f);

	//		if (m_nCounter % 5 == 0)
	//		{
	//			// �����̐���
	//			CExplosion::Create(D3DXVECTOR3((float)LibrarySpace::GetRandNum((int)(pos.x + (size.x / 2)), (int)(pos.x - (size.x / 2))),
	//				(float)LibrarySpace::GetRandNum((int)(pos.y + (size.y / 2)), (int)(pos.y - (size.y / 2))), 0.0f),
	//				D3DXVECTOR2(size.x / 2, size.y / 2));
	//		}

	//		if (LibrarySpace::OutScreen2D(&pos, size) == true)
	//		{
	//			//��ʂ�h�炷
	//			//CObject::SetShake(60);
	//			// �{�X���S��
	//			CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION_BOSS);
	//			// �j��
	//			Uninit();

	//			// ���b�V���w�i�̔j��
	//			CMeshField *pMesh = CGame::GetMeshField();
	//			if (pMesh != nullptr)
	//			{
	//				pMesh->SetUninit(true);
	//			}

	//			// �Q�[���N���A���S�̐���
	//			CLogo::Create(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, 100.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_CLEAR, CLogo::ANIM_LENGTHWISE, 420);

	//			CLogo::Create(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH / 4, 150.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_BONUS, CLogo::ANIM_LENGTHWISE, 420);

	//			// �Q�[���N���A��
	//			CSound::Play(CSound::SOUND_LABEL_SE_CLEAR);

	//			// �{�[�i�X�X�R�A���Z
	//			for (int nCnt = 0; nCnt < CPlayer::PLAYER_MAX; nCnt++)
	//			{
	//				CPlayer *pPlayer = CGame::GetPlayer(nCnt);
	//				if (pPlayer != nullptr)
	//				{
	//					// �X�R�A
	//					CScore* pScore = pPlayer->GetScore();
	//						
	//					if (pScore != nullptr)
	//					{
	//						pScore->Add(30000);
	//					}
	//				}
	//			}
	//			return true;
	//		}
	//	}
	//	break;

	default:
		break;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// �g�k����
//-----------------------------------------------------------------------------------------------
void CBoss::ChangeSize(D3DXVECTOR2 *pSize, const float& fSize)
{
	//if (!m_bSizeChange)
	//{
	//	*pSize -= D3DXVECTOR2(fSize, fSize);
	//	if (pSize->x <= SIZE_WIDTH - 20.0f)
	//	{
	//		m_bSizeChange = true;
	//	}
	//}
	//else if (m_bSizeChange)
	//{
	//	*pSize += D3DXVECTOR2(fSize, fSize);
	//	if (pSize->x >= SIZE_WIDTH)
	//	{
	//		m_bSizeChange = false;
	//	}
	//}
}

//-----------------------------------------------------------------------------------------------
// �����o�ϐ����Z�b�g
//-----------------------------------------------------------------------------------------------
void CBoss::StateReset()
{
	//m_nCounter = 0;
	//m_nCountObject = 0;
	//m_fAttackRot = 0.0f;
	//m_pattern = PATTERN_NORMAL;
	//m_nCountOperation = RUSH_OPERATION;
}

//-----------------------------------------------------------------------------------------------
//
// �G�̏���[enemy.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "enemy.h"
#include "manager.h"
#include "renderer.h"

#include "game.h"
#include "library.h"

#include "score.h"
#include "item.h"

#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "spray.h"

//-----------------------------------------------------------------------------------------------
// �萔�ϐ�
//-----------------------------------------------------------------------------------------------
// ��
const float CEnemy::SIZE_WIDTH = 50.0f;
// ����
const float CEnemy::SIZE_HEIGHT = 50.0f;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TYPE_MAX] = { nullptr };

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemy::CEnemy() :
	m_move(0.0f, 0.0f, 0.0f), m_state(STATE_NORMAL), m_type(TYPE_NONE), m_col(COLOR_NONE), m_nLife(0),
	m_nCntState(0), m_nPattern(0), m_nCounter(0), m_nCountAttack(0), m_nNumPatten(0)
{
	CObject::SetType(EObject::OBJ_ENEMY);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemy::~CEnemy()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CEnemy *CEnemy::Create(const D3DXVECTOR3& pos, TYPE type, int nLife, EnemyMove *pEnemyMove)
{
	// �|�C���^�N���X��錾
	CEnemy* pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		//�ʒu�ݒ�
		pEnemy->SetPosition(pos);

		//�ړ����̐ݒ�
		pEnemy->m_pMoveInfo = pEnemyMove;

		//��ނ̐ݒ�
		pEnemy->SetType(type);

		//���C�t�̐ݒ�
		pEnemy->SetLife(nLife);

		// ������
		pEnemy->Init();

		// �e�N�X�`���̐ݒ�
		pEnemy->BindTexture(m_apTexture[pEnemy->m_type]);
	}

	return pEnemy;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CEnemy::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy000.png", &m_apTexture[TYPE_STARFISH]);			// �q�g�f�^�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy001.png", &m_apTexture[TYPE_MOSQUITO]);			// �H���^�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy002.png", &m_apTexture[TYPE_SPHERE]);				// ���̌^�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy003.png", &m_apTexture[TYPE_ASSAULT]);			// �ˌ��^�̓G(�o�g�~���g���̋ʂ݂����ȓG)
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy004.png", &m_apTexture[TYPE_SEAURCHIN]);			// �E�j�^�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy005.png", &m_apTexture[TYPE_ROWLING]);			// ��]�^�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy006.png", &m_apTexture[TYPE_FREEFALL]);			// ���R�����^�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy007.png", &m_apTexture[TYPE_SHOT]);				// �ˌ��^�̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy008.png", &m_apTexture[TYPE_SENTRYGUN]);			// �Œ�C��̓G
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Enemy009.png", &m_apTexture[TYPE_FLYINGFISH]);			// ���ʂ��ԓG
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/EnemyBoss000.png", &m_apTexture[TYPE_RING_BOSS]);		// �����O�^�̒��{�X
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/EnemyBoss001.png", &m_apTexture[TYPE_DARK_BOSS]);		// ��{�X

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̍폜
//-----------------------------------------------------------------------------------------------
void CEnemy::Unload()
{
	for (int nCntEnemy = 0; nCntEnemy < TYPE_MAX; nCntEnemy++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCntEnemy] != nullptr)
		{
			m_apTexture[nCntEnemy]->Release();
			m_apTexture[nCntEnemy] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CEnemy::Init()
{
	// �ړ��ʂ̌v�Z
	m_nRestTime = m_pMoveInfo->nFrameMove;

	// �E�j�^�̓G�����T�C�Y��2�{�ɂ���
	if (m_type == CEnemy::TYPE_SEAURCHIN)
	{
		// �T�C�Y�ݒ�
		CObject2D::SetSize(D3DXVECTOR2(SIZE_WIDTH * 2, SIZE_HEIGHT * 2));
	}
	// �Œ�C��A�G���ݏo���^�̓G�����T�C�Y��1.5�{�ɂ���
	else if (m_type == CEnemy::TYPE_SENTRYGUN || m_type == CEnemy::TYPE_FREEFALL)
	{
		// �T�C�Y�ݒ�
		CObject2D::SetSize(D3DXVECTOR2(SIZE_WIDTH * 1.5f, SIZE_HEIGHT * 1.5f));
	}
	else
	{
		// �T�C�Y�ݒ�
		CObject2D::SetSize(D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT));
	}
	
	// �I�u�W�F�N�g���̏�����
	CObject2D::Init();

	//�H���^�Ǝˌ��^�̓G�����e�N�X�`�����W��ݒ肷��
	if (m_type == CEnemy::TYPE_MOSQUITO || m_type == CEnemy::TYPE_SHOT)
	{
		CObject2D::SetAnimation(m_nPattern, 0, 2, 1);
	}
	// ���ʂ��ԓG�̂݁A�����Ԃ��𐶐�
	else if (m_type == CEnemy::TYPE_FLYINGFISH)
	{
		D3DXVECTOR3 pos = GetPosition();
		CSpray::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));
	}
	
	//if (CManager::GetManager()->GetGame()->GetBubble() == false)
	//{
	//	// ���_�J���[�̐ݒ�
	//	CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.3f, 1.0f));
	//}
	//else
	//{
	//	// ���_�J���[�̐ݒ�
	//	CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CEnemy::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();
	//�ړ��ʂ̐ݒ�
	m_move = (m_pMoveInfo->posEnd - pos) / (float)m_nRestTime;
	//�ړ��܂ł̎��Ԃ�����
	m_nRestTime--;

	// �ړ��ʂ̍X�V
	pos += m_move;

	if (m_nLife <= 0)
	{// ���C�t��0

		// �F���ʏ�ȊO�Ȃ�
		if (m_col != COLOR_NONE)
		{//���S���ɃA�C�e���h���b�v
			//CItem::Create(pos, (CItem::EType)m_col);
		}

		// �����̐���
		CExplosion::Create(pos,GetSize());
		// �j��
		Uninit();
		return;
	}
	else if (LibrarySpace::OutScreen2D(&pos, CObject2D::GetSize()))
	{//��ʊO�ɏo����
		// ���ʂ��ԓG�̂݁A�����Ԃ��𐶐�
		if (m_type == CEnemy::TYPE_FLYINGFISH)
		{
			pos = GetPosition();
			CSpray::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));
		}
		// �j��
		Uninit();
		return;
	}

	//�ړ��ʂ̍Đݒ�
	if (m_nRestTime <= 0)
	{//�ړI�̈ʒu�ɓ��B������
		SetMove(); 
	}

	//�����蔻��
	Collision(pos);


	//�A�j���[�V��������
	SetAnim();
	//��ԊǗ�
	State();
	// �ʒu�̍X�V
	CObject2D::SetPosition(pos);
	//���_���W�̐ݒ�
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CEnemy::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�e�N�X�`���u�����f�B���O�����Z�����ɂ���
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//�`�揈��
	CObject2D::Draw();

	//�e�N�X�`���u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
}

//-----------------------------------------------------------------------------------------------
// �_���[�W����
//-----------------------------------------------------------------------------------------------
void CEnemy::Damage(int nDamage,CPlayer* pPlayer)
{
	m_nLife -= nDamage;
	m_state = STATE_DAMAGE;
	m_nCntState = 5;

	// ���C�t��0�ȉ�
	if (m_nLife <= 0)
	{
		// �X�R�A���Z
		CScore *pScore = pPlayer->GetScore();

		if (pScore != nullptr)
		{
			pScore->Add(200);
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ��ԊǗ�
//-----------------------------------------------------------------------------------------------
void CEnemy::State()
{
	switch (m_state)
	{
	case STATE_NORMAL:			//�G�l�~�[�̏�Ԃ��ʏ�̏ꍇ
		break;
	case STATE_DAMAGE:			//�G�l�~�[���_���[�W��Ԃ̏ꍇ
		//��ԃJ�E���^�[�̌��Z
		m_nCntState--;
		//�_�ł�����
		if (m_nCntState % 2 == 0)
		{//���F
			CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{//�s���N
			CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f));
		}

		//��Ԃ�ʏ�ɖ߂�
		if (m_nCntState <= 0)
		{
			m_state = STATE_NORMAL;

			//�F�t���̓G�Ȃ�
			if (m_col != COLOR_NONE)
			{//�F�̐ݒ�
				SetItemColor(m_col);
			}
			////�����ɓ����Ă����
			//else if (CManager::GetManager()->GetGame()->GetBubble() == false)
			//{//���F�ɂ���
			//	CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.3f, 1.0f));
			//}
			//else
			//{//�ʏ�F�ɖ߂�
			//	CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			//}
		}
		break;
	}
}

//-----------------------------------------------------------------------------------------------
// �v���C���[�Ƃ̓����蔻��
//-----------------------------------------------------------------------------------------------
bool CEnemy::Collision(D3DXVECTOR3 posStart)
{
	//�G�̃T�C�Y�擾
	float fStartLength = GetLength();

	// �v���C���[����
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		//�v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(nCntPlayer);

		if (pPlayer != nullptr)
		{
			// �v���C���[���ʏ��Ԃ�������
			if (pPlayer->GetState() == CPlayer::STATE_NORMAL)
			{
				////�G�Ɠ���������(���̂̓����蔻��)
				//if (LibrarySpace::SphereCollision2D(posStart, pPlayer->GetPosition(), fStartLength, pPlayer->GetLength() - 30.0f))
				//{//�_���[�W����
				//	pPlayer->Damage();
				//	return true;	//��������
				//}
			}
		}
	}

	return false;	//�������ĂȂ�
}

//-----------------------------------------------------------------------------------------------
// �ړ��ʂ̐ݒ�(�v�Z)
//-----------------------------------------------------------------------------------------------
void CEnemy::SetMove()
{
	m_pMoveInfo++;
	m_nRestTime = m_pMoveInfo->nFrameMove;
}

//-----------------------------------------------------------------------------------------------
// �G���ƂɃA�j���[�V����,������ݒ�
//-----------------------------------------------------------------------------------------------
void CEnemy::SetAnim()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();
	//�����̎擾
	float fRot = CObject2D::GetRot();

	switch (m_type)
	{
		//--------------------------------------
		// ���^�A��]�^�̓G
		//--------------------------------------
	case CEnemy::TYPE_STARFISH:
	case CEnemy::TYPE_ROWLING:

		fRot -= 0.1f;

		//�����̍X�V
		CObject2D::SetRot(fRot);

		break;

		//--------------------------------------
		// �H���^�̓G
		//--------------------------------------
	case CEnemy::TYPE_MOSQUITO:

		// �e�̔z�u
		SetVector();

		// ��ɃA�j���[�V��������
		m_nCounter++;
		if (m_nCounter >= 2)
		{
			m_nPattern++;
			m_nCounter = 0;

			if (m_nPattern >= 2)
			{
				m_nPattern = 0;
			}
			CObject2D::SetAnimation(m_nPattern, 0, 2, 1);
		}

		break;

		//--------------------------------------
		// �ˌ��^�̓G
		//--------------------------------------
	case CEnemy::TYPE_ASSAULT:
	{
		// �e�̔z�u
		D3DXVECTOR3 vec = SetVector();

		float fAngle = atan2f(vec.x, vec.y);
		CObject2D::SetRot(fAngle);
	}
	break;

	//--------------------------------------
	// �ی^�̓G
	//--------------------------------------
	case CEnemy::TYPE_SPHERE:
		// �e�̔z�u
		SetVector();
		break;

		//--------------------------------------
		// �E�j�^�̓G
		//--------------------------------------
	case CEnemy::TYPE_SEAURCHIN:
	{
		// �T�C�Y�̎擾
		D3DXVECTOR2 size = CObject2D::GetSize();
		m_nCounter++;

		if (m_nCounter >= 30)
		{
			//�J�E���^�[�̃��Z�b�g
			m_nCounter = 0;
			//�p�^�[���ԍ���؂�ւ���
			m_nPattern = ~m_nPattern;

			if (m_nPattern)
			{
				CObject2D::SetSize(D3DXVECTOR2(size.x + 20.0f, size.y + 20.0f));
			}
			else
			{
				CObject2D::SetSize(D3DXVECTOR2(size.x - 20.0f, size.y - 20.0f));
			}

			//�U���J�E���^�[�����Z
			m_nCountAttack++;
			if (m_nCountAttack >= 3)
			{
				//�J�E���^�[���Z�b�g
				m_nCountAttack = 0;

				float fDeg = 0.0f;

				while (fDeg <= 340.0f)
				{
					// �e���~��ɔz�u
					float fRad = fDeg * (D3DX_PI / 180);
					D3DXVECTOR3 vec = D3DXVECTOR3(sinf(fRad) * 7.0f, cosf(fRad) * 7.0f, 0);
					CBullet* pBullet = CBullet::Create(pos, vec, 1, CBullet::TYPE_ENEMY_LASER);
					pBullet->SetParent(CBullet::PARENT_ENEMY);
					pBullet->SetRot(fRad);
					fDeg += 20.0f;
				}
			}
		}
	}
	break;

	//--------------------------------------
	// ���R�����^�̓G
	//--------------------------------------
	case CEnemy::TYPE_FREEFALL:
		break;

		//--------------------------------------
		// �ˌ��^�̓G
		//--------------------------------------
	case CEnemy::TYPE_SHOT:
		//�U���J�E���^�[�����Z
		m_nCounter++;

		if (m_nCounter >= 60)
		{
			//�A���U���J�E���^�[�����Z
			m_nCountAttack++;

			if (m_nCountAttack >= 5)
			{
				CBullet::Create(pos, D3DXVECTOR3(-7.0f, 0.0f, 0.0f), 1, CBullet::TYPE_ENEMY_RED)->SetParent(CBullet::PARENT_ENEMY);

				m_nCountAttack = 0;
				m_nPattern = ~m_nPattern;

				m_nNumPatten++;
				if (m_nNumPatten >= 3)
				{
					m_nNumPatten = 0;
					m_nCounter = 0;
					m_nPattern = 0;
				}

				CObject2D::SetAnimation(m_nPattern, 0, 2, 1);
			}
		}
		break;

		//--------------------------------------
		// �Œ�C��^�̓G
		//--------------------------------------
	case CEnemy::TYPE_SENTRYGUN:
		//�U���J�E���^�[�����Z
		m_nCounter++;
		//��ɉ�]������
		fRot += 0.01f;

		if (m_nCounter >= 180)
		{
			//�A���U���J�E���^�[�����Z
			m_nCountAttack++;

			if (m_nCountAttack >= 5)
			{
				m_nCountAttack = 0;
				m_nPattern++;
				float fDeg = 0.0f;

				while (fDeg <= 330.0f)
				{
					// �e���~��ɔz�u
					float fRad = (fDeg * (D3DX_PI / 180)) + fRot;
					D3DXVECTOR3 vec = D3DXVECTOR3(sinf(fRad) * 4.0f, cosf(fRad) * 4.0f, 0);
					CBullet* pBullet = CBullet::Create(pos, vec, 1, CBullet::TYPE_ENEMY_RED);
					pBullet->SetParent(CBullet::PARENT_ENEMY);
					pBullet->SetRot(fRad);
					fDeg += 30.0f;

					D3DXVECTOR3(sinf(fRad) * 4.0f, cosf(fRad) * 4.0f, 0);
				}

				if (m_nPattern >= 3)
				{
					m_nCounter = 0;
					m_nPattern = 0;
				}
			}
		}
		CObject2D::SetRot(fRot);

		break;

		//--------------------------------------
		// ���ʂ��ԓG
		//--------------------------------------
	case CEnemy::TYPE_FLYINGFISH:
		//��ɉ�]������
		fRot += 0.025f;

		CObject2D::SetRot(fRot);
		break;

	default:
		break;
	}
}

//-----------------------------------------------------------------------------------------------
// �e�x�N�g���ݒ菈��
//-----------------------------------------------------------------------------------------------
D3DXVECTOR3 CEnemy::SetVector()
{
	// �v���C���[�̈ʒu
	D3DXVECTOR3 posPlayer;
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();
	// �v���C���[�̃G���g���[���
	bool bEntry[CPlayer::PLAYER_MAX];

	//// �v���C���[ENTRY���̎擾
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	bEntry[nCntPlayer] = CManager::GetManager()->GetEntry(nCntPlayer);
	//}

	// 2�l�v���C�����Ă���ꍇ
	if (bEntry[CPlayer::PLAYER_1] == true && bEntry[CPlayer::PLAYER_2] == true)
	{
		// �����ۑ��p
		float nLength[CPlayer::PLAYER_MAX];
		// �v���C���[���̎擾
		CPlayer *pPlayer[CPlayer::PLAYER_MAX];

		// �S�Ẵv���C���[�̋�����ۑ�
		for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
		{
			pPlayer[nCntPlayer] = CManager::GetManager()->GetGame()->GetPlayer(nCntPlayer);

			if (pPlayer[nCntPlayer] != nullptr)
			{
				// �v���C���[�̈ʒu�擾
				posPlayer = pPlayer[nCntPlayer]->GetPosition();
				// �G�ƃv���C���[�̋�����ۑ�
				nLength[nCntPlayer] = LibrarySpace::SphereRange(pos, posPlayer);
			}
		}

		// 2P���1P�̈ʒu���߂����
		if (nLength[CPlayer::PLAYER_1] <= nLength[CPlayer::PLAYER_2])
		{
			if (pPlayer[CPlayer::PLAYER_1] != nullptr)
			{
				// 1P�̈ʒu�ۑ�
				posPlayer = pPlayer[CPlayer::PLAYER_1]->GetPosition();
			}
		}
	}
	// 1P�v���C�Ȃ�
	else if (bEntry[CPlayer::PLAYER_1] == true)
	{
		// �v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(CPlayer::PLAYER_1);

		if (pPlayer != nullptr)
		{
			// 1P�̈ʒu�ۑ�
			posPlayer = pPlayer->GetPosition();
		}
	}
	// 2P�v���C�Ȃ�
	else if (bEntry[CPlayer::PLAYER_2] == true)
	{
		// �v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(CPlayer::PLAYER_2);

		if (pPlayer != nullptr)
		{
			// 2P�̈ʒu�ۑ�
			posPlayer = pPlayer->GetPosition();
		}
	}

	//��Ƀv���C���[�̕���������
	D3DXVECTOR3 vec = posPlayer - pos;

	m_nCounter++;

	if (m_nCounter >= 120)
	{
		//�G����v���C���[�ւ̃x�N�g��(�ړ���)�ɕϊ�����
		D3DXVec3Normalize(&vec, &vec);
		//�x�N�g���ʂ̒���
		vec.x *= 5.0f;
		vec.y *= 5.0f;
		//�e�̐���
		CBullet::Create(pos, vec, 1, CBullet::TYPE_ENEMY_ORANGE)->SetParent(CBullet::PARENT_ENEMY);
		//�U���J�E���^�[�̃��Z�b�g
		m_nCounter = 0;
	}

	return vec;
}

//-----------------------------------------------------------------------------------------------
// �F�̐ݒ�(���Ƃ��A�C�e���̎�ނ�ݒ�)
//-----------------------------------------------------------------------------------------------
void CEnemy::SetItemColor(COLORITEM color)
{
	// �F�̐ݒ�
	m_col = color;

	// ���_�J���[�̐ݒ�
	switch (m_col)
	{
		//��
	case CEnemy::COLOR_RED:
		CObject2D::SetColor(D3DXCOLOR(0.6f, 0.0f, 0.0f, 1.0f));
		break;
		//��
	case CEnemy::COLOR_BLUE:
		CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.6f, 1.0f));
		break;
		//��
	case CEnemy::COLOR_GREEN:
		CObject2D::SetColor(D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f));
		break;
	default:
		break;
	}
}

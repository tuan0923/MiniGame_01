//-----------------------------------------------------------------------------------------------
//
// �e�̏���[bullet.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"

#include "sound.h"
#include "library.h"

#include "player.h"
#include "score.h"
#include "x_file.h"

//-----------------------------------------------------------------------------------------------
// �萔��`
//-----------------------------------------------------------------------------------------------
// ��
const float CItem::SIZE_WIDTH = 40.0f;
// ����
const float CItem::SIZE_HEIGHT = 40.0f;
// ��{�ړ���
const float CItem::MOVE_DEFAULT = 6.0f;
// �A�j���[�V�����Ԋu
const int CItem::ANIM_INTERVAL = 5;
// �A�j���[�V�����ő吔
const int CItem::MAX_ANIM = 4;
// U���W�̍ő啪����
const int CItem::DIVISION_U = 4;
// V���W�̍ő啪����
const int CItem::DIVISION_V = 1;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CItem::m_apTexture[TYPE_MAX] = { nullptr };

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CItem::CItem() :
	m_fRot(0.0f), m_nCntAnim(0), m_nPatternAnim(0), m_type(TYPE_NONE)
{
	SetType(EObject::OBJ_ITEM);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CItem::~CItem()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CItem* CItem::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const EType type, const char* name)
{
	// �|�C���^�N���X��錾
	CItem* pItem = new CItem;

	if (pItem != nullptr)
	{// ����nullptr�ł͂Ȃ�������

		// �ʒu�̐ݒ�
		pItem->SetPosition(pos);
		// �p�x�ݒ�
		pItem->SetRotation(rot);
		//�e�N�X�`����ނ̐ݒ�
		pItem->m_type = type;

		// �e�N�X�`���̐ݒ�
		pItem->BindXFile(CManager::GetManager()->GetXFile()->GetXFile(name));

		// ������
		pItem->Init();

		
	}

	return pItem;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CItem::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item000.png",
		&m_apTexture[TYPE_RED]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item001.png",
		&m_apTexture[TYPE_BLUE]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item002.png",
		&m_apTexture[TYPE_GREEN]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item003.png",
		&m_apTexture[TYPE_ORANGE]);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̍폜
//-----------------------------------------------------------------------------------------------
void CItem::Unload()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CItem::Init()
{
	//// �T�C�Y
	//CObject2D::SetSize(D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT));
	//// ������
	//CObject2D::Init();

	// ������
	CModel::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CItem::Uninit()
{
	//CObject2D::Uninit();

	CModel::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CItem::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	// ��]�ʂ̉��Z
	m_fRot += 0.05f;
	if (m_fRot >= D3DX_PI * 2)
	{
		m_fRot = 0.0f;
	}
	// �ʒu�����擾

	//�ʒu���X�V
	CModel::SetPosition(pos);
	//// �ړ��_�𒆐S�ɉ�]������
	//pos += D3DXVECTOR3(sinf(m_fRot) * MOVE_DEFAULT - 2.5f,
	//	-cosf(m_fRot) * MOVE_DEFAULT,
	//	0.0f);

	//// �T�C�Y�̎擾
	//D3DXVECTOR2 size = CObject2D::GetSize();

	//if (pos.x + (size.x / 2) <= 0.0f)
	//{//����ʒ[�ɏo����I��
	//	Uninit();
	//	return;
	//}

	//�����蔻��
	if (Collision(pos))
	{// ����������I��	
		Uninit();
		return;
	}

	//// �ʒu�̍X�V
	//CObject2D::SetPosition(pos);

	//// �J�E���g�𑝂₷
	//m_nCntAnim++;

	//// ���t���[�����o������
	//if (m_nCntAnim % ANIM_INTERVAL == 0)
	//{
	//	// �A�j���[�V����������1�i�߂�
	//	m_nPatternAnim++;
	//}

	//// �A�j���[�V�������I�������
	//if (m_nPatternAnim == MAX_ANIM)
	//{
	//	// �A�j���[�V����������������
	//	m_nPatternAnim = 0;
	//}
	//else
	//{
	//	//���_���W�̐ݒ�
	//	CObject2D::SetVertex();

	//	//�e�N�X�`���A�j���[�V����
	//	CObject2D::SetAnimation(m_nPatternAnim, 1, DIVISION_U, DIVISION_V);
	//}
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CItem::Draw()
{
	//CObject2D::Draw();
	CModel::Draw();
}

//-----------------------------------------------------------------------------------------------
// �����蔻��
//-----------------------------------------------------------------------------------------------
bool CItem::Collision(D3DXVECTOR3 posStart)
{
	//�T�C�Y�擾
	float fLength = GetSizeMax().x;

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
				// �v���C���[���W
				D3DXVECTOR3 posPlayer = D3DXVECTOR2(pPlayer->GetPosition().x, pPlayer->GetPosition().z);

				//�G�Ɠ���������(���̂̓����蔻��)
				if (LibrarySpace::CylinderCollision3D(posStart, posPlayer, fLength, pPlayer->GetSizeMax().x))
				{//�_���[�W����
					pPlayer->Uninit();
					return true;	//��������
				}
			}
		}
	}

	return false;	//�������ĂȂ�
	////�A�C�e���̃T�C�Y�擾
	//float fStartLength = GetLength();

	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// �v���C���[���̎擾
	//	CPlayer *pPlayer = CGame::GetPlayer(nCntPlayer);

	//	if (pPlayer != nullptr)
	//	{
	//		if (LibrarySpace::SphereCollision2D(posStart, pPlayer->GetPosition(), fStartLength, pPlayer->GetLength()))
	//		{//�A�C�e���Ɠ���������(���̂̓����蔻��)

	//			//�p���[�A�b�v����
	//			pPlayer->SetLevel(m_type);

	//			// �v���C���[���S��
	//			CSound::Play(CSound::SOUND_LABEL_SE_ITEM);

	//			//�X�R�A���Z
	//			CScore* pScore = pPlayer->GetScore();
	//			if (pScore != nullptr)
	//			{
	//				pScore->Add(200);
	//			}

	//			return true;	//��������
	//		}
	//	}
	//}

	//return false;		//�������ĂȂ�
}

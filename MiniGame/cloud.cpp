//-----------------------------------------------------------------------------------------------
//
// �e�̏���[bullet.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "cloud.h"
#include "manager.h"
#include "renderer.h"

#include "library.h"

//-----------------------------------------------------------------------------------------------
// using�錾
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CCloud::m_apTexture[MAX_TEX] = { nullptr };
float CCloud::m_fCreatePos = 0.0f;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CCloud::CCloud() :
	m_move(0.0f, 0.0f, 0.0f)
{
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	SetType(EObject::OBJ_CLOUD);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CCloud::~CCloud()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CCloud * CCloud::Create()
{
	// �|�C���^�N���X��錾
	CCloud* pCloud = new CCloud;

	if (pCloud != nullptr)
	{
		// �ʒu�A�T�C�Y�A�ړ��ʂ𗐐��Őݒ�
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR2 size = SetRandSize();	//�T�C�Y�̐ݒ�

		if (CRenderer::SCREEN_HEIGHT <= (int)m_fCreatePos + 300)
		{
			m_fCreatePos = (float)CRenderer::SCREEN_HEIGHT - 300;
		}

		// �ʒu��(��ʂ̉E�[+�_�̃T�C�Y)�ɐݒ�
		pos.x = (float)CRenderer::SCREEN_WIDTH + (size.x / 2);
		pos.y = (float)GetRandNum((CRenderer::SCREEN_HEIGHT - 300) - (int)m_fCreatePos, 0);
		pos.z = 0.0f;

		//�ʒu�ݒ�
		pCloud->SetPosition(pos);
		//�T�C�Y�ݒ�
		pCloud->SetSize(size);
		// ������
		pCloud->Init();

		// �e�N�X�`���̐ݒ�(�����_���Ńe�N�X�`����ݒ�)
		pCloud->BindTexture(m_apTexture[GetRandNum(1, 0)]);
	}

	return pCloud;
}

//-----------------------------------------------------------------------------------------------
// ����(��������)
//-----------------------------------------------------------------------------------------------
CCloud* CCloud::Create(D3DXVECTOR3 pos)
{
	// �|�C���^�N���X��錾
	CCloud* pCloud = new CCloud;

	if (pCloud != nullptr)
	{
		//�ʒu�ݒ�
		pCloud->SetPosition(pos);
		//�T�C�Y�ݒ�
		pCloud->SetSize(SetRandSize());
		// ������
		pCloud->Init();

		// �e�N�X�`���̐ݒ�(�����_���Ńe�N�X�`����ݒ�)
		pCloud->BindTexture(m_apTexture[GetRandNum(1, 0)]);
	}

	return pCloud;
}

//-----------------------------------------------------------------------------------------------
// �T�C�Y�������_���Ɍ��߂�
//-----------------------------------------------------------------------------------------------
D3DXVECTOR2 CCloud::SetRandSize()
{
	D3DXVECTOR2 size;	//�T�C�Y

	// �T�C�Y�̐ݒ�
	size.x = (float)GetRandNum(DEFAULT_WIDTH, MAX_WIDTH);
	size.y = (float)GetRandNum(DEFAULT_HEIGHT, MAX_HEIGHT);

	return size;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CCloud::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/cloud000.png",
		&m_apTexture[0]);
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/cloud001.png",
		&m_apTexture[1]);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̍폜
//-----------------------------------------------------------------------------------------------
void CCloud::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
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
// �ړ�����
//-----------------------------------------------------------------------------------------------
void CCloud::Move(float fMove)
{
	D3DXVECTOR3 pos;	//�ʒu���i�[�p

	// �_�I�u�W�F�N�g�̎擾
	for (int nCntObject = 0; nCntObject < CObject::MAX_OBJECT; nCntObject++)
	{
		//�I�u�W�F�N�g���̎擾
		CObject *pObject = CObject::GetObject(nCntObject);
		if (pObject != nullptr)
		{
			//�I�u�W�F�N�g�^�C�v�̎擾
			CObject::EObject objType = pObject->GetObjType();
			//�I�u�W�F�N�g�^�C�v���_��������
			if (objType == CObject::OBJ_CLOUD)
			{
				//�_����Ɉړ�����
				CObject2D *pCloud = (CObject2D*)pObject;
				pos = pCloud->GetPosition();
				pos.y += fMove;
				pCloud->SetPosition(pos);
				pCloud->SetVertex();
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CCloud::Init()
{
	// �ړ��ʂ𗐐��Őݒ�(X�̂�)
	m_move.x = -(float)GetRandNum(MAX_MOVEING, DEFAULT_MOVE);
	// ������
	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CCloud::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CCloud::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();
	D3DXVECTOR2 size = CObject2D::GetSize();

	// �ړ��ʂ̍X�V
	pos += m_move;

	if (OutScreen2D(&pos, size))
	{// ���C�t��0
		// �_�̔j��
		Uninit();
	}
	else
	{
		// �ʒu�̍X�V
		CObject2D::SetPosition(pos);

		//���_���W�̐ݒ�
		CObject2D::SetVertex();
	}
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CCloud::Draw()
{
	CObject2D::Draw();
}

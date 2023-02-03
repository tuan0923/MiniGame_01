//=============================================================================
//
// �A�G�t�F�N�g���� (bubble.cpp)
// Author : �㓡�T�V��
//
//=============================================================================
#include "bubble.h"
#include "manager.h"
#include "library.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CBubble::m_pTexture = nullptr;
int CBubble::m_nReverseCount = 0;

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CBubble::CBubble() :m_move(0.0f, 0.0f, 0.0f),m_nReverse(0)
{
	//�^�C�v�̐ݒ�
	SetType(EObject::OBJ_BUBBLE);
	m_nReverseCount++;
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CBubble::~CBubble()
{
}

//-----------------------------------------------------------------------------
// ��������
//-----------------------------------------------------------------------------
CBubble *CBubble::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size)
{
	//�C���X�^���X����
	CBubble *pBubble = new CBubble;

	if (pBubble != nullptr)
	{
		//�ʒu�ݒ�
		pBubble->SetPosition(pos);
		//�T�C�Y�ݒ�
		pBubble->SetSize(size);

		//��������
		pBubble->Init();

		// �e�N�X�`���̐ݒ�
		pBubble->BindTexture(m_pTexture);
	}

	return pBubble;
}

//-----------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------
HRESULT CBubble::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �e�N�X�`���̔j��
//-----------------------------------------------------------------------------
void CBubble::Unload()
{
	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CBubble::Init()
{
	//�ړ��ʂ̐ݒ�
	m_move.y = -1.0f;

	//�h��𔽓]������
	if (m_nReverseCount % 2 == 0)
	{
		m_nReverse = -1;
	}
	else
	{
		m_nReverse = 1;
	}

	CObject2D::Init();
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CBubble::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CBubble::Update()
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();
	D3DXCOLOR col = GetColor();

	col.a -= 0.01f;

	m_move.x += 1.0f;

	//�ړ��ʂ����Z
	pos.x += sinf(m_move.x / 5.0f) * m_nReverse;
	//��ɍ���ɗ���
	pos.x -= 1.0f;
	pos.y += m_move.y;

	// ���l��0�ȉ��܂��͉�ʊO�Ŕj��
	if (col.a <= 0 || LibrarySpace::OutScreen2D(&pos, CObject2D::GetSize()))
	{
		Uninit();
		return;
	}

	//�ʒu�̐ݒ�
	SetPosition(pos);

	//�F(���l)�̐ݒ�
	SetColor(col);

	//���_���W�̐ݒ�
	SetVertex();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CBubble::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �����_�[�X�e�[�g(���Z�����ɂ���)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	// �����_�[�X�e�[�g(���Z������߂�)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

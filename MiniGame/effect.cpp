//===============================================
//
// �G�t�F�N�g���� (effect.cpp)
// Author : SHUGO KURODA
//
//===============================================

//========================
// �C���N���[�h�t�@�C��
//========================
#include "effect.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "library.h"
#include "player.h"
#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include "bg.h"
#include "boss.h"

//=======================================
// �ÓI�����o�ϐ��錾
//=======================================
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[TEX_MAX] = {};

//========================================
// �R���X�g���N�^
//========================================
CEffect::CEffect() :m_move(0.0f, 0.0f, 0.0f), m_nLife(0), m_type(TYPE_SPHERE)
{
	CObject2D::SetType(EObject::OBJ_EFFECT);
}

//========================================
// �f�X�g���N�^
//========================================
CEffect::~CEffect()
{

}

//================================
// ����
//================================
CEffect *CEffect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const TYPE& type, const TEX& tex)
{
	// �ϐ��錾
	CEffect *pEffect = new CEffect;

	if (pEffect != nullptr)
	{
		// �ʒu�ݒ�
		pEffect->SetPosition(pos);

		// �T�C�Y�ݒ�
		pEffect->SetSize(size);

		// �^�C�v�̐ݒ�
		pEffect->m_type = type;

		// ������
		pEffect->Init();

		// �e�N�X�`�������蓖��
		pEffect->BindTexture(m_apTexture[tex]);
	}

	return pEffect;
}


//========================================
// �G�t�F�N�g�̉摜���[�h����
//========================================
HRESULT CEffect::Load()
{
	// �����_���[����f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/particle000.jpg", &m_apTexture[TEX_SPHERE]);		// ���̃p�[�e�B�N��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/EnemyBoss001.png", &m_apTexture[TEX_BOSS]);		// �G�{�X

	return S_OK;
}

//========================================
// �G�t�F�N�g�̉摜�j������
//========================================
void CEffect::Unload()
{
	// �e�N�X�`���̔j��
	for (int nCntTexture = 0; nCntTexture < TYPE_MAX; nCntTexture++)
	{
		if (m_apTexture[nCntTexture] != nullptr)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = nullptr;
		}
	}
}

//========================================
// ������
//========================================
HRESULT CEffect::Init()
{
	//�����̐ݒ�
	m_nLife = MAX_LIFE;

    // ������
	CObject2D::Init();

	// �F�̐ݒ�
	CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	// �e�N�X�`�����W�̐ݒ�
	CObject2D::SetAnimation(0, 0, CBoss::DIVISION_U, CBoss::DIVISION_V);

    return S_OK;
}

//========================================
// �I��
//========================================
void CEffect::Uninit()
{
    // �I������
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CEffect::Update()
{
    // �F�̎擾
    D3DXCOLOR col = GetColor();

	col.a -= 0.1f;

	// ���S�ɓ����ɂȂ�����
	if (col.a <= 0.0f)
	{//�j��
		Uninit();
		return;
	}

	// �F�̐ݒ�
	SetColor(col);
}

//========================================
// �G�t�F�N�g�̕`�揈��
//========================================
void CEffect::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�e�N�X�`���u�����f�B���O�����Z�����ɂ���
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

    // �`�揈��
    CObject2D::Draw();

	//�e�N�X�`���u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
}

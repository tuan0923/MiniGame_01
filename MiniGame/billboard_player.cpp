//========================================================
//
// �r���{�[�h���� [billboard_player.cpp]
// Author : SHUGO KURODA
//
//========================================================
#include "manager.h"
#include "renderer.h"
#include "object3D.h"
#include "billboard_player.h"

#include "texture.h"

//========================================================
// �}�N����`
//========================================================
#define SIZE	(D3DXVECTOR2(200.0f,200.0f))

//========================================================
// �R���X�g���N�^
//========================================================
CBillboardPlayer::CBillboardPlayer() :m_pPosParent(nullptr)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetType(EObject::OBJ_PLAYER);
}

//========================================================
// �f�X�g���N�^
//========================================================
CBillboardPlayer::~CBillboardPlayer()
{
}

//========================================================
// ����
// const D3DXVECTOR3& ParentPos �� �Ǐ]�Ώ�
//========================================================
CBillboardPlayer * CBillboardPlayer::Create(D3DXVECTOR3* pParentPos, const char* name)
{
	//�C���X�^���X����
	CBillboardPlayer *pBillboard = new CBillboardPlayer;

	// �Ǐ]�Ώۂ̈ʒu�ݒ�
	pBillboard->m_pPosParent = pParentPos;

	// ������
	pBillboard->Init();

	// �e�N�X�`���̊��蓖��
	pBillboard->BindTexture(CManager::GetManager()->GetTexture()->GetTexture(name));

	return pBillboard;
}

//========================================================
// ������
//========================================================
HRESULT CBillboardPlayer::Init()
{
	// �ʒu�̐ݒ�
	CBillboard::SetPosition(D3DXVECTOR3(m_pPosParent->x, m_pPosParent->y + 200.0f, m_pPosParent->z));

	// �T�C�Y�̐ݒ�
	CBillboard::SetSize(SIZE);

	// ������
	CBillboard::Init();

	return S_OK;
}

//========================================================
// �j��
//========================================================
void CBillboardPlayer::Uninit()
{
	CBillboard::Uninit();
}

//========================================================
// �X�V
//========================================================
void CBillboardPlayer::Update()
{
	// �ʒu�̐ݒ�
	CBillboard::SetPosition(D3DXVECTOR3(m_pPosParent->x, m_pPosParent->y + 200.0f, m_pPosParent->z));
}

//========================================================
// �`��
//========================================================
void CBillboardPlayer::Draw()
{
	CBillboard::Draw();
}

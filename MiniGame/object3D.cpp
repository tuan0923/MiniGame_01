//===================================================================
//
//	3D�|���S������ [object3D.cpp]
//	Author:SHUGO KURODA
//
//===================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include "object3D.h"

#include "input_keyboard.h"

#include "game.h"
#include "boss.h"

//======================================================
//	�R���X�g���N�^
//======================================================
CObject3D::CObject3D() :
	m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f),
	m_size(0.0f, 0.0f), m_nDel(0), m_bStop(false)
{
}

//======================================================
//	�f�X�g���N�^
//======================================================
CObject3D::~CObject3D()
{
}

//======================================================
//	��������
//======================================================
CObject3D *CObject3D::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size)
{
	//�C���X�^���X����
	CObject3D *pObject3D = new CObject3D;

	// �ʒu�ݒ�
	pObject3D->SetPosition(pos);

	// �T�C�Y�ݒ�
	pObject3D->SetSize(size);

	// ������
	pObject3D->Init();

	// �e�N�X�`���̊��蓖��
	pObject3D->BindTexture(CManager::GetManager()->GetTexture()->GetTexture("TEX_TYPE_TITLE_FLOOR"));

	return pObject3D;
}

//======================================================
//	����������
//======================================================
HRESULT CObject3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx = nullptr;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y, m_pos.z + (m_size.y / 2));
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y, m_pos.z + (m_size.y / 2));
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y, m_pos.z - (m_size.y / 2));
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y, m_pos.z - (m_size.y / 2));

	//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================================================
//	�I������
//======================================================
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//======================================================
//	�X�V����
//======================================================
void CObject3D::Update()
{
	//CInputKeyboard* pInput = CManager::GetManager()->GetInputKeyboard();

	//if (pInput->GetPress(CInputKeyboard::KEYINFO_2))
	//{
	//	m_rot.x += 0.01f;
	//}

	if (m_bStop == false)
	{
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			if (CManager::GetManager()->GetGame()->GetEnd() == false)
			{
				m_pos.z = CManager::GetManager()->GetGame()->GetEnemyBoss()->GetPosition().z;
			}

			//m_nDel++;

			//if (2400 <= m_nDel)
			//{// �j��
			//	
			//}
		}
	}
}

//======================================================
//	�`�揈��
//======================================================
void CObject3D::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,			//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);			//�v���~�e�B�u�i�|���S���j��
}

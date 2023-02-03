//========================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : SHUGO KURODA
//
//========================================================
#include "manager.h"
#include "renderer.h"
#include "object3D.h"
#include "billboard.h"

#include "texture.h"

//========================================================
// �}�N����`
//========================================================
#define BILLBOARD_SIZE (10)												//�r���{�[�h�̃T�C�Y

//========================================================
// �R���X�g���N�^
//========================================================
CBillboard::CBillboard()
{
}

//========================================================
// �f�X�g���N�^
//========================================================
CBillboard::~CBillboard()
{
}

//========================================================
// ����
//========================================================
CBillboard * CBillboard::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const D3DXVECTOR3& rot, const char* name)
{
	//�C���X�^���X����
	CBillboard *pBillboard = new CBillboard;

	// �ʒu�ݒ�
	pBillboard->SetPosition(pos);

	// �p�x�ݒ�
	pBillboard->SetRotation(rot);

	// �T�C�Y�ݒ�
	pBillboard->SetSize(size);

	// ������
	pBillboard->Init();

	// �e�N�X�`���̊��蓖��
	pBillboard->BindTexture(CManager::GetManager()->GetTexture()->GetTexture(name));

	return pBillboard;
}

//========================================================
// ������
//========================================================
HRESULT CBillboard::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CObject3D::VERTEX_3D) * CObject3D::MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		CObject3D::FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���|�C���^��錾
	CObject3D::VERTEX_3D *pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e���_�ʒu�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(-D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(-D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//�e���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//========================================================
// �j��
//========================================================
void CBillboard::Uninit()
{
	//���_�o�b�t�@�̉��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//========================================================
// �X�V
//========================================================
void CBillboard::Update()
{
}

//========================================================
// �`��
//========================================================
void CBillboard::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans, mtxRot, mtxView;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�o�b�t�@�@�̗L����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject3D::VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CObject3D::FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�r���{�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�@��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//�J������L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);
}

//========================================================
// �T�C�Y�̐ݒ�
//========================================================
void CBillboard::SetSize(D3DXVECTOR2 size)
{
	//�傫���̐ݒ�
	m_size = size;
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(size.x * size.x + size.y * size.y) / 2.0f;
	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(size.x, size.y);
}

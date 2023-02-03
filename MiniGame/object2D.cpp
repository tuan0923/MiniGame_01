//=============================================================================
//
// �I�u�W�F�N�g����[object.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "object2D.h"

#include "manager.h"
#include "renderer.h"

#include <assert.h>

//*****************************************************************************
// �e���v���[�g�֐�                       
//*****************************************************************************

//*****************************************************************************
// ����Z
//
// ����   :data0,data1 
// �߂�l :�v�Z����
//*****************************************************************************
template<class T> T Divide(const T data0, const T data1)
{
	T answer = data0 / data1;
	return answer;
}

//-----------------------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-----------------------------------------------------------------------------
CObject2D::CObject2D()
	: m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pos(0.0f, 0.0f, 0.0f), m_size(0.0f, 0.0f), m_fRot(0.0f), m_fLength(0.0f), m_fAngle(0.0f),
	m_col(1.0f, 1.0f, 1.0f, 1.0f), m_nCounterAnim(0), m_nPatternAnim(0), m_move(0.0f, 0.0f, 0.0f)
{
}

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CObject2D::CObject2D(EObject type)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetType(type);
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CObject2D::~CObject2D()
{
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CObject2D::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���|�C���^��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_fRot + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fRot + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fRot + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fRot + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fRot + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fRot + (0.0f - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fRot + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fRot + (0.0f + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_col);
	pVtx[1].col = D3DXCOLOR(m_col);
	pVtx[2].col = D3DXCOLOR(m_col);
	pVtx[3].col = D3DXCOLOR(m_col);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CObject2D::Uninit()
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

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CObject2D::Update()
{
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CObject2D::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-----------------------------------------------------------------------------
// �T�C�Y�̐ݒ�
//-----------------------------------------------------------------------------
void CObject2D::SetSize(D3DXVECTOR2 size)
{
	//�傫���̐ݒ�
	m_size = size;
	//�Ίp���̒������Z�o
	m_fLength = sqrtf(size.x * size.x + size.y * size.y) / 2.0f;
	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(size.x, size.y);
}

//-----------------------------------------------------------------------------
// ���_���W�̐ݒ�
//-----------------------------------------------------------------------------
void CObject2D::SetVertex()
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = (m_pos.x + m_move.x) + sinf(m_fRot + (-D3DX_PI + m_fAngle))*m_fLength;
	pVtx[0].pos.y = (m_pos.y + m_move.y) + cosf(m_fRot + (-D3DX_PI + m_fAngle))*m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = (m_pos.x + m_move.x) + sinf(m_fRot + (D3DX_PI - m_fAngle))*m_fLength;
	pVtx[1].pos.y = (m_pos.y + m_move.y) + cosf(m_fRot + (D3DX_PI - m_fAngle))*m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = (m_pos.x + m_move.x) + sinf(m_fRot + (0.0f - m_fAngle))*m_fLength;
	pVtx[2].pos.y = (m_pos.y + m_move.y) + cosf(m_fRot + (0.0f - m_fAngle))*m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = (m_pos.x + m_move.x) + sinf(m_fRot + (0.0f + m_fAngle))*m_fLength;
	pVtx[3].pos.y = (m_pos.y + m_move.y) + cosf(m_fRot + (0.0f + m_fAngle))*m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@�̉��
	m_pVtxBuff->Unlock();
}

//-----------------------------------------------------------------------------
// ���_�J���[�̐ݒ�
//-----------------------------------------------------------------------------
void CObject2D::SetColor(D3DXCOLOR col)
{
	// �J���[�̐ݒ�
	m_col = col;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_col);
	pVtx[1].col = D3DXCOLOR(m_col);
	pVtx[2].col = D3DXCOLOR(m_col);
	pVtx[3].col = D3DXCOLOR(m_col);

	//���_�o�b�t�@�̉��
	m_pVtxBuff->Unlock();
}

//-----------------------------------------------------------------------------
// �e�N�X�`���A�j���[�V��������(int)
//
// nAnimU �� ���݂̃A�j���[�V����U���W
// nAnimV �� ���݂̃A�j���[�V����V���W
// nPartU �� U���W�̍ő啪����
// nPartV �� V���W�̍ő啪����
//-----------------------------------------------------------------------------
void CObject2D::SetAnimation(int nAnimU, int nAnimV, int nPartU, int nPartV)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f / nPartU) * nAnimU, 0.0f + (1.0f / nPartV) * nAnimV);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nPartU) * (nAnimU + 1), 0.0f + (1.0f / nPartV) * nAnimV);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (1.0f / nPartU) * nAnimU, (1.0f / nPartV) * (nAnimV + 1));
	pVtx[3].tex = D3DXVECTOR2((1.0f / nPartU) * (nAnimU + 1), (1.0f / nPartV) * (nAnimV + 1));

	//���_�o�b�t�@�̉��
	m_pVtxBuff->Unlock();
}

//-----------------------------------------------------------------------------
// �e�N�X�`���A�j���[�V��������(float)
//
// nAnimU �� ���݂̃A�j���[�V����U���W
// nAnimV �� ���݂̃A�j���[�V����V���W
// fPartU �� U���W�̍ő啪����
// fPartV �� V���W�̍ő啪����
//-----------------------------------------------------------------------------
void CObject2D::SetAnimation(int nAnimU, int nAnimV, float fPartU, float fPartV)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̐ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f / fPartU) * nAnimU, 0.0f + (1.0f / fPartV) * nAnimV);
	pVtx[1].tex = D3DXVECTOR2((1.0f / fPartU) * (nAnimU + 1), 0.0f + (1.0f / fPartV) * nAnimV);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (1.0f / fPartU) * nAnimU, (1.0f / fPartV) * (nAnimV + 1));
	pVtx[3].tex = D3DXVECTOR2((1.0f / fPartU) * (nAnimU + 1), (1.0f / fPartV) * (nAnimV + 1));

	//���_�o�b�t�@�̉��
	m_pVtxBuff->Unlock();
}

//-----------------------------------------------------------------------------
// �w�i�A�j���[�V��������
//-----------------------------------------------------------------------------
void CObject2D::SetAnimBg(int nSpeed, int nPattern, bool bRightToLeft)
{
	// �A�j���[�V����
	m_nCounterAnim++;	//�J�E���^���Z

	if (m_nCounterAnim == nSpeed)//����
	{
		// �I�[�o�[�t���[�h�~
		m_nCounterAnim = 0;  // �J�E���^��0�ɖ߂�

		// �A�j���[�V������؂�ւ���
		m_nPatternAnim = (m_nPatternAnim + 1) % nPattern;  // ����
	}

	// ���������邩�v�Z
	float fEqualDivision = Divide(1.0f, (float)nPattern);

	// ������E�Ȃ�A-1��������
	if (bRightToLeft == false)
	{
		fEqualDivision *= -1;
	}

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`���̍��W�𔽉f
	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * fEqualDivision, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * fEqualDivision + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * fEqualDivision, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * fEqualDivision + 1.0f, 1.0f);

	//���_�o�b�t�@�̉��
	m_pVtxBuff->Unlock();
}

//-----------------------------------------------------------------------------
// �w�i�A�j���[�V��������(�E���オ��)
//-----------------------------------------------------------------------------
void CObject2D::SetAnimBgLeftUp(int nSpeed, int nPattern, bool bRightToLeft)
{
	// �A�j���[�V����
	m_nCounterAnim++;	//�J�E���^���Z

	if (m_nCounterAnim == nSpeed)//����
	{
		// �I�[�o�[�t���[�h�~
		m_nCounterAnim = 0;  // �J�E���^��0�ɖ߂�

		// �A�j���[�V������؂�ւ���
		m_nPatternAnim = (m_nPatternAnim + 1) % nPattern;  // ����
	}

	// ���������邩�v�Z
	float fEqualDivision = Divide(1.0f, (float)nPattern);

	// ������E�Ȃ�A-1��������
	if (bRightToLeft == false)
	{
		fEqualDivision *= -1;
	}

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`���̍��W�𔽉f
	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * fEqualDivision, m_nPatternAnim * (fEqualDivision * (-1)));
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * fEqualDivision + 1.0f, m_nPatternAnim * (fEqualDivision * (-1)));
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * fEqualDivision, m_nPatternAnim * (fEqualDivision * (-1)) + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * fEqualDivision + 1.0f, m_nPatternAnim * (fEqualDivision * (-1)) + 1.0f);

	//���_�o�b�t�@�̉��
	m_pVtxBuff->Unlock();
}

//-----------------------------------------------------------------------------
// �e�N�X�`���̕`��͈͂̐ݒ�
//-----------------------------------------------------------------------------
void CObject2D::SetTextureRange(int nRange, int nPattern)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	float fEqualDivision = 0.0f;   // �e�N�X�`���𓙕�����

	// ���������邩�v�Z
	fEqualDivision = Divide((float)nRange, (float)nPattern);

	// �e�N�X�`���̍��W�𔽉f
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fEqualDivision, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fEqualDivision, 1.0f);

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

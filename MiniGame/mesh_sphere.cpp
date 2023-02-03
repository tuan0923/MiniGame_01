//=============================================================================
//
// ���b�V��(��)���� [mesh_sphere.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "object3D.h"

#include "mesh_sphere.h"
#include "texture.h"

#include "game.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define CYLINDER_MAX		(256)		//���̂̍ő吔

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CMeshSphere::CMeshSphere() :
	m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pIdxBuff(nullptr), m_pos(0.0f, 0.0f, 0.0f), m_pPosTrak(nullptr),
	m_rot(0.0f, 0.0f, 0.0f), m_col(0.0f, 0.0f, 0.0f, 0.0f), m_rad(0.0f, 0.0f), m_nMeshX(0), m_nMeshZ(0), m_bMove(false)
{
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CMeshSphere::~CMeshSphere()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CMeshSphere* CMeshSphere::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXCOLOR& col, const D3DXVECTOR2& rad, const int& nMeshX, const int& nMeshZ, const char* name)
{
	// ����
	CMeshSphere* pMeshSphere = new CMeshSphere;

	// �\���̂��g�p��Ԃɂ���
	pMeshSphere->m_pos = pos;
	pMeshSphere->m_rot = rot;
	pMeshSphere->m_col = col;
	pMeshSphere->m_rad = rad;
	pMeshSphere->m_nMeshX = nMeshX;
	pMeshSphere->m_nMeshZ = nMeshZ;
	pMeshSphere->m_pTexture = CManager::GetManager()->GetTexture()->GetTexture(name);

	// ������
	pMeshSphere->Init();

	return pMeshSphere;
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CMeshSphere::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// ���_���̌v�Z
	m_nTop = (m_nMeshX + 1) * (m_nMeshZ + 1);
	// �C���f�b�N�X���̌v�Z
	m_nIdx = (m_nMeshX + 1) * 2 * m_nMeshZ + (m_nMeshZ - 1) * 2;
	// �|���S�����̌v�Z
	m_nPolygon = m_nMeshX * m_nMeshZ * 2 + (m_nMeshZ - 1) * 4;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CObject3D::VERTEX_3D) * 4 * m_nTop,	// �m�ۂ��钸�_�̐�
		D3DUSAGE_WRITEONLY,
		CObject3D::FVF_VERTEX_3D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�̃C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 4 * m_nIdx,	// �m�ۂ��钸�_�̐�
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	CObject3D::VERTEX_3D *pVtx = NULL;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= m_nMeshZ; nCntZ++)
	{
		float fData = m_rad.y * cosf((D3DX_PI / m_nMeshZ * nCntZ) - D3DX_PI / 2);

		for (int nCntX = 0; nCntX <= m_nMeshX; nCntX++)
		{
			pVtx[0].pos.x = fData * sinf(D3DX_PI * 2 / m_nMeshX * nCntX);
			pVtx[0].pos.y = m_rad.y * sinf((D3DX_PI / m_nMeshZ  * nCntZ) - D3DX_PI / 2);
			pVtx[0].pos.z = fData * cosf(D3DX_PI * 2 / m_nMeshX * nCntX);

			// �e���_�̖@���̐ݒ�i�x�N�g���̑傫���͂P�ɂ���K�v������j
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = m_col;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((1.0f / m_nMeshX) * nCntX, (1.0f / m_nMeshZ) * nCntZ);

			// �f�[�^��1���i�߂�
			pVtx++;
		}
	}

	// �C���f�b�N�X���ւ̃|�C���^
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntZ = 0; nCntZ <= m_nMeshZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_nMeshX; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (WORD)(nCntX + (m_nMeshX + 1) * (nCntZ + 1));
			pIdx[1] = (WORD)(nCntX + (m_nMeshX + 1) * nCntZ);
			pIdx += 2;		//�C���f�b�N�X�̃f�[�^���Q�����߂�
		}

		if (nCntZ < m_nMeshZ - 1)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = pIdx[-1];
			pIdx[1] = (WORD)((m_nMeshX + 1) * (nCntZ + 2));
			pIdx += 2;		//�C���f�b�N�X�̃f�[�^���Q�����߂�
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �j��
//-----------------------------------------------------------------------------------------------
void CMeshSphere::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	Release();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CMeshSphere::Update()
{
	if (m_bMove == false)
	{
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			if (CManager::GetManager()->GetGame()->GetEnd() == true)
			{
				m_pPosTrak = nullptr;
				m_bMove = true;
			}
			else if (CManager::GetManager()->GetGame()->GetEnd() == false)
			{
				if (m_pPosTrak != nullptr)
				{
					m_pos = *m_pPosTrak;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CMeshSphere::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�J�����OOFF
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject3D::VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CObject3D::FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,					// �`�悷��ŏ��̒��_�C���f�b�N�X
		0,					// �C���f�b�N�X�̍ŏ��l
		m_nTop,				// ���_�̐�
		0,					// �C���f�b�N�X�̍ŏ��̐�
		m_nPolygon);		// �v���~�e�B�u�i�|���S���j��

	//�J�����O�����ɖ߂�(ON)
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

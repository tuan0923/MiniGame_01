//-----------------------------------------------------------------------------------------------
//
// ���b�V���t�B�[���h����[meshfield.cpp]
// Author : SHUGO KURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "object2D.h"

#include "mesh_field.h"
#include "input_keyboard.h"

//-----------------------------------------------------------------------------------------------
//	�}�N����`
//-----------------------------------------------------------------------------------------------
#define MESHFIELD_VERTEX_NUM		((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Y_BLOCK + 1))		//���_��
#define MESHFIELD_INDEX_NUM			((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Y_BLOCK + (MESHFIELD_Y_BLOCK - 1) * 2)		//�C���f�b�N�X��
#define MESHFIELD_PRIMITIVE_NUM		(MESHFIELD_X_BLOCK * MESHFIELD_Y_BLOCK * 2 + (MESHFIELD_Y_BLOCK - 1) * 4)			//�|���S����

//-----------------------------------------------------------------------------------------------
//	�ÓI�����o�ϐ��錾
//-----------------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = {};

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CMeshField::CMeshField() :m_pos(0.0f, 0.0f, 0.0f), m_pVtxBuff(nullptr), m_pIdxBuff(nullptr),
m_nCounterAnim(0), m_nPatternAnim(0), m_col(0.0f, 0.0f, 0.0f, 0.0f), m_bCol(false), m_move(0.0f, 0.0f, 0.0f), m_bUninit(false)
{
	SetType(EObject::OBJ_BG_MOVE);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CMeshField::~CMeshField()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CMeshField *CMeshField::Create()
{
	// �|�C���^�N���X��錾
	CMeshField* pMeshField = new CMeshField;

	// ������
	pMeshField->Init();

	return pMeshField;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CMeshField::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	HRESULT hr = D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000_11.jpg",
		&m_pTexture);

	return hr;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̔j��
//-----------------------------------------------------------------------------------------------
void CMeshField::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CMeshField::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(CObject2D::VERTEX_2D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		CObject2D::FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	CObject2D::VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	WORD *pIdx;				//�C���f�b�N�X���ւ̃|�C���^

	m_pos = D3DXVECTOR3(-CRenderer::SCREEN_WIDTH / 2, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e���_���W�̐ݒ�
	for (int nCntBlockY = 0; nCntBlockY < MESHFIELD_Y_BLOCK + 1; nCntBlockY++)
	{//Y�����̍��W�ݒ�
		for (int nCntBlockX = 0; nCntBlockX < MESHFIELD_X_BLOCK + 1; nCntBlockX++)
		{//X�����̍��W�ݒ�
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(m_pos.x + ((CRenderer::SCREEN_WIDTH * 1.6f) / MESHFIELD_X_BLOCK) * nCntBlockX, m_pos.y + (CRenderer::SCREEN_HEIGHT / MESHFIELD_Y_BLOCK) * nCntBlockY, m_pos.z);
			//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���K�v������)
			pVtx[0].rhw = 1.0f;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(m_col);
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((1.0f / MESHFIELD_X_BLOCK) * nCntBlockX, (1.0f / MESHFIELD_Y_BLOCK) * nCntBlockY);

			pVtx++;
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	{
		int nCntIdxX, nCntIdxY;

		//�C���f�b�N�X�̐ݒ�
		for (nCntIdxY = 0; nCntIdxY < MESHFIELD_Y_BLOCK; nCntIdxY++)
		{//Z�����̃C���f�b�N�X�ݒ�
			for (nCntIdxX = 0; nCntIdxX < MESHFIELD_X_BLOCK + 1; nCntIdxX++)
			{//X�����̃C���f�b�N�X�ݒ�
				pIdx[0] = (WORD)(nCntIdxX + ((MESHFIELD_X_BLOCK + 1) * nCntIdxY) + MESHFIELD_X_BLOCK + 1);
				pIdx[1] = (WORD)(nCntIdxX + ((MESHFIELD_X_BLOCK + 1) * nCntIdxY));

				pIdx += 2;
			}

			//�k�ރ|���S���p�̃C���f�b�N�X�ݒ�
			if (nCntIdxY <= MESHFIELD_Y_BLOCK - 2)
			{//�Ō�̃C���f�b�N�X�ԍ��ł͂Ȃ���
				pIdx[0] = (WORD)((nCntIdxX - 1) + ((MESHFIELD_X_BLOCK + 1) * nCntIdxY));
				pIdx[1] = (WORD)((nCntIdxX + (MESHFIELD_X_BLOCK + 1)) + ((MESHFIELD_X_BLOCK + 1) * nCntIdxY));
			}
			pIdx += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �j��
//-----------------------------------------------------------------------------------------------
void CMeshField::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//�C���f�b�N�X�o�b�t�@�̉��
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
void CMeshField::Update()
{
	// �A�j���[�V����
	m_nCounterAnim++;	//�J�E���^���Z

	if (m_nCounterAnim == 2)//����
	{
		// �I�[�o�[�t���[�h�~
		m_nCounterAnim = 0;  // �J�E���^��0�ɖ߂�

		// �A�j���[�V������؂�ւ���
		m_nPatternAnim = (m_nPatternAnim + 1) % 1000;  // ����
	}

	// ���������邩�v�Z
	float fEqualDivision = 1.0f / (float)1000;

	// ���_���ւ̃|�C���^
	CObject2D::VERTEX_2D *pVtx;

	if (m_bCol == true)
	{
		m_col.r += 0.01f;
		m_col.b -= 0.01f;
		if (m_col.r >= 1.0f)
		{
			m_bCol = false;
		}
	}
	else if (m_bCol == false)
	{
		m_col.r -= 0.01f;
		m_col.b += 0.01f;
		if (m_col.r <= 0.0f)
		{
			m_bCol = true;
		}
	}

	// �I���t���O����������
	if (m_bUninit == true)
	{
		m_col.a -= 0.01f;

		if (m_col.a <= 0.0f)
		{
			// �I��
			Uninit();
			return;
		}
	}
	else if (m_col.a <= 1.0f)
	{
		m_col.a += 0.005f;
	}

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e���_���W�̐ݒ�
	for (int nCntBlockY = 0; nCntBlockY < MESHFIELD_Y_BLOCK + 1; nCntBlockY++)
	{//Y�����̍��W�ݒ�

		for (int nCntBlockX = 0; nCntBlockX < MESHFIELD_X_BLOCK + 1; nCntBlockX++)
		{//X�����̍��W�ݒ�
			float offsetX = sinf(D3DX_PI * 2.0f * (nCntBlockY + m_nPatternAnim) / MESHFIELD_Y_BLOCK * 0.2f) * 20.0f;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3((m_pos.x + m_move.x) + ((CRenderer::SCREEN_WIDTH * 1.6f) / MESHFIELD_X_BLOCK) * nCntBlockX + offsetX,
				(m_pos.y + m_move.y) + (CRenderer::SCREEN_HEIGHT / MESHFIELD_Y_BLOCK) * nCntBlockY,
				m_pos.z);

			// �F�̐ݒ�
			pVtx[0].col = D3DXCOLOR(m_col);

			// �e�N�X�`���̍��W�𔽉f
			pVtx[0].tex = D3DXVECTOR2(((1.0f / MESHFIELD_X_BLOCK) * nCntBlockX) + m_nPatternAnim * fEqualDivision, (1.0f / MESHFIELD_Y_BLOCK) * nCntBlockY);

			pVtx++;
		}
	}

	//���_�o�b�t�@�̉��
	m_pVtxBuff->Unlock();

#ifdef _DEBUG
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();

	if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_1) == true)
	{//3�L�[�������ꂽ
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_2) == true)
	{//4�L�[�������ꂽ
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
#endif // _DEBUG
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CMeshField::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject2D::VERTEX_2D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CObject2D::FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,			//
		0,			//
		MESHFIELD_VERTEX_NUM,		//���_��
		0,							//�`�悷��ŏ��̒��_�C���f�b�N�X
		MESHFIELD_PRIMITIVE_NUM);	//�v���~�e�B�u�i�|���S���j��
}

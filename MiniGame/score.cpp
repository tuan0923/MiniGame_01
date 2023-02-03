//=============================================================================
//
// �X�R�A����[score.cpp]
// Author : SHUGO KURODA
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"
#include "score.h"
#include "number.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore() :m_nScore(0)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetType(EObject::OBJ_PAUSE);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// ����
// const D3DXVECTOR3& pos �� ��������ʒu
// const D3DXVECTOR2& size �� ��������T�C�Y
// const int& nNumSpace �� �����̊Ԋu
//=============================================================================
CScore *CScore::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size,const int& nNumSpace)
{
	CScore *pScore = new CScore;

	if (pScore != nullptr)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{
			// �����|���S������
			pScore->m_apNumber[nCntScore] = new CNumber("TEX_TYPE_SCORE_UI");

			if (pScore->m_apNumber[nCntScore] != nullptr)
			{
				// �ʒu�ݒ�
				pScore->m_apNumber[nCntScore]->SetPosition(D3DXVECTOR3(pos.x + (nCntScore * nNumSpace), pos.y, pos.z));
				// �T�C�Y�ݒ�
				pScore->m_apNumber[nCntScore]->SetSize(size);
				// ������
				pScore->m_apNumber[nCntScore]->Init();
			}
		}
	}

	return pScore;
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CScore::Init()
{
	CObject::SetType(CObject::OBJ_SCORE);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CScore::Uninit()
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE; nCntNumber++)
	{
		// ���g������Ȃ�
		if (m_apNumber[nCntNumber] != nullptr)
		{
			// �������̏I������
			m_apNumber[nCntNumber]->Uninit();
			m_apNumber[nCntNumber] = nullptr;
		}
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CScore::Update()
{
}

//=============================================================================
// �`��
//=============================================================================
void CScore::Draw()
{
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CScore::Add(const int& nScore)
{
	m_nScore += nScore;
	Set();
}

//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
void CScore::Set(const int& nScore)
{
	m_nScore = nScore;
	Set();
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CScore::SetColor(D3DXCOLOR col)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE; nCntNumber++)
	{
		// ���g������Ȃ�
		if (m_apNumber[nCntNumber] != nullptr)
		{// �������̐F��ݒ�
			m_apNumber[nCntNumber]->SetColor(col);
		}
	}
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
D3DXCOLOR CScore::GetColor()
{
	return m_apNumber[0]->GetColor();
}

//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
void CScore::Set()
{
	//�e���̐��l���i�[(pPostexU[�����Ƃ̐��l])
	int aPosTexU[MAX_SCORE];

	aPosTexU[0] = (m_nScore % 100000000) / 10000000;
	aPosTexU[1] = (m_nScore % 10000000) / 1000000;
	aPosTexU[2] = (m_nScore % 1000000) / 100000;
	aPosTexU[3] = (m_nScore % 100000) / 10000;
	aPosTexU[4] = (m_nScore % 10000) / 1000;
	aPosTexU[5] = (m_nScore % 1000) / 100;
	aPosTexU[6] = (m_nScore % 100) / 10;
	aPosTexU[7] = m_nScore % 10;

	//�e�N�X�`�����X�V����
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]->SetAnimation(aPosTexU[nCntScore], 0, CNumber::DIVISION_U, CNumber::DIVISION_V);
	}
}
//=============================================================================
//
// �����N���� [rank.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _RANK_H_
#define _RANK_H_

#include "object2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;

//*****************************************************************************
// �����L���O�N���X(�h���N���X)
//*****************************************************************************
class CRank : public CObject
{
public:
	// �ő僉���L���O�X�R�A��
	static const int MAX_RANKING = 5;
	// �ő�v���C���[�X�R�A��
	static const int MAX_PLAYER_SCORE = 2;

	enum TYPE
	{//�w�i�̎��
		TYPE_PLAYER1 = 0,	// �v���C���[1
		TYPE_PLAYER2,		// �v���C���[2
		TYPE_BG,			// �w�i
		TYPE_RANK,			// �����L���OUI
		TYPE_MAX			// �w�i�̍ő吔
	};

	CRank();
	~CRank();

	static CRank *Create();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Save(int nHiScore);

	CScore* GetScore() { return m_pScore; }

private:
	// �X�R�A�i�[�p
	CScore* m_pScore;
};

#endif

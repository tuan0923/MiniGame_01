//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "enemy_data.h"

#include "player.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;
class CBoss;
class CItem;
class CCamera;
class CRank;

//-----------------------------------------------------------------------------
// �Q�[����ʃN���X
//-----------------------------------------------------------------------------
class CGame
{
private:	//�萔
	static const int MAX_POS_CLOUD = 250;
	static const int MIN_POS_CLOUD = 180;

public:		//�����o�֐�
	CGame();
	~CGame();

	// ������
	HRESULT Init();
	// �I��
	void Uninit();
	// �X�V
	void Update();

	// �Q�[�����I�����邩�ǂ����𔻒�
	bool CheckGameEnd();
	// �G�𐶐�
	void CreateEnemy();
	// ���S�𐶐�
	void CreateLogo(int nCounter);

	// �Q�[���J�n�t���O��ݒ�
	void SetStart(bool bStart) { m_bStart = bStart; }
	void SetCameraPlayer(bool bCamera);

	// �v���C���[���̎擾
	CPlayer *GetPlayer(int nNum) { return m_pPlayer[nNum]; }
	// �G�{�X���
	CBoss* GetEnemyBoss() { return m_pEnemyBoss; }
	//Item ���
	CItem* GetItem() { return m_pItem; }
	//�J�������
	CCamera* GetCamera() { return m_pCamera; }

	// �Ō�Ɏ��񂾃v���C���[�ԍ��̎擾
	int GetPlayerDie() { return m_nPlayerDie; }
	// �Q�[���J�n�t���O���擾
	bool GetStart() { return m_bStart; }
	// �Q�[���J�n�t���O���擾
	bool GetEnd() { return m_bEnd; }
	// �v���C���[�̃X�R�A�������L���O�ɐݒ�1
	void SetPlayerScore();

private:
	// �e�N�X�`���ǂݍ���
	//static void LoadAll();
	// �e�N�X�`���j��
	//static void UnloadAll();

private:	//�����o�ϐ�
	// �v���C���[���
	CPlayer *m_pPlayer[CPlayer::PLAYER_MAX];
	CBoss* m_pEnemyBoss;
	CItem* m_pItem;
	CCamera* m_pCamera;
	CRank* m_pRank;

	// �Q�[�����n�܂������ǂ���
	bool m_bStart;
	// �Q�[�����I���������ǂ���
	bool m_bEnd;
	// �v���C���[�ɃJ������Ǐ]���邩�ǂ���
	bool m_bCameraPlayer;

	// �G�̃Z�b�g���
	EnemySetInfo m_EnemyInfo;

	// �J�E���g�_�E�����n�߂�܂ł̃J�E���^�[
	int m_nStartCnt;
	// �Ō�Ɏ��񂾃v���C���[�ԍ�
	int m_nPlayerDie;
	// ��ʑJ�ڂ���܂ł̃J�E���^�[
	int m_nScene;
};

#endif	//_GAME_H_

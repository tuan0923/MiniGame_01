//===================================================================
//
//	�v���C���[�̏���[player.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object2D.h"
#include "motion.h"

//*******************************************************************
//	�O���錾
//*******************************************************************
class CLife;
class CScore;
class CLogo;

//*******************************************************************
//	�}�N����`
//*******************************************************************
#define PLAYER_SIZE					(D3DXVECTOR3(10.0f,90.0f,10.0f))

//*******************************************************************
//	�v���C���[�N���X�̒�`
//*******************************************************************
class CPlayer : public CMotion
{
private:
	//�v���C���[�̃T�C�Y(X)
	static const float SIZE_X;
	// �v���C���[�̃T�C�Y(Y)
	static const float SIZE_Y;
	// �v���C���[�̊�{�ړ���
	static const float MOVE_DEFAULT;
	// �A�j���[�V�����Ԋu
	static const int ANIM_INTERVAL;
	// �A�j���[�V�����ő吔
	static const int MAX_ANIM;
	// U���W�̍ő啪����
	static const int DIVISION_U;
	// V���W�̍ő啪����
	static const int DIVISION_V;
	// �v���C���[�̃f�t�H���g�J���[
	static const D3DXCOLOR DEFAULT_COL;
	// �ő�I�v�V������
	static const int MAX_OPTION = 4;
	// �f�t�H���g�c�@��
	static const int DEFAULT_LIFE;

public:
	// �v���C���[
	enum PLAYER
	{
		PLAYER_1 = 0,	//1P
		PLAYER_2,		//2P
		PLAYER_3,		//3P
		PLAYER_4,		//4P
		PLAYER_MAX
	};

	//���
	enum STATE
	{
		STATE_NORMAL = 0,	// �ʏ�
		STATE_RUN,			// ����
		STATE_ATTACK,		// �U��
		STATE_JUMP,			// �W�����v
		STATE_DAMAGE,		// ��e
		STATE_DIE,			// ���S���
		STATE_INAVALANCHE,	// ����Ɋ������܂�Ă�����
		STATE_END,			// �I��
		STATE_MAX
	};

	//�A�j���[�V�����ԍ�
	enum ANIMTYPE
	{
		TYPE_NEUTRAL = 0,
		TYPE_UP,
		TYPE_DOWN,
		TYPE_MAX
	};

	//�����o�֐�
public:

	// �R���X�g���N�^
	CPlayer();
	// �f�X�g���N�^
	~CPlayer() override;

	// ����
	static CPlayer *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name, int nPlayerNum);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;
	// ���S����
	void Die();

	// ��Ԃ̎擾
	STATE GetState() { return m_state; }
	// �X�R�A���̎擾
	CScore *GetScore() { return m_pScore; }
	// ���S��Ԃ̎擾
	bool GetDie() { return m_bDie; }
	// �ߋ��̈ʒu���擾
	D3DXVECTOR3 GetPositionOld() { return m_posOld; }
	// �v���C���[�ԍ��̎擾
	int GetNum() { return m_nPlayerNum; }
	// �v���C���[�ԍ��̎擾
	int GetPadNum() { return m_nGamePadNum; }
	// �v���C���[�ԍ��̎擾
	bool GetReady() { return m_bReady; }	
	
	// �ړ��ʂ̐ݒ�
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }
	// �ړ���X�̐ݒ�
	void SetMoveX(const float& fmove) { m_move.x = fmove; }
	// �ړ���Z�̐ݒ�
	void SetMoveZ(const float& fmove) { m_move.z = fmove; }
	// �ړ���Y�̐ݒ�
	void SetMoveY(const float& fmove) { m_move.y = fmove; }
	// ��Ԃ̐ݒ�
	void SetState(const STATE& inState) { m_state = inState; }
	// ��e�x�N�g���̐ݒ�
	void SetVec(const D3DXVECTOR3& vec) { m_knockBack = vec; }
	// �����Ԃ̐ݒ�
	void SetControl(const bool& bControl) { m_bControl = bControl; }

	// �W�����v�t���O�̐ݒ�
	void SetJumping(const bool& bJumping) { m_bIsJumping = bJumping; }
	// �L�[�{�[�h�g�p�t���O�̐ݒ�
	void SetKeyboard(const bool& bControl) { m_bControlKeyboard = bControl; }
	// �Q�[���p�b�h�ԍ��̐ݒ�
	void SetGamePadNum(const int& nNum) { m_nGamePadNum = nNum; }
	// �Q�[���J�n�t���O�̐ݒ�
	void SetStart(const bool& bStart) { m_bStart = bStart; }

private:
	// �ړ�
	bool Move();
	// �W�����v
	void Jump();
	// �U��
	void Attack();
	// ��e����
	void Damage();
	// ��ԊǗ�
	void State();

	//�����o�ϐ�
private:	
	// ���C�t�̃|�C���^
	CLife *m_pLife;
	// �X�R�A�̃|�C���^
	CScore *m_pScore;
	CLogo *m_pLogo;

	//�ړ���
	D3DXVECTOR3 m_move;
	//�O��̈ʒu
	D3DXVECTOR3 m_posOld;
	//���
	STATE m_state;
	//��ԃJ�E���^�[
	int m_nCntState;
	//�U���J�E���^�[
	int m_nCntAttack;
	//�A�j���[�V�����J�E���^�[
	int m_nCntAnim;
	//�A�j���[�V�����̃p�^�[��No.
	int m_nPatternAnim;
	//�A�j���[�V�����J�ڂ܂ł̍d���J�E���^�[
	int m_nCntAnimMove;
	//���݂̃A�j���[�V����V�ԍ�
	int m_nPatterAnimV;
	//�e�N�X�`���A�j���[�V�����̎��
	ANIMTYPE m_nTexRotType;

	// �v���C���[�̔ԍ�
	int m_nPlayerNum;
	// �g���Q�[���p�b�h�̔ԍ�
	int m_nGamePadNum;

	// �W�����v���Ă��邩�ǂ���
	bool m_bIsJumping;
	//�v���C���[������ł��邩�ǂ���
	bool m_bControl;
	// �L�[�{�[�h�ő��삵�Ă��邩�ǂ���
	bool m_bControlKeyboard;
	//�C�ɓ��������ǂ���
	bool m_bInSea;

	// �U�������ǂ���
	bool m_bAttack;
	// �U�������J�E���^�[
	int m_nAttackCnt;

	// ��e�x�N�g��
	D3DXVECTOR3 m_knockBack;
	// ��e�����p�J�E���^�[
	int m_nDamageCnt;

	//����𔲂��邽�߂̃L�[(�{�^��)���͉�
	int m_nPushButton;

	// �Q�[�����J�n���Ă��邩�ǂ���
	bool m_bStart;
	// ���S�������ǂ���
	bool m_bDie;

	bool m_bReady;
};

#endif	//_PLAYER_H_

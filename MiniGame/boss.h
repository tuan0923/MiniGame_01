//===================================================================
//
//	�G�{�X�̏���[boss.h]
//	Author : �e���A��
//
//===================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "motion.h"

//*******************************************************************
//	�O���錾
//*******************************************************************
class CPlayer;

//*******************************************************************
//	�G�N���X�̒�`
//*******************************************************************
class CBoss : public CMotion
{
public:		//�萔
	// ��
	static const float SIZE_WIDTH;
	// ����
	static const float SIZE_HEIGHT;
	// U���W�̍ő啪����
	static const int DIVISION_U;
	// V���W�̍ő啪����
	static const int DIVISION_V;
private:
	// ����
	static const int LIFE;
	// �U���O�̗\������Ԋu
	static const int RUSH_OPERATION;

public:
	//���
	enum STATE
	{
		STATE_NORMAL = 0,	//�ʏ�
		STATE_DAMAGE,		//�_���[�W���
		STATE_MAX
	};

	//�s���p�^�[��
	enum PATTERN
	{
		PATTERN_ENTRY = 0,	// �o��
		PATTERN_NORMAL,		// �ʏ�
		PATTERN_RUN,		// �ړ�
		PATTERN_SNOWBALL,	// ��ʓ����U��
		PATTERN_POW,		// �n�k�U��
		PATTERN_BARRAGE,	// �e���U��
		PATTERN_DIE,		// ���S
		PATTERN_MAX
	};

	CBoss();
	~CBoss() override;

	//�����o�֐�
	static CBoss *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);		//�C���X�^���X��������

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	bool Collision(D3DXVECTOR3 posStart);
	bool Pattern(D3DXVECTOR3& pos);
	void ChangeSize(D3DXVECTOR2 *pSize, const float& fSize);
	void StateReset();

	PATTERN GetPattern() { return m_pattern; }
	void SetPattern(PATTERN pattern) { m_pattern = pattern; }
	void SetAdd(const float& fAdd) { m_fAdd += fAdd; }

private:
	// �ړ���
	D3DXVECTOR3 m_move;
	// �s���p�^�[��
	PATTERN m_pattern;
	// �s���ω��܂ł̃J�E���^�[
	int8_t m_nCounter;			
	// �ːi�O�̗\������̊Ԋu
	int m_nCountOperation;
	// �ːi�U���A�e���˂̊p�x
	float m_fAttackRot;
	// �傫���̕ύX
	bool m_bSizeChange;
	// �I�u�W�F�N�g�𐶐�������
	int m_nCountObject;

	// �����x
	float m_fAdd;
};

#endif	// _BOSS_H_

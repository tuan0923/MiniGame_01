//===================================================================
//
//	�I�v�V�����e�̏���[bullet_option.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "object2D.h"

//*******************************************************************
//	�e�N���X�̒�`
//*******************************************************************
class CBarrier : public CObject2D
{
private:
	//�T�C�Y(X)
	static const float SIZE_X;
	//�T�C�Y(Y)
	static const float SIZE_Y;
	// �A�j���[�V�����Ԋu
	static const int ANIM_INTERVAL;
	// �A�j���[�V�����ő吔
	static const int MAX_ANIM;
	// U���W�̍ő啪����
	static const int DIVISION_U;
	// V���W�̍ő啪����
	static const int DIVISION_V;

public:
	// �o���A�̍ő勭����
	static const int MAX_NUM = 4;

	// �e�v���C���[
	enum PARENT
	{
		PLAYER_1 = 0,	//1P
		PLAYER_2,		//2P
	};

	enum LEVEL
	{//����(�F�̕ω�)���
		LEVEL_NONE = 0,
		LEVEL_GREEN,	//1�i�K��
		LEVEL_SILVER,	//2�i�K��
		LEVEL_GOLD,		//3�i�K��
		LEVEL_MAX
	};

	CBarrier();
	~CBarrier() override;

	//�����o�֐�
	static CBarrier *Create(const D3DXVECTOR3& pos, const PARENT& parent);		//�C���X�^���X��������
	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̍폜

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetBarrier(LEVEL col);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[LEVEL_MAX];		// �e�N�X�`���̃|�C���^
	float m_fRad;				// �p�x
	LEVEL m_col;				// �F�̎��
	int m_nDamage;				// �_���[�W��
	PARENT m_parent;	// ���L����v���C���[

	// �A�j���[�V�����p�J�E���^�[
	int m_nCntAnim;
	// ���݂̃A�j���[�V�����ԍ�
	int m_nPatternAnim;
	// ���݂̃A�j���[�V����V�ԍ�
	int m_nPatterAnimV;
};

#endif		// _BARRIER_H_

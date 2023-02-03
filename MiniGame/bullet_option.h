//===================================================================
//
//	�I�v�V�����e�̏���[bullet_option.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BULLET_OPTION_H_
#define _BULLET_OPTION_H_

#include "object2D.h"

//*******************************************************************
//	�e�N���X�̒�`
//*******************************************************************
class CBulletOption : public CObject2D
{
private:
	// �I�v�V�����̒��a�T�C�Y
	static const int SIZE = 30;
	// �I�v�V�����̃_���[�W��
	static const int DAMAGE = 5;

public:
	// �I�v�V�����̍ő吶����
	static const int MAX_NUM = 4;

	// �e�v���C���[
	enum PARENT
	{
		PLAYER_1 = 0,	//1P
		PLAYER_2,		//2P
	};

	// �������
	enum LEVEL
	{
		LEVEL_NONE = 0,
		LEVEL_1,		//1�i�K��
		LEVEL_2,		//2�i�K��
		LEVEL_3,		//3�i�K��
	};

	enum EColor
	{//�F�̕ω����
		FADE_NONE = 0,
		FADE_RED,
		FADE_GREEN,
		FADE_BLUE,
	};

	CBulletOption();
	~CBulletOption() override;

	//�����o�֐�
	static CBulletOption *Create(const float& fRot, const PARENT& parent);		//�C���X�^���X��������
	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̍폜

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Attack();
	void SetRad(float fRad) { m_fRad = fRad; }

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture;		// �e�N�X�`���̃|�C���^
	float m_fRad;				// �p�x
	EColor m_col;				// �F�̎��
	PARENT m_parent;			// ���L����v���C���[
	int m_nCounterAttack;		// �U���J�E���^�[
};

#endif		// _BULLET_H_

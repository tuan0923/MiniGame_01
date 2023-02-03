//===================================================================
//
//	�w�i����[bg.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BG_H_
#define _BG_H_

#include "object.h"

//*******************************************************************
// �O���錾
//*******************************************************************
class CObject2D;

//*******************************************************************
//	�w�i�N���X�̒�`
//*******************************************************************
class CBg : public CObject
{
private:
	// ����
	static const int LIFE = 50;
	//�v���C���[�̃T�C�Y(X)
	static const float SIZE_WIDTH;
	//�v���C���[�̃T�C�Y(Y)
	static const float SIZE_HEIGHT;
	//�v���C���[�̊�{�ړ���
	static const float MOVE_DEFAULT;
	// �A�j���[�V�����Ԋu
	static const int ANIM_INTERVAL;
	// �A�j���[�V�����ő吔
	static const int MAX_ANIM;
	// U���W�̍ő啪����
	static const int DIVISION_U;
	// V���W�̍ő啪����
	static const int DIVISION_V;

public:
	// �w�i�̃Z�b�g
	enum ESet
	{
		SET_NONE = 0,
		SET_A,			// ZONE_A
		SET_B,			// ZONE_B
		SET_C,			// ZONE_C
		SET_MAX			// �Z�b�g�̍ő吔
	};

	enum EZone_A
	{//�w�i�̎��
		BG_A_SKY = 0,		// ��
		BG_A_UNDERWATER,	// �C��
		BG_A_SEA,			// �C��
		BG_A_WAVE1,			// �g1
		BG_A_WAVE2,			// �g2
		BG_A_WAVE3,			// �g3
		BG_A_ROCK,			// ��
		BG_A_SETWEED,		// �C��
		BG_A_BOSS,			// �{�X��̔w�i
		BG_A_FLOOR,			// �C���̏�
		BG_A_SETWEED2,		// �C��
		BG_A_FADEBLACK,		// �w�i�t�F�[�h�p
		BG_A_SEA_OTHER,		// �C�̗���(�C������݂��C��)
		BG_A_MAX			// �w�i�̍ő吔
	};

	CBg();
	~CBg() override;

	//�����o�֐�
	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̍폜
	static CBg *Create(ESet set);	//�C���X�^���X��������
	static CObject2D *GetObjectBg(EZone_A index) { return m_apObject2D[index]; }

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[BG_A_MAX];	//�e�N�X�`���̃|�C���^
	static CObject2D *m_apObject2D[BG_A_MAX];			//2D�|���S���ւ̃|�C���^
	ESet m_set;					//�`�悷��w�i(ZONE)
	int m_nCntBgChange;			//���̔w�i���`�悳���܂ł̃J�E���^�[
};

#endif		// _BG_H_

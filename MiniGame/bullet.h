//===================================================================
//
//	�e�̏���[bullet.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "object2D.h"

//*******************************************************************
//	�e�N���X�̒�`
//*******************************************************************
class CBullet : public CObject2D
{
private:
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
	enum EParent
	{//�e�̐�����(���L��)
		PARENT_PLAYER1 = 0,
		PARENT_PLAYER2,
		PARENT_ENEMY,
		PARENT_MAX
	};

	enum EType
	{//�e�̎��
		TYPE_PLAYER_BLUE = 0,
		TYPE_ENEMY_ORANGE,
		TYPE_ENEMY_LASER,
		TYPE_ENEMY_RED,
		TYPE_PLAYER_GREEN,
		TYPE_MAX
	};

	CBullet();
	~CBullet() override;

	//�����o�֐�
	static CBullet *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int& nDamage, const EType type);	//�C���X�^���X��������
	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̍폜

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetParent(EParent parent) { m_parent = parent; }
	bool Collision(D3DXVECTOR3 posStart);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_move;				//�ړ���
	int m_nDamage;					//�e�̃_���[�W
	int m_nCntAnim;					//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;				//�A�j���[�V�����̃p�^�[��No.
	EParent m_parent;				//�e�̐������̎��
	EType m_type;					//�e�̎��
};

#endif		// _BULLET_H_

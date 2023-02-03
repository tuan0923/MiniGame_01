//-------------------------------------------
//
// UI���[ui.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _UI_H_
#define _UI_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "object2D.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CUi : public CObject2D
{
public:
	// �ǂ̃v���C���[��UI��
	enum PARENT
	{
		PLAYER_1 = 0,			// 1P
		PLAYER_2,				// 2P
		PLAYER_1_NOT_ENTRY,		// 1P(�G���g���[���Ă��Ȃ��ꍇ)
		PLAYER_2_NOT_ENTRY,		// 2P
		PLAYER_NONE,			// �ǂ���ł��Ȃ�
	};

	enum TYPE
	{//���
		TYPE_NONE = 0,			// �����Ȃ�
		TYPE_AREA_A,			// �G���AA
		TYPE_PLAYER1,			// �v���C���[1
		TYPE_PLAYER2,			// �v���C���[2
		TYPE_PRESS_ANY_BUTTON,	// �G���g���[�҂�1
		TYPE_TO_START,			// �G���g���[�҂�2
		TYPE_LIFE1,				// �v���C���[1�̎c�@
		TYPE_LIFE2,				// �v���C���[2�̎c�@
		TYPE_BULLET,			// ���C���e
		TYPE_BULLET_OPTION,		// �I�v�V�����e
		TYPE_BARRIER,			// �o���A
		TYPE_OK,				// �G���g���[���
		TYPE_CONTINUE,			// �R���e�B�j���[
		TYPE_MAX
	};

	enum ANIMTYPE
	{//�A�j���[�V�����̎��
		ANIM_NONE = 0,		// �������Ȃ�
		ANIM_FLASHING,		// �_��
	};

	// �R���X�g���N�^
	CUi();
	// �f�X�g���N�^
	~CUi() override;

	// ����
	static CUi* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const TYPE& type, const ANIMTYPE& AnimType, const PARENT& parent);
	// �e�N�X�`���̓ǂݍ���
	static HRESULT Load();
	// �e�N�X�`���̍폜
	static void Unload();

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
	// �A�j���[�V�����̎��
	ANIMTYPE m_AnimType;
	// �j������܂ł̃J�E���^�[
	int m_nCountUninit;
	// �ǂ̃v���C���[��UI��
	PARENT m_parent;
};

#endif		// _UI_H_

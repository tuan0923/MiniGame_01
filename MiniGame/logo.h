//-------------------------------------------
//
// ���S�̏��[logo.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _LOGO_H_
#define _LOGO_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "object2D.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CLogo : public CObject2D
{
public:
	enum LOGOTYPE
	{//���S�̎��
		TYPE_NONE = 0,		// �����Ȃ�
		TYPE_ESCAPE,		// �������N���S
		TYPE_WARNING,		// �{�X�ڋ߃��S
		TYPE_WARNING_SUB,	// �{�X�ڋ߂̐������S
		TYPE_REMINDER,		// ���ӊ��N�W���̃��S
		TYPE_CLEAR,			// �Q�[���N���A�̃��S
		TYPE_BONUS,			// �{�[�i�X�X�R�A�̃��S
		TYPE_GAMEOVER,		// �Q�[���I�[�o�[�̃��S
		TYPE_MAX
	};

	enum ANIMTYPE
	{//�A�j���[�V�����̎��
		ANIM_NONE = 0,		// �������Ȃ�
		ANIM_LENGTHWISE,	// �c�ɍL����
		ANIM_HORIZONTALLY,	// ���ɍL����
		ANIM_FLASHING,		// �_��
		ANIM_MAX
	};

	// �R���X�g���N�^
	CLogo();
	// �f�X�g���N�^
	~CLogo() override;

	// ����
	static CLogo* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const char* name, const int& nCount);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;
	// �j���J�E���^�[�̐ݒ�
	void SetCountUninit(int nCounter) { m_nCountUninit = nCounter; }
	// �j���J�E���^�[�̎擾
	int GetCountUninit() { return m_nCountUninit; }

private:
	// �j������܂ł̃J�E���^�[
	int m_nCountUninit;
};

#endif		// _LOGO_H_

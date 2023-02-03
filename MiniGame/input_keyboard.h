//=============================================================================
//
// �L�[�{�[�h���� [input_keyboard.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include "input.h"

//-----------------------------------------------------------------------------
// �L�[�{�[�h�N���X(�h���N���X)
//-----------------------------------------------------------------------------
class CInputKeyboard : public CInput
{
private:
	static const int MAX_KEY = 256;

public:
	// �L�[���͏��
	enum KEYINFO
	{
		KEYINFO_OK = 0,				// ����
		KEYINFO_UP,					// ��I��
		KEYINFO_DOWN,				// ���I��
		KEYINFO_RIGHT,				// �E�ړ�
		KEYINFO_LEFT,				// ���ړ�
		KEYINFO_PAUSE,				// �|�[�Y
		KEYINFO_JUMP,				// �W�����v
		KEYINFO_ATTACK,				// �U��
		KEYINFO_1,					// 1
		KEYINFO_2,					// 2
		KEYINFO_3,					// 3
		KEYINFO_4,					// 4
		KEYINFO_5,					// 5
		KEYINFO_6,					// 6

		// �e�X�g�p
		KEYINFO_Q,
		KEYINFO_E,
		KEYINFO_Z,
		KEYINFO_C,
		KEYINFO_R,
		KEYINFO_F,
		KEYINFO_T,
		KEYINFO_G,
		KEYINFO_Y,
		KEYINFO_H,
		KEYINFO_MAX,
	};

	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(int nKey) { return (m_aKeyState[m_aKeyInfo[nKey]] & 0x80) ? true : false; }
	bool GetTrigger(int nKey){ return (m_aKeyStateTrigger[m_aKeyInfo[nKey]] & 0x80) ? true : false; }
	bool GetReleace(int nKey){ return (m_aKeyStateReleace[m_aKeyInfo[nKey]] & 0x80) ? true : false; }

private:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
	BYTE m_aKeyStateReleace[MAX_KEY];

	int m_aKeyInfo[KEYINFO_MAX] =
	{
		DIK_RETURN,		// ����
		DIK_W,			// ��I��
		DIK_S,			// ���I�� 
		DIK_D,			// �E�ړ�
		DIK_A,			// ���ړ�
		DIK_P,			// �|�[�Y
		DIK_SPACE,		// �W�����v
		DIK_L,			// �U��
		DIK_1,			// 1
		DIK_2,			// 2
		DIK_3,			// 3
		DIK_4,			// 4
		DIK_5,			// 5
		DIK_6,			// 6

		// �e�X�g�p
		DIK_Q,
		DIK_E,
		DIK_Z,
		DIK_C,
		DIK_R,
		DIK_F,
		DIK_T,
		DIK_G,
		DIK_Y,
		DIK_H
	};
};
#endif
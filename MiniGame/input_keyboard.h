//=============================================================================
//
// キーボード処理 [input_keyboard.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include "input.h"

//-----------------------------------------------------------------------------
// キーボードクラス(派生クラス)
//-----------------------------------------------------------------------------
class CInputKeyboard : public CInput
{
private:
	static const int MAX_KEY = 256;

public:
	// キー入力情報
	enum KEYINFO
	{
		KEYINFO_OK = 0,				// 決定
		KEYINFO_UP,					// 上選択
		KEYINFO_DOWN,				// 下選択
		KEYINFO_RIGHT,				// 右移動
		KEYINFO_LEFT,				// 左移動
		KEYINFO_PAUSE,				// ポーズ
		KEYINFO_JUMP,				// ジャンプ
		KEYINFO_ATTACK,				// 攻撃
		KEYINFO_1,					// 1
		KEYINFO_2,					// 2
		KEYINFO_3,					// 3
		KEYINFO_4,					// 4
		KEYINFO_5,					// 5
		KEYINFO_6,					// 6

		// テスト用
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
		DIK_RETURN,		// 決定
		DIK_W,			// 上選択
		DIK_S,			// 下選択 
		DIK_D,			// 右移動
		DIK_A,			// 左移動
		DIK_P,			// ポーズ
		DIK_SPACE,		// ジャンプ
		DIK_L,			// 攻撃
		DIK_1,			// 1
		DIK_2,			// 2
		DIK_3,			// 3
		DIK_4,			// 4
		DIK_5,			// 5
		DIK_6,			// 6

		// テスト用
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
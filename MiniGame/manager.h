//=============================================================================
//
// マネージャー処理[manager.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "player.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;

class CTitle;
class CGame;
class CResult;

class CSound;				// サウンドクラス
class CFade;				// フェードクラス
class CInputKeyboard;		// キーボードクラス
class CInputJoypad;			// ジョイパッドクラス
class CInputMouse;			// マウスクラス

// 追加
class CTexture;				// テクスチャクラス
class CXFile;				// Xファイルクラス
class CXFileMotion;			// モデルモーションクラス
class CSetModel;			// モデル配置クラス
class CDebugProc;			// デバック表示クラス

//*****************************************************************************
// クラス定義(基本クラス)
//*****************************************************************************
class CManager
{
public:
	// モードの種類
	enum MODE
	{
		MODE_TITLE = 0,		// タイトル
		MODE_TUTORIAL,		// チュートリアル
		MODE_GAME,			// ゲーム
		MODE_RESULT,		// リザルト
		MODE_MAX,
	};

	// プレイヤーの参加情報
	struct SEntryInfo
	{
		// エントリーしているかどうか
		bool bEntry;
		// ゲームパッドの番号
		int nGamePadNum;
		// キーボードで参加しているかどうか
		bool bEntryKeyboard;
	};

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	// 全てのシーンを破棄
	void UninitSceneAll();
	
	void SetMode(MODE mode);
	MODE GetMode() { return m_mode; }
	
	CRenderer *GetRenderer() { return m_pRenderer; }

	CTitle *GetTitle() { return m_pTitle; }
	CGame *GetGame() { return m_pGame; }
	CResult *GetResult() { return m_pResult; }

	CFade *GetFade() { return m_pFade; }
	CSound *GetSound() { return m_pSound; }
	CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }
	CInputJoypad *GetInputJoypad() { return m_pInputJoypad; }
	CInputMouse *GetInputMouse() { return m_pInputMouse; }

	// 追加
	CTexture *GetTexture() { return m_pTexture; }
	CXFile *GetXFile() { return m_pXFile; }
	CXFileMotion *GetMotion() { return m_pMotion; }
	CSetModel *GetModelSet() { return m_pSetModel; }
	CDebugProc *GetDebugProc() { return m_pDebugProc; }
	/**/
	
	bool GetPause() { return m_bPause; }
	void SetPause(bool bPause) { m_bPause = bPause; }

	static CManager *GetManager() { return m_pManager; }
	static void SetManager(CManager *pManager) { m_pManager = pManager; }

	// 全てのプレイヤーが参加しているかどうか
	bool GetEntryAll();
	// プレイヤー参加情報の設定
	void SetEntryAll(SEntryInfo *pEntry);

	void ResetEntry();

	// プレイヤー参加情報の取得
	SEntryInfo *GetEntry() { return &m_EntryInfo[0]; }

private:
	static CManager *m_pManager;		// マネージャーのポインタ

	CTitle *m_pTitle;					// タイトル情報のポインタ
	CGame *m_pGame;						// ゲーム情報のポインタ
	CResult *m_pResult;					// リザルト情報のポインタ

	CRenderer *m_pRenderer;				// レンダラー情報のポインタ
	CInputKeyboard *m_pInputKeyboard;	// キーボード情報のポインタ
	CInputJoypad *m_pInputJoypad;		// ジョイパッド情報のポインタ
	CInputMouse *m_pInputMouse;			// マウス情報のポインタ
	CSound *m_pSound;					// サウンド情報のポインタ
	CFade *m_pFade;						// 画面フェード情報のポインタ

	// 追加
	CTexture *m_pTexture;				// テクスチャ情報のポインタ
	CXFile *m_pXFile;					// Xファイル情報のポインタ
	CXFileMotion *m_pMotion;			// モデルモーション情報のポインタ
	CSetModel *m_pSetModel;				// モデル配置情報のポインタ
	CDebugProc *m_pDebugProc;			// デバック表示情報のポインタ
	/**/

	MODE m_mode;						// モード情報
	bool m_bPause;						// ポーズするかどうか

	int8_t m_nCounter;

	// 参加しているかどうか
	SEntryInfo m_EntryInfo[CPlayer::PLAYER_MAX];
};

#endif // _MANAGER_

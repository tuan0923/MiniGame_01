//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "renderer.h"
#include "player.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CPlayer;
class CCamera;
class CLogo;
class CLogoFlash;

//-----------------------------------------------------------------------------
// タイトル画面クラス
//-----------------------------------------------------------------------------
class CTitle
{
public:
	enum TITLE_OBJ
	{//背景の種類
		BG_SKY = 0,		// 背景の空
		LOGO_PLAYER,	// プレイヤーロゴ
		LOGO_TITLE,		// タイトルロゴ
		LOGO_PRESS,		// PRESSロゴ
		BG_FADE,		// 画面を薄暗くする用
		LOGO_TUTORIAL,	// チュートリアル
		LOGO_SHADOW,	// プレイヤーロゴ(黒)
		OBJ_MAX			// 背景の最大数
	};

public:
	CTitle();
	~CTitle();

	//メンバ関数
	HRESULT Init();
	void Uninit();
	void Update();

	void LogoMove();
	void Ready();

	// プレイヤー情報
	CPlayer* GetPlayer(int nNum) { return m_pPlayer[nNum]; }
	//カメラ情報
	CCamera* GetCamera() { return m_pCamera; }
	//タイトルロゴ情報
	CLogo* GetLogo() { return m_pLogo; }
	//タイトルロゴ情報
	int GetEntry() { return m_nEntryNum; }

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[OBJ_MAX];		//テクスチャのポインタ
	CPlayer* m_pPlayer[CPlayer::PLAYER_MAX];
	CCamera* m_pCamera;
	CObject2D *m_apObject2D[OBJ_MAX - 1];
	CLogo* m_pLogo;
	CLogoFlash* m_pLogoFlash;

	bool m_bPush;
	// キーボードで参加したかどうか
	bool m_bEntryKeyboard;
	// 参加番号
	int m_nEntryNum;
	int m_nCounter;
	D3DXVECTOR3 m_move;		// 移動量

	bool m_bLogoMove;
	bool m_bPlay;

	bool m_PlayerEnt[CPlayer::PLAYER_MAX];

	bool m_bUi;
};

#endif		// _TITLE_H_

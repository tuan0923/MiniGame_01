//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA, SHUGO KURODA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>					// サウンド再生に必要

//-----------------------------------------------------------------------------
// サウンドクラス(基本クラス)
//-----------------------------------------------------------------------------
class CSound
{
public:
	CSound();
	~CSound();

	// サウンドファイル
	typedef enum
	{
		// BGM音
		SOUND_LABEL_TITLE = 0,			// タイトルBGM
		SOUND_LABEL_GAME,				// ゲームBGM
		// ゲームSE音
		SOUND_LABEL_SE_ATTACK,			// 攻撃
		SOUND_LABEL_SE_DAMAGE,			// 被弾
		SOUND_LABEL_SE_DIE,				// 死亡
		SOUND_LABEL_SE_JUMP,			// ジャンプ
		SOUND_LABEL_SE_ENTRY,			// プレイヤー参加
		SOUND_LABEL_SE_PAUSE,			// ポーズ画面を開く
		SOUND_LABEL_SE_BOSS,			// 猛獣の咆哮
		SOUND_LABEL_SE_WIN,				// 勝利ファンファーレ
		SOUND_LABEL_SE_COUNT,			// カウントダウン音
		SOUND_LABEL_SE_START,			// スタート
		SOUND_LABEL_SE_MENU_OK,			// 決定
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit();
	static HRESULT Play(SOUND_LABEL label);
	static void Stop(SOUND_LABEL label);
	static void Stop();

private:
	// パラメータ構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	static IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// オーディオデータサイズ

	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif

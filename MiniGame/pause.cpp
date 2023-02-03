//=============================================================================
//
// ポーズ画面情報 [pause.cpp]
// Author:SHUGO KURODA
//
//=============================================================================
#include "pause.h"
#include "game.h"
#include "fade.h"
#include "input_keyboard.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "input_joypad.h"

// 追加
#include "texture.h"

//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------
CObject2D *CPause::m_apObject2D[TYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause() :m_bPause(false), m_nPauseSelect(0), m_bWait(false), m_nNumPlayer(0)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}

	// オブジェクトタイプの設定
	SetType(OBJ_PAUSE);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CPause *CPause::Create(int nNumPlayer)
{
	// ポインタ変数の生成
	CPause *pPause = new CPause;

	// NULLチェック
	if (pPause != nullptr)
	{
		// ポーズメニューを開いたプレイヤー
		pPause->m_nNumPlayer = nNumPlayer;

		// 初期化処理
		pPause->Init();
	}

	return pPause;
}

//=============================================================================
// ポーズの初期化処理
//=============================================================================
HRESULT CPause::Init()
{
	SetPause();

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{// 生成
		m_apObject2D[nCnt] = new CObject2D;
		// オブジェクトタイプの設定
		m_apObject2D[nCnt]->SetType(OBJ_PAUSE_MENU);
	}
	m_apObject2D[TYPE_FRAME]->SetType(OBJ_PAUSE);

	// スクリーンサイズの保存
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	// ポーズ番号
	m_nPauseSelect = TYPE_RESTART;

	// テクスチャポインタの取得
	CTexture *pTex = CManager::GetManager()->GetTexture();

	// ポーズ画面枠
	m_apObject2D[TYPE_FRAME]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[TYPE_FRAME]->SetSize(D3DXVECTOR2(700.0f, 700.0f));
	m_apObject2D[TYPE_FRAME]->BindTexture(pTex->GetTexture("TEX_TYPE_PAUSE_FRAME"));
	//// 再開
	//m_apObject2D[TYPE_RESUME]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, 200.0f, 0.0f));
	//m_apObject2D[TYPE_RESUME]->SetSize(D3DXVECTOR2(ScreenSize.x / 2, 80.0f));
	// やり直し
	m_apObject2D[TYPE_RESTART]->SetPosition(D3DXVECTOR3(450.0f, ScreenSize.y / 2, 0.0f));
	m_apObject2D[TYPE_RESTART]->SetSize(D3DXVECTOR2(300.0f, 300.0f));
	m_apObject2D[TYPE_RESTART]->BindTexture(pTex->GetTexture("TEX_TYPE_PAUSE_RETURN"));
	// タイトルに戻る
	m_apObject2D[TYPE_EXIT]->SetPosition(D3DXVECTOR3(800.0f, ScreenSize.y / 2, 0.0f));
	m_apObject2D[TYPE_EXIT]->SetSize(D3DXVECTOR2(300.0f, 300.0f));
	m_apObject2D[TYPE_EXIT]->BindTexture(pTex->GetTexture("TEX_TYPE_PAUSE_END"));
	// 選択カーソル
	m_apObject2D[TYPE_SELECTOR]->SetPosition(D3DXVECTOR3(450.0f, ScreenSize.y / 2, 0.0f));
	m_apObject2D[TYPE_SELECTOR]->SetSize(D3DXVECTOR2(450.0f, 450.0f));
	m_apObject2D[TYPE_SELECTOR]->BindTexture(pTex->GetTexture("TEX_TYPE_PAUSE_CURSOR"));

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{// 初期化とテクスチャの設定
		m_apObject2D[nCnt]->Init();
	}

	m_apObject2D[TYPE_SELECTOR]->SetColor(D3DXCOLOR(0.0f, 0.4f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// ポーズの終了処理
//=============================================================================
void CPause::Uninit()
{
	// ポーズ状態をfalseにする
	CManager::GetManager()->SetPause(false);

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}

	// オブジェクト破棄
	Release();
}

//=============================================================================
// ポーズの更新処理
//=============================================================================
void CPause::Update()
{
	// 選択カーソルの角度取得
	float fRot = m_apObject2D[TYPE_SELECTOR]->GetRot();
	// 角度加算
	fRot += 0.01f;
	// 角度の設定
	m_apObject2D[TYPE_SELECTOR]->SetRot(fRot);

	if (m_bPause == true)
	{
		// キーボード情報の取得
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
		// ゲームパッド情報の取得
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_LEFT) == true 
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_LEFT, 0) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_LEFT, 1) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_LEFT, 2) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_LEFT, 3) == true)
		{
			// 現在選択されている項目の色を元に戻す
			m_apObject2D[m_nPauseSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// 上にいくとき番号を減らす
			m_nPauseSelect--;

			// ポーズ項目の最上部を超えたとき
			if (m_nPauseSelect < TYPE_RESTART)
			{
				m_nPauseSelect = TYPE_EXIT;
			}

			// 選択されているポーズ項目の位置を取得
			D3DXVECTOR3 pos = m_apObject2D[m_nPauseSelect]->GetPosition();
			// 選択カーソルの位置設定
			m_apObject2D[TYPE_SELECTOR]->SetPosition(pos);

			// 効果音
			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);
		}
		else if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_RIGHT) 
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_RIGHT, 0) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_RIGHT, 1) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_RIGHT, 2) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_RIGHT, 3) == true)
		{
			// 現在選択されている項目の色を元に戻す
			m_apObject2D[m_nPauseSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// 下にいくとき番号を増やす
			m_nPauseSelect++;

			// ポーズ項目の最下部を超えたとき
			if (m_nPauseSelect > TYPE_EXIT)
			{
				m_nPauseSelect = TYPE_RESTART;
			}

			// 選択されているポーズ項目の位置を取得
			D3DXVECTOR3 pos = m_apObject2D[m_nPauseSelect]->GetPosition();
			// 選択カーソルの位置設定
			m_apObject2D[TYPE_SELECTOR]->SetPosition(pos);

			// 効果音
			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);
		}

		// 現在選択されている項目は色を黄色に設定
		m_apObject2D[m_nPauseSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

		if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_OK) 
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, 0) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, 1) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, 2) == true
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, 3) == true)
		{
			// 選択されているUIを参照し、どの処理をするか決定
			switch (m_nPauseSelect)
			{
			//	// 再開ボタン
			//case TYPE_RESUME:
			//	// ポーズを閉じる
			//	SetPause();
			//	Uninit();
			//	return;
				// リトライボタン
			case TYPE_RESTART:
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME);
				Uninit();
				return;
				// 終了ボタン
			case TYPE_EXIT:
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
				Uninit();
				return;
			default:
				break;
			}
		}

		// ポーズ画面を終える
		if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_PAUSE) ||
			pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, m_nNumPlayer))
		{
			if (m_bWait == true)
			{
				SetPause();
				Uninit();
				return;
			}
		}

		// 頂点座標の設定
		m_apObject2D[TYPE_SELECTOR]->SetVertex();

		m_bWait = true;
	}
}

//=============================================================================
// ポーズの描画処理
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// ポーズの処理
//=============================================================================
void CPause::SetPause()
{
	m_bPause = m_bPause ? false : true;

	if (m_bPause == true)
	{
		CSound::Play(CSound::SOUND_LABEL_SE_PAUSE);
	}
	else if (m_bPause == false)
	{
		CSound::Play(CSound::SOUND_LABEL_SE_PAUSE);
	}

	CManager::GetManager()->SetPause(m_bPause);
}

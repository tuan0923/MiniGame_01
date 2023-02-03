//=============================================================================
//
// ランク処理 [rank.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "rank.h"

#include "manager.h"
#include "renderer.h"
#include "load.h"

#include "score.h"
#include "input_joypad.h"
#include "input_keyboard.h"
#include "sound.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define SCORE_POS				(D3DXVECTOR3(70.0f,CRenderer::SCREEN_HEIGHT - 30.0f,0.0f))
#define PLAYER_SCORE_POS		(D3DXVECTOR3(220.0f,CRenderer::SCREEN_HEIGHT - 50.0f,0.0f))
#define SCORE_SIZE				(D3DXVECTOR2(30.0f,30.0f))
#define PLAYER_SCORE_SIZE		(D3DXVECTOR2(50.0f,60.0f))
#define SCORE_SPACE				(20)
#define PLAYER_SCORE_SPACE		(40)

//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------

//=============================================================================
// CRankのコンストラクタ
//=============================================================================
CRank::CRank() :m_pScore{ nullptr }
{
	SetType(CObject::OBJ_UI);
}

//=============================================================================
// CRankのデストラクタ
//=============================================================================
CRank::~CRank()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CRank *CRank::Create()
{
	// ポインタ変数の生成
	CRank *pRank = new CRank;

	// 初期化処理
	pRank->Init();

	return pRank;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRank::Init()
{
	m_pScore = CScore::Create(SCORE_POS, SCORE_SIZE, SCORE_SPACE);

	//// プレイヤースコアの生成
	//for (int nCnt = 0; nCnt < MAX_PLAYER_SCORE; nCnt++)
	//{
	//	// プレイヤーENTRY情報の取得
	//	bool bEntry = CManager::GetManager()->GetEntry(nCnt);

	//	// エントリーしていれば
	//	if (bEntry == true)
	//	{// プレイヤースコア生成
	//		m_pScore[nCnt + MAX_RANKING] = CScore::Create(D3DXVECTOR3(PLAYER_SCORE_POS.x + (nCnt * 650.0f), PLAYER_SCORE_POS.y, SCORE_POS.z),
	//			PLAYER_SCORE_SIZE, PLAYER_SCORE_SPACE);

	//		// スコアの設定
	//		m_aScore[nCnt + MAX_RANKING] = m_nScorePlayer[nCnt];

	//		// UIの生成
	//		m_apObject2D[nCnt] = new CObject2D;
	//		m_apObject2D[nCnt]->SetType(EObject::OBJ_UI);
	//		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(100.0f + (nCnt * 650.0f), CRenderer::SCREEN_HEIGHT - 50.0f, 0.0f));
	//		m_apObject2D[nCnt]->SetSize(D3DXVECTOR2(200.0f, 100.0f));
	//		m_apObject2D[nCnt]->Init();
	//		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	//	}
	//}

	// テキストからスコアをロード
	m_pScore->Set(LoadSpace::LoadScore());

	// Top3のスコア色を設定
	m_pScore->SetColor(D3DXCOLOR(0.1f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRank::Uninit()
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRank::Update()
{
	//// テクスチャの頂点座標を変更
	//m_apObject2D[TYPE_BG]->SetAnimBgLeftUp(1, 400, true);

	//// キーボード情報の取得
	//CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	//// ゲームパッド情報の取得
	//CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	//for (int nCnt = CInputKeyboard::KEYINFO_OK; nCnt < CInputKeyboard::KEYINFO_MAX; nCnt++)
	//{
	//	// キーボードのENTRY処理
	//	if (pKeyboard->GetTrigger(nCnt))
	//	{
	//		for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
	//		{
	//			if (m_pScore[nCnt] != nullptr)
	//			{// スコア設定
	//				if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
	//				{
	//					m_pScore[nCnt]->Set(m_aScore[nCnt]);
	//				}
	//			}
	//		}

	//		if (m_bNextMode == true)
	//		{
	//			// 決定音
	//			CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

	//			// モードの設定
	//			CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);
	//			return;
	//		}

	//		m_bNextMode = true;
	//		break;
	//	}
	//}

	//// プレイヤーのエントリー処理
	//for (int nCntController = 0; nCntController < CPlayer::PLAYER_MAX; nCntController++)
	//{
	//	for (int nCnt = CInputJoypad::JOYKEY_UP; nCnt < CInputJoypad::JOYKEY_MAX; nCnt++)
	//	{
	//		if (pJoypad->GetTrigger((CInputJoypad::JOYKEY)nCnt, nCntController))
	//		{
	//			// 決定音
	//			CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

	//			for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
	//			{
	//				if (m_pScore[nCnt] != nullptr)
	//				{// スコア設定
	//					if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
	//					{
	//						m_pScore[nCnt]->Set(m_aScore[nCnt]);
	//					}
	//				}
	//			}

	//			if (m_bNextMode == true)
	//			{
	//				// モードの設定
	//				CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);
	//				return;
	//			}

	//			m_bNextMode = true;
	//			break;
	//		}
	//	}
	//}

	//// スコア情報を格納
	//for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
	//{
	//	if (m_pScore[nCnt] != nullptr)
	//	{// 毎秒スコア加算
	//		if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
	//		{
	//			m_pScore[nCnt]->Add(200);
	//		}
	//		else if (m_nScorePlayer[0] == m_pScore[nCnt]->GetScore() ||
	//			m_nScorePlayer[1] == m_pScore[nCnt]->GetScore())
	//		{
	//			// PRESSロゴの色を取得
	//			D3DXCOLOR col = m_pScore[nCnt]->GetColor();

	//			// PRESSロゴを点滅させる
	//			if (m_bMyScoreFade[nCnt] == false)
	//			{
	//				// a値を加算
	//				col.a += 0.02f;
	//				// a値の加算が終わったら
	//				if (col.a >= 1.0f)
	//				{// a値の減算を始める
	//					m_bMyScoreFade[nCnt] = true;
	//				}
	//			}
	//			else if (m_bMyScoreFade[nCnt] == true)
	//			{
	//				// a値を減算
	//				col.a -= 0.02f;
	//				// a値の減算が終わったら
	//				if (col.a <= 0.0f)
	//				{// a値の加算を始める
	//					m_bMyScoreFade[nCnt] = false;
	//				}
	//			}

	//			// 色の設定
	//			m_pScore[nCnt]->SetColor(col);
	//		}
	//	}
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void CRank::Draw()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CRank::Save(int nHiScore)
{
	m_pScore->Set(nHiScore);

	// テキストにスコアをセーブ
	LoadSpace::SaveScore(nHiScore);
}

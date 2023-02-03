//===============================================================================================
//
// ゲーム画面処理 [title.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "title.h"
#include "sound.h"

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "object.h"
#include "object2D.h"

#include "library.h"
#include "fade.h"

#include "cloud.h"
#include "fade_scene.h"
#include "library.h"
#include "ui.h"

// 追加
#include "object3D.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "boss.h"
#include "item.h"
#include "model_obstacle.h"
#include "model_manager.h"
#include "mesh_sphere.h"
#include "logo.h"
#include "logo_flash.h"
//#include "avalanche.h"

#include "set_model.h"

#include "motion.h"

#include "tutorial.h"

//-----------------------------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------
// テクスチャのポインタ
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[OBJ_MAX] = { nullptr };

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CTitle::CTitle() :m_bPush(false), m_move(0.0f, 0.0f, 0.0f), m_nCounter(0), m_bPlay(false), m_PlayerEnt{false},
m_pPlayer{}, m_pCamera(), m_bEntryKeyboard(false), m_nEntryNum(0), m_pLogo{ nullptr }, m_bLogoMove(false), m_bUi(false)
{
	for (int nCnt = 0; nCnt < OBJ_MAX - 1; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CTitle::~CTitle()
{
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CTitle::Init()
{
	// 決定音
	CSound::Play(CSound::SOUND_LABEL_TITLE);

	// チュートリアルボタン
	CTutorial::Create(D3DXVECTOR3(0.0f, 2.0f, -50.0f));

	// カメラ生成
	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 60.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),50.0f);

	// 球体メッシュの配置
	CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2(3000.0f, 3000.0f), 10, 10, "TEX_TYPE_GAME_BG");

	// 板ポリ生成
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(2000.0f, 2000.0f));

	// ライト生成
	CLight::Create(D3DXVECTOR3(-0.2f, -0.8f, 0.4f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create(D3DXVECTOR3(0.2f, -0.1f, -0.8f), D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
	//CLight::Create(D3DXVECTOR3(0.2f, 1.0f, -0.0f), D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));

	// エントリー情報のリセット
	CManager::GetManager()->ResetEntry();
	// プレイヤー参加情報の取得
	CManager::SEntryInfo *pEntry = CManager::GetManager()->GetEntry();

	//// プレイヤー生成
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// 現在の番号が参加しているなら
	//	if (pEntry[nCntPlayer].bEntry == true)
	//	{
	//		// キーボードで参加しているなら
	//		if (pEntry[nCntPlayer].bEntryKeyboard == true)
	//		{
	//			// プレイヤー生成
	//			m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "MODEL_PINGU", nCntPlayer);
	//			m_pPlayer[nCntPlayer]->SetKeyboard(pEntry[nCntPlayer].bEntryKeyboard);

	//			// エントリー可能数が上限を超えるまで
	//			if (m_nEntryNum < CPlayer::PLAYER_MAX)
	//			{// エントリー番号の加算
	//				m_nEntryNum++;
	//			}
	//		}
	//		else
	//		{
	//			// プレイヤー生成
	//			m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "MODEL_PINGU", nCntPlayer);
	//			m_pPlayer[nCntPlayer]->SetGamePadNum(pEntry[nCntPlayer].nGamePadNum);

	//			// エントリー可能数が上限を超えるまで
	//			if (m_nEntryNum < CPlayer::PLAYER_MAX)
	//			{// エントリー番号の加算
	//				m_nEntryNum++;
	//			}
	//		}
	//	}
	//}
	
	// モデルの配置
	CManager::GetManager()->GetModelSet()->LoadModel("MODEL_TITLE");

	// タイトルロゴの生成
	m_pLogo = CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, -250.0f, 0.0f),
		D3DXVECTOR2(CRenderer::SCREEN_WIDTH - 300.0f, 400.0f), "TEX_TYPE_LOGO_TITLE", -1);

	//// テクスチャのロード
	//CTitle::Load();
	//// 雲
	//CCloud::Load();

	//// スクリーンサイズの保存
	//D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	//for (int nCnt = 0; nCnt < OBJ_MAX - 1; nCnt++)
	//{// 生成
	//	m_apObject2D[nCnt] = new CObject2D;
	//}

	//// 空
	//m_apObject2D[BG_SKY]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, -ScreenSize.y / 2, 0.0f));
	//m_apObject2D[BG_SKY]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y * 3));
	//// タイトルロゴ
	//m_apObject2D[LOGO_TITLE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y - 450.0f, 0.0f));
	//m_apObject2D[LOGO_TITLE]->SetSize(D3DXVECTOR2(ScreenSize.x - 550.0f, ScreenSize.y / 2.5f));
	//// プレイヤーロゴ
	//m_apObject2D[LOGO_PLAYER]->SetPosition(D3DXVECTOR3(-ScreenSize.x, 160.0f, 0.0f));
	//m_apObject2D[LOGO_PLAYER]->SetSize(D3DXVECTOR2(300.0f, 150.0f));
	//// Pressロゴ
	//m_apObject2D[LOGO_PRESS]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y - 150.0f, 0.0f));
	//m_apObject2D[LOGO_PRESS]->SetSize(D3DXVECTOR2(ScreenSize.x - 550.0f, 90.0f));
	//// フェード
	//m_apObject2D[BG_FADE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	//m_apObject2D[BG_FADE]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	//// チュートリアル
	//m_apObject2D[LOGO_TUTORIAL]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	//m_apObject2D[LOGO_TUTORIAL]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));

	//for (int nCnt = 0; nCnt < OBJ_MAX - 1; nCnt++)
	//{// 初期化とテクスチャの設定
	//	m_apObject2D[nCnt]->Init();
	//	m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	//}

	////背景とプレイヤーロゴ以外を前に描画する(タイプを設定する)
	//for (int nCnt = LOGO_TITLE; nCnt < OBJ_MAX - 1; nCnt++)
	//{
	//	m_apObject2D[nCnt]->SetObjType(CObject::OBJ_TITLE);
	//}
	////プレイヤーロゴを背景の次に描画する
	//m_apObject2D[LOGO_PLAYER]->SetObjType(CObject::OBJ_TITLE_LOGO);
	//m_apObject2D[BG_FADE]->SetObjType(CObject::OBJ_BLACK);
	//m_apObject2D[LOGO_TUTORIAL]->SetObjType(CObject::OBJ_LOGO);

	////タイトルとPressロゴを透明にする
	//m_apObject2D[LOGO_TITLE]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//m_apObject2D[LOGO_PRESS]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//m_apObject2D[BG_FADE]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	//m_apObject2D[LOGO_TUTORIAL]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//// 雲を複数、初期配置する
	//for (int nCntCloud = 0; nCntCloud < 25; nCntCloud++)
	//{
	//	// 位置を設定
	//	D3DXVECTOR3 pos;
	//	pos.x = (float)GetRandNum(CRenderer::SCREEN_WIDTH, 0);
	//	pos.y = (float)GetRandNum(CRenderer::SCREEN_HEIGHT - 300, CRenderer::SCREEN_HEIGHT * -4);
	//	pos.z = 0.0f;

	//	// 雲の生成
	//	CCloud::Create(pos);
	//}

	//// タイトルBGM
	//CSound::Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CTitle::Uninit()
{
	// ポインタの破棄
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt] = nullptr;
		}
	}

	// タイトルBGM
	CSound::Stop();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CTitle::Update()
{
	//if (GetEntryAll() == false)
	//{

	//}

	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	// ジョイパッド情報の取得
	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	// プレイヤー参加情報の取得
	CManager::SEntryInfo *pEntry = CManager::GetManager()->GetEntry();

	// プレイヤー生成
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		// 現在の番号が参加していないなら
		if (pEntry[m_nEntryNum].bEntry == false)
		{
			if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, nCntPlayer) == true)
			{// スタートボタン押下
				if (m_PlayerEnt[nCntPlayer] == false)
				{
					m_pPlayer[m_nEntryNum] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "MODEL_PINGU", m_nEntryNum);
					m_pPlayer[m_nEntryNum]->SetGamePadNum(nCntPlayer);
					pEntry[m_nEntryNum].nGamePadNum = nCntPlayer;
					pEntry[m_nEntryNum].bEntry = true;
					m_PlayerEnt[nCntPlayer] = true;

					// エントリー可能数が上限を超えるまで
					if (m_nEntryNum < CPlayer::PLAYER_MAX)
					{// エントリー番号の加算
						m_nEntryNum++;
					}

					if (m_pLogo != nullptr)
					{
						m_pLogo->Uninit();
						m_pLogo = nullptr;
						m_bLogoMove = true;
					}

					if (m_pLogoFlash != nullptr)
					{
						m_pLogoFlash->Uninit();
						m_pLogoFlash = nullptr;
					}

					break;
				}
			}
			if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_OK) == true && m_bEntryKeyboard == false)
			{// エンターキー押下 && キーボードで参加していなければ
				m_pPlayer[m_nEntryNum] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "MODEL_PINGU", m_nEntryNum);
				m_pPlayer[m_nEntryNum]->SetKeyboard(true);
				m_bEntryKeyboard = true;
				pEntry[m_nEntryNum].bEntryKeyboard = true;
				pEntry[m_nEntryNum].bEntry = true;
				
				// エントリー可能数が上限を超えるまで
				if (m_nEntryNum < CPlayer::PLAYER_MAX)
				{// エントリー番号の加算
					m_nEntryNum++;
				}

				if (m_pLogo != nullptr)
				{
					m_pLogo->Uninit();
					m_pLogo = nullptr;
					m_bLogoMove = true;
				}

				if (m_pLogoFlash != nullptr)
				{
					m_pLogoFlash->Uninit();
					m_pLogoFlash = nullptr;
				}

				break;
			}
		}

		//// ゲーム開始の繰り返し防止
		//if (m_bPush == false)
		//{
		//	//キーを押されたら
		//	if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_1) == true)
		//	{
		//		// 決定音
		//		CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

		//		// モードの設定
		//		CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);
		//		m_bPush = true;

		//		return;
		//	}
		//}
	}

	if (m_bUi == false)
	{
		if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_OK) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, 0))
		{
			CLogo::Create(D3DXVECTOR3(150.0f, CRenderer::SCREEN_HEIGHT - 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_1", -1);
			CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 110.0f, CRenderer::SCREEN_HEIGHT - 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_2", -1);
			m_bUi = true;
		}
	}

	if (m_pLogo == nullptr)
	{
		// 準備
		Ready();
	}
	// タイトルの動き
	LogoMove();

	//m_nCounter++;
}

void CTitle::LogoMove()
{
	if (m_bLogoMove == false)
	{
		// 位置取得
		D3DXVECTOR3 posLogo = m_pLogo->GetPosition();

		if (posLogo.y >= 250.0f)
		{
			m_bLogoMove = true;

			m_pLogoFlash = CLogoFlash::Create(D3DXVECTOR2(CRenderer::SCREEN_WIDTH / 3, 80.0f), "TEX_TYPE_LOGO_TITLEPUSH", -1);
		}
		else
		{
			posLogo.y += 3.0f;
		}

		m_pLogo->SetPosition(posLogo);
		m_pLogo->SetVertex();
	}
}

void CTitle::Ready()
{
	if (m_bPlay == false)
	{
		// プレイヤーの死亡数
		int nNumReady = 0;

		// プレイヤー生成
		for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
		{
			// 現在のプレイヤーが参加しているなら
			if (m_pPlayer[nCntPlayer] != nullptr)
			{
				// 死亡していたら
				if (m_pPlayer[nCntPlayer]->GetReady() == true)
				{// プレイヤーの死亡数を加算
					nNumReady++;
				}
			}
			else
			{// プレイヤーの死亡数を加算
				nNumReady++;
			}
		}

		// プレイヤーが全員死亡していたら
		if (CPlayer::PLAYER_MAX <= nNumReady)
		{
			// ゲーム終了フラグを立てる
			m_bPlay = true;

			// 決定音
			CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

			// モードの設定
			CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);
		}
	}
}

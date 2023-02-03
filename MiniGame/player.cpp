//=============================================================================
//
//	プレイヤー処理[player.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"
#include "renderer.h"

#include "library.h"

#include "bg.h"
#include "spray.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "ui.h"
#include "gauge.h"
#include "life.h"
#include "score.h"

#include "rank.h"

// 追加
#include "model_obstacle.h"
#include "title.h"
#include "game.h"
#include "camera.h"
#include "x_file_motion.h"
#include "billboard_player.h"
#include "logo.h"
#include "texture.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_UI_SIZE				(D3DXVECTOR2(200.0f, 50.0f))
#define LIFE_UI_SIZE				(D3DXVECTOR2(120.0f, 30.0f))
#define LEVEL_UI_SIZE				(D3DXVECTOR2(50.0f, 50.0f))
#define ATTACK_INTERVAL				(7)
#define JOYKEY_LEFT_STICK_UP		(-0.2f)
#define JOYKEY_LEFT_STICK_DOWN		(0.2f)

#define FIELD_SIZE_WIDTH			(280.0f)
#define FIELD_SIZE_HEIGHT			(250.0f)
#define FIELD_SIZE_HEIGHT_CAMERA	(200.0f)

// 重力
#define GRAVITY			(0.1f)
// ジャンプ力
#define JUMP_POWER		(2.0f)
// 当たり判定の範囲
#define ATTACK_LENGTH	(50.0f)

//-----------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------
using namespace LibrarySpace;

//*****************************************************************************
// 定数宣言
//*****************************************************************************
const float CPlayer::SIZE_X = 90.0f;
const float CPlayer::SIZE_Y = 40.0f;
const float CPlayer::MOVE_DEFAULT = 0.35f;
// アニメーション間隔
const int CPlayer::ANIM_INTERVAL = 5;
// アニメーション最大数
const int CPlayer::MAX_ANIM = 2;
// U座標の最大分割数
const int CPlayer::DIVISION_U = 2;
// V座標の最大分割数
const int CPlayer::DIVISION_V = 4;
// プレイヤーのデフォルトカラー
const D3DXCOLOR CPlayer::DEFAULT_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
// デフォルト残機
const int CPlayer::DEFAULT_LIFE = 2;

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CPlayer::CPlayer() :
	m_move(0.0f, 0.0f, 0.0f), m_posOld(0.0f, 0.0f, 0.0f), m_state(STATE_NORMAL), m_nCntState(0), m_nCntAttack(0), m_nCntAnim(0),
	m_nPatternAnim(0), m_nCntAnimMove(0), m_bControlKeyboard(false), m_nGamePadNum(0), m_nTexRotType(TYPE_NEUTRAL), m_nPlayerNum(0),
	m_bIsJumping(false), m_bControl(false), m_bInSea(false), m_pLife(nullptr), m_pScore(nullptr), m_bDie(false), m_bStart(false),
	m_knockBack(0.0f, 0.0f, 0.0f), m_nDamageCnt(0), m_nAttackCnt(0), m_pLogo(nullptr), m_bReady(0)
{
	//オブジェクトの種類設定
	SetType(EObject::OBJ_PLAYER);
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-----------------------------------------------------------------------------
// インスタンス生成処理
//-----------------------------------------------------------------------------
CPlayer *CPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name, int nPlayerNum)
{
	//インスタンス生成
	CPlayer *pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		// 位置設定
		pPlayer->SetPosition(pos);
		// 角度設定
		pPlayer->SetRotation(rot);
		// Xファイルの設定
		pPlayer->BindMotion(CManager::GetManager()->GetMotion()->GetMotion(name));
		// プレイヤー番号の設定
		pPlayer->m_nPlayerNum = nPlayerNum;
		// 生成処理
		pPlayer->Init();
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// タイトル画面
	if (CManager::GetManager()->GetTitle() != nullptr)
	{
		// カメラ位置の取得
		D3DXVECTOR3 rotCamera = CManager::GetManager()->GetTitle()->GetCamera()->GetRotation();
		// 目的の角度設定
		CMotion::SetRotation(D3DXVECTOR3(0.0f, rotCamera.y, 0.0f));
		// 目的の角度設定
		CMotion::SetRotDest(rotCamera);

		// 効果音
		CSound::Play(CSound::SOUND_LABEL_SE_ENTRY);
	}

	// 色の設定
	switch (m_nPlayerNum)
	{
		// 1P
	case 0:

		// ゲーム中なら
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			// スコアの生成
			m_pScore = CScore::Create(D3DXVECTOR3(150.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);
			// 色の設定
			m_pScore->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
		}
		// タイトル画面なら
		else if (CManager::GetManager()->GetTitle() != nullptr)
		{
			m_pLogo = CLogo::Create(D3DXVECTOR3(150.0f, 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_SET", -1);

			// 操作可能状態にする
			m_bControl = true;
		}

		// 色の設定
		CMotion::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));

		// プレイヤー表記の生成
		CBillboardPlayer::Create(GetpPosition(), "TEX_TYPE_BILLBOARD_1P");

		break;

		// 2P
	case 1:

		// ゲーム中なら
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			// スコアの生成
			m_pScore = CScore::Create(D3DXVECTOR3(450.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);
			// 色の設定
			m_pScore->SetColor(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));
		}
		// タイトル画面なら
		else if (CManager::GetManager()->GetTitle() != nullptr)
		{
			m_pLogo = CLogo::Create(D3DXVECTOR3(450.0f, 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_SET", -1);

			// 操作可能状態にする
			m_bControl = true;
		}

		// 色の設定
		CMotion::SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f));

		// プレイヤー表記の生成
		CBillboardPlayer::Create(&GetPosition(), "TEX_TYPE_BILLBOARD_2P");
		break;

		// 3P
	case 2:

		// ゲーム中なら
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			// スコアの生成
			m_pScore = CScore::Create(D3DXVECTOR3(750.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);
			// 色の設定
			m_pScore->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
		}
		// タイトル画面なら
		else if (CManager::GetManager()->GetTitle() != nullptr)
		{
			m_pLogo = CLogo::Create(D3DXVECTOR3(750.0f, 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_SET", -1);

			// 操作可能状態にする
			m_bControl = true;
		}

		// 色の設定
		CMotion::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));

		// プレイヤー表記の生成
		CBillboardPlayer::Create(&GetPosition(), "TEX_TYPE_BILLBOARD_3P");
		break;

		// 4P
	case 3:

		// ゲーム中なら
		if (CManager::GetManager()->GetGame() != nullptr)
		{
			// スコアの生成
			m_pScore = CScore::Create(D3DXVECTOR3(1050.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);
			// 色の設定
			m_pScore->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f));
		}
		// タイトル画面なら
		else if (CManager::GetManager()->GetTitle() != nullptr)
		{
			m_pLogo = CLogo::Create(D3DXVECTOR3(1050.0f, 30.0f, 0.0f), D3DXVECTOR2(220.0f, 60.0f), "TEX_TYPE_UI_SET", -1);

			// 操作可能状態にする
			m_bControl = true;
		}

		// 色の設定
		CMotion::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));

		// プレイヤー表記の生成
		CBillboardPlayer::Create(&GetPosition(), "TEX_TYPE_BILLBOARD_3P");
		break;
	default:
		break;
	}

	// 初期化
	CMotion::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CMotion::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CPlayer::Update()
{
	if (CManager::GetManager()->GetGame() != nullptr)
	{
		if (CManager::GetManager()->GetGame()->GetStart() == true && CManager::GetManager()->GetGame()->GetEnd() == false)
		{
			if (m_state != STATE_DAMAGE)
			{
				m_bControl = true;
			}
		}
	}

	// 前回の位置を保存
	m_posOld = GetPosition();

	// 位置情報を取得
	D3DXVECTOR3 pos = CMotion::GetPosition();
	// サイズの取得
	D3DXVECTOR3 size = CMotion::GetSizeMax();

	// 操作できる状態なら && 死亡していないなら
	if (m_bControl == true && m_state != STATE_DIE)
	{
		// 移動していなければ
		if (Move() == false)
		{
			m_state = STATE_NORMAL;
		}

		// ジャンプ
		Jump();

		// 攻撃
		Attack();
	}

	if (m_state == STATE_DAMAGE)
	{
		// 被弾処理
		Damage();
	}

	// 重力負荷をかける
	m_move.y -= GRAVITY;
	
	////プレイヤーが雪崩に巻き込まれていたら
	//if (m_state == STATE_INAVALANCHE)
	//{
	//	// キーボード情報の取得
	//	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	//	// ジョイパッド情報の取得
	//	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	//	//プレイヤーを後退させる
	//	m_move.z -= 1.0f;

	//	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_OK))
	//	{
	//		m_nPushButton++;
	//		if (m_nPushButton >= 1/*何回押したら雪崩を抜けるか*/)
	//		{
	//			m_state = STATE_NORMAL;
	//		}
	//	}
	//}

	// 移動量の加算
	pos += m_move;

	// 障害物の当たり判定
	CObstacle::CollisionAll(&pos, m_nPlayerNum);

	// 移動量の減衰
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;

	//壁・床の当たり判定処理
	if (pos.x - (size.x / 2) <= -FIELD_SIZE_WIDTH / 2)
	{// 左壁
		pos.x = (-FIELD_SIZE_WIDTH / 2) + (size.x / 2);
	}
	else if (pos.x + (size.x / 2) >= FIELD_SIZE_WIDTH / 2)
	{// 右壁
		pos.x = (FIELD_SIZE_WIDTH / 2) - (size.x / 2);
	}
	//if (g_Player.pos.z + (PLAYER_WIDTH / 2) >= 400.0f / 2)
	//{//奥壁
	//	g_Player.pos.z = (400.0f / 2) - (PLAYER_WIDTH / 2);
	//}

	// ゲーム参加中であれば
	if (m_bStart == true)
	{
		if (CManager::GetManager()->GetGame()->GetEnd() == false)
		{
			// ゲームが始まったら
			if (CManager::GetManager()->GetGame()->GetStart() == true && m_bDie == false)
			{
				m_pScore->Add(1);
			}

			// カメラ位置の取得
			D3DXVECTOR3 posCamera = CManager::GetManager()->GetGame()->GetCamera()->GetPosV();

			if (pos.z - (size.z / 2) <= posCamera.z + FIELD_SIZE_HEIGHT_CAMERA)
			{// 手前壁
				pos.z = (posCamera.z + FIELD_SIZE_HEIGHT_CAMERA) + (size.z / 2);
			}
		}
	}
	// ロビー待機中であれば
	else
	{
		if (pos.z - (size.z / 2) <= -FIELD_SIZE_HEIGHT / 2)
		{// 手前壁
			pos.z = (-FIELD_SIZE_HEIGHT / 2) + (size.z / 2);
		}

		// キーボード情報の取得
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
		// ジョイパッド情報の取得
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		// キーボード操作の場合
		if (m_bControlKeyboard == true &&
			pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_1) == true)
		{// SPACEキー押下
			m_bReady = m_bReady ? false : true;

			// 被弾音
			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);
		}
		// ゲームパッド操作の場合
		else if (m_bControlKeyboard == false &&
			pJoypad->GetTrigger(CInputJoypad::JOYKEY_X, m_nGamePadNum) == true)
		{// Aボタン押下
			m_bReady = m_bReady ? false : true;

			// 被弾音
			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);
		}

		if (m_bReady == true)
		{
			m_pLogo->BindTexture(CManager::GetManager()->GetTexture()->GetTexture("TEX_TYPE_UI_OK"));
		}
		else
		{
			m_pLogo->BindTexture(CManager::GetManager()->GetTexture()->GetTexture("TEX_TYPE_UI_SET"));
		}
	}

	if (pos.y <= 0.0f)
	{// 床
		pos.y = 0.0f;
		m_bIsJumping = false;
		// 移動量Yの初期化
		m_move.y = 0.0f;
	}

	// 位置情報更新
	CMotion::SetPosition(pos);

	// 角度の正規化
	CMotion::NormalizeRot();

	// プレイヤーが終了していなければ
	if (m_state != STATE_END)
	{
		// 状態管理
		State();

		// モーション再生
		if (CMotion::Motion() == true && m_state == STATE_DIE)
		{
			m_state = STATE_END;
		}
	}
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CPlayer::Draw()
{
	//描画
	CMotion::Draw();
}

//-----------------------------------------------------------------------------
// 移動処理
//-----------------------------------------------------------------------------
bool CPlayer::Move()
{
	// 移動しているかどうか
	bool bMove = false;
	// 目的の角度
	D3DXVECTOR3 rotDest = { 0,0,0 };
	// カメラ位置の取得
	D3DXVECTOR3 rotCamera = { 0,0,0 };

	// 移動力を取得
	float fMove = CMotion::GetMotion().fMove;

	if (m_bStart == false)
	{
		// カメラ位置の取得
		rotCamera = CManager::GetManager()->GetTitle()->GetCamera()->GetRotation();
	}

	// キーボードで操作しているなら
	if (m_bControlKeyboard == true)
	{
		// キーボード情報の取得
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();

		if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_LEFT) == true)
		{// 左キー押下
			if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
			{// 下キー押下
				// 移動量加算
				m_move.x += -GetSinVec(-4.0f, rotCamera.y, fMove);
				m_move.z += -GetCosVec(-4.0f, rotCamera.y, fMove);
				// 目的の角度設定
				rotDest.y = (D3DX_PI / 4.0f) + rotCamera.y;
			}
			else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
			{// 上キー押下
				m_move.x += -GetSinVec(-1.5f, rotCamera.y, fMove);
				m_move.z += -GetCosVec(-1.5f, rotCamera.y, fMove);
				// 目的の角度設定
				rotDest.y = (D3DX_PI / 1.5f) + rotCamera.y;
			}
			else
			{// 左移動
				m_move.x += GetSinVec(2.0f, rotCamera.y, fMove);
				m_move.z += GetCosVec(2.0f, rotCamera.y, fMove);
				// 目的の角度設定
				rotDest.y = (D3DX_PI / 2.0f) + rotCamera.y;
			}

			// 移動フラグを立てる
			bMove = true;
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_RIGHT) == true)
		{// 右キー押下
			if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
			{// 上キー押下
				m_move.x += -GetSinVec(4.0f, rotCamera.y, fMove);
				m_move.z += -GetCosVec(4.0f, rotCamera.y, fMove);
				// 目的の角度設定
				rotDest.y = (-D3DX_PI / 4) + rotCamera.y;
			}
			else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
			{// 下キー押下
				m_move.x += -GetSinVec(1.5f, rotCamera.y, fMove);
				m_move.z += -GetCosVec(1.5f, rotCamera.y, fMove);
				// 目的の角度設定
				rotDest.y = (-D3DX_PI / 1.5f) + rotCamera.y;
			}
			else
			{
				m_move.x += GetSinVec(-2.0f, rotCamera.y, fMove);
				m_move.z += GetCosVec(-2.0f, rotCamera.y, fMove);
				// 目的の角度設定
				rotDest.y = (-D3DX_PI / 2.0f) + rotCamera.y;
			}

			// 移動フラグを立てる
			bMove = true;
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
		{// 上キー押下
			m_move.x += -GetSinVec(1.0f, rotCamera.y, fMove);
			m_move.z += -GetCosVec(1.0f, rotCamera.y, fMove);
			// 目的の角度設定
			rotDest.y = D3DX_PI + rotCamera.y;

			// 移動フラグを立てる
			bMove = true;
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
		{// 下キー押下
			m_move.x += GetSinVec(1.0f, rotCamera.y, fMove);
			m_move.z += GetCosVec(1.0f, rotCamera.y, fMove);
			// 目的の角度設定
			rotDest.y = 0.0f + rotCamera.y;

			// 移動フラグを立てる
			bMove = true;
		}
	}
	// ゲームパッド操作なら
	else
	{
		// ジョイパッド情報の取得
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		if (pJoypad->GetPress(CInputJoypad::JOYKEY_LEFT, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).x <= -0.2f)
		{// 左キー押下
			if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
			{// 上キー押下
				// 移動量加算
				m_move.x += GetSinVec(-0.75f, fMove);
				m_move.z += GetCosVec(-0.75f, fMove);
				// 目的の角度設定
				rotDest.y = D3DX_PI / 4;
			}
			else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
			{// 下キー押下
				m_move.x += GetSinVec(-0.25f, fMove);
				m_move.z += GetCosVec(-0.25f, fMove);
				// 目的の角度設定
				rotDest.y = D3DX_PI / 1.5f;
			}
			else
			{
				m_move.x += GetSinVec(-0.5f, fMove);
				m_move.z += GetCosVec(-0.5f, fMove);
				// 目的の角度設定
				rotDest.y = D3DX_PI / 2;
			}

			// 移動フラグを立てる
			bMove = true;
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_RIGHT, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).x >= 0.2f)
		{// 右キー押下
			if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
			{// 上キー押下
				m_move.x += GetSinVec(0.75f, fMove);
				m_move.z += GetCosVec(0.75f, fMove);
				// 目的の角度設定
				rotDest.y = -D3DX_PI / 4;
			}
			else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
			{// 下キー押下
				m_move.x += GetSinVec(0.25f, fMove);
				m_move.z += GetCosVec(0.25f, fMove);
				// 目的の角度設定
				rotDest.y = -D3DX_PI / 1.5f;
			}
			else
			{
				m_move.x += GetSinVec(0.5f, fMove);
				m_move.z += GetCosVec(0.5f, fMove);
				// 目的の角度設定
				rotDest.y = -D3DX_PI / 2;
			}

			// 移動フラグを立てる
			bMove = true;
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
		{// 上キー押下
			m_move.x += GetSinVec(1.0f, fMove);
			m_move.z += GetCosVec(1.0f, fMove);
			// 目的の角度設定
			rotDest.y = 0.0f;

			// 移動フラグを立てる
			bMove = true;
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
		{// 下キー押下
			m_move.x += GetSinVec(0.0f, fMove);
			m_move.z += GetCosVec(0.0f, fMove);
			// 目的の角度設定
			rotDest.y = D3DX_PI;

			// 移動フラグを立てる
			bMove = true;
		}
	}

	// 移動してれば
	if (bMove == true)
	{
		// 角度設定
		CMotion::SetRotDest(rotDest);
		// 状態の設定
		m_state = STATE_RUN;
	}

	return bMove;
}

//-----------------------------------------------------------------------------
// ジャンプ
//-----------------------------------------------------------------------------
void CPlayer::Jump()
{
	// ジャンプしていれば
	if (m_bIsJumping == true)
	{
		m_state = STATE_JUMP;
	}
	// ジャンプしていなければ
	else if (m_bIsJumping == false)
	{
		// キーボード情報の取得
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
		// ジョイパッド情報の取得
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		// ジャンプ力を取得
		float fJump = CMotion::GetMotion().fJump;

		// キーボード操作の場合
		if (m_bControlKeyboard == true &&
			pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_JUMP) == true)
		{// SPACEキー押下

			// ジャンプ力の設定
			m_move.y = fJump;

			// ジャンプフラグの設定
			m_bIsJumping = true;

			// 効果音
			CSound::Play(CSound::SOUND_LABEL_SE_JUMP);
		}
		// ゲームパッド操作の場合
		else if (m_bControlKeyboard == false &&
			pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, m_nGamePadNum) == true)
		{// Aボタン押下

			// ジャンプ力の設定
			m_move.y = fJump;

			// ジャンプフラグの設定
			m_bIsJumping = true;

			// 効果音
			CSound::Play(CSound::SOUND_LABEL_SE_JUMP);
		}
	}
}

//-----------------------------------------------------------------------------
// 攻撃処理
//-----------------------------------------------------------------------------
void CPlayer::Attack()
{
	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	// ジョイパッド情報の取得
	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	if (m_bAttack)
	{
		m_state = STATE_ATTACK;

		//腕先の位置情報を取得(ワールドマトリックスからワールド座標を取得)
		D3DXVECTOR3 AttackPos = D3DXVECTOR3(
			CMotion::GetMotion().aParts[6].mtxWorld._41,
			CMotion::GetMotion().aParts[6].mtxWorld._42,
			CMotion::GetMotion().aParts[6].mtxWorld._43);

		for (int nCntPlayer = 0; nCntPlayer < PLAYER_MAX; nCntPlayer++)
		{
			// 攻撃対象が自分自身なら
			if (nCntPlayer == m_nPlayerNum)
			{
				continue;
			}

			CTitle *pTitle = CManager::GetManager()->GetTitle();
			CGame *pGame = CManager::GetManager()->GetGame();

			// タイトルのnullチェック
			if (pTitle != nullptr)
			{
				CPlayer *pPlayer = pTitle->GetPlayer(nCntPlayer);

				// プレイヤーのnullチェック
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 OutPos = pPlayer->GetPosition();

					if (pPlayer->GetState() != STATE_DAMAGE && LibrarySpace::SphereCollision(AttackPos,
						D3DXVECTOR3(OutPos.x, OutPos.y + 50.0f, OutPos.z), ATTACK_LENGTH, pPlayer->GetSizeMax().x))
					{//弾と当たったら(球体の当たり判定)

						// 被弾音
						CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE);

						//敵とプレイヤーの距離差分を保存(目的の位置 - 現在の位置)
						D3DXVECTOR3 vecToPlayer = pPlayer->GetPosition() - AttackPos;

						//敵からプレイヤーへのベクトル(移動量)に変換する
						D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

						// ダメージ状態にする
						pPlayer->SetState(STATE_DAMAGE);

						pPlayer->SetControl(false);

						// ベクトルを保存
						pPlayer->SetVec(vecToPlayer);

						//return true;	//当たった
					}
				}
			}
			// タイトルのnullチェック
			if (pGame != nullptr)
			{
				CPlayer *pPlayer = pGame->GetPlayer(nCntPlayer);

				// プレイヤーのnullチェック
				if (pPlayer != nullptr)
				{
					D3DXVECTOR3 OutPos = pPlayer->GetPosition();

					if (pPlayer->GetState() != STATE_DAMAGE && LibrarySpace::SphereCollision(AttackPos,
						D3DXVECTOR3(OutPos.x, OutPos.y + 50.0f, OutPos.z), ATTACK_LENGTH, pPlayer->GetSizeMax().x))
					{//弾と当たったら(球体の当たり判定)

						// 被弾音
						CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE);

						//敵とプレイヤーの距離差分を保存(目的の位置 - 現在の位置)
						D3DXVECTOR3 vecToPlayer = pPlayer->GetPosition() - AttackPos;

						//敵からプレイヤーへのベクトル(移動量)に変換する
						D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

						// ダメージ状態にする
						pPlayer->SetState(STATE_DAMAGE);

						pPlayer->SetControl(false);

						// ベクトルを保存
						pPlayer->SetVec(vecToPlayer);

						//return true;	//当たった
					}
				}
			}
		}
		
		// 攻撃カウンター加算
		m_nAttackCnt++;

		// 攻撃終了
		if (m_nAttackCnt >= 55)
		{
			m_bAttack = false;
			m_nAttackCnt = 0;
		}
	}
	else if (GetChange() == false)
	{
		// キーボード操作の場合
		if (m_bControlKeyboard == true && pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_ATTACK) == true ||
			m_bControlKeyboard == false && pJoypad->GetTrigger(CInputJoypad::JOYKEY_B, m_nGamePadNum) == true)
		{// SPACEキー押下

			// 効果音
			CSound::Play(CSound::SOUND_LABEL_SE_ATTACK);

			m_bAttack = true;
		}
	}
}

//-----------------------------------------------------------------------------
// 状態管理
//-----------------------------------------------------------------------------
void CPlayer::State()
{
	switch (m_state)
	{
		// 通常
	case CPlayer::STATE_NORMAL:

		// 待機モーション
		CMotion::Set(0);

		break;

		// 走る
	case CPlayer::STATE_RUN:

		// 移動モーション
		CMotion::Set(1);

		break;

		// 攻撃
	case CPlayer::STATE_ATTACK:

		// 移動モーション
		CMotion::Set(2);

		break;

		// ジャンプ
	case CPlayer::STATE_JUMP:

		// ジャンプモーション
		CMotion::Set(3);

		break;

		// 被弾
	case CPlayer::STATE_DAMAGE:

		// 操作不能状態にする
		m_bControl = false;

		// 被弾モーション
		CMotion::Set(7);

		//ダメージ処理
		Damage();

		break;

		// 死亡
	case CPlayer::STATE_DIE:

		// 死亡モーション
		CMotion::Set(8);

		break;

		// 雪崩に巻き込まれてる
	case CPlayer::STATE_INAVALANCHE:
		break;

		// 終了
	case CPlayer::STATE_END:
		break;

	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// ダメージ処理
//-----------------------------------------------------------------------------
void CPlayer::Damage()
{
	// 位置の取得
	D3DXVECTOR3 pos = GetPosition();

	// 被弾ベクトルの加算
	pos += m_knockBack;

	// 位置の設定
	SetPosition(pos);

	m_nDamageCnt++;

	if (m_nDamageCnt >= 30)
	{
		m_state = STATE_NORMAL;
		m_nDamageCnt = 0;
		m_bControl = true;
	}

	//if (m_BarrierLevel == CBarrier::LEVEL_NONE)
	//{

	// 死亡処理
	//Die();

	// プレイヤー死亡音
	//CSound::Play(CSound::SOUND_LABEL_SE_DIE_PLAYER);

	//}
	//else
	//{
	//	m_BarrierLevel = (CBarrier::LEVEL)(m_BarrierLevel - 1);

	//	if (m_BarrierLevel == CBarrier::LEVEL_NONE)
	//	{
	//		if (m_pBarrier != nullptr)
	//		{
	//			m_pBarrier->Uninit();
	//			m_pBarrier = nullptr;
	//		}
	//	}
	//	else
	//	{
	//		m_pBarrier->SetBarrier(m_BarrierLevel);
	//	}
	//	m_state = STATE_RESPAWN;
	//	m_nCntState = 150;
	//}
}

//-----------------------------------------------------------------------------
// 死亡処理
//-----------------------------------------------------------------------------
void CPlayer::Die()
{
	//CModel::Uninit();

	// 操作不能にする
	m_bControl = false;
	// プレイヤーを死亡状態にする
	m_bDie = true;
	m_state = STATE_DIE;

	if (m_pScore != nullptr)
	{
		// スコアの色を変える
		m_pScore->SetColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	}

	// 効果音
	CSound::Play(CSound::SOUND_LABEL_SE_DIE);

	//// ライフが破棄されていなければ
	//if (m_pLife != nullptr)
	//{
	//	// ライフを減らす
	//	m_pLife->Add(-1);

	//	// ライフが0未満
	//	if (m_pLife->GetLife() < 0)
	//	{
	//		// スコアの破棄
	//		if (m_pScore != nullptr)
	//		{
	//			m_pScore->Uninit();
	//			m_pScore = nullptr;
	//		}

	//		// ライフの破棄
	//		m_pLife->Uninit();
	//		m_pLife = nullptr;

	//		// プレイヤーを死亡状態にする
	//		m_bDie = true;

	//		// サイズの取得
	//		D3DXVECTOR2 size = GetSize();
	//		// 爆発の生成
	//		CExplosion::Create(CObject2D::GetPosition(), D3DXVECTOR2(size.x, size.y * 2));

	//		return;
	//	}

	//	// 操作不能にする
	//	m_bControl = false;
	//	// リスポーン状態にする
	//	m_state = STATE_DIE;
	//	m_nCntState = 60;

	//	// 変数のリセット
	//	m_nTexRotType = TYPE_NEUTRAL;		//アニメーション番号をリセットする

	//										// バリアの破棄
	//	if (m_pBarrier != nullptr)
	//	{
	//		m_pBarrier->Uninit();
	//		m_pBarrier = nullptr;
	//	}

	//	// オプションの破棄
	//	for (int nCnt = 0; nCnt < MAX_OPTION; nCnt++)
	//	{
	//		if (m_pOption[nCnt] != nullptr)
	//		{
	//			m_pOption[nCnt]->Uninit();
	//			m_pOption[nCnt] = nullptr;
	//		}
	//	}

	//	// 各強化状態を初期化する
	//	m_OptionLevel = CBulletOption::LEVEL_NONE;
	//	m_BarrierLevel = CBarrier::LEVEL_NONE;
	//	m_BulletLevel = CPlayer::LEVEL_1;

	//	// サイズの取得
	//	D3DXVECTOR2 size = GetSize();
	//	// 爆発の生成
	//	CExplosion::Create(CObject2D::GetPosition(), D3DXVECTOR2(size.x, size.y * 2));

	//	//プレイヤーの位置を左端に設定する
	//	if (m_nPlayerNum == PLAYER_1)
	//	{// 1Pの場合
	//		CObject2D::SetPosition(D3DXVECTOR3(-SIZE_X, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
	//	}
	//	else
	//	{// 2Pの場合
	//		CObject2D::SetPosition(D3DXVECTOR3(-SIZE_X, CRenderer::SCREEN_HEIGHT / 2 + SIZE_Y, 0.0f));
	//	}

	//}
}

//-----------------------------------------------------------------------------------------------
//
// 敵ボスの処理[boss.cpp]
// Author : SHUGO KURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "boss.h"
#include "manager.h"
#include "renderer.h"

#include "load.h"
#include "sound.h"

#include "game.h"
#include "library.h"
#include "effect.h"
#include "logo.h"
#include "score.h"
#include "fade_scene.h"

#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "logo.h"

// 追加
#include "x_file_motion.h"
#include "motion_data.h"

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 体力
const int CBoss::LIFE = 2000;
// 幅
const float CBoss::SIZE_WIDTH = 300.0f;
// 高さ
const float CBoss::SIZE_HEIGHT = 270.0f;
// U座標の最大分割数
const int CBoss::DIVISION_U = 4;
// V座標の最大分割数
const int CBoss::DIVISION_V = 1;
// 攻撃前の予備動作間隔
const int CBoss::RUSH_OPERATION = 60;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CBoss::CBoss()
	:m_move(0.0f, 0.0f, 0.0f), m_pattern(PATTERN_ENTRY), m_nCounter(0), m_fAttackRot(0.0f),
	m_bSizeChange(false), m_nCountObject(0), m_fAdd(0.0f)
{
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CBoss::~CBoss()
{
}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CBoss *CBoss::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// ポインタクラスを宣言
	CBoss* pEnemy = new CBoss;

	if (pEnemy != nullptr)
	{
		//位置設定
		pEnemy->SetPosition(pos);
		// 角度設定
		pEnemy->SetRotation(rot);
		// Xファイルの設定
		pEnemy->BindMotion(CManager::GetManager()->GetMotion()->GetMotion(name));
		// 初期化
		pEnemy->Init();
	}

	return pEnemy;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CBoss::Init()
{
	// 種類を設定
	SetType(EObject::OBJ_ENEMYBOSS);
	// 初期化
	CMotion::Init();

	// 攻撃前の予備動作間隔を設定
	m_nCountOperation = RUSH_OPERATION;

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CBoss::Uninit()
{
	CMotion::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CBoss::Update()
{
	// 位置の取得
	D3DXVECTOR3 pos = CMotion::GetPosition();

	// 各行動
	Pattern(pos);

	// 移動処理
	if (m_pattern == PATTERN_NORMAL)
	{// 移動モーション
		
	}
	else
	{
	}

	// 移動量の加算
	pos += m_move;

	// 移動量の減衰
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;
	
	// 当たり判定
	Collision(pos);

	// 位置情報更新
	CMotion::SetPosition(pos);

	// 角度の正規化
	CMotion::NormalizeRot();

	//}
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CBoss::Draw()
{
	//描画処理
	CMotion::Draw();
}

//-----------------------------------------------------------------------------------------------
// 当たり判定
//-----------------------------------------------------------------------------------------------
bool CBoss::Collision(D3DXVECTOR3 posStart)
{
	// プレイヤー生成
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		//プレイヤー情報の取得
		CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(nCntPlayer);

		if (pPlayer != nullptr)
		{
			// プレイヤーが通常状態だったら
			if (pPlayer->GetState() != CPlayer::STATE_DIE && pPlayer->GetState() != CPlayer::STATE_END)
			{
				// プレイヤー座標の取得
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

				//敵と当たったら(球体の当たり判定)
				if (LibrarySpace::PlaneCollision(posPlayer.z, posStart.z - 50.0f))
				{//ダメージ処理
					pPlayer->Die();

					return true;	//当たった
				}
			}
		}
	}

	return false;	//当たってない
}

//-----------------------------------------------------------------------------------------------
// 行動パターン管理
//-----------------------------------------------------------------------------------------------
bool CBoss::Pattern(D3DXVECTOR3& pos)
{
	//雑魚敵生成情報の取得
	//ParentEnemyInfo *pBossInfo = LoadSpace::GetParentEnemy();

	// モーション再生
	bool bEnd = CMotion::Motion();

	switch (m_pattern)
	{
		//=================================
		// 登場
		//=================================
	case CBoss::PATTERN_ENTRY:

		// ゲームが始まったら
		if (CManager::GetManager()->GetGame()->GetStart())
		{// 通常状態にする
			m_pattern = PATTERN_RUN;
		}

		if (bEnd == true)
		{
			m_pattern = PATTERN_NORMAL;
			break;
		}

		CMotion::Set(0);

		break;

		//=================================
		// 通常
		//=================================
	case CBoss::PATTERN_NORMAL:

		// ゲームが始まったら
		if (CManager::GetManager()->GetGame()->GetStart())
		{// 通常状態にする
			m_pattern = PATTERN_RUN;
		}

		CMotion::Set(1);

		break;

		//=================================
		// 通常
		//=================================
	case CBoss::PATTERN_RUN:

		if (m_fAdd > 0.9f)
		{
			m_fAdd = 0.9f;
		}

		// 移動量の加算
		m_move.z -= GetMotion().fMove + m_fAdd;

		CMotion::Set(2);

		m_nCounter++;

		if (m_nCounter >= 300)
		{
			//カウンターリセット
			m_nCounter = 0;
			//次の行動をランダムで決める
			m_pattern = (PATTERN)LibrarySpace::GetRandNum(PATTERN_BARRAGE, PATTERN_SNOWBALL);
		}

		break;

		//=================================
		// 連続突進攻撃
		//=================================
	//case CEnemyBoss::PATTERN_RUSH:

	//	if (m_nCountOperation <= 0)
	//	{
	//		m_nCountOperation--;

	//		// 画面の中心座標を保存
	//		D3DXVECTOR2 ScreenCenter = D3DXVECTOR2(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2);

	//		if (m_nCounter >= 5)
	//		{
	//			//位置の保存
	//			D3DXVECTOR3 vec = m_PosOld - pos;
	//			//敵からプレイヤーへのベクトル(移動量)に変換する
	//			D3DXVec3Normalize(&vec, &vec);
	//			//移動量に倍率を掛ける
	//			vec.x *= 4.0f;
	//			vec.y *= 4.0f;
	//			//移動量の加算
	//			pos += vec;

	//			//前回の位置に移動し終えたら
	//			if (pos.x <= m_PosOld.x)
	//			{
	//				// 通常状態に戻す(変数のリセット)
	//				StateReset();
	//			}
	//		}
	//		else if (m_nCountOperation == -120)
	//		{
	//			// 突進する角度を決める
	//			m_fAttackRot = LibrarySpace::GetRandFloat(3, 0, 100);

	//			// 警告音
	//			CSound::Play(CSound::SOUND_LABEL_SE_WARNING2);

	//			// 敵の予測軌道範囲ロゴ
	//			CLogo::Create(D3DXVECTOR3(ScreenCenter.x, ScreenCenter.y, 0.0f), D3DXVECTOR2(ScreenCenter.x * 2.5f, SIZE_HEIGHT),
	//				D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f), m_fAttackRot, CLogo::TYPE_NONE, CLogo::ANIM_NONE, 60);

	//			// 注意喚起標識のロゴ
	//			CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(200.0f, 200.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_REMINDER, CLogo::ANIM_FLASHING, 60);

	//			pos = D3DXVECTOR3(ScreenCenter.x, ScreenCenter.y, 0.0f);
	//			float fLenght = sqrtf((ScreenCenter.x * ScreenCenter.x) + (ScreenCenter.y * ScreenCenter.y));
	//			pos += D3DXVECTOR3(cosf(m_fAttackRot) * (fLenght + SIZE_WIDTH), -sinf(m_fAttackRot) * (fLenght + SIZE_HEIGHT), 0);
	//		}
	//		else if (m_nCountOperation <= -180)
	//		{
	//			if (m_nCountOperation == -180)
	//			{
	//				// 突進音
	//				CSound::Play(CSound::SOUND_LABEL_SE_RUSH);

	//				// 警告音のストップ
	//				CSound::Stop(CSound::SOUND_LABEL_SE_WARNING2);
	//			}

	//			// エフェクト生成
	//			CEffect::Create(pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT), CEffect::TYPE_AFTERIMAGE, CEffect::TEX_BOSS);
	//			D3DXVECTOR3 vec = D3DXVECTOR3((cosf(m_fAttackRot) * 30.0f), -(sinf(m_fAttackRot) * 30.0f), 0);
	//			pos -= vec;
	//			if (LibrarySpace::OutScreen2D(&pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT)) && m_nCountOperation <= -200)
	//			{
	//				m_nCountOperation = -90;
	//				m_nCounter++;

	//				// 5回突進したら
	//				if (m_nCounter >= 5)
	//				{
	//					pos = D3DXVECTOR3((ScreenCenter.x * 2) + (SIZE_WIDTH / 2), ScreenCenter.y - 110.0f, 0.0f);
	//				}
	//			}
	//		}
	//		else if (!LibrarySpace::OutScreen2D(&pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT)))
	//		{
	//			// エフェクト生成
	//			CEffect::Create(pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT), CEffect::TYPE_AFTERIMAGE, CEffect::TEX_BOSS);
	//			// 左に突進する
	//			pos.x += -30.0f;
	//		}
	//	}
	//	else
	//	{
	//		//拡縮させる
	//		ChangeSize(&size, 2.0f);

	//		if (m_nCountOperation == RUSH_OPERATION)
	//		{// 最初のみ位置を保存
	//			m_PosOld = pos;
	//		}

	//		m_nCountOperation--;
	//		pos.x += m_nCountOperation * 0.1f;

	//		if(m_nCountOperation==1)
	//		{
	//			// 突進音
	//			CSound::Play(CSound::SOUND_LABEL_SE_RUSH);
	//		}
	//	}

	//	break;
	//	//=================================
	//	// 雑魚敵の生成攻撃
	//	//=================================
	//case CEnemyBoss::PATTERN_CREATE:

	//	//拡縮させる
	//	ChangeSize(&size, 3.0f);

	//	//攻撃カウンターを加算
	//	m_nCounter++;

	//	if (m_nCounter >= 60)
	//	{
	//		m_nCountOperation--;

	//		if (m_nCountOperation <= RUSH_OPERATION - pBossInfo->nInterval)
	//		{
	//			m_nCountOperation = RUSH_OPERATION;
	//			CEnemy::Create(pos, (CEnemy::TYPE)pBossInfo->nType, pBossInfo->nLife, pBossInfo->move);
	//			m_nCountObject++;
	//			if (m_nCountObject >= pBossInfo->nNum)
	//			{
	//				// 通常状態に戻す(変数のリセット)
	//				StateReset();
	//			}
	//		}
	//	}

	//	break;
	//case CEnemyBoss::PATTERN_BARRAGE:

	//	//拡縮させる
	//	ChangeSize(&size, 3.0f);

	//	//攻撃カウンターを加算
	//	m_nCounter++;
	//	//常に回転させる
	//	m_fAttackRot += 0.05f;

	//	if (m_nCounter >= 60)
	//	{
	//		//連続攻撃カウンターを加算
	//		m_nCountOperation--;

	//		if (m_nCountOperation <= RUSH_OPERATION - 3)
	//		{
	//			m_nCountOperation = RUSH_OPERATION;
	//			m_nCountObject++;
	//			float fDeg = 0.0f;

	//			while (fDeg <= 330.0f)
	//			{
	//				// 弾を円状に配置
	//				float fRad = (fDeg * (D3DX_PI / 180)) + m_fAttackRot;
	//				D3DXVECTOR3 vec = D3DXVECTOR3(sinf(fRad) * 10.0f, cosf(fRad) * 10.0f, 0);
	//				CBullet* pBullet = CBullet::Create(pos, vec, 1, CBullet::TYPE_ENEMY_RED);
	//				pBullet->SetParent(CBullet::PARENT_ENEMY);
	//				pBullet->SetRot(fRad);
	//				fDeg += 60.0f;
	//			}

	//			if (m_nCountObject >= 40)
	//			{
	//				// 通常状態に戻す(変数のリセット)
	//				StateReset();
	//			}

	//			// 弾発射音
	//			CSound::Play(CSound::SOUND_LABEL_SE_SHOT2);
	//		}
	//	}
	//	break;

	//	//=================================
	//	// 死亡
	//	//=================================
	//case CEnemyBoss::PATTERN_DIE:
	//	// 死亡カウンターを加算
	//	m_nCounter++;

	//	if (m_nCounter == 1)
	//	{
	//		// 白フェードの生成
	//		CFadeScene::Create(CFadeScene::TYPE_WHITE);

	//		// 敵の死亡フラグを立てる
	//		CGame::SetDieBoss(true);

	//		// ボス死亡音
	//		CSound::Play(CSound::SOUND_LABEL_SE_DIE_BOSS);

	//		// ボスBGMを止める
	//		CSound::Stop(CSound::SOUND_LABEL_BOSS);
	//	}
	//	else if (m_nCounter == 40)
	//	{
	//		// ポーズ解除
	//		CManager::SetPause(false);
	//	}
	//	else if (m_nCounter >= 40)
	//	{
	//		// 位置を左下に下げる
	//		pos += D3DXVECTOR3(-1.0f, 2.0f, 0.0f);

	//		if (m_nCounter % 5 == 0)
	//		{
	//			// 爆発の生成
	//			CExplosion::Create(D3DXVECTOR3((float)LibrarySpace::GetRandNum((int)(pos.x + (size.x / 2)), (int)(pos.x - (size.x / 2))),
	//				(float)LibrarySpace::GetRandNum((int)(pos.y + (size.y / 2)), (int)(pos.y - (size.y / 2))), 0.0f),
	//				D3DXVECTOR2(size.x / 2, size.y / 2));
	//		}

	//		if (LibrarySpace::OutScreen2D(&pos, size) == true)
	//		{
	//			//画面を揺らす
	//			//CObject::SetShake(60);
	//			// ボス死亡音
	//			CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION_BOSS);
	//			// 破棄
	//			Uninit();

	//			// メッシュ背景の破棄
	//			CMeshField *pMesh = CGame::GetMeshField();
	//			if (pMesh != nullptr)
	//			{
	//				pMesh->SetUninit(true);
	//			}

	//			// ゲームクリアロゴの生成
	//			CLogo::Create(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, 100.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_CLEAR, CLogo::ANIM_LENGTHWISE, 420);

	//			CLogo::Create(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH / 4, 150.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_BONUS, CLogo::ANIM_LENGTHWISE, 420);

	//			// ゲームクリア音
	//			CSound::Play(CSound::SOUND_LABEL_SE_CLEAR);

	//			// ボーナススコア加算
	//			for (int nCnt = 0; nCnt < CPlayer::PLAYER_MAX; nCnt++)
	//			{
	//				CPlayer *pPlayer = CGame::GetPlayer(nCnt);
	//				if (pPlayer != nullptr)
	//				{
	//					// スコア
	//					CScore* pScore = pPlayer->GetScore();
	//						
	//					if (pScore != nullptr)
	//					{
	//						pScore->Add(30000);
	//					}
	//				}
	//			}
	//			return true;
	//		}
	//	}
	//	break;

	default:
		break;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// 拡縮処理
//-----------------------------------------------------------------------------------------------
void CBoss::ChangeSize(D3DXVECTOR2 *pSize, const float& fSize)
{
	//if (!m_bSizeChange)
	//{
	//	*pSize -= D3DXVECTOR2(fSize, fSize);
	//	if (pSize->x <= SIZE_WIDTH - 20.0f)
	//	{
	//		m_bSizeChange = true;
	//	}
	//}
	//else if (m_bSizeChange)
	//{
	//	*pSize += D3DXVECTOR2(fSize, fSize);
	//	if (pSize->x >= SIZE_WIDTH)
	//	{
	//		m_bSizeChange = false;
	//	}
	//}
}

//-----------------------------------------------------------------------------------------------
// メンバ変数リセット
//-----------------------------------------------------------------------------------------------
void CBoss::StateReset()
{
	//m_nCounter = 0;
	//m_nCountObject = 0;
	//m_fAttackRot = 0.0f;
	//m_pattern = PATTERN_NORMAL;
	//m_nCountOperation = RUSH_OPERATION;
}

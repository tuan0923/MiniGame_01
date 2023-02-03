//-----------------------------------------------------------------------------------------------
//
//	モデルのマネージャー処理[model_obstacle.cpp]
//	Author : SHUGO KURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"

#include "library.h"

// 追加
#include "x_file.h"
#include "model_manager.h"
#include "game.h"
#include "camera.h"
#include "model_obstacle.h"
#include "object3D.h"
#include "boss.h"

//-----------------------------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CModelManager::CModelManager() :m_nCounter(0), m_nCounterCreate(0), m_nNumCreate(0), m_nCreateInterval(0), m_nNumModel(0), m_nNumCreateModel(0)
{
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CModelManager::~CModelManager()
{
}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CModelManager *CModelManager::Create()
{
	// ポインタクラスを宣言
	CModelManager* pObstacle = new CModelManager;

	if (pObstacle != nullptr)
	{
		// 初期化
		pObstacle->Init();
	}

	return pObstacle;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CModelManager::Init()
{
	// モデル生成までの数値取得
	m_nCounterCreate = GetRandNum(120, 60);

	m_nCreateInterval = 90;

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CModelManager::Uninit()
{
	// 破棄
	Release();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CModelManager::Update()
{
	// ゲームが開始していれば
	if (CManager::GetManager()->GetGame()->GetStart() == true)
	{
		// カウンター加算
		m_nCounter++;

		// カウンターが生成までの数値以上になったら
		if (m_nCounterCreate <= m_nCounter)
		{
			// カウンターリセット
			m_nCounter = 0;
			// モデル生成までの数値取得
			m_nCounterCreate = GetRandNum(240, m_nCreateInterval);
			// 生成するオブジェクト数を取得
			m_nNumCreate = GetRandNum(3 + m_nNumCreateModel, 1);

			m_nCreateInterval--;

			if (m_nCreateInterval <= 0)
			{
				m_nCreateInterval = 1;
			}

			m_nNumModel++;

			if (m_nNumModel >= 5)
			{
				m_nNumCreateModel++;

				// ボスの移動速度を早める
				CManager::GetManager()->GetGame()->GetEnemyBoss()->SetAdd(0.002f);

				if (m_nNumCreateModel > 8)
				{
					m_nNumCreateModel = 8;
				}
			}

			// カメラ情報の取得
			D3DXVECTOR3 posCamera = CManager::GetManager()->GetGame()->GetCamera()->GetPosV();

			//木を生成
			CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, posCamera.z + 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_1")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, posCamera.z - 200.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_2")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, posCamera.z - 450.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_3")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, posCamera.z - 600.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_4")->SetCollision(true);

			CObstacle::Create(D3DXVECTOR3(-270.0f, 0.0f, posCamera.z + 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_1")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(-270.0f, 0.0f, posCamera.z - 200.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_2")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(-270.0f, 0.0f, posCamera.z - 450.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_3")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(-270.0f, 0.0f, posCamera.z - 600.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_4")->SetCollision(true);

			CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, posCamera.z + 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_1")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, posCamera.z - 200.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_2")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, posCamera.z - 450.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_3")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, posCamera.z - 600.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_4")->SetCollision(true);

			CObstacle::Create(D3DXVECTOR3(270.0f, 0.0f, posCamera.z + 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_1")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(270.0f, 0.0f, posCamera.z - 200.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_2")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(270.0f, 0.0f, posCamera.z - 450.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_3")->SetCollision(true);
			CObstacle::Create(D3DXVECTOR3(270.0f, 0.0f, posCamera.z - 600.0f * m_nNumCreate), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WOOD_4")->SetCollision(true);

			for (int nCntModel = 0; nCntModel < m_nNumCreate; nCntModel++)
			{
				//2列木生成
				float fRand = (float)GetRandNum(180, -180);

				// 障害物生成
				switch (GetRandNum(2, 0))
				{
				case 0:
					CObstacle::Create(D3DXVECTOR3(fRand, 0.0f, posCamera.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_ROCKICE_SMALL");
					break;

				case 1:
					CObstacle::Create(D3DXVECTOR3(fRand, 0.0f, posCamera.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_ROCKICE_NORMAL");
					break;

				case 2:
					CObstacle::Create(D3DXVECTOR3(fRand, 0.0f, posCamera.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_ROCKICE_BIG");
					break;

				default:
					break;
				}
			}

			// 板ポリ生成
			//CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, posCamera.z), D3DXVECTOR2(2000.0f, 2000.0f));
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CModelManager::Draw()
{
}

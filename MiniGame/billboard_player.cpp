//========================================================
//
// ビルボード処理 [billboard_player.cpp]
// Author : SHUGO KURODA
//
//========================================================
#include "manager.h"
#include "renderer.h"
#include "object3D.h"
#include "billboard_player.h"

#include "texture.h"

//========================================================
// マクロ定義
//========================================================
#define SIZE	(D3DXVECTOR2(200.0f,200.0f))

//========================================================
// コンストラクタ
//========================================================
CBillboardPlayer::CBillboardPlayer() :m_pPosParent(nullptr)
{
	//オブジェクトの種類設定
	SetType(EObject::OBJ_PLAYER);
}

//========================================================
// デストラクタ
//========================================================
CBillboardPlayer::~CBillboardPlayer()
{
}

//========================================================
// 生成
// const D3DXVECTOR3& ParentPos → 追従対象
//========================================================
CBillboardPlayer * CBillboardPlayer::Create(D3DXVECTOR3* pParentPos, const char* name)
{
	//インスタンス生成
	CBillboardPlayer *pBillboard = new CBillboardPlayer;

	// 追従対象の位置設定
	pBillboard->m_pPosParent = pParentPos;

	// 初期化
	pBillboard->Init();

	// テクスチャの割り当て
	pBillboard->BindTexture(CManager::GetManager()->GetTexture()->GetTexture(name));

	return pBillboard;
}

//========================================================
// 初期化
//========================================================
HRESULT CBillboardPlayer::Init()
{
	// 位置の設定
	CBillboard::SetPosition(D3DXVECTOR3(m_pPosParent->x, m_pPosParent->y + 200.0f, m_pPosParent->z));

	// サイズの設定
	CBillboard::SetSize(SIZE);

	// 初期化
	CBillboard::Init();

	return S_OK;
}

//========================================================
// 破棄
//========================================================
void CBillboardPlayer::Uninit()
{
	CBillboard::Uninit();
}

//========================================================
// 更新
//========================================================
void CBillboardPlayer::Update()
{
	// 位置の設定
	CBillboard::SetPosition(D3DXVECTOR3(m_pPosParent->x, m_pPosParent->y + 200.0f, m_pPosParent->z));
}

//========================================================
// 描画
//========================================================
void CBillboardPlayer::Draw()
{
	CBillboard::Draw();
}

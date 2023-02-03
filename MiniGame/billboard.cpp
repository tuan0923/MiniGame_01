//========================================================
//
// ビルボード処理 [billboard.cpp]
// Author : SHUGO KURODA
//
//========================================================
#include "manager.h"
#include "renderer.h"
#include "object3D.h"
#include "billboard.h"

#include "texture.h"

//========================================================
// マクロ定義
//========================================================
#define BILLBOARD_SIZE (10)												//ビルボードのサイズ

//========================================================
// コンストラクタ
//========================================================
CBillboard::CBillboard()
{
}

//========================================================
// デストラクタ
//========================================================
CBillboard::~CBillboard()
{
}

//========================================================
// 生成
//========================================================
CBillboard * CBillboard::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const D3DXVECTOR3& rot, const char* name)
{
	//インスタンス生成
	CBillboard *pBillboard = new CBillboard;

	// 位置設定
	pBillboard->SetPosition(pos);

	// 角度設定
	pBillboard->SetRotation(rot);

	// サイズ設定
	pBillboard->SetSize(size);

	// 初期化
	pBillboard->Init();

	// テクスチャの割り当て
	pBillboard->BindTexture(CManager::GetManager()->GetTexture()->GetTexture(name));

	return pBillboard;
}

//========================================================
// 初期化
//========================================================
HRESULT CBillboard::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CObject3D::VERTEX_3D) * CObject3D::MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		CObject3D::FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報ポインタを宣言
	CObject3D::VERTEX_3D *pVtx = nullptr;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//各頂点位置の設定
	pVtx[0].pos.x = m_pos.x + sinf(-D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(-D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//各頂点の法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//各頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//========================================================
// 破棄
//========================================================
void CBillboard::Uninit()
{
	//頂点バッファの解放
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// オブジェクトの破棄
	Release();
}

//========================================================
// 更新
//========================================================
void CBillboard::Update()
{
}

//========================================================
// 描画
//========================================================
void CBillboard::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
	// 計算用マトリックス
	D3DXMATRIX mtxTrans, mtxRot, mtxView;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zバッファ法の有効化
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスの設定
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject3D::VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(CObject3D::FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ビルボードの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファ法を有効に戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//カメラを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// テクスチャを戻す
	pDevice->SetTexture(0, NULL);
}

//========================================================
// サイズの設定
//========================================================
void CBillboard::SetSize(D3DXVECTOR2 size)
{
	//大きさの設定
	m_size = size;
	//対角線の長さを算出
	m_fLength = sqrtf(size.x * size.x + size.y * size.y) / 2.0f;
	//対角線の角度を算出する
	m_fAngle = atan2f(size.x, size.y);
}

//===================================================================
//
//		ポリゴン処理のヘッダー[polygon.h]
//		Author:SHUGO KURODA
//
//===================================================================
#ifndef _POLYGON_H_			//このマクロ定義がされなかったら
#define _POLYGON_H_			//2重インクルード防止のマクロ定義

#include "object.h"

//======================================================
//	マクロ定義
//======================================================
#define POLYGON_SIZE	(2000.0f)	//ポリゴンのサイズ

//======================================================
//	クラス宣言
//======================================================
class CObject3D : public CObject
{
public:
	// 頂点フォーマット
	static const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//座標・法線・カラー・テクスチャ;
	// 頂点の数
	static const int MAX_VERTEX = 4;

	// 頂点データ
	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;		//頂点座標
		D3DXVECTOR3 nor;		//法線ベクトル
		D3DCOLOR col;			//頂点カラー
		D3DXVECTOR2 tex;		//テクスチャ座標
	};

	CObject3D();
	~CObject3D() override;

	static CObject3D *Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	D3DXVECTOR3 GetPosition() { return m_pos; }
	D3DXVECTOR3 GetRotation() { return m_rot; }
	D3DXVECTOR2 GetSize() { return m_size; }

	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetSize(const D3DXVECTOR2& size) { m_size = size; }
	void SetStop(const bool& bStop) { m_bStop = bStop; }

	// テクスチャの設定
	void BindTexture(LPDIRECT3DTEXTURE9 Texture) { m_pTexture = Texture; }

private:
	// 頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;
	// テクスチャへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
	// 位置
	D3DXVECTOR3 m_pos;
	// 向き
	D3DXVECTOR3 m_rot;
	// サイズ
	D3DXVECTOR2 m_size;
	// ワールドマトリックス
	D3DXMATRIX m_mtxWorld;

	// 破棄カウンター
	int m_nDel;
	bool m_bStop;
};

#endif
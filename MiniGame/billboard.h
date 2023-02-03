//========================================================
//
// ビルボード処理 [billboard.cpp]
// Author : SHUGO KURODA
//
//========================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "object.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBillboard : public CObject
{
public:
	//メンバ関数
	CBillboard();						//コンストラクタ
	virtual ~CBillboard() override;		//デストラクタ

	// 生成
	static CBillboard* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const D3DXVECTOR3& rot, const char* name);

	// 初期化
	virtual HRESULT Init() override;
	// 終了
	virtual void Uninit() override;
	// 更新
	virtual void Update() override;
	// 描画
	virtual void Draw() override;

	// 位置設定
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	// 角度設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	// サイズ設定
	void SetSize(D3DXVECTOR2 size);
	// 位置取得
	D3DXVECTOR3 GetPosition() { return m_pos; }
	// 角度取得
	D3DXVECTOR3 GetRotation() { return m_rot; }
	// モデルの設定
	void BindTexture(LPDIRECT3DTEXTURE9 texture) { m_pTexture = texture; }

private:
	//テクスチャへのポインター
	LPDIRECT3DTEXTURE9 m_pTexture;
	//ビルボードの頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	//位置
	D3DXVECTOR3 m_pos;
	//回転
	D3DXVECTOR3 m_rot;
	//サイズ
	D3DXVECTOR2 m_size;
	//対角線の長さ
	float m_fLength;
	//対角線の角度
	float m_fAngle;
	//ワールドマトリックス
	D3DXMATRIX m_mtxWorld;
};

#endif 

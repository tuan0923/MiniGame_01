//========================================================
//
// ビルボード処理 [billboard_player.cpp]
// Author : SHUGO KURODA
//
//========================================================
#ifndef _BILLBOARD_PLAYER_H_
#define _BILLBOARD_PLAYER_H_

#include "billboard.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBillboardPlayer : public CBillboard
{
public:
	//メンバ関数
	CBillboardPlayer();						//コンストラクタ
	virtual ~CBillboardPlayer() override;	//デストラクタ

	// 生成
	static CBillboardPlayer* Create(D3DXVECTOR3* ParentPos, const char* name);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// 追従対象の位置
	D3DXVECTOR3 *m_pPosParent;
};

#endif 

//-------------------------------------------
//
// ロゴの情報[logo_flash.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _LOGO_FLASH_H_
#define _LOGO_FLASH_H_

//-------------------------------------------
// インクルード
//-------------------------------------------
#include "logo.h"

//-------------------------------------------
// ロゴクラス
//-------------------------------------------
class CLogoFlash : public CLogo
{
private:
	// 動き方の種類
	enum EAnim
	{
		ANIM_NONE = 0,
		ANIM_ADD,
		ANIM_SUB,
	};

public:
	// コンストラクタ
	CLogoFlash();
	// デストラクタ
	~CLogoFlash() override;

	// 生成
	static CLogoFlash* Create(const D3DXVECTOR2& size, const char* name, const int& nCount);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 破棄時の画面遷移判定の設定
	void SetSceneChange(bool bScene) { m_bSceneChange = bScene; }

	// 動き方の設定
	void Pattern();

	// メンバ変数
private:
	// 動き方の種類
	EAnim m_anim;
	// 破棄時に画面遷移するかどうか
	bool m_bSceneChange;
};

#endif		// _LOGO_FLASH_H_

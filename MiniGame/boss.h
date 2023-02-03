//===================================================================
//
//	敵ボスの処理[boss.h]
//	Author : SHUGO KURODA
//
//===================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "motion.h"

//*******************************************************************
//	前方宣言
//*******************************************************************
class CPlayer;

//*******************************************************************
//	敵クラスの定義
//*******************************************************************
class CBoss : public CMotion
{
public:		//定数
	// 幅
	static const float SIZE_WIDTH;
	// 高さ
	static const float SIZE_HEIGHT;
	// U座標の最大分割数
	static const int DIVISION_U;
	// V座標の最大分割数
	static const int DIVISION_V;
private:
	// 寿命
	static const int LIFE;
	// 攻撃前の予備動作間隔
	static const int RUSH_OPERATION;

public:
	//状態
	enum STATE
	{
		STATE_NORMAL = 0,	//通常
		STATE_DAMAGE,		//ダメージ状態
		STATE_MAX
	};

	//行動パターン
	enum PATTERN
	{
		PATTERN_ENTRY = 0,	// 登場
		PATTERN_NORMAL,		// 通常
		PATTERN_RUN,		// 移動
		PATTERN_SNOWBALL,	// 雪玉投擲攻撃
		PATTERN_POW,		// 地震攻撃
		PATTERN_BARRAGE,	// 弾幕攻撃
		PATTERN_DIE,		// 死亡
		PATTERN_MAX
	};

	CBoss();
	~CBoss() override;

	//メンバ関数
	static CBoss *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);		//インスタンス生成処理

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	bool Collision(D3DXVECTOR3 posStart);
	bool Pattern(D3DXVECTOR3& pos);
	void ChangeSize(D3DXVECTOR2 *pSize, const float& fSize);
	void StateReset();

	PATTERN GetPattern() { return m_pattern; }
	void SetPattern(PATTERN pattern) { m_pattern = pattern; }
	void SetAdd(const float& fAdd) { m_fAdd += fAdd; }

private:
	// 移動量
	D3DXVECTOR3 m_move;
	// 行動パターン
	PATTERN m_pattern;
	// 行動変化までのカウンター
	int8_t m_nCounter;			
	// 突進前の予備動作の間隔
	int m_nCountOperation;
	// 突進攻撃、弾発射の角度
	float m_fAttackRot;
	// 大きさの変更
	bool m_bSizeChange;
	// オブジェクトを生成した数
	int m_nCountObject;

	// 加速度
	float m_fAdd;
};

#endif	// _BOSS_H_

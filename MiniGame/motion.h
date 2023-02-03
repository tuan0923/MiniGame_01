//===================================================================
//
//	モデル処理のヘッダー[motion.h]
//	Author : SHUGO KURODA
//
//===================================================================
#ifndef _MOTION_H_			//このマクロ定義がされなかったら
#define _MOTION_H_			//2重インクルード防止のマクロ定義

#include "object.h"
#include "motion_data.h"

//=============================================================================
// クラス定義
//=============================================================================
class CMotion : public CObject
{
	// 構造体
private:
	//モーション番号情報
	struct AnimIdx
	{
		int nFrame;				// 現在のフレーム数
		int nKeySetIdx;			// 再生中のキーセット番号
		int nMotionIdx;			// 再生中のモーション番号
	};

	// メンバ関数
public:
	CMotion();		// コンストラクタ
	virtual ~CMotion() override;	// デストラクタ

	// 生成
	static CMotion* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);

	// 初期化
	virtual HRESULT Init() override;
	// 終了
	virtual void Uninit() override;
	// 更新
	virtual void Update() override;
	// 描画
	virtual void Draw() override;
	// 角度の正規化
	void NormalizeRot();

	// 位置設定
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	// 角度設定
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
	// 目的の角度設定
	void SetRotDest(const D3DXVECTOR3& rotDest) { m_rotDest = rotDest; }
	// 全体の色設定
	void SetColor(const D3DXCOLOR& col) { m_col = col; }
	// 位置設定
	void SetSizeMax(const D3DXVECTOR3& size) { m_vtxMax = size; }
	// 当たり判定の設定
	void SetCollision(const float& fLength) { m_fLength = fLength; }
	// 位置取得
	D3DXVECTOR3 GetPosition() { return m_pos; }
	// 位置取得
	D3DXVECTOR3 *GetpPosition() { return &m_pos; }
	// 角度取得
	D3DXVECTOR3 GetRotation() { return m_rot; }
	// 最大サイズ取得
	D3DXVECTOR3 GetSizeMax() { return m_vtxMax; }
	// 最小サイズ取得
	D3DXVECTOR3 GetSizeMin() { return m_vtxMin; }
	// モーション情報の取得
	ModelMotion GetMotion() { return m_motion; }
	// モーション切り替え情報の取得
	bool GetChange() { return m_bChange; }
	// モーション情報の設定
	void BindMotion(const ModelMotion& motion) { m_motion = motion; }

protected:
	// モーション再生
	bool Motion();
	// モーション設定
	void Set(const int& nNum);

private:
	// モーション変更
	void Change(const int& nMotion, const int& nKey);

	// メンバ変数
private:
	//モーション情報
	ModelMotion m_motion;
	// 現在のモーション番号情報
	AnimIdx m_animIdx;
	// 位置
	D3DXVECTOR3 m_pos;
	// 回転
	D3DXVECTOR3 m_rot;
	// 目的の角度
	D3DXVECTOR3 m_rotDest;
	// モデルの最大サイズ,最小サイズ
	D3DXVECTOR3 m_vtxMax, m_vtxMin;
	// モデルの当たり判定大きさ
	float m_fLength;
	// 全体の色
	D3DXCOLOR m_col;
	// ワールドマトリックス
	D3DXMATRIX m_mtxWorld;
	// モーション切り替え中かどうか
	bool m_bChange;
};

#endif		// _MOTION_H_

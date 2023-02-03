//===================================================================
//
//		カメラ処理のヘッダー[camera.h]
//		Author:SHUGO KURODA
//
//===================================================================
#ifndef _CAMERA_H_			//このマクロ定義がされなかったら
#define _CAMERA_H_			//2重インクルード防止のマクロ定義

#include "object.h"

//======================================================
//	カメラの構造体
//======================================================
class CCamera : public CObject
{
public:
	CCamera();
	~CCamera() override;

	static CCamera *Create(const D3DXVECTOR3& posV, const D3DXVECTOR3& posR, const D3DXVECTOR3& rot, float fNear);	//インスタンス生成処理

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// 視点位置の設定
	void SetPosV(D3DXVECTOR3 posV)
	{
		m_posV = posV;
		m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//注視点までの距離
		D3DXVECTOR3 Distance = D3DXVECTOR3((m_posV.x + m_posR.x), (m_posV.y + m_posR.y), (m_posV.z + m_posR.z));

		//視点から注視点までの距離を初期化する
		m_fDistance = sqrtf(Distance.x * Distance.x + Distance.z * Distance.z);
		m_fDistance = sqrtf(Distance.y * Distance.y + m_fDistance * m_fDistance);
	}

	// 視点位置の設定
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }

	void SetTrackingSize(D3DXVECTOR2 size) { m_pTrackingSize = size; }

	void SetDistance(float fDistance) { m_fDistance = fDistance; }
		
	// 視点位置の取得
	D3DXVECTOR3 GetPosV() { return m_posV; }
	// 注視点位置の取得
	D3DXVECTOR3 GetPosR() { return m_posR; }
	// 角度の取得
	D3DXVECTOR3 GetRotation() { return m_rot; }

	// 追従対象の設定
	void SetPosTracking(D3DXVECTOR3 *pPosDest) { m_pPosTracking = pPosDest; }

private:
	D3DXVECTOR3 m_move;				// 移動量
	D3DXVECTOR3 m_posV;				// 視点
	D3DXVECTOR3 m_posR;				// 注視点
	D3DXVECTOR3 m_vecU;				// 上方向ベクトル
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 *m_pPosTracking;	// 追従対象の位置
	D3DXVECTOR2 m_pTrackingSize;	// 
	D3DXVECTOR3 m_posVDest;			// 目的の視点
	D3DXVECTOR3 m_posRDest;			// 目的の注視点
	float m_fDistance;				// 視点から注視点までの距離
	float m_fNear;					// 視野角
	D3DXMATRIX m_mtxProjection;		// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス
};

#endif

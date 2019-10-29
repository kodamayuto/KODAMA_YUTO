//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//===================================================================
// クラスの定義
//===================================================================

class CCamera
{
public:
	CCamera();
	~CCamera();


	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	D3DXVECTOR3 GetRotation(void) { return m_rot; };
private:
	D3DXVECTOR3 m_posV;	//視点
	D3DXVECTOR3 m_posVdest;
	D3DXVECTOR3 m_posR;	//注視点
	D3DXVECTOR3 m_posRdest;
	D3DXVECTOR3 m_vecU;	//上方向ベクトル
	D3DXVECTOR3 m_rot;	//角度
	D3DXMATRIX m_mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX m_mtxView;	//ビューマトリックス

	float m_fCameraAngle;	//カメラ角

};
#endif // !_CAMERA_H_

//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ANGLE_MOVE  (0.03f) //カメラ角度の移動量
#define CAMERA_MOVE (1.5f)  //カメラの移動量

#define CAMERA_POS_INTERVAL (20.0f)			//カメラの注視点の位置
#define CAMERA_POSV_COEFFICIENT (0.20f);	//カメラ視点の係数
#define CAMERA_POSR_COEFFICIENT (0.18f);	//カメラ注視点の係数

#define CAMERA_ROTMOVE_INTERVAL (60)		//視点移動の待機時間
//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;	 //視点
	D3DXVECTOR3 posR;	 //注視点
	D3DXVECTOR3 posVDest;//目的の視点
	D3DXVECTOR3 posRDest;//目的の注視点
	D3DXVECTOR3 vecU;	 //上方向ベクトル
	D3DXMATRIX mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX mtxView;	 //ビューマトリックス
	D3DXVECTOR3 rot;	 //角度
	D3DXVECTOR3 rotmove; //角移動量
	int nRotmoveCount;	 //視点移動の待機時間
	float fLength;		 //距離	
}Camera;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);

#endif

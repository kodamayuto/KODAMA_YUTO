//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "camera.h"
#include "input.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_camera;	//カメラの情報

float g_fCameraAngle;

bool g_bCameraRotFollow = false;	//カメラの回り込みフラグ
//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
		g_camera.posV = D3DXVECTOR3(0.0f, 70.0f, -180.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.nRotmoveCount = 0;
		g_camera.fLength = g_camera.posV.z - g_camera.posR.z;
		g_fCameraAngle = 37.0f;

		g_bCameraRotFollow = false;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	if (GetMode() == MODE_TITLE)
	{
		g_camera.rot.y -= ANGLE_MOVE /5.0f;
		g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

		g_camera.posV = D3DXVECTOR3(g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength,
			g_camera.posV.y,
			g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength);

	}
	else if (GetMode() == MODE_RANKING)
	{
		g_camera.rot.y += ANGLE_MOVE / 5.0f;
		g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

		g_camera.posV = D3DXVECTOR3(g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength,
			g_camera.posV.y,
			g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength);


	}
	else if (GetMode() == MODE_GAME)
	{

		PLAYER *pPlayer;

		pPlayer = GetPlayer();
		//カメラ回り込みのon/off
		if (GetKeyboardTrigger(DIK_M) == true)
		{
			g_bCameraRotFollow = g_bCameraRotFollow ? false : true;
		}

		//カメラ回り込み
		if (pPlayer->move.x <= 0.1f &&
			pPlayer->move.x >= -0.1f&&
			pPlayer->move.z <= 0.1f &&
			pPlayer->move.z >= -0.1f&&
			GetKeyboardPress(DIK_LEFT) == false &&
			GetKeyboardPress(DIK_RIGHT) == false &&
			g_bCameraRotFollow == true)
		{

			g_camera.nRotmoveCount++;
			if (g_camera.nRotmoveCount > CAMERA_ROTMOVE_INTERVAL)
			{
				//回転量の計算
				g_camera.rotmove.y = (pPlayer->rot.y + D3DX_PI) - g_camera.rot.y;
				g_camera.rotmove.y = RotOverwhelming(g_camera.rotmove.y);

				//角度に回転量に係数を掛けた値を代入
				g_camera.rot.y += g_camera.rotmove.y * 0.01f;
				g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

				//カメラの注視点・視点の計算
				g_camera.posRDest = pPlayer->pos;
				g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.006f;
				//g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.035f;
				g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.004f;

				g_camera.posVDest.x = g_camera.posRDest.x + sinf(g_camera.rot.y) * g_camera.fLength;
				g_camera.posVDest.y = g_camera.posV.y;
				g_camera.posVDest.z = g_camera.posRDest.z + cosf(g_camera.rot.y) * g_camera.fLength;

				g_camera.posV += (g_camera.posVDest - g_camera.posV) * CAMERA_POSV_COEFFICIENT;
			}
		}
		else
		{
			g_camera.nRotmoveCount = 0;

			g_camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * CAMERA_POS_INTERVAL;
			g_camera.posRDest.y = g_camera.posR.y;
			g_camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * CAMERA_POS_INTERVAL;

			g_camera.posR += (g_camera.posRDest - g_camera.posR) * CAMERA_POSR_COEFFICIENT;

			g_camera.posVDest.x = g_camera.posRDest.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.y = g_camera.posV.y;
			g_camera.posVDest.z = g_camera.posRDest.z + cosf(g_camera.rot.y) * g_camera.fLength;

			g_camera.posV += (g_camera.posVDest - g_camera.posV) * CAMERA_POSV_COEFFICIENT;
		}


		//視点移動
		if (GetKeyboardPress(DIK_LEFT)== true)//時計回り
		{
			g_camera.rot.y -= ANGLE_MOVE;
		}
		if (GetKeyboardPress(DIK_RIGHT) == true)//反時計回り
		{
			g_camera.rot.y += ANGLE_MOVE;
		}
		g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

		g_camera.posV = D3DXVECTOR3(g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength,
			g_camera.posV.y,
			g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength);

		//カメラ角の拡縮
		if (GetKeyboardPress(DIK_0) == true)
		{
			g_fCameraAngle -= 1.0f;
		}
		if (GetKeyboardPress(DIK_9) == true)
		{
			g_fCameraAngle += 1.0f;
		}
	}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(g_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		4000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,&g_camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
					   &g_camera.posV,
					   &g_camera.posR,
		               &g_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}


//=============================================================================
//	カメラの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}
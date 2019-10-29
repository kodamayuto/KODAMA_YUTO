//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "main.h"
#include "modeselect.h"
#include "player.h"
#include "fade.h"
#include "game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_ANGEL_VIEW  (45.0f)    // カメラの画角
#define CAMERA_MOVE        (20.0f)     // カメラの移動量
#define AROUND_SPEED       (0.02f)    // 回り込み速度初期値
#define AROUND_TIME        (50)       // 回り込み待ち時間初期値

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_camera;  // カメラの情報
int g_Timer;	  //タイマー

				  //=============================================================================
				  // カメラの初期化処理
				  //=============================================================================
void InitCamera(void)
{
	MODE pMode;
	pMode = GetMode();

	switch (pMode)
	{
	case MODE_TITLE:
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, -1700.0f);  // 現在の視点を初期化
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // 現在の注視点を初期化
		g_camera.fLength = 1000.0f;                           // 距離を初期化

		break;
	case MODE_SELECT:
		g_camera.posV = D3DXVECTOR3(0.0f, 40.0f, -200.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 40.0f, 0.0f);       // 現在の注視点を初期化
		g_camera.fLength = 400.0f;
		break;
	case MODE_TUTORIAL:
		g_camera.posV = D3DXVECTOR3(0.0f, 265.0f, -1000.0f);  // 現在の視点を初期化
		g_camera.posR = D3DXVECTOR3(0.0f, 228.0f, 0.0f);       // 現在の注視点を初期化
		g_camera.fLength = 1000.0f;								// 距離を初期化

		break;
	case MODE_GAME:
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, 0.0f);  // 現在の視点を初期化
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // 現在の注視点を初期化
		g_camera.fLength = 1000.0f;                           // 距離を初期化
		break;
	case MODE_CLEAR:
		g_camera.posV = D3DXVECTOR3(0.0f, 70.0f, -1700.0f);  // 現在の視点を初期化
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // 現在の注視点を初期化
		g_camera.fLength = 1000.0f;								// 距離を初期化
		break;
	case MODE_OVER:
		g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -1700.0f);  // 現在の視点を初期化
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // 現在の注視点を初期化
		g_camera.fLength = 1000.0f;								// 距離を初期化
		break;
	case MODE_RANKING:
		g_camera.posV = D3DXVECTOR3(0.0f, 20.0f, -100.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.fLength = g_camera.posV.z - g_camera.posR.z;

		break;
	}

	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 目的の視点を初期化
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 目的の注視点を初期化
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       // ベクトルを初期化
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // 現在の向きを初期化
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 目的の向きを初期化
	g_camera.state = CAMERASTATE_NORMAL;                 // 通常の状態に
	g_camera.fWaraparoundSpeed = AROUND_SPEED;           // 回り込み速度を初期化
	g_camera.nWaraparoundTime = AROUND_TIME;             // 回り込み待ち時間を初期化
	g_camera.nCounterTime = 0;                           // 待ち時間カウンターを初期化
	g_camera.posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 加える分の視点座標を初期化
	g_camera.posRAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 加える分の注視点座標を初期化

	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	g_Timer = 0;
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
	D3DXVECTOR3 MasuPos;
	float masuRot;

	Player *pPlayer;
	pPlayer = GetPlayer();

	switch (GetMode())
	{
	case MODE_TITLE:
		g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_MOVE / 5;
		g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_MOVE / 5;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

		break;
	case MODE_SELECT:
		g_camera.SelectModelpos[0] = D3DXVECTOR3(-200.0f, 0.0f, 200.0f);
		g_camera.SelectModelpos[1] = D3DXVECTOR3(200.0f, 0.0f, 200.0f);
		g_camera.SelectModelpos[2] = D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
		g_camera.SelectModelpos[3] = D3DXVECTOR3(200.0f, 0.0f, -200.0f);
		g_camera.fLength = -300.0f;

		g_camera.posRDest = g_camera.SelectModelpos[GetNumber()] - g_camera.posR;

		g_camera.posR.x += g_camera.posRDest.x * 0.04f;
		g_camera.posR.z += g_camera.posRDest.z * 0.04f;

		g_camera.posVDest.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = g_camera.posV.y;
		g_camera.posVDest.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength;

		g_camera.posV += (g_camera.posVDest - g_camera.posV) * 0.86f;
		break;
	case MODE_GAME:
		g_camera.fLength = -500.0f;                           // 距離を初期化

		switch (GetTurnState())
		{
		case TURNSTATE_DICE:
			MasuPos = PlayerDistance();

			masuRot = atan2f(MasuPos.x - g_camera.posR.x, MasuPos.z - g_camera.posR.z);
			//回転量の計算
			g_camera.rotDest.y = (masuRot)-g_camera.rot.y;
			g_camera.rotDest.y = RotOverwhelming(g_camera.rotDest.y);

			//角度に回転量に係数を掛けた値を代入
			g_camera.rot.y += g_camera.rotDest.y * 0.01f;
			g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

			pPlayer->rot.y = g_camera.rot.y + D3DX_PI;

			//カメラの注視点・視点の計算
			g_camera.posRDest = pPlayer->pos;
			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.166f;
			g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.166f;

			g_camera.posVDest.x = g_camera.posRDest.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.y = g_camera.posRDest.y + 300.0f;
			g_camera.posVDest.z = g_camera.posRDest.z + cosf(g_camera.rot.y) * g_camera.fLength;

			g_camera.posV += (g_camera.posVDest - g_camera.posV) * 0.15f;

			break;

		case TURNSTATE_MAP:
			//平行移動
			if (GetKeyboardPress(DIK_D) == true || GetJoyPadPress(DIJS_BUTTON_20, GetIdxPlayer()) == true || GetJoyPadPress(DIJS_BUTTON_12, GetIdxPlayer()) == true)//→
			{
				g_camera.posV.x += sinf((D3DX_PI * 0.5f) + g_camera.rot.y) * CAMERA_MOVE;
				g_camera.posV.z += cosf((D3DX_PI * 0.5f) + g_camera.rot.y) * CAMERA_MOVE;
			}
			if (GetKeyboardPress(DIK_A) == true || GetJoyPadPress(DIJS_BUTTON_21, GetIdxPlayer()) == true || GetJoyPadPress(DIJS_BUTTON_13, GetIdxPlayer()) == true)//←
			{
				g_camera.posV.x += sinf((D3DX_PI * -0.5f) + g_camera.rot.y) * CAMERA_MOVE;
				g_camera.posV.z += cosf((D3DX_PI * -0.5f) + g_camera.rot.y) * CAMERA_MOVE;
			}
			if (GetKeyboardPress(DIK_W) == true || GetJoyPadPress(DIJS_BUTTON_18, GetIdxPlayer()) == true || GetJoyPadPress(DIJS_BUTTON_10, GetIdxPlayer()) == true)//↑
			{
				g_camera.posV.x += sinf((D3DX_PI * 0.0f) + g_camera.rot.y) * CAMERA_MOVE;
				g_camera.posV.z += cosf((D3DX_PI * 0.0f) + g_camera.rot.y) * CAMERA_MOVE;
			}
			if (GetKeyboardPress(DIK_S) == true || GetJoyPadPress(DIJS_BUTTON_19, GetIdxPlayer()) == true || GetJoyPadPress(DIJS_BUTTON_11, GetIdxPlayer()) == true)//↓
			{
				g_camera.posV.x += sinf((D3DX_PI)+g_camera.rot.y) * CAMERA_MOVE;
				g_camera.posV.z += cosf((D3DX_PI)+g_camera.rot.y) * CAMERA_MOVE;

			}

			g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * g_camera.fLength;

			break;
		default:

			//回転量の計算
			g_camera.rotDest.y = (pPlayer->rot.y + D3DX_PI) - g_camera.rot.y;
			g_camera.rotDest.y = RotOverwhelming(g_camera.rotDest.y);

			//角度に回転量に係数を掛けた値を代入
			g_camera.rot.y += g_camera.rotDest.y * 0.01f;
			g_camera.rot.y = RotOverwhelming(g_camera.rot.y);

			//カメラの注視点・視点の計算
			g_camera.posRDest = pPlayer->pos;
			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.166f;
			g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.166f;

			g_camera.posVDest.x = g_camera.posRDest.x + sinf(g_camera.rot.y) * g_camera.fLength;
			g_camera.posVDest.y = g_camera.posRDest.y + 300.0f;
			g_camera.posVDest.z = g_camera.posRDest.z + cosf(g_camera.rot.y) * g_camera.fLength;

			g_camera.posV += (g_camera.posVDest - g_camera.posV) * 0.15f;


			break;

		}

		break;
	case MODE_RANKING:
		break;
	}
	// カメラ操作の処理
#if 0
	//-----------------
	// 視点移動
	//-----------------
	if (GetKeyboardPress(DIK_LEFT) == true)
	{// Aキーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{// 同時にWキーが押された
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// 同時にSキーが押された
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// 同時に何も押されていない
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{// Dキーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{// 同時にWキーが押された
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// 同時にSキーが押された
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// 同時に何も押されていない
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{// Wキーが押された
		g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_MOVE;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{// Sキーが押された
		g_camera.posV.x -= sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z -= cosf(g_camera.rot.y) * CAMERA_MOVE;
	}
	//-----------------
	// 視点旋回
	//-----------------
	if (GetKeyboardPress(DIK_Z) == true)
	{// Zキーが押された
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y <= -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;

	}
	if (GetKeyboardPress(DIK_C) == true)
	{// Cキーが押された
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}
	//-----------------
	// 注視点旋回
	//-----------------
	if (GetKeyboardPress(DIK_Q) == true)
	{// Qキーが押された
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
	}
	if (GetKeyboardPress(DIK_E) == true)
	{// Eキーが押された
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
	}
	//-----------------
	// カメラリセット
	//-----------------
	if (GetKeyboardPress(DIK_G) == true)
	{// SPACEキーが押された
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, -250.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 00.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//-----------------
	// 注視点上昇下降
	//-----------------
	if (GetKeyboardPress(DIK_T) == true)
	{// Tキーが押された
		g_camera.posR.y += 1.5f;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{// Bキーが押された
		g_camera.posR.y -= 1.5f;
	}
	//-----------------
	// 視点上昇下降
	//-----------------
	if (GetKeyboardPress(DIK_Y) == true)
	{// Yキーが押された
		g_camera.posV.y += 1.5f;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{// Nキーが押された
		g_camera.posV.y -= 1.5f;
	}

	//------------------------
	// ズームイン ズームアウト
	//------------------------
	if (GetKeyboardPress(DIK_U) == true)
	{// Uキーが押された
		if (g_camera.fLength >= 100)
		{
			g_camera.fLength -= 0.5f;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}
	if (GetKeyboardPress(DIK_M) == true)
	{// Mキーが押された
		if (g_camera.fLength <= 500)
		{
			g_camera.fLength += 0.5f;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;


	/*Player *pPlayer = GetPlayer();*/  // プレイヤーの取得

										// 視点設定
										//g_camera.posVDest.x = (pPlayer->pos.x + g_camera.posVAdd.x) + sinf(-g_camera.rot.y) * g_camera.fLength;  // 目的の視点を設定
										//g_camera.posVDest.y = (pPlayer->pos.y + g_camera.posVAdd.y) + cosf(D3DX_PI) * -g_camera.fLength / 2;  // 目的の視点を設定
										//g_camera.posVDest.z = (pPlayer->pos.z + g_camera.posVAdd.z) + cosf(-g_camera.rot.y) * g_camera.fLength;  // 目的の視点を設定

										//// 注視点設定
										//g_camera.posRDest.x = (pPlayer->pos.x + g_camera.posRAdd.x) - sinf(pPlayer->rot.y) * ((pPlayer->move.x * pPlayer->move.x) + (7.0f + 1.5f * (pPlayer->move.x * pPlayer->move.x))); // 目的の注視点を設定
										//g_camera.posRDest.y = (pPlayer->pos.y + g_camera.posRAdd.y) - sinf(pPlayer->rot.y) * ((pPlayer->move.x * pPlayer->move.x) + (7.0f + 1.5f * (pPlayer->move.y * pPlayer->move.y))); // 目的の注視点を設定
										//g_camera.posRDest.z = (pPlayer->pos.z + g_camera.posRAdd.z) - cosf(pPlayer->rot.y) * ((pPlayer->move.x * pPlayer->move.x) + (7.0f + 1.5f * (pPlayer->move.z * pPlayer->move.z))); // 目的の注視点を設定

										//if (pPlayer->state == PLAYERSTATE_NORMAL)
										//{// 通常の状態だったら
										//	g_camera.nCounterTime++;               // カウンターを進める
										//	if (g_camera.nCounterTime >= g_camera.nWaraparoundTime)
										//	{// 回り込み待ち時間が既定の値を超えた
										//		g_camera.rotDest = -pPlayer->rot;  // 目的の向きを設定
										//		g_camera.rotDiff = g_camera.rotDest.y - g_camera.rot.y;  // 目的と現在の向きの差分を計算
										//		if (g_camera.rotDiff > D3DX_PI)
										//		{// 差分がD3DX_PIを超えた
										//			g_camera.rotDiff -= D3DX_PI * 2.0f;
										//		}
										//		if (g_camera.rotDiff < -D3DX_PI)
										//		{// 差分が-D3DX_PIを超えた
										//			g_camera.rotDiff += D3DX_PI * 2.0f;
										//		}

										//		g_camera.rot.y += g_camera.rotDiff * g_camera.fWaraparoundSpeed;  // 現在の向きを目的の向きに移行

										//		if (g_camera.rot.y > D3DX_PI)
										//		{// 現在の向きがD3DX_PIを超えた
										//			g_camera.rot.y -= D3DX_PI * 2.0f;
										//		}
										//		if (g_camera.rot.y < -D3DX_PI)
										//		{// 現在の向きが-D3DX_PIを超えた
										//			g_camera.rot.y += D3DX_PI * 2.0f;
										//		}
										//	}
										//}
										//else if (pPlayer->state != PLAYERSTATE_NORMAL)
										//{// 移動している状態だったら
										//	g_camera.nCounterTime = 0;  // カウンターを0に戻す
										//}

										//-----------------
										// 注視点上昇下降
										//-----------------
	if (GetKeyboardPress(DIK_T) == true)
	{// Tキーが押された
		g_camera.posRAdd.y += 1.5f;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{// Bキーが押された
		g_camera.posRAdd.y -= 1.5f;
	}
	//-----------------
	// 視点上昇下降
	//-----------------
	if (GetKeyboardPress(DIK_Y) == true)
	{// Yキーが押された
		g_camera.posVAdd.y += 1.5f;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{// Nキーが押された
		g_camera.posVAdd.y -= 1.5f;
	}

	//------------------------
	// ズームイン ズームアウト
	//------------------------
	if (GetKeyboardPress(DIK_U) == true)
	{// Uキーが押された
		if (g_camera.fLength >= 60)
		{
			g_camera.fLength -= 2.0f;
		}
	}
	if (GetKeyboardPress(DIK_M) == true)
	{// Mキーが押された
		if (g_camera.fLength <= 350)
		{
			g_camera.fLength += 2.0f;
		}
	}

	//g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.54f; // 現在の視点を設定
	//g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.54f;  // 現在の視点を設定
	//g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.54f; // 現在の視点を設定

	//g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.07f; // 現在の注視点を設定
	//g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.07f; // 現在の注視点を設定
	//g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.07f; // 現在の注視点を設定

	//// 慣性を働かせる
	//g_camera.posV.x += (0.0f - g_camera.posV.x) * 0.25f;
	//g_camera.posV.y += (0.0f - g_camera.posV.y) * 0.25f;
	//g_camera.posV.z += (0.0f - g_camera.posV.z) * 0.25f;
	//g_camera.posR.x += (0.0f - g_camera.posR.x) * (0.00001f);
	//g_camera.posR.y += (0.0f - g_camera.posR.y) * (0.00001f);
	//g_camera.posR.z += (0.0f - g_camera.posR.z) * (0.00001f);
#endif
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
		D3DXToRadian(CAMERA_ANGEL_VIEW),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		50000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

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
// カメラの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}
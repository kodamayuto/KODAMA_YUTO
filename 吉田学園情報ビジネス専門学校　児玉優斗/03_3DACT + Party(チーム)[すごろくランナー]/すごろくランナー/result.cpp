//=============================================================================
//
// 結果画面処理 [result.cpp]
// Author : Niwa Hodaka, Miyu Takahashi
//
//=============================================================================
#include "result.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "meshField.h"
#include "ocean.h"
#include "sky.h"
#include "sound.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_MODELDATA	"data\\MODEL\\wood4.x"			// 読み込むモデルファイル(木)
#define RESULT_MODELDATA2	"data\\MODEL\\lake.x"			// 読み込むモデルファイル(オアシス)

#define RESULT_BOARD1		"data\\MODEL\\board1.x"			// 読み込むモデルファイル(一位看板)
#define RESULT_BOARD2		"data\\MODEL\\board2.x"			// 読み込むモデルファイル(二位看板)
#define RESULT_BOARD3		"data\\MODEL\\resultwood.x"		// 読み込むモデルファイル(リザルト看板)
#define RESULT_BOARD4		"data\\MODEL\\resultwood2.x"	// 読み込むモデルファイル(GAMEOVER看板)

#define MAX_TEXTURE			(4)								// テクスチャの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9* g_pTextureResult[MAX_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		// 頂点バッファへのポインタ
ResultModel g_ResultModel[RESULT_MODELC];				// モデルの情報
D3DXVECTOR3 g_vtxMinResult, g_vtxMaxResult;				// モデルの最小値・最大値
int    g_nCounterResult;								// タイトル画面に遷移するタイミング

//=============================================================================
// 初期化処理
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	MODE g_Mode;

	g_nCounterResult = 0;			// カウンターを0に

									//デバイスの取得
	pDevice = GetDevice();
	g_Mode = GetMode();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// 影の初期化
	InitShadow();

	// メッシュフィールドの初期化処理
	InitMeshField();

	// 海の床の初期化処理
	InitOcean();

	// 空の初期化処理
	InitSky();

	// プレイヤーの初期化処理
	InitPlayer();

	if (g_Mode == MODE_CLEAR)
	{// ゲームクリア

	 // Xファイルの読み込み(一位看板)
		D3DXLoadMeshFromX(RESULT_BOARD1,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_ResultModel[0].pBuffMat,
			NULL,
			&g_ResultModel[0].nNumMat,
			&g_ResultModel[0].pMesh);

		// マテリアル情報からテクスチャを引き出す
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_ResultModel[0].pBuffMat->GetBufferPointer();
		D3DMATERIAL9 *pMatBuff = new D3DMATERIAL9[g_ResultModel[0].nNumMat];
		g_pTextureResult[0] = new LPDIRECT3DTEXTURE9[g_ResultModel[0].nNumMat];

		for (DWORD nCntRanking = 0; nCntRanking < g_ResultModel[0].nNumMat; nCntRanking++)
		{// マテリアル情報を読み込む
			pMatBuff[nCntRanking] = pMat[nCntRanking].MatD3D;

			// テクスチャ情報を初期化
			g_pTextureResult[0][nCntRanking] = NULL;

			// テクスチャ情報を読み込む
			if (pMat[nCntRanking].pTextureFilename != NULL &&
				lstrlen(pMat[nCntRanking].pTextureFilename) > 0)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntRanking].pTextureFilename,
					&g_pTextureResult[0][nCntRanking]);
			}

			// Xファイルの読み込み(二位看板)
			D3DXLoadMeshFromX(RESULT_BOARD2,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[1].pBuffMat,
				NULL,
				&g_ResultModel[1].nNumMat,
				&g_ResultModel[1].pMesh);

			// マテリアル情報からテクスチャを引き出す
			D3DXMATERIAL *pMat1 = (D3DXMATERIAL*)g_ResultModel[1].pBuffMat->GetBufferPointer();
			D3DMATERIAL9 *pMatBuff1 = new D3DMATERIAL9[g_ResultModel[1].nNumMat];
			g_pTextureResult[1] = new LPDIRECT3DTEXTURE9[g_ResultModel[1].nNumMat];

			for (DWORD nCntRanking = 0; nCntRanking < g_ResultModel[1].nNumMat; nCntRanking++)
			{// マテリアル情報を読み込む
				pMatBuff1[nCntRanking] = pMat1[nCntRanking].MatD3D;

				// テクスチャ情報を初期化
				g_pTextureResult[1][nCntRanking] = NULL;

				// テクスチャ情報を読み込む
				if (pMat1[nCntRanking].pTextureFilename != NULL &&
					lstrlen(pMat1[nCntRanking].pTextureFilename) > 0)
				{
					D3DXCreateTextureFromFile(pDevice,
						pMat1[nCntRanking].pTextureFilename,
						&g_pTextureResult[1][nCntRanking]);
				}
			}

			// Xファイルの読み込み(リザルト看板)
			D3DXLoadMeshFromX(RESULT_BOARD3,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[2].pBuffMat,
				NULL,
				&g_ResultModel[2].nNumMat,
				&g_ResultModel[2].pMesh);

			// マテリアル情報からテクスチャを引き出す
			D3DXMATERIAL *pMat2 = (D3DXMATERIAL*)g_ResultModel[2].pBuffMat->GetBufferPointer();
			D3DMATERIAL9 *pMatBuff2 = new D3DMATERIAL9[g_ResultModel[2].nNumMat];
			g_pTextureResult[2] = new LPDIRECT3DTEXTURE9[g_ResultModel[2].nNumMat];

			for (DWORD nCntRanking = 0; nCntRanking < g_ResultModel[2].nNumMat; nCntRanking++)
			{// マテリアル情報を読み込む
				pMatBuff2[nCntRanking] = pMat2[nCntRanking].MatD3D;

				// テクスチャ情報を初期化
				g_pTextureResult[2][nCntRanking] = NULL;

				// テクスチャ情報を読み込む
				if (pMat2[nCntRanking].pTextureFilename != NULL &&
					lstrlen(pMat2[nCntRanking].pTextureFilename) > 0)
				{
					D3DXCreateTextureFromFile(pDevice,
						pMat2[nCntRanking].pTextureFilename,
						&g_pTextureResult[2][nCntRanking]);
				}
			}

			// Xファイルの読み込み(木)
			D3DXLoadMeshFromX(RESULT_MODELDATA,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[3].pBuffMat,
				NULL,
				&g_ResultModel[3].nNumMat,
				&g_ResultModel[3].pMesh);

			// Xファイルの読み込み(木)
			D3DXLoadMeshFromX(RESULT_MODELDATA,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[4].pBuffMat,
				NULL,
				&g_ResultModel[4].nNumMat,
				&g_ResultModel[4].pMesh);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(RESULT_MODELDATA2,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[5].pBuffMat,
				NULL,
				&g_ResultModel[5].nNumMat,
				&g_ResultModel[5].pMesh);
		}

		// 順位看板の位置
		g_ResultModel[0].pos = D3DXVECTOR3(-58.0f, 10.0f, -1577.0f);	// 一位
		g_ResultModel[1].pos = D3DXVECTOR3(54.0f, 13.0f, -1560.0f);		// 二位
		g_ResultModel[2].pos = D3DXVECTOR3(1.0f, 91.0f, -1530.0f);		// リザルト

																		// 木の位置
		g_ResultModel[3].pos = D3DXVECTOR3(-90.0f, 0.0f, -1110.0f);		// 木
		g_ResultModel[4].pos = D3DXVECTOR3(60.0f, 0.0f, -990.0f);		// 木
		g_ResultModel[5].pos = D3DXVECTOR3(0.0f, -60.0f, -900.0f);		// オアシス

	}
	else if (g_Mode == MODE_OVER)
	{// ゲームオーバー

	 // Xファイルの読み込み(GAMEOVER看板)
		D3DXLoadMeshFromX(RESULT_BOARD4,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_ResultModel[0].pBuffMat,
			NULL,
			&g_ResultModel[0].nNumMat,
			&g_ResultModel[0].pMesh);

		// マテリアル情報からテクスチャを引き出す
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_ResultModel[0].pBuffMat->GetBufferPointer();
		D3DMATERIAL9 *pMatBuff = new D3DMATERIAL9[g_ResultModel[0].nNumMat];
		g_pTextureResult[0] = new LPDIRECT3DTEXTURE9[g_ResultModel[0].nNumMat];

		for (DWORD nCntRanking = 0; nCntRanking < g_ResultModel[0].nNumMat; nCntRanking++)
		{// マテリアル情報を読み込む
			pMatBuff[nCntRanking] = pMat[nCntRanking].MatD3D;

			// テクスチャ情報を初期化
			g_pTextureResult[0][nCntRanking] = NULL;

			// テクスチャ情報を読み込む
			if (pMat[nCntRanking].pTextureFilename != NULL &&
				lstrlen(pMat[nCntRanking].pTextureFilename) > 0)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntRanking].pTextureFilename,
					&g_pTextureResult[0][nCntRanking]);
			}
		}

		// GAMEOVER看板の位置
		g_ResultModel[0].pos = D3DXVECTOR3(1.0f, 108.0f, -1550.0f);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	int nCntResult;

	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// メッシュフィールドの終了処理
	UninitMeshField();

	// 海の床の終了処理
	UninitOcean();

	// 空の終了処理
	UninitSky();

	// プレイヤーの終了処理
	UninitPlayer();

	// 影の終了
	UninitShadow();

	for (nCntResult = 0; nCntResult < RESULT_MODELC; nCntResult++)
	{
		// メッシュの開放
		if (g_ResultModel[nCntResult].pMesh != NULL)
		{
			g_ResultModel[nCntResult].pMesh->Release();
			g_ResultModel[nCntResult].pMesh = NULL;
		}

		// マテリアルの開放
		if (g_ResultModel[nCntResult].pBuffMat != NULL)
		{
			g_ResultModel[nCntResult].pBuffMat->Release();
			g_ResultModel[nCntResult].pBuffMat = NULL;
		}

		// テクスチャの開放
		if (nCntResult <= 2)
		{
			for (DWORD nCntMat = 0; nCntMat < g_ResultModel[nCntResult].nNumMat; nCntMat++)
			{
				if (g_pTextureResult[nCntResult][nCntMat] != NULL)
				{
					g_pTextureResult[nCntResult][nCntMat]->Release();
					g_pTextureResult[nCntResult][nCntMat] = NULL;
				}
			}
		}
		else
		{
			if (g_pTextureResult[nCntResult] != NULL)
			{
				g_pTextureResult[nCntResult] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	g_nCounterResult++;

	// カメラ取得
	Camera *pCamera = GetCamera();

	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	// メッシュフィールドの更新処理
	UpdateMeshField();

	// 海の床の更新処理
	UpdateOcean();

	// 空の更新処理
	UpdateSky();

	// プレイヤーの更新処理
	UpdatePlayer();

	// 影の更新
	UpdateShadow();

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE || GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE && GetFade() == FADE_NONE || g_nCounterResult % 300 == 0 && GetFade() == FADE_NONE)
	{// 決定ボタンが押された
		if (GetMode() == MODE_CLEAR)
		{// クリアしたら
			SetFade(MODE_RANKING);
		}
		else if (GetMode() == MODE_OVER)
		{// ゲームオーバーだったら
			SetFade(MODE_SELECT);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	// カメラの設定
	SetCamera();

	// 空の描画処理
	DrawSky();

	// プレイヤーの描画処理
	DrawPlayer();

	// 影の描画
	DrawShadow();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	MODE g_Mode;

	//デバイスの取得
	pDevice = GetDevice();
	g_Mode = GetMode();

	if (g_Mode == MODE_CLEAR)
	{
		// メッシュフィールドの描画処理
		DrawMeshField();

		for (int nCntResult = 0; nCntResult < RESULT_MODELC; nCntResult++)
		{
			if (nCntResult == 2)
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			}

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_ResultModel[nCntResult].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ResultModel[nCntResult].rot.y, g_ResultModel[nCntResult].rot.x, g_ResultModel[nCntResult].rot.z);
			D3DXMatrixMultiply(&g_ResultModel[nCntResult].mtxWorld, &g_ResultModel[nCntResult].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_ResultModel[nCntResult].pos.x, g_ResultModel[nCntResult].pos.y, g_ResultModel[nCntResult].pos.z);
			D3DXMatrixMultiply(&g_ResultModel[nCntResult].mtxWorld, &g_ResultModel[nCntResult].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_ResultModel[nCntResult].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_ResultModel[nCntResult].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ResultModel[nCntResult].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (nCntResult <= 2)
				{
					// テクスチャの設定
					pDevice->SetTexture(0, g_pTextureResult[nCntResult][nCntMat]);
				}
				else
				{
					// テクスチャの設定
					pDevice->SetTexture(0, NULL);
				}

				// プレイヤー(パーツ)の描画
				g_ResultModel[nCntResult].pMesh->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);

			if (nCntResult == 2)
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}
	else if (g_Mode == MODE_OVER)
	{// ゲームオーバー

	 // 海の床の描画処理
		DrawOcean();

		for (int nCntResult = 0; nCntResult < RESULT_MODELO; nCntResult++)
		{
			if (nCntResult == 0)
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			}

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_ResultModel[nCntResult].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ResultModel[nCntResult].rot.y, g_ResultModel[nCntResult].rot.x, g_ResultModel[nCntResult].rot.z);
			D3DXMatrixMultiply(&g_ResultModel[nCntResult].mtxWorld, &g_ResultModel[nCntResult].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_ResultModel[nCntResult].pos.x, g_ResultModel[nCntResult].pos.y, g_ResultModel[nCntResult].pos.z);
			D3DXMatrixMultiply(&g_ResultModel[nCntResult].mtxWorld, &g_ResultModel[nCntResult].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_ResultModel[nCntResult].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_ResultModel[nCntResult].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ResultModel[nCntResult].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (nCntResult <= 0)
				{
					// テクスチャの設定
					pDevice->SetTexture(0, g_pTextureResult[nCntResult][nCntMat]);
				}
				else
				{
					// テクスチャの設定
					pDevice->SetTexture(0, NULL);
				}

				// プレイヤー(パーツ)の描画
				g_ResultModel[nCntResult].pMesh->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);

			if (nCntResult == 0)
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}
}
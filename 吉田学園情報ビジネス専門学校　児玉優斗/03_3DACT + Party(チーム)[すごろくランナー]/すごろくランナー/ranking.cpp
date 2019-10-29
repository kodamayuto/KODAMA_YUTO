//=============================================================================
//
// ランキング画面 [ranking.cpp]
// Author : 高橋美優
//
//=============================================================================
#include "ranking.h"
#include "fade.h"
#include "input.h"
#include "rankingscore.h"
#include "camera.h"
#include "light.h"
#include "sky.h"
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKING_MODEL	"data\\MODEL\\board1.x"		// 読み込むモデルファイル名1
#define RANKING_MODEL1	"data\\MODEL\\board2.x"		// 読み込むモデルファイル名2
#define RANKING_MODEL2	"data\\MODEL\\board3.x"		// 読み込むモデルファイル名3
#define RANKING_MODEL3	"data\\MODEL\\board4.x"		// 読み込むモデルファイル名4
#define RANKING_MODEL4	"data\\MODEL\\board5.x"		// 読み込むモデルファイル名5

#define MODEL_L			"data\\MODEL\\boardL.x"		// 読み込むモデルファイル名

#define MAX_TEXTURE		(5)							// テクスチャの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_nCntRanking;												// ○秒後にフェード
LPDIRECT3DTEXTURE9*		g_pTextureRanking[MAX_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;				// 頂点バッファへのポインタ
RankingModel g_RankingModel[10];								// モデルの情報
D3DXVECTOR3 g_vtxMinRanking, g_vtxMaxRanking;					// モデルの最小値・最大値
RankingOld g_RankingOld = RANKINGOLD_TITLE;
int g_nCntRankingMove = 1;										//ランキングでのカメラ移動
int g_nRankingMoveCount = 4;									//ランキング時のカメラ操作管理


//=============================================================================
// ランキング画面の初期化処理
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	// 初期化
	g_nCntRanking = 0;


	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//地面の初期化処理
	InitPolygon();

	//空の初期化処理
	InitSky();

	// ランキングスコアの初期化処理
	InitRankingscore();

	SetPolygon(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGONTYPE_GRASS, 10000.0f, 10000.0f);


	// Xファイルの読み込み5
	D3DXLoadMeshFromX(RANKING_MODEL4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[0].pBuffMat,
		NULL,
		&g_RankingModel[0].nNumMat,
		&g_RankingModel[0].pMesh);

	// マテリアル情報からテクスチャを引き出す
	D3DXMATERIAL *pMat4 = (D3DXMATERIAL*)g_RankingModel[0].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff4 = new D3DMATERIAL9[g_RankingModel[0].nNumMat];
	g_pTextureRanking[0] = new LPDIRECT3DTEXTURE9[g_RankingModel[0].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[0].nNumMat; nCntRanking++)
	{// マテリアル情報を読み込む
		pMatBuff4[nCntRanking] = pMat4[nCntRanking].MatD3D;

		// テクスチャ情報を初期化
		g_pTextureRanking[0][nCntRanking] = NULL;

		// テクスチャ情報を読み込む
		if (pMat4[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat4[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat4[nCntRanking].pTextureFilename,
				&g_pTextureRanking[0][nCntRanking]);
		}
	}
	// Xファイルの読み込み4
	D3DXLoadMeshFromX(RANKING_MODEL3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[1].pBuffMat,
		NULL,
		&g_RankingModel[1].nNumMat,
		&g_RankingModel[1].pMesh);

	// マテリアル情報からテクスチャを引き出す
	D3DXMATERIAL *pMat3 = (D3DXMATERIAL*)g_RankingModel[1].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff3 = new D3DMATERIAL9[g_RankingModel[1].nNumMat];
	g_pTextureRanking[1] = new LPDIRECT3DTEXTURE9[g_RankingModel[1].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[1].nNumMat; nCntRanking++)
	{// マテリアル情報を読み込む
		pMatBuff3[nCntRanking] = pMat3[nCntRanking].MatD3D;

		// テクスチャ情報を初期化
		g_pTextureRanking[1][nCntRanking] = NULL;

		// テクスチャ情報を読み込む
		if (pMat3[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat3[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat3[nCntRanking].pTextureFilename,
				&g_pTextureRanking[1][nCntRanking]);
		}
	}


	// Xファイルの読み込み3
	D3DXLoadMeshFromX(RANKING_MODEL2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[2].pBuffMat,
		NULL,
		&g_RankingModel[2].nNumMat,
		&g_RankingModel[2].pMesh);

	// マテリアル情報からテクスチャを引き出す
	D3DXMATERIAL *pMat2 = (D3DXMATERIAL*)g_RankingModel[2].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff2 = new D3DMATERIAL9[g_RankingModel[2].nNumMat];
	g_pTextureRanking[2] = new LPDIRECT3DTEXTURE9[g_RankingModel[2].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[2].nNumMat; nCntRanking++)
	{// マテリアル情報を読み込む
		pMatBuff2[nCntRanking] = pMat2[nCntRanking].MatD3D;

		// テクスチャ情報を初期化
		g_pTextureRanking[2][nCntRanking] = NULL;

		// テクスチャ情報を読み込む
		if (pMat2[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat2[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat2[nCntRanking].pTextureFilename,
				&g_pTextureRanking[2][nCntRanking]);
		}
	}

	// Xファイルの読み込み2
	D3DXLoadMeshFromX(RANKING_MODEL1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[3].pBuffMat,
		NULL,
		&g_RankingModel[3].nNumMat,
		&g_RankingModel[3].pMesh);

	// マテリアル情報からテクスチャを引き出す
	D3DXMATERIAL *pMat1 = (D3DXMATERIAL*)g_RankingModel[3].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff1 = new D3DMATERIAL9[g_RankingModel[3].nNumMat];
	g_pTextureRanking[3] = new LPDIRECT3DTEXTURE9[g_RankingModel[3].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[3].nNumMat; nCntRanking++)
	{// マテリアル情報を読み込む
		pMatBuff1[nCntRanking] = pMat1[nCntRanking].MatD3D;

		// テクスチャ情報を初期化
		g_pTextureRanking[3][nCntRanking] = NULL;

		// テクスチャ情報を読み込む
		if (pMat1[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat1[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat1[nCntRanking].pTextureFilename,
				&g_pTextureRanking[3][nCntRanking]);
		}
	}


	// Xファイルの読み込み1
	D3DXLoadMeshFromX(RANKING_MODEL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[4].pBuffMat,
		NULL,
		&g_RankingModel[4].nNumMat,
		&g_RankingModel[4].pMesh);

	// マテリアル情報からテクスチャを引き出す
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_RankingModel[4].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff = new D3DMATERIAL9[g_RankingModel[4].nNumMat];
	g_pTextureRanking[4] = new LPDIRECT3DTEXTURE9[g_RankingModel[4].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[4].nNumMat; nCntRanking++)
	{// マテリアル情報を読み込む
		pMatBuff[nCntRanking] = pMat[nCntRanking].MatD3D;

		// テクスチャ情報を初期化
		g_pTextureRanking[4][nCntRanking] = NULL;

		// テクスチャ情報を読み込む
		if (pMat[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntRanking].pTextureFilename,
				&g_pTextureRanking[4][nCntRanking]);
		}
	}

	// Xファイルの読み込み(スコア看板)1
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[5].pBuffMat,
		NULL,
		&g_RankingModel[5].nNumMat,
		&g_RankingModel[5].pMesh);

	// Xファイルの読み込み(スコア看板)2
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[6].pBuffMat,
		NULL,
		&g_RankingModel[6].nNumMat,
		&g_RankingModel[6].pMesh);

	// Xファイルの読み込み(スコア看板)3
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[7].pBuffMat,
		NULL,
		&g_RankingModel[7].nNumMat,
		&g_RankingModel[7].pMesh);

	// Xファイルの読み込み(スコア看板)4
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[8].pBuffMat,
		NULL,
		&g_RankingModel[8].nNumMat,
		&g_RankingModel[8].pMesh);

	// Xファイルの読み込み(スコア看板)5
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[9].pBuffMat,
		NULL,
		&g_RankingModel[9].nNumMat,
		&g_RankingModel[9].pMesh);

	// 初期化
	for (int nCntRanking = 0; nCntRanking < MAX_MODEL; nCntRanking++)
	{
		g_RankingModel[nCntRanking].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_RankingModel[nCntRanking].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	}

	// 順位看板
	g_RankingModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 400.0f);
	g_RankingModel[1].pos = D3DXVECTOR3(40.0f, 0.0f, 300.0f);
	g_RankingModel[2].pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);
	g_RankingModel[3].pos = D3DXVECTOR3(40.0f, 0.0f, 100.0f);
	g_RankingModel[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// スコア看板
	g_RankingModel[5].pos = D3DXVECTOR3(40.0f, 0.0f, 0.0f);
	g_RankingModel[6].pos = D3DXVECTOR3(80.0f, 0.0f, 100.0f);
	g_RankingModel[7].pos = D3DXVECTOR3(40.0f, 0.0f, 200.0f);
	g_RankingModel[8].pos = D3DXVECTOR3(80.0f, 0.0f, 300.0f);
	g_RankingModel[9].pos = D3DXVECTOR3(40.0f, 0.0f, 400.0f);

	//タイマーの初期化
	g_nRankingMoveCount = 4;		//ランキング時のカメラ操作管理


}

//=============================================================================
// ランキング画面の終了処理
//=============================================================================
void UninitRanking(void)
{

	// カメラの終了処理
	UninitCamera();

	//地面の終了処理
	UninitPolygon();

	// ライトの終了処理
	UninitLight();

	//空の終了処理
	UninitSky();

	// ランキングスコアの終了処理
	UninitRankingscore();

	for (int nCntRanking = 0; nCntRanking < MAX_MODEL; nCntRanking++)
	{
		// メッシュの開放
		if (g_RankingModel[nCntRanking].pMesh != NULL)
		{
			g_RankingModel[nCntRanking].pMesh->Release();
			g_RankingModel[nCntRanking].pMesh = NULL;
		}

		// マテリアルの開放
		if (g_RankingModel[nCntRanking].pBuffMat != NULL)
		{
			g_RankingModel[nCntRanking].pBuffMat->Release();
			g_RankingModel[nCntRanking].pBuffMat = NULL;
		}

		// テクスチャの開放
		if (nCntRanking <= 4)
		{
			for (DWORD nCntMat = 0; nCntMat < g_RankingModel[nCntRanking].nNumMat; nCntMat++)
			{
				if (g_pTextureRanking[nCntRanking][nCntMat] != NULL)
				{
					g_pTextureRanking[nCntRanking][nCntMat]->Release();
					g_pTextureRanking[nCntRanking][nCntMat] = NULL;
				}
			}
		}
		else
		{
			if (g_pTextureRanking[nCntRanking] != NULL)
			{
				g_pTextureRanking[nCntRanking] = NULL;
			}
		}
	}
}

//=============================================================================
// ランキング画面の更新処理
//=============================================================================
void UpdateRanking(void)
{
	FADE g_fade;

	g_fade = GetFade();

	g_nCntRanking++;

	// カメラ取得
	Camera *pCamera = GetCamera();

	// カメラの更新処理
	g_nCntRankingMove = (g_nCntRankingMove + 1) % 200;
	pCamera->SelectModelpos[4] = D3DXVECTOR3(20.0f, 20.0f, -80.0f);
	pCamera->SelectModelpos[3] = D3DXVECTOR3(60.0f, 20.0f, 20.0f);
	pCamera->SelectModelpos[2] = D3DXVECTOR3(20.0f, 20.0f, 120.0f);
	pCamera->SelectModelpos[1] = D3DXVECTOR3(60.0f, 20.0f, 220.0f);
	pCamera->SelectModelpos[0] = D3DXVECTOR3(20.0f, 20.0f, 320.0f);

	if (g_nCntRankingMove % 200 == 0)
	{
		if (g_nRankingMoveCount == 0)
		{
			switch (g_RankingOld)
			{
			case RANKINGOLD_TITLE:
				SetFade(MODE_TITLE);
				break;

			case RANKINGOLD_SELECT:
				SetFade(MODE_SELECT);
				break;
			}
		}
		else
		{
			if (GetFade() == FADE_NONE)
			{
				g_nRankingMoveCount = (g_nRankingMoveCount + 4) % 5;
			}
		}
	}
	pCamera->posRDest = D3DXVECTOR3(pCamera->SelectModelpos[g_nRankingMoveCount].x - pCamera->posR.x,
		0.0f,
		(pCamera->SelectModelpos[g_nRankingMoveCount].z + 80.0f) - pCamera->posR.z);
	pCamera->posR.x += pCamera->posRDest.x * 0.04f;
	pCamera->posR.z += pCamera->posRDest.z * 0.04f;

	pCamera->posVDest = pCamera->SelectModelpos[g_nRankingMoveCount];
	pCamera->posV += (pCamera->posVDest - pCamera->posV) * 0.04f;

	// ライトの更新処理
	UpdateLight();

	//地面の更新処理
	UpdatePolygon();

	//空の更新処理
	UpdateSky();

	// ランキングスコアの更新処理
	UpdateRankingscore();

	// 決定キー(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_2, 0) == true)
	{
		if (g_fade != FADE_OUT)
		{
			//モード設定
			switch (g_RankingOld)
			{
			case RANKINGOLD_TITLE:
				SetFade(MODE_TITLE);
				break;

			case RANKINGOLD_SELECT:
				SetFade(MODE_SELECT);
				break;
			}

			SetDrawScore(4);
			//PlaySound(SOUND_LABEL_SE_BOTAN001);
		}
	}
}

//=============================================================================
// ランキング画面の描画処理
//=============================================================================
void DrawRanking(void)
{
	// カメラの設定
	SetCamera();

	//地面の描画処理
	DrawPolygon();

	//空の描画処理
	DrawSky();

	int nCntRanking = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nCntRanking = 0; nCntRanking < MAX_MODEL; nCntRanking++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_RankingModel[nCntRanking].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_RankingModel[nCntRanking].rot.y, g_RankingModel[nCntRanking].rot.x, g_RankingModel[nCntRanking].rot.z);
		D3DXMatrixMultiply(&g_RankingModel[nCntRanking].mtxWorld, &g_RankingModel[nCntRanking].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_RankingModel[nCntRanking].pos.x, g_RankingModel[nCntRanking].pos.y, g_RankingModel[nCntRanking].pos.z);
		D3DXMatrixMultiply(&g_RankingModel[nCntRanking].mtxWorld, &g_RankingModel[nCntRanking].mtxWorld, &mtxTrans);

		//// 関連付け
		//D3DXMatrixMultiply(&g_RankingModel[nCntRanking].mtxWorld, &g_RankingModel[nCntRanking].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_RankingModel[nCntRanking].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_RankingModel[nCntRanking].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_RankingModel[nCntRanking].nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (nCntRanking <= 4)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureRanking[nCntRanking][nCntMat]);
			}
			else
			{
				// テクスチャの設定
				pDevice->SetTexture(0, NULL);
			}

			// プレイヤー(パーツ)の描画
			g_RankingModel[nCntRanking].pMesh->DrawSubset(nCntMat);

		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
	// カメラの設定
	//SetCamera();
	//pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// ランキングスコアの描画処理
	DrawRankingscore();

}

//=============================================================================
// ランキング画面の描画処理
//=============================================================================
void SetRankingOld(RankingOld ranking)
{
	g_RankingOld = ranking;
}
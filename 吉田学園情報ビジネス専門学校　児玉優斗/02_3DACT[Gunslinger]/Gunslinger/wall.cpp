//=============================================================================
//
// 壁処理[wall.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "wall.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WALL_FILENAME0 "data/TEXTURE/wall000.jpg"
#define WALL_FILENAME1 "data/TEXTURE/wall000.jpg"
#define MAX_WALL (256)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall[2] = {};	    //テクスチャへのポインタ

WALL g_Wall[MAX_WALL];
//=============================================================================
// 初期化処理
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, WALL_FILENAME0, &g_pTextureWall[0]);
	D3DXCreateTextureFromFile(pDevice, WALL_FILENAME1, &g_pTextureWall[1]);

	MakeVertexWall(pDevice);

	//構造体の初期化
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWall(void)
{
	// 頂点バッファの開放
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureWall[nCntTex] != NULL)
		{
			g_pTextureWall[nCntTex]->Release();
			g_pTextureWall[nCntTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	// ワールドマトリックスの初期化
	// ポリゴンの描画
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			D3DXMatrixIdentity(&g_Wall[nCntWall].g_mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Wall[nCntWall].rot.y,
				g_Wall[nCntWall].rot.x,
				g_Wall[nCntWall].rot.z);

			D3DXMatrixMultiply(&g_Wall[nCntWall].g_mtxWorld,
				&g_Wall[nCntWall].g_mtxWorld,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Wall[nCntWall].pos.x,
				g_Wall[nCntWall].pos.y,
				g_Wall[nCntWall].pos.z);

			D3DXMatrixMultiply(&g_Wall[nCntWall].g_mtxWorld,
				&g_Wall[nCntWall].g_mtxWorld,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

				// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall[0]);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
				4 * nCntWall,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}
	}
}

//=============================================================================
// ポリゴンの設定
//=============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, WALLTYPE type, float fWidth ,float fHaight)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].rot = rot;
			g_Wall[nCntWall].fWidth = fWidth;
			g_Wall[nCntWall].Haight = fHaight;
			g_Wall[nCntWall].type = type;
			

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntWall;
			switch (g_Wall[nCntWall].type)
			{
			case WALLTYPE_1:

				pVtx[0].pos = D3DXVECTOR3(-g_Wall[nCntWall].fWidth, g_Wall[nCntWall].Haight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Wall[nCntWall].fWidth, g_Wall[nCntWall].Haight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Wall[nCntWall].fWidth,0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Wall[nCntWall].fWidth, 0.0f, 0.0f);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Wall[nCntWall].fWidth / 100.0f) + 1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, (g_Wall[nCntWall].Haight / 100.0f) + 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Wall[nCntWall].fWidth / 100.0f) + 1.0f, (g_Wall[nCntWall].Haight / 100.0f) + 1.0f);
				break;
			}
			//頂点バッファをアンロックする
			g_pVtxBuffWall->Unlock();
			g_Wall[nCntWall].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntWall;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffWall->Unlock();
	}
}


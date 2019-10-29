//=============================================================================
//
// モデル処理 [island.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "island.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ISLAND_FILENAME "data/MODEL/island/3d_001_Land000.x"
#define ISLAND_MOVE_SPEED (1.0f)
#define ISLAND_ROTMOVE_COEFFICIENT (0.11f)
#define MAX_NUM_ISLAND (4)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshISLAND[MAX_NUM_ISLAND] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatISLAND[MAX_NUM_ISLAND] = {};	//マテリアル情報へのポインタ

ISLAND g_ISLAND[MAX_NUM_ISLAND];
//=============================================================================
// 初期化処理
//=============================================================================
void InitIsland(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイル名を代入
	g_ISLAND[0].filename = "data/MODEL/island/3d_001_Land000.x";
	g_ISLAND[1].filename = "data/MODEL/island/3d_001_Land001.x";
	g_ISLAND[2].filename = "data/MODEL/island/3d_001_Land002.x";
	g_ISLAND[3].filename = "data/MODEL/island/3d_001_Land003.x";

	for (int nCntNpc = 0; nCntNpc < MAX_NUM_ISLAND; nCntNpc++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(g_ISLAND[nCntNpc].filename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatISLAND[nCntNpc],
			NULL,
			&g_ISLAND[nCntNpc].nNumMatISLAND,
			&g_pMeshISLAND[nCntNpc]);

		// 向きの初期設定
		g_ISLAND[nCntNpc].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//移動量・回転量の初期化
		g_ISLAND[nCntNpc].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ISLAND[nCntNpc].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	g_ISLAND[0].pos = D3DXVECTOR3(-200.0f, 0.0f, 200.0f);
	g_ISLAND[1].pos = D3DXVECTOR3(200.0f, 0.0f, 200.0f);
	g_ISLAND[2].pos = D3DXVECTOR3(-200.0f, 0.0f, -200.0f);
	g_ISLAND[3].pos = D3DXVECTOR3(200.0f, 0.0f, -200.0f);

	g_ISLAND[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_ISLAND[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_ISLAND[2].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	g_ISLAND[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitIsland(void)
{
	// メッシュの解放
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_ISLAND; nCntMesh++)
	{
		if (g_pMeshISLAND[nCntMesh] != NULL)
		{
			g_pMeshISLAND[nCntMesh]->Release();
			g_pMeshISLAND[nCntMesh] = NULL;
		}
		/*テクスチャの解放*/
		//マテリアルの解放
		if (g_pBuffMatISLAND[nCntMesh] != NULL)
		{
			g_pBuffMatISLAND[nCntMesh]->Release();
			g_pBuffMatISLAND[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateIsland(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawIsland(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	for (int nCntNpc = 0; nCntNpc < MAX_NUM_ISLAND; nCntNpc++)
	{
		//if (g_ISLAND[nCntNpc].bUse == true)
		//{

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_ISLAND[nCntNpc].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_ISLAND[nCntNpc].rot.y,
				g_ISLAND[nCntNpc].rot.x,
				g_ISLAND[nCntNpc].rot.z);

			D3DXMatrixMultiply(&g_ISLAND[nCntNpc].mtxWorld,
				&g_ISLAND[nCntNpc].mtxWorld,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_ISLAND[nCntNpc].pos.x,
				g_ISLAND[nCntNpc].pos.y,
				g_ISLAND[nCntNpc].pos.z);

			D3DXMatrixMultiply(&g_ISLAND[nCntNpc].mtxWorld,
				&g_ISLAND[nCntNpc].mtxWorld,
				&mtxTrans);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_ISLAND[nCntNpc].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatISLAND[nCntNpc]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ISLAND[nCntNpc].nNumMatISLAND; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*テクスチャの設定*/
				pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

				// モデル(パーツ)の描画
				g_pMeshISLAND[nCntNpc]->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		//}
	}
}

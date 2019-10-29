//=============================================================================
//
// ポリゴン処理 [MeshField.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "meshField.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_FILENAME0 "data/TEXTURE/field000.jpg"
#define MAX_MESHFIELD (1)

#define MESH_BLOCK_WIDTH (4)
#define MESH_BLOCK_DEPTH (4)

#define MESH_WIDTH (1000.0f)
#define MESH_DEPTH (1000.0f)

//****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshField= NULL;	    //テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;

MESHFIELD g_MeshField[2];

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_FILENAME0, &g_pTextureMeshField);

	MakeVertexMeshField(pDevice);

	//構造体の初期化
	for (int nCntMesh = 0; nCntMesh < MAX_MESHFIELD; nCntMesh++)
	{
		g_MeshField[nCntMesh].pos = D3DXVECTOR3(0.0f + (100.0f * nCntMesh), 0.0f, 0.0f);
		g_MeshField[nCntMesh].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntMesh].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
		if (g_pTextureMeshField != NULL)
		{
			g_pTextureMeshField->Release();
			g_pTextureMeshField = NULL;
		}
	//頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	for (int nCntMesh = 0; nCntMesh < MAX_MESHFIELD; nCntMesh++)
	{

		g_MeshField[nCntMesh].nNumPolygon = (MESH_BLOCK_WIDTH * MESH_BLOCK_DEPTH * 2) + (4 * (MESH_BLOCK_DEPTH - 1));
		// ワールドマトリックスの初期化
		// ポリゴンの描画
		D3DXMatrixIdentity(&g_MeshField[nCntMesh].g_mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_MeshField[nCntMesh].rot.y,
			g_MeshField[nCntMesh].rot.x,
			g_MeshField[nCntMesh].rot.z);

		D3DXMatrixMultiply(&g_MeshField[nCntMesh].g_mtxWorld,
			&g_MeshField[nCntMesh].g_mtxWorld,
			&mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_MeshField[nCntMesh].pos.x,
			g_MeshField[nCntMesh].pos.y,
			g_MeshField[nCntMesh].pos.z);

		D3DXMatrixMultiply(&g_MeshField[nCntMesh].g_mtxWorld,
			&g_MeshField[nCntMesh].g_mtxWorld,
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshField[nCntMesh].g_mtxWorld);

		pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshField);

		pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

			// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshField);//テクスチャの設定

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			g_MeshField[nCntMesh].nNumVertex,
			0,
			g_MeshField[nCntMesh].nNumPolygon);
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMesh = 0; nCntMesh < MAX_MESHFIELD; nCntMesh++)
	{

		g_MeshField[nCntMesh].nNumVertex = (MESH_BLOCK_DEPTH + 1) * (MESH_BLOCK_WIDTH + 1);
		g_MeshField[nCntMesh].nNumIndex = (MESH_BLOCK_WIDTH * MESH_BLOCK_DEPTH * 2) + (4 * (MESH_BLOCK_DEPTH - 1)) + 2;

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshField[nCntMesh].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshField,
			NULL);

		//インデックスバッファの生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_MeshField[nCntMesh].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshField,
			NULL);

		//変数宣言
		VERTEX_3D *pVtx;	//頂点情報へのポインタ


		for (int nCntDepth = 0; nCntDepth < MESH_BLOCK_DEPTH + 1; nCntDepth++)
		{
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (MESH_BLOCK_WIDTH + 1) * nCntDepth;
			for (int nCntWidth = 0; nCntWidth < MESH_BLOCK_WIDTH + 1; nCntWidth++)
			{
				pVtx[nCntWidth].pos = D3DXVECTOR3(-MESH_WIDTH + ((MESH_WIDTH / (MESH_BLOCK_WIDTH / 2.0f)) * nCntWidth),
					0.0f,
					MESH_DEPTH - ((MESH_DEPTH / (MESH_BLOCK_DEPTH / 2.0f))* nCntDepth));

				pVtx[nCntWidth].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[nCntWidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntWidth].tex = D3DXVECTOR2(nCntWidth * 1.0f,nCntDepth * 1.0f);
				//pVtx[nCntWidth].tex = D3DXVECTOR2(((1.0f / MESH_BLOCK_WIDTH) * nCntWidth), ((1.0f / MESH_BLOCK_DEPTH) * nCntDepth));
			}
			//頂点バッファをアンロックする
			g_pVtxBuffMeshField->Unlock();
		}


		//インデックスデータの設定
		WORD *Idx;			//インデックスデータへのポインタ
		bool flag = false;
		//インデックスバッファをロックし、頂点データへのポインタを取得
		g_pIdxBuffMeshField->Lock(0, 0, (void**)&Idx, 0);
		for (int nCntIdxDepth = 0; nCntIdxDepth < MESH_BLOCK_DEPTH; nCntIdxDepth++)
		{
			for (int nCntIdxWidth = 0; nCntIdxWidth < MESH_BLOCK_WIDTH + 1; nCntIdxWidth++)
			{
				Idx[0] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxDepth + 1));

				if (flag == true)
				{//縮退ポリゴンの処理（下）
					Idx[1] = Idx[0];
					Idx[2] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxDepth));
					Idx += 3;
					flag = false;
				}
				else
				{//縮退ポリゴンでなければ

					Idx[1] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxDepth));
					Idx += 2;
				}

				if (Idx[-1] % (MESH_BLOCK_WIDTH + 1) == MESH_BLOCK_WIDTH && flag == false)
				{//縮退ポリゴンの処理（上）
					Idx[0] = Idx[-1];
					Idx += 1;
					flag = true;
				}
			}
		}
		//インデックスバッファをアンロックする
		g_pIdxBuffMeshField->Unlock();
	}


}



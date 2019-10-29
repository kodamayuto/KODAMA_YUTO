//=============================================================================
//
// ポリゴン処理 [MeshCylinder.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "meshCylinder.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHCYLINDER_FILENAME0 "data/TEXTURE/thK0A5DS5J.jpg"
#define MAX_MESHCYLINDER (2)

#define MESH_BLOCK_WIDTH (100)
#define MESH_BLOCK_HAIGHT (1)

#define MESH_WIDTH (1500.0f)
#define MESH_HAIGHT (1000.0f)

//****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder= NULL;	    //テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;

MESHCYLINDER g_MeshCylinder[MAX_MESHCYLINDER];

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_FILENAME0, &g_pTextureMeshCylinder);

	MakeVertexMeshCylinder(pDevice);

	//構造体の初期化
	for (int nCntMesh = 0; nCntMesh < MAX_MESHCYLINDER; nCntMesh++)
	{
		g_MeshCylinder[nCntMesh].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshCylinder[nCntMesh].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshCylinder[nCntMesh].bUse = false;
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshCylinder(void)
{
		if (g_pTextureMeshCylinder != NULL)
		{
			g_pTextureMeshCylinder->Release();
			g_pTextureMeshCylinder = NULL;
		}
	//頂点バッファの破棄
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshCylinder(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_MESHCYLINDER; nCntMesh++)
	{
		g_MeshCylinder[nCntMesh].rot.y += 0.0005f;

		RotOverwhelming(g_MeshCylinder[nCntMesh].rot.y);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (int nCntMesh = 0; nCntMesh < MAX_MESHCYLINDER; nCntMesh++)
	{

		g_MeshCylinder[nCntMesh].nNumPolygon = (MESH_BLOCK_WIDTH * MESH_BLOCK_HAIGHT * 2) + (4 * (MESH_BLOCK_HAIGHT - 1));
		// ワールドマトリックスの初期化
		// ポリゴンの描画
		D3DXMatrixIdentity(&g_MeshCylinder[nCntMesh].g_mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_MeshCylinder[nCntMesh].rot.y,
			g_MeshCylinder[nCntMesh].rot.x,
			g_MeshCylinder[nCntMesh].rot.z);

		D3DXMatrixMultiply(&g_MeshCylinder[nCntMesh].g_mtxWorld,
			&g_MeshCylinder[nCntMesh].g_mtxWorld,
			&mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_MeshCylinder[nCntMesh].pos.x,
			g_MeshCylinder[nCntMesh].pos.y,
			g_MeshCylinder[nCntMesh].pos.z);

		D3DXMatrixMultiply(&g_MeshCylinder[nCntMesh].g_mtxWorld,
			&g_MeshCylinder[nCntMesh].g_mtxWorld,
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshCylinder[nCntMesh].g_mtxWorld);

		pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshCylinder);

		pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

			// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshCylinder);//テクスチャの設定

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			g_MeshCylinder[nCntMesh].nNumVertex,
			0,
			g_MeshCylinder[nCntMesh].nNumPolygon);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vecNor;		//法線の正規化用

	for (int nCntMesh = 0; nCntMesh < MAX_MESHCYLINDER; nCntMesh++)
	{

		g_MeshCylinder[nCntMesh].nNumVertex = (MESH_BLOCK_HAIGHT + 1) * (MESH_BLOCK_WIDTH + 1);
		g_MeshCylinder[nCntMesh].nNumIndex = (MESH_BLOCK_WIDTH * MESH_BLOCK_HAIGHT * 2) + (4 * (MESH_BLOCK_HAIGHT - 1)) + 2;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshCylinder[nCntMesh].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshCylinder,
			NULL);

		pDevice->CreateIndexBuffer(sizeof(WORD) * g_MeshCylinder[nCntMesh].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshCylinder,
			NULL);

		//変数宣言
		VERTEX_3D *pVtx;	//頂点情報へのポインタ

		for (int nCntHaight = 0; nCntHaight < MESH_BLOCK_HAIGHT + 1; nCntHaight++)
		{
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (MESH_BLOCK_WIDTH + 1) * nCntHaight;
			for (int nCntWidth = 0; nCntWidth < MESH_BLOCK_WIDTH + 1; nCntWidth++)
			{
				pVtx[nCntWidth].pos = D3DXVECTOR3(sinf(((D3DX_PI * 2.0f)/ MESH_BLOCK_WIDTH) * nCntWidth) * MESH_WIDTH,
					MESH_HAIGHT - ((MESH_HAIGHT / MESH_BLOCK_HAIGHT) * nCntHaight),
					cosf(((D3DX_PI * 2.0f) / MESH_BLOCK_WIDTH) * nCntWidth) * MESH_WIDTH);

				D3DXVec3Normalize(&vecNor, &pVtx[nCntWidth].pos);

				pVtx[nCntWidth].nor.x = vecNor.x;
				pVtx[nCntWidth].nor.y = 0.0f;
				pVtx[nCntWidth].nor.z = vecNor.z;

				pVtx[nCntWidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntWidth].tex = D3DXVECTOR2((1.0f / MESH_BLOCK_WIDTH) * nCntWidth, (1.0f / MESH_BLOCK_HAIGHT) * nCntHaight);
			}
			//頂点バッファをアンロックする
			g_pVtxBuffMeshCylinder->Unlock();

		}

		//インデックスバッファの生成

		//インデックスデータの設定
		WORD *Idx;			//インデックスデータへのポインタ
		bool flag = false;
		//インデックスバッファをロックし、頂点データへのポインタを取得
		g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&Idx, 0);
		for (int nCntIdxHaight = 0; nCntIdxHaight < MESH_BLOCK_HAIGHT; nCntIdxHaight++)
		{
			for (int nCntIdxWidth = 0; nCntIdxWidth < MESH_BLOCK_WIDTH + 1; nCntIdxWidth++)
			{
				Idx[0] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxHaight + 1));

				if (flag == true)
				{//縮退ポリゴンの処理（下）
					Idx[1] = Idx[0];
					Idx[2] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxHaight));
					Idx += 3;
					flag = false;
				}
				else
				{//縮退ポリゴンでなければ

					Idx[1] = nCntIdxWidth + ((MESH_BLOCK_WIDTH + 1) * (nCntIdxHaight));
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
		g_pIdxBuffMeshCylinder->Unlock();

	}


}



//=============================================================================
//
// ポリゴン処理 [MeshWall.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "meshWall.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHWALL_FILENAME0 "data/TEXTURE/wall000.jpg"
#define MAX_MESHWALL (200)

#define MESH_BLOCK_WIDTH (4)
#define MESH_BLOCK_HAIGHT (4)

#define MESH_WIDTH (1000.0f)
#define MESH_HAIGHT (50.0f)

//****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall[MAX_MESHWALL] = {};	//頂点バッファへのポインタ	(壁の枚数分作る)
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall[MAX_MESHWALL] = {};
LPDIRECT3DTEXTURE9 g_pTextureMeshWall= NULL;	    //テクスチャへのポインタ

MESHWALL g_MeshWall[MAX_MESHWALL];

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, MESHWALL_FILENAME0, &g_pTextureMeshWall);

	//構造体の初期化
	for (int nCntMesh = 0; nCntMesh < MAX_MESHWALL; nCntMesh++)
	{
		g_MeshWall[nCntMesh].nMeshBlockWidth = 4;
		g_MeshWall[nCntMesh].nMeshBlockHaight = 4;
		g_MeshWall[nCntMesh].fMeshSizeW = 100.0f;
		g_MeshWall[nCntMesh].fMeshSizeH = 50.0f;

		g_MeshWall[nCntMesh].bUse = false;
		g_MeshWall[nCntMesh].nNumVertex = (g_MeshWall[nCntMesh].nMeshBlockHaight + 1) * (g_MeshWall[nCntMesh].nMeshBlockWidth + 1);
		g_MeshWall[nCntMesh].nNumIndex = (g_MeshWall[nCntMesh].nMeshBlockWidth * g_MeshWall[nCntMesh].nMeshBlockHaight * 2) + (4 * (g_MeshWall[nCntMesh].nMeshBlockHaight - 1)) + 2;
	}

	MakeVertexMeshWall(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshWall(void)
{
		if (g_pTextureMeshWall != NULL)
		{
			g_pTextureMeshWall->Release();
			g_pTextureMeshWall = NULL;
		}
	//頂点バッファの破棄
		for (int nCntBuff = 0; nCntBuff < MAX_MESHWALL; nCntBuff++)
		{
			if (g_pVtxBuffMeshWall[nCntBuff] != NULL)
			{
				g_pVtxBuffMeshWall[nCntBuff]->Release();
				g_pVtxBuffMeshWall[nCntBuff] = NULL;
			}


			//インデックスバッファの破棄
			if (g_pIdxBuffMeshWall[nCntBuff] != NULL)
			{
				g_pIdxBuffMeshWall[nCntBuff]->Release();
				g_pIdxBuffMeshWall[nCntBuff] = NULL;
			}

		}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshWall(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_MESHWALL; nCntMesh++)
	{

		g_MeshWall[nCntMesh].aPos.x = g_MeshWall[nCntMesh].pos.x + 
		sinf(g_MeshWall[nCntMesh].rot.y - (D3DX_PI * 0.5f))* g_MeshWall[nCntMesh].fMeshSizeW;

		g_MeshWall[nCntMesh].aPos.z = g_MeshWall[nCntMesh].pos.z +
			cosf(g_MeshWall[nCntMesh].rot.y - (D3DX_PI * 0.5f))* g_MeshWall[nCntMesh].fMeshSizeW;


		g_MeshWall[nCntMesh].bPos.x = g_MeshWall[nCntMesh].pos.x +
			sinf(g_MeshWall[nCntMesh].rot.y + (D3DX_PI * 0.5f))* g_MeshWall[nCntMesh].fMeshSizeW;

		g_MeshWall[nCntMesh].bPos.z = g_MeshWall[nCntMesh].pos.z +
			cosf(g_MeshWall[nCntMesh].rot.y + (D3DX_PI * 0.5f))* g_MeshWall[nCntMesh].fMeshSizeW;

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	for (int nCntMesh = 0; nCntMesh < MAX_MESHWALL; nCntMesh++)
	{
		if (g_MeshWall[nCntMesh].bUse == true)
		{

		g_MeshWall[nCntMesh].nNumPolygon = (g_MeshWall[nCntMesh].nMeshBlockWidth * g_MeshWall[nCntMesh].nMeshBlockHaight * 2) + (4 * (g_MeshWall[nCntMesh].nMeshBlockHaight - 1));
		// ワールドマトリックスの初期化
		// ポリゴンの描画
		D3DXMatrixIdentity(&g_MeshWall[nCntMesh].g_mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_MeshWall[nCntMesh].rot.y,
			g_MeshWall[nCntMesh].rot.x,
			g_MeshWall[nCntMesh].rot.z);

		D3DXMatrixMultiply(&g_MeshWall[nCntMesh].g_mtxWorld,
			&g_MeshWall[nCntMesh].g_mtxWorld,
			&mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_MeshWall[nCntMesh].pos.x,
			g_MeshWall[nCntMesh].pos.y,
			g_MeshWall[nCntMesh].pos.z);

		D3DXMatrixMultiply(&g_MeshWall[nCntMesh].g_mtxWorld,
			&g_MeshWall[nCntMesh].g_mtxWorld,
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntMesh].g_mtxWorld);

		pDevice->SetStreamSource(0, g_pVtxBuffMeshWall[nCntMesh], 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshWall[nCntMesh]);

		pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

			// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshWall);//テクスチャの設定

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			g_MeshWall[nCntMesh].nNumVertex,
			0,
			g_MeshWall[nCntMesh].nNumPolygon);
		}
	}
}


//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{	
	for (int nCntMesh = 0; nCntMesh < MAX_MESHWALL; nCntMesh++)
	{
		//頂点バッファの作成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshWall[nCntMesh].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshWall[nCntMesh],
			NULL);

		//頂点インデックスの作成
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_MeshWall[nCntMesh].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshWall[nCntMesh],
			NULL);


		//変数宣言
		VERTEX_3D *pVtx;	//頂点情報へのポインタ
							//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffMeshWall[nCntMesh]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntHaight = 0; nCntHaight < g_MeshWall[nCntMesh].nMeshBlockHaight + 1; nCntHaight++)
		{
			for (int nCntWidth = 0; nCntWidth < g_MeshWall[nCntMesh].nMeshBlockWidth + 1; nCntWidth++)
			{
				pVtx[nCntWidth].pos = D3DXVECTOR3(-g_MeshWall[nCntMesh].fMeshSizeW + ((g_MeshWall[nCntMesh].fMeshSizeW / (g_MeshWall[nCntMesh].nMeshBlockWidth / 2.0f)) * nCntWidth),
					((g_MeshWall[nCntMesh].fMeshSizeH / (g_MeshWall[nCntMesh].nMeshBlockHaight / 2.0f))* nCntHaight),
					0.0f);

				pVtx[nCntWidth].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[nCntWidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntWidth].tex = D3DXVECTOR2(nCntWidth * 1.0f, nCntHaight * 1.0f);
			}
			pVtx += (g_MeshWall[nCntMesh].nMeshBlockWidth + 1);

		}
		//頂点バッファをアンロックする
		g_pVtxBuffMeshWall[nCntMesh]->Unlock();


		//インデックスデータの設定
		WORD *Idx;			//インデックスデータへのポインタ
		bool flag = false;
		//インデックスバッファをロックし、頂点データへのポインタを取得
		g_pIdxBuffMeshWall[nCntMesh]->Lock(0, 0, (void**)&Idx, 0);

		for (int nCntIdxHaight = 0; nCntIdxHaight < g_MeshWall[nCntMesh].nMeshBlockHaight; nCntIdxHaight++)
		{
			for (int nCntIdxWidth = 0; nCntIdxWidth < g_MeshWall[nCntMesh].nMeshBlockWidth +1 ; nCntIdxWidth++)
			{
				Idx[0] = nCntIdxWidth + ((g_MeshWall[nCntMesh].nMeshBlockWidth + 1) * (nCntIdxHaight + 1));

				if (flag == true)
				{//縮退ポリゴンの処理（下）
					Idx[1] = Idx[0];
					Idx[2] = nCntIdxWidth + ((g_MeshWall[nCntMesh].nMeshBlockWidth + 1) * (nCntIdxHaight));
					Idx += 3;
					flag = false;
				}
				else
				{//縮退ポリゴンでなければ

					Idx[1] = nCntIdxWidth + ((g_MeshWall[nCntMesh].nMeshBlockWidth + 1) * (nCntIdxHaight));
					Idx += 2;
				}

				if (Idx[-1] % (g_MeshWall[nCntMesh].nMeshBlockWidth + 1) == g_MeshWall[nCntMesh].nMeshBlockWidth && flag == false)
				{//縮退ポリゴンの処理（上）
					Idx[0] = Idx[-1];
					Idx += 1;
					flag = true;
				}

			}

		}
		//インデックスバッファをアンロックする
		g_pIdxBuffMeshWall[nCntMesh]->Unlock();
	}
	
}

//=======================================================================================
// 外積を用いた壁の当たり判定
//---------------------------------------------------------------------------------------
//								[当たり判定の定義]
//
//	弾の現座標と前座標(pPos,pPosOld)を a,bとし、壁の始点と終点(bPos,aPos)を c,dとすると
//
//						直線abと線分cdが交差していて、かつ
//						線分abと直線cdが交差している状態である。
//
//=======================================================================================
bool CollisionMeshWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld)
{
		D3DXVECTOR3 VecA, VecB, VecC, VecD, VecE, VecF;	//それぞれのベクトルをここで定義

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse == true)
		{

			VecA = g_MeshWall[nCntWall].aPos - g_MeshWall[nCntWall].bPos;	//壁のベクトル
			VecB = *pPosOld - g_MeshWall[nCntWall].bPos;					//壁の始点と弾の前座標を結んだベクトル
			VecC = *pPos - g_MeshWall[nCntWall].bPos;						//壁の始点と弾の現座標を結んだベクトル

			VecD = *pPos - *pPosOld;										//弾のベクトル
			VecE = g_MeshWall[nCntWall].bPos - *pPosOld;					//弾の前座標と壁の始点を結んだベクトル
			VecF = g_MeshWall[nCntWall].aPos - *pPosOld;					//弾の前座標と壁の終点を結んだベクトル

			if ((VecD.z * VecE.x) - (VecD.x * VecE.z) < 0 &&
				(VecD.z * VecF.x) - (VecD.x * VecF.z) > 0)
			{//pPosとpPosOldを通る直線と、壁の線分(aPos～bPos)が交差しているか
				if ((VecA.z * VecC.x) - (VecA.x * VecC.z) < 0 &&
					(VecA.z * VecB.x) - (VecA.x * VecB.z) > 0)
				{//aPosとbPosを通る直線と、弾の線分(pPos～pPosOld)が交差しているか
					return true;
				}

			}
		}
	}
	return false;
}

//=============================================================================
// 壁の座標設定
//=============================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse == false)
		{
			g_MeshWall[nCntWall].pos = pos;
			g_MeshWall[nCntWall].rot = rot;

			g_MeshWall[nCntWall].bUse = true;
			break;
		}
	}
}


//=============================================================================
//
// 柱処理 [piller.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "piller.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PILLER_FILENAME "data/MODEL/piller000.x"
#define PILLER_MOVE_SPEED (0.7f)
#define PILLER_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_PILLER (250)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshPiller[MAX_NUM_PILLER] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatPiller[MAX_NUM_PILLER] = {};//マテリアル情報へのポインタ

PILLER g_Piller[MAX_NUM_PILLER];
//=============================================================================
// 初期化処理
//=============================================================================
void InitPiller(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPiller = 0; nCntPiller < MAX_NUM_PILLER; nCntPiller++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(PILLER_FILENAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatPiller[nCntPiller],
			NULL,
			&g_Piller[nCntPiller].NumMatModel,
			&g_pMeshPiller[nCntPiller]);

		/*当たり判定の設定*/
		//頂点数の取得
		SetPillerVertex(nCntPiller);

		g_Piller[nCntPiller].bUse = false;
		g_Piller[nCntPiller].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPiller(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_PILLER; nCntMesh++)
	{
		// メッシュの解放
		if (g_pMeshPiller[nCntMesh] != NULL)
		{
			g_pMeshPiller[nCntMesh]->Release();
			g_pMeshPiller[nCntMesh] = NULL;
		}
		/*テクスチャの解放*/
		//マテリアルの解放
		if (g_pBuffMatPiller[nCntMesh] != NULL)
		{
			g_pBuffMatPiller[nCntMesh]->Release();
			g_pBuffMatPiller[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePiller(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPiller(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	for (int nCntPiller = 0; nCntPiller < MAX_NUM_PILLER; nCntPiller++)
	{
		if (g_Piller[nCntPiller].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Piller[nCntPiller].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Piller[nCntPiller].rot.y,
				g_Piller[nCntPiller].rot.x,
				g_Piller[nCntPiller].rot.z);

			D3DXMatrixMultiply(&g_Piller[nCntPiller].mtxWorld,
				&g_Piller[nCntPiller].mtxWorld,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Piller[nCntPiller].pos.x,
				g_Piller[nCntPiller].pos.y,
				g_Piller[nCntPiller].pos.z);

			D3DXMatrixMultiply(&g_Piller[nCntPiller].mtxWorld,
				&g_Piller[nCntPiller].mtxWorld,
				&mtxTrans);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Piller[nCntPiller].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatPiller[nCntPiller]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Piller[nCntPiller].NumMatModel; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*テクスチャの設定*/
				pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

				// モデル(パーツ)の描画
				g_pMeshPiller[nCntPiller]->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=============================================================================
// 当たり判定の処理
//=============================================================================
bool CollisionPiller(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//変数宣言
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_NUM_PILLER; nCntData++)
	{
		if (g_Piller[nCntData].bUse == true)
		{
			if (g_Piller[nCntData].VtxMin.z + g_Piller[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_Piller[nCntData].VtxMax.z + g_Piller[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_Piller[nCntData].VtxMin.x + g_Piller[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_Piller[nCntData].VtxMin.x + g_Piller[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//左から右
					pPos->x = g_Piller[nCntData].VtxMin.x + g_Piller[nCntData].pos.x - pVtxMax->x;
					pMove->x = 0.0f;
				}
				if (g_Piller[nCntData].VtxMax.x + g_Piller[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_Piller[nCntData].VtxMax.x + g_Piller[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//右から左
					pPos->x = g_Piller[nCntData].VtxMax.x + g_Piller[nCntData].pos.x - pVtxMin->x;
					pMove->x = 0.0f;
				}
			}

			if (g_Piller[nCntData].VtxMin.x + g_Piller[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_Piller[nCntData].VtxMax.x + g_Piller[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_Piller[nCntData].VtxMin.z + g_Piller[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Piller[nCntData].VtxMin.z + g_Piller[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//手前から奥
					pPos->z = g_Piller[nCntData].VtxMin.z + g_Piller[nCntData].pos.z - pVtxMax->z;
					pMove->z = 0.0f;
				}
				if (g_Piller[nCntData].VtxMax.z + g_Piller[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_Piller[nCntData].VtxMax.z + g_Piller[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//奥から手前
					pPos->z = g_Piller[nCntData].VtxMax.z + g_Piller[nCntData].pos.z - pVtxMin->z;
					pMove->z = 0.0f;
				}
			}
		}
		
	}
	return bLand;

}
//=============================================================================
// 最大・最小の頂点座標を取得
//=============================================================================
void SetPillerVertex(int nCntPiller)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	g_Piller[nCntPiller].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Piller[nCntPiller].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//頂点数の取得
	nNumVtx = g_pMeshPiller[nCntPiller]->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPiller[nCntPiller]->GetFVF());

	//頂点バッファのロック
	g_pMeshPiller[nCntPiller]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

													//頂点を比較してモデルの最小・最大を抜き出す
													//x
		if (g_Piller[nCntPiller].VtxMin.x > vtx.x)
		{
			g_Piller[nCntPiller].VtxMin.x = vtx.x;
		}
		if (g_Piller[nCntPiller].VtxMax.x < vtx.x)
		{
			g_Piller[nCntPiller].VtxMax.x = vtx.x;
		}

		//y
		if (g_Piller[nCntPiller].VtxMin.y > vtx.y)
		{
			g_Piller[nCntPiller].VtxMin.y = vtx.y;
		}
		if (g_Piller[nCntPiller].VtxMax.y < vtx.y)
		{
			g_Piller[nCntPiller].VtxMax.y = vtx.y;
		}

		//z
		if (g_Piller[nCntPiller].VtxMin.z > vtx.z)
		{
			g_Piller[nCntPiller].VtxMin.z = vtx.z;
		}
		if (g_Piller[nCntPiller].VtxMax.z < vtx.z)
		{
			g_Piller[nCntPiller].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
	}
	//アンロック
	g_pMeshPiller[nCntPiller]->UnlockVertexBuffer();

}

//=============================================================================
// モデルの位置代入
//=============================================================================
void SetPiller(D3DXVECTOR3 pos)
{
	for (int nCntPiller = 0; nCntPiller < MAX_NUM_PILLER; nCntPiller++)
	{
		if (g_Piller[nCntPiller].bUse == false)
		{
			g_Piller[nCntPiller].pos = pos;
			g_Piller[nCntPiller].bUse = true;

			break;
		}
	}
}

//=============================================================================
// モデルの情報を取得
//=============================================================================
PILLER *GetPiller(void)
{
	return g_Piller;
}
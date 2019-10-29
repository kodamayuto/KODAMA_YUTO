//=============================================================================
//
// モデル処理 [model.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "model.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_FILENAME "data/MODEL/3d_001_OBJ.x"
#define MODEL_MOVE_SPEED (0.7f)
#define MODEL_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_MODEL (1)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshModel[MAX_NUM_MODEL] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatModel[MAX_NUM_MODEL] = {};//マテリアル情報へのポインタ

MODEL g_Model[MAX_NUM_MODEL];
//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_NUM_MODEL; nCntModel++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_FILENAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatModel[nCntModel],
			NULL,
			&g_Model[nCntModel].NumMatModel,
			&g_pMeshModel[nCntModel]);

		/*当たり判定の設定*/
		SetModelVertex(nCntModel);
		//頂点数の取得

		// 位置・向きの初期設定
		g_Model[nCntModel].pos = D3DXVECTOR3(-900.0f, 0.0f, 900.0f);
		g_Model[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//移動量・回転量の初期化
		g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntModel].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Model[nCntModel].bUse = true;

	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_MODEL; nCntMesh++)
	{
		// メッシュの解放
		if (g_pMeshModel[nCntMesh] != NULL)
		{
			g_pMeshModel[nCntMesh]->Release();
			g_pMeshModel[nCntMesh] = NULL;
		}
		/*テクスチャの解放*/
		//マテリアルの解放
		if (g_pBuffMatModel[nCntMesh] != NULL)
		{
			g_pBuffMatModel[nCntMesh]->Release();
			g_pBuffMatModel[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	for (int nCntModel = 0; nCntModel < MAX_NUM_MODEL; nCntModel++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Model[nCntModel].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Model[nCntModel].rot.y,
			g_Model[nCntModel].rot.x,
			g_Model[nCntModel].rot.z);

		D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorld,
			&g_Model[nCntModel].mtxWorld,
			&mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_Model[nCntModel].pos.x,
			g_Model[nCntModel].pos.y,
			g_Model[nCntModel].pos.z);

		D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorld,
			&g_Model[nCntModel].mtxWorld,
			&mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntModel].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCntModel]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Model[nCntModel].NumMatModel; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			/*テクスチャの設定*/
			pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

			// モデル(パーツ)の描画
			g_pMeshModel[nCntModel]->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// 当たり判定の処理
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//変数宣言
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_NUM_MODEL; nCntData++)
	{
		if (g_Model[nCntData].bUse == true)
		{
			if (g_Model[nCntData].VtxMin.z + g_Model[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_Model[nCntData].VtxMax.z + g_Model[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_Model[nCntData].VtxMin.x + g_Model[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_Model[nCntData].VtxMin.x + g_Model[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//左から右
					pPos->x = g_Model[nCntData].VtxMin.x + g_Model[nCntData].pos.x - pVtxMax->x;
					pMove->x = 0.0f;
				}
				if (g_Model[nCntData].VtxMax.x + g_Model[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_Model[nCntData].VtxMax.x + g_Model[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//右から左
					pPos->x = g_Model[nCntData].VtxMax.x + g_Model[nCntData].pos.x - pVtxMin->x;
					pMove->x = 0.0f;
				}
			}

			if (g_Model[nCntData].VtxMin.x + g_Model[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_Model[nCntData].VtxMax.x + g_Model[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_Model[nCntData].VtxMin.z + g_Model[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Model[nCntData].VtxMin.z + g_Model[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//手前から奥
					pPos->z = g_Model[nCntData].VtxMin.z + g_Model[nCntData].pos.z - pVtxMax->z;
					pMove->z = 0.0f;
				}
				if (g_Model[nCntData].VtxMax.z + g_Model[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_Model[nCntData].VtxMax.z + g_Model[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//奥から手前
					pPos->z = g_Model[nCntData].VtxMax.z + g_Model[nCntData].pos.z - pVtxMin->z;
					pMove->z = 0.0f;
				}
			}
		}
		
		if (((pPos->x - g_Model[nCntData].pos.x) * (pPos->x - g_Model[nCntData].pos.x)) +
			((pPos->z - g_Model[nCntData].pos.z) * (pPos->z - g_Model[nCntData].pos.z)) <=
			10000.0f)
		{
			return true;
		}
	}
	return bLand;

}
//=============================================================================
// 最大・最小の頂点座標を取得
//=============================================================================
void SetModelVertex(int nCntModel)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	g_Model[nCntModel].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Model[nCntModel].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//頂点数の取得
	nNumVtx = g_pMeshModel[nCntModel]->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel[nCntModel]->GetFVF());

	//頂点バッファのロック
	g_pMeshModel[nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

													//頂点を比較してモデルの最小・最大を抜き出す
													//x
		if (g_Model[nCntModel].VtxMin.x > vtx.x)
		{
			g_Model[nCntModel].VtxMin.x = vtx.x;
		}
		if (g_Model[nCntModel].VtxMax.x < vtx.x)
		{
			g_Model[nCntModel].VtxMax.x = vtx.x;
		}

		//y
		if (g_Model[nCntModel].VtxMin.y > vtx.y)
		{
			g_Model[nCntModel].VtxMin.y = vtx.y;
		}
		if (g_Model[nCntModel].VtxMax.y < vtx.y)
		{
			g_Model[nCntModel].VtxMax.y = vtx.y;
		}

		//z
		if (g_Model[nCntModel].VtxMin.z > vtx.z)
		{
			g_Model[nCntModel].VtxMin.z = vtx.z;
		}
		if (g_Model[nCntModel].VtxMax.z < vtx.z)
		{
			g_Model[nCntModel].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
	}
	//アンロック
	g_pMeshModel[nCntModel]->UnlockVertexBuffer();

}
//=============================================================================
// モデルの情報を取得
//=============================================================================
MODEL *GetModel(void)
{
	return g_Model;
}
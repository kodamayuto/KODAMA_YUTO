//=============================================================================
//
// モデル処理 [object.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "object.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBJECT_FILENAME1 "data/MODEL/3d_001_Chain0.x"
#define OBJECT_FILENAME2 "data/MODEL/3d_001_Mace2.x"
#define OBJECT_FILENAME3 "data/MODEL/3d_001_Box0.x"
#define OBJECT_FILENAME4 "data/MODEL/3d_001_Stone0.x"
#define OBJECT_FILENAME5 "data/MODEL/3d_001_Stone1.x"
#define OBJECT_FILENAME6 "data/MODEL/3d_001_Stone2.x"

#define OBJECT_MOVE_SPEED (0.7f)
#define OBJECT_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_OBJECT (17)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshObject[MAX_NUM_OBJECT] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatObject[MAX_NUM_OBJECT] = {};//マテリアル情報へのポインタ

OBJECT g_Object[MAX_NUM_OBJECT];
//=============================================================================
// 初期化処理
//=============================================================================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置の初期設定
	g_Object[0].FireName = OBJECT_FILENAME1;
	g_Object[0].pos = D3DXVECTOR3(998.0f, 70.0f, -800.0f);
	g_Object[0].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);

	g_Object[1].FireName = OBJECT_FILENAME2;
	g_Object[1].pos = D3DXVECTOR3(730.0f, 10.0f, -620.0f);
	g_Object[1].rot = D3DXVECTOR3(-0.1f, 0.0f, D3DX_PI * 0.15f);

	g_Object[2].FireName = OBJECT_FILENAME3;
	g_Object[2].pos = D3DXVECTOR3(400.0f, 0.0f, 500.0f);
	g_Object[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Object[3].FireName = OBJECT_FILENAME3;
	g_Object[3].pos = D3DXVECTOR3(-950.0f, 0.0f, -950.0f);
	g_Object[3].rot = D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f);

	g_Object[4].FireName = OBJECT_FILENAME1;
	g_Object[4].pos = D3DXVECTOR3(0.0f, 70.0f, -198.0f);
	g_Object[4].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

	g_Object[5].FireName = OBJECT_FILENAME4;
	g_Object[5].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Object[6].FireName = OBJECT_FILENAME5;
	g_Object[6].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	g_Object[6].rot = D3DXVECTOR3(0.0f, 0.1f, 0.0f);

	g_Object[7].FireName = OBJECT_FILENAME6;
	g_Object[7].pos = D3DXVECTOR3(-250.0f, 0.0f, 0.0f);
	g_Object[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	g_Object[8].FireName = OBJECT_FILENAME5;
	g_Object[8].pos = D3DXVECTOR3(-350.0f, 0.0f, 0.0f);
	g_Object[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Object[9].FireName = OBJECT_FILENAME6;
	g_Object[9].pos = D3DXVECTOR3(-650.0f, 0.0f, -200.0f);
	g_Object[9].rot = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	g_Object[10].FireName = OBJECT_FILENAME4;
	g_Object[10].pos = D3DXVECTOR3(-500.0f, 0.0f, -350.0f);
	g_Object[10].rot = D3DXVECTOR3(0.0f, -0.5f, 0.0f);

	g_Object[11].FireName = OBJECT_FILENAME6;
	g_Object[11].pos = D3DXVECTOR3(140.0f, 0.0f, -320.0f);
	g_Object[11].rot = D3DXVECTOR3(0.0f, 0.7f, 0.0f);

	g_Object[12].FireName = OBJECT_FILENAME5;
	g_Object[12].pos = D3DXVECTOR3(280.0f, 0.0f, -380.0f);
	g_Object[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Object[13].FireName = OBJECT_FILENAME4;
	g_Object[13].pos = D3DXVECTOR3(380.0f, 0.0f, -290.0f);
	g_Object[13].rot = D3DXVECTOR3(0.0f, 0.4f, 0.0f);

	g_Object[14].FireName = OBJECT_FILENAME5;
	g_Object[14].pos = D3DXVECTOR3(800.0f, 0.0f, -600.0f);
	g_Object[14].rot = D3DXVECTOR3(0.0f, 0.4f, 0.0f);

	g_Object[15].FireName = OBJECT_FILENAME6;
	g_Object[15].pos = D3DXVECTOR3(900.0f, 0.0f, -850.0f);
	g_Object[15].rot = D3DXVECTOR3(0.0f, 0.4f, 0.0f);

	g_Object[16].FireName = OBJECT_FILENAME5;
	g_Object[16].pos = D3DXVECTOR3(900.0f, 0.0f, 0.0f);
	g_Object[16].rot = D3DXVECTOR3(0.0f, 0.7f, 0.0f);

	for (int nCntObject = 0; nCntObject < MAX_NUM_OBJECT; nCntObject++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(g_Object[nCntObject].FireName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObject[nCntObject],
			NULL,
			&g_Object[nCntObject].NumMatModel,
			&g_pMeshObject[nCntObject]);

		/*当たり判定の設定*/
		//頂点数の取得
		SetObjectVertex(nCntObject);

		g_Object[nCntObject].bUse = true;

	}


}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObject(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_OBJECT; nCntMesh++)
	{
		// メッシュの解放
		if (g_pMeshObject[nCntMesh] != NULL)
		{
			g_pMeshObject[nCntMesh]->Release();
			g_pMeshObject[nCntMesh] = NULL;
		}
		/*テクスチャの解放*/
		//マテリアルの解放
		if (g_pBuffMatObject[nCntMesh] != NULL)
		{
			g_pBuffMatObject[nCntMesh]->Release();
			g_pBuffMatObject[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObject(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	for (int nCntObject = 0; nCntObject < MAX_NUM_OBJECT; nCntObject++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Object[nCntObject].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Object[nCntObject].rot.y,
			g_Object[nCntObject].rot.x,
			g_Object[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorld,
			&g_Object[nCntObject].mtxWorld,
			&mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_Object[nCntObject].pos.x,
			g_Object[nCntObject].pos.y,
			g_Object[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorld,
			&g_Object[nCntObject].mtxWorld,
			&mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCntObject].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Object[nCntObject].NumMatModel; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			/*テクスチャの設定*/
			pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

			// モデル(パーツ)の描画
			g_pMeshObject[nCntObject]->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// 当たり判定の処理
//=============================================================================
bool CollisionObject(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//変数宣言
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_NUM_OBJECT; nCntData++)
	{
		if (g_Object[nCntData].bUse == true)
		{
			if (g_Object[nCntData].VtxMin.z + g_Object[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_Object[nCntData].VtxMax.z + g_Object[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_Object[nCntData].VtxMin.x + g_Object[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_Object[nCntData].VtxMin.x + g_Object[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//左から右
					pPos->x = g_Object[nCntData].VtxMin.x + g_Object[nCntData].pos.x - pVtxMax->x;
					pMove->x = 0.0f;
				}
				if (g_Object[nCntData].VtxMax.x + g_Object[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_Object[nCntData].VtxMax.x + g_Object[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//右から左
					pPos->x = g_Object[nCntData].VtxMax.x + g_Object[nCntData].pos.x - pVtxMin->x;
					pMove->x = 0.0f;
				}
			}

			if (g_Object[nCntData].VtxMin.x + g_Object[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_Object[nCntData].VtxMax.x + g_Object[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_Object[nCntData].VtxMin.z + g_Object[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Object[nCntData].VtxMin.z + g_Object[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//手前から奥
					pPos->z = g_Object[nCntData].VtxMin.z + g_Object[nCntData].pos.z - pVtxMax->z;
					pMove->z = 0.0f;
				}
				if (g_Object[nCntData].VtxMax.z + g_Object[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_Object[nCntData].VtxMax.z + g_Object[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//奥から手前
					pPos->z = g_Object[nCntData].VtxMax.z + g_Object[nCntData].pos.z - pVtxMin->z;
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
void SetObjectVertex(int nCntObject)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	g_Object[nCntObject].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Object[nCntObject].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//頂点数の取得
	nNumVtx = g_pMeshObject[nCntObject]->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[nCntObject]->GetFVF());

	//頂点バッファのロック
	g_pMeshObject[nCntObject]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

													//頂点を比較してモデルの最小・最大を抜き出す
													//x
		if (g_Object[nCntObject].VtxMin.x > vtx.x)
		{
			g_Object[nCntObject].VtxMin.x = vtx.x;
		}
		if (g_Object[nCntObject].VtxMax.x < vtx.x)
		{
			g_Object[nCntObject].VtxMax.x = vtx.x;
		}

		//y
		if (g_Object[nCntObject].VtxMin.y > vtx.y)
		{
			g_Object[nCntObject].VtxMin.y = vtx.y;
		}
		if (g_Object[nCntObject].VtxMax.y < vtx.y)
		{
			g_Object[nCntObject].VtxMax.y = vtx.y;
		}

		//z
		if (g_Object[nCntObject].VtxMin.z > vtx.z)
		{
			g_Object[nCntObject].VtxMin.z = vtx.z;
		}
		if (g_Object[nCntObject].VtxMax.z < vtx.z)
		{
			g_Object[nCntObject].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
	}
	//アンロック
	g_pMeshObject[nCntObject]->UnlockVertexBuffer();

}
//=============================================================================
// モデルの情報を取得
//=============================================================================
OBJECT *Getobject(void)
{
	return g_Object;
}
//=============================================================================
//
// 背景の木処理 [woodbg.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "woodBG.h"
#include "input.h"
#include "camera.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WOODBG_NAME0	"data\\MODEL\\wood4.x"			// 木(小)のモデル名
#define WOODBG_NAME1	"data\\MODEL\\lake.x"			// 木(中)のモデル名

#define FIELD_SIZE		    (300.0f)							// フィールドの大きさ
#define WOODBG_SIZE			(5.0f)								// モデルの大きさ
#define MAX_WOODBG			(200)
#define MAX_WOODBG_TYPE		(WOODBG_TYPE_MAX)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH		    g_pMeshWoodBG[MAX_WOODBG_TYPE];	              // メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER	    g_pBuffMatWoodBG[MAX_WOODBG_TYPE];	          // マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9* g_pTextureWoodBG[MAX_WOODBG_TYPE];            // テクスチャ情報へのポインタ
DWORD			    g_nNumMatWoodBG[MAX_WOODBG_TYPE] = { 0,0 }; // マテリアル情報の数
WOODBG	        g_aWoodBG[MAX_WOODBG_TYPE][MAX_WOODBG];     // 障害物の情報
//=============================================================================
// 初期化処理
//=============================================================================
void InitWoodBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	char aXFileName[MAX_WOODBG_TYPE][64] = { WOODBG_NAME0,
		WOODBG_NAME1	,
	};

	for (int nCntType = 0; nCntType < MAX_WOODBG_TYPE; nCntType++)
	{// 障害物の種類だけ繰り返し
	 // Xファイルの読み込み
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatWoodBG[nCntType],
			NULL,
			&g_nNumMatWoodBG[nCntType],
			&g_pMeshWoodBG[nCntType]);

		// マテリアル情報からテクスチャを引き出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatWoodBG[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatWoodBG[nCntType]];
		g_pTextureWoodBG[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatWoodBG[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatWoodBG[nCntType]; nCntMat++)
		{// 頂点数の数だけ繰り返し 
		 // マテリアル情報を読み込む
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// 環境光を初期化する
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// テクスチャ情報を初期化
			g_pTextureWoodBG[nCntType][nCntMat] = NULL;

			// テクスチャの情報を読み込む
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// テクスチャのファイル名がある
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureWoodBG[nCntType][nCntMat]);
			}
		}

		for (int nCntWoodBG = 0; nCntWoodBG < MAX_WOODBG; nCntWoodBG++)
		{// 障害物の数だけ繰り返し
		 // 障害物情報の初期化
			g_aWoodBG[nCntType][nCntWoodBG].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 座標を初期化
			g_aWoodBG[nCntType][nCntWoodBG].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 向きをを初期化
			g_aWoodBG[nCntType][nCntWoodBG].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 移動量をを初期化
			g_aWoodBG[nCntType][nCntWoodBG].nType = (WOODBG_TYPE)nCntType;         // 種類をを初期化
			g_aWoodBG[nCntType][nCntWoodBG].bUse = false;                            // 使用していない状態にする

			if (nCntWoodBG == 0)
			{// 1回目だったら
				int nNumVtx;	 // 頂点数
				DWORD sizeFVF;	 // 頂点フォーマットのサイズ
				BYTE *pVtxBuff;  // 頂点バッファへのポインタ

								 // 最小値の設定
				g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// 頂点数を取得
				nNumVtx = g_pMeshWoodBG[nCntType]->GetNumVertices();

				// 頂点フォーマットのサイズを取得
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshWoodBG[nCntType]->GetFVF());

				// 頂点バッファをロック
				g_pMeshWoodBG[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// モデルの頂点数だけ繰り返し
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

					if (vtx.x < g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x)
					{// X座標がより小さい
						g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x = vtx.x;
					}
					if (vtx.y < g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y)
					{// Y座標がより小さい
						g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y = vtx.y;
					}
					if (vtx.z < g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z)
					{// Z座標がより小さい
						g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z = vtx.z;
					}

					if (vtx.x > g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x)
					{// X座標がより大きい
						g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x = vtx.x;
					}
					if (vtx.y > g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y)
					{// Y座標がより大きい
						g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y = vtx.y;
					}
					if (vtx.z > g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z)
					{// Z座標がより大きい
						g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// サイズ分ポインタを進める
				}

				// 頂点バッファをアンロック
				g_pMeshWoodBG[nCntType]->UnlockVertexBuffer();
			}
			else
			{// それ以降
				g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG = g_aWoodBG[nCntType][nCntWoodBG - 1].vtxMaxWoodBG;
				g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG = g_aWoodBG[nCntType][nCntWoodBG - 1].vtxMinWoodBG;
			}
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWoodBG(void)
{
	for (int nCntType = 0; nCntType < MAX_WOODBG_TYPE; nCntType++)
	{
		// メッシュの開放
		if (g_pMeshWoodBG[nCntType] != NULL)
		{
			g_pMeshWoodBG[nCntType]->Release();
			g_pMeshWoodBG[nCntType] = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatWoodBG[nCntType] != NULL)
		{
			g_pBuffMatWoodBG[nCntType]->Release();
			g_pBuffMatWoodBG[nCntType] = NULL;
		}
		// テクスチャの開放
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatWoodBG[nCntType]; nCntMat++)
		{
			if (g_pTextureWoodBG[nCntType][nCntMat] != NULL)
			{
				g_pTextureWoodBG[nCntType][nCntMat]->Release();
				g_pTextureWoodBG[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWoodBG(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWoodBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCntType = 0; nCntType< MAX_WOODBG_TYPE; nCntType++)
	{// 障害物の種類の数だけ繰り返し
		for (int nCntWoodBG = 0; nCntWoodBG < MAX_WOODBG; nCntWoodBG++)
		{// 障害物の数だけ繰り返し
			if (g_aWoodBG[nCntType][nCntWoodBG].bUse == true)
			{// 障害物が使用されている
			 // ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aWoodBG[nCntType][nCntWoodBG].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWoodBG[nCntType][nCntWoodBG].rot.y, g_aWoodBG[nCntType][nCntWoodBG].rot.x, g_aWoodBG[nCntType][nCntWoodBG].rot.z);
				D3DXMatrixMultiply(&g_aWoodBG[nCntType][nCntWoodBG].mtxWorld, &g_aWoodBG[nCntType][nCntWoodBG].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aWoodBG[nCntType][nCntWoodBG].pos.x, g_aWoodBG[nCntType][nCntWoodBG].pos.y, g_aWoodBG[nCntType][nCntWoodBG].pos.z);
				D3DXMatrixMultiply(&g_aWoodBG[nCntType][nCntWoodBG].mtxWorld, &g_aWoodBG[nCntType][nCntWoodBG].mtxWorld, &mtxTrans);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aWoodBG[nCntType][nCntWoodBG].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatWoodBG[nCntType]->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_nNumMatWoodBG[nCntType]; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					pDevice->SetTexture(0, g_pTextureWoodBG[nCntType][nCntMat]);

					// モデル(パーツ)の描画
					g_pMeshWoodBG[nCntType]->DrawSubset(nCntMat);
				}
				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=============================================================================
// 障害物の設定処理
//=============================================================================
void SetWoodBG(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, WOODBG_TYPE nType)
{
	for (int nCntWoodBG = 0; nCntWoodBG < MAX_WOODBG; nCntWoodBG++)
	{// 障害物の数だけ繰り返し
		if (g_aWoodBG[nType][nCntWoodBG].bUse == false)
		{// 障害物が使用されていない
		 // 位置・向きの初期設定
			g_aWoodBG[nType][nCntWoodBG].pos = pos;
			g_aWoodBG[nType][nCntWoodBG].rot = rot;
			g_aWoodBG[nType][nCntWoodBG].move = move;
			//　影のセット
			//g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);
			g_aWoodBG[nType][nCntWoodBG].bUse = true;
			break;
		}
	}

}

//=============================================================================
// 障害物の取得
//=============================================================================
WOODBG *GetWoodBG(void)
{
	return &g_aWoodBG[0][0];
}
//=============================================================================
// 障害物の当たり判定
//=============================================================================
//bool CollisionWoodBG(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
//{
//	bool bLand = false;  // 乗ったかどうか
//
//	for (int nCntType = 0; nCntType < MAX_WOODBG_TYPE; nCntType++)
//	{// 障害物の種類だけ繰り返し
//		for (int nCntWoodBG = 0; nCntWoodBG < MAX_WOODBG; nCntWoodBG++)
//		{// 障害物の数だけ繰り返し
//			if (g_aWoodBG[nCntType][nCntWoodBG].bUse == true)
//			{// 障害物が使用されている
//				if (pPos->y <= g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y && pPos->y + radius.y > g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y
//					|| pPos->y + radius.y > g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y && pPos->y < g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y
//					|| pPos->y + radius.y > g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y && pPos->y < g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.y)
//				{// 障害物のY座標の中にいる
//					if (pPos->z - radius.z <= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z && pPos->z + radius.z >= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z)
//					{// 障害物のZ座標の中にいる
//						if (pPosOld->x + radius.x <= g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x
//							&& pPos->x + radius.x > g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x)
//						{// X座標の中に左から入った
//							pPos->x = g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x - radius.x;
//							pMove->x = 0.0f;
//						}
//						else if (pPosOld->x - radius.x >= g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x
//							&& pPos->x - radius.x < g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x)
//						{// X座標の中に右から入った
//							pPos->x = g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x + radius.x + 0.1f;
//							pMove->x = 0.0f;
//						}
//					}
//					if (pPos->x - radius.x <= g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x && pPos->x + radius.x >= g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x)
//					{// 障害物のX座標の中にいる
//						if (pPosOld->z + radius.z <= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z
//							&& pPos->z + radius.z > g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z)
//						{// Z座標の中に前から入った
//							pPos->z = g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z - radius.z;
//							pMove->z = 0.0f;
//						}
//						else if (pPosOld->z - radius.z >= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z
//							&& pPos->z - radius.z < g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z)
//						{// Z座標の中に後ろから入った
//							pPos->z = g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z + radius.z + 0.1f;
//							pMove->z = 0.0f;
//						}
//					}
//
//					if (pPos->x - radius.x < g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.x - 2.0f&& pPos->x + radius.x > g_aWoodBG[nCntType][nCntWoodBG].pos.x + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.x + 2.0f
//						&& pPos->z - radius.z <= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.z - 2.0f && pPos->z + radius.z >= g_aWoodBG[nCntType][nCntWoodBG].pos.z + g_aWoodBG[nCntType][nCntWoodBG].vtxMinWoodBG.z + 2.0f)
//					{// 障害物の内側に乗った
//						bLand = true;  // 乗った判定を返す
//						pPos->y = g_aWoodBG[nCntType][nCntWoodBG].pos.y + g_aWoodBG[nCntType][nCntWoodBG].vtxMaxWoodBG.y + 0.1f;
//						pMove->y = 0.0f;  // 移動量をなくす
//					}
//				}
//			}
//		}
//	}
//
//	return bLand;   // 乗ったかどうかを返す
//}


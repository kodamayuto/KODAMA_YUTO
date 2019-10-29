//=============================================================================
//
// モデル処理 [model.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "masu.h"
#include "input.h"
#include "camera.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MASU_NAME0	"data\\MODEL\\trout\\jumpUP.x"      // マスのモデル名(ジャンプ力上昇マス)
#define MASU_NAME1	"data\\MODEL\\trout\\jumpDOWN.x"    // マスのモデル名(ジャンプ力減少マス)
#define MASU_NAME2	"data\\MODEL\\trout\\speedUP.x"     // マスのモデル名(移動力上昇マス)
#define MASU_NAME3	"data\\MODEL\\trout\\speedDOWN.x"     // マスのモデル名(移動力減少マス)
#define MASU_NAME4	"data\\MODEL\\trout\\saikoroUP.x"   // マスのモデル名(サイコロ２倍マス)
#define MASU_NAME5	"data\\MODEL\\trout\\trampoline.x"  // マスのモデル名(ジャンプ台マス)
#define MASU_NAME6	"data\\MODEL\\trout\\masu.x"  // マスのモデル名(通常マス)
#define MASU_NAME7	"data\\MODEL\\trout\\3d_001_Goal000.x"  // マスのモデル名(ゴールマス)
#define MASU_NAME8	"data\\MODEL\\trout\\start.x"  // マスのモデル名(スタートマス)
#define MAX_MASU		(50)
#define MAX_MASU_TYPE		(MASUTYPE_MAX)

// 半径147

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH		g_pMeshMasu[MASUTYPE_MAX];		  // メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER	g_pBuffMatMasu[MASUTYPE_MAX];	  // マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9* g_pTextureMasu[MASUTYPE_MAX]; // テクスチャ情報へのポインタ
DWORD			g_nNumMatMasu[MASUTYPE_MAX];      // マテリアル情報の数
MASU			g_Masu[MASUTYPE_MAX][MAX_MASU];   // マスの情報

												  //=============================================================================
												  // 初期化処理
												  //=============================================================================
void InitMasu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// xファイルのデータを読み込むために使用
	char aXFileName[MASUTYPE_MAX][64] = {
		MASU_NAME0,
		MASU_NAME1,
		MASU_NAME2,
		MASU_NAME3,
		MASU_NAME4,
		MASU_NAME5,
		MASU_NAME6,
		MASU_NAME7,
		MASU_NAME8,
	};

	for (int nCntType = 0; nCntType < MAX_MASU_TYPE; nCntType++)
	{// 障害物の種類だけ繰り返し
	 // Xファイルの読み込み
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatMasu[nCntType],
			NULL,
			&g_nNumMatMasu[nCntType],
			&g_pMeshMasu[nCntType]);

		// マテリアル情報からテクスチャを引き出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatMasu[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatMasu[nCntType]];
		g_pTextureMasu[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatMasu[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatMasu[nCntType]; nCntMat++)
		{// 頂点数の数だけ繰り返し 
		 // マテリアル情報を読み込む
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// 環境光を初期化する
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// テクスチャ情報を初期化
			g_pTextureMasu[nCntType][nCntMat] = NULL;

			// テクスチャの情報を読み込む
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// テクスチャのファイル名がある
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureMasu[nCntType][nCntMat]);
			}
		}

		for (int nCntMasu = 0; nCntMasu < MAX_MASU; nCntMasu++)
		{// 障害物の数だけ繰り返し
		 // 障害物情報の初期化
			g_Masu[nCntType][nCntMasu].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 座標を初期化
			g_Masu[nCntType][nCntMasu].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 向きをを初期化
			g_Masu[nCntType][nCntMasu].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 移動量をを初期化
			g_Masu[nCntType][nCntMasu].masuType = (MASUTYPE)nCntType;         // 種類をを初期化
			g_Masu[nCntType][nCntMasu].bUse = false;                            // 使用していない状態にする

			if (nCntMasu == 0)
			{// 1回目だったら
				int nNumVtx;	 // 頂点数
				DWORD sizeFVF;	 // 頂点フォーマットのサイズ
				BYTE *pVtxBuff;  // 頂点バッファへのポインタ

								 // 最小値の設定
				g_Masu[nCntType][nCntMasu].vtxMinMasu = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_Masu[nCntType][nCntMasu].vtxMaxMasu = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// 頂点数を取得
				nNumVtx = g_pMeshMasu[nCntType]->GetNumVertices();

				// 頂点フォーマットのサイズを取得
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshMasu[nCntType]->GetFVF());

				// 頂点バッファをロック
				g_pMeshMasu[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// モデルの頂点数だけ繰り返し
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

					if (vtx.x < g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
					{// X座標がより小さい
						g_Masu[nCntType][nCntMasu].vtxMinMasu.x = vtx.x;
					}
					if (vtx.y < g_Masu[nCntType][nCntMasu].vtxMinMasu.y)
					{// Y座標がより小さい
						g_Masu[nCntType][nCntMasu].vtxMinMasu.y = vtx.y;
					}
					if (vtx.z < g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
					{// Z座標がより小さい
						g_Masu[nCntType][nCntMasu].vtxMinMasu.z = vtx.z;
					}

					if (vtx.x > g_Masu[nCntType][nCntMasu].vtxMaxMasu.x)
					{// X座標がより大きい
						g_Masu[nCntType][nCntMasu].vtxMaxMasu.x = vtx.x;
					}
					if (vtx.y > g_Masu[nCntType][nCntMasu].vtxMaxMasu.y)
					{// Y座標がより大きい
						g_Masu[nCntType][nCntMasu].vtxMaxMasu.y = vtx.y;
					}
					if (vtx.z > g_Masu[nCntType][nCntMasu].vtxMaxMasu.z)
					{// Z座標がより大きい
						g_Masu[nCntType][nCntMasu].vtxMaxMasu.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// サイズ分ポインタを進める
				}

				// 頂点バッファをアンロック
				g_pMeshMasu[nCntType]->UnlockVertexBuffer();
			}
			else
			{// それ以降
				g_Masu[nCntType][nCntMasu].vtxMaxMasu = g_Masu[nCntType][nCntMasu - 1].vtxMaxMasu;
				g_Masu[nCntType][nCntMasu].vtxMinMasu = g_Masu[nCntType][nCntMasu - 1].vtxMinMasu;
			}
		}
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMasu(void)
{
	for (int nCntType = 0; nCntType < MASUTYPE_MAX; nCntType++)
	{// マスの種類だけ繰り返し
	 // メッシュの開放
		if (g_pMeshMasu[nCntType] != NULL)
		{
			g_pMeshMasu[nCntType]->Release();
			g_pMeshMasu[nCntType] = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatMasu[nCntType] != NULL)
		{
			g_pBuffMatMasu[nCntType]->Release();
			g_pBuffMatMasu[nCntType] = NULL;
		}
		//テクスチャの開放
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatMasu[nCntType]; nCntMat++)
		{
			if (g_pTextureMasu[nCntType][nCntMat] != NULL)
			{
				g_pTextureMasu[nCntType][nCntMat]->Release();
				g_pTextureMasu[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMasu(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMasu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCntType = 0; nCntType < MASUTYPE_MAX; nCntType++)
	{// マスの種類だけ繰り返し
		for (int nCntMasu = 0; nCntMasu < MAX_MASU; nCntMasu++)
		{// マスの数だけ繰り返し
			if (g_Masu[nCntType][nCntMasu].bUse == true)
			{// マスが使用されている
			 // ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Masu[nCntType][nCntMasu].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Masu[nCntType][nCntMasu].rot.y, g_Masu[nCntType][nCntMasu].rot.x, g_Masu[nCntType][nCntMasu].rot.z);
				D3DXMatrixMultiply(&g_Masu[nCntType][nCntMasu].mtxWorld, &g_Masu[nCntType][nCntMasu].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Masu[nCntType][nCntMasu].pos.x, g_Masu[nCntType][nCntMasu].pos.y, g_Masu[nCntType][nCntMasu].pos.z);
				D3DXMatrixMultiply(&g_Masu[nCntType][nCntMasu].mtxWorld, &g_Masu[nCntType][nCntMasu].mtxWorld, &mtxTrans);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Masu[nCntType][nCntMasu].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatMasu[nCntType]->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_nNumMatMasu[nCntType]; nCntMat++)
				{// マテリアル情報の数だけ繰り返し
				 // マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					pDevice->SetTexture(0, g_pTextureMasu[nCntType][nCntMat]);

					// モデル(パーツ)の描画
					g_pMeshMasu[nCntType]->DrawSubset(nCntMat);

				}
				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// マスの当たり判定
//=============================================================================
bool CollisionMasu(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MASU **pMasu)
{
	bool bLand = false;  // 乗ったかどうか

	D3DXVECTOR3 fData;
	D3DXVECTOR3 fData1(147.0f, 0.0f, 147.0f);
	float fLength;

	for (int nCntType = 0; nCntType < MAX_MASU_TYPE; nCntType++)
	{// 障害物の種類だけ繰り返し
		for (int nCntMasu = 0; nCntMasu < MAX_MASU; nCntMasu++)
		{// 障害物の数だけ繰り返し
			if (g_Masu[nCntType][nCntMasu].bUse == true)
			{// 障害物が使用されている
				fData = *pPos - g_Masu[nCntType][nCntMasu].pos;

				fLength = sqrtf((fData.x * fData.x) + (fData.z * fData.z));

				//// 正規化
				//D3DXVec3Normalize(&fData, &fData);

				//if (fData1.x * fData.x > fData2.x/* && fData1.z * fData.z > fData2.z*/)
				//{
				//	bLand = true;  // 乗った判定を返す
				//	pPos->y = g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y;
				//	pMove->y = 0.0f;  // 移動量をなくす
				//	*pMasu = &g_Masu[nCntType][nCntMasu];
				//}

				if (pPos->y <= g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y
					|| pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y < g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y
					|| pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y < g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y)
				{// 障害物のY座標の中にいる
				 //	if (pPos->z - radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z && pPos->z + radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
				 //	{// 障害物のZ座標の中にいる
				 //		if (pPosOld->x + radius.x <= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x
				 //			&& pPos->x + radius.x > g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
				 //		{// X座標の中に左から入った
				 //			pPos->x = g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x - radius.x;
				 //			pMove->x = 0.0f;
				 //		}
				 //		else if (pPosOld->x - radius.x >= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x
				 //			&& pPos->x - radius.x < g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x)
				 //		{// X座標の中に右から入った
				 //			pPos->x = g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x + radius.x + 0.1f;
				 //			pMove->x = 0.0f;
				 //		}
				 //	}
				 //	if (pPos->x - radius.x <= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x && pPos->x + radius.x >= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
				 //	{// 障害物のX座標の中にいる
				 //		if (pPosOld->z + radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z
				 //			&& pPos->z + radius.z > g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
				 //		{// Z座標の中に前から入った
				 //			pPos->z = g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z - radius.z;
				 //			pMove->z = 0.0f;
				 //		}
				 //		else if (pPosOld->z - radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z
				 //			&& pPos->z - radius.z < g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z)
				 //		{// Z座標の中に後ろから入った
				 //			pPos->z = g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z + radius.z + 0.1f;
				 //			pMove->z = 0.0f;
				 //		}
				 //	}

				 //	if (pPos->x - radius.x < g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x - 2.0f&& pPos->x + radius.x > g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x + 2.0f
				 //		&& pPos->z - radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z - 2.0f && pPos->z + radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z + 2.0f)
				 //	{// 障害物の内側に乗った
				 //		bLand = true;  // 乗った判定を返す
				 //		pPos->y = g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y;
				 //		pMove->y = 0.0f;  // 移動量をなくす
				 //		*pMasu = &g_Masu[nCntType][nCntMasu];
				 //	}
				 //}

				 //if (pPos->y <= g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y
				 //	|| pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y < g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y
				 //	|| pPos->y + radius.y > g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y && pPos->y < g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMinMasu.y)
				 //{// 障害物のY座標の中にいる
				 //	if (pPos->z - radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z && pPos->z + radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
				 //	{// 障害物のZ座標の中にいる
				 //		if (pPosOld->x + radius.x <= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x
				 //			&& pPos->x + radius.x > g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
				 //		{// X座標の中に左から入った
				 //			pPos->x = g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x - radius.x;
				 //			pMove->x = 0.0f;
				 //		}
				 //		else if (pPosOld->x - radius.x >= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x
				 //			&& pPos->x - radius.x < g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x)
				 //		{// X座標の中に右から入った
				 //			pPos->x = g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x + radius.x + 0.1f;
				 //			pMove->x = 0.0f;
				 //		}
				 //	}
				 //	if (pPos->x - radius.x <= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x && pPos->x + radius.x >= g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x)
				 //	{// 障害物のX座標の中にいる
				 //		if (pPosOld->z + radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z
				 //			&& pPos->z + radius.z > g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z)
				 //		{// Z座標の中に前から入った
				 //			pPos->z = g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z - radius.z;
				 //			pMove->z = 0.0f;
				 //		}
				 //		else if (pPosOld->z - radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z
				 //			&& pPos->z - radius.z < g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z)
				 //		{// Z座標の中に後ろから入った
				 //			pPos->z = g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z + radius.z + 0.1f;
				 //			pMove->z = 0.0f;
				 //		}
				 //	}

				 //if (pPos->x - radius.x < g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMaxMasu.x - 2.0f&& pPos->x + radius.x > g_Masu[nCntType][nCntMasu].pos.x + g_Masu[nCntType][nCntMasu].vtxMinMasu.x + 2.0f
				 //	&& pPos->z - radius.z <= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMaxMasu.z - 2.0f && pPos->z + radius.z >= g_Masu[nCntType][nCntMasu].pos.z + g_Masu[nCntType][nCntMasu].vtxMinMasu.z + 2.0f)
				 //{// 障害物の内側に乗った
				 //	bLand = true;  // 乗った判定を返す
				 //	pPos->y = g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y;
				 //	pMove->y = 0.0f;  // 移動量をなくす
				 //	*pMasu = &g_Masu[nCntType][nCntMasu];
				 //}

					if (fLength < 134)
					{// 障害物の内側に乗った
						bLand = true;  // 乗った判定を返す
						pPos->y = g_Masu[nCntType][nCntMasu].pos.y + g_Masu[nCntType][nCntMasu].vtxMaxMasu.y;
						pMove->y = 0.0f;  // 移動量をなくす
						*pMasu = &g_Masu[nCntType][nCntMasu];
					}
				}
			}
		}
	}

	return bLand;   // 乗ったかどうかを返す
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetMasu(D3DXVECTOR3 pos, MASUTYPE Type)
{
	for (int nCntMasu = 0; nCntMasu < MAX_MASU; nCntMasu++)
	{// マスの数だけ繰り返し
		if (g_Masu[Type][nCntMasu].bUse == false)
		{// マスが使用されていない
			g_Masu[Type][nCntMasu].pos = pos;    // 座標を設定
			g_Masu[Type][nCntMasu].bUse = true;  // 使用されている状態にする
			break;
		}
	}
}

//=============================================================================
// 一番近いマスの取得
//=============================================================================
D3DXVECTOR3 PlayerDistance(void)
{
	return g_Masu[MASUTYPE_GOAL][0].pos;
}

//=============================================================================
// マスの取得
//=============================================================================
MASU *GetMasu(void)
{
	return &g_Masu[0][0];
}
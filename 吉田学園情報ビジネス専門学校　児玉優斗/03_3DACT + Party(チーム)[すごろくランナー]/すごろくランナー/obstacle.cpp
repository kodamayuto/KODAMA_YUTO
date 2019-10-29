//=============================================================================
//
// 障害物の処理処理 [obstacle.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "obstacle.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBSTACLE_NAME0	"data\\MODEL\\obstacle\\logS.x"			// 木(小)のモデル名
#define OBSTACLE_NAME1	"data\\MODEL\\obstacle\\logM.x"			// 木(中)のモデル名
#define OBSTACLE_NAME2	"data\\MODEL\\obstacle\\logL.x"			// 木(大)のモデル名
#define OBSTACLE_NAME3	"data\\MODEL\\obstacle\\move.x"			// 倒木のモデル名
#define OBSTACLE_NAME4	"data\\MODEL\\obstacle\\move.x"			// 倒木のモデル名
#define OBSTACLE_NAME5	"data\\MODEL\\obstacle\\logL.x"			// 倒木のモデル名
#define OBSTACLE_NAME6	"data\\MODEL\\obstacle\\logBase.x"			// 倒木のモデル名
#define OBSTACLE_NAME7	"data\\MODEL\\obstacle\\logM.x"	    // 移動丸太のモデル名
#define OBSTACLE_NAME8	"data\\MODEL\\obstacle\\logFat.x"	    // 太い丸太のモデル名
#define OBSTACLE_NAME9	"data\\MODEL\\obstacle\\logL.x"			// 木(左回転)のモデル名
#define OBSTACLE_NAME10	"data\\MODEL\\obstacle\\logL.x"			// 木(右回転)のモデル名
#define OBSTACLE_NAME11	"data\\MODEL\\obstacle\\logStairs_S.x"	// 木（階段）S
#define OBSTACLE_NAME12	"data\\MODEL\\obstacle\\logStairs_M.x"	// 木（階段）M
#define OBSTACLE_NAME13	"data\\MODEL\\obstacle\\logStairs_L.x"	// 木（階段）L
#define OBSTACLE_NAME14	"data\\MODEL\\obstacle\\halflogStairs_S.x"	// 木（階段半分）S
#define OBSTACLE_NAME15	"data\\MODEL\\obstacle\\halflogStairs_M.x"	// 木（階段半分）M
#define OBSTACLE_NAME16	"data\\MODEL\\obstacle\\halflogStairs_L.x"	// 木（階段半分）L
#define FIELD_SIZE		    (300.0f)							// フィールドの大きさ
#define OBSTACLE_SIZE		(5.0f)								// モデルの大きさ
#define MAX_OBSTACLE		(200)
#define MAX_OBSTACLE_TYPE   (OBSTACLE_TYPE_MAX)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH		    g_pMeshObstacle[MAX_OBSTACLE_TYPE];	              // メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER	    g_pBuffMatObstacle[MAX_OBSTACLE_TYPE];	          // マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9* g_pTextureObstacle[MAX_OBSTACLE_TYPE];            // テクスチャ情報へのポインタ
DWORD			    g_nNumMatObstacle[MAX_OBSTACLE_TYPE] = { 0,0,0,0 }; // マテリアル情報の数
OBSTACLE	        g_aObstacle[MAX_OBSTACLE_TYPE][MAX_OBSTACLE];     // 障害物の情報
int g_nMoveTimer;
//=============================================================================
// 初期化処理
//=============================================================================
void InitObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nMoveTimer = 0;
	char aXFileName[MAX_OBSTACLE_TYPE][64] = { OBSTACLE_NAME0,
		OBSTACLE_NAME1	,
		OBSTACLE_NAME2,
		OBSTACLE_NAME3,
		OBSTACLE_NAME4,
		OBSTACLE_NAME5,
		OBSTACLE_NAME6,
		OBSTACLE_NAME7,
		OBSTACLE_NAME8,
		OBSTACLE_NAME9,
		OBSTACLE_NAME10,
		OBSTACLE_NAME11,
		OBSTACLE_NAME12,
		OBSTACLE_NAME13,
		OBSTACLE_NAME14,
		OBSTACLE_NAME15,
		OBSTACLE_NAME16,
	};

	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// 障害物の種類だけ繰り返し
	 // Xファイルの読み込み
		D3DXLoadMeshFromX(aXFileName[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObstacle[nCntType],
			NULL,
			&g_nNumMatObstacle[nCntType],
			&g_pMeshObstacle[nCntType]);

		// マテリアル情報からテクスチャを引き出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType]->GetBufferPointer();
		D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_nNumMatObstacle[nCntType]];
		g_pTextureObstacle[nCntType] = new LPDIRECT3DTEXTURE9[g_nNumMatObstacle[nCntType]];

		for (DWORD nCntMat = 0; nCntMat < g_nNumMatObstacle[nCntType]; nCntMat++)
		{// 頂点数の数だけ繰り返し 
		 // マテリアル情報を読み込む
			pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

			// 環境光を初期化する
			pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

			// テクスチャ情報を初期化
			g_pTextureObstacle[nCntType][nCntMat] = NULL;

			// テクスチャの情報を読み込む
			if (pMat[nCntMat].pTextureFilename != NULL &&
				lstrlen(pMat[nCntMat].pTextureFilename) > 0)
			{// テクスチャのファイル名がある
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureObstacle[nCntType][nCntMat]);
			}
		}

		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// 障害物の数だけ繰り返し
		 // 障害物情報の初期化
			g_aObstacle[nCntType][nCntObstacle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 座標を初期化
			g_aObstacle[nCntType][nCntObstacle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 向きをを初期化
			g_aObstacle[nCntType][nCntObstacle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 移動量をを初期化
			g_aObstacle[nCntType][nCntObstacle].nType = (OBSTACLE_TYPE)nCntType;         // 種類をを初期化
			g_aObstacle[nCntType][nCntObstacle].bUse = false;                            // 使用していない状態にする
			for (int nCntVer = 0; nCntVer < 4; nCntVer++)
			{// 頂点数の数だけ繰り返し
				g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

			if (nCntObstacle == 0)
			{// 1回目だったら
				int nNumVtx;	 // 頂点数
				DWORD sizeFVF;	 // 頂点フォーマットのサイズ
				BYTE *pVtxBuff;  // 頂点バッファへのポインタ

								 // 最小値の設定
				g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
				g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

				// 頂点数を取得
				nNumVtx = g_pMeshObstacle[nCntType]->GetNumVertices();

				// 頂点フォーマットのサイズを取得
				sizeFVF = D3DXGetFVFVertexSize(g_pMeshObstacle[nCntType]->GetFVF());

				// 頂点バッファをロック
				g_pMeshObstacle[nCntType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{// モデルの頂点数だけ繰り返し
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

					if (vtx.x < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x)
					{// X座標がより小さい
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.x = vtx.x;
					}
					if (vtx.y < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y)
					{// Y座標がより小さい
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y = vtx.y;
					}
					if (vtx.z < g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z)
					{// Z座標がより小さい
						g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.z = vtx.z;
					}

					if (vtx.x > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x)
					{// X座標がより大きい
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.x = vtx.x;
					}
					if (vtx.y > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y)
					{// Y座標がより大きい
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y = vtx.y;
					}
					if (vtx.z > g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z)
					{// Z座標がより大きい
						g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.z = vtx.z;
					}

					pVtxBuff += sizeFVF;	// サイズ分ポインタを進める
				}

				// 頂点バッファをアンロック
				g_pMeshObstacle[nCntType]->UnlockVertexBuffer();
			}
			else
			{// それ以降
				g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle = g_aObstacle[nCntType][nCntObstacle - 1].vtxMaxObstacle;
				g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle = g_aObstacle[nCntType][nCntObstacle - 1].vtxMinObstacle;
			}
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObstacle(void)
{
	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{
		// メッシュの開放
		if (g_pMeshObstacle[nCntType] != NULL)
		{
			g_pMeshObstacle[nCntType]->Release();
			g_pMeshObstacle[nCntType] = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatObstacle[nCntType] != NULL)
		{
			g_pBuffMatObstacle[nCntType]->Release();
			g_pBuffMatObstacle[nCntType] = NULL;
		}
		// テクスチャの開放
		for (DWORD nCntMat = 0; nCntMat < g_nNumMatObstacle[nCntType]; nCntMat++)
		{
			if (g_pTextureObstacle[nCntType][nCntMat] != NULL)
			{
				g_pTextureObstacle[nCntType][nCntMat]->Release();
				g_pTextureObstacle[nCntType][nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObstacle(void)
{
	g_nMoveTimer++;
	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// 障害物の種類の数だけ繰り返し
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// 障害物の置ける数だけ繰り返し
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// 障害物が使用されている
			 // 前回の位置更新
				g_aObstacle[nCntType][nCntObstacle].posold = g_aObstacle[nCntType][nCntObstacle].pos;

				// 移動させる
				g_aObstacle[nCntType][nCntObstacle].pos += g_aObstacle[nCntType][nCntObstacle].move;

				switch (g_aObstacle[nCntType][nCntObstacle].nType)
				{// 障害物の種類ごとに処理わけ
				case OBSTACLE_TYPE_LOG_S:	//ｓサイズ丸太
					break;
				case OBSTACLE_TYPE_LOG_M:	//ｍサイズ丸太
					break;
				case OBSTACLE_TYPE_LOG_L:	//ｌサイズ丸太203268535
					break;

				case OBSTACLE_TYPE_MOVE:	//移動床
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// プレイヤーの数だけ繰り返し
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;
				case OBSTACLE_TYPE_HALFMOVE://移動半分床
					if (g_nMoveTimer % 92 == 0)
					{
						g_aObstacle[nCntType][nCntObstacle].move.x *= -1;
						g_aObstacle[nCntType][nCntObstacle].move.z *= -1;
					}
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// プレイヤーの数だけ繰り返し
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;
				case OBSTACLE_TYPE_UPDOWNLOG://上下移動丸太
					if (g_nMoveTimer % 50 == 0)
					{
						g_aObstacle[nCntType][nCntObstacle].move.y *= -1;
					}
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// プレイヤーの数だけ繰り返し
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;
				case OBSTACLE_TYPE_LOGMOVE://移動丸太
					if (g_nMoveTimer % 92 == 0)
					{
						g_aObstacle[nCntType][nCntObstacle].move.x *= -1;
						g_aObstacle[nCntType][nCntObstacle].move.z *= -1;
					}
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// プレイヤーの数だけ繰り返し
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;
				case OBSTACLE_TYPE_ROLL_LEFT:// 左回転丸太
					g_aObstacle[nCntType][nCntObstacle].rot.y -= D3DX_PI / 120;
					if (g_aObstacle[nCntType][nCntObstacle].rot.y <= -D3DX_PI)
					{
						g_aObstacle[nCntType][nCntObstacle].rot.y = D3DX_PI;
					}
					g_aObstacle[nCntType][nCntObstacle].pos.x = g_aObstacle[nCntType][nCntObstacle].pos.x - sinf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
					g_aObstacle[nCntType][nCntObstacle].pos.z = g_aObstacle[nCntType][nCntObstacle].pos.z - cosf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// プレイヤーの数だけ繰り返し
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;

				case OBSTACLE_TYPE_ROLL_RIGHT:// 左回転丸太
					g_aObstacle[nCntType][nCntObstacle].rot.y += D3DX_PI / 120;
					if (g_aObstacle[nCntType][nCntObstacle].rot.y >= D3DX_PI)
					{
						g_aObstacle[nCntType][nCntObstacle].rot.y = -D3DX_PI;
					}
					g_aObstacle[nCntType][nCntObstacle].pos.x = g_aObstacle[nCntType][nCntObstacle].pos.x - sinf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
					g_aObstacle[nCntType][nCntObstacle].pos.z = g_aObstacle[nCntType][nCntObstacle].pos.z - cosf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{// プレイヤーの数だけ繰り返し
						CollisionMoveOb(g_aObstacle[nCntType][nCntObstacle].pos, g_aObstacle[nCntType][nCntObstacle].posold, g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle, g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle, nCntPlayer);
					}
					break;

				case OBSTACLE_TYPE_STAIRS_S:
					if (GetKeyboardPress(DIK_9) == true)
					{
						g_aObstacle[nCntType][nCntObstacle].rot.y += 0.04f;
					}
					break;
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nCntType = 0; nCntType< MAX_OBSTACLE_TYPE; nCntType++)
	{// 障害物の種類の数だけ繰り返し
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// 障害物の数だけ繰り返し
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// 障害物が使用されている
			 // ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aObstacle[nCntType][nCntObstacle].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObstacle[nCntType][nCntObstacle].rot.y, g_aObstacle[nCntType][nCntObstacle].rot.x, g_aObstacle[nCntType][nCntObstacle].rot.z);
				D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aObstacle[nCntType][nCntObstacle].pos.x, g_aObstacle[nCntType][nCntObstacle].pos.y, g_aObstacle[nCntType][nCntObstacle].pos.z);
				D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld, &mtxTrans);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aObstacle[nCntType][nCntObstacle].mtxWorld);

				for (int nCntVer = 0; nCntVer < 4; nCntVer++)
				{// 頂点数の数だけ繰り返し
				 // ワールドマトリックスの初期化
					D3DXMatrixIdentity(&g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld);

					// 回転を反映
					D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].rot.y, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].rot.x, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].rot.z);
					D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &mtxRot);

					// 位置を反映
					D3DXMatrixTranslation(&mtxTrans, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].pos.x, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].pos.y, g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].pos.z);
					D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &mtxTrans);

					// 親のマトリックスを掛け合わせる
					D3DXMatrixMultiply(&g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].Vertex[nCntVer].mtxWorld, &g_aObstacle[nCntType][nCntObstacle].mtxWorld);
				}

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType]->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_nNumMatObstacle[nCntType]; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					pDevice->SetTexture(0, g_pTextureObstacle[nCntType][nCntMat]);

					// モデル(パーツ)の描画
					g_pMeshObstacle[nCntType]->DrawSubset(nCntMat);
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
void SetObstacle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, OBSTACLE_TYPE nType)
{
	for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
	{// 障害物の数だけ繰り返し
		if (g_aObstacle[nType][nCntObstacle].bUse == false)
		{// 障害物が使用されていない
		 // 位置・向きの初期設定
			g_aObstacle[nType][nCntObstacle].pos = pos;
			g_aObstacle[nType][nCntObstacle].rot = rot;
			g_aObstacle[nType][nCntObstacle].move = move;
			//　影のセット
			//g_aModel[nCntModel].nIdxShadow = SetShadow(g_aModel[nCntModel].pos, D3DXVECTOR3(0, 0, 0), 20.0f);

			g_aObstacle[nType][nCntObstacle].Vertex[0].pos = D3DXVECTOR3(g_aObstacle[nType][nCntObstacle].vtxMinObstacle.x - 8.0f, 0.0f, g_aObstacle[nType][nCntObstacle].vtxMaxObstacle.z + 8.0f);
			g_aObstacle[nType][nCntObstacle].Vertex[1].pos = D3DXVECTOR3(g_aObstacle[nType][nCntObstacle].vtxMaxObstacle.x + 8.0f, 0.0f, g_aObstacle[nType][nCntObstacle].vtxMaxObstacle.z + 8.0f);
			g_aObstacle[nType][nCntObstacle].Vertex[2].pos = D3DXVECTOR3(g_aObstacle[nType][nCntObstacle].vtxMaxObstacle.x + 8.0f, 0.0f, g_aObstacle[nType][nCntObstacle].vtxMinObstacle.z - 8.0f);
			g_aObstacle[nType][nCntObstacle].Vertex[3].pos = D3DXVECTOR3(g_aObstacle[nType][nCntObstacle].vtxMinObstacle.x - 8.0f, 0.0f, g_aObstacle[nType][nCntObstacle].vtxMinObstacle.z - 8.0f);

			g_aObstacle[nType][nCntObstacle].bUse = true;
			break;
		}
	}

}

//=============================================================================
// 障害物の取得
//=============================================================================
OBSTACLE *GetObstacle(void)
{
	return &g_aObstacle[0][0];
}
//=============================================================================
// 障害物の当たり判定
//=============================================================================
bool CollisionObstacle(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
{
	bool bLand = false;  // 乗ったかどうか

						 // 外積の当たり判定用
	D3DXVECTOR3 vecA, vecC;
	D3DXVECTOR3 aVerPos[4];
	int nCntVec = 0;

	for (int nCntType = 0; nCntType < MAX_OBSTACLE_TYPE; nCntType++)
	{// 障害物の種類だけ繰り返し
		for (int nCntObstacle = 0; nCntObstacle < MAX_OBSTACLE; nCntObstacle++)
		{// 障害物の数だけ繰り返し
			if (g_aObstacle[nCntType][nCntObstacle].bUse == true)
			{// 障害物が使用されている
				nCntVec = 0;
				// そのコースの頂点座標を取得
				aVerPos[0] = D3DXVECTOR3(g_aObstacle[nCntType][nCntObstacle].Vertex[0].mtxWorld._41, g_aObstacle[nCntType][nCntObstacle].Vertex[0].mtxWorld._42, g_aObstacle[nCntType][nCntObstacle].Vertex[0].mtxWorld._43);
				aVerPos[1] = D3DXVECTOR3(g_aObstacle[nCntType][nCntObstacle].Vertex[1].mtxWorld._41, g_aObstacle[nCntType][nCntObstacle].Vertex[1].mtxWorld._42, g_aObstacle[nCntType][nCntObstacle].Vertex[1].mtxWorld._43);
				aVerPos[2] = D3DXVECTOR3(g_aObstacle[nCntType][nCntObstacle].Vertex[2].mtxWorld._41, g_aObstacle[nCntType][nCntObstacle].Vertex[2].mtxWorld._42, g_aObstacle[nCntType][nCntObstacle].Vertex[2].mtxWorld._43);
				aVerPos[3] = D3DXVECTOR3(g_aObstacle[nCntType][nCntObstacle].Vertex[3].mtxWorld._41, g_aObstacle[nCntType][nCntObstacle].Vertex[3].mtxWorld._42, g_aObstacle[nCntType][nCntObstacle].Vertex[3].mtxWorld._43);

				for (int nCntVer = 0; nCntVer < 4; nCntVer++)
				{// 頂点数の数だけ繰り返し
					vecC = *pPos - aVerPos[nCntVer];
					vecA = aVerPos[(nCntVer + 1) % 4] - aVerPos[nCntVer];

					if ((vecA.z * vecC.x) - (vecA.x * vecC.z) < 0)
					{// そのベクトルの外側にいる
						nCntVec++;
					}
				}

				if (pPos->y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 5.0f && pPos->y + radius.y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 5.0f
					|| pPos->y + radius.y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y && pPos->y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y
					|| pPos->y + radius.y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 5.0f && pPos->y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMinObstacle.y)
				{// 障害物のY座標の中にいる
					if (nCntVec == 0)
					{// 一度もベクトルの外側にいなかった
						pPos->x = pPosOld->x;
						pPos->z = pPosOld->z;
						pPos->x -= pMove->x * 0.001f;
						pPos->z -= pMove->z * 0.001f;
						pPos->x += g_aObstacle[nCntType][nCntObstacle].move.x;
						pPos->z += g_aObstacle[nCntType][nCntObstacle].move.z;
					}
				}
				if (pPosOld->y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPos->y < g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y
					|| pPos->y <= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y && pPosOld->y > g_aObstacle[nCntType][nCntObstacle].posold.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y
					/*					|| g_aObstacle[nCntType][nCntObstacle].posold.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y <= pPos->y && g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y >= pPos->y && pPos->y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 20.0f
					|| g_aObstacle[nCntType][nCntObstacle].posold.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y <= pPosOld->y && g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y >= pPosOld->y && pPos->y >= g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y - 20.0f*/)
				{// 障害物の内側に乗った
					if (nCntVec == 0)
					{// 一度もベクトルの外側にいなかった
						bLand = true;     // 乗った判定を返す
						pPos->y = g_aObstacle[nCntType][nCntObstacle].pos.y + g_aObstacle[nCntType][nCntObstacle].vtxMaxObstacle.y + 0.1f;
						pMove->y = 0.0f;  // 移動量をなくす
						*pPos += g_aObstacle[nCntType][nCntObstacle].move;
						if (g_aObstacle[nCntType][nCntObstacle].nType == OBSTACLE_TYPE_ROLL_LEFT || g_aObstacle[nCntType][nCntObstacle].nType == OBSTACLE_TYPE_ROLL_RIGHT)
						{// まわる動きをする障害物ならば
							pPos->x = g_aObstacle[nCntType][nCntObstacle].pos.x - sinf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
							pPos->z = g_aObstacle[nCntType][nCntObstacle].pos.z - cosf(g_aObstacle[nCntType][nCntObstacle].rot.y) * 1.5f;
						}
					}
				}
			}
		}
	}

	return bLand;   // 乗ったかどうかを返す
}

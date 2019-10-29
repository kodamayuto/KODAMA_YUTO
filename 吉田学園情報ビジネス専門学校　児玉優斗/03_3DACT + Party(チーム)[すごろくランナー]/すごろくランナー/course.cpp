//=============================================================================
//
// コースの処理 [course.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "course.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COURSE_TEXTURE_NAME	"data\\TEXTURE\\course000.jpg"	// 地面のテクスチャ名
#define COURSE_SIZE_X		(50.0f)							// 地面大きさ
#define COURSE_SIZE_Z		(200.0f)						// 地面大きさ
#define MAX_COURSE			(126)							// コースの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexCourse(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffCourse = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureCourse = NULL;	// テクスチャへのポインタ
COURSE					g_aCourse[MAX_COURSE];

//=============================================================================
// 初期化処理
//=============================================================================
void InitCourse(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

												// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, COURSE_TEXTURE_NAME, &g_pTextureCourse);

	// 頂点情報の作成
	MakeVertexCourse(pDevice);

	for (int nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{// コースの数だけ繰り返し
		// ポリゴンの情報を設定
		g_aCourse[nCntCourse].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_aCourse[nCntCourse].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_aCourse[nCntCourse].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
		g_aCourse[nCntCourse].fDepth = 0.0f;						// 奥行
		g_aCourse[nCntCourse].fWidth = 0.0f;						// 幅
		for(int nCntVer = 0;nCntVer < 4;nCntVer++)
		{// 頂点数の数だけ繰り返し
			g_aCourse[nCntCourse].Vertex[nCntVer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aCourse[nCntCourse].Vertex[nCntVer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		g_aCourse[nCntCourse].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCourse(void)
{
	// テクスチャの破棄
	if (g_pTextureCourse != NULL)
	{
		g_pTextureCourse->Release();
		g_pTextureCourse = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffCourse != NULL)
	{
		g_pVtxBuffCourse->Release();
		g_pVtxBuffCourse = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCourse(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCourse(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// デバイスの取得
	pDevice = GetDevice();

	for (int nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aCourse[nCntCourse].mtxWorldCourse);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCourse[nCntCourse].rot.y, g_aCourse[nCntCourse].rot.x, g_aCourse[nCntCourse].rot.z);
		D3DXMatrixMultiply(&g_aCourse[nCntCourse].mtxWorldCourse, &g_aCourse[nCntCourse].mtxWorldCourse, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aCourse[nCntCourse].pos.x, g_aCourse[nCntCourse].pos.y, g_aCourse[nCntCourse].pos.z);
		D3DXMatrixMultiply(&g_aCourse[nCntCourse].mtxWorldCourse, &g_aCourse[nCntCourse].mtxWorldCourse, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aCourse[nCntCourse].mtxWorldCourse);

		for (int nCntVer = 0; nCntVer < 4; nCntVer++)
		{// 頂点数の数だけ繰り返し
		    // ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCourse[nCntCourse].Vertex[nCntVer].rot.y, g_aCourse[nCntCourse].Vertex[nCntVer].rot.x, g_aCourse[nCntCourse].Vertex[nCntVer].rot.z);
			D3DXMatrixMultiply(&g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aCourse[nCntCourse].Vertex[nCntVer].pos.x, g_aCourse[nCntCourse].Vertex[nCntVer].pos.y, g_aCourse[nCntCourse].Vertex[nCntVer].pos.z);
			D3DXMatrixMultiply(&g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &mtxTrans);

			// 親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &g_aCourse[nCntCourse].mtxWorldCourse);
		}

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffCourse, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCourse);

		if (g_aCourse[nCntCourse].bUse == true)	// 弾が使用されている
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntCourse,
				2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexCourse(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_COURSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCourse,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCourse->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aCourse[nCntCourse].fWidth, 0.0f, g_aCourse[nCntCourse].fDepth);
		pVtx[1].pos = D3DXVECTOR3(g_aCourse[nCntCourse].fWidth, 0.0f, g_aCourse[nCntCourse].fDepth);
		pVtx[2].pos = D3DXVECTOR3(-g_aCourse[nCntCourse].fWidth, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCourse[nCntCourse].fWidth, 0.0f, 0.0f);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点データのポインタを4つ分進める
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffCourse->Unlock();
}

//=============================================================================
// コースの設定
//=============================================================================
void SetCourse(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth)
{
	int nCntCourse;

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCourse->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{
		if (g_aCourse[nCntCourse].bUse == false)
		{
			g_aCourse[nCntCourse].fWidth = fWidth;
			g_aCourse[nCntCourse].fDepth = fDepth;
			g_aCourse[nCntCourse].pos = pos;
			g_aCourse[nCntCourse].rot = rot;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aCourse[nCntCourse].fWidth, 0.0f, g_aCourse[nCntCourse].fDepth);
			pVtx[1].pos = D3DXVECTOR3(g_aCourse[nCntCourse].fWidth, 0.0f, g_aCourse[nCntCourse].fDepth);
			pVtx[2].pos = D3DXVECTOR3(-g_aCourse[nCntCourse].fWidth, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aCourse[nCntCourse].fWidth, 0.0f, 0.0f);


			for (int nCntVer = 0; nCntVer < 4; nCntVer++)
			{// 頂点数の数だけ繰り返し
				g_aCourse[nCntCourse].Vertex[nCntVer].pos = pVtx[nCntVer].pos;
			}

			g_aCourse[nCntCourse].bUse = true;
			break;
		}
		pVtx += 4;	// 該当の位置まで進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffCourse->Unlock();
}
//=============================================================================
// コースとの当たり判定
//=============================================================================
bool CollisionCourse(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
{
	// コースに乗ったか乗っていないか
	bool bLand = false;

	// 外積の当たり判定用
	D3DXVECTOR3 vecA, vecC;
	D3DXVECTOR3 aVerPos[4];
	int nCntVec = 0;

	for (int nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{// コースの数だけ繰り返し
		if (g_aCourse[nCntCourse].bUse == true)
		{// コースが使用されている
			if (pPosOld->y >= g_aCourse[nCntCourse].pos.y && pPos->y < g_aCourse[nCntCourse].pos.y)
			{// コースより上にいたのに落ちている
				nCntVec = 0;
				// そのコースの頂点座標を取得
				aVerPos[0] = D3DXVECTOR3(g_aCourse[nCntCourse].Vertex[0].mtxWorld._41, g_aCourse[nCntCourse].Vertex[0].mtxWorld._42, g_aCourse[nCntCourse].Vertex[0].mtxWorld._43);
				aVerPos[1] = D3DXVECTOR3(g_aCourse[nCntCourse].Vertex[1].mtxWorld._41, g_aCourse[nCntCourse].Vertex[1].mtxWorld._42, g_aCourse[nCntCourse].Vertex[1].mtxWorld._43);
				aVerPos[3] = D3DXVECTOR3(g_aCourse[nCntCourse].Vertex[2].mtxWorld._41, g_aCourse[nCntCourse].Vertex[2].mtxWorld._42, g_aCourse[nCntCourse].Vertex[2].mtxWorld._43);
				aVerPos[2] = D3DXVECTOR3(g_aCourse[nCntCourse].Vertex[3].mtxWorld._41, g_aCourse[nCntCourse].Vertex[3].mtxWorld._42, g_aCourse[nCntCourse].Vertex[3].mtxWorld._43);
				for (int nCntVer = 0; nCntVer < 4; nCntVer++)
				{// 頂点数の数だけ繰り返し
					vecC = *pPos - aVerPos[nCntVer];
					vecA = aVerPos[(nCntVer + 1) % 4] - aVerPos[nCntVer];

					if ((vecA.z * vecC.x) - (vecA.x * vecC.z) < 0)
					{// そのベクトルの外側にいる
						nCntVec++;
					}
				}
				if (nCntVec == 0)
				{// 一度もベクトルの外側にいなかった
					pPos->y = g_aCourse[nCntCourse].pos.y;
					pMove->y = 0.0f;
					bLand = true;
				}
			}
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffCourse->Unlock();

	return bLand;
}
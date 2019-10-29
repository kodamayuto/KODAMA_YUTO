//=============================================================================
//
// ランキングスコア処理 [rankingscore.cpp]
// Author : 高橋美優
// Editor : Yuto Kodama
//
//=============================================================================
#include "rankingscore.h"
#include "score.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RANKINGSCORE	"data/TEXTURE/score.png"	// 読み込むテクスチャファイル名
#define MAX_RANKINGSCORE		(8)							// 桁の最大数
#define MIN_RANKINGSCORE		(6)
#define MAX_LENGTH				(5)							// 縦に出す数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRankingscore(LPDIRECT3DDEVICE9 pDevice);		// 頂点情報の作成

															//*****************************************************************************
															// グローバル変数
															//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRankingscore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingscore = NULL;		// 頂点バッファへのポインタ
int	g_nRankingscore;										// 入れ替え用(ソート)
int	g_nRankingscore2;										// 入れ替え用(ソート)
Ranking g_Ranking[MAX_LENGTH][MAX_RANKINGSCORE];
int g_aHighscore[MAX_LENGTH];								// 5個変数を格納できる
bool bRanking = true;										// ランキング記憶

int g_nDrawRanking = 4;
//=============================================================================
// 初期化処理
//=============================================================================
void InitRankingscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNum = 100000000;
	int nNum1 = 10000000;
	int nCnt;
	int nCntLength;

	// 初期化
	g_nRankingscore = 0;
	g_nRankingscore2 = 0;

	// 縦に何個出すかのfor文の初期化
	for (nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{// 何桁にするかのfor文の初期化
		for (nCnt = 0; nCnt < MAX_RANKINGSCORE; nCnt++)
		{// 桁の座標の計算 
			g_Ranking[nCntLength][nCnt].g_aRankingscore = 0;
		}
	}

	// 数字のスコアの初期化
	if (bRanking == true)
	{
		g_aHighscore[0] = 10;
		g_aHighscore[1] = 20;
		g_aHighscore[2] = 30;
		g_aHighscore[3] = 40;
		g_aHighscore[4] = 50;

		bRanking = false;
	}
	// スコアの初期化処理
	InitScore();

	// スコアの呼び出し
	SetHighScore(GetScore());


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_RANKINGSCORE,		// ファイルの名前
		&g_pTextureRankingscore);	// テクスチャへのポインタ

									// 頂点情報の作成
	MakeVertexRankingscore(pDevice);
	//// スコア看板
	//g_RankingModel[5].pos = D3DXVECTOR3(40.0f, 0.0f, 0.0f);
	//g_RankingModel[6].pos = D3DXVECTOR3(80.0f, 0.0f, 100.0f);
	//g_RankingModel[7].pos = D3DXVECTOR3(40.0f, 0.0f, 200.0f);
	//g_RankingModel[8].pos = D3DXVECTOR3(80.0f, 0.0f, 300.0f);
	//g_RankingModel[9].pos = D3DXVECTOR3(40.0f, 0.0f, 400.0f);

	//g_camera.SelectModelpos[4] = D3DXVECTOR3(20.0f, 20.0f, -80.0f);
	//g_camera.SelectModelpos[3] = D3DXVECTOR3(60.0f, 20.0f, 20.0f);
	//g_camera.SelectModelpos[2] = D3DXVECTOR3(20.0f, 20.0f, 120.0f);
	//g_camera.SelectModelpos[1] = D3DXVECTOR3(60.0f, 20.0f, 220.0f);
	//g_camera.SelectModelpos[0] = D3DXVECTOR3(20.0f, 20.0f, 320.0f);

	for (int nCntRankingscore = MIN_RANKINGSCORE; nCntRankingscore < MAX_RANKINGSCORE; nCntRankingscore++)
	{
		g_Ranking[0][nCntRankingscore].pos = D3DXVECTOR3(20.0f + (3.0f * nCntRankingscore), 15.0f, -5.0f);
		g_Ranking[1][nCntRankingscore].pos = D3DXVECTOR3(60.0f + (3.0f * nCntRankingscore), 15.0f, 95.0f);
		g_Ranking[2][nCntRankingscore].pos = D3DXVECTOR3(20.0f + (3.0f * nCntRankingscore), 15.0f, 195.0f);
		g_Ranking[3][nCntRankingscore].pos = D3DXVECTOR3(60.0f + (3.0f * nCntRankingscore), 15.0f, 295.0f);
		g_Ranking[4][nCntRankingscore].pos = D3DXVECTOR3(20.0f + (3.0f * nCntRankingscore), 15.0f, 395.0f);

		g_Ranking[0][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ranking[1][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ranking[2][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ranking[3][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ranking[4][nCntRankingscore].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRankingscore(void)
{
	// テクスチャの開放
	if (g_pTextureRankingscore != NULL)
	{
		g_pTextureRankingscore->Release();
		g_pTextureRankingscore = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRankingscore != NULL)
	{
		g_pVtxBuffRankingscore->Release();
		g_pVtxBuffRankingscore = NULL;
	}

	// スコアの終了処理
	UninitScore();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRankingscore(void)
{
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRankingscore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{

		for (int nCntRankingscore = MIN_RANKINGSCORE; nCntRankingscore < MAX_RANKINGSCORE; nCntRankingscore++)
		{
			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_Ranking[nCntLength][nCntRankingscore].g_aRankingscore * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_Ranking[nCntLength][nCntRankingscore].g_aRankingscore * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_Ranking[nCntLength][nCntRankingscore].g_aRankingscore * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_Ranking[nCntLength][nCntRankingscore].g_aRankingscore * 0.1f), 1.0f);

			pVtx += 4;		// 頂点データのポインタを４つ分進める
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRankingscore->Unlock();

	// スコアの更新処理
	UpdateScore();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRankingscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntRankingscore;
	D3DXMATRIX mtxRot, mtxTrans, mtxView;               // 計算用マトリックス
	int nCntDraw = 0;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//g_aRankingMatrix[nCntLength][nCntRankingscore]
	// ポリゴンの描画
	for (int nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{
		for (nCntRankingscore = MIN_RANKINGSCORE; nCntRankingscore < MAX_RANKINGSCORE; nCntRankingscore++)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix);
			//pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._11 = mtxView._11;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._12 = mtxView._21;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._13 = mtxView._31;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._21 = mtxView._12;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._22 = mtxView._22;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._23 = mtxView._32;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._31 = mtxView._13;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._32 = mtxView._23;
			//g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix._33 = mtxView._33;

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Ranking[nCntLength][nCntRankingscore].rot.y,
				g_Ranking[nCntLength][nCntRankingscore].rot.x,
				g_Ranking[nCntLength][nCntRankingscore].rot.z);

			D3DXMatrixMultiply(&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix,
				&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix,
				&mtxRot);


			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Ranking[nCntLength][nCntRankingscore].pos.x,
				g_Ranking[nCntLength][nCntRankingscore].pos.y,
				g_Ranking[nCntLength][nCntRankingscore].pos.z);

			D3DXMatrixMultiply(&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix,
				&g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Ranking[nCntLength][nCntRankingscore].g_aRankingMatrix);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRankingscore, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRankingscore);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntDraw,
				2);
			nCntDraw++;
		}

	}


	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRankingscore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntRankingscore;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点情報の作成
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_RANKINGSCORE * MAX_LENGTH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingscore,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRankingscore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{
		for (nCntRankingscore = MIN_RANKINGSCORE; nCntRankingscore < MAX_RANKINGSCORE; nCntRankingscore++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-1.5f, 2.0f, 0.0f);	// 横、縦、(幅)
			pVtx[1].pos = D3DXVECTOR3(1.5f, 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-1.5f, -2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1.5f, -2.0f, 0.0f);

			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青、透明度
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;		//頂点データのポインタを４つ分進める
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankingscore->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void SetHighScore(int nScore)
{
	int nCntNum;			//スコアの桁数のカウンター
	int nCntLength;
	int nCntLength2;
	int nNum = 100000000;
	int nNum2 = 10000000;

	for (nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{// 順位変更
		if (g_aHighscore[nCntLength] > nScore)
		{// 上書き阻止のために数字を逃がす
			g_nRankingscore = g_aHighscore[nCntLength];
			g_aHighscore[nCntLength] = nScore;

			// 関係ないところは並べないfor文
			for (nCntLength2 = nCntLength + 1; nCntLength2 < MAX_LENGTH; nCntLength2++)
			{// 書き換えたときの次の数字を並べ替え
				g_nRankingscore2 = g_aHighscore[nCntLength2];
				g_aHighscore[nCntLength2] = g_nRankingscore;
				g_nRankingscore = g_nRankingscore2;
			}

			break;
		}
	}

	for (nCntLength = 0; nCntLength < MAX_LENGTH; nCntLength++)
	{// 変わった数字の計算のし直し
		for (nCntNum = 0; nCntNum < MAX_RANKINGSCORE; nCntNum++)
		{// 桁の座標の計算
			g_Ranking[nCntLength][nCntNum].g_aRankingscore = (g_aHighscore[nCntLength] % nNum) / nNum2;

			//桁数を１桁減らす
			nNum = nNum / 10;
			nNum2 = nNum2 / 10;

			if (nCntNum == MAX_RANKINGSCORE - 1)
			{//初期化する
				nNum = 100000000;
				nNum2 = 10000000;
			}
		}
	}

	//// スコアの描画処理
	//DrawScore();
}
//=============================================================================
// スコアの加算
//=============================================================================
void SetDrawScore(int nNumScore)
{
	g_nDrawRanking = nNumScore;
}
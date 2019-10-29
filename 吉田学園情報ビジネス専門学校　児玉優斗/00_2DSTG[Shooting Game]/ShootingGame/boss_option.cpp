//=============================================================================
//
// ボス処理 [boss.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "boss_option.h"
#include "Explosion.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OPTION_BULLET_ROTATION (3.3f)
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBossOption = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossOption = NULL;					// 頂点バッファへのポインタ

BOSS_OPTION g_BossOption;	//敵のデータ格納

int g_BulletRot;
//=============================================================================
// 初期化処理
//=============================================================================
void InitBossOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	g_BossOption.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_BossOption.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BossOption.bUse = false;
	g_BossOption.nCounterBullet = 0;

	g_BulletRot = 1;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BOSS_OPTION_TEXTURE, &g_pTextureBossOption);

	// 頂点情報の作成
	VERTEX_2D *pVtx;
	

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBossOption,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBossOption->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(0 - BOSS_OPTION_POLYGON_SIZE, 0 - BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0 + BOSS_OPTION_POLYGON_SIZE, 0 - BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0 - BOSS_OPTION_POLYGON_SIZE, 0 + BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0 + BOSS_OPTION_POLYGON_SIZE, 0 + BOSS_OPTION_POLYGON_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(BOSS_OPTION_COLOR_RED, BOSS_OPTION_COLOR_GREEN,  BOSS_OPTION_COLOR_BLUE, BOSS_OPTION_COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(BOSS_OPTION_COLOR_RED, BOSS_OPTION_COLOR_GREEN, BOSS_OPTION_COLOR_BLUE, BOSS_OPTION_COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(BOSS_OPTION_COLOR_RED, BOSS_OPTION_COLOR_GREEN, BOSS_OPTION_COLOR_BLUE, BOSS_OPTION_COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(BOSS_OPTION_COLOR_RED, BOSS_OPTION_COLOR_GREEN, BOSS_OPTION_COLOR_BLUE, BOSS_OPTION_COLOR_ALPHA);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファをアンロックする
		g_pVtxBuffBossOption->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBossOption(void)
{

		// テクスチャの開放
		if (g_pTextureBossOption != NULL)
		{
			g_pTextureBossOption->Release();
			g_pTextureBossOption = NULL;
		}

	// 頂点バッファの開放
	if (g_pVtxBuffBossOption != NULL)
	{
		g_pVtxBuffBossOption->Release();
		g_pVtxBuffBossOption = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBossOption(void)
{
	// 頂点情報の作成
	BOSS *pBoss = GetBoss();

	float fBulletRot;

	g_BossOption.nCounterBullet++;

	if (pBoss->bUse == false)
	{
		g_BossOption.bUse = false;
	}

	if (g_BossOption.bUse == true)
	{
		//弾打ち
		if (pBoss->bUse == true)
		{
			fBulletRot = OPTION_BULLET_ROTATION * ((g_BossOption.nCounterBullet) % 3600);
			SetBullet(g_BossOption.pos, D3DXVECTOR3(sinf(fBulletRot * g_BulletRot) * 8.0f, cosf(fBulletRot * g_BulletRot) * 8.0f, 0.0f), BULLETTYPE_BOSS, D3DXCOLOR(0.7f, 0.4f, 0.95f, 1.0f), 0.0f);
		}
		g_BossOption.pos += g_BossOption.move;

		if (g_BossOption.pos.x <= pBoss->pos.x - 200 || g_BossOption.pos.x >= pBoss->pos.x + 200)
		{
			g_BossOption.move.x = g_BossOption.move.x * -1.0f;
			g_BulletRot = g_BulletRot * - 1;
		}

		VERTEX_2D *pVtx;
		g_pVtxBuffBossOption->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(g_BossOption.pos.x - BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y - BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_BossOption.pos.x + BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y - BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_BossOption.pos.x - BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y + BOSS_OPTION_POLYGON_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_BossOption.pos.x + BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y + BOSS_OPTION_POLYGON_SIZE, 0.0f);

		g_pVtxBuffBossOption->Unlock();




	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBossOption(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	BOSS *pBoss = GetBoss();

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBossOption, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	
		if (g_BossOption.bUse == true)
		{
			//テクスチャの設定
				pDevice->SetTexture(0,g_pTextureBossOption);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
				0,							   //開始する頂点のインデックス(基本０)
				2);		   							       //プリミティブの数
		}
	
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetBossOption(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;

		if (g_BossOption.bUse == false)
		{
			g_pVtxBuffBossOption->Lock(0, 0, (void**)&pVtx, 0);

			g_BossOption.pos = pos;

			g_BossOption.move = move;

			pVtx[0].pos = D3DXVECTOR3(g_BossOption.pos.x - BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y - BOSS_OPTION_POLYGON_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_BossOption.pos.x + BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y - BOSS_OPTION_POLYGON_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_BossOption.pos.x - BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y + BOSS_OPTION_POLYGON_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_BossOption.pos.x + BOSS_OPTION_POLYGON_SIZE, g_BossOption.pos.y + BOSS_OPTION_POLYGON_SIZE, 0.0f);

			g_BossOption.nCounterBullet = 0;
			g_BossOption.bUse = true;


			g_pVtxBuffBossOption->Unlock();
	}
}


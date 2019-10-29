//*****************************************************************************
//
//					DirectX タイトル処理 [title.cpp]
//					Author Kodama Yuto
//(:3 )三
//****************************************************************************
//インクルードファイル
#include "title.h"
#include "fade.h"

//=============================================================================
//							マクロ定義
//=============================================================================
#define MAX_TEXTURE (2)

//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEXTURE] = {};	               //テクスチャへのポインタ

D3DXCOLOR g_TitleColor;
int g_nCounterTitle = 0;
bool g_bEnterDispTitle = true;
bool g_bTitleFade = true;
//-----------------------------------------------------------------------------
//						   背景の初期化処理
//-----------------------------------------------------------------------------
void InitTitle(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_ENTER, &g_pTextureTitle[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	g_nCounterTitle = 0;
	g_bTitleFade = true;
	g_TitleColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	//title
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(50, 100, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1230, 100, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(50, 330, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1230, 330, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = g_TitleColor;
	pVtx[1].col = g_TitleColor;
	pVtx[2].col = g_TitleColor;
	pVtx[3].col = g_TitleColor;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//ENTER
	pVtx += 4;

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(400, 500, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(880, 500, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400, 550, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(880, 550, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//メッシュフィールドの初期化処理
	InitMeshField();

	//メッシュウォールの初期化処理
	InitMeshWall();

	// 壁の初期化処理
	InitWall();

	//屋根の初期化処理
	InitRoof();

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);
	SetWall(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f), WALLTYPE_1, 1000.0f, 100.0f);


	SetRoof(D3DXVECTOR3(0.0f, 100.0f, 1000.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, 0.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(0.0f, 100.0f, -1000.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, D3DX_PI, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, D3DX_PI / 2.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);
	SetRoof(D3DXVECTOR3(-1000.0f, 100.0f, 0.0f), D3DXVECTOR3(-D3DX_PI / 4.0f, -D3DX_PI / 2.0f, 0.0f), ROOFTYPE_1, 1000.0f, 1000.0f);

	PlaySound(SOUND_LABEL_BGM000);


}

//-----------------------------------------------------------------------------
//						   背景の終了処理
//-----------------------------------------------------------------------------

void UninitTitle(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//メッシュウォールの終了処理
	UninitMeshWall();

	// 壁の終了処理
	UninitWall();

	//屋根の終了処理
	UninitRoof();

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//-----------------------------------------------------------------------------
//							背景の更新処理
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	//XINPUT_STATE KeyState;
	//KeyState = GetState();
	//||KeyState.Gamepad.wButtons & XINPUT_GAMEPAD_A
	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	//メッシュフィールドの更新処理
	UpdateMeshField();

	//メッシュウォールの更新処理
	UpdateMeshWall();

	// 壁の更新処理
	UpdateWall();

	//屋根の更新処理
	UpdateRoof();

	//VERTEX_2D *pVtx;				//頂点情報へのポインタ
	FADE *pFade;
	pFade = GetFade();
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	g_nCounterTitle++;
	if (g_nCounterTitle % 40 == 0 || *pFade == FADE_OUT && g_nCounterTitle % 3 == 0)
	{
		g_bEnterDispTitle = g_bEnterDispTitle ? false : true;
	}

	if (g_nCounterTitle % 2 == 0 && g_bTitleFade == true)
	{
		g_TitleColor.a += TITLE_FADE;
	}
	if (g_TitleColor.a >= 1.0f)
	{
		g_TitleColor.a = 1.0f;
		g_bTitleFade = false;
	}

	//ランキングへの遷移
	if (g_nCounterTitle >= 1000 && *pFade != FADE_OUT)
	{
		//StopSound();
		SetFade(MODE_RANKING);
	}
	//ENTERキーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true /*|| KeyState.Gamepad.wButtons & XINPUT_GAMEPAD_A*/)
	{
		g_TitleColor.a = 1.0f;
		g_bTitleFade = false;

		if (*pFade != FADE_OUT)
		{
			StopSound();
			PlaySound(SOUND_LABEL_SE001);
			SetFade(MODE_TUTORIAL);
			//PlaySound(SOUND_LABEL_SE_000);
		}
	}

	//title
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = g_TitleColor;
	pVtx[1].col = g_TitleColor;
	pVtx[2].col = g_TitleColor;
	pVtx[3].col = g_TitleColor;

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();


}

//-----------------------------------------------------------------------------
//							背景の描画処理
//-----------------------------------------------------------------------------

void DrawTitle(void)
{
	// カメラの設定
	SetCamera();

	//メッシュフィールドの描画処理
	DrawMeshField();

	//メッシュウォールの描画処理
	DrawMeshWall();

	// 壁の描画処理
	DrawWall();

	//屋根の描画処理
	DrawRoof();

	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//描画
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (nCntTex != 1 || nCntTex == 1 && g_bEnterDispTitle == true)
		{
			pDevice->SetTexture(0, g_pTextureTitle[nCntTex]);//テクスチャの設定

												 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
				4 * nCntTex,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}
	}
}


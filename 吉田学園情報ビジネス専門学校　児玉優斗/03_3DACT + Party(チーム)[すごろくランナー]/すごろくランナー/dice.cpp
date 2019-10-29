//=============================================================================
//
// モデル処理 [dice.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "dice.h"
#include "camera.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "timer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DICE_FILENAME "data/MODEL/dice.x"
#define DICE_MOVE_SPEED (0.7f)
#define DICE_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_DICE (2)
#define DICE_MOVE_INTERVAL (2)		//ダイスの回転速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeDebugFont(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshDice[MAX_NUM_DICE] = {};		// メッシュ情報へのポインタ[モデルの最大数]
LPD3DXBUFFER g_pBuffMatDice[MAX_NUM_DICE] = {};	// マテリアル情報へのポインタ[モデルの最大数]

DICE g_Dice[MAX_NUM_DICE];						// モデルの情報[モデルの最大数]

bool g_bTimerFlag = false;		//タイマーのセット管理
int g_nMaxNumDice;				// ダイスの出目の合計値

LPD3DXFONT	pDiceFont = NULL;	// フォントオブジェクトのポインタ
D3DXCOLOR g_DiceFontColor;		// フォントの色
char g_DiceNumber[256];			// 文字列格納用[256で固定]

RECT g_NumRect = {				// 文字を置く範囲
	50,		// 左上のX座標
	500,	// 左上のY座標
	200,	// 右下のX座標
	650		// 右下のY座標
};

//=============================================================================
// 初期化処理
//=============================================================================
void InitDice(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntDice = 0; nCntDice < MAX_NUM_DICE; nCntDice++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(DICE_FILENAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatDice[nCntDice],
			NULL,
			&g_Dice[nCntDice].NumMatDice,
			&g_pMeshDice[nCntDice]);

		// 位置・向きの初期設定
		g_Dice[nCntDice].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f);

		//移動量・回転量の初期化
		g_Dice[nCntDice].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Dice[nCntDice].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//その他変数の初期化
		g_Dice[nCntDice].bUse = false;
		g_Dice[nCntDice].nCntDiceMove = 0;
		g_Dice[nCntDice].nNumDice = 0;
		g_Dice[nCntDice].DiceMotion = DICEMOTION_NONE;
	}

	//位置の設定(後で消す)
	g_Dice[0].pos = D3DXVECTOR3(50.0f, -10.0f, 40.0f);
	g_Dice[0].oldPos = g_Dice[0].pos;
	g_Dice[1].pos = D3DXVECTOR3(-50.0f, -10.0f, 40.0f);
	g_Dice[1].oldPos = g_Dice[1].pos;

	//グローバル変数の初期化
	g_bTimerFlag = true;
	g_DiceFontColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//フォントの作成
	MakeDebugFont(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDice(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_DICE; nCntMesh++)
	{
		// メッシュの解放
		if (g_pMeshDice[nCntMesh] != NULL)
		{
			g_pMeshDice[nCntMesh]->Release();
			g_pMeshDice[nCntMesh] = NULL;

		}
		/*テクスチャの解放*/
		//マテリアルの解放
		if (g_pBuffMatDice[nCntMesh] != NULL)
		{
			g_pBuffMatDice[nCntMesh]->Release();
			g_pBuffMatDice[nCntMesh] = NULL;

		}

	}

	//フォントの解放
	if (pDiceFont != NULL)
	{
		pDiceFont->Release();
		pDiceFont = NULL;

	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateDice(void)
{
	for (int nCntDice = 0; nCntDice < MAX_NUM_DICE; nCntDice++)
	{

		if (g_Dice[nCntDice].bUse == true)
		{//使われていたら
			switch (g_Dice[nCntDice].DiceMotion)
			{
			case DICEMOTION_NONE://無し
				break;
			case DICEMOTION_MOVE://定位置で回転
				g_Dice[nCntDice].nCntDiceMove++;
				if (g_Dice[nCntDice].nCntDiceMove % DICE_MOVE_INTERVAL == 0)
				{
					g_Dice[nCntDice].rot.x += (rand() % 40 + 40) * 0.01f;
					g_Dice[nCntDice].rot.y += D3DX_PI * 0.125f;
					g_Dice[nCntDice].rot.z += (rand() % 40 + 40) * 0.01f;

					g_Dice[nCntDice].rot.x = RotOverwhelming(g_Dice[nCntDice].rot.x);
					g_Dice[nCntDice].rot.y = RotOverwhelming(g_Dice[nCntDice].rot.y);
					g_Dice[nCntDice].rot.z = RotOverwhelming(g_Dice[nCntDice].rot.z);
				}
				break;
			case DICEMOTION_THROW://上に打ちあがった状態
				if (g_Dice[nCntDice].pos.y >= g_Dice[nCntDice].oldPos.y)
				{
					g_Dice[nCntDice].move.y -= 0.75f;

					g_Dice[nCntDice].rot.x += (rand() % 40 + 40) * 0.01f;
					g_Dice[nCntDice].rot.y += D3DX_PI * 0.125f;
					g_Dice[nCntDice].rot.z += (rand() % 40 + 40) * 0.01f;

					g_Dice[nCntDice].rot.x = RotOverwhelming(g_Dice[nCntDice].rot.x);
					g_Dice[nCntDice].rot.y = RotOverwhelming(g_Dice[nCntDice].rot.y);
					g_Dice[nCntDice].rot.z = RotOverwhelming(g_Dice[nCntDice].rot.z);

				}
				else
				{
					g_Dice[nCntDice].DiceMotion = DICEMOTION_STOP;
				}
				g_Dice[nCntDice].move.z += (0.0f - g_Dice[nCntDice].move.z) * 0.1f;
				g_Dice[nCntDice].pos.z += g_Dice[nCntDice].move.z;
				g_Dice[nCntDice].move.y += (0.0f - g_Dice[nCntDice].move.y) * 0.1f;
				g_Dice[nCntDice].pos.y += g_Dice[nCntDice].move.y;

				break;
			case DICEMOTION_STOP://落ちて静止
				g_Dice[nCntDice].pos.y = g_Dice[nCntDice].oldPos.y;

				switch (g_Dice[nCntDice].nNumDice)
				{//出目に角度を合わせる
				case 1:
					g_Dice[nCntDice].rot.x = D3DX_PI * 0.5f;
					g_Dice[nCntDice].rot.z = 0.0f;
					break;
				case 2:
					g_Dice[nCntDice].rot.x = 0.0f;
					g_Dice[nCntDice].rot.z = 0.0f;
					break;
				case 3:
					g_Dice[nCntDice].rot.x = 0.0f;
					g_Dice[nCntDice].rot.z = D3DX_PI * -0.5f;
					break;
				case 4:
					g_Dice[nCntDice].rot.x = 0.0f;
					g_Dice[nCntDice].rot.z = D3DX_PI * 0.5f;
					break;
				case 5:
					g_Dice[nCntDice].rot.x = D3DX_PI;
					g_Dice[nCntDice].rot.z = 0.0f;
					break;
				case 6:
					g_Dice[nCntDice].rot.x = D3DX_PI * -0.5f;
					g_Dice[nCntDice].rot.z = 0.0f;
					break;
				}
				//g_Dice[nCntDice].rot.y = D3DX_PI * 0.25f;

				if (g_bTimerFlag == true)
				{
					g_bTimerFlag = false;
					SetTurnState(TURNSTATE_COUNTDOWN);
					SetTimer(g_nMaxNumDice);

				}

				//出力する文字の上書き
				wsprintf(g_DiceNumber, "%d", g_nMaxNumDice);

				break;
			}

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_1, GetIdxPlayer()) == TRUE)
			{//サイコロを投げる
				if (g_Dice[nCntDice].DiceMotion == DICEMOTION_MOVE)
				{
					g_Dice[nCntDice].nNumDice = rand() % 6 + 1;
					g_Dice[nCntDice].move.z += (rand() % 6 - 3) * 1.0f;
					g_Dice[nCntDice].move.y += 25.0f;

					g_bTimerFlag = true;
					g_Dice[nCntDice].DiceMotion = DICEMOTION_THROW;
					g_Dice[nCntDice].pos = g_Dice[nCntDice].oldPos;

					g_Dice[nCntDice].nCntDiceMove = 0;
				}
			}

			g_Dice[nCntDice].move.z += (0.0f - g_Dice[nCntDice].move.z) * 0.1f;
			g_Dice[nCntDice].pos.z += g_Dice[nCntDice].move.z;
			g_Dice[nCntDice].move.y += (0.0f - g_Dice[nCntDice].move.y) * 0.1f;
			g_Dice[nCntDice].pos.y += g_Dice[nCntDice].move.y;

		}

	}

	if (g_nMaxNumDice != (g_Dice[0].nNumDice + g_Dice[1].nNumDice))
	{//出目が更新されるなら
		g_nMaxNumDice = (g_Dice[0].nNumDice + g_Dice[1].nNumDice);

	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ


	for (int nCntDice = 0; nCntDice < MAX_NUM_DICE; nCntDice++)
	{
		if (g_Dice[nCntDice].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Dice[nCntDice].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Dice[nCntDice].rot.y,
				g_Dice[nCntDice].rot.x,
				g_Dice[nCntDice].rot.z);

			D3DXMatrixMultiply(&g_Dice[nCntDice].mtxWorld,
				&g_Dice[nCntDice].mtxWorld,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Dice[nCntDice].pos.x,
				g_Dice[nCntDice].pos.y,
				g_Dice[nCntDice].pos.z);

			D3DXMatrixMultiply(&g_Dice[nCntDice].mtxWorld,
				&g_Dice[nCntDice].mtxWorld,
				&mtxTrans);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Dice[nCntDice].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatDice[nCntDice]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Dice[nCntDice].NumMatDice; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*テクスチャの設定*/
				pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

											 // モデル(パーツ)の描画
				g_pMeshDice[nCntDice]->DrawSubset(nCntMat);

			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}

	//フォントの描画
	pDiceFont->DrawText(
		NULL,								// NULL
		g_DiceNumber,						// 描画するテキスト
		-1,									// 描画する文字数(-1で上のテキストの文字数を取得してくれる)
		&g_NumRect,							// 描画範囲(上で定義したRECT型の変数のポインタを入れる)
		DT_VCENTER | DT_CENTER,				// 描画オプション
		g_DiceFontColor						// 色指定
	);

}

//===========================================================
//	フォントの作成
//===========================================================
void MakeDebugFont(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFont(
		pDevice,					// デバイスのポインタ
		192,							// 高さ
		80,							// 幅
		FW_ULTRABOLD,				// フォントの太さ
		NULL,						// 下線
		FALSE,						// 斜体(TRUEでon,FALSEでoff)
		SHIFTJIS_CHARSET,			// 文字セット
		OUT_DEFAULT_PRECIS,			// 出力制度(OUT_DEFAULT_PRECISで固定)
		PROOF_QUALITY,				// 文字の品質
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリのインデックス
		TEXT("Meiryo UI"),			// フォント名(空白、大文字も含めて正確に入力すること)
		&pDiceFont);					// フォントのポインタ

}
//===========================================================
//	ダイスの設定
//===========================================================
void SetDice(int nNumDice)
{
	Camera *pCamera;
	pCamera = GetCamera();

	Player *pPlayer;
	pPlayer = GetPlayer();


	switch (nNumDice)
	{//サイコロ数に応じて位置を微調整
	case 1:
		g_Dice[0].pos = D3DXVECTOR3(pPlayer->pos.x - 100.0f, -20.0f, pPlayer->pos.z + 40.0f);
		g_Dice[0].oldPos = g_Dice[0].pos;
		g_Dice[0].bUse = true;
		g_Dice[0].DiceMotion = DICEMOTION_MOVE;
		break;
	case 2:
		g_Dice[0].pos = D3DXVECTOR3(pPlayer->pos.x - 150.0f, -20.0f, pPlayer->pos.z + 40.0f);
		g_Dice[0].oldPos = g_Dice[0].pos;
		g_Dice[0].bUse = true;
		g_Dice[0].DiceMotion = DICEMOTION_MOVE;

		g_Dice[1].pos = D3DXVECTOR3(pPlayer->pos.x - 50.0f, -20.0f, pPlayer->pos.z + 40.0f);
		g_Dice[1].oldPos = g_Dice[1].pos;
		g_Dice[1].bUse = true;
		g_Dice[1].DiceMotion = DICEMOTION_MOVE;
		break;
	}
}
//===========================================================
//	ダイスの消去
//===========================================================
void DeleteDice(int nNumDice)
{
	switch (nNumDice)
	{
	case 1:
		g_Dice[0].bUse = false;
		g_Dice[0].DiceMotion = DICEMOTION_NONE;
		break;
	case 2:
		g_Dice[0].bUse = false;
		g_Dice[0].DiceMotion = DICEMOTION_NONE;
		g_Dice[1].bUse = false;
		g_Dice[1].DiceMotion = DICEMOTION_NONE;

		break;
	}

}

//==================================================
//サイコロの合計値を返す関数
//==================================================
int  GetNumDice(void)
{
	if (g_nMaxNumDice <= 1)
	{
		return -1;
	}
	else
	{
		return g_nMaxNumDice;
	}

}
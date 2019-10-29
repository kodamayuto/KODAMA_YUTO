//*****************************************************************************
//
// ゲームの処理[game.cpp]
// Author : kodama Yuto
//
//*****************************************************************************
//インクルードファイル
#include "game.h"
#include "fade.h"
#include "pause.h"
#include"ranking.h"
//=============================================================================
//	グローバル変数宣言
//=============================================================================
GAMESTATE g_gamestate		  = GAMESTATE_NONE;		//ゲームの条件
int g_nCounterGameState;    						//カウンター

bool g_bPause;				//ポーズ処理用  true = ポーズ中

//=============================================================================
//	初期化処理
//=============================================================================
void InitGame(void)
{
	InitPause();		//ポーズ
	InitBG();			//背景
	InitPlayer();		//プレイヤーのポリゴン
	InitBullet();		//弾
	InitExplosion();	//爆発
	InitScore();		//スコア
	InitLife();			//ライフ
	InitPlayerMode();	//自機の状態変化
	InitEffect();		//エフェクト
	InitEnemy();		//敵のポリゴン
	InitBoss();			//ボス
	InitBossOption();	//ボスのオプション

	 //==============//
	 //  敵をセット  //
	 //==============//

	// nCntData == 行　nCntSetEnemy == 列
	for (int nCntData = 0; nCntData < MAX_TYPE_ENEMY / 2; nCntData++)
	{
		for (int nCntSetEnemy = 0; nCntSetEnemy < 13; nCntSetEnemy++)
		{
			SetEnemy(D3DXVECTOR3(50.0f + (100 * nCntSetEnemy), 200.0f + (-50 * nCntData), 0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f),(nCntData) % 4);
		}

	}


	//グローバル変数の初期化
	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPause = false;

	PlaySound(SOUND_LABEL_BGM001);//音

}

//=============================================================================
//	終了処理
//=============================================================================
void UninitGame(void)
{
	UninitPause();		//ポーズ
	UninitBG();			//背景
	UninitPlayer();		//ポリゴン
	UninitBullet();		//弾
	UninitExplosion();	//爆発
	UninitScore();		//スコア
	UninitLife();		//ライフ
	UninitPlayerMode();	//自機の状態変化
	UninitEffect();		//エフェクト
	UninitEnemy();		//敵
	UninitBoss();		//ボス
	UninitBossOption();
}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateGame(void)
{

	//ポーズ　ON/OFF
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		PauseModeChange();
		SerectReset();
		DispReset();
		if (g_gamestate == GAMESTATE_NORMAL)
		{

		PlaySound(SOUND_LABEL_SE_PAUSE);//音
		}

	}

	if (g_bPause == false || g_gamestate == GAMESTATE_END || g_gamestate == GAMESTATE_NONE)
	{
		UpdateBG();			//背景
		UpdatePlayer();		//ポリゴン
		UpdateBullet();		//弾
		UpdateExplosion();	//爆発
		UpdateScore();		//スコア
		UpdateLife();		//ライフ
		UpdatePlayerMode();	//自機の状態変化
		UpdateEffect();		//エフェクト
		UpdateEnemy();		//敵
		UpdateBoss();		//ボス
		UpdateBossOption();

	}
	else if(g_bPause == true && g_gamestate != GAMESTATE_END || g_gamestate != GAMESTATE_NONE)
	{
		UpdatePause();//ポーズ処理
	}

	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		BulletErese();
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			SetRankScore(GetScore());
			SetFade(MODE_RESULT);
			g_gamestate = GAMESTATE_NONE;			//モード設定
		}
		break;
	}
}

//=============================================================================
//	描画処理
//=============================================================================
void DrawGame(void)
{
	//***各種オブジェクトの描画処理***
	DrawBG();			//背景
	DrawBullet();		//弾
	DrawExplosion();	//爆発
	DrawEffect();		//エフェクト
	DrawEnemy();		//敵
	DrawLife();			//ライフ
	DrawPlayerMode();	//自機の状態変化
	DrawScore();		//スコア
	DrawPlayer();		//自機
	DrawBoss();			//ボス
	DrawBossOption();	//ボスのオプション

	if (g_bPause == true && g_gamestate == GAMESTATE_NORMAL)
	{
		DrawPause();	//ポーズ画面
	}
}

//=============================================================================
//	ゲームの状態の設定
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}

//=============================================================================
//	ゲームの状態の取得
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gamestate;
}
//=============================================================================
//	ポーズ状態の切り替え
//=============================================================================
void PauseModeChange(void)
{
	g_bPause = g_bPause ? false : true;
}

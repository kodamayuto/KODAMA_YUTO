//*****************************************************************************
//
//DirectX プレイヤーの処理 [player.h]
//Author : Kodama Yuto
//
//*****************************************************************************
#ifndef _PLAYER_H_	//二重インクルード防止のマクロ定義
#define _PLAYER_H_

//=============================================================================
//								マクロ定義
//=============================================================================
#define PLAYER_TEXTURE "data/TEXTURE/Draw004Fryer1.png"	//プレイヤーの貼るテクスチャの名前

#define SENT_POS_X (SCREEN_WIDTH / 2)					//プレイヤーの中心座標.x
#define SENT_POS_Y (500)					//プレイヤーの中心座標.y

#define PLAYER_SIZE (25.0f)					//プレイヤーの大きさ

#define PLAYER_MOVE_SPEED (5.0f)			//プレイヤーの移動速度
#define PLAYER_MOVE_COEFFICIENT (0.3f)		//プレイヤーの減速係数

#define PLAYER_COLOR_RED (255)				//プレイヤーの色.r
#define PLAYER_COLOR_GREEN (255)			//プレイヤーの色.g
#define PLAYER_COLOR_BLUE (255)				//プレイヤーの色.b
#define PLAYER_COLOR_ALPHA (255)			//プレイヤーの色.a

#define PLAYER_LIFE (8)						//プレイヤーの体力

//=============================================================================
//	構造体の定義
//=============================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//無敵
	PLAYERSTATE_NORMAL,		//通常
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_DEATH,		//死
	PLAYERSTATE_END,		//終了
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	PLAYERSTATE state;		//状態
	int nCountState;		//状態のカウンタ
	int nBulletPattern;		//弾のパターン
	int nCntBullet;			//弾の発射カウント
	int nLife;				//体力
	bool bDisp;				//使用の有無
	bool bMove;				//低速移動
}Player;

//-----------------------------------------------------------------------------
//							プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void HitPlayer(int nDamage);

#endif // !_PLAYER_H_


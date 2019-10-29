//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "wall.h"
#include "billboard.h"
#include "shadow.h"
#include "effect.h"
#include "particle.h"
#include "obstacle.h"
#include "course.h"
#include "masu.h"
#include "timer.h"
#include "game.h"
#include "orbit.h"
#include "fade.h"
#include "rank.h"
#include "turnNum.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_FILENAME   "MODEL_FILENAME"
#define CHARACTERSET     "CHARACTERSET"
#define MOVE             "MOVE"
#define JUMP             "JUMP"
#define INDEX            "INDEX"
#define PARENT           "PARENT"
#define POS              "POS"
#define ROT              "ROT"
#define PARTSSET         "PARTSSET"
#define END_PARTSSET     "END_PARTSSET"
#define END_CHARACTERSET "END_CHARACTERSET"
#define MOTIONSET        "MOTIONSET"
#define LOOP             "LOOP"
#define NUM_KEY          "NUM_KEY"
#define KEYSET           "KEYSET"
#define FRAME            "FRAME"
#define KEY              "KEY"
#define END_KEY          "END_KEY"
#define END_KEYSET       "END_KEYSET"
#define END_MOTIONSET    "END_MOTIONSET"

#define PLAYER_INERTIA	(0.123f)			// 慣性
#define GRAVITY_POWER	(-0.4f)				// 重力
#define MOVE_NORMAL		(0.5f)				// 移動
#define JUMP_NORMAL		(8.0f)				// ジャンプ力
#define JUMP_UP			(9.0f)				// ジャンプ力UP
#define JUMP_DOWN		(7.5f)				// ジャンプ力DOWN
#define MOVE_UP			(0.8f)				// 移動UP
#define MOVE_DOWN		(0.3f)				// 移動DOWN


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PlayerMove(int nIdxPlayer);               // 操作できるプレイヤーの移動処理
void PlayerTransition(int nIdxPlayer);         // 操作できるプレイヤーの遷移処理
void PlayerImpossible(int nIdxPlayer);         // 操作できないプレイヤーの処理
void PlayerMotion(int nIdxPlayer);             // モーション処理
void PlayerMotionBlend(int nIdxPlayer);        // モーションブレンド処理
void PlayerMotionAdvance(int nIdxPlayer);      // モーション進行処理
void SwitchKey(int nIdxPlayer);                // キーフレームの切り替え処理
void SwitchMotion(int nIdxPlayer);             // モーション切り替え処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player  g_Player[MAX_PLAYER];                 // プレイヤー情報
int     g_PlayerPossible;                     // 現在操作できるプレーヤーの番号

bool g_bPlayerMoveFlag = false;			// プレイヤーの操作フラグ
int  g_ChangeTimer;                     // パーティクルを移す時間を数えるタイマー
//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	FILE  *pFile;           // テキストファイルへのポインタ
	char  str0[128];        // いらない文字
	char  xFileName[64];    // xファイルの名前
	D3DXVECTOR3 OffsetPos;  // 親モデルからの距離
	D3DXVECTOR3 OffsetRot;  // 親モデルからの向き
	float fJump;            // ジャンプ力
	float fMovement;        // 移動量
	int   nIdxParent;       // 親モデル
	int   nCntModel = 0;    // モデルを読み込んだ数を数える変数
	int   nCntParts = 0;    // モデルのパーツ情報を読み込んだ回数を数える変数
	int   nCntPlayer = 0;   // プレイヤーの数
	int   nCntMotion = 0;   // モーションの番号
	int   nCntKey = 0;      // キーフレームの番号を数える変数
	int   nPlaybackKey;     // フレーム数
	int   nCntKeyModel = 0; // モデルの数分のキーフレームを数える変数
	int   bLoop;            // モーションがループするかしないか
	int   nNumKey = 0;      // キーフレームの数
	D3DXVECTOR3 posAdd;     // 基準の位置に加える値
	D3DXVECTOR3 DestAngle;  // 目的の向き

	// ファイルオープン
	pFile = fopen("data/player_00.txt", "r");

	if (pFile != NULL)
	{// ファイルが開けた
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// テキストファイルの末端まで文字列を改行か空白があるまで読み取る
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// xファイルの拡張子が書かれていたら
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// モデルのファイル名を読み取ったら
				 // xファイルの読み込み
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].pBuffMat,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].nNumMat,
						&g_Player[nCntPlayer].aModel[nCntModel].pMesh);

					// マテリアル情報からテクスチャを引き出す
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];
					g_Player[nCntPlayer].aModel[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];

					for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
					{// 頂点数の数だけ繰り返し 
					 // マテリアル情報を読み込む
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// 環境光を初期化する
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// テクスチャ情報を初期化
						g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;

						// テクスチャの情報を読み込む
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// テクスチャのファイル名がある
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);
						}

					}
				}
				nCntModel++;  // 種類が変わるので進めておく
			}
			if (strcmp(&str0[0], CHARACTERSET) == 0)
			{// キャラクター情報が書かれていたら
				while (strcmp(&str0[0], END_CHARACTERSET) != 0)
				{// キャラクター情報が終わるまで読み取る
					if (strcmp(&str0[0], MOVE) == 0)
					{// 移動力が書かれていたら
						if (fscanf(pFile, "%s %f", &str0[0], &fMovement) == 2)
						{// 移動力を読み取ったら
							g_Player[nCntPlayer].fMovement = fMovement;
						}
					}
					if (strcmp(&str0[0], JUMP) == 0)
					{// ジャンプ力が書かれていたら
						if (fscanf(pFile, "%s %f", &str0[0], &fJump) == 2)
						{// ジャンプ力を読み取ったら
							g_Player[nCntPlayer].fJumpPower = fJump;
						}
					}

					if (strcmp(&str0[0], PARTSSET) == 0)
					{// モデルのパーツ情報が書かれていたら
						int nCntSet = 0;
						int nCntPartsNum = 0;
						while (strcmp(&str0[0], END_PARTSSET) != 0)
						{// モデルのパーツ情報が終わるまで読み取る
							if (strcmp(&str0[0], INDEX) == 0)
							{// パーツ番号を読み取る
								fscanf(pFile, "%s %d", &str0[0], &nCntPartsNum);
							}
							else if (strcmp(&str0[0], PARENT) == 0)
							{// 親モデルの番号を読み取る
								if (fscanf(pFile, "%s %d", &str0[0], &nIdxParent) == 2)
								{// 親モデルの番号を読み取る
									g_Player[nCntPlayer].aModel[nCntPartsNum].nIdxModelParent = nIdxParent;
								}
							}
							else if (strcmp(&str0[0], POS) == 0)
							{// 親モデルからの距離を読み取る
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetPos.x, &OffsetPos.y, &OffsetPos.z) == 4)
								{// 座標情報を読み取ったら
									g_Player[nCntPlayer].aModel[nCntPartsNum].pos = OffsetPos;
								}
							}
							else if (strcmp(&str0[0], ROT) == 0)
							{// 親モデルからの向きを読み取る
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetRot.x, &OffsetRot.y, &OffsetRot.z) == 4)
								{// 向き情報を読み取ったら
									g_Player[nCntPlayer].aModel[nCntPartsNum].rot = OffsetRot;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
							nCntSet++;                     // セットした回数を増やす
						}
					}
					fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
				}
			}
			if (strcmp(&str0[0], MOTIONSET) == 0)
			{// モーション情報が書かれていたら
				nCntKey = 0;    // キーフレームのポインタ座標を戻す
				while (strcmp(&str0[0], END_MOTIONSET) != 0)
				{// モーション情報が終わるまで読み取る
					if (strcmp(&str0[0], LOOP) == 0)
					{// ループするかしないかを読み取る
						if (fscanf(pFile, "%s %d", &str0[0], &bLoop) == 2)
						{// ループするかしないかを読み取れた
							if (bLoop == 1)
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = true;
							}
							else
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = false;
							}
						}
					}
					else if (strcmp(&str0[0], NUM_KEY) == 0)
					{// キーフレーム数を読み取る
						if (fscanf(pFile, "%s %d", &str0[0], &nNumKey) == 2)
						{// キーフレーム数を読み取れた
							g_Player[nCntPlayer].aMotion[nCntMotion].nNumKey = nNumKey;
						}
					}
					else if (strcmp(&str0[0], KEYSET) == 0)
					{// キーフレーム情報が書かれていたら
						nCntKeyModel = 0;
						while (strcmp(&str0[0], FRAME) != 0)
						{// キーフレーム数情報が終わるまで読み取る
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
						}
						if (fscanf(pFile, "%s %d", &str0[0], &nPlaybackKey) == 2)
						{// キーフレーム数を読み取れた
							g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].nPlayBackKey = nPlaybackKey;
						}
						while (strcmp(&str0[0], END_KEYSET) != 0)
						{// キーフレーム情報が終わるまで読み取る
							if (strcmp(&str0[0], KEY) == 0)
							{// キーフレームの目的の位置情報が書かれていたら
								while (strcmp(&str0[0], END_KEY) != 0)
								{// キーフレームの目的の位置情報が終わるまで読み取る
									if (strcmp(&str0[0], POS) == 0)
									{// 座標情報を読み取る
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &posAdd.x, &posAdd.y, &posAdd.z) == 4)
										{// 座標情報を読み取ったら
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].posAdd[nCntKeyModel] = posAdd;
										}
									}
									else if (strcmp(&str0[0], ROT) == 0)
									{// 向き情報を読み取る
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &DestAngle.x, &DestAngle.y, &DestAngle.z) == 4)
										{// 向き情報を読み取ったら
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].DestAngle[nCntKeyModel] = DestAngle;
										}
									}
									fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
								}
								if (nCntKeyModel < MAX_MODEL - 1)
								{// モデルごとのキーフレームが用意できる数までよりポインタが進んでない
									nCntKeyModel++;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
						}
						if (nCntKey < MAX_MODEL - 1)
						{// キーフレームが用意できる数までよりポインタが進んでない
							nCntKey++;
						}
					}
					fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
				}
				if (nCntMotion < MAX_MOTION - 1)
				{// モーションが用意できる数までよりポインタが進んでない
					nCntMotion++;   // モーション番号をずらす
				}
			}
		}
	}

	// ファイルを閉じて他のプログラムからいじれるようにする
	fclose(pFile);

	nCntModel = 0;    // モデルを読み込んだ数を数える変数
	nCntParts = 0;    // モデルのパーツ情報を読み込んだ回数を数える変数
	nCntMotion = 0;   // モーションの番号
	nCntKey = 0;      // キーフレームの番号を数える変数
	nCntKeyModel = 0; // モデルの数分のキーフレームを数える変数
	nNumKey = 0;      // キーフレームの数

	if (nCntPlayer < MAX_PLAYER)
	{// プレイヤーの最大人数よりポインタが進んでない
		nCntPlayer++;    // プレイヤー情報のポインタを進める
	}

	// ファイルオープン
	pFile = fopen("data/player_01.txt", "r");

	if (pFile != NULL)
	{// ファイルが開けた
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// テキストファイルの末端まで文字列を改行か空白があるまで読み取る
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// xファイルの拡張子が書かれていたら
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// モデルのファイル名を読み取ったら
				 // xファイルの読み込み
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].pBuffMat,
						NULL,
						&g_Player[nCntPlayer].aModel[nCntModel].nNumMat,
						&g_Player[nCntPlayer].aModel[nCntModel].pMesh);

					// マテリアル情報からテクスチャを引き出す
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];
					g_Player[nCntPlayer].aModel[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[g_Player[nCntPlayer].aModel[nCntModel].nNumMat];

					for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
					{// 頂点数の数だけ繰り返し 
					 // マテリアル情報を読み込む
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// 環境光を初期化する
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// テクスチャ情報を初期化
						g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;

						// テクスチャの情報を読み込む
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// テクスチャのファイル名がある
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);
						}

					}
				}
				nCntModel++;  // 種類が変わるので進めておく
			}
			if (strcmp(&str0[0], CHARACTERSET) == 0)
			{// キャラクター情報が書かれていたら
				while (strcmp(&str0[0], END_CHARACTERSET) != 0)
				{// キャラクター情報が終わるまで読み取る
					if (strcmp(&str0[0], MOVE) == 0)
					{// 移動力が書かれていたら
						if (fscanf(pFile, "%s %f", &str0[0], &fMovement) == 2)
						{// 移動力を読み取ったら
							g_Player[nCntPlayer].fMovement = fMovement;
						}
					}
					if (strcmp(&str0[0], JUMP) == 0)
					{// ジャンプ力が書かれていたら
						if (fscanf(pFile, "%s %f", &str0[0], &fJump) == 2)
						{// ジャンプ力を読み取ったら
							g_Player[nCntPlayer].fJumpPower = fJump;
						}
					}

					if (strcmp(&str0[0], PARTSSET) == 0)
					{// モデルのパーツ情報が書かれていたら
						int nCntSet = 0;
						int nCntPartsNum = 0;
						while (strcmp(&str0[0], END_PARTSSET) != 0)
						{// モデルのパーツ情報が終わるまで読み取る
							if (strcmp(&str0[0], INDEX) == 0)
							{// パーツ番号を読み取る
								fscanf(pFile, "%s %d", &str0[0], &nCntPartsNum);
							}
							else if (strcmp(&str0[0], PARENT) == 0)
							{// 親モデルの番号を読み取る
								if (fscanf(pFile, "%s %d", &str0[0], &nIdxParent) == 2)
								{// 親モデルの番号を読み取る
									g_Player[nCntPlayer].aModel[nCntPartsNum].nIdxModelParent = nIdxParent;
								}
							}
							else if (strcmp(&str0[0], POS) == 0)
							{// 親モデルからの距離を読み取る
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetPos.x, &OffsetPos.y, &OffsetPos.z) == 4)
								{// 座標情報を読み取ったら
									g_Player[nCntPlayer].aModel[nCntPartsNum].pos = OffsetPos;
								}
							}
							else if (strcmp(&str0[0], ROT) == 0)
							{// 親モデルからの向きを読み取る
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetRot.x, &OffsetRot.y, &OffsetRot.z) == 4)
								{// 向き情報を読み取ったら
									g_Player[nCntPlayer].aModel[nCntPartsNum].rot = OffsetRot;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
							nCntSet++;                     // セットした回数を増やす
						}
					}
					fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
				}
			}
			if (strcmp(&str0[0], MOTIONSET) == 0)
			{// モーション情報が書かれていたら
				nCntKey = 0;   // キーフレームのポインタ座標を戻す
				while (strcmp(&str0[0], END_MOTIONSET) != 0)
				{// モーション情報が終わるまで読み取る
					if (strcmp(&str0[0], LOOP) == 0)
					{// ループするかしないかを読み取る
						if (fscanf(pFile, "%s %d", &str0[0], &bLoop) == 2)
						{// ループするかしないかを読み取れた
							if (bLoop == 1)
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = true;
							}
							else
							{
								g_Player[nCntPlayer].aMotion[nCntMotion].bLoop = false;
							}
						}
					}
					else if (strcmp(&str0[0], NUM_KEY) == 0)
					{// キーフレーム数を読み取る
						if (fscanf(pFile, "%s %d", &str0[0], &nNumKey) == 2)
						{// キーフレーム数を読み取れた
							g_Player[nCntPlayer].aMotion[nCntMotion].nNumKey = nNumKey;
						}
					}
					else if (strcmp(&str0[0], KEYSET) == 0)
					{// キーフレーム情報が書かれていたら
						nCntKeyModel = 0;
						while (strcmp(&str0[0], FRAME) != 0)
						{// キーフレーム数情報が終わるまで読み取る
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
						}
						if (fscanf(pFile, "%s %d", &str0[0], &nPlaybackKey) == 2)
						{// キーフレーム数を読み取れた
							g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].nPlayBackKey = nPlaybackKey;
						}
						while (strcmp(&str0[0], END_KEYSET) != 0)
						{// キーフレーム情報が終わるまで読み取る
							if (strcmp(&str0[0], KEY) == 0)
							{// キーフレームの目的の位置情報が書かれていたら
								while (strcmp(&str0[0], END_KEY) != 0)
								{// キーフレームの目的の位置情報が終わるまで読み取る
									if (strcmp(&str0[0], POS) == 0)
									{// 座標情報を読み取る
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &posAdd.x, &posAdd.y, &posAdd.z) == 4)
										{// 座標情報を読み取ったら
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].posAdd[nCntKeyModel] = posAdd;
										}
									}
									else if (strcmp(&str0[0], ROT) == 0)
									{// 向き情報を読み取る
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &DestAngle.x, &DestAngle.y, &DestAngle.z) == 4)
										{// 向き情報を読み取ったら
											g_Player[nCntPlayer].aMotion[nCntMotion].Key[nCntKey].DestAngle[nCntKeyModel] = DestAngle;
										}
									}
									fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
								}
								if (nCntKeyModel < MAX_MODEL - 1)
								{// モデルごとのキーフレームが用意できる数までよりポインタが進んでない
									nCntKeyModel++;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
						}
						if (nCntKey < MAX_MODEL)
						{// キーフレームが用意できる数までよりポインタが進んでない
							nCntKey++;
						}
					}
					fscanf(pFile, "%s", &str0[0]); // ファイルを読み進める
				}
				if (nCntMotion < MAX_MOTION)
				{// モーションが用意できる数までよりポインタが進んでない
					nCntMotion++;   // モーション番号をずらす
				}
			}
		}
	}

	// ファイルを閉じて他のプログラムからいじれるようにする
	fclose(pFile);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// プレイヤーの人数だけ繰り返し
		g_Player[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);           // 移動量を初期化
		g_Player[nCntPlayer].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);            // 現在の向きを初期化
		g_Player[nCntPlayer].DestAngle = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);      // 目的の向きを初期化
		g_Player[nCntPlayer].DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 差分を初期化
		g_Player[nCntPlayer].state = PLAYERSTATE_NORMAL;                     // 通常の状態に
		g_Player[nCntPlayer].radius = D3DXVECTOR3(11.5f, 30.0f, 11.5f);      // 当たり判定を取る範囲を初期化
		g_Player[nCntPlayer].ShadowCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f); // 影の色を設定
		g_Player[nCntPlayer].ShadowWidth = 15;                               // 影の幅を設定
		g_Player[nCntPlayer].ShadowDepth = 15;                               // 影の奥行を設定
		g_Player[nCntPlayer].pMasu = NULL;                                   // マスのポインタを空にしておく
		g_Player[nCntPlayer].bJump = false;                                  // ジャンプしていない状態に
		g_Player[nCntPlayer].bGrab = false;                                  // ツタにつかまっていない状態
		g_Player[nCntPlayer].bDisp = true;                                   // 描画する状態にする
		g_Player[nCntPlayer].mState = MOTIONSTATE_NORMAL;                    // モーションの状態は通常の状態に

		// 影の番号を設定
		g_Player[nCntPlayer].nIdxShadow = SetShadow(D3DXVECTOR3(g_Player[nCntPlayer].pos.x, 1.0f, g_Player[nCntPlayer].pos.z), g_Player[nCntPlayer].rot, g_Player[nCntPlayer].ShadowCol, g_Player[nCntPlayer].ShadowWidth, g_Player[nCntPlayer].ShadowDepth);

		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// モデルのパーツ数分繰り返し
			g_Player[nCntPlayer].aModel[nCntModel].posStd = g_Player[nCntPlayer].aModel[nCntModel].pos;
			g_Player[nCntPlayer].aModel[nCntModel].rot = g_Player[nCntPlayer].aMotion[nCntModel].Key[g_Player[nCntPlayer].state].DestAngle[nCntModel];
		}
	}

	g_Player[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 現在の位置を初期化
	g_Player[0].posold = g_Player[0].pos;  // 現在の位置を初期化

	g_Player[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // 現在の位置を初期化
	g_Player[1].posold = g_Player[1].pos;  // 現在の位置を初期化

	if (GetMode() == MODE_CLEAR || GetMode() == MODE_OVER)
	{// 結果画面だったら
		g_Player[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 現在の向きを初期化
		g_Player[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 現在の向きを初期化
	}

	g_PlayerPossible = 0;   // 番号は0に
	g_ChangeTimer = 0;      // タイマーは0に
	g_bPlayerMoveFlag = false; // 動ける状態ではなくする
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// プレイヤーの数だけ繰り返し
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// モデルのパーツ数だけ繰り返し
		 // メッシュの破棄
			if (g_Player[nCntPlayer].aModel[nCntModel].pMesh != NULL)
			{
				g_Player[nCntPlayer].aModel[nCntModel].pMesh->Release();
				g_Player[nCntPlayer].aModel[nCntModel].pMesh = NULL;
			}

			// マテリアルの破棄
			if (g_Player[nCntPlayer].aModel[nCntModel].pBuffMat != NULL)
			{
				g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->Release();
				g_Player[nCntPlayer].aModel[nCntModel].pBuffMat = NULL;
			}

			// テクスチャの破棄
			for (DWORD nCntMat = 0; nCntMat < g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
			{
				if (g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] != NULL)
				{
					g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]->Release();
					g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat] = NULL;
				}
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	int nMasu;

	MODE g_Mode = GetMode();

	if (g_Mode == MODE_GAME)
	{

		if (GetTimer() != -1)
		{//タイマーが動いていれば
			if (g_bPlayerMoveFlag == true )
			{//プレイヤーが動ける状態であれば

				if (g_Player[g_PlayerPossible].bDisp == true)
				{
					if (g_Player[g_PlayerPossible].state != PLAYERSTATE_PANCH
						&& g_Player[g_PlayerPossible].state != PLAYERSTATE_LANDING)
					{// 動ける状態である
					 // 移動処理
						PlayerMove(g_PlayerPossible);

						// 操作できないプレイヤーの処理
						PlayerImpossible((g_PlayerPossible + 1) % 2);

					}
				}
			}
		}
		else
		{//動いていなければ
			if (g_Player[g_PlayerPossible].state != PLAYERSTATE_NORMAL)
			{
				g_Player[g_PlayerPossible].state = PLAYERSTATE_NORMAL;   // 通常状態に
																		 // モーション切り替え処理
				SwitchMotion(g_PlayerPossible);
			}
			g_Player[g_PlayerPossible].move.y += GRAVITY_POWER;
			g_Player[g_PlayerPossible].pos.y += g_Player[g_PlayerPossible].move.y;

			if (g_Player[g_PlayerPossible].pos.y < 0.0f)
			{// 着地した
				g_Player[g_PlayerPossible].pos.y = 0.0f;
				g_Player[g_PlayerPossible].move.y = 0.0f;
				if (g_Player[g_PlayerPossible].bJump == true)
				{// ジャンプしていた
					if (g_Player[g_PlayerPossible].move.x <= 0.5f && g_Player[g_PlayerPossible].move.x >= -0.5f &&
						g_Player[g_PlayerPossible].move.z <= 0.5f && g_Player[g_PlayerPossible].move.z >= -0.5f)
					{// 移動していなかったら
						g_Player[g_PlayerPossible].state = PLAYERSTATE_LANDING;  // 着地状態に
																				 // モーション切り替え処理
						SwitchMotion(g_PlayerPossible);
					}
				}
				else if (g_Player[g_PlayerPossible].state == PLAYERSTATE_DAMAGE)
				{// ダメージ状態だった
					g_Player[g_PlayerPossible].state = PLAYERSTATE_LANDING;  // 着地状態に
																			 // モーション切り替え処理
					SwitchMotion(g_PlayerPossible);
				}
				else if (g_Player[g_PlayerPossible].state == PLAYERSTATE_KICK)
				{// キック状態だった
					if (g_Player[g_PlayerPossible].move.x <= 0.5f && g_Player[g_PlayerPossible].move.x >= -0.5f &&
						g_Player[g_PlayerPossible].move.z <= 0.5f && g_Player[g_PlayerPossible].move.z >= -0.5f)
					{// 移動していなかったら
						g_Player[g_PlayerPossible].state = PLAYERSTATE_LANDING;  // 着地状態に
																				 // モーション切り替え処理
						SwitchMotion(g_PlayerPossible);
					}
					else if (g_Player[g_PlayerPossible].move.x > 0.5f || g_Player[g_PlayerPossible].move.x < -0.5f ||
						g_Player[g_PlayerPossible].move.z > 0.5f || g_Player[g_PlayerPossible].move.z < -0.5f)
					{// 移動していたら
						if (g_Player[g_PlayerPossible].state != PLAYERSTATE_MOVE)
						{// 移動している状態じゃなかったら
							g_Player[g_PlayerPossible].state = PLAYERSTATE_MOVE;   // 移動している状態に
																				   // モーション切り替え処理
							SwitchMotion(g_PlayerPossible);
						}
					}
				}
				g_Player[g_PlayerPossible].bJump = false;  // ジャンプしていない判定に
			}
		}

		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{// プレイヤーの数だけ繰り返し
			if (g_Player[nCntPlayer].bDisp == true)
			{// 描画する状態ならば
				if (g_Player[nCntPlayer].mState == MOTIONSTATE_NORMAL)
				{// 通常のモーション状態だったら
				 // モーション処理
					PlayerMotion(nCntPlayer);
				}
				else if (g_Player[nCntPlayer].mState == MOTIONSTATE_SWITCH)
				{// モーション切り替え状態だったら
				 // モーションブレンド処理
					PlayerMotionBlend(nCntPlayer);
				}

				if (g_Player[nCntPlayer].mState == MOTIONSTATE_NORMAL)
				{// キーフレームを進める状態だったら
				 // モーション進行処理
					PlayerMotionAdvance(nCntPlayer);
				}

				SetOrbit(D3DXVECTOR3(g_Player[nCntPlayer].aModel[0].mtxWorld._41, g_Player[nCntPlayer].aModel[0].mtxWorld._42 - 7.0f, g_Player[nCntPlayer].aModel[0].mtxWorld._43), D3DXVECTOR3(g_Player[nCntPlayer].aModel[1].mtxWorld._41, g_Player[nCntPlayer].aModel[1].mtxWorld._42 + 10.0f, g_Player[nCntPlayer].aModel[1].mtxWorld._43), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f), nCntPlayer);


				if (g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE)
				{// ダメージ状態だったら
					for (int nCntParticle = 0; nCntParticle < 1; nCntParticle++)
					{// 発生させるパーティクルの数だけ繰り返し
						SetParticle(D3DXVECTOR3(g_Player[nCntPlayer].aModel[0].mtxWorld._41, g_Player[nCntPlayer].aModel[0].mtxWorld._42, g_Player[nCntPlayer].aModel[0].mtxWorld._43), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 100 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 100 * D3DX_PI / 100 - 1.0f) * 1.5f, 0.0f), 8.0f, 60);
					}
				}

				if (CollisionObstacle(&g_Player[nCntPlayer].pos, &g_Player[nCntPlayer].posold, &g_Player[nCntPlayer].move, D3DXVECTOR3(12.0f, 30.0f, 12.0f)) == true)
				{// 障害物に当たっている
					if (g_Player[nCntPlayer].state == PLAYERSTATE_KICK || g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE)
					{// キックしているかダメージ状態だったら
						g_Player[nCntPlayer].state = PLAYERSTATE_LANDING;   // 着地の状態に
						SwitchMotion(nCntPlayer);
					}
					if (g_Player[nCntPlayer].bJump == true)
					{// ジャンプしている
						if (g_Player[nCntPlayer].move.x <= 0.5f && g_Player[nCntPlayer].move.x >= -0.5f &&
							g_Player[nCntPlayer].move.z <= 0.5f && g_Player[nCntPlayer].move.z >= -0.5f)
						{// 移動していなかったら
							if (g_Player[nCntPlayer].state != PLAYERSTATE_LANDING)
							{// 移動していない状態じゃなかったら
								g_Player[nCntPlayer].state = PLAYERSTATE_LANDING;   // 着地の状態に
								SwitchMotion(nCntPlayer);
							}
						}
						else if (g_Player[nCntPlayer].move.x > 0.5f || g_Player[nCntPlayer].move.x < -0.5f ||
							g_Player[nCntPlayer].move.z > 0.5f || g_Player[nCntPlayer].move.z < -0.5f)
						{// 移動していたら
							if (g_Player[nCntPlayer].state != PLAYERSTATE_MOVE)
							{// 移動している状態じゃなかったら
								g_Player[nCntPlayer].state = PLAYERSTATE_MOVE;     // 移動している状態に
								SwitchMotion(nCntPlayer);
							}
						}
					}
					g_Player[nCntPlayer].bJump = false;  // ジャンプしない判定に
				}

				if (CollisionMasu(&g_Player[nCntPlayer].pos, &g_Player[nCntPlayer].posold, &g_Player[nCntPlayer].move, D3DXVECTOR3(15.0f, 30.0f, 15.0f), &g_Player[nCntPlayer].pMasu) == true)
				{// マスに当たっている
					if (g_Player[nCntPlayer].state == PLAYERSTATE_KICK || g_Player[nCntPlayer].state == PLAYERSTATE_DAMAGE)
					{// キックしているかダメージ状態だったら
						g_Player[nCntPlayer].state = PLAYERSTATE_LANDING;   // 着地の状態に
						SwitchMotion(nCntPlayer);
					}
					if (g_Player[nCntPlayer].bJump == true)
					{// ジャンプしている
						if (g_Player[nCntPlayer].move.x <= 0.5f && g_Player[nCntPlayer].move.x >= -0.5f &&
							g_Player[nCntPlayer].move.z <= 0.5f && g_Player[nCntPlayer].move.z >= -0.5f)
						{// 移動していなかったら
							if (g_Player[nCntPlayer].state != PLAYERSTATE_LANDING)
							{// 移動していない状態じゃなかったら
								g_Player[nCntPlayer].state = PLAYERSTATE_LANDING;   // 着地の状態に
								SwitchMotion(nCntPlayer);
							}
						}
						else if (g_Player[nCntPlayer].move.x > 0.5f || g_Player[nCntPlayer].move.x < -0.5f ||
							g_Player[nCntPlayer].move.z > 0.5f || g_Player[nCntPlayer].move.z < -0.5f)
						{// 移動していたら
							if (g_Player[nCntPlayer].state != PLAYERSTATE_MOVE)
							{// 移動している状態じゃなかったら
								g_Player[nCntPlayer].state = PLAYERSTATE_MOVE;     // 移動している状態に
								SwitchMotion(nCntPlayer);
							}
						}
					}
					g_Player[nCntPlayer].bJump = false;  // ジャンプしない判定に

					if (g_Player[nCntPlayer].pMasu->masuType == MASUTYPE_NORMAL)
					{
						g_Player[nCntPlayer].pMasu->bUse = false;

						nMasu = rand() % 4;

						if (nMasu == 0)
						{
							SetMasu(g_Player[nCntPlayer].pMasu->pos, MASUTYPE_JUMP_UP);
							PlaySound(SOUND_LABEL_SE009);							for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
							{// 発生させるパーティクルの数だけ繰り返し
								SetParticle(g_Player[nCntPlayer].pMasu->pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
							}

						}
						else if (nMasu == 1)
						{
							SetMasu(g_Player[nCntPlayer].pMasu->pos, MASUTYPE_JUMP_DOWN);

							PlaySound(SOUND_LABEL_SE010);

							for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
							{// 発生させるパーティクルの数だけ繰り返し
								SetParticle(g_Player[nCntPlayer].pMasu->pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
							}
						}
						else if (nMasu == 2)
						{
							SetMasu(g_Player[nCntPlayer].pMasu->pos, MASUTYPE_SPEED_DOWN);

							PlaySound(SOUND_LABEL_SE010);

							for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
							{// 発生させるパーティクルの数だけ繰り返し
								SetParticle(g_Player[nCntPlayer].pMasu->pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
							}
						}
						else if (nMasu == 3)
						{
							SetMasu(g_Player[nCntPlayer].pMasu->pos, MASUTYPE_SPEED_UP);

							PlaySound(SOUND_LABEL_SE009);

							for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
							{// 発生させるパーティクルの数だけ繰り返し
								SetParticle(g_Player[nCntPlayer].pMasu->pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
							}
						}
					}
				}
				else
				{
					if (g_Player[g_PlayerPossible].bGrab == false)
					{// ツタにつかまっていない
						if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoyPadTrigger(DIJS_BUTTON_2, g_PlayerPossible))
						{// アクションボタンが押された
							if (g_Player[g_PlayerPossible].bJump == true)
							{// 空中にいる
								g_Player[g_PlayerPossible].state = PLAYERSTATE_KICK;   // キック状態に
								PlaySound(SOUND_LABEL_SE013);
																					   // モーション切り替え処理
								SwitchMotion(g_PlayerPossible);
							}
							else
							{
								g_Player[g_PlayerPossible].state = PLAYERSTATE_PANCH;  // パンチ状態に
								PlaySound(SOUND_LABEL_SE005);
																					   // モーション切り替え処理
								SwitchMotion(g_PlayerPossible);
							}
						}

						if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoyPadTrigger(DIJS_BUTTON_2, g_PlayerPossible ^ 1))
						{// アクションボタンが押された
							if (g_Player[g_PlayerPossible ^ 1].bJump == true)
							{// 空中にいる
								g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_KICK;   // キック状態に
																					   // モーション切り替え処理
								SwitchMotion(g_PlayerPossible ^ 1);
							}
							else
							{
								g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_PANCH;  // パンチ状態に
																					   // モーション切り替え処理
								SwitchMotion(g_PlayerPossible ^ 1);
							}
						}

					}
				}

				if (g_Player[nCntPlayer].pMasu != NULL)
				{
					if (g_Player[nCntPlayer].pMasu->masuType == MASUTYPE_GOAL)
					{

						SetGameState(GAMESTATE_CLEAR);
					}
				}
			}
			else
			{// 描画しない状態ならば
				g_ChangeTimer++;
				if (g_ChangeTimer >= 60)
				{// 一秒経過
					g_Player[g_PlayerPossible].bDisp = true;
					//位置かえ
					//D3DXVECTOR3 NearMasu = PlayerDistance(g_Player[g_PlayerPossible].pos);
					g_Player[g_PlayerPossible].pos = g_Player[g_PlayerPossible].pMasu->pos;
					g_Player[g_PlayerPossible].posold = g_Player[g_PlayerPossible].pMasu->pos;
					g_Player[g_PlayerPossible].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

					g_Player[g_PlayerPossible].ShadowCol.a = 0.35f;  // 影をもう一度出す

																	 // 影の位置更新
					SetPositionShadow(g_Player[g_PlayerPossible].nIdxShadow, D3DXVECTOR3(g_Player[g_PlayerPossible].pos.x, 0.0f, g_Player[g_PlayerPossible].pos.z));
					// 影の色更新
					SetColShadow(g_Player[g_PlayerPossible].nIdxShadow, g_Player[g_PlayerPossible].ShadowCol);
					// 影の大きさ更新
					SetSizeShadow(g_Player[g_PlayerPossible].nIdxShadow, g_Player[g_PlayerPossible].ShadowWidth, g_Player[g_PlayerPossible].ShadowDepth);

					// 軌道の位置修正(1人目)
					SetPosiotionOrbit(D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[0].mtxWorld._41, g_Player[g_PlayerPossible].aModel[0].mtxWorld._42 - 7.0f, g_Player[g_PlayerPossible].aModel[0].mtxWorld._43), D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[1].mtxWorld._41, g_Player[g_PlayerPossible].aModel[1].mtxWorld._42 + 10.0f, g_Player[g_PlayerPossible].aModel[1].mtxWorld._43), g_PlayerPossible);

					if (GetIdxPlayer() == 1)
					{
						AddTurnNum(1);
					}

					// モーション切り替え処理
					SwitchMotion(g_PlayerPossible);
					g_PlayerPossible = (g_PlayerPossible + 1) % 2;          // 操作できるプレイヤーを入れ替える

					SetTurnState(TURNSTATE_DICE);

					g_ChangeTimer = 0;  // タイマーを戻す

					// 軌道の位置修正(2人目)
					SetPosiotionOrbit(D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[0].mtxWorld._41, g_Player[g_PlayerPossible].aModel[0].mtxWorld._42 - 7.0f, g_Player[g_PlayerPossible].aModel[0].mtxWorld._43), D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[1].mtxWorld._41, g_Player[g_PlayerPossible].aModel[1].mtxWorld._42 + 10.0f, g_Player[g_PlayerPossible].aModel[1].mtxWorld._43), g_PlayerPossible);

				}
			}
		}

		if (g_Player[g_PlayerPossible].bGrab == false)
		{// ツタにつかまっていない
		 // プレイヤーの攻撃処理
			if (g_Player[g_PlayerPossible].state == PLAYERSTATE_PANCH)
			{// パンチモーションだったら
				g_Player[g_PlayerPossible].move.x = 0.0f;  // 移動を無視
				g_Player[g_PlayerPossible].move.z = 0.0f;  // 移動を無視
				if (g_Player[g_PlayerPossible].nKey >= 2)
				{// モーションが16フレーム分再生できた
					CollisionPlayer(0, g_PlayerPossible, (g_PlayerPossible + 1) % 2);
				}
				// エフェクトの設定
				SetEffect(D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[3].mtxWorld._41, g_Player[g_PlayerPossible].aModel[3].mtxWorld._42, g_Player[g_PlayerPossible].aModel[3].mtxWorld._43), g_Player[g_PlayerPossible].rot, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 15.0f, 100);
			}
			else if (g_Player[g_PlayerPossible].state == PLAYERSTATE_KICK)
			{// キックモーションだったら
				CollisionPlayer(0, g_PlayerPossible, (g_PlayerPossible + 1) % 2);
				// エフェクトの設定
				SetEffect(D3DXVECTOR3(g_Player[g_PlayerPossible].aModel[7].mtxWorld._41, g_Player[g_PlayerPossible].aModel[7].mtxWorld._42, g_Player[g_PlayerPossible].aModel[7].mtxWorld._43), g_Player[g_PlayerPossible].rot, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 15.0f, 100);
			}
		}

		if (g_Player[g_PlayerPossible].state != PLAYERSTATE_GRABJUMP && g_Player[g_PlayerPossible].bGrab == false)
		{// ツタにつかまっていない
			if (CollisionBillboard(g_Player[g_PlayerPossible].pos, D3DXVECTOR3(10.0f, 20.0f, 10.0f)) == true)
			{// ツタに触れた
				g_Player[g_PlayerPossible].move.y = 0.0f;             // 重力を無視
				g_Player[g_PlayerPossible].move.x = 0.0f;             // 移動を無視
				g_Player[g_PlayerPossible].move.z = 0.0f;             // 移動を無視
				g_Player[g_PlayerPossible].state = PLAYERSTATE_GRAB;  // ツタにつかまっている状態にする
				g_Player[g_PlayerPossible].bJump = false;             // ジャンプしていない状態に
				g_Player[g_PlayerPossible].bGrab = true;              // ツタにつかまっている状態に
																	  // モーション切り替え処理
				SwitchMotion(g_PlayerPossible);
				PlaySound(SOUND_LABEL_SE011);
			}
		}
		else if (g_Player[g_PlayerPossible].bGrab == true)
		{// ツタにつかまっている
			if (CollisionBillboard(g_Player[g_PlayerPossible].pos, D3DXVECTOR3(10.0f, 20.0f, 10.0f)) == false)
			{// ツタに触れた
				g_Player[g_PlayerPossible].move.y = 0.0f;                  // 重力を無視
				g_Player[g_PlayerPossible].state = PLAYERSTATE_GRABJUMP;   // ツタにつかまっている状態にする
				g_Player[g_PlayerPossible].bJump = true;                   // ジャンプしている状態に
				g_Player[g_PlayerPossible].bGrab = false;                  // ツタにつかまっていない状態に
			}
		}
		else if (g_Player[g_PlayerPossible].move.y <= -5.0f && g_Player[g_PlayerPossible].state == PLAYERSTATE_GRABJUMP)
		{// ツタからジャンプしたが落ちている
			if (CollisionBillboard(g_Player[g_PlayerPossible].pos, D3DXVECTOR3(10.0f, 40.0f, 10.0f)) == true)
			{// ツタに触れた
				g_Player[g_PlayerPossible].move.y = 0.0f;             // 重力を無視
				g_Player[g_PlayerPossible].state = PLAYERSTATE_GRAB;  // ツタにつかまっている状態にする
				g_Player[g_PlayerPossible].bJump = false;             // ジャンプしていない状態に
				g_Player[g_PlayerPossible].bGrab = true;              // ツタにつかまっている状態に
																	  // モーション切り替え処理
				SwitchMotion(g_PlayerPossible);
			}
		}


		if (g_Player[g_PlayerPossible ^ 1].bGrab == false)
		{// ツタにつかまっていない
		 // プレイヤーの攻撃処理
			if (g_Player[g_PlayerPossible ^ 1].state == PLAYERSTATE_PANCH)
			{// パンチモーションだったら
				PlaySound(SOUND_LABEL_SE005);
				g_Player[g_PlayerPossible ^ 1].move.x = 0.0f;  // 移動を無視
				g_Player[g_PlayerPossible ^ 1].move.z = 0.0f;  // 移動を無視
				if (g_Player[g_PlayerPossible ^ 1].nKey >= 2)
				{// モーションが16フレーム分再生できた
					CollisionPlayer(0, g_PlayerPossible ^ 1, g_PlayerPossible);
				}
				// エフェクトの設定
				SetEffect(D3DXVECTOR3(g_Player[g_PlayerPossible ^ 1].aModel[3].mtxWorld._41, g_Player[g_PlayerPossible ^ 1].aModel[3].mtxWorld._42, g_Player[g_PlayerPossible ^ 1].aModel[3].mtxWorld._43), g_Player[g_PlayerPossible ^ 1].rot, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 15.0f, 100);
			}
			else if (g_Player[g_PlayerPossible ^ 1].state == PLAYERSTATE_KICK)
			{// キックモーションだったら
				PlaySound(SOUND_LABEL_SE013);
				CollisionPlayer(0, g_PlayerPossible ^ 1, g_PlayerPossible);
				// エフェクトの設定
				SetEffect(D3DXVECTOR3(g_Player[g_PlayerPossible ^ 1].aModel[7].mtxWorld._41, g_Player[g_PlayerPossible ^ 1].aModel[7].mtxWorld._42, g_Player[g_PlayerPossible ^ 1].aModel[7].mtxWorld._43), g_Player[g_PlayerPossible ^ 1].rot, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 15.0f, 100);
			}
		}

		if (g_Player[g_PlayerPossible ^ 1].state != PLAYERSTATE_GRABJUMP && g_Player[g_PlayerPossible ^ 1].bGrab == false)
		{// ツタにつかまっていない
			if (CollisionBillboard(g_Player[g_PlayerPossible ^ 1].pos, D3DXVECTOR3(10.0f, 20.0f, 10.0f)) == true)
			{// ツタに触れた
				g_Player[g_PlayerPossible ^ 1].move.y = 0.0f;             // 重力を無視
				g_Player[g_PlayerPossible ^ 1].move.x = 0.0f;             // 移動を無視
				g_Player[g_PlayerPossible ^ 1].move.z = 0.0f;             // 移動を無視
				g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_GRAB;  // ツタにつかまっている状態にする
				g_Player[g_PlayerPossible ^ 1].bJump = false;             // ジャンプしていない状態に
				g_Player[g_PlayerPossible ^ 1].bGrab = true;              // ツタにつかまっている状態に
																	  // モーション切り替え処理
				SwitchMotion(g_PlayerPossible ^ 1);
				PlaySound(SOUND_LABEL_SE011);
			}
		}
		else if (g_Player[g_PlayerPossible ^ 1].bGrab == true)
		{// ツタにつかまっている
			if (CollisionBillboard(g_Player[g_PlayerPossible ^ 1].pos, D3DXVECTOR3(10.0f, 20.0f, 10.0f)) == false)
			{// ツタに触れた
				g_Player[g_PlayerPossible ^ 1].move.y = 0.0f;                  // 重力を無視
				g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_GRABJUMP;   // ツタにつかまっている状態にする
				g_Player[g_PlayerPossible ^ 1].bJump = true;                   // ジャンプしている状態に
				g_Player[g_PlayerPossible ^ 1].bGrab = false;                  // ツタにつかまっていない状態に
			}
		}
		else if (g_Player[g_PlayerPossible ^ 1].move.y <= -5.0f && g_Player[g_PlayerPossible ^ 1].state == PLAYERSTATE_GRABJUMP)
		{// ツタからジャンプしたが落ちている
			if (CollisionBillboard(g_Player[g_PlayerPossible ^ 1].pos, D3DXVECTOR3(10.0f, 40.0f, 10.0f)) == true)
			{// ツタに触れた
				g_Player[g_PlayerPossible ^ 1].move.y = 0.0f;             // 重力を無視
				g_Player[g_PlayerPossible ^ 1].state = PLAYERSTATE_GRAB;  // ツタにつかまっている状態にする
				g_Player[g_PlayerPossible ^ 1].bJump = false;             // ジャンプしていない状態に
				g_Player[g_PlayerPossible ^ 1].bGrab = true;              // ツタにつかまっている状態に
																	  // モーション切り替え処理
				SwitchMotion(g_PlayerPossible ^ 1);
			}
		}

		// 影の位置更新
		SetPositionShadow(g_Player[g_PlayerPossible].nIdxShadow, D3DXVECTOR3(g_Player[g_PlayerPossible].pos.x, g_Player[g_PlayerPossible].pos.y + 1.0f, g_Player[g_PlayerPossible].pos.z));

		// 影の色更新
		SetColShadow(g_Player[g_PlayerPossible].nIdxShadow, g_Player[g_PlayerPossible].ShadowCol);

		// 影の大きさ更新
		SetSizeShadow(g_Player[g_PlayerPossible].nIdxShadow, g_Player[g_PlayerPossible].ShadowWidth, g_Player[g_PlayerPossible].ShadowDepth);

#if _DEBUG

		if (GetKeyboardTrigger(DIK_F2) == true || GetJoyPadTrigger(DIJS_BUTTON_5, g_PlayerPossible) == TRUE)
		{// プレイヤーの切り替え
		 //g_Player[g_PlayerPossible].move.y = 0.0f;               // 重力を無視
		 //g_Player[g_PlayerPossible].move.x = 0.0f;               // 移動を無視
		 //g_Player[g_PlayerPossible].move.z = 0.0f;               // 移動を無視
		 //g_Player[g_PlayerPossible].state = PLAYERSTATE_NORMAL;  // 通常状態にする
		 //g_Player[g_PlayerPossible].bJump = false;               // ジャンプしていない状態に
		 //g_Player[g_PlayerPossible].bGrab = false;               // ツタにつかまっていない状態に
		 // モーション切り替え処理
			PlayerChange(g_PlayerPossible);

			//SwitchMotion(g_PlayerPossible);
			//g_PlayerPossible = (g_PlayerPossible + 1) % 2;          // 操作できるプレイヤーを入れ替える
		}
#endif

		//ランクの取得
		RANK *pRank;
		pRank = GetRank();

		if (g_PlayerPossible == 0)
		{//操作プレイヤーが０番の場合
			if (g_Player[0].pos.z >= g_Player[1].pos.z)
			{//プレイヤー０がプレイヤー１より前の場合
				SetRank(RANK_1);	//ランク１に設定
			}
			else
			{//それ以外の場合
				SetRank(RANK_2);	//ランク２に設定
			}
		}
		else if (g_PlayerPossible == 1)
		{//操作プレイヤーが１番の場合
			if (g_Player[0].pos.z <= g_Player[1].pos.z)
			{//プレイヤー１がプレイヤー０より前の場合
				SetRank(RANK_1);	//ランク１に設定
			}
			else
			{
				SetRank(RANK_2);	//ランク２に設定
			}
		}
	}
	else if (g_Mode == MODE_CLEAR)
	{// ゲームクリア
		if (GetIdxPlayer() == 0)
		{// プレイヤー0が勝ったらこの位置
			g_Player[0].pos = D3DXVECTOR3(-40.0f, 0.0f, -1550.0f);	// 位置
			g_Player[1].pos = D3DXVECTOR3(50.0f, 0.0f, -1500.0f);	// 位置
		}
		else if (GetIdxPlayer() == 1)
		{// プレイヤー1が勝ったらこの位置
			g_Player[1].pos = D3DXVECTOR3(-40.0f, 0.0f, -1550.0f);	// 位置
			g_Player[0].pos = D3DXVECTOR3(50.0f, 0.0f, -1500.0f);	// 位置
		}

		// プレイヤーのモーション
		if (g_Player[0].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotion(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotion(1);
		}
		if (g_Player[0].mState == MOTIONSTATE_SWITCH)
		{
			PlayerMotionBlend(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_SWITCH)
		{
			PlayerMotionBlend(1);
		}
		if (g_Player[0].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotionAdvance(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotionAdvance(1);
		}
	}
	else if (g_Mode == MODE_OVER)
	{// ゲームオーバー
		g_Player[0].pos = D3DXVECTOR3(-40.0f, 0.0f, -1480.0f);	// 位置
		g_Player[1].pos = D3DXVECTOR3(50.0f, 0.0f, -1480.0f);	// 位置

																// プレイヤーのモーション
		if (g_Player[0].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotion(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotion(1);
		}
		if (g_Player[0].mState == MOTIONSTATE_SWITCH)
		{
			PlayerMotionBlend(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_SWITCH)
		{
			PlayerMotionBlend(1);
		}
		if (g_Player[0].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotionAdvance(0);
		}
		if (g_Player[1].mState == MOTIONSTATE_NORMAL)
		{
			PlayerMotionAdvance(1);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;      // 計算用マトリックス
	D3DXVECTOR3 vecRot, vecTrans;               // 計算用モデルの向き,座標
	D3DMATERIAL9 matDef;                        // 現在のマテリアル保存用
	D3DXMATERIAL *pMat;                         // マテリアルデータへのポインタ

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// プレイヤーの人数だけ繰り返し
		if (g_Player[nCntPlayer].bDisp == true)
		{// 描画する状態なら
		 // ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player[nCntPlayer].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player[nCntPlayer].rot.y, g_Player[nCntPlayer].rot.x, g_Player[nCntPlayer].rot.z);
			D3DXMatrixMultiply(&g_Player[nCntPlayer].mtxWorld, &g_Player[nCntPlayer].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Player[nCntPlayer].pos.x, g_Player[nCntPlayer].pos.y, g_Player[nCntPlayer].pos.z);
			D3DXMatrixMultiply(&g_Player[nCntPlayer].mtxWorld, &g_Player[nCntPlayer].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player[nCntPlayer].mtxWorld);

			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{// モデルのパーツ数だけ繰り返し
				if (g_Player[nCntPlayer].aModel[nCntModel].nIdxModelParent == -1)
				{// 親がいない
					mtxParent = g_Player[nCntPlayer].mtxWorld;     // プレイヤーのマトリックス情報をもらう
				}
				else
				{// 親がいる
					mtxParent = g_Player[nCntPlayer].aModel[g_Player[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;   // 親モデルのマトリックス情報をもらう
				}
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player[nCntPlayer].aModel[nCntModel].rot.y, g_Player[nCntPlayer].aModel[nCntModel].rot.x, g_Player[nCntPlayer].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Player[nCntPlayer].aModel[nCntModel].pos.x, g_Player[nCntPlayer].aModel[nCntModel].pos.y, g_Player[nCntPlayer].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxTrans);

				// 親の情報を自分に反映
				D3DXMatrixMultiply(&g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxParent);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Player[nCntPlayer].aModel[nCntModel].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_Player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
				{// 設定されていたマテリアルの数だけ繰り返し
				 // マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					pDevice->SetTexture(0, g_Player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);

					// モデル(パーツ)の描画
					g_Player[nCntPlayer].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				// 保存していたマテリアルに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=============================================================================
// プレイヤーの移動処理
//=============================================================================
void PlayerMove(int nIdxPlayer)
{
	g_Player[nIdxPlayer].posold = g_Player[nIdxPlayer].pos;   // 前回の位置更新

															  //プレイヤーの取得
	Player *pPlayer;
	pPlayer = GetPlayer();


	if (g_Player[nIdxPlayer].bGrab == false)
	{// ツタにつかまっていない
		if (GetKeyboardPress(DIK_A) == true)
		{// 左方向の入力がされた
			Camera *pCamera;
			pCamera = GetCamera();
			if (GetKeyboardPress(DIK_W) == true)
			{// 同時に上方向の入力がされた
			 // 移動処理
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.75f);
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// 同時に下方向の入力がされた
			 // 移動処理
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.25f);
			}
			else
			{// 何も押されてない
			 // 移動処理
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.5f);
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// 右方向の入力がされた
			Camera *pCamera;
			pCamera = GetCamera();
			if (GetKeyboardPress(DIK_W) == true)
			{// 同時に上方向の入力がされた
			 // 移動処理
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.75f);
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// 同時に下方向の入力がされた
			 // 移動処理
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.25f);
			}
			else
			{// 何も押されてない
			 // 移動処理
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.5f);
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// 上方向の入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y + D3DX_PI) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y + D3DX_PI) * g_Player[nIdxPlayer].fMovement;

			// 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + D3DX_PI;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// 下方向の入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;

			// 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_10, g_PlayerPossible) == true || GetJoyPadPress(DIJS_BUTTON_11, g_PlayerPossible) == true ||
			GetJoyPadPress(DIJS_BUTTON_12, g_PlayerPossible) == true || GetJoyPadPress(DIJS_BUTTON_13, g_PlayerPossible) == true)
		{// 左アナログスティックの入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible)) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible)) * g_Player[nIdxPlayer].fMovement;

			// 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible);
		}
		else if (GetJoyPadPress(DIJS_BUTTON_18, g_PlayerPossible) == true || GetJoyPadPress(DIJS_BUTTON_19, g_PlayerPossible) == true
			|| GetJoyPadPress(DIJS_BUTTON_20, g_PlayerPossible) == true || GetJoyPadPress(DIJS_BUTTON_21, g_PlayerPossible) == true)
		{// 十字キー入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y + GetJotPadRadian(g_PlayerPossible)) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y + GetJotPadRadian(g_PlayerPossible)) * g_Player[nIdxPlayer].fMovement;

			// 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + GetJotPadRadian(g_PlayerPossible) - D3DX_PI;
		}
	}
	else if (g_Player[nIdxPlayer].bGrab == true)
	{// ツタにつかまっている
		if (GetJoyPadPress(DIJS_BUTTON_10, g_PlayerPossible) == TRUE ||
			GetJoyPadPress(DIJS_BUTTON_18, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_W) == true)
		{// 上方向の入力がされた
			g_Player[nIdxPlayer].move.y += 1.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_11, g_PlayerPossible) == TRUE ||
			GetJoyPadPress(DIJS_BUTTON_19, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_S) == true)
		{// 下方向の入力がされた
			g_Player[nIdxPlayer].move.y -= 1.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_16, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_A) == true)
		{// 左方向の入力がされた
		 // 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = -D3DX_PI * 0.5f;

			// 座標修正
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x - 7.0f;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_17, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_D) == true)
		{// 右方向の入力がされた
		 // 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = D3DX_PI * 0.5f;

			// 座標修正
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x + 7.0f;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_14, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_K) == true)
		{// 上方向の入力がされた
		 // 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = D3DX_PI;

			// 座標修正
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z - 10.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_15, g_PlayerPossible) == TRUE ||
			GetKeyboardPress(DIK_I) == true)
		{// 下方向の入力がされた
		 // 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = 0.0f;

			// 座標修正
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z + 10.0f;
		}
		if (g_Player[nIdxPlayer].move.y <= 0.1f && g_Player[nIdxPlayer].move.y >= -0.1f)
		{// 移動していなかったら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABNOR)
			{// 移動していない状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABNOR;        // ツタニュートラルの状態に
																		 // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.y > 0.1f)
		{// 上っている
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABUP)
			{// 移動している状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABUP;         // ツタを上っている状態に
																		 // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.y < -0.1f)
		{// 下っていたら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABDOWN)
			{// 移動している状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABDOWN;        // ツタを下りている状態に
																		  // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
	}


	if (GetJoyPadTrigger(DIJS_BUTTON_1, g_PlayerPossible) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
	{// キーボードの[ENTER]キーが押された
		if (g_Player[nIdxPlayer].bJump == false)
		{// ジャンプしていなかった
			if (g_Player[nIdxPlayer].bGrab == true)
			{// ツタにつかまっている
				Camera *pCamera;
				pCamera = GetCamera();

				// 移動処理
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + D3DX_PI;

				g_Player[nIdxPlayer].move.y += g_Player[nIdxPlayer].fJumpPower;          // 上に飛ばす
				g_Player[nIdxPlayer].bJump = true;                  // ジャンプしている判定に
				g_Player[nIdxPlayer].bGrab = false;                 // ツタにつかまっていない状態に
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABJUMP;  // ツタからジャンプした状態に
				PlaySound(SOUND_LABEL_SE011);		
				// モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else
			{// ツタにつかまっていない
				g_Player[nIdxPlayer].move.y += g_Player[nIdxPlayer].fJumpPower;    // 上に飛ばす
				g_Player[nIdxPlayer].bJump = true;                  // ジャンプしている判定に
				g_Player[nIdxPlayer].state = PLAYERSTATE_JUMP;      // ジャンプ状態に
				PlaySound(SOUND_LABEL_SE008);
				// モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// 目的の角度の修正
	g_Player[nIdxPlayer].DiffAngle.y = g_Player[nIdxPlayer].DestAngle.y - g_Player[nIdxPlayer].rot.y;   // 現在の向きと目的の向きの差分を計算

	if (g_Player[nIdxPlayer].DiffAngle.y > D3DX_PI)
	{// 差分がD3DX_PIを超えた
		g_Player[nIdxPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].DiffAngle.y < -D3DX_PI)
	{// 差分が-D3DX_PIを超えた
		g_Player[nIdxPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	//現在の角度の修正
	g_Player[nIdxPlayer].rot.y += g_Player[nIdxPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nIdxPlayer].rot.y > D3DX_PI)
	{// 現在の向きがD3DX_PIを超えた
		g_Player[nIdxPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].rot.y < -D3DX_PI)
	{// 現在の向きが-D3DX_PIを超えた
		g_Player[nIdxPlayer].rot.y += D3DX_PI * 2.0f;
	}

	// 落下処理
	if (g_Player[nIdxPlayer].bGrab == false)
	{// ツタにつかまっていない
		g_Player[nIdxPlayer].move.y += GRAVITY_POWER;
	}

	// 位置を移動
	g_Player[nIdxPlayer].pos.x += g_Player[nIdxPlayer].move.x;
	g_Player[nIdxPlayer].pos.y += g_Player[nIdxPlayer].move.y;
	g_Player[nIdxPlayer].pos.z += g_Player[nIdxPlayer].move.z;

	if (g_Player[nIdxPlayer].bGrab == true)
	{// ツタにつかまっている
		g_Player[nIdxPlayer].move.y = 0.0f;
	}

	if (g_Player[nIdxPlayer].bJump == false && g_Player[nIdxPlayer].state != PLAYERSTATE_LANDING && g_Player[nIdxPlayer].state != PLAYERSTATE_KICK && g_Player[nIdxPlayer].state != PLAYERSTATE_PANCH
		&& g_Player[nIdxPlayer].state != PLAYERSTATE_DAMAGE && g_Player[nIdxPlayer].bGrab == false)
	{// ジャンプしていないかつ着地状態でないかつアクション状態でないかつダメージ状態でない
		if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
			g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
		{// 移動していなかったら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_NORMAL)
			{// 移動していない状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;   // 通常の状態に
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
			g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
		{// 移動していたら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
			{// 移動している状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;     // 移動している状態に
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// コースの当たり判定
#if 1
	if (CollisionCourse(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold, &g_Player[nIdxPlayer].move, D3DXVECTOR3(0.0f, 0.0f, 0.0f)) == true)
	{// コースに乗れている
		if (g_Player[nIdxPlayer].bJump == true)
		{// ジャンプしていた
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// ダメージ状態だった
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // 着地状態に
																   // モーション切り替え処理
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// キック状態だった
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// 移動していたら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// 移動している状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // 移動している状態に
																	// モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		g_Player[nIdxPlayer].bJump = false;  // ジャンプしていない判定に
	}
	else
	{
		if (g_Player[nIdxPlayer].pos.y < -200.0f)
		{
			PlayerChange(nIdxPlayer);
		}
	}
#endif

	// デバック用
#if 0
	if (g_Player[nIdxPlayer].pos.y <= 0.0f)
	{// 地上にいる
		g_Player[nIdxPlayer].pos.y = 0.0f;
		g_Player[nIdxPlayer].move.y = 0.0f;
		if (g_Player[nIdxPlayer].bJump == true)
		{// ジャンプしていた
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// ダメージ状態だった
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // 着地状態に
																   // モーション切り替え処理
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// キック状態だった
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// 移動していたら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// 移動している状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // 移動している状態に
																	// モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		g_Player[nIdxPlayer].bJump = false;  // ジャンプしていない判定に
	}
#endif

	// 慣性を働かせる
	g_Player[nIdxPlayer].move.x += (0.0f - g_Player[nIdxPlayer].move.x) * PLAYER_INERTIA;
	g_Player[nIdxPlayer].move.z += (0.0f - g_Player[nIdxPlayer].move.z) * PLAYER_INERTIA;
}

//=============================================================================
// 操作できるプレイヤーの遷移処理
//=============================================================================
void PlayerTransition(int nIdxPlayer)
{
	g_Player[nIdxPlayer].posold = g_Player[nIdxPlayer].pos;   // 前回の位置更新

															  // 目的の角度の修正
	g_Player[nIdxPlayer].DiffAngle.y = g_Player[nIdxPlayer].DestAngle.y - g_Player[nIdxPlayer].rot.y;   // 現在の向きと目的の向きの差分を計算

	if (g_Player[nIdxPlayer].DiffAngle.y > D3DX_PI)
	{// 差分がD3DX_PIを超えた
		g_Player[nIdxPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].DiffAngle.y < -D3DX_PI)
	{// 差分が-D3DX_PIを超えた
		g_Player[nIdxPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	//現在の角度の修正
	g_Player[nIdxPlayer].rot.y += g_Player[nIdxPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nIdxPlayer].rot.y > D3DX_PI)
	{// 現在の向きがD3DX_PIを超えた
		g_Player[nIdxPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].rot.y < -D3DX_PI)
	{// 現在の向きが-D3DX_PIを超えた
		g_Player[nIdxPlayer].rot.y += D3DX_PI * 2.0f;
	}

	// 落下処理
	if (g_Player[nIdxPlayer].bGrab == false)
	{// ツタにつかまっていない
		g_Player[nIdxPlayer].move.y += GRAVITY_POWER;
	}

	// 位置を移動
	g_Player[nIdxPlayer].pos.x += g_Player[nIdxPlayer].move.x;
	g_Player[nIdxPlayer].pos.y += g_Player[nIdxPlayer].move.y;
	g_Player[nIdxPlayer].pos.z += g_Player[nIdxPlayer].move.z;

	if (g_Player[nIdxPlayer].bGrab == true)
	{// ツタにつかまっている
		g_Player[nIdxPlayer].move.y = 0.0f;
	}

	if (g_Player[nIdxPlayer].state != PLAYERSTATE_JUMP && g_Player[nIdxPlayer].state != PLAYERSTATE_LANDING && g_Player[nIdxPlayer].state != PLAYERSTATE_KICK && g_Player[nIdxPlayer].state != PLAYERSTATE_PANCH
		&& g_Player[nIdxPlayer].state != PLAYERSTATE_DAMAGE && g_Player[nIdxPlayer].state != PLAYERSTATE_GRABJUMP && g_Player[nIdxPlayer].bGrab == false)
	{// ジャンプしていないかつ着地状態でないかつアクション状態でないかつダメージ状態でない
		if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
			g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
		{// 移動していなかったら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_NORMAL)
			{// 移動していない状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;   // 通常の状態に
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
			g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
		{// 移動していたら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
			{// 移動している状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;     // 移動している状態に
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// 影の位置更新
	SetPositionShadow(g_Player[nIdxPlayer].nIdxShadow, D3DXVECTOR3(g_Player[nIdxPlayer].pos.x, 1.0f, g_Player[nIdxPlayer].pos.z));

	// 影の色更新
	SetColShadow(g_Player[nIdxPlayer].nIdxShadow, g_Player[nIdxPlayer].ShadowCol);

	// 影の大きさ更新
	SetSizeShadow(g_Player[nIdxPlayer].nIdxShadow, g_Player[nIdxPlayer].ShadowWidth, g_Player[nIdxPlayer].ShadowDepth);

	if (CollisionObstacle(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold, &g_Player[nIdxPlayer].move, g_Player[nIdxPlayer].radius) == true)
	{// 障害物に当たっている
		if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK || g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// キックしていたら
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;   // 着地の状態に
			SwitchMotion(nIdxPlayer);
		}
		if (g_Player[nIdxPlayer].state == PLAYERSTATE_JUMP || g_Player[nIdxPlayer].state == PLAYERSTATE_GRABJUMP)
		{// ジャンプしている
			g_Player[nIdxPlayer].bJump = false;    // ジャンプする判定に
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_LANDING)
				{// 移動していない状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;   // 着地の状態に
					SwitchMotion(nIdxPlayer);
				}
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// 移動していたら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// 移動している状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;     // 移動している状態に
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		// 影の位置更新
		SetPositionShadow(g_Player[nIdxPlayer].nIdxShadow, D3DXVECTOR3(g_Player[nIdxPlayer].pos.x, g_Player[nIdxPlayer].pos.y + 1.0f, g_Player[nIdxPlayer].pos.z));
	}
	else
	{// 障害物に乗っていない
		if (g_Player[nIdxPlayer].bJump == false)
		{// ジャンプしている
			g_Player[nIdxPlayer].bJump = true;  // ジャンプしない判定に
		}
	}

	// コースの当たり判定
#if 1
	if (CollisionCourse(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold, &g_Player[nIdxPlayer].move, D3DXVECTOR3(0.0f, 0.0f, 0.0f)) == true)
	{// コースに乗れている
		if (g_Player[nIdxPlayer].state == PLAYERSTATE_JUMP || g_Player[nIdxPlayer].state == PLAYERSTATE_GRABJUMP)
		{// ジャンプしていた
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// 移動していたら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// 移動している状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // 移動している状態に
																	// モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// ダメージ状態だった
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // 着地状態に
																   // モーション切り替え処理
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// キック状態だった
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// 移動していたら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// 移動している状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // 移動している状態に
																	// モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		g_Player[nIdxPlayer].bJump = false;  // ジャンプしていない判定に
	}
	else
	{// コースに乗っていない
	 // 影の位置更新
		SetPositionShadow(g_Player[nIdxPlayer].nIdxShadow, D3DXVECTOR3(g_Player[nIdxPlayer].pos.x, g_Player[nIdxPlayer].pos.y + 1.0f, g_Player[nIdxPlayer].pos.z));

#if _DEBUG
		if (GetKeyboardTrigger(DIK_F8) == true)
		{
			g_Player[nIdxPlayer].pos.y = 30.0f;
			g_Player[nIdxPlayer].move.y = 0.0f;
		}
#endif
	}
#endif

	// デバック用
#if 0
	if (g_Player[nIdxPlayer].pos.y <= 0.0f)
	{// 地上にいる
		g_Player[nIdxPlayer].pos.y = 0.0f;
		g_Player[nIdxPlayer].move.y = 0.0f;
		g_Player[nIdxPlayer].bJump = false;  // ジャンプしていない判定に
		if (g_Player[nIdxPlayer].state == PLAYERSTATE_JUMP || g_Player[nIdxPlayer].state == PLAYERSTATE_GRABJUMP)
		{// ジャンプしていた
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// 移動していたら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// 移動している状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // 移動している状態に
																	// モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// ダメージ状態だった
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // 着地状態に
																   // モーション切り替え処理
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// キック状態だった
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// 移動していたら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// 移動している状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // 移動している状態に
																	// モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
			}
		}
	}
#endif

	// 慣性を働かせる
	g_Player[nIdxPlayer].move.x += (0.0f - g_Player[nIdxPlayer].move.x) * PLAYER_INERTIA;
	g_Player[nIdxPlayer].move.z += (0.0f - g_Player[nIdxPlayer].move.z) * PLAYER_INERTIA;
}

//=============================================================================
// 操作できないプレイヤーの処理
//=============================================================================
void PlayerImpossible(int nIdxPlayer)
{
	g_Player[nIdxPlayer].posold = g_Player[nIdxPlayer].pos;   // 前回の位置更新

	// 落下処理
	g_Player[nIdxPlayer].move.y += GRAVITY_POWER;

	if (g_Player[nIdxPlayer].bGrab == false)
	{// ツタにつかまっていない
		if (GetKeyboardPress(DIK_A) == true)
		{// 左方向の入力がされた
			Camera *pCamera;
			pCamera = GetCamera();
			if (GetKeyboardPress(DIK_W) == true)
			{// 同時に上方向の入力がされた
			 // 移動処理
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.75f);
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// 同時に下方向の入力がされた
			 // 移動処理
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.25f);
			}
			else
			{// 何も押されてない
			 // 移動処理
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.5f);
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// 右方向の入力がされた
			Camera *pCamera;
			pCamera = GetCamera();
			if (GetKeyboardPress(DIK_W) == true)
			{// 同時に上方向の入力がされた
			 // 移動処理
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.75f);
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// 同時に下方向の入力がされた
			 // 移動処理
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.25f);
			}
			else
			{// 何も押されてない
			 // 移動処理
				g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.5f);
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// 上方向の入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y + D3DX_PI) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y + D3DX_PI) * g_Player[nIdxPlayer].fMovement;

			// 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + D3DX_PI;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// 下方向の入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;

			// 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_10, g_PlayerPossible ^ 1) == true || GetJoyPadPress(DIJS_BUTTON_11, g_PlayerPossible ^ 1) == true ||
			GetJoyPadPress(DIJS_BUTTON_12, g_PlayerPossible ^ 1) == true || GetJoyPadPress(DIJS_BUTTON_13, g_PlayerPossible ^ 1) == true)
		{// 左アナログスティックの入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player[nIdxPlayer].move.x -= sinf(pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible ^ 1)) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z -= cosf(pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible ^ 1)) * g_Player[nIdxPlayer].fMovement;

			// 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y - GetJotPadRightStick(g_PlayerPossible ^ 1);
		}
		else if (GetJoyPadPress(DIJS_BUTTON_18, g_PlayerPossible ^ 1) == true || GetJoyPadPress(DIJS_BUTTON_19, g_PlayerPossible ^ 1) == true
			|| GetJoyPadPress(DIJS_BUTTON_20, g_PlayerPossible ^ 1) == true || GetJoyPadPress(DIJS_BUTTON_21, g_PlayerPossible ^ 1) == true)
		{// 十字キー入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y + GetJotPadRadian(g_PlayerPossible ^ 1)) * g_Player[nIdxPlayer].fMovement;
			g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y + GetJotPadRadian(g_PlayerPossible ^ 1)) * g_Player[nIdxPlayer].fMovement;

			// 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + GetJotPadRadian(g_PlayerPossible ^ 1) - D3DX_PI;
		}
	}
	else if (g_Player[nIdxPlayer].bGrab == true)
	{// ツタにつかまっている
		if (GetJoyPadPress(DIJS_BUTTON_10, g_PlayerPossible ^ 1) == TRUE ||
			GetJoyPadPress(DIJS_BUTTON_18, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_W) == true)
		{// 上方向の入力がされた
			g_Player[nIdxPlayer].move.y += 1.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_11, g_PlayerPossible ^ 1) == TRUE ||
			GetJoyPadPress(DIJS_BUTTON_19, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_S) == true)
		{// 下方向の入力がされた
			g_Player[nIdxPlayer].move.y -= 1.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_16, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_A) == true)
		{// 左方向の入力がされた
		 // 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = -D3DX_PI * 0.5f;

			// 座標修正
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x - 7.0f;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_17, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_D) == true)
		{// 右方向の入力がされた
		 // 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = D3DX_PI * 0.5f;

			// 座標修正
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x + 7.0f;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_14, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_K) == true)
		{// 上方向の入力がされた
		 // 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = D3DX_PI;

			// 座標修正
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z - 10.0f;
		}
		else if (GetJoyPadPress(DIJS_BUTTON_15, g_PlayerPossible ^ 1) == TRUE ||
			GetKeyboardPress(DIK_I) == true)
		{// 下方向の入力がされた
		 // 目的の角度変更
			g_Player[nIdxPlayer].DestAngle.y = 0.0f;

			// 座標修正
			Billboard *pBillboard = GetBillboard();
			g_Player[nIdxPlayer].pos.x = pBillboard->pos.x;
			g_Player[nIdxPlayer].pos.z = pBillboard->pos.z + 10.0f;
		}
		if (g_Player[nIdxPlayer].move.y <= 0.1f && g_Player[nIdxPlayer].move.y >= -0.1f)
		{// 移動していなかったら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABNOR)
			{// 移動していない状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABNOR;        // ツタニュートラルの状態に
																		 // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.y > 0.1f)
		{// 上っている
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABUP)
			{// 移動している状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABUP;         // ツタを上っている状態に
																		 // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.y < -0.1f)
		{// 下っていたら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_GRABDOWN)
			{// 移動している状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABDOWN;        // ツタを下りている状態に
																		  // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
	}


	if (GetJoyPadTrigger(DIJS_BUTTON_1, g_PlayerPossible ^ 1) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
	{// キーボードの[ENTER]キーが押された
		if (g_Player[nIdxPlayer].bJump == false)
		{// ジャンプしていなかった
			if (g_Player[nIdxPlayer].bGrab == true)
			{// ツタにつかまっている
				Camera *pCamera;
				pCamera = GetCamera();

				// 移動処理
				g_Player[nIdxPlayer].move.x += sinf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;
				g_Player[nIdxPlayer].move.z += cosf(pCamera->rot.y) * g_Player[nIdxPlayer].fMovement;

				// 目的の角度変更
				g_Player[nIdxPlayer].DestAngle.y = pCamera->rot.y + D3DX_PI;

				g_Player[nIdxPlayer].move.y += g_Player[nIdxPlayer].fJumpPower;          // 上に飛ばす
				g_Player[nIdxPlayer].bJump = true;                  // ジャンプしている判定に
				g_Player[nIdxPlayer].bGrab = false;                 // ツタにつかまっていない状態に
				g_Player[nIdxPlayer].state = PLAYERSTATE_GRABJUMP;  // ツタからジャンプした状態に
				PlaySound(SOUND_LABEL_SE011);				
				// モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else
			{// ツタにつかまっていない
				g_Player[nIdxPlayer].move.y += g_Player[nIdxPlayer].fJumpPower;    // 上に飛ばす
				g_Player[nIdxPlayer].bJump = true;                  // ジャンプしている判定に
				g_Player[nIdxPlayer].state = PLAYERSTATE_JUMP;      // ジャンプ状態に
				PlaySound(SOUND_LABEL_SE008);
				// モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// 目的の角度の修正
	g_Player[nIdxPlayer].DiffAngle.y = g_Player[nIdxPlayer].DestAngle.y - g_Player[nIdxPlayer].rot.y;   // 現在の向きと目的の向きの差分を計算

	if (g_Player[nIdxPlayer].DiffAngle.y > D3DX_PI)
	{// 差分がD3DX_PIを超えた
		g_Player[nIdxPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].DiffAngle.y < -D3DX_PI)
	{// 差分が-D3DX_PIを超えた
		g_Player[nIdxPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	//現在の角度の修正
	g_Player[nIdxPlayer].rot.y += g_Player[nIdxPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nIdxPlayer].rot.y > D3DX_PI)
	{// 現在の向きがD3DX_PIを超えた
		g_Player[nIdxPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].rot.y < -D3DX_PI)
	{// 現在の向きが-D3DX_PIを超えた
		g_Player[nIdxPlayer].rot.y += D3DX_PI * 2.0f;
	}

	// 位置を移動
	g_Player[nIdxPlayer].pos.x += g_Player[nIdxPlayer].move.x;
	g_Player[nIdxPlayer].pos.y += g_Player[nIdxPlayer].move.y;
	g_Player[nIdxPlayer].pos.z += g_Player[nIdxPlayer].move.z;

	if (CollisionWall(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold) == true)
	{
		g_Player[nIdxPlayer].pos.x = g_Player[nIdxPlayer].posold.x;
		g_Player[nIdxPlayer].pos.z = g_Player[nIdxPlayer].posold.z;
	}

	// 目的の角度の修正
	g_Player[nIdxPlayer].DiffAngle.y = g_Player[nIdxPlayer].DestAngle.y - g_Player[nIdxPlayer].rot.y;   // 現在の向きと目的の向きの差分を計算

	if (g_Player[nIdxPlayer].DiffAngle.y > D3DX_PI)
	{// 差分がD3DX_PIを超えた
		g_Player[nIdxPlayer].DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].DiffAngle.y < -D3DX_PI)
	{// 差分が-D3DX_PIを超えた
		g_Player[nIdxPlayer].DiffAngle.y += D3DX_PI * 2.0f;
	}

	//現在の角度の修正
	g_Player[nIdxPlayer].rot.y += g_Player[nIdxPlayer].DiffAngle.y * 0.1f;

	if (g_Player[nIdxPlayer].rot.y > D3DX_PI)
	{// 現在の向きがD3DX_PIを超えた
		g_Player[nIdxPlayer].rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nIdxPlayer].rot.y < -D3DX_PI)
	{// 現在の向きが-D3DX_PIを超えた
		g_Player[nIdxPlayer].rot.y += D3DX_PI * 2.0f;
	}


	if (g_Player[nIdxPlayer].bGrab == true)
	{// ツタにつかまっている
		g_Player[nIdxPlayer].move.y = 0.0f;
	}

	if (g_Player[nIdxPlayer].bJump == false && g_Player[nIdxPlayer].state != PLAYERSTATE_LANDING && g_Player[nIdxPlayer].state != PLAYERSTATE_KICK && g_Player[nIdxPlayer].state != PLAYERSTATE_PANCH
		&& g_Player[nIdxPlayer].state != PLAYERSTATE_DAMAGE && g_Player[nIdxPlayer].bGrab == false)
	{// ジャンプしていないかつ着地状態でないかつアクション状態でないかつダメージ状態でない
		if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
			g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
		{// 移動していなかったら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_NORMAL)
			{// 移動していない状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;   // 通常の状態に
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
			g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
		{// 移動していたら
			if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
			{// 移動している状態じゃなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;     // 移動している状態に
				SwitchMotion(nIdxPlayer);
			}
		}
	}

	// コースの当たり判定
	if (CollisionCourse(&g_Player[nIdxPlayer].pos, &g_Player[nIdxPlayer].posold, &g_Player[nIdxPlayer].move, D3DXVECTOR3(0.0f, 0.0f, 0.0f)) == true)
	{// コースに乗れている
		if (g_Player[nIdxPlayer].bJump == true)
		{// ジャンプしていた
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE)
		{// ダメージ状態だった
			g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;      // 着地状態に
																   // モーション切り替え処理
			SwitchMotion(nIdxPlayer);
		}
		else if (g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
		{// キック状態だった
			if (g_Player[nIdxPlayer].move.x <= 0.5f && g_Player[nIdxPlayer].move.x >= -0.5f &&
				g_Player[nIdxPlayer].move.z <= 0.5f && g_Player[nIdxPlayer].move.z >= -0.5f)
			{// 移動していなかったら
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;  // 着地状態に
																   // モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
			else if (g_Player[nIdxPlayer].move.x > 0.5f || g_Player[nIdxPlayer].move.x < -0.5f ||
				g_Player[nIdxPlayer].move.z > 0.5f || g_Player[nIdxPlayer].move.z < -0.5f)
			{// 移動していたら
				if (g_Player[nIdxPlayer].state != PLAYERSTATE_MOVE)
				{// 移動している状態じゃなかったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_MOVE;  // 移動している状態に
																	// モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
			}
		}
		g_Player[nIdxPlayer].bJump = false;  // ジャンプしていない判定に
	}

	// 慣性を働かせる
	g_Player[nIdxPlayer].move.x += (0.0f - g_Player[nIdxPlayer].move.x) * PLAYER_INERTIA;
	g_Player[nIdxPlayer].move.z += (0.0f - g_Player[nIdxPlayer].move.z) * PLAYER_INERTIA;


}
//=============================================================================
// プレイヤーのモーション
//=============================================================================
void PlayerMotion(int nIdxPlayer)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数分繰り返し
	 // 現在の位置更新
		g_Player[nIdxPlayer].aModel[nCntModel].pos.x += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.x / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;
		g_Player[nIdxPlayer].aModel[nCntModel].pos.y += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.y / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;
		g_Player[nIdxPlayer].aModel[nCntModel].pos.z += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.z / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;

		g_Player[nIdxPlayer].aModel[nCntModel].rot.x += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.x > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.x < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}

		g_Player[nIdxPlayer].aModel[nCntModel].rot.y += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.y > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.y < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}

		g_Player[nIdxPlayer].aModel[nCntModel].rot.z += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z / g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey;

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.z > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.z < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// プレイヤーのモーションブレンド処理
//=============================================================================
void PlayerMotionBlend(int nIdxPlayer)
{
	// ブレンドカウンターを進める
	g_Player[nIdxPlayer].nBlendCounter++;
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数分繰り返し
	 // 現在の位置更新
		g_Player[nIdxPlayer].aModel[nCntModel].pos.x += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.x / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);
		g_Player[nIdxPlayer].aModel[nCntModel].pos.y += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.y / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);
		g_Player[nIdxPlayer].aModel[nCntModel].pos.z += g_Player[nIdxPlayer].aModel[nCntModel].posDiff.z / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);

		g_Player[nIdxPlayer].aModel[nCntModel].rot.x += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.x > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.x < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		g_Player[nIdxPlayer].aModel[nCntModel].rot.y += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.y > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.y < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}

		g_Player[nIdxPlayer].aModel[nCntModel].rot.z += g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z / (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f);

		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.z > D3DX_PI)
		{// 現在の向きがD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].rot.z < -D3DX_PI)
		{// 現在の向きが-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}

	if (g_Player[nIdxPlayer].nBlendCounter >= g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey * 0.3f)
	{// ブレンドカウンターが既定の値に
		g_Player[nIdxPlayer].nBlendCounter = 0;            // ブレンドカウンターを初期化
		if (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].nNumKey >= 2)
		{// キーフレームが2つ以上あったら
			g_Player[nIdxPlayer].mState = MOTIONSTATE_NORMAL;  // モーションの状態を通常の状態に
			g_Player[nIdxPlayer].nKey++;                       // キーフレームを進める
															   // キーフレーム切り替え処理
			SwitchKey(nIdxPlayer);
		}
		else
		{// キーフレームがこれ以上ない
			g_Player[nIdxPlayer].mState = MOTIONSTATE_STOP;    // モーションの状態をモーションしない状態に
		}
	}
}
//=============================================================================
// モーション進行処理
//=============================================================================
void PlayerMotionAdvance(int nIdxPlayer)
{
	g_Player[nIdxPlayer].nMotionCounter++;   // モーションカウンターを進める
	if (g_Player[nIdxPlayer].nMotionCounter >= g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].nPlayBackKey)
	{// 再生フレーム数に達した
		if (g_Player[nIdxPlayer].nKey == g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].nNumKey - 1)
		{// 現在のキーフレーム数がそのモーションのキーフレームの総数を上回った
			if (g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].bLoop == true)
			{// ループする判定だったら
				g_Player[nIdxPlayer].nKey = 0;             // 現在のキーフレームを元に戻す
														   // キーフレーム切り替え処理
				SwitchKey(nIdxPlayer);
			}
			else
			{// ループしない判定だったら
				if (g_Player[nIdxPlayer].state == PLAYERSTATE_DAMAGE || g_Player[nIdxPlayer].state == PLAYERSTATE_LANDING || g_Player[nIdxPlayer].state == PLAYERSTATE_PANCH || g_Player[nIdxPlayer].state == PLAYERSTATE_KICK)
				{// 着地状態かアクション状態だったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;  // 通常状態に

																	  // モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
				else if (g_Player[nIdxPlayer].state == PLAYERSTATE_GRAB)
				{// ツタつかまりモーションだったら
					g_Player[nIdxPlayer].state = PLAYERSTATE_GRABNOR;  // ツタニュートラル状態に

																	   // モーション切り替え処理
					SwitchMotion(nIdxPlayer);
				}
				else
				{// それ以外のモーションならば
					g_Player[nIdxPlayer].mState = MOTIONSTATE_STOP;
				}
			}
		}
		else
		{
			g_Player[nIdxPlayer].nKey++;         // 現在のキーフレームを進める

												 // キーフレーム切り替え処理
			SwitchKey(nIdxPlayer);
		}
		g_Player[nIdxPlayer].nMotionCounter = 0;   // カウンターを戻す
	}
}
//=============================================================================
// キーフレーム切り替え処理
//=============================================================================
void SwitchKey(int nIdxPlayer)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数分繰り返し
	 // 目標の座標設定
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.x = g_Player[nIdxPlayer].aModel[nCntModel].posStd.x - (g_Player[nIdxPlayer].aModel[nCntModel].pos.x - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].x);
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.y = g_Player[nIdxPlayer].aModel[nCntModel].posStd.y - (g_Player[nIdxPlayer].aModel[nCntModel].pos.y - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].y);
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.z = g_Player[nIdxPlayer].aModel[nCntModel].posStd.z - (g_Player[nIdxPlayer].aModel[nCntModel].pos.z - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].z);

		// 角度の差分の修正
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].x - g_Player[nIdxPlayer].aModel[nCntModel].rot.x;   // 現在の向きと目的の向きの差分を計算

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// 角度の差分の修正
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].y - g_Player[nIdxPlayer].aModel[nCntModel].rot.y;   // 現在の向きと目的の向きの差分を計算

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// 角度の差分の修正
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].z - g_Player[nIdxPlayer].aModel[nCntModel].rot.z;   // 現在の向きと目的の向きの差分を計算

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// モーション切り替え処理
//=============================================================================
void SwitchMotion(int nIdxPlayer)
{

	g_Player[nIdxPlayer].nMotionCounter = 0;          // モーションカウンターをリセット
	g_Player[nIdxPlayer].nKey = 0;                    // 現在のキーフレームをリセット
	g_Player[nIdxPlayer].mState = MOTIONSTATE_SWITCH; // モーション切り替え状態に

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// モデルのパーツ数分繰り返し
	 // 目標の座標設定
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.x = g_Player[nIdxPlayer].aModel[nCntModel].posStd.x - (g_Player[nIdxPlayer].aModel[nCntModel].pos.x - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].x);
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.y = g_Player[nIdxPlayer].aModel[nCntModel].posStd.y - (g_Player[nIdxPlayer].aModel[nCntModel].pos.y - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].y);
		g_Player[nIdxPlayer].aModel[nCntModel].posDiff.z = g_Player[nIdxPlayer].aModel[nCntModel].posStd.z - (g_Player[nIdxPlayer].aModel[nCntModel].pos.z - g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].posAdd[nCntModel].z);

		// 角度の差分の修正
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].x - g_Player[nIdxPlayer].aModel[nCntModel].rot.x;   // 現在の向きと目的の向きの差分を計算

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// 角度の差分の修正
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].y - g_Player[nIdxPlayer].aModel[nCntModel].rot.y;   // 現在の向きと目的の向きの差分を計算

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// 角度の差分の修正
		g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z = g_Player[nIdxPlayer].aMotion[g_Player[nIdxPlayer].state].Key[g_Player[nIdxPlayer].nKey].DestAngle[nCntModel].z - g_Player[nIdxPlayer].aModel[nCntModel].rot.z;   // 現在の向きと目的の向きの差分を計算

		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// 差分がD3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// 差分が-D3DX_PIを超えた
			g_Player[nIdxPlayer].aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player[g_PlayerPossible];
}

//=============================================================================
// プレイヤー同士の当たり判定
//=============================================================================
void CollisionPlayer(int nIdxParts, int nAttackNum, int nDiffenceNum)
{
	if (g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._42 - 20.0f < g_Player[nDiffenceNum].pos.y + 50.0f
		&& g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._42 + 20.0f > g_Player[nDiffenceNum].pos.y)
	{// 攻撃した側が防衛側のY座標の中にいる
		if (g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._43 - 15.0f < g_Player[nDiffenceNum].pos.z + 15.0f
			&& g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._43 + 15.0f >  g_Player[nDiffenceNum].pos.z - 15.0f)
		{// 攻撃した側が防衛側のZ座標の中にいる
			if (g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._41 - 17.0f < g_Player[nDiffenceNum].pos.x + 17.0f
				&& g_Player[nAttackNum].aModel[nIdxParts].mtxWorld._41 + 17.0f >  g_Player[nDiffenceNum].pos.x - 17.0f)
			{// 攻撃した側が防衛側のX座標の中にいる
				if (g_Player[nDiffenceNum].state != PLAYERSTATE_DAMAGE)
				{// 防衛側がダメージ状態でない
					HitPlayer(nAttackNum, nDiffenceNum);
				}
			}
		}
	}
}
//=============================================================================
// プレイヤーのダメージ処理
//=============================================================================
void HitPlayer(int nAttackNum, int nDiffenceNum)
{
	PlaySound(SOUND_LABEL_SE006);
	// ぶっ飛び処理
	g_Player[nDiffenceNum].move.x -= sinf(g_Player[nAttackNum].rot.y) * 15.0f;
	g_Player[nDiffenceNum].move.y += 10.0f;
	g_Player[nDiffenceNum].move.z -= cosf(g_Player[nAttackNum].rot.y) * 15.0f;

	g_Player[nDiffenceNum].DestAngle.y = g_Player[nAttackNum].rot.y + D3DX_PI;

	if (g_Player[nDiffenceNum].DestAngle.y > D3DX_PI)
	{// 現在の向きがD3DX_PIを超えた
		g_Player[nDiffenceNum].DestAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player[nDiffenceNum].DestAngle.y < -D3DX_PI)
	{// 現在の向きが-D3DX_PIを超えた
		g_Player[nDiffenceNum].DestAngle.y += D3DX_PI * 2.0f;
	}

	for (int nCntParticle = 0; nCntParticle < 50; nCntParticle++)
	{// 発生させるパーティクルの数だけ繰り返し
		SetParticle(D3DXVECTOR3(g_Player[nDiffenceNum].aModel[0].mtxWorld._41, g_Player[nDiffenceNum].aModel[0].mtxWorld._42, g_Player[nDiffenceNum].aModel[0].mtxWorld._43), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 1.5f), 12.0f, 100);
	}

	g_Player[nDiffenceNum].state = PLAYERSTATE_DAMAGE;   // ダメージ状態に
														 // モーション切り替え処理
	SwitchMotion(nDiffenceNum);
}

//=============================================================================
// プレイヤーの移動フラグ管理
//=============================================================================
void SetPlayerMoveFlag(bool bFlag)
{
	g_bPlayerMoveFlag = bFlag;
}

//=============================================================================
// プレイヤーの交代処理
//=============================================================================
void PlayerChange(int nIdxPlayer)
{
	g_Player[nIdxPlayer].move.y = 0.0f;               // 重力を無視
	g_Player[nIdxPlayer].move.x = 0.0f;               // 移動を無視
	g_Player[nIdxPlayer].move.z = 0.0f;               // 移動を無視
	g_Player[nIdxPlayer].state = PLAYERSTATE_NORMAL;  // 通常状態にする
	g_Player[nIdxPlayer].bJump = false;               // ジャンプしていない状態に
	g_Player[nIdxPlayer].bGrab = false;               // ツタにつかまっていない状態に

	if (g_Player[nIdxPlayer].pMasu != NULL)
	{
		switch (g_Player[nIdxPlayer].pMasu->masuType)
		{
			// 通常マス
		case MASUTYPE_NORMAL:
			g_Player[nIdxPlayer].fJumpPower = JUMP_NORMAL;
			g_Player[nIdxPlayer].fMovement = MOVE_NORMAL;
			break;
			// ジャンプUPマス
		case MASUTYPE_JUMP_UP:
			g_Player[nIdxPlayer].fJumpPower = JUMP_UP;
			g_Player[nIdxPlayer].fMovement = MOVE_NORMAL;
			break;
			// ジャンプDOWNマス
		case MASUTYPE_JUMP_DOWN:
			g_Player[nIdxPlayer].fJumpPower = JUMP_DOWN;
			g_Player[nIdxPlayer].fMovement = MOVE_NORMAL;
			break;
			// 移動UPマス
		case MASUTYPE_SPEED_UP:
			g_Player[nIdxPlayer].fJumpPower = JUMP_NORMAL;
			g_Player[nIdxPlayer].fMovement = MOVE_UP;
			break;

			// 移動UPマス
		case MASUTYPE_SPEED_DOWN:
			g_Player[nIdxPlayer].fJumpPower = JUMP_NORMAL;
			g_Player[nIdxPlayer].fMovement = MOVE_DOWN;
			break;
		}
	}

	g_Player[nIdxPlayer].bDisp = false;  // 描画しない状態にする

	g_Player[nIdxPlayer].ShadowCol.a = 0.0f;  // 影を消す

	//if (g_Player[nIdxPlayer ^ 1].pMasu != NULL)
	//{
	//	g_Player[nIdxPlayer ^ 1].pos = g_Player[nIdxPlayer ^ 1].pMasu->pos;
	//}
	//else
	//{
	//	g_Player[nIdxPlayer ^ 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//}
	// 影の色更新
	SetColShadow(g_Player[nIdxPlayer].nIdxShadow, g_Player[nIdxPlayer].ShadowCol);

	for (int nCntParticle = 0; nCntParticle < 15; nCntParticle++)
	{// 発生させるパーティクルの数だけ繰り返し
		SetParticle(g_Player[nIdxPlayer].pos, D3DXCOLOR(rand() % 10 / 10.0f, rand() % 10 / 10.0f, rand() % 10 / 10.0f, 1.0f), D3DXVECTOR3(sinf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 4.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 4.5f, cosf(rand() % 300 * D3DX_PI / 100 - 1.0f) * 4.5f), 30.0f, 100);
	}


	//次操作するキャラの位置を戻す
	g_Player[nIdxPlayer ^ 1].pos = g_Player[nIdxPlayer ^ 1].pMasu->pos;

}
//=============================================================================
// プレイヤー番号取得処理
//=============================================================================
int GetIdxPlayer(void)
{
	return g_PlayerPossible;
}

//=============================================================================
// プレイヤーと動くものの当たり判定
//=============================================================================
void CollisionMoveOb(D3DXVECTOR3 Pos, D3DXVECTOR3 PosOld, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, int nIdxPlayer)
{
	if (g_Player[nIdxPlayer].pos.y < Pos.y + vtxMax.y && g_Player[nIdxPlayer].pos.y + g_Player[nIdxPlayer].radius.y > Pos.y + vtxMax.y
		|| g_Player[nIdxPlayer].pos.y < Pos.y + vtxMin.y && g_Player[nIdxPlayer].pos.y + g_Player[nIdxPlayer].radius.y > Pos.y + vtxMin.y
		|| g_Player[nIdxPlayer].pos.y > Pos.y + vtxMin.y && g_Player[nIdxPlayer].pos.y + g_Player[nIdxPlayer].radius.y < Pos.y + vtxMax.y)
	{// 動くもののY座標中にプレイヤーがいる
		if (g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z > PosOld.z + vtxMin.z && g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z < PosOld.z + vtxMax.z)
		{// 動くもののZ座標中にプレイヤーがいる
			if (PosOld.x + vtxMin.x >= g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x - 5.0f && Pos.x + vtxMin.x < g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x
				|| g_Player[nIdxPlayer].posold.x + g_Player[nIdxPlayer].radius.x <= PosOld.x + vtxMin.x - 5.0f && g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x > Pos.x + vtxMin.x)
			{// 動くものの左側からプレイヤーが埋まった
				g_Player[nIdxPlayer].pos.x = Pos.x + vtxMin.x - g_Player[nIdxPlayer].radius.x;
			}
			else if (PosOld.x + vtxMax.x <= g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x + 5.0f && Pos.x + vtxMax.x > g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x
				|| g_Player[nIdxPlayer].posold.x - g_Player[nIdxPlayer].radius.x + 5.0f >= PosOld.x + vtxMax.x && g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x < Pos.x + vtxMax.x)
			{// 動くものの右側からプレイヤーが埋まった
				g_Player[nIdxPlayer].pos.x = Pos.x + vtxMax.x + g_Player[nIdxPlayer].radius.x;
			}
		}
		if (g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x >= PosOld.x + vtxMin.x && g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x <= PosOld.x + vtxMax.x)
		{// 動くもののX座標中にプレイヤーがいる
			if (PosOld.z + vtxMin.z >= g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z - 5.0f && Pos.z + vtxMin.z < g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z
				|| PosOld.z + vtxMin.z >= g_Player[nIdxPlayer].posold.z + g_Player[nIdxPlayer].radius.z - 5.0f && Pos.z + vtxMin.z < g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z)
			{// 動くものの前側からプレイヤーが埋まった
				g_Player[nIdxPlayer].pos.z = Pos.z + vtxMin.z - g_Player[nIdxPlayer].radius.z - 1.0f;
			}
			else if (PosOld.z + vtxMax.z <= g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z + 5.0f && Pos.z + vtxMax.z > g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z
				|| PosOld.z + vtxMax.z <= g_Player[nIdxPlayer].posold.z - g_Player[nIdxPlayer].radius.z + 5.0f && Pos.z + vtxMax.z > g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z)
			{// 動くものの後ろ側からプレイヤーが埋まった
				g_Player[nIdxPlayer].pos.z = Pos.z + vtxMax.z + g_Player[nIdxPlayer].radius.z + 1.0f;
			}
		}
	}
	else
	{// Y座標の中にいない
		if (g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x <= Pos.x + vtxMax.x && g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x >= Pos.x + vtxMin.x
			&& g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z <= Pos.z + vtxMax.z && g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z >= Pos.z + vtxMin.z
			&& g_Player[nIdxPlayer].pos.x + g_Player[nIdxPlayer].radius.x <= PosOld.x + vtxMax.x && g_Player[nIdxPlayer].pos.x - g_Player[nIdxPlayer].radius.x >= PosOld.x + vtxMin.x
			&& g_Player[nIdxPlayer].pos.z + g_Player[nIdxPlayer].radius.z <= PosOld.z + vtxMax.z && g_Player[nIdxPlayer].pos.z - g_Player[nIdxPlayer].radius.z >= PosOld.z + vtxMin.z)
		{// 動くものの中にいる
			if (g_Player[nIdxPlayer].posold.y >= Pos.y + vtxMax.y && g_Player[nIdxPlayer].posold.y <= Pos.y + vtxMax.y
				|| g_Player[nIdxPlayer].pos.y >= Pos.y + vtxMax.y && g_Player[nIdxPlayer].pos.y <= Pos.y + vtxMax.y
				|| g_Player[nIdxPlayer].posold.y >= PosOld.y + vtxMax.y && g_Player[nIdxPlayer].posold.y <= PosOld.y + vtxMax.y
				|| g_Player[nIdxPlayer].pos.y >= PosOld.y + vtxMax.y && g_Player[nIdxPlayer].pos.y <= PosOld.y + vtxMax.y)
			{// 着地した
				g_Player[nIdxPlayer].pos.y = Pos.y + vtxMax.y;
				g_Player[nIdxPlayer].state = PLAYERSTATE_LANDING;
				// モーション切り替え処理
				SwitchMotion(nIdxPlayer);
			}
		}
	}
}
#pragma once
//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

#include "model.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "shadow.h"
#include "wall.h"
#include "bullet.h"
#include "explosion.h"
#include "meshField.h"
#include "meshWall.h"
#include "meshCylinder.h"
#include "effect.h"
#include "player.h"
#include "npc.h"
#include "particle.h"
#include "arrow.h"
#include "Timer.h"
#include "piller.h"
#include "roof.h"
#include "object.h"
#include "miniMap.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define GRAVITY (0.7f)					//�d��

//=============================================================================
//	�Q�[���̏��
//=============================================================================
typedef enum
{
	GAMESTATE_NONE = 0,	//�������ĂȂ����
	GAMESTATE_NORMAL,	//�ʏ���
	GAMESTATE_END,		//�I�����
	GAMESTATE_MAX
}GAMESTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

void PauseModeChange(void);
#endif

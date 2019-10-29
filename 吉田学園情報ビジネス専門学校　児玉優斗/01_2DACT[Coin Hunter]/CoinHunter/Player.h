#pragma once
//*****************************************************************************
//
//	DirectX �v���C���[�̏��� [player.h]
//	Author : Kodama Yuto
//
//*****************************************************************************
#ifndef _PLAYER_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _PLAYER_H_

#include "block.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define PLAYER_TEXTURE "data/TEXTURE/player000.png"	//�v���C���[�̓\��e�N�X�`���̖��O

#define PLAYER_SIZE_X (20)						//�v���C���[�̃T�C�Y.X
#define PLAYER_SIZE_Y (20)						//�v���C���[�̃T�C�Y.Y

#define PLAYER_POS_X (150)						//�v���C���[�̍��W.X
#define PLAYER_POS_Y (650)						//�v���C���[�̍��W.Y

#define PLAYER_MOVE_SPEED (2.0f)				//�v���C���[��X�̈ړ����x(�f�t�H���g)
#define PLAYER_JUMPMOVE_SPEED (1.5f)			//�v���C���[��X�̈ړ����x(�W�����v��)

#define PLAYER_DASH_SPEED	  (1.2f)			//�v���C���[�̃_�b�V�����Ɋ|����W��

#define PLAYER_MOVE_COEFFICIENT (0.3f)			//�v���C���[�̌����W��
#define PLAYER_JUMP_MOVE (14.5f)				//�v���C���[�̃W�����v��(�f�t�H���g)			

#define PLAYER_COLOR_R (1.0f)				//�v���C���[�̐F.r
#define PLAYER_COLOR_G (1.0f)				//�v���C���[�̐F.g
#define PLAYER_COLOR_B (1.0f)				//�v���C���[�̐F.b
#define PLAYER_COLOR_A (1.0f)				//�v���C���[�̐F.a(��)

#define PLAYER_ANIM_INTERVAL (8)		//�A�j���[�V�����̊Ԋu

//=============================================================================
//	�\���̂̒�`
//=============================================================================
typedef enum
{//�v���C���[�̏�ԗ�
	PLAYERSTATE_NORMAL = 0,	//�ʏ펞
	PLAYERSTATE_MAX,
}PLAYERSTATE;

typedef struct
{//�v���C���[�̍\����
	PLAYERSTATE state;		//���
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 oldPos;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;
	int nTexAnim;			//�e�N�X�`���[�̃A�j���[�V����
	int nCntAnim;			//�A�j���[�V�����p�̃J�E���^�[
	float fJump;			//�W�����v��
	float fGravity;			//�d��
	bool bDirection;		//����				false == �E
	bool bUse;				//�����Ă��邩		false == ��
	bool bJump;				//���ł��邩		false == ���ł��Ȃ�
	bool bLand;				//�ڒn���Ă��邩	false == �ڒn���ĂȂ�
}Player;

//-----------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void CollisionItem(void);

Player *GetPlayer(void);

#endif // !_PLAYER_H_


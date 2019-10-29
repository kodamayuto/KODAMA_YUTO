//*****************************************************************************
//
//DirectX �e�̔��ˏ���  [main.h]
//Author : Kodama Yuto
//
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//�C���N���[�h�t�@�C��
#include <windows.h>
#include "d3dx9.h"		//�`�揈���ɕK�v

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"	//�T�E���h�̏����ɕK�v

//
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "effect.h"
#include "sound.h"
#include "playermode.h"
#include "boss.h"
#include "boss_option.h"

//-----------------------------------------------------------------------------
//						���C�u�����̃����N
//-----------------------------------------------------------------------------
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9.h]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�������̎擾�ɕK�v
#pragma comment(lib,"dinput8.lib")

//-----------------------------------------------------------------------------
//						 �}�N����`
//-----------------------------------------------------------------------------
#define SCREEN_WIDTH	(1280)										   //�E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)										   //�E�C���h�E�̍���

#define FVF_VERTEX_2D   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���_�t�H�[�}�b�g

#define TEX_PATTERN         (8)

//-----------------------------------------------------------------------------
//						 �\���̂̒�`
//-----------------------------------------------------------------------------
typedef enum
{
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX,
}MODE;

typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//1,0f�ŌŒ�
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
}VERTEX_2D;

//----------------------------------------------------------------------------
//						�v���g�^�C�v�錾
//----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif
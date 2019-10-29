//=============================================================================
//
// �u���b�N�̏��� [block.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
//=============================================================================
//	�}�N����`
//=============================================================================
// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_BLOCK		"data/TEXTURE/block000.jpg"
#define TEXTURE_BLOCK_1		"data/TEXTURE/block001.jpg"
#define TEXTURE_BLOCK_2		"data/TEXTURE/block002.jpg"
#define TEXTURE_BLOCK_3		"data/TEXTURE/block003.jpg"
#define TEXTURE_BLOCK_4		"data/TEXTURE/Tile001.png"
#define TEXTURE_BLOCK_5		"data/TEXTURE/block005.jpg"
#define TEXTURE_BLOCK_6		"data/TEXTURE/block006.jpg"
#define TEXTURE_BLOCK_7		"data/TEXTURE/rESET.png"

#define	MAX_BLOCK			(512)							// �u���b�N�̍ő吔

#define MAX_BLOCK_TEXTURE	(8)

#define BLOCK_INV_SPEED (0.015f)	//�u���b�N�̏����鑬�x

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	BLOCKTYPE_NORMAL = 0, //�ʏ�
	BLOCKTYPE_MOVE,		  //����
	BLOCKTYPE_FALL,		  //���Ɨ�����
	BLOCKTYPE_INV,		  //���Ə�����
	BLOCKTYPE_ATTACK_MOVE,//�������Ɠ���
	BLOCKTYPE_WARP_IN,	  //����OUT�܂Ń��[�v����
	BLOCKTYPE_WARP_OUT,
	BLOCKTYPE_RESET,	  //AttckMove�̈ړ��ʂ����Z�b�g����
	BLOCKTYPE_MAX
}BLOCKTYPE;

typedef enum
{
	BLOCKCONTACT_NONE = 0,//�ڐG���Ă��Ȃ�
	BLOCKCONTACT_ON,	  //��ɐڐG���Ă���
	BLOCKCONTACT_UNDER,	  //���ɐڐG���Ă���
	BLOCKCONTACT_LEFT,	  //���ɐڐG���Ă���
	BLOCKCONTACT_RIGHT,	  //���ɐڐG���Ă���
	BLOCKCONTACT_MAX
}BLOCKCONTACT;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 OldPos;		// ���̈ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �J���[
	float fWidth;			// ��
	float fHeight;			// ����
	bool bUse;				// �g�p���Ă��邩�ǂ���
	bool bFlag;
	int nWarpCount;
	BLOCKTYPE type;
	BLOCKCONTACT ContBlock;
} Block;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	float fWidth;
	float fHeight;
	BLOCKTYPE type;
}BlockInfo;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);

void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth,float fHeight, BLOCKTYPE type);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldPos, D3DXVECTOR3 *pMove);
int ReturnBlockIndex(int nIndex);
void ResetAttackMoveBlock(void);
#endif

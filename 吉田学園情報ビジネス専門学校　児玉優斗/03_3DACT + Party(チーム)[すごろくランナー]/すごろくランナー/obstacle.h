//=============================================================================
//
// ��Q���̏��� [obstacle.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	OBSTACLE_TYPE_LOG_S = 0, // �ۑ�(S)
	OBSTACLE_TYPE_LOG_M,	 // �ۑ�(M)
	OBSTACLE_TYPE_LOG_L,     // �ۑ�(L)
	OBSTACLE_TYPE_MOVE,
	OBSTACLE_TYPE_HALFMOVE,
	OBSTACLE_TYPE_UPDOWNLOG,
	OBSTACLE_TYPE_BASE,
	OBSTACLE_TYPE_LOGMOVE,
	OBSTACLE_TYPE_LOGFAT,
	OBSTACLE_TYPE_ROLL_LEFT,
	OBSTACLE_TYPE_ROLL_RIGHT,
	OBSTACLE_TYPE_STAIRS_S,
	OBSTACLE_TYPE_STAIRS_M,
	OBSTACLE_TYPE_STAIRS_L,
	OBSTACLE_TYPE_HALFSTAIRS_S,
	OBSTACLE_TYPE_HALFSTAIRS_M,
	OBSTACLE_TYPE_HALFSTAIRS_L,
	OBSTACLE_TYPE_MAX
}OBSTACLE_TYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;    // ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;        // ���W
	D3DXVECTOR3 rot;        // ����
}Vertex_Obstacle;


typedef struct
{
	D3DXVECTOR3 pos;	              // ���݂̈ʒu
	D3DXVECTOR3 posold;	              // �O��̈ʒu
	D3DXVECTOR3 rot;	              // ����
	D3DXVECTOR3 move;	              // �ړ���
	int			nInxShadow;           // �e
	OBSTACLE_TYPE	nType;            // ���
	D3DXMATRIX	mtxWorld;	          // ���[���h�}�g���b�N�X
	bool		bUse;                 // �g�p���Ă��邩�ǂ���
	D3DXVECTOR3	vtxMinObstacle, vtxMaxObstacle;	// ���f���̍ŏ��l�A�ő�l
	D3DXMATRIX  mtxWorldMaxCol;       // �����蔻�����郏�[���h���W�p(�ő�l)
	D3DXMATRIX  mtxWorldMinCol;       // �����蔻�����郏�[���h���W�p(�ŏ��l)
	Vertex_Obstacle Vertex[4];        // ���_�̃��[���h�}�g���b�N�X
}OBSTACLE;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;        // ����
	D3DXVECTOR3 move;		// �ړ���
	OBSTACLE_TYPE nType;	// ���
}OBSTACLE_INFO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitObstacle(void);
void UninitObstacle(void);
void UpdateObstacle(void);
void DrawObstacle(void);
OBSTACLE *GetObstacle(void);
void SetObstacle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, OBSTACLE_TYPE nType);
bool CollisionObstacle(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius);

#endif

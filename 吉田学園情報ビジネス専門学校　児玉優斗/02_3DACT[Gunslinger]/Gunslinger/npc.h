//=============================================================================
//
// ���f������ [npc.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _NPC_H_
#define _NPC_H_

#include "main.h"

//
//
//
#define NPC_FILENAME0 "data/MODEL/3d_001_body4.x"
#define NPC_FILENAME1 "data/MODEL/3d_001_head4.x"
#define NPC_FILENAME2 "data/MODEL/3d_001_armR1.x"
#define NPC_FILENAME3 "data/MODEL/3d_001_handR.x"
#define NPC_FILENAME4 "data/MODEL/3d_001_armL1.x"
#define NPC_FILENAME5 "data/MODEL/3d_001_handL.x"
#define NPC_FILENAME6 "data/MODEL/3d_001_legR2.x"
#define NPC_FILENAME7 "data/MODEL/3d_001_footR1.x"
#define NPC_FILENAME8 "data/MODEL/3d_001_legL2.x"
#define NPC_FILENAME9 "data/MODEL/3d_001_footL1.x"
#define NPC_FILENAME10 "data/MODEL/3d_001_Weppon_sword2.x"

#define PARTS_NUM_NPC (11)

#define NPC_MOVE_SPEED (1.95f)
#define NPC_ROTMOVE_COEFFICIENT (0.11f)
#define MAX_NUM_NPC (4)
#define CHASE_RANGE (100.0f)			//�ǐՔ͈�

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	AI_RANDOM = 0,//�����_���ړ�
	AI_CHASE,	  //�ǐ�
	AI_TERRITORY, //�̈���ǐ�
	AI_ESCAPE,	  //����
	AI_PATOROL,   //����
	AI_MAX
}NPC_AI;//NPC�̍s���A���S���Y��

typedef enum
{
	NPCSTATE_NONE = 0,
	NPCSTATE_MOVE,
	NPCSTATE_DAMAGE,
	NPCSTATE_MAX
}NPC_STATE;
typedef struct
{
	D3DXVECTOR3 motion0[2];
	int nKeyFrame;
}NPCMOTION;

typedef struct
{
	LPD3DXMESH pMesh = NULL;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL;//�}�e���A�����ւ̃|�C���^
	DWORD		 nNumMat = 0;	//�}�e���A�����̐�
	D3DXMATRIX  mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nIdxModelParent;		//�e���f���̃C���f�b�N�X
	LPCSTR FireName;
	NPCMOTION motion;
	int nMotionCount = 0;			//���[�V�����̎��Ԍv���p
	int nMotionNum = 0;				//���[�V�����̊Ǘ��p

}NPCMODEL;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMove;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 difAngle;
	D3DXMATRIX  mtxWorld;
	int nIdxShadow;
	DWORD nNumMatNPC = 0;		//�}�e���A�����̐�
	bool bUse;
	D3DXVECTOR3 VtxMin;	//���f���̓����蔻��̍ŏ�
	D3DXVECTOR3 VtxMax;	//���f���̓����蔻��̍ő�
	int nMoveCount;		//NPC�̈ړ����ԊǗ��p
	NPCMODEL aModel[PARTS_NUM_NPC];
	NPC_AI npcAI;		//NPC�̍s���A���S���Y��
	NPC_STATE state;	//NPC�̏��
	int nCntMove;		//�_���[�W��̒�~����
	int nCntBullet = 0;
	D3DLIGHT9 light;		//���C�g�̏��

}NPC;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitNpc(void);
void UninitNpc(void);
void UpdateNpc(void);
void DrawNpc(void);
bool CollisionNpc(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax);

int CollisionBullet(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax,
	int *pDeleteIdxNpc);

void SetNpcVertex(int nCntNpc);
void DeleteNpc(int nIdxNpc);

bool CountUseNpc(void);

NPC *GetNPC(void);

#endif

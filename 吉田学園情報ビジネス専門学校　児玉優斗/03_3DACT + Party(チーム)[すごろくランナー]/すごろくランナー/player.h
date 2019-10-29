//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "masu.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define  MAX_PLAYER  (2)        // �v���C���[�̑��l��
#define  MAX_MODEL   (10)       // �v���C���[���f���̑���
#define  MAX_MOTION  (20)       // ���[�V�����̑���

//*****************************************************************************
// �v���C���[�̍\����
//*****************************************************************************
typedef enum
{
	PLAYERSTATUS_MOVEMENT = 0,  // �ړ���
	PLAYERSTATUS_JUMPPOWER,     // �W�����v��
	PLAYERSTATUS_MAX
}PLAYERSTATUS;

typedef enum
{
	PARTSSET_INDEX = 0,   // �p�[�c�ԍ�
	PARTSSET_PARENT,      // �e���f���̔ԍ�
	PARTSSET_OFFSET_POS,  // �e���f������̋���
	PARTSSET_OFFSET_ROT,  // �e���f������̌���
	PARTSSET_MAX
}PARTSSET;

typedef enum
{
	PLAYERSTATE_NORMAL = 0, // �ʏ�̏��
	PLAYERSTATE_MOVE,       // �ړ����Ă�����
	PLAYERSTATE_PANCH,      // �p���`���Ă�����
	PLAYERSTATE_KICK,       // �L�b�N���Ă�����
	PLAYERSTATE_JUMP,       // �W�����v���Ă�����
	PLAYERSTATE_LANDING,    // ���n���Ă�����
	PLAYERSTATE_GRAB,       // �c�^�ɂ��܂�ɍs�����
	PLAYERSTATE_GRABNOR,    // �c�^�ɂ��܂������
	PLAYERSTATE_GRABUP,     // �c�^�ɂ��܂��ďオ�������
	PLAYERSTATE_GRABDOWN,   // �c�^�ɂ��܂��ĉ����������
	PLAYERSTATE_GRABJUMP,   // �c�^����W�����v�������
	PLAYERSTATE_DAMAGE,     // �_���[�W���󂯂����
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef enum
{
	MOTIONSTATE_NORMAL = 0,  // �ʏ�̏��
	MOTIONSTATE_STOP,        // ���[�V�������I��������
	MOTIONSTATE_SWITCH,      // ���[�V�����؂�ւ����
	MOTIONSTATE_MAX
}MOTIONSTATE;

typedef struct
{
	LPD3DXMESH   pMesh = NULL;            // ���b�V�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9* pTexture = NULL;  // �e�N�X�`���̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL;         // �}�e���A�����ւ̃|�C���^
	DWORD        nNumMat = NULL;          // �}�e���A�����̐�
	D3DXMATRIX   mtxWorld;                // ���[���h�}�g���b�N�X
	D3DXVECTOR3  vtxMin, vtxMax;          // �v���C���[�̍ŏ��l, �ő�l
	D3DXVECTOR3  pos;                     // ���݂̈ʒu
	D3DXVECTOR3  posStd;                  // ��̈ʒu
	D3DXVECTOR3  posDiff;                 // �����̈ʒu
	D3DXVECTOR3  DiffAngle;               // �����̌���
	D3DXVECTOR3  rot;                     // ���݂̌���
	int nIdxModelParent;                  // �e���f���̃C���f�b�N�X
}Model_Player;

typedef struct
{
	D3DXVECTOR3  posAdd[MAX_MODEL];       // ��̈ʒu�ɉ�����l
	D3DXVECTOR3  DestAngle[MAX_MODEL];    // �ړI�̌���
	int nPlayBackKey;                     // �Đ��t���[����
}KeyFrame_Player;

typedef struct
{
	KeyFrame_Player Key[MAX_MODEL];      // �L�[�t���[���̏��
	bool bLoop;                          // ���[�v���邩���Ȃ���
	int nNumKey;                         // �L�[�t���[����
}Motion_Player;

typedef struct
{
	D3DXVECTOR3  pos;                       // ���݂̈ʒu
	D3DXVECTOR3  posold;                    // �O��̈ʒu
	D3DXVECTOR3  move;                      // �ړ���
	D3DXVECTOR3  rot;                       // ���݂̌���
	D3DXVECTOR3 DiffAngle;                  // ����
	D3DXVECTOR3 DestAngle;                  // �ړI�̌���
	D3DXVECTOR3 radius;						// �����蔻��Ɏg���͈�
	D3DXMATRIX   mtxWorld;                  // ���[���h�}�g���b�N�X
	PLAYERSTATE state;                      // ���
	float fMovement;                        // �ړ���
	float fJumpPower;                       // �W�����v��
	int nIdxShadow;                         // �g�p���Ă���e�̔ԍ�
	D3DXCOLOR ShadowCol;                    // �e�̐F
	float ShadowWidth;                      // �e�̕�
	float ShadowDepth;                      // �e�̉��s
	bool bJump;                             // �W�����v�ł��邩�ł��Ȃ���
	bool bGrab;                             // �c�^�ɂ��܂��Ă��邩�ǂ���
	Model_Player aModel[MAX_MODEL];         // ���f���̑��� 
	Motion_Player aMotion[PLAYERSTATE_MAX]; // ���[�V�����̏��
	MOTIONSTATE mState;                     // ���[�V�����̏��
	int nKey;                               // ���݂̃L�[�t���[��
	int nMotionCounter;                     // ���[�V�����J�E���^�[
	int nBlendCounter;                      // ���[�V�����u�����h�J�E���^�[
	MASU *pMasu;							// �u���b�N�ւ̃|�C���^
	bool bDisp;								// �`�悷�邩���Ȃ���
}Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

void CollisionPlayer(int nIdxParts, int nAttackNum, int nDiffenceNum);
void HitPlayer(int nAttackNum, int nDiffenceNum);

void SetPlayerMoveFlag(bool bFlag);
void PlayerChange(int nIdxPlayer);
int GetIdxPlayer(void);

void CollisionMoveOb(D3DXVECTOR3 Pos, D3DXVECTOR3 PosOld, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, int nIdxPlayer);

#endif
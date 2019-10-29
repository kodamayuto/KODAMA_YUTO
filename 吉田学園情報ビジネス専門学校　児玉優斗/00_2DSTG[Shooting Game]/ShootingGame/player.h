//*****************************************************************************
//
//DirectX �v���C���[�̏��� [player.h]
//Author : Kodama Yuto
//
//*****************************************************************************
#ifndef _PLAYER_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _PLAYER_H_

//=============================================================================
//								�}�N����`
//=============================================================================
#define PLAYER_TEXTURE "data/TEXTURE/Draw004Fryer1.png"	//�v���C���[�̓\��e�N�X�`���̖��O

#define SENT_POS_X (SCREEN_WIDTH / 2)					//�v���C���[�̒��S���W.x
#define SENT_POS_Y (500)					//�v���C���[�̒��S���W.y

#define PLAYER_SIZE (25.0f)					//�v���C���[�̑傫��

#define PLAYER_MOVE_SPEED (5.0f)			//�v���C���[�̈ړ����x
#define PLAYER_MOVE_COEFFICIENT (0.3f)		//�v���C���[�̌����W��

#define PLAYER_COLOR_RED (255)				//�v���C���[�̐F.r
#define PLAYER_COLOR_GREEN (255)			//�v���C���[�̐F.g
#define PLAYER_COLOR_BLUE (255)				//�v���C���[�̐F.b
#define PLAYER_COLOR_ALPHA (255)			//�v���C���[�̐F.a

#define PLAYER_LIFE (8)						//�v���C���[�̗̑�

//=============================================================================
//	�\���̂̒�`
//=============================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	//���G
	PLAYERSTATE_NORMAL,		//�ʏ�
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_DEATH,		//��
	PLAYERSTATE_END,		//�I��
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	PLAYERSTATE state;		//���
	int nCountState;		//��Ԃ̃J�E���^
	int nBulletPattern;		//�e�̃p�^�[��
	int nCntBullet;			//�e�̔��˃J�E���g
	int nLife;				//�̗�
	bool bDisp;				//�g�p�̗L��
	bool bMove;				//�ᑬ�ړ�
}Player;

//-----------------------------------------------------------------------------
//							�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void HitPlayer(int nDamage);

#endif // !_PLAYER_H_


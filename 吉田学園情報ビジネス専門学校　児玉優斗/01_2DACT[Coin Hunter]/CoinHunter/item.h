//=============================================================================
//
// �A�C�e������ [item.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM		(256)						//�A�C�e���̍ő吔

#define ITEM_TEXTURE "data/TEXTURE/coin000.png"		//�A�C�e���̃e�N�X�`��
#define NUM_TEXTURE (1)
#define ITEM_SIZE (20)

#define TEX_PATTERN (4)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	ITEM_SCOREUP_COIN = 0,//�R�C��
	ITEM_GROWUP_POTION,	  //������
	ITEM_MAX
}ITEM_PROPERTY;//�A�C�e���̑���

typedef struct
{
	D3DXVECTOR3 pos;	   //�ʒu
	D3DXCOLOR col;		   //�F
	float fWidth;		   //��
	float fHeight;		   //����
	int nScore;			   //�X�R�A
	float fAngle;		   //��]�p
	float fLength;		   //����
	int nCounterAnim;	   //�J�E���^�[	
	int nPatternAnim;	   //�e�N�X�`���̃A�j���[�V����
	bool bUse;			   //�g�p���Ă��邩		false == �g���ĂȂ�
	bool bDisp;			   //�����Ă��邩
	bool bDeleteFlag;	   //���ꂽ��			false == ����ĂȂ�
	ITEM_PROPERTY Property;//�A�C�e���̑���
}ITEM;//�A�C�e���̍\����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos,D3DXCOLOR col,int Score,ITEM_PROPERTY Property);

ITEM *GetItem(void);
int GetNumCoin(void);
void NumCoinReduce(void);

#endif

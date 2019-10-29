//=============================================================================
//
// �������� [Explosion.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION		(MAX_BULLET)						//�����̍ő吔
#define EXPLOSION_SIZE		(BULLET_SIZE * 3.5f)				//�����̃T�C�Y

#define EXPLOSION_TEXTURE "data/TEXTURE/explosion000.png"		//�����̃e�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col);

#endif

//=============================================================================
//
// �e����[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_FILENAME0 "data/TEXTURE/bullet000.png"
#define MAX_BULLET (256)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;	    //�e�N�X�`���ւ̃|�C���^

BULLET g_Bullet[MAX_BULLET];

int g_nBulletThreshold = 0;	//�����x��臒l

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, BULLET_FILENAME0, &g_pTextureBullet);

	MakeVertexBullet(pDevice);

	//�\���̂̏�����
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].nLife = 0;
		g_Bullet[nCntBullet].nDeleteIdxNpc = -1;
		g_Bullet[nCntBullet].bUse = false;

	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
		if (g_pTextureBullet != NULL)
		{
			g_pTextureBullet->Release();
			g_pTextureBullet = NULL;
		}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			g_Bullet[nCntBullet].Oldpos = g_Bullet[nCntBullet].pos;

			SetEffect(g_Bullet[nCntBullet].pos,
					  g_Bullet[nCntBullet].rot,
					  D3DXCOLOR(0.8f,0.5f,0.5f,1.0f),
					  g_Bullet[nCntBullet].fWidth * 1.1f,
					  g_Bullet[nCntBullet].Haight * 1.1f);


			//�e�̗͂����炷
			g_Bullet[nCntBullet].nLife--;
			if (g_Bullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_Bullet[nCntBullet].pos,
					g_Bullet[nCntBullet].rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					g_Bullet[nCntBullet].fWidth * 6.0f,
					g_Bullet[nCntBullet].Haight * 6.0f);

				DeleteShadow(g_Bullet[nCntBullet].nIdxShadow);
				g_Bullet[nCntBullet].bUse = false;
			}

			g_Bullet[nCntBullet].pos.x += sinf(g_Bullet[nCntBullet].rot.y + D3DX_PI) * g_Bullet[nCntBullet].move.x;
			g_Bullet[nCntBullet].pos.z += cosf(g_Bullet[nCntBullet].rot.y + D3DX_PI) * g_Bullet[nCntBullet].move.z;

			//�Փ˔���
			switch (g_Bullet[nCntBullet].type)
			{
			case BULLETTYPE_PLAYER:
				
				g_Bullet[nCntBullet].nDeleteIdxNpc = CollisionBullet(&g_Bullet[nCntBullet].pos,
					&g_Bullet[nCntBullet].Oldpos,
					&g_Bullet[nCntBullet].move,
					&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					&g_Bullet[nCntBullet].nDeleteIdxNpc);

				if (g_Bullet[nCntBullet].nDeleteIdxNpc != -1)
				{
					SetExplosion(g_Bullet[nCntBullet].pos,
						g_Bullet[nCntBullet].rot,
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						g_Bullet[nCntBullet].fWidth * 6.0f,
						g_Bullet[nCntBullet].Haight * 6.0f);

					DeleteShadow(g_Bullet[nCntBullet].nIdxShadow);
					g_Bullet[nCntBullet].bUse = false;
					DeleteNpc(g_Bullet[nCntBullet].nDeleteIdxNpc);
					g_Bullet[nCntBullet].nDeleteIdxNpc = -1;
				}
				break;

			case BULLETTYPE_ENEMY:

				if (CollisionPlayer(&g_Bullet[nCntBullet].pos,
					&g_Bullet[nCntBullet].Oldpos,
					&g_Bullet[nCntBullet].move,
					&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					&D3DXVECTOR3(0.0f, 0.0f, 0.0f)) == true)
				{
					DeletePlayer();
					DeleteShadow(g_Bullet[nCntBullet].nIdxShadow);
					g_Bullet[nCntBullet].bUse = false;
					g_Bullet[nCntBullet].nDeleteIdxNpc = -1;

				}
				
				break;

			}
			//�͈͊O�Œe����

			if (CollisionMeshWall(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].Oldpos) == true)
			{
					SetExplosion(g_Bullet[nCntBullet].pos,
						g_Bullet[nCntBullet].rot,
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						g_Bullet[nCntBullet].fWidth * 6.0f,
						g_Bullet[nCntBullet].Haight * 6.0f);

					DeleteShadow(g_Bullet[nCntBullet].nIdxShadow);
					g_Bullet[nCntBullet].bUse = false;
					PlaySound(SOUND_LABEL_SE004);

			}
			if (g_Bullet[nCntBullet].pos.x < -1000.0f||
				g_Bullet[nCntBullet].pos.x > 1000.0f||
				g_Bullet[nCntBullet].pos.z < -1000.0f|| 
				g_Bullet[nCntBullet].pos.z > 1000.0f)
			{
				SetExplosion(g_Bullet[nCntBullet].pos,
					g_Bullet[nCntBullet].rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					g_Bullet[nCntBullet].fWidth * 6.0f,
					g_Bullet[nCntBullet].Haight * 6.0f);

				DeleteShadow(g_Bullet[nCntBullet].nIdxShadow);
				g_Bullet[nCntBullet].bUse = false;
				PlaySound(SOUND_LABEL_SE004);

			}

			SetPositionShadow(g_Bullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_Bullet[nCntBullet].pos.x, 0.0f, g_Bullet[nCntBullet].pos.z));
			SetSizeShadow(g_Bullet[nCntBullet].nIdxShadow, g_Bullet[nCntBullet].pos.y , -g_Bullet[nCntBullet].Haight * 2);
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans , mtxView;				// �v�Z�p�}�g���b�N�X
	// ���[���h�}�g���b�N�X�̏�����
	// �|���S���̕`��

	//���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, g_nBulletThreshold);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	// ���C�e�B���O���[�h�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].g_mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW,&mtxView);

			g_Bullet[nCntBullet].g_mtxWorld._11 = mtxView._11;
			g_Bullet[nCntBullet].g_mtxWorld._12 = mtxView._21;
			g_Bullet[nCntBullet].g_mtxWorld._13 = mtxView._31;
			g_Bullet[nCntBullet].g_mtxWorld._21 = mtxView._12;
			g_Bullet[nCntBullet].g_mtxWorld._22 = mtxView._22;
			g_Bullet[nCntBullet].g_mtxWorld._23 = mtxView._32;
			g_Bullet[nCntBullet].g_mtxWorld._31 = mtxView._13;
			g_Bullet[nCntBullet].g_mtxWorld._32 = mtxView._23;
			g_Bullet[nCntBullet].g_mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Bullet[nCntBullet].pos.x,
				g_Bullet[nCntBullet].pos.y,
				g_Bullet[nCntBullet].pos.z);

			D3DXMatrixMultiply(&g_Bullet[nCntBullet].g_mtxWorld,
				&g_Bullet[nCntBullet].g_mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				4 * nCntBullet,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}
	}
	// ���C�e�B���O���[�h�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// �|���S���̐ݒ�
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fWidth, float haight, BULLETTYPE type)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{
			g_Bullet[nCntBullet].pos = pos;
			g_Bullet[nCntBullet].rot = rot;
			g_Bullet[nCntBullet].fWidth = fWidth;
			g_Bullet[nCntBullet].move = move;
			g_Bullet[nCntBullet].Haight = haight;
			g_Bullet[nCntBullet].type = type;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntBullet;
			pVtx[0].pos = D3DXVECTOR3(-g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Bullet[nCntBullet].fWidth, g_Bullet[nCntBullet].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Bullet[nCntBullet].fWidth, -g_Bullet[nCntBullet].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Bullet[nCntBullet].fWidth, -g_Bullet[nCntBullet].Haight, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBullet->Unlock();
			g_Bullet[nCntBullet].nLife = 100;
			g_Bullet[nCntBullet].bUse = true;

				g_Bullet[nCntBullet].nIdxShadow = 
					SetShadow(D3DXVECTOR3(g_Bullet[nCntBullet].pos.x, 0.0f, g_Bullet[nCntBullet].pos.z),
										  g_Bullet[nCntBullet].rot);
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntBullet;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBullet->Unlock();
	}
}
//=============================================================================
//	�I�����e����
//=============================================================================
void BulletErese(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].bUse = false;
	}
}



//typedef enum _D3DCMPFUNC {
//	D3DCMP_NEVER = 1,			//�S�ĕ`�悵�Ȃ�
//	D3DCMP_LESS = 2,			//��l����
//	D3DCMP_EQUAL = 3,			//��l�Ɠ������̂̂�
//	D3DCMP_LESSEQUAL = 4,		//��l�ȉ�
//	D3DCMP_GREATER = 5,			//��l����
//	D3DCMP_NOTEQUAL = 6,		//��l�ł͂Ȃ���
//	D3DCMP_GREATEREQUAL = 7,	//��l�ȏ�
//	D3DCMP_ALWAYS = 8,
//	D3DCMP_FORCE_DWORD = 0x7fffffff, 
//} D3DCMPFUNC;

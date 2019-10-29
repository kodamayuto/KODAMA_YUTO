//=============================================================================
//
// �Ǐ���[explosion.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "explosion.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EXPLOSION_FILENAME0 "data/TEXTURE/Effect_p011.png"		//�t�@�C�����̃}�N��
#define MAX_EXPLOSION (1024)									//

#define ANIM_EXPLOSION (8)

#define ANIM_COUNT_INTERVAL (4)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;	    //�e�N�X�`���ւ̃|�C���^

EXPLOSION g_Explosion[MAX_EXPLOSION];

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_FILENAME0, &g_pTextureExplosion);

	MakeVertexExplosion(pDevice);

	//�\���̂̏�����
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_Explosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Explosion[nCntExplosion].fWidth = 0.0f;
		g_Explosion[nCntExplosion].Haight = 0.0f;
		g_Explosion[nCntExplosion].nAnim = 0;
		g_Explosion[nCntExplosion].nCntAnimation = 0;
		g_Explosion[nCntExplosion].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// ���_�o�b�t�@�̊J��
		if (g_pTextureExplosion != NULL)
		{
			g_pTextureExplosion->Release();
			g_pTextureExplosion = NULL;
		}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == true)
		{
			g_Explosion[nCntExplosion].fWidth += 0.8f;
			g_Explosion[nCntExplosion].Haight += 0.8f;
			g_Explosion[nCntExplosion].nCntAnimation++;
			if (g_Explosion[nCntExplosion].nCntAnimation % ANIM_COUNT_INTERVAL == 0)
			{
				g_Explosion[nCntExplosion].nAnim++;

				if (g_Explosion[nCntExplosion].nAnim >= ANIM_EXPLOSION)
				{
					g_Explosion[nCntExplosion].bUse = false;
				}
			}
			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntExplosion;

			pVtx[0].pos = D3DXVECTOR3(-g_Explosion[nCntExplosion].fWidth, g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Explosion[nCntExplosion].fWidth, g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Explosion[nCntExplosion].fWidth, -g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Explosion[nCntExplosion].fWidth, -g_Explosion[nCntExplosion].Haight, 0.0f);

			pVtx[0].tex = D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (g_Explosion[nCntExplosion].nAnim % ANIM_EXPLOSION), 0.0f);
			pVtx[1].tex = D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (g_Explosion[nCntExplosion].nAnim % ANIM_EXPLOSION) + (1.0f / ANIM_EXPLOSION), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (g_Explosion[nCntExplosion].nAnim % ANIM_EXPLOSION), 1.0f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / ANIM_EXPLOSION) * (g_Explosion[nCntExplosion].nAnim % ANIM_EXPLOSION) + (1.0f / ANIM_EXPLOSION), 1.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffExplosion->Unlock();

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans , mtxView;				// �v�Z�p�}�g���b�N�X

	// �|���S���̕`��
	//// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//���e�X�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// Z�o�b�t�@�𖳌���
			pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);						

			// ���C�e�B���O���[�h�𖳌���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == true)
		{
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			D3DXMatrixIdentity(&g_Explosion[nCntExplosion].g_mtxWorld);

			g_Explosion[nCntExplosion].g_mtxWorld._11 = mtxView._11;
			g_Explosion[nCntExplosion].g_mtxWorld._12 = mtxView._21;
			g_Explosion[nCntExplosion].g_mtxWorld._13 = mtxView._31;
			g_Explosion[nCntExplosion].g_mtxWorld._21 = mtxView._12;
			g_Explosion[nCntExplosion].g_mtxWorld._22 = mtxView._22;
			g_Explosion[nCntExplosion].g_mtxWorld._23 = mtxView._32;
			g_Explosion[nCntExplosion].g_mtxWorld._31 = mtxView._13;
			g_Explosion[nCntExplosion].g_mtxWorld._32 = mtxView._23;
			g_Explosion[nCntExplosion].g_mtxWorld._33 = mtxView._33;
			
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Explosion[nCntExplosion].pos.x,
				g_Explosion[nCntExplosion].pos.y,
				g_Explosion[nCntExplosion].pos.z);

			D3DXMatrixMultiply(&g_Explosion[nCntExplosion].g_mtxWorld,
				&g_Explosion[nCntExplosion].g_mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCntExplosion].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				4 * nCntExplosion,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}

	}

	// ���C�e�B���O���[�h�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�o�b�t�@�̗L����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// �|���S���̐ݒ�
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float haight)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_Explosion[nCntExplosion].bUse == false)
		{
			g_Explosion[nCntExplosion].pos = pos;
			g_Explosion[nCntExplosion].rot = rot;
			g_Explosion[nCntExplosion].col = col;
			g_Explosion[nCntExplosion].fWidth = fWidth;
			g_Explosion[nCntExplosion].Haight = haight;
			g_Explosion[nCntExplosion].nAnim = 0;
			g_Explosion[nCntExplosion].nCntAnimation = 0;


			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntExplosion;
			pVtx[0].pos = D3DXVECTOR3(-g_Explosion[nCntExplosion].fWidth, g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Explosion[nCntExplosion].fWidth, g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Explosion[nCntExplosion].fWidth, -g_Explosion[nCntExplosion].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Explosion[nCntExplosion].fWidth, -g_Explosion[nCntExplosion].Haight, 0.0f);

			pVtx[0].col = g_Explosion[nCntExplosion].col;
			pVtx[1].col = g_Explosion[nCntExplosion].col;
			pVtx[2].col = g_Explosion[nCntExplosion].col;
			pVtx[3].col = g_Explosion[nCntExplosion].col;


			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffExplosion->Unlock();
			g_Explosion[nCntExplosion].bUse = true;

			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntExplosion;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		//pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffExplosion->Unlock();
	}
}


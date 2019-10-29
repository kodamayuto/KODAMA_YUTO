//=============================================================================
//
// �Ǐ���[particle.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "particle.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PARTICLE_FILENAME0 "data/TEXTURE/Ring000.png"
#define MAX_PARTICLE (4096)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;	    //�e�N�X�`���ւ̃|�C���^

PARTICLE g_Particle[MAX_PARTICLE];

//=============================================================================
// ����������
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, PARTICLE_FILENAME0, &g_pTextureParticle);

	MakeVertexParticle(pDevice);

	//�\���̂̏�����
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_Particle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Particle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Particle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Particle[nCntParticle].fWidth = 0.0f;
		g_Particle[nCntParticle].Haight = 0.0f;
		g_Particle[nCntParticle].nLife = 0;
		g_Particle[nCntParticle].bUse = false;
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitParticle(void)
{
	// ���_�o�b�t�@�̊J��
		if (g_pTextureParticle != NULL)
		{
			g_pTextureParticle->Release();
			g_pTextureParticle = NULL;
		}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParticle(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == true)
		{
			g_Particle[nCntParticle].fWidth -= 2.0f;
			g_Particle[nCntParticle].Haight -= 2.0f;

			if (g_Particle[nCntParticle].fWidth <= 0.0f || g_Particle[nCntParticle].Haight <= 0.0f)
			{
					g_Particle[nCntParticle].bUse = false;
			}


			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntParticle;

			pVtx[0].pos = D3DXVECTOR3(-g_Particle[nCntParticle].fWidth, g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Particle[nCntParticle].fWidth, g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Particle[nCntParticle].fWidth, -g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Particle[nCntParticle].fWidth, -g_Particle[nCntParticle].Haight, 0.0f);

			pVtx[0].col = g_Particle[nCntParticle].col;
			pVtx[1].col = g_Particle[nCntParticle].col;
			pVtx[2].col = g_Particle[nCntParticle].col;
			pVtx[3].col = g_Particle[nCntParticle].col;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffParticle->Unlock();

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans , mtxView;				// �v�Z�p�}�g���b�N�X
	PLAYER *pPlayer = GetPlayer();
	D3DXMATRIX playerMtx;
	// �|���S���̕`��
			//// ���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			//���e�X�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 120);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// Z�o�b�t�@�𖳌���
			pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == true)
		{

			D3DXMatrixIdentity(&g_Particle[nCntParticle].g_mtxWorld);

			g_Particle[nCntParticle].g_mtxWorld._11 = mtxView._11;
			g_Particle[nCntParticle].g_mtxWorld._12 = mtxView._21;
			g_Particle[nCntParticle].g_mtxWorld._13 = mtxView._31;
			g_Particle[nCntParticle].g_mtxWorld._21 = mtxView._12;
			g_Particle[nCntParticle].g_mtxWorld._22 = mtxView._22;
			g_Particle[nCntParticle].g_mtxWorld._23 = mtxView._32;
			g_Particle[nCntParticle].g_mtxWorld._31 = mtxView._13;
			g_Particle[nCntParticle].g_mtxWorld._32 = mtxView._23;
			g_Particle[nCntParticle].g_mtxWorld._33 = mtxView._33;
			
			//// �ʒu�𔽉f
			//D3DXMatrixTranslation(&mtxTrans,
			//	g_Particle[nCntParticle].pos.x,
			//	g_Particle[nCntParticle].pos.y,
			//	g_Particle[nCntParticle].pos.z);

			//D3DXMatrixMultiply(&g_Particle[nCntParticle].g_mtxWorld,
			//	&g_Particle[nCntParticle].g_mtxWorld,
			//	&mtxTrans);

			//�v���C���[�̈ʒu�𔽉f
			D3DXMatrixTranslation(&playerMtx,
				pPlayer->pos.x,
				pPlayer->pos.y,
				pPlayer->pos.z);

			D3DXMatrixMultiply(&g_Particle[nCntParticle].g_mtxWorld,
				&g_Particle[nCntParticle].g_mtxWorld,
				&playerMtx);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Particle[nCntParticle].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				4 * nCntParticle,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}

	}
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
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float haight)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse == false)
		{
			g_Particle[nCntParticle].pos = pos;
			g_Particle[nCntParticle].rot = rot;
			g_Particle[nCntParticle].col = col;
			g_Particle[nCntParticle].move = move;
			g_Particle[nCntParticle].fWidth = fWidth;
			g_Particle[nCntParticle].Haight = haight;


			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntParticle;
			pVtx[0].pos = D3DXVECTOR3(-g_Particle[nCntParticle].fWidth, g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Particle[nCntParticle].fWidth, g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Particle[nCntParticle].fWidth, -g_Particle[nCntParticle].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Particle[nCntParticle].fWidth, -g_Particle[nCntParticle].Haight, 0.0f);

			pVtx[0].col = g_Particle[nCntParticle].col;
			pVtx[1].col = g_Particle[nCntParticle].col;
			pVtx[2].col = g_Particle[nCntParticle].col;
			pVtx[3].col = g_Particle[nCntParticle].col;


			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffParticle->Unlock();
			g_Particle[nCntParticle].bUse = true;

			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntParticle;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffParticle->Unlock();
	}
}


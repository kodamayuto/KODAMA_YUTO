//=============================================================================
//
// �Ǐ���[wall.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "wall.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WALL_FILENAME0 "data/TEXTURE/wall000.jpg"
#define WALL_FILENAME1 "data/TEXTURE/wall000.jpg"
#define MAX_WALL (256)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall[2] = {};	    //�e�N�X�`���ւ̃|�C���^

WALL g_Wall[MAX_WALL];
//=============================================================================
// ����������
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, WALL_FILENAME0, &g_pTextureWall[0]);
	D3DXCreateTextureFromFile(pDevice, WALL_FILENAME1, &g_pTextureWall[1]);

	MakeVertexWall(pDevice);

	//�\���̂̏�����
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	// ���_�o�b�t�@�̊J��
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureWall[nCntTex] != NULL)
		{
			g_pTextureWall[nCntTex]->Release();
			g_pTextureWall[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	// ���[���h�}�g���b�N�X�̏�����
	// �|���S���̕`��
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			D3DXMatrixIdentity(&g_Wall[nCntWall].g_mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Wall[nCntWall].rot.y,
				g_Wall[nCntWall].rot.x,
				g_Wall[nCntWall].rot.z);

			D3DXMatrixMultiply(&g_Wall[nCntWall].g_mtxWorld,
				&g_Wall[nCntWall].g_mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Wall[nCntWall].pos.x,
				g_Wall[nCntWall].pos.y,
				g_Wall[nCntWall].pos.z);

			D3DXMatrixMultiply(&g_Wall[nCntWall].g_mtxWorld,
				&g_Wall[nCntWall].g_mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

			pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

				// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall[0]);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
				4 * nCntWall,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// �|���S���̐ݒ�
//=============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, WALLTYPE type, float fWidth ,float fHaight)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].rot = rot;
			g_Wall[nCntWall].fWidth = fWidth;
			g_Wall[nCntWall].Haight = fHaight;
			g_Wall[nCntWall].type = type;
			

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntWall;
			switch (g_Wall[nCntWall].type)
			{
			case WALLTYPE_1:

				pVtx[0].pos = D3DXVECTOR3(-g_Wall[nCntWall].fWidth, g_Wall[nCntWall].Haight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Wall[nCntWall].fWidth, g_Wall[nCntWall].Haight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Wall[nCntWall].fWidth,0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Wall[nCntWall].fWidth, 0.0f, 0.0f);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Wall[nCntWall].fWidth / 100.0f) + 1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, (g_Wall[nCntWall].Haight / 100.0f) + 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Wall[nCntWall].fWidth / 100.0f) + 1.0f, (g_Wall[nCntWall].Haight / 100.0f) + 1.0f);
				break;
			}
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffWall->Unlock();
			g_Wall[nCntWall].bUse = true;
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//�ϐ��錾
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntWall;

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
		g_pVtxBuffWall->Unlock();
	}
}


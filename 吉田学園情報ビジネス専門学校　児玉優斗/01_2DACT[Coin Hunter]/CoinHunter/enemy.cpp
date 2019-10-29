//=============================================================================
//
// �G���� [enemy.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "enemy.h"

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^

ENEMY g_aEnemy[MAX_ENEMY];	//�G�̃f�[�^�i�[
int g_nNumEnemy;			//�G�̑���
int g_nCounterGame;			//�o�����Ԃ̊Ǘ�

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 5;
		g_aEnemy[nCntEnemy].bDirection = false;
	}
	g_nNumEnemy = 0;
	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_00, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_01, &g_apTextureEnemy[1]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		pVtx[0].pos = D3DXVECTOR3(0 - ENEMY_POLYGON_SIZE, 0 - ENEMY_POLYGON_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0 + ENEMY_POLYGON_SIZE, 0 - ENEMY_POLYGON_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0 - ENEMY_POLYGON_SIZE, 0 + ENEMY_POLYGON_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0 + ENEMY_POLYGON_SIZE, 0 + ENEMY_POLYGON_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(ENEMY_COLOR_RED, ENEMY_COLOR_GREEN, ENEMY_COLOR_BLUE, ENEMY_COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(ENEMY_COLOR_RED, ENEMY_COLOR_GREEN, ENEMY_COLOR_BLUE, ENEMY_COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(ENEMY_COLOR_RED, ENEMY_COLOR_GREEN, ENEMY_COLOR_BLUE, ENEMY_COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(ENEMY_COLOR_RED, ENEMY_COLOR_GREEN, ENEMY_COLOR_BLUE, ENEMY_COLOR_ALPHA);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			switch (g_aEnemy[nCntEnemy].nType)
			{
			case 0:
				if (g_aEnemy[nCntEnemy].pos.x <= 0 || g_aEnemy[nCntEnemy].pos.x >= SCREEN_WIDTH)
				{
					g_aEnemy[nCntEnemy].bDirection = g_aEnemy[nCntEnemy].bDirection ? false : true;
					g_aEnemy[nCntEnemy].move.x *= -1;
				}

				break;
			}
			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntEnemy;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_POLYGON_SIZE, 0.0f);

			if (g_aEnemy[nCntEnemy].bDirection == false)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);

			}

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEnemy->Unlock();


		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			}
			else if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DAMAGE)
			{
				pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType + 4]);
			}

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
				4 * nCntEnemy,							   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							       //�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	int nCntEnemy;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (4*nCntEnemy);

			g_aEnemy[nCntEnemy].pos = pos;

			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_POLYGON_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_POLYGON_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_POLYGON_SIZE, 0.0f);

			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;

			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

			g_aEnemy[nCntEnemy].nCounterState = 0;

			g_aEnemy[nCntEnemy].nLife = 2 * (1 + nType);
			g_aEnemy[nCntEnemy].bUse = true;

			g_aEnemy[nCntEnemy].bDirection = false;

			g_pVtxBuffEnemy->Unlock();

			g_nNumEnemy++;
			break;
		}	
	}
}

//=============================================================================
// �G�̎擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=============================================================================
// �G�̐��̎擾
//=============================================================================
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}

//=============================================================================
//	�_���[�W����
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{

}

//=============================================================================
//	�G�̗̑͌���(�f�o�b�N�p)
//=============================================================================
void DebugEnemyLifeDown(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].nLife = 1;
		}
	}
}

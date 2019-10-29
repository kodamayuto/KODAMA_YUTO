//=============================================================================
//
// �^�C�}�[���� [miniMap.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "miniMap.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_MINIMAP_POLYGON (2 + MAX_NUM_NPC)

//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void MakeVertexminiMap(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffminiMap = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureminiMap[2] = {};						//�e�N�X�`���ւ̃|�C���^

CHARACTER_TILE g_CharaTile[MAX_NUM_NPC + 1];
//=============================================================================
//	����������
//=============================================================================
void InitMiniMap(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/MiniMap000.png", &g_pTextureminiMap[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mapChara000.png", &g_pTextureminiMap[1]);

	MakeVertexminiMap(pDevice);
}

//=============================================================================
//	�I������
//=============================================================================
void UninitMiniMap(void)
{
	//�e�N�X�`���̉��
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureminiMap[nCntTex] != NULL)
		{
			g_pTextureminiMap[nCntTex]->Release();
			g_pTextureminiMap[nCntTex] = NULL;
		}

	}
	//�o�b�t�@�̉��
	if (g_pVtxBuffminiMap != NULL)
	{
		g_pVtxBuffminiMap->Release();
		g_pVtxBuffminiMap = NULL;

	}

}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdateMiniMap(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	NPC *pNPC;
	pNPC = GetNPC();

	g_CharaTile[0].pos.x = (pPlayer->pos.x + 1000.0f) / 8.0f;
	g_CharaTile[0].pos.y = (-pPlayer->pos.z + 1000.0f) / 8.0f;
	g_CharaTile[0].nTextype = 0;

	for (int nCntNPC = 0; nCntNPC < MAX_NUM_NPC; nCntNPC++)
	{
		g_CharaTile[nCntNPC + 1].pos.x = (pNPC->pos.x + 1000.0f) / 8.0f;
		g_CharaTile[nCntNPC + 1].pos.y = (-pNPC->pos.z + 1000.0f) / 8.0f;
		g_CharaTile[nCntNPC + 1].nTextype = 1;

		pNPC++;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffminiMap->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	for (int nCntTile = 0; nCntTile < MAX_MINIMAP_POLYGON - 1; nCntTile++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_CharaTile[nCntTile].pos.x - 10.0f + 10.0f, g_CharaTile[nCntTile].pos.y - 10.0f + 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_CharaTile[nCntTile].pos.x + 10.0f + 10.0f, g_CharaTile[nCntTile].pos.y - 10.0f + 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_CharaTile[nCntTile].pos.x - 10.0f + 10.0f, g_CharaTile[nCntTile].pos.y + 10.0f + 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_CharaTile[nCntTile].pos.x + 10.0f + 10.0f, g_CharaTile[nCntTile].pos.y + 10.0f + 10.0f, 0.0f);

		if (g_CharaTile[nCntTile].nTextype == 0)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		}
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffminiMap->Unlock();

}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawMiniMap(void)
{
	for (int nCntminiMap = 0; nCntminiMap < MAX_MINIMAP_POLYGON; nCntminiMap++)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		pDevice->SetStreamSource(0, g_pVtxBuffminiMap, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

									   // �e�N�X�`���̐ݒ�
		if (nCntminiMap == 0)
		{
			pDevice->SetTexture(0, g_pTextureminiMap[0]);//�e�N�X�`���̐ݒ�
		}
		else
		{
			pDevice->SetTexture(0, g_pTextureminiMap[1]);//�e�N�X�`���̐ݒ�
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��					//�v���~�e�B�u == �|���S��
			4 * nCntminiMap,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�
	}
}

//=============================================================================
//	���_���̒ǉ�
//=============================================================================
void MakeVertexminiMap(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MINIMAP_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffminiMap,
		NULL);

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffminiMap->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(260.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(10.0f, 260.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(260.0f, 260.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[	��
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		for (int nCntTile = 1; nCntTile < MAX_MINIMAP_POLYGON; nCntTile++)
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[	��
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx += 4;

		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffminiMap->Unlock();

}

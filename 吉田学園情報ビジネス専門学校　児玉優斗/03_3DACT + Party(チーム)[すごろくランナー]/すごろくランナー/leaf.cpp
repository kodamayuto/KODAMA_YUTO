//=============================================================================
//
// ���̏��� [leaf.cpp]
// Author :Jukiya Hayakawa
//
//=============================================================================
#include "leaf.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_LEAF			(256)								// �e�̍ő吔
#define POLYGON_X			(1200)								// �|���S����X���W
#define POLYGON_Y			(350)								// �|���S����Y���W
#define LEAF_TEXTURENAME	"data\\TEXTURE\\leaf.png"			// �e�N�X�`����
#define LEAF_SIZE			(500.0f)							    // �e�̑傫��
#define LEAF_HIT			(30)								// �����蔻��

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLeaf = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLeaf = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Leaf g_aLeaf[MAX_LEAF];						// �g�p���Ă��邩�ǂ���

//=============================================================================
// ����������
//=============================================================================
void InitLeaf(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLeaf;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//// �|���S�����W�̐ݒ�
	//g_aLeaf[0].pos = D3DXVECTOR3(POLYGON_X, POLYGON_Y, 0.0f);
	//g_aLeaf[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���̏��̏�����
	for (nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{
		g_aLeaf[nCntLeaf].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaf[nCntLeaf].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaf[nCntLeaf].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, LEAF_TEXTURENAME, &g_pTextureLeaf);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LEAF,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffLeaf,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLeaf->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x - LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y - LEAF_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x + LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y - LEAF_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x - LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y + LEAF_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x + LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y + LEAF_SIZE, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// ���_�f�[�^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffLeaf->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitLeaf(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureLeaf != NULL)
	{
		g_pTextureLeaf->Release();
		g_pTextureLeaf = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLeaf != NULL)
	{
		g_pVtxBuffLeaf->Release();
		g_pVtxBuffLeaf = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLeaf(void)
{
	int nCntLeaf;

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLeaf->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{
		if (g_aLeaf[nCntLeaf].bUse == true)	// �g�p����Ă���
		{
					g_aLeaf[nCntLeaf].pos += g_aLeaf[nCntLeaf].move;
	
			// ���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x - LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y - LEAF_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x + LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y - LEAF_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x - LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y + LEAF_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLeaf[nCntLeaf].pos.x + LEAF_SIZE, g_aLeaf[nCntLeaf].pos.y + LEAF_SIZE, 0.0f);

		}

		pVtx += 4;	// �Y���̈ʒu�܂Ői�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffLeaf->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLeaf(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLeaf;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffLeaf, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLeaf);

	// �|���S���̕`��
	for (nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{
		if (g_aLeaf[nCntLeaf].bUse == true)	// �e���g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntLeaf,
				2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetLeaf(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	for (int nCntLeaf = 0; nCntLeaf < MAX_LEAF; nCntLeaf++)
	{//�ǂ̐������J��Ԃ�
		if (g_aLeaf[nCntLeaf].bUse == false)
		{//�ǂ��g�p���Ă��Ȃ��ꍇ
			g_aLeaf[nCntLeaf].pos = pos;
			g_aLeaf[nCntLeaf].move = move;
			g_aLeaf[nCntLeaf].bUse = true;

			break;
		}
	}
}
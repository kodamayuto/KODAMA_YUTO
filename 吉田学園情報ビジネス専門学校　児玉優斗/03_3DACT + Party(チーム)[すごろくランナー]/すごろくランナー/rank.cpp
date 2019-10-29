//=============================================================================
//
// �����N���� [rank.cpp]
// Author :�@Jukiya Hayakawa
//
//=============================================================================
#include "rank.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANK_TEXTURE_NAME0	"data\\TEXTURE\\rank.png"		// �e�N�X�`����
#define	RANK_SIZE			(130)							// �傫��
#define	MAX_RANK			(2)								//�����N�̍ő吔

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureRank = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
RANK g_aRank;												// �����N�̏��

//=============================================================================
// ����������
//=============================================================================
void InitRank(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	g_aRank.pos = D3DXVECTOR3(1165.0f, 635.0f, 0.0f);	//�ʒu�̏�����
	g_aRank.rank = RANK_1;								//�����N�̏�����
	g_aRank.bUse = true;								//�g�p��Ԃɂ���

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, RANK_TEXTURE_NAME0, &g_apTextureRank);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aRank.pos.x - RANK_SIZE, g_aRank.pos.y - RANK_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aRank.pos.x + RANK_SIZE, g_aRank.pos.y - RANK_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aRank.pos.x - RANK_SIZE, g_aRank.pos.y + RANK_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aRank.pos.x + RANK_SIZE, g_aRank.pos.y + RANK_SIZE, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		break;

		pVtx += 4;	// ���_�f�[�^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitRank(void)
{

	// �e�N�X�`���̊J��
	if (g_apTextureRank != NULL)
	{
		g_apTextureRank->Release();
		g_apTextureRank = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRank(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRank(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (g_aRank.bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureRank);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntRank,
				2);
		}
	}
}

//=============================================================================
// �����N�̐ݒ�
//=============================================================================
void SetRank(PLAYER_RANK rank)
{
	int nCntRank;

	g_aRank.rank = rank;

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//�����N�̐������J��Ԃ�
		VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntRank * 4);	// �Y���̈ʒu�܂Ői�߂�

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aRank.pos.x - RANK_SIZE, g_aRank.pos.y - RANK_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aRank.pos.x + RANK_SIZE, g_aRank.pos.y - RANK_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aRank.pos.x - RANK_SIZE, g_aRank.pos.y + RANK_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aRank.pos.x + RANK_SIZE, g_aRank.pos.y + RANK_SIZE, 0.0f);

		switch (g_aRank.rank)
		{
		case RANK_1:
			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
			break;

		case RANK_2:
			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}
		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffRank->Unlock();
		break;
	}
}

//=============================================================================
// �����N�̎擾
//=============================================================================
RANK *GetRank(void)
{
	return &g_aRank;
}

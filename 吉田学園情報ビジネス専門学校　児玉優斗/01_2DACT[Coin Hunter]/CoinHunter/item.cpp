//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "item.h"

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[NUM_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

ITEM g_aItem[MAX_ITEM];							// �A�C�e���̏��

int g_nNumCoin = 0;
//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aItem[nCntItem].fWidth = 0.0f;
		g_aItem[nCntItem].fHeight = 0.0f;
		g_aItem[nCntItem].nScore = 0;
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].bUse = false;
		g_aItem[nCntItem].bDisp = false;
		g_aItem[nCntItem].Property = ITEM_SCOREUP_COIN;
	}
	g_nNumCoin = 0;
	// �e�N�X�`���̓ǂݍ���
	
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE, &g_pTextureItem[0]);

	// ���_���̍쐬

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{

	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < NUM_TEXTURE; nCntTex++)
	{
		if (g_pTextureItem[nCntTex] != NULL)
		{
			g_pTextureItem[nCntTex]->Release();
			g_pTextureItem[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	Player *pPlayer;
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		
		if (g_aItem[nCntItem].bDisp == true)
		{
			//�A�j���[�V����
			g_aItem[nCntItem].nCounterAnim++;
			if (g_aItem[nCntItem].nCounterAnim % 5 == 0)
			{
				g_aItem[nCntItem].nPatternAnim = (g_aItem[nCntItem].nPatternAnim + 1) % TEX_PATTERN;
			}
			//g_aItem[nCntItem].fAngle = atan2f(g_aItem[nCntItem].fWidth ,g_aItem[nCntItem].fHeight);
			if (g_aItem[nCntItem].bDeleteFlag == true)
			{
				g_aItem[nCntItem].bUse = false;
				g_aItem[nCntItem].fAngle -= 0.05f;
				g_aItem[nCntItem].fLength -= 0.5f;
				g_aItem[nCntItem].pos.y -= 6.0f;
				g_aItem[nCntItem].col.a -= 0.05f;
				if (g_aItem[nCntItem].fAngle < 0.0f)
				{
					g_aItem[nCntItem].bDisp = false;
					NumCoinReduce();
				}
			}
			//g_aItem[nCntItem].fLength = sqrtf((g_aItem[nCntItem].fWidth) *(g_aItem[nCntItem].fWidth)+ 
			//									(g_aItem[nCntItem].fHeight) * (g_aItem[nCntItem].fHeight));

			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y - cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y - cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y + cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y + cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);

			pVtx[0].col = g_aItem[nCntItem].col;
			pVtx[1].col = g_aItem[nCntItem].col;
			pVtx[2].col = g_aItem[nCntItem].col;
			pVtx[3].col = g_aItem[nCntItem].col;

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2((1.0f / TEX_PATTERN) * (g_aItem[nCntItem].nPatternAnim % TEX_PATTERN), 0.0f);
			pVtx[1].tex = D3DXVECTOR2((1.0f / TEX_PATTERN) * (g_aItem[nCntItem].nPatternAnim % TEX_PATTERN) + (1.0f / TEX_PATTERN), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((1.0f / TEX_PATTERN) * (g_aItem[nCntItem].nPatternAnim % TEX_PATTERN), 1.0f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / TEX_PATTERN) * (g_aItem[nCntItem].nPatternAnim % TEX_PATTERN) + (1.0f / TEX_PATTERN), 1.0f);
			
		}
		pVtx += 4;

	}
	
	// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureItem[0]);

	// �|���S���̕`��
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bDisp == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
				4* nCntItem,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							       //�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col, int Score, ITEM_PROPERTY Property)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	int nCntItem;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)//�g�p���ĂȂ����̂���g�p����
		{
			g_aItem[nCntItem].Property = Property;

			//�T�C�Y
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].fWidth = ITEM_SIZE;
			g_aItem[nCntItem].fHeight = ITEM_SIZE;

			g_aItem[nCntItem].fAngle = atan2f(g_aItem[nCntItem].fWidth, g_aItem[nCntItem].fHeight);
			g_aItem[nCntItem].fLength = sqrtf((g_aItem[nCntItem].fWidth) *(g_aItem[nCntItem].fWidth) +
				(g_aItem[nCntItem].fHeight) * (g_aItem[nCntItem].fHeight));

			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y - cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y - cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y + cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + sinf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, g_aItem[nCntItem].pos.y + cosf(g_aItem[nCntItem].fAngle) * g_aItem[nCntItem].fLength, 0.0f);

			//�F
			g_aItem[nCntItem].col = col;
			pVtx[0].col = g_aItem[nCntItem].col;
			pVtx[1].col = g_aItem[nCntItem].col;
			pVtx[2].col = g_aItem[nCntItem].col;
			pVtx[3].col = g_aItem[nCntItem].col;

			//�e�N�X�`��
			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].nPatternAnim = 0;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			//����
			g_aItem[nCntItem].nScore = Score;
			g_aItem[nCntItem].bUse = true;
			g_aItem[nCntItem].bDisp = true;
			g_aItem[nCntItem].bDeleteFlag = false;

			if (g_aItem[nCntItem].Property == ITEM_SCOREUP_COIN)
			{
				g_nNumCoin++;
			}
			break;
		}
		pVtx += 4;
		
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();

}
//=============================================================================
// �A�C�e���̏��擾
//=============================================================================
ITEM *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// �c�R�C�����擾
//=============================================================================
int GetNumCoin(void)
{
	return g_nNumCoin;
}

//=============================================================================
// �R�C���������炷
//=============================================================================
void NumCoinReduce(void)
{
	g_nNumCoin--;
}
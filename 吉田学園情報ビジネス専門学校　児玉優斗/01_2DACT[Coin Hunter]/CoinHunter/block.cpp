//=============================================================================
//
// �u���b�N�̏��� [block.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "block.h"
#include "Player.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_BLOCK_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Block					g_aBlock[MAX_BLOCK];		//�u���b�N�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bFlag = false;
		g_aBlock[nCntBlock].nWarpCount = 10;
		g_aBlock[nCntBlock].type = BLOCKTYPE_NORMAL;
		g_aBlock[nCntBlock].ContBlock = BLOCKCONTACT_NONE;
	}

	// ���_���̍쐬
	MakeVertexBlock(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlock(void)
{
	for (int nCntTex = 0; nCntTex < MAX_BLOCK_TEXTURE; nCntTex++)
	{	// �e�N�X�`���̊J��
		if (g_pTextureBlock[nCntTex] != NULL)
		{
			g_pTextureBlock[nCntTex]->Release();
			g_pTextureBlock[nCntTex] = NULL;
		}

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffBlock != NULL)
		{
			g_pVtxBuffBlock->Release();
			g_pVtxBuffBlock = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	for (int nCntData = 0; nCntData < MAX_BLOCK; nCntData++)
	{
		if (g_aBlock[nCntData].bUse == true)
		{
				g_aBlock[nCntData].pos += g_aBlock[nCntData].move;

			switch (g_aBlock[nCntData].type)
			{
			case BLOCKTYPE_MOVE://�ړ�
				if (g_aBlock[nCntData].OldPos.x - g_aBlock[nCntData].pos.x <= -150||
					g_aBlock[nCntData].OldPos.x - g_aBlock[nCntData].pos.x >= 150)
				{
					g_aBlock[nCntData].move.x *= -1;
				}
				if (g_aBlock[nCntData].OldPos.y - g_aBlock[nCntData].pos.y <= -250 ||
					g_aBlock[nCntData].OldPos.y - g_aBlock[nCntData].pos.y >= 250)
				{
					g_aBlock[nCntData].move.y *= -1;
				}
				break;

			case BLOCKTYPE_FALL://������
				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_ON)
				{
					g_aBlock[nCntData].bFlag = true;
				}
				if (g_aBlock[nCntData].bFlag == true)
				{
					g_aBlock[nCntData].move.y += 0.6f;
				}
				if (g_aBlock[nCntData].pos.y > SCREEN_HEIGHT)
				{
					g_aBlock[nCntData].bUse = false;
					g_aBlock[nCntData].bFlag = false;
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_NONE;
				}
				break;

			case BLOCKTYPE_ATTACK_MOVE:
				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_UNDER)
				{
					g_aBlock[nCntData].pos.y -= g_aBlock[nCntData].fHeight - 5;
				}
				break;

			case BLOCKTYPE_INV:
				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_ON)
				{
					g_aBlock[nCntData].bFlag = true;
				}
				if (g_aBlock[nCntData].bFlag == true)
				{
					g_aBlock[nCntData].col.a -= 0.01f;
				}
				if (g_aBlock[nCntData].col.a <= 0.0f)
				{
					g_aBlock[nCntData].col.a = 0.0f;
					g_aBlock[nCntData].bUse = false;
					g_aBlock[nCntData].bFlag = false;
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_NONE;
				}
				break;

			case BLOCKTYPE_WARP_IN:
				int nOUTIndex;
				Player *pPlayer;
				pPlayer = GetPlayer();

				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_ON)
				{
					g_aBlock[nCntData].bFlag = true;
				}
				if (g_aBlock[nCntData].bFlag == true)
				{
					pPlayer->move.x = 0.0f;
					pPlayer->move.y -= 2.0f;
					pPlayer->col.a -= 0.2f;
					g_aBlock[nCntData].nWarpCount--;
				}
				if (g_aBlock[nCntData].nWarpCount == 5)
				{
					nOUTIndex = ReturnBlockIndex(nCntData);
					PlaySound(SOUND_LABEL_SE_005);

					pPlayer->pos = D3DXVECTOR3(g_aBlock[nOUTIndex].pos.x + g_aBlock[nOUTIndex].fWidth / 2,
											   g_aBlock[nOUTIndex].pos.y,
											   0.0f);
					pPlayer->col.a += 0.2f;
					pPlayer->move.x = 0.0f;
					pPlayer->move.y = 0.0f;
				}
				if (g_aBlock[nCntData].nWarpCount <= 0)
				{
					g_aBlock[nCntData].bFlag = false;
					pPlayer->col.a = 1.0f;
					g_aBlock[nCntData].nWarpCount = 10;
				}
				break;
			case BLOCKTYPE_RESET:
				if (g_aBlock[nCntData].ContBlock == BLOCKCONTACT_UNDER)
				{
					ResetAttackMoveBlock();
				}

				break;
			}

			// ���_����ݒ�
			g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntData;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);

			pVtx[0].col = g_aBlock[nCntData].col;
			pVtx[1].col = g_aBlock[nCntData].col;
			pVtx[2].col = g_aBlock[nCntData].col;
			pVtx[3].col = g_aBlock[nCntData].col;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBlock->Unlock();
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBlock;
	
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�

	// �|���S���̕`��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
				4 * nCntBlock,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   			   //�v���~�e�B�u�̐�
		}

	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK,	&g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_1, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_4, &g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_5, &g_pTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_6, &g_pTextureBlock[6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLOCK_7, &g_pTextureBlock[7]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						// ���_����ݒ�
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_BLOCK; nCntData++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = g_aBlock[nCntData].col;
		pVtx[1].col = g_aBlock[nCntData].col;
		pVtx[2].col = g_aBlock[nCntData].col;
		pVtx[3].col = g_aBlock[nCntData].col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();


}

//=============================================================================
// �u���b�N�̐ݒ�
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWidth,float fHeight, BLOCKTYPE type)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	int nCntData;
	for (nCntData = 0; nCntData < MAX_BLOCK; nCntData++)
	{
		if (g_aBlock[nCntData].bUse == false)
		{
			g_aBlock[nCntData].pos = pos;
			g_aBlock[nCntData].OldPos = pos;
			g_aBlock[nCntData].move = move;
			g_aBlock[nCntData].fWidth = fWidth;
			g_aBlock[nCntData].fHeight = fHeight;
		
			// ���_����ݒ�
			g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntData;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth, g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight, 0.0f);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = g_aBlock[nCntData].col;
			pVtx[1].col = g_aBlock[nCntData].col;
			pVtx[2].col = g_aBlock[nCntData].col;
			pVtx[3].col = g_aBlock[nCntData].col;

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f * (g_aBlock[nCntData].fWidth / 40.0f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * (g_aBlock[nCntData].fHeight / 40.0f));
			pVtx[3].tex = D3DXVECTOR2(1.0f * (g_aBlock[nCntData].fWidth / 40.0f), 1.0f * (g_aBlock[nCntData].fHeight / 40.0f));


			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBlock->Unlock();
			g_aBlock[nCntData].type = type;

			g_aBlock[nCntData].bUse = true;
			break;
		}
	}
}

//=============================================================================
//	�u���b�N�̓����蔻��
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldPos, D3DXVECTOR3 *pMove)
{
	//�ϐ��錾
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_BLOCK; nCntData++)
	{
		g_aBlock[nCntData].ContBlock = BLOCKCONTACT_NONE;
		if (g_aBlock[nCntData].bUse == true)//�g���Ă�����
		{
			if (g_aBlock[nCntData].pos.x  <= pOldPos->x &&
				g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth >= pOldPos->x)
			{
				if (g_aBlock[nCntData].pos.y <= pPos->y&&
					g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight >= pOldPos->y)
				{//�ォ�牺��
					bLand = true;//�n�ʂɏ���Ă��锻��
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_ON;
					pPos->y = g_aBlock[nCntData].pos.y;
					pMove->x += g_aBlock[nCntData].move.x /2.4f;
					pMove->y = 0.0f;
					pMove->y += g_aBlock[nCntData].move.y;
				}
				
				if (g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight >= pPos->y - PLAYER_SIZE_Y * 2 &&
					g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight <= pOldPos->y - PLAYER_SIZE_Y * 2)
				{//��������
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_UNDER;
					pPos->y = g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight + PLAYER_SIZE_Y * 2;
					pMove->y = 0.1f;
					PlaySound(SOUND_LABEL_SE_007);
				}
			}
			 if (g_aBlock[nCntData].pos.y < pOldPos->y - PLAYER_SIZE_Y&&
				g_aBlock[nCntData].pos.y + g_aBlock[nCntData].fHeight >= pOldPos->y - PLAYER_SIZE_Y * 2)
			{
				if (g_aBlock[nCntData].pos.x <= pPos->x + PLAYER_SIZE_X &&
					g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth >= pPos->x + PLAYER_SIZE_X &&
					g_aBlock[nCntData].pos.x >= pOldPos->x)
				{//������E��
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_LEFT;
					pPos->x = g_aBlock[nCntData].pos.x - PLAYER_SIZE_X;
					pMove->x = 0;
				}

				if (g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth >= pPos->x - PLAYER_SIZE_X&&
					g_aBlock[nCntData].pos.x <= pPos->x - PLAYER_SIZE_X &&
					g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth <= pOldPos->x)
				{//�E���獶��
					g_aBlock[nCntData].ContBlock = BLOCKCONTACT_RIGHT;
					pPos->x = g_aBlock[nCntData].pos.x + g_aBlock[nCntData].fWidth + PLAYER_SIZE_X;
					pMove->x = 0;
				}
			}
		}
	}
	return bLand;//�ǂ����̒n�ʂɏ���Ă����true��Ԃ�
}

//=============================================================================
//	���[�v��̃u���b�N��Ԃ��֐�
//=============================================================================
int ReturnBlockIndex(int nIndex)
{
	int nCntData = nIndex;
	while (1)
	{
		nCntData++;
		if (g_aBlock[nCntData].type == BLOCKTYPE_WARP_OUT)
		{
			break;
		}
	}

	return nCntData;
}
//=============================================================================
//	�u���b�N�̈ʒu�����ɖ߂��֐�
//=============================================================================
void ResetAttackMoveBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].type == BLOCKTYPE_ATTACK_MOVE)
		{
			g_aBlock[nCntBlock].pos = g_aBlock[nCntBlock].OldPos;
		}
	}
}
//*****************************************************************************
//
//	DirectX �v���C���[�̏��� [player.cpp]
//	Author : Kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "Player.h"
#include "block.h"

//=============================================================================
//	�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;	                    //�e�N�X�`���ւ̃|�C���^

Player g_Player;		//�v���C���[�̏��

//-----------------------------------------------------------------------------
//	�|���S���̏���������
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���C���[�̏��̏�����
	g_Player.pos = D3DXVECTOR3(PLAYER_POS_X,PLAYER_POS_Y,0.0f);
	g_Player.oldPos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);
	g_Player.col = D3DXCOLOR(PLAYER_COLOR_R, PLAYER_COLOR_G, PLAYER_COLOR_B, PLAYER_COLOR_A);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.fJump = PLAYER_JUMP_MOVE;
	g_Player.fGravity = GRAVITY;
	g_Player.bDirection = false;
	g_Player.bJump = false;
	g_Player.bUse = true;
	g_Player.nCntAnim = 0;
	g_Player.nTexAnim = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE, &g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE_X, g_Player.pos.y - PLAYER_SIZE_Y * 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE_X, g_Player.pos.y - PLAYER_SIZE_Y * 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE_X, g_Player.pos.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = g_Player.col;
	pVtx[1].col = g_Player.col;
	pVtx[2].col = g_Player.col;
	pVtx[3].col = g_Player.col;
	//pVtx[0].col = D3DXCOLOR(0, 0, 0, PLAYER_COLOR_A);
	//pVtx[1].col = D3DXCOLOR(0, 0, 0, PLAYER_COLOR_A);
	//pVtx[2].col = D3DXCOLOR(0, 0, 0, PLAYER_COLOR_A);
	//pVtx[3].col = D3DXCOLOR(0, 0, 0, PLAYER_COLOR_A);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//-----------------------------------------------------------------------------
//	 �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//-----------------------------------------------------------------------------
//	�|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{
	if (g_Player.bUse == true)
	{
		//oldPos�ɑO���pos������
		g_Player.oldPos = g_Player.pos;

		//�ړ�
		if (GetKeyboardPress(DIK_A) == true)		//��
		{
			if (g_Player.pos.x <= 0 - PLAYER_SIZE_X)
			{//���[�ɍs������
				g_Player.pos.x = SCREEN_WIDTH + PLAYER_SIZE_X;
			}

			if (GetKeyboardPress(DIK_D) != true)		
			{//���L�[�������ĂȂ����

				if (g_Player.bJump == true)
				{
					g_Player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_JUMPMOVE_SPEED;
					g_Player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_JUMPMOVE_SPEED;

				}
				else
				{
					g_Player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_MOVE_SPEED;
					g_Player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_MOVE_SPEED;
				}
				g_Player.bDirection = true;//����������
			}
			else
			{
				g_Player.move.x = 0;
			}
		}

		if (GetKeyboardPress(DIK_D) == true)	//��
		{
			if (g_Player.pos.x >= SCREEN_WIDTH + PLAYER_SIZE_X)
			{//�E�[�ɍs������
				g_Player.pos.x = 0 - PLAYER_SIZE_X;
			}

			if (GetKeyboardPress(DIK_A) != true)		
			{//�E�L�[�������ĂȂ����

				if (g_Player.bJump == true)
				{
					g_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_JUMPMOVE_SPEED;
					g_Player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_JUMPMOVE_SPEED;

				}
				else
				{
					g_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_MOVE_SPEED;
					g_Player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_MOVE_SPEED;

				}
				g_Player.bDirection = false;//�������E��
			}
			else
			{
				g_Player.move.x = 0;
			}
		}

		//����(�_�b�V��)
		if (GetKeyboardPress(DIK_M) == true)
		{
			if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_A) == true)
			{
				g_Player.move.x = g_Player.move.x * PLAYER_DASH_SPEED;
			}
		}

		//����(�����x�̂�)
		g_Player.move.x += (0.0f - g_Player.move.x) * PLAYER_MOVE_COEFFICIENT;

		//�d�͉��Z
		g_Player.move.y += g_Player.fGravity;

		//�W�����v
		if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bLand == true || GetKeyboardPress(DIK_W) == true && g_Player.bLand== true)
		{
			g_Player.move.y = -g_Player.fJump;
			PlaySound(SOUND_LABEL_SE_006);
			g_Player.bJump = true;
			g_Player.bLand = false;

		}
		//pos��move�����Z
		g_Player.pos += g_Player.move;

		//�A�j���[�V����
		if (g_Player.bJump == false && g_Player.bLand == true)
		{
			g_Player.nCntAnim = (g_Player.nCntAnim + 1) % PLAYER_ANIM_INTERVAL;
		}
		else
		{//�W�����v��ԂȂ�
			if (g_Player.nTexAnim % 2 == 0)
			{
				g_Player.nTexAnim = (g_Player.nTexAnim + 1) % 4;
			}
		}

		//TexAnim�̍X�V
		if (g_Player.nCntAnim == PLAYER_ANIM_INTERVAL - 1)
		{
			if (GetKeyboardPress(DIK_D) == true && g_Player.move.x != 0 || GetKeyboardPress(DIK_A) == true && g_Player.move.x != 0)
			{//�L�[�������Ă��āA���ړ��ʂ�0�łȂ����
				
				g_Player.nTexAnim = (g_Player.nTexAnim + 1) % 4;
				g_Player.nCntAnim = 0;
			}
			else
			{//�����łȂ����
				if (g_Player.nTexAnim % 2 == 1)
				{
					g_Player.nTexAnim = (g_Player.nTexAnim + 1) % 4;
				}
			}
		}
		//�u���b�N�̓����蔻��
		if (CollisionBlock(&g_Player.pos, &g_Player.oldPos, &g_Player.move) == true)
		{
			g_Player.bJump = false;
			g_Player.bLand = true;
		}
		else
		{
			g_Player.bJump = true;
			g_Player.bLand = false;

		}
		//�A�C�e���̓����蔻��
		CollisionItem();

		/*	pVtx�̍X�V  */

		//�ϐ��錾
		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE_X, g_Player.pos.y - PLAYER_SIZE_Y * 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE_X, g_Player.pos.y - PLAYER_SIZE_Y * 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_SIZE_X, g_Player.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_SIZE_X, g_Player.pos.y, 0.0f);

		pVtx[0].col = g_Player.col;
		pVtx[1].col = g_Player.col;
		pVtx[2].col = g_Player.col;
		pVtx[3].col = g_Player.col;

		//bDirection�ɉ����Č�����ς���
		if (g_Player.bDirection == false)
		{//�E
			pVtx[0].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.0f,  0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.0f,  0.5f);
			pVtx[3].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.25f, 0.5f);
		}
		else
		{//��
			pVtx[0].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.0f,  0.5f);
			pVtx[1].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.0f,  1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_Player.nTexAnim * 0.25f) + 0.25f, 1.0f);
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
}

//-----------------------------------------------------------------------------
//	�|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//�`��
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

		pDevice->SetTexture(0, g_pTexturePlayer);//�e�N�X�`���̐ݒ�

		if (g_Player.bUse == true)
		{//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��			//�v���~�e�B�u == �|���S��
					0,									   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
					2);		   							   //�v���~�e�B�u�̐�
		}										 
}
//-----------------------------------------------------------------------------
//	�v���C���[�ƃA�C�e���̓����蔻��
//-----------------------------------------------------------------------------
void CollisionItem(void)
{
	ITEM *pItem;
	pItem = GetItem();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,pItem++)
	{
		if (pItem->bUse == true)
		{
			//�����蔻��(�v���C���[���d�Ȃ�Ə�����)
			if (g_Player.pos.y - PLAYER_SIZE_Y <= pItem->pos.y + pItem->fHeight&&//����
				g_Player.pos.y - PLAYER_SIZE_Y >= pItem->pos.y - pItem->fHeight&&//�㑤
				g_Player.pos.x <= pItem->pos.x + pItem->fWidth&&				 //�E��
				g_Player.pos.x >= pItem->pos.x - pItem->fWidth)					 //����
			{
				AddScore(pItem->nScore);
				pItem->bDeleteFlag = true;
				
				int nCoinSound = rand() % 2;

				if (nCoinSound == 0)
				{
					PlaySound(SOUND_LABEL_SE_003);
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_004);
				}
			}
		}
	}
}

//=============================================================================
//	�v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}

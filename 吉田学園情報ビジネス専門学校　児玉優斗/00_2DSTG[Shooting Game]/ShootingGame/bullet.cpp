//=============================================================================
//
//					DirectX �e�̔��ˏ���  [bullet.cpp]
//					Author Kodama Yuto
//
//=============================================================================
#include"game.h"

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

Bullet g_aBullet[MAX_BULLET];						//�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE, &g_pTextureBullet);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (4*nCntBullet);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = g_aBullet[nCntBullet].col;
		pVtx[1].col = g_aBullet[nCntBullet].col;
		pVtx[2].col = g_aBullet[nCntBullet].col;
		pVtx[3].col = g_aBullet[nCntBullet].col;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�̗�
		g_aBullet[nCntBullet].nLife = MAX_BULLET_LIFE;

		//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	Player *pPlayer;

	pPlayer = GetPlayer();

	int nCntEnemy;
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{

		//��ʊO�Œe����
		if (g_aBullet[nCntBullet].pos.x < -20 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + 20 ||
			g_aBullet[nCntBullet].pos.y < -20 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT + 20)
		{
			g_aBullet[nCntBullet].bUse = false;
		}

		if (g_aBullet[nCntBullet].bUse == true)//�e���g���Ă�����
		{

			//�G�t�F�N�g�̐ݒu
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.48f, 1.0f, 1.0f), BULLET_SIZE * 1.55f, 10);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY || g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY_HOMING)
			{
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.6f, 0.85f, 0.1f, 1.0f), BULLET_SIZE * 1.5, 10);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_BOSS )
			{
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.7f, 0.4f, 0.95f, 1.0f), BULLET_SIZE * 2, 15);
			}

			ENEMY *pEnemy;
			int nNumEnemy;
			//�G�̎擾
			pEnemy = GetEnemy();
			nNumEnemy = GetNumEnemy();

		//�����蔻��
		if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)//�v���C���[�̒e
		{
			if (nNumEnemy != 0)
			{
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)//�G���g���Ă�����
					{

						if (g_aBullet[nCntBullet].pos.x > pEnemy->pos.x - ENEMY_POLYGON_SIZE - BULLET_SIZE && g_aBullet[nCntBullet].pos.x < pEnemy->pos.x + ENEMY_POLYGON_SIZE + BULLET_SIZE && g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - ENEMY_POLYGON_SIZE - BULLET_SIZE && g_aBullet[nCntBullet].pos.y < pEnemy->pos.y + ENEMY_POLYGON_SIZE + BULLET_SIZE)
						{//����������
							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			else
			{
				BOSS *pBoss;
				pBoss = GetBoss();

				if (pBoss->state == BOSSSTATE_NORMAL)
				{
					if (g_aBullet[nCntBullet].pos.x > pBoss->pos.x - BOSS_POLYGON_SIZE - BULLET_SIZE && g_aBullet[nCntBullet].pos.x < pBoss->pos.x + BOSS_POLYGON_SIZE + BULLET_SIZE && g_aBullet[nCntBullet].pos.y > pBoss->pos.y - BOSS_POLYGON_SIZE - BULLET_SIZE && g_aBullet[nCntBullet].pos.y < pBoss->pos.y + BOSS_POLYGON_SIZE + BULLET_SIZE)
					{//����������
						HitBoss(1);
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}
		}
		else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)//�G�̒e
		{

			if (pPlayer->state == PLAYERSTATE_NORMAL)
			{
				if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - PLAYER_SIZE && g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + PLAYER_SIZE + 0 && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - PLAYER_SIZE - 0 && g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + PLAYER_SIZE + 0)
				{//����������
					HitPlayer(1);
					g_aBullet[nCntBullet].bUse = false;
				}
			}
		}
		else if (g_aBullet[nCntBullet].type == BULLETTYPE_BOSS || g_aBullet[nCntBullet].type == BULLETTYPE_BOSS_OPTION)
		{
			if (pPlayer->state == PLAYERSTATE_NORMAL)
			{

				if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - PLAYER_SIZE - 0 && g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + PLAYER_SIZE + 0 && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - PLAYER_SIZE - 0 && g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + PLAYER_SIZE + 0)
				{//����������
					HitPlayer(1);
					g_aBullet[nCntBullet].bUse = false;
				}
			}
		}
		g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntBullet;

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

		g_aBullet[nCntBullet].nLife--;

			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY || g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY_HOMING)
				{
					SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
				else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
				{
					SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
			}
			else if (g_aBullet[nCntBullet].pos.y <= 0 || g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT || g_aBullet[nCntBullet].pos.x<=0 || g_aBullet[nCntBullet].pos.x>= SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBullet->Unlock();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	// �|���S���̕`��
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
				4*nCntBullet,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							       //�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,D3DXCOLOR col,float angle)
{
	int nCntBullet;
//�ϐ��錾
			VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			if (type == BULLETTYPE_ENEMY || type == BULLETTYPE_ENEMY_HOMING || type == BULLETTYPE_BOSS)
			{
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (4 * nCntBullet);
				g_aBullet[nCntBullet].pos = pos;

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = type;
				g_aBullet[nCntBullet].col = col;
				g_aBullet[nCntBullet].fAngle = angle;

				pVtx[0].col = g_aBullet[nCntBullet].col;
				pVtx[1].col = g_aBullet[nCntBullet].col;
				pVtx[2].col = g_aBullet[nCntBullet].col;
				pVtx[3].col = g_aBullet[nCntBullet].col;

				g_aBullet[nCntBullet].bUse = true;

				g_aBullet[nCntBullet].nLife = MAX_BULLET_LIFE;
				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffBullet->Unlock();


				break;
			}
			else if(type == BULLETTYPE_PLAYER)
			{
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (4 * nCntBullet);
				g_aBullet[nCntBullet].pos = pos;

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = type;
				g_aBullet[nCntBullet].col = col;

				pVtx[0].col = g_aBullet[nCntBullet].col;
				pVtx[1].col = g_aBullet[nCntBullet].col;
				pVtx[2].col = g_aBullet[nCntBullet].col;
				pVtx[3].col = g_aBullet[nCntBullet].col;

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffBullet->Unlock();
				g_aBullet[nCntBullet].bUse = true;

				g_aBullet[nCntBullet].nLife = MAX_BULLET_LIFE;

				PlaySound(SOUND_LABEL_SE_SHOT);//��

				break;
			}
			else if (type == BULLETTYPE_BOSS_OPTION)
			{
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += (4 * nCntBullet);
				g_aBullet[nCntBullet].pos = pos;

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = type;
				g_aBullet[nCntBullet].col = col;

				pVtx[0].col = g_aBullet[nCntBullet].col;
				pVtx[1].col = g_aBullet[nCntBullet].col;
				pVtx[2].col = g_aBullet[nCntBullet].col;
				pVtx[3].col = g_aBullet[nCntBullet].col;

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffBullet->Unlock();
				g_aBullet[nCntBullet].bUse = true;

				g_aBullet[nCntBullet].nLife = MAX_BULLET_LIFE;

				PlaySound(SOUND_LABEL_SE_SHOT);//��

				break;
			}

		}
	}
}

//=============================================================================
// �e�̎擾
//=============================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}

//=============================================================================
//	�I�����e����
//=============================================================================
void BulletErese(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].bUse = false;
	}
}


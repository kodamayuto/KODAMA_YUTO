//=============================================================================
//
//					DirectX �e�̔�������  [Explosion.cpp]
//					Author Kodama Yuto
//
//=============================================================================
#include "Explosion.h"
#include "effect.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;
}Explosion;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

Explosion g_aExplosion[MAX_EXPLOSION];						//�����̏��

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURE, &g_pTextureExplosion);

	// ���_���̍쐬

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);

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
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;

	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{

		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//SetEffect(g_aExplosion[nCntExplosion].pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f), EXPLOSION_SIZE * 1.5, 10);

			g_aExplosion[nCntExplosion].nCounterAnim++;
			if (g_aExplosion[nCntExplosion].nCounterAnim % 5 == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % TEX_PATTERN;
			}
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) +0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 1.0f);

			if (g_aExplosion[nCntExplosion].nPatternAnim >= TEX_PATTERN - 1)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
			else if (g_aExplosion[nCntExplosion].pos.y <= 0)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}

		}
		pVtx += 4;

	}

	// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	// �|���S���̕`��
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //�v���~�e�B�u�̎��		//�v���~�e�B�u == �|���S��
				4*nCntExplosion,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							       //�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
	int nCntExplosion;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{

			g_aExplosion[nCntExplosion].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE, 0.0f);

			g_aExplosion[nCntExplosion].col = col;
			pVtx[0].col = g_aExplosion[nCntExplosion].col;
			pVtx[1].col = g_aExplosion[nCntExplosion].col;
			pVtx[2].col = g_aExplosion[nCntExplosion].col;
			pVtx[3].col = g_aExplosion[nCntExplosion].col;

			g_aExplosion[nCntExplosion].nCounterAnim = 0;

			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);


			g_aExplosion[nCntExplosion].bUse = true;

			SetEffect(g_aExplosion[nCntExplosion].pos, g_aExplosion[nCntExplosion].col + D3DXCOLOR(0.1f,0.1f,0.1f,-0.5f), EXPLOSION_SIZE * 2, 10);
			break;
		}
		pVtx += 4;

	}

	//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffExplosion->Unlock();


}


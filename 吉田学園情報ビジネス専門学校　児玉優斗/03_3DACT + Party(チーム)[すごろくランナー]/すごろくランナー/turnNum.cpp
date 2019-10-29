//=============================================================================
//
// �^�[�������� [turnNum.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "turnNum.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NAME_SCORE  "data/TEXTURE/score.png"      // �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZEX       (100)                         // �e�N�X�`���̃T�C�Y
#define TEXTURE_SIZEY       (100)                         // �e�N�X�`���̃T�C�Y
#define MAX_SCORENUMBER     (8)                           // �^�[�����̌����̍ő�l
#define TURNNUM_POS_X       (200.0f)
#define TURNNUM_POS_Y       (100.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTurnNum(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTurnNum = NULL;   // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTurnNum = NULL;   // ���_�o�b�t�@�ւ̃|�C���^
TurnNum                 g_TurnNum;                  // �^�[�����̏��

//=============================================================================
// ����������
//=============================================================================
void InitTurnNum(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �^�[�����̏���������
	g_TurnNum.pos = D3DXVECTOR3(TURNNUM_POS_X, TURNNUM_POS_Y, 0.0f);  // ���W��������
	g_TurnNum.TexturePos = 1;                                   // �e�N�X�`�����W��������
	g_TurnNum.nScore = 1;                                       // ����������
	g_TurnNum.NumScore = 1;                                     // �X�R�A�̌�����������
	g_TurnNum.Width = TEXTURE_SIZEX;                            // ����������
	g_TurnNum.Height = TEXTURE_SIZEY;                           // ������������

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME_SCORE,
		&g_pTextureTurnNum);

	// ���_���̍쐬
	MakeVertexTurnNum(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTurnNum(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTurnNum != NULL)
	{
		g_pTextureTurnNum->Release();
		g_pTextureTurnNum = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTurnNum != NULL)
	{
		g_pVtxBuffTurnNum->Release();
		g_pVtxBuffTurnNum = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTurnNum(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTurnNum(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTurnNum, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTurnNum);

	// �|���S���̕`��
	for (int nCntScore = 0; nCntScore < g_TurnNum.NumScore; nCntScore++)
	{// �\������X�R�A�̌��������J��Ԃ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntScore * 4,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTurnNum(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (4 * MAX_SCORENUMBER),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTurnNum,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTurnNum->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	for (int nCntScore = 0; nCntScore < MAX_SCORENUMBER; nCntScore++)
	{// �^�[�����̌��������J��Ԃ�
	    // ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_TurnNum.pos.x + sinf(-D3DX_PI * 0.75f) * g_TurnNum.Width, g_TurnNum.pos.y + cosf(-D3DX_PI * 0.75f) * g_TurnNum.Height, g_TurnNum.pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_TurnNum.pos.x + sinf(D3DX_PI * 0.75f) * g_TurnNum.Width, g_TurnNum.pos.y + cosf(D3DX_PI * 0.75f) * g_TurnNum.Height, g_TurnNum.pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_TurnNum.pos.x + sinf(-D3DX_PI * 0.25f) * g_TurnNum.Width, g_TurnNum.pos.y + cosf(-D3DX_PI * 0.25f) * g_TurnNum.Height, g_TurnNum.pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_TurnNum.pos.x + sinf(D3DX_PI * 0.25f) * g_TurnNum.Width, g_TurnNum.pos.y + cosf(D3DX_PI * 0.25f) * g_TurnNum.Height, g_TurnNum.pos.z);

		// ���_�e�N�X�`��
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
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TurnNum.TexturePos), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TurnNum.TexturePos), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TurnNum.TexturePos), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TurnNum.TexturePos), 1.0f);

		pVtx += 4;
		g_TurnNum.pos.x -= TEXTURE_SIZEX + 5.0f;
	}
	g_TurnNum.pos.x = TURNNUM_POS_X;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTurnNum->Unlock();
}
//=============================================================================
// �^�[�����̉��Z
//=============================================================================
void AddTurnNum(int nValue)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;
	g_TurnNum.nScore += nValue;

	if (g_TurnNum.nScore / (int)powf(10.0f, (float)g_TurnNum.NumScore) >= 1)
	{// �����オ����
		g_TurnNum.NumScore++;

	}

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTurnNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < g_TurnNum.NumScore; nCntScore++)
	{// �^�[�����̌��������J��Ԃ�
		g_TurnNum.TexturePos = g_TurnNum.nScore % ((int)powf(10.0f, (float)nCntScore) * 10) / (int)powf(10.0f, (float)nCntScore);
		
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TurnNum.TexturePos), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TurnNum.TexturePos), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TurnNum.TexturePos), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TurnNum.TexturePos), 1.0f);

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTurnNum->Unlock();
}
//=============================================================================
// �^�[�����̎擾
//=============================================================================
int GetTurnNum(void)
{
	return g_TurnNum.nScore;
}
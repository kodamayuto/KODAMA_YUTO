//=============================================================================
//
// �t�H���g���� [gameFont.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "gameFont.h"
#include "game.h"

//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void MakeGameFont(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pvtxBuffFont = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureFont = NULL; //�e�N�X�`���ւ̃|�C���^

LPD3DXFONT	g_pGameFont = NULL;	// �t�H���g�I�u�W�F�N�g
D3DXCOLOR g_FontCol;		//�t�H���g�̐F
char g_FontText[256];	//�t�H���g�̕���[256�ŌŒ�]

RECT g_FontRect = {	//�t�H���g��u���͈�
	900,		// �����x���W
	300,		// �����y���W
	1300,		// �E����x���W
	500			// �E����y���W
};

//=============================================================================
//	����������
//=============================================================================
void InitFont(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��̏�����
	g_FontCol = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	//�t�H���g�̍쐬
	MakeGameFont(pDevice);

	ZeroMemory(&g_FontText, sizeof(char));

	wsprintf(g_FontText, "Y�{�^���Ń}�b�v���[�h\nA�{�^���Ń_�C�X��U��");
	D3DXCreateTextureFromFile(pDevice, FONT_TEXFILE, &g_pTextureFont);


}

//=============================================================================
//	�I������
//=============================================================================
void UninitFont(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureFont != NULL)
	{
		g_pTextureFont->Release();
		g_pTextureFont = NULL;

	}
	//���_�o�b�t�@�̉��
	if (g_pvtxBuffFont != NULL)
	{
		g_pvtxBuffFont->Release();
		g_pvtxBuffFont = NULL;
	}
	//�t�H���g�̉��
	if (g_pGameFont != NULL)
	{
		g_pGameFont->Release();
		g_pGameFont = NULL;
	}

}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdateFont(void)
{

}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawFont(void)
{
	if (GetTurnState() == TURNSTATE_DICE)
	{
		//�ϐ��錾
		LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//�`��
		pDevice->SetStreamSource(0, g_pvtxBuffFont, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetTexture(0, g_pTextureFont);//�e�N�X�`���̐ݒ�

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			0,										//�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   							   //�v���~�e�B�u�̐�


		//�t�H���g�̕`��
		g_pGameFont->DrawText(
			NULL,								// NULL
			g_FontText,						// �`�悷��e�L�X�g
			-1,									// �`�悷�镶����(-1�ŏ�̃e�L�X�g�̕��������擾���Ă����)
			&g_FontRect,						// �`��͈�(��Œ�`����RECT�^�̕ϐ��̃|�C���^������)
			DT_VCENTER | DT_LEFT,				// �`��I�v�V����
			g_FontCol					// �F�w��
		);


	}
}

//=============================================================================
//	�t�H���g�̍쐬
//=============================================================================
void MakeGameFont(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	D3DXCreateFont(
		pDevice,					// �f�o�C�X�̃|�C���^
		48,							// ����
		20,							// ��
		FW_BLACK,					// �t�H���g�̑���
		NULL,						// ����
		FALSE,						// �Α�(TRUE��on,FALSE��off)
		SHIFTJIS_CHARSET,			// �����Z�b�g
		OUT_DEFAULT_PRECIS,			// �o�͐��x(OUT_DEFAULT_PRECIS�ŌŒ�)
		PROOF_QUALITY,				// �����̕i��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~���̃C���f�b�N�X
		TEXT("Meiryo UI"),			// �t�H���g��(�󔒁A�啶�����܂߂Đ��m�ɓ��͂��邱��)
		&g_pGameFont);				// �t�H���g�̃|�C���^

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pvtxBuffFont,
		NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pvtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(870.0f,320.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(1300.0f, 320.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(870.0f, 480.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1300.0f, 480.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pvtxBuffFont->Unlock();

}


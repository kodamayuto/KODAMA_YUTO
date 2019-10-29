//*****************************************************************************
//
//					DirectX ���[�h�I������ [modeSelect.cpp]
//					Author Kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "modeSelect.h"
#include "input.h"
#include "polygon.h"
#include "island.h"
#include "camera.h"
#include "light.h"
#include "sky.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define	SELECTMENU_NUM_POLYGON (5)
#define FADEFONT_A			   (0.06f)

//=============================================================================
//							�v���g�^�C�v�錾
//=============================================================================
void MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice);
void MakeFont(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturemodeSelect[SELECTMENU_NUM_POLYGON] = {}; //�e�N�X�`���ւ̃|�C���^

D3DXCOLOR g_aColormodeSelect;
int g_nSerectMenuX;		//�|�[�Y��ʂł̃��[�h�I��
int g_nSerectMenuY;
bool g_bmodeSelectMenuDisp;		//�|�[�Y��ʂ̕\���E��\��		true == �\��

LPD3DXFONT	pFont = NULL;	// �t�H���g�I�u�W�F�N�g
D3DXCOLOR g_FontColor;		//�t�H���g�̐F
char g_ModeselectText[256];	//�t�H���g�̕���

RECT g_Rect = {					//�t�H���g��u���͈�
	250,		// �����x���W
	580,		// �����y���W
	1230,		// �E����x���W
	720			// �E����y���W
};

//-----------------------------------------------------------------------------
//						   ����������
//-----------------------------------------------------------------------------
void InitModeSelect(void)
{
	InitCamera();
	InitLight();

	InitPolygon();
	//InitMeshCylinder();
	InitIsland();
	InitSky();
	SetPolygon(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGONTYPE_FIELD, 10000.0f, 10000.0f);


	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	g_nSerectMenuX = 0;
	g_nSerectMenuY = 0;
	g_aColormodeSelect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_FontColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_bmodeSelectMenuDisp = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_002, &g_pTexturemodeSelect[0]);
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_003, &g_pTexturemodeSelect[1]);
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_004, &g_pTexturemodeSelect[2]);
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_005, &g_pTexturemodeSelect[3]);
	D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_006, &g_pTexturemodeSelect[4]);
	//D3DXCreateTextureFromFile(pDevice, MODESELECT_TEXTURE_006, &g_pTexturemodeSelect[5]);

	//���_�̍쐬
	MakeVertexSelect(pDevice);

	// �t�H���g�̍쐬
	MakeFont(pDevice);

}

//-----------------------------------------------------------------------------
//						  �I������
//-----------------------------------------------------------------------------
void UninitModeSelect(void)
{
	UninitCamera();
	UninitLight();
	UninitPolygon();
	UninitIsland();
	UninitSky();
	//�e�N�X�`���̔j��
	for (int nCntData = 0; nCntData < SELECTMENU_NUM_POLYGON; nCntData++)
	{
		if (g_pTexturemodeSelect[nCntData] != NULL)
		{
			g_pTexturemodeSelect[nCntData]->Release();
			g_pTexturemodeSelect[nCntData] = NULL;

		}

	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;

	}

	//�t�H���g�̃|�C���^�̔j��
	if (pFont != NULL)
	{
		pFont->Release();
		pFont = NULL;

	}

}

//-----------------------------------------------------------------------------
//							�X�V����
//-----------------------------------------------------------------------------
void UpdateModeSelect(void)
{
	UpdateCamera();
	UpdateLight();

	UpdatePolygon();
	UpdateIsland();
	UpdateSky();
	
	//���[�h�I��
	if (GetKeyboardTrigger(DIK_A) == true || GetJoyPadTrigger(DIJS_BUTTON_21, 0) == true && g_bmodeSelectMenuDisp == true)//��
	{
		g_nSerectMenuX = (g_nSerectMenuX + 1) % 2;//0��2��1��0
		g_FontColor.a = 0.0f;
		PlaySound(SOUND_LABEL_SE002);
	}
	else if (GetKeyboardTrigger(DIK_D) == true || GetJoyPadTrigger(DIJS_BUTTON_20, 0) == true && g_bmodeSelectMenuDisp == true)//��
	{
		g_nSerectMenuX = (g_nSerectMenuX + 1) % 2;//0��1��2��0
		g_FontColor.a = 0.0f;
		PlaySound(SOUND_LABEL_SE002);

	}

	if (GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(DIJS_BUTTON_18, 0) == true && g_bmodeSelectMenuDisp == true)
	{
		if (g_nSerectMenuY == 0)
		{
			g_nSerectMenuY = 2;

		}
		else if (g_nSerectMenuY == 2)
		{
			g_nSerectMenuY = 0;

		}
		g_FontColor.a = 0.0f;
		PlaySound(SOUND_LABEL_SE002);
	}
	else if (GetKeyboardTrigger(DIK_S) == true || GetJoyPadTrigger(DIJS_BUTTON_19, 0) == true && g_bmodeSelectMenuDisp == true)//��
	{
		if (g_nSerectMenuY == 0)
		{
			g_nSerectMenuY = 2;

		}
		else if (g_nSerectMenuY == 2)
		{
			g_nSerectMenuY = 0;

		}
		g_FontColor.a = 0.0f;
		PlaySound(SOUND_LABEL_SE002);
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE || GetJoyPadTrigger(DIJS_BUTTON_1, 0) == true && GetFade() == FADE_NONE)
	{//�������Ƃ���g_nSerectmodeSelectMenu�̈ʒu�ɉ����ċ��������߂�
		PlaySound(SOUND_LABEL_SE000);
		switch (g_nSerectMenuX + g_nSerectMenuY)
		{
		case 0://�Q�[��
			SetFade(MODE_GAME);
			break;
		case 1://�`���[�g���A��
			SetFade(MODE_TUTORIAL);
			break;
		case 2://�����L���O
			SetFade(MODE_RANKING);
			SetRankingOld(RANKINGOLD_SELECT);

			break;
		case 3://�^�C�g��
			SetFade(MODE_TITLE);

			break;
		}
		//DispReset();
		//SerectReset();

	}
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	for (int nCntmodeSelectPolygon = 1; nCntmodeSelectPolygon < SELECTMENU_NUM_POLYGON; nCntmodeSelectPolygon++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntmodeSelectPolygon;

		pVtx[0].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffSelect->Unlock();

	}
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * ((g_nSerectMenuX + g_nSerectMenuY) + 1);

	pVtx[0].col = g_aColormodeSelect;
	pVtx[1].col = g_aColormodeSelect;
	pVtx[2].col = g_aColormodeSelect;
	pVtx[3].col = g_aColormodeSelect;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();


	//���l�ɉ����ĕ`�悷�镶��������߂�
	switch (GetNumber())
	{
	case 0:
		wsprintf(g_ModeselectText, "mode �Q�[�� : �Q�[�����J�n���܂�");
		break;
	case 1:
		wsprintf(g_ModeselectText, "mode �`���[�g���A�� : ����������J���܂�");
		break;
	case 2:
		wsprintf(g_ModeselectText, "mode �����L���O : ����܂ł̐�т�\�����܂�");
		break;
	case 3:
		wsprintf(g_ModeselectText, "mode �^�C�g�� : �^�C�g���ɖ߂�܂�");
		break;
	}

	//�����̃t�F�[�h
	if (g_FontColor.a <= 1.0f)
	{
		g_FontColor.a += FADEFONT_A;

	}
	else
	{
		g_FontColor.a = 1.0f;

	}

}

//-----------------------------------------------------------------------------
//							�`�揈��
//-----------------------------------------------------------------------------
void DrawModeSelect(void)
{
	SetCamera();

	DrawPolygon();
	DrawIsland();
	DrawSky();
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�`��
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	if (g_bmodeSelectMenuDisp == true)
	{
		//�|���S���̕`��
		for (int nCntmodeSelectPolygon = 0; nCntmodeSelectPolygon < SELECTMENU_NUM_POLYGON; nCntmodeSelectPolygon++)
		{
			pDevice->SetTexture(0, g_pTexturemodeSelect[nCntmodeSelectPolygon]);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntmodeSelectPolygon,				   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							   //�v���~�e�B�u�̐�

		}

	}

	//�t�H���g�̕`��
	pFont->DrawText(
		NULL,								// NULL
		g_ModeselectText,					// �`�悷��e�L�X�g
		-1,									// �`�悷�镶����(-1�Ńe�L�X�g�̕��������擾���Ă����)
		&g_Rect,							// �`��͈�(��Œ�`����RECT�^�̕ϐ��̃|�C���^������)
		DT_VCENTER | DT_LEFT,				// �`��I�v�V����
		g_FontColor							// �F�w��
	);

}
//-----------------------------------------------------------------------------
//						���_�̍쐬
//-----------------------------------------------------------------------------
void MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

									//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SELECTMENU_NUM_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	/*�o�b�N�X�N���[��*/
	//���_���W
	//pVtx[0].pos = D3DXVECTOR3(MODESELECT_POS_X, MODESELECT_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(MODESELECT_WIDTH, MODESELECT_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(MODESELECT_POS_X, MODESELECT_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(MODESELECT_WIDTH, MODESELECT_HEIGHT, 0.0f);
	//
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;
	//
	////���_�J���[	��
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, MODESELECT_COL_A);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, MODESELECT_COL_A);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, MODESELECT_COL_A);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, MODESELECT_COL_A);
	////�e�N�X�`�����W
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//
	//pVtx += 4;

	/*�����ӂ�����*/
	pVtx[0].pos = D3DXVECTOR3(150, 580, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1130, 580, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(150, 720, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1130, 720, 0.0f);

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
	pVtx += 4;


	/*�|�[�YUI*/
	for (int nCntmodeSelectPolygon = 0; nCntmodeSelectPolygon < 4; nCntmodeSelectPolygon++)
	{

		pVtx[0].pos = D3DXVECTOR3(80.0f + (650.0f * (nCntmodeSelectPolygon % 2)), 40.0f + (300.0f * (nCntmodeSelectPolygon / 2)), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(550.0f + (650.0f * (nCntmodeSelectPolygon % 2)), 40.0f + (300.0f * (nCntmodeSelectPolygon / 2)), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(80.0f + (650.0f * (nCntmodeSelectPolygon % 2)), 250.0f + (300.0f * (nCntmodeSelectPolygon / 2)), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(550.0f + (650.0f * (nCntmodeSelectPolygon % 2)), 250.0f + (300.0f * (nCntmodeSelectPolygon / 2)), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();

}
//-----------------------------------------------------------------------------
//						�t�H���g�̍쐬
//-----------------------------------------------------------------------------
void MakeFont(LPDIRECT3DDEVICE9 pDevice)
{
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
		&pFont);					// �t�H���g�̃|�C���^

}

//=============================================================================
//		�I���̏�����
//=============================================================================
void SerectReset(void)
{
	g_nSerectMenuX = 0;
	g_nSerectMenuY = 0;

}

//=============================================================================
//		�\����Ԃ̏�����
//=============================================================================
void DispReset(void)
{
	g_bmodeSelectMenuDisp = true;

}

//=============================================================================
//		�f�o�b�N�p�����\��
//=============================================================================
int GetNumber(void)
{
	return (g_nSerectMenuX + g_nSerectMenuY);
}
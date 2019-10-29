//*****************************************************************************
//
//					DirectX �|�[�Y���� [pause.cpp]
//					Author Kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define	PAUSEMENU_NUM_POLYGON (4)

//=============================================================================
//							�v���g�^�C�v�錾
//=============================================================================
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSEMENU_NUM_POLYGON] = {}; //�e�N�X�`���ւ̃|�C���^

D3DXCOLOR g_aColorPause;
int g_nSerectPauseMenu;		//�|�[�Y��ʂł̃��[�h�I��
bool g_bPauseMenuDisp;		//�|�[�Y��ʂ̕\���E��\��		true == �\��

//-----------------------------------------------------------------------------
//						   �|�[�Y��ʂ̏���������
//-----------------------------------------------------------------------------
void InitPause(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾
	
	pDevice = GetDevice();

	//������
	g_nSerectPauseMenu = 0;
	g_aColorPause = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	g_bPauseMenuDisp = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURE_001,&g_pTexturePause[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURE_002, &g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURE_003, &g_pTexturePause[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURE_004, &g_pTexturePause[3]);

	//���_�̍쐬
	MakeVertexPause(pDevice);

}

//-----------------------------------------------------------------------------
//						   �|�[�Y��ʂ̏I������
//-----------------------------------------------------------------------------
void UninitPause(void)
{
	//�e�N�X�`���̔j��
	for (int nCntData = 0; nCntData < PAUSEMENU_NUM_POLYGON; nCntData++)
	{
		if (g_pTexturePause[nCntData] != NULL)
		{
			g_pTexturePause[nCntData]->Release();
			g_pTexturePause[nCntData] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//-----------------------------------------------------------------------------
//							�|�[�Y��ʂ̍X�V����
//-----------------------------------------------------------------------------
void UpdatePause(void)
{
	FADE *pFade;
	pFade = GetFade();

	//�|�[�Y��ʂ̕\���E��\��
	if (GetKeyboardTrigger(DIK_O) == true)
	{
		g_bPauseMenuDisp = g_bPauseMenuDisp ? false : true;
		SerectReset();

	}
	//���[�h�I��
	if (GetKeyboardTrigger(DIK_W) == true && g_bPauseMenuDisp == true)//��
	{
		g_nSerectPauseMenu = (g_nSerectPauseMenu + 1) % 2;//0��1��0
		PlaySound(SOUND_LABEL_SE_001);
	}
	else if (GetKeyboardTrigger(DIK_S) == true && g_bPauseMenuDisp == true)//��
	{
		g_nSerectPauseMenu = (g_nSerectPauseMenu + 1) % 2;//0��1��0
		PlaySound(SOUND_LABEL_SE_001);
	}


	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//�������Ƃ���g_nSerectPauseMenu�̈ʒu�ɉ����ċ��������߂�
		switch (g_nSerectPauseMenu)
		{
		case 0://�ĊJ
			PauseModeChange();
			PlaySound(SOUND_LABEL_SE_002);
			break;
		case 1://�I��
			if (*pFade != FADE_OUT)
			{
				SetFade(MODE_TITLE);
				StopSound(SOUND_LABEL_BGM001);
				PlaySound(SOUND_LABEL_SE_000);
			}
			break;
		}

		DispReset();
	}
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	for (int nCntPausePolygon = 2; nCntPausePolygon < PAUSEMENU_NUM_POLYGON; nCntPausePolygon++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntPausePolygon;

		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPause->Unlock();
	}
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * (g_nSerectPauseMenu + 2);

	pVtx[0].col = g_aColorPause;
	pVtx[1].col = g_aColorPause;
	pVtx[2].col = g_aColorPause;
	pVtx[3].col = g_aColorPause;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

}

//-----------------------------------------------------------------------------
//							�|�[�Y��ʂ̕`�揈��
//-----------------------------------------------------------------------------
void DrawPause(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�`��
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	if (g_bPauseMenuDisp == true)
	{
		//�|���S���̕`��
		for (int nCntPausePolygon = 0; nCntPausePolygon < PAUSEMENU_NUM_POLYGON; nCntPausePolygon++)
		{
			pDevice->SetTexture(0, g_pTexturePause[nCntPausePolygon]);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntPausePolygon,				   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							   //�v���~�e�B�u�̐�

		}
	}
												
}
//-----------------------------------------------------------------------------
//						�|�[�Y��ʂ̒��_�̍쐬
//-----------------------------------------------------------------------------
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSEMENU_NUM_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	/*�o�b�N�X�N���[��*/
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);
	
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	//���_�J���[	��
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	pVtx += 4;

	/*�������*/
	pVtx[0].pos = D3DXVECTOR3(PAUSE_WIDTH-750, PAUSE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSE_WIDTH-750, PAUSE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);

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
	for (int nCntPausePolygon = 0; nCntPausePolygon < 2; nCntPausePolygon++)
	{

		pVtx[0].pos = D3DXVECTOR3(50, 140.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(480, 140.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50, 190.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(480, 190.0f + (250 * nCntPausePolygon), 0.0f);

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
	g_pVtxBuffPause->Unlock();

}
//=============================================================================
//		�I���̏�����
//=============================================================================
void SerectReset(void)
{
	g_nSerectPauseMenu = 0;	
}

//=============================================================================
//		�\����Ԃ̏�����
//=============================================================================
void DispReset(void)
{
	g_bPauseMenuDisp = true;
}
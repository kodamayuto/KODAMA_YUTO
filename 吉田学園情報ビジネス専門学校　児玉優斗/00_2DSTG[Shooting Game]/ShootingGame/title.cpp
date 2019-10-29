//*****************************************************************************
//
//					DirectX �^�C�g������ [result.cpp]
//					Author Kodama Yuto
//(:3 )�O
//****************************************************************************
//�C���N���[�h�t�@�C��
#include "title.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//							�}�N����`
//=============================================================================
#define MAX_TEXTURE (5)

//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEXTURE] = {};	               //�e�N�X�`���ւ̃|�C���^

int g_nCounterTitle = 0;
bool g_bEnterDispTitle = true;
//-----------------------------------------------------------------------------
//						   �w�i�̏���������
//-----------------------------------------------------------------------------
void InitTitle(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_100  , &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_101  , &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_102  , &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE      , &g_pTextureTitle[3]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_ENTER, &g_pTextureTitle[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	g_nCounterTitle = 0;

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntTex;

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTitle->Unlock();
	}
	//title
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * 3;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(200, 100, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1080, 100, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(200, 200, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1080, 200, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//ENTER
	pVtx += 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(400, 500, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(880, 500, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400, 550, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(880, 550, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM000);//��
}

//-----------------------------------------------------------------------------
//						   �w�i�̏I������
//-----------------------------------------------------------------------------

void UninitTitle(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//-----------------------------------------------------------------------------
//							�w�i�̍X�V����
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	FADE *pFade;
	pFade = GetFade();


	g_nCounterTitle++;
	if (g_nCounterTitle % 40 == 0 || *pFade == FADE_OUT && g_nCounterTitle % 3 == 0)
	{
		g_bEnterDispTitle = g_bEnterDispTitle ? false : true;
	}
	//title<-->ranking�̑J��
	if (g_nCounterTitle % 1000 == 0)
	{
		SetFade(MODE_RANKING);
	}

	//ENTER�L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (*pFade != FADE_OUT)
		{
			StopSound(SOUND_LABEL_BGM000);
			PlaySound(SOUND_LABEL_SE_DECIDE);//��

			SetFade(MODE_TUTORIAL);
		}
		
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.002f * -g_nCounterTitle + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.002f * -g_nCounterTitle + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.002f * -g_nCounterTitle + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.002f * -g_nCounterTitle + 1.0f);

	pVtx += 4;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.004f * -g_nCounterTitle + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.004f * -g_nCounterTitle + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.004f * -g_nCounterTitle + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.004f * -g_nCounterTitle + 1.0f);

	pVtx += 4;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.007f * -g_nCounterTitle + 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.007f * -g_nCounterTitle + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.007f * -g_nCounterTitle + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.007f * -g_nCounterTitle + 1.0f);

	g_pVtxBuffTitle->Unlock();

}

//-----------------------------------------------------------------------------
//							�w�i�̕`�揈��
//-----------------------------------------------------------------------------

void DrawTitle(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�`��
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (nCntTex != 4 || nCntTex == 4 && g_bEnterDispTitle == true)
		{
			pDevice->SetTexture(0, g_pTextureTitle[nCntTex]);//�e�N�X�`���̐ݒ�

												 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}
	}
}


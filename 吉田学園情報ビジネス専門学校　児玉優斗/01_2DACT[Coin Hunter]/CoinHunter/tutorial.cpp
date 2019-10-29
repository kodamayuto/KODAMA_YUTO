//*****************************************************************************
//
//					DirectX �^�C�g������ [tutorial.cpp]
//					Author Kodama Yuto
//	(:3 )�O
//****************************************************************************
//�C���N���[�h�t�@�C��
#include "tutorial.h"
#include "fade.h"

//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTutorial[5] = {};	                //�e�N�X�`���ւ̃|�C���^

int g_CounterTutorial = 0;
bool g_bEnterDispTutorial = true;
int g_nTutorialChange = 0;

//-----------------------------------------------------------------------------
//						   �w�i�̏���������
//-----------------------------------------------------------------------------
void InitTutorial(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	g_nTutorialChange = 0;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE, &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_2, &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_3, &g_pTextureTutorial[2]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_ENTER, &g_pTextureTutorial[3]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_START, &g_pTextureTutorial[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, TUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);

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

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(920, 120, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1170, 120, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(920, 160, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1170, 160, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

}

//-----------------------------------------------------------------------------
//						   �w�i�̏I������
//-----------------------------------------------------------------------------

void UninitTutorial(void)
{

	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_pTextureTutorial[nCntTex] != NULL)
		{
			g_pTextureTutorial[nCntTex]->Release();
			g_pTextureTutorial[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}

//-----------------------------------------------------------------------------
//							�w�i�̍X�V����
//-----------------------------------------------------------------------------
void UpdateTutorial(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_CounterTutorial++;
	if (g_CounterTutorial % 40 == 0 || *pFade == FADE_OUT && g_CounterTutorial % 3 == 0)
	{
		g_bEnterDispTutorial = g_bEnterDispTutorial ? false : true;
	}

	//ENTER�L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_nTutorialChange < 2)
		{
			g_nTutorialChange++;
			PlaySound(SOUND_LABEL_SE_001);
		}
		else
		{
			if (*pFade != FADE_OUT)
			{

				StopSound(SOUND_LABEL_BGM000);
				PlaySound(SOUND_LABEL_SE_000);
				PlaySound(SOUND_LABEL_BGM001);
				SetFade(MODE_CHANGE);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//							�w�i�̕`�揈��
//-----------------------------------------------------------------------------

void DrawTutorial(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�`��
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (nCntTex != 1)
		{
			if (g_nTutorialChange == 0)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[0]);//�e�N�X�`���̐ݒ�

			}
			else if(g_nTutorialChange == 1)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[1]);//�e�N�X�`���̐ݒ�

			}
			else if (g_nTutorialChange == 2)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[2]);//�e�N�X�`���̐ݒ�

			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�

		}
		else if (nCntTex == 1 && g_bEnterDispTutorial == true)
		{
			if (g_nTutorialChange < 2)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[3]);//�e�N�X�`���̐ݒ�
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureTutorial[4]);//�e�N�X�`���̐ݒ�
			}
		

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
		}
	}
}


//*****************************************************************************
//
//					DirectX ���_�o�b�t�@ [bg.cpp]
//						Author Kodama Yuto
//
//*****************************************************************************
#include "bg.h"

//=============================================================================
//								�}�N����`
//=============================================================================
#define MAX_BG_TEXTURE (3)

//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBG[MAX_BG_TEXTURE] = {};	                    //�e�N�X�`���ւ̃|�C���^

int g_nCounterBG = 0;
//-----------------------------------------------------------------------------
//						   �w�i�̏���������
//-----------------------------------------------------------------------------
void InitBG(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾
	
	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	g_nCounterBG = 0;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE,&g_pTextureBG[0]);
	D3DXCreateTextureFromFile(pDevice, BG_MOUNTEN_TEXTURE, &g_pTextureBG[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_001, &g_pTextureBG[2]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

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
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, 500, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 500, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

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
	g_pVtxBuffBG->Unlock();
}

//-----------------------------------------------------------------------------
//						   �w�i�̏I������
//-----------------------------------------------------------------------------
void UninitBG(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_BG_TEXTURE; nCntTex++)
	{
		if (g_pTextureBG[nCntTex] != NULL)
		{
			g_pTextureBG[nCntTex]->Release();
			g_pTextureBG[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//-----------------------------------------------------------------------------
//							�w�i�̍X�V����
//-----------------------------------------------------------------------------
void UpdateBG(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	g_nCounterBG++;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(0.00005f * -g_nCounterBG + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.00005f * -g_nCounterBG + 0.25f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.00005f * -g_nCounterBG + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.00005f * -g_nCounterBG + 0.25f,1.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();

}

//-----------------------------------------------------------------------------
//							�w�i�̕`�揈��
//-----------------------------------------------------------------------------
void DrawBG(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�`��
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	switch (GetNumStage())
	{
	case 0:
		for (int nCntTex = 0; nCntTex < 2; nCntTex++)
		{

			pDevice->SetTexture(0, g_pTextureBG[nCntTex]);//�e�N�X�`���̐ݒ�

														  //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�			
		}

		break;
	case 1:
		for (int nCntTex = 0; nCntTex < 1; nCntTex++)
		{

			pDevice->SetTexture(0, g_pTextureBG[nCntTex]);//�e�N�X�`���̐ݒ�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�			
		}
		break;
	case 2:
		for (int nCntTex = 0; nCntTex < 2; nCntTex++)
		{

			pDevice->SetTexture(0, g_pTextureBG[nCntTex]);//�e�N�X�`���̐ݒ�

														  //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�			
		}
		break;
	case 3:
		pDevice->SetTexture(0, g_pTextureBG[2]);//�e�N�X�`���̐ݒ�

													  //�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			0,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�	
		break;
	case 4:
		pDevice->SetTexture(0, g_pTextureBG[2]);//�e�N�X�`���̐ݒ�

												//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			0,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�	

		pDevice->SetTexture(0, g_pTextureBG[1]);//�e�N�X�`���̐ݒ�

												//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			4,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�	

		break;

	}
}


//*****************************************************************************
//
//					DirectX �X�e�[�W���� [stage_change.cpp]
//					Author Kodama Yuto
//	(:3 )�O
//****************************************************************************
//�C���N���[�h�t�@�C��
#include "stage_change.h"
#include "fade.h"

//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChange = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureChange[3] = {};	                //�e�N�X�`���ւ̃|�C���^

int g_CounterChange = 0;

//-----------------------------------------------------------------------------
//						   �w�i�̏���������
//-----------------------------------------------------------------------------
void InitChange(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	int nNumStage;

	nNumStage = GetNumStage() + 1;

	g_CounterChange = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CHANGE_TEXTURE_1, &g_pTextureChange[0]);
	D3DXCreateTextureFromFile(pDevice, CHANGE_TEXTURE_2, &g_pTextureChange[1]);
	D3DXCreateTextureFromFile(pDevice, CHANGE_TEXTURE_3, &g_pTextureChange[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffChange,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffChange->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(200, 160, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(800, 160, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(200, 360, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(800, 360, 0.0f);

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

	pVtx[0].pos = D3DXVECTOR3(850, 180, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(940, 180, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(850, 360, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(940, 360, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2((0.1f * nNumStage) + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((0.1f * nNumStage) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((0.1f * nNumStage) + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((0.1f * nNumStage) + 0.1f, 1.0f);

	pVtx += 4;
	pVtx[0].pos = D3DXVECTOR3(200, 460, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1000, 460, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(200, 660, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1000, 660, 0.0f);

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
	g_pVtxBuffChange->Unlock();

}

//-----------------------------------------------------------------------------
//						   �w�i�̏I������
//-----------------------------------------------------------------------------

void UninitChange(void)
{

	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (g_pTextureChange[nCntTex] != NULL)
		{
			g_pTextureChange[nCntTex]->Release();
			g_pTextureChange[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffChange != NULL)
	{
		g_pVtxBuffChange->Release();
		g_pVtxBuffChange = NULL;
	}
}

//-----------------------------------------------------------------------------
//							�w�i�̍X�V����
//-----------------------------------------------------------------------------
void UpdateChange(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_CounterChange++;

		if (*pFade != FADE_OUT && g_CounterChange >= CHANGE_INTERVAL)
		{
			SetFade(MODE_GAME);
		}
}

//-----------------------------------------------------------------------------
//							�w�i�̕`�揈��
//-----------------------------------------------------------------------------

void DrawChange(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�`��
	pDevice->SetStreamSource(0, g_pVtxBuffChange, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
			pDevice->SetTexture(0, g_pTextureChange[nCntTex]);//�e�N�X�`���̐ݒ�

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntTex,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   	       //�v���~�e�B�u�̐�
	}
}


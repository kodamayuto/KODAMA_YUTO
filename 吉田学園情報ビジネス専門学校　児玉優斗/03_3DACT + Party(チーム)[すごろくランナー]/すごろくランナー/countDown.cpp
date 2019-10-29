//=============================================================================
//
// �J�E���g�_�E������ [countDown.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "countDown.h"
#include "game.h"
#include "meter.h"

//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void MakeVertexCountDown(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCountDown = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCountDown = NULL;						//�e�N�X�`���ւ̃|�C���^

int g_nCountDown = 0;			//�J�E���g�_�E���̐���
int g_nCntNumber = 0;			//�J�E���^�[

bool g_bCountDownFlag = false;	//�J�E���g�_�E���̕\��

//=============================================================================
//	����������
//=============================================================================
void InitCountDown(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
		
	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, COUNTDOWN_TEXTURE_FIRENAME, &g_pTextureCountDown);

	//���_���̐ݒ�
	MakeVertexCountDown(pDevice);
}

//=============================================================================
//	�I������
//=============================================================================
void UninitCountDown(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureCountDown != NULL)
	{
		g_pTextureCountDown->Release();
		g_pTextureCountDown = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCountDown != NULL)
	{
		g_pVtxBuffCountDown->Release();
		g_pVtxBuffCountDown = NULL;
	}

}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdateCountDown(void)
{
	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^
		
	if (g_bCountDownFlag == true)
	{//�J�E���g�_�E�����n�܂��Ă�����
		g_nCntNumber++;
		if (g_nCntNumber % 60 == 59)
		{
			g_nCountDown--;
		}

		if (g_nCountDown == 0)
		{
			g_bCountDownFlag = false;
			SetTurnState(TURNSTATE_MOVEandATTACK);
		}

	}
	//���_���̍X�V
	g_pVtxBuffCountDown->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(1.0f, (g_nCountDown - 1) * 0.25f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, (g_nCountDown - 1) * 0.25f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, (g_nCountDown - 1) * 0.25f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, (g_nCountDown - 1) * 0.25f, 0.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2((g_nCountDown) * 0.2f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_nCountDown + 1) * 0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((g_nCountDown) * 0.2f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2((g_nCountDown + 1) * 0.2f, 0.5f);


	g_pVtxBuffCountDown->Unlock();

}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawCountDown(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�`��
	if (g_bCountDownFlag == true)
	{
		pDevice->SetStreamSource(0, g_pVtxBuffCountDown, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

		for (int nCntCountDown = 0; nCntCountDown < MAX_POLYGON_METER; nCntCountDown++)
		{
			pDevice->SetTexture(0, g_pTextureCountDown);//�e�N�X�`���̐ݒ�

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
				4 * nCntCountDown,									   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
				2);		   							   //�v���~�e�B�u�̐�
		}

	}

}

//=============================================================================
//	���_�̐ݒ�
//=============================================================================
void MakeVertexCountDown(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCountDown,
		NULL);

	//���_���̏����ݒ�
	g_pVtxBuffCountDown->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(520.0f, 200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(720.0f, 200.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(520.0f, 400.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(720.0f, 400.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	

	g_pVtxBuffCountDown->Unlock();

}
//=============================================================================
//	�J�E���g�_�E���̐ݒ菈��
//=============================================================================
void SetCountDown(void)
{
	g_nCountDown = 3;
	g_nCntNumber = 0;
	g_bCountDownFlag = true;
}
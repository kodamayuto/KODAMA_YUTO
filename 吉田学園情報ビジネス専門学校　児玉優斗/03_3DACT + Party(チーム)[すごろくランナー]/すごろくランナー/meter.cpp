//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "meter.h"
#include "game.h"
#include "timer.h"

//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeter(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeter = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeter[MAX_POLYGON_METER] = {};						//�e�N�X�`���ւ̃|�C���^

int g_nCntMeter;			//���[�^�[�̌����J�E���g
float g_fMeterSize;			//���[�^�[�̒���

							//=============================================================================
							//	����������
							//=============================================================================
void InitMeter(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ�������
	g_nCntMeter = 0;
	g_fMeterSize = METER_SIZE_MAX;

	D3DXCreateTextureFromFile(pDevice, METER_TEXTURE_FIRENAME0, &g_pTextureMeter[0]);
	D3DXCreateTextureFromFile(pDevice, METER_TEXTURE_FIRENAME, &g_pTextureMeter[1]);

	//���_���̐ݒ�
	MakeVertexMeter(pDevice);
}

//=============================================================================
//	�I������
//=============================================================================
void UninitMeter(void)
{
	//�e�N�X�`���̔j��
	for (int nCntMeter = 0; nCntMeter < MAX_POLYGON_METER; nCntMeter++)
	{

		if (g_pTextureMeter[nCntMeter] != NULL)
		{
			g_pTextureMeter[nCntMeter]->Release();
			g_pTextureMeter[nCntMeter] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeter != NULL)
	{
		g_pVtxBuffMeter->Release();
		g_pVtxBuffMeter = NULL;
	}

}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdateMeter(void)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	TURNSTATE pTstate;
	pTstate = GetTurnState();
	if (GetTimer() != -1 && GetSetTimerFlag() == true && pTstate == TURNSTATE_MOVEandATTACK)
	{//�^�C�}�[�������Ă���Ƃ��������[�^�[�𓮂���
		g_nCntMeter++;

		if (g_nCntMeter % 30 == 29 && g_fMeterSize >= METER_SIZE_MIN)
		{
			g_fMeterSize -= METER_MOVE;
		}
	}
	else
	{
		g_nCntMeter = 0;
	}

	//���_���̍X�V
	g_pVtxBuffMeter->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(METER_SIZE_MIN, 5.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fMeterSize, 5.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(METER_SIZE_MIN, 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fMeterSize, 100.0f, 0.0f);

	if (g_fMeterSize > (METER_SIZE_MAX + METER_SIZE_MIN) / 2)
	{

		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.8f);
	}
	else if (g_fMeterSize - METER_SIZE_MIN < (METER_SIZE_MAX - METER_SIZE_MIN) / 4)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);

	}
	else
	{

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);

	}
	g_pVtxBuffMeter->Unlock();
}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawMeter(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�`��

	pDevice->SetStreamSource(0, g_pVtxBuffMeter, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	for (int nCntMeter = 0; nCntMeter < MAX_POLYGON_METER; nCntMeter++)
	{
		pDevice->SetTexture(0, g_pTextureMeter[nCntMeter]);//�e�N�X�`���̐ݒ�

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			4 * nCntMeter,									   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   							   //�v���~�e�B�u�̐�

	}

}

//=============================================================================
//	���_�̐ݒ�
//=============================================================================
void MakeVertexMeter(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

									//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON_METER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeter,
		NULL);

	//���_���̏����ݒ�
	g_pVtxBuffMeter->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(400.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(500.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400.0f, 200.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(METER_SIZE_MIN - 20.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_fMeterSize + 20.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(METER_SIZE_MIN - 20.0f, 110.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_fMeterSize + 20.0f, 110.0f, 0.0f);

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


	g_pVtxBuffMeter->Unlock();

}
//=============================================================================
//	���[�^�[�T�C�Y�̎擾
//=============================================================================
float GetMeterSize(void)
{
	return g_fMeterSize - METER_SIZE_MIN;
}
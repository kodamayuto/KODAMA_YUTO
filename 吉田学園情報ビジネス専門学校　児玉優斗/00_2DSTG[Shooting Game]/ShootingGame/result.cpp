//*****************************************************************************
//
//					DirectX �^�C�g������ [result.cpp]
//					Author Kodama Yuto
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "result.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//							�O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResult[3] = {};	                    //�e�N�X�`���ւ̃|�C���^

int g_CounterEnter = 0;
bool g_bEnterDisp = false;
//-----------------------------------------------------------------------------
//						   �w�i�̏���������
//-----------------------------------------------------------------------------
void InitResult(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	g_CounterEnter = 0;
	g_bEnterDisp = false;
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURE_LOSE, &g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURE_WIN, &g_pTextureResult[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURE_ENTER, &g_pTextureResult[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);



	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

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
	pVtx[0].pos = D3DXVECTOR3(400, 500, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(880, 500, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(400, 600, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(880, 600, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	PlaySound(SOUND_LABEL_BGM002);//��

}

//-----------------------------------------------------------------------------
//						   �w�i�̏I������
//-----------------------------------------------------------------------------
void UninitResult(void)
{
	//�e�N�X�`���̔j��
	for (int nCntData = 0; nCntData < 3; nCntData++)
	{
		if (g_pTextureResult[nCntData] != NULL)
		{
			g_pTextureResult[nCntData] ->Release();
			g_pTextureResult[nCntData] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//-----------------------------------------------------------------------------
//							�w�i�̍X�V����
//-----------------------------------------------------------------------------
void UpdateResult(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_CounterEnter++;
	if (g_CounterEnter % 40 == 0 && g_CounterEnter >= 90 ||*pFade ==FADE_OUT && g_CounterEnter % 3 == 0)
	{
		g_bEnterDisp = g_bEnterDisp ? false : true;
	}

	//ENTER�L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{

		if (*pFade != FADE_OUT)
		{
			SetFade(MODE_RANKING);
		}
	}
}

//-----------------------------------------------------------------------------
//							�w�i�̕`�揈��
//-----------------------------------------------------------------------------
void DrawResult(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer;
	BOSS *pBoss;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�`��
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	pPlayer = GetPlayer();
	pBoss = GetBoss();
	if (pPlayer->bDisp == false)
	{
		pDevice->SetTexture(0, g_pTextureResult[0]);//�e�N�X�`���̐ݒ�
													//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			0,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�

	}
	else
	{
		pDevice->SetTexture(0, g_pTextureResult[1]);//�e�N�X�`���̐ݒ�
													//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			0,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�

	}

	if (g_bEnterDisp == true)
	{
		pDevice->SetTexture(0, g_pTextureResult[2]);//�e�N�X�`���̐ݒ�

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			4,					   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   	       //�v���~�e�B�u�̐�

	}
}


//=============================================================================
//
// �t���[���̏��� [frame.cpp]
// Author :�@Jukiya Hayakawa
//
//=============================================================================
#include "frame.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FRAME_TEXTURE_NAME0	"data\\TEXTURE\\rankframe.png"		// �e�N�X�`����
#define	FRAME_SIZE_X			(160)								// �傫��
#define	FRAME_SIZE_Y			(160)								// �傫��
#define	MAX_FRAME			(1)									//�����N�̍ő吔

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureFrame = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
FRAME g_aFrame;													// �����N�̏��

//=============================================================================
// ����������
//=============================================================================
void InitFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFrame;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	g_aFrame.pos = D3DXVECTOR3(1175.0f, 650.0f, 0.0f);	//�ʒu�̏�����
	g_aFrame.bUse = true;								//�g�p��Ԃɂ���

														// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FRAME_TEXTURE_NAME0, &g_apTextureFrame);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aFrame.pos.x - FRAME_SIZE_X, g_aFrame.pos.y - FRAME_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aFrame.pos.x + FRAME_SIZE_X, g_aFrame.pos.y - FRAME_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aFrame.pos.x - FRAME_SIZE_X, g_aFrame.pos.y + FRAME_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aFrame.pos.x + FRAME_SIZE_X, g_aFrame.pos.y + FRAME_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;

		pVtx += 4;	// ���_�f�[�^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrame->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitFrame(void)
{

	// �e�N�X�`���̊J��
	if (g_apTextureFrame != NULL)
	{
		g_apTextureFrame->Release();
		g_apTextureFrame = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFrame(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		if (g_aFrame.bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureFrame);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntFrame,
				2);
		}
	}
}
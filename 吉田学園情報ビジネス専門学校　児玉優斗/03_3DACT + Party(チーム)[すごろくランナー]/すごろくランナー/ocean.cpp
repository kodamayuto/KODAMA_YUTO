//=============================================================================
//
// �C�̏��̏��� [ocean.cpp]
// Author : Miyu Takahashi
//
//=============================================================================
#include "ocean.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OCEAN_TEXTURE_NAME	"data\\TEXTURE\\ocean000.jpg"	// �n�ʂ̃e�N�X�`����
#define OCEAN_SIZE_X		(40000.0f)						// �n�ʑ傫��
#define OCEAN_SIZE_Z		(40000.0f)						// �n�ʑ傫��
#define POLYGON_X			(3)								// �|���S���̐��iX�j
#define POLYGON_Z			(3)								// �|���S���̐��iZ�j

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexOcean(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffOcean = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureOcean = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffOcean = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXMATRIX				g_mtxWorldOcean;		// ���[���h�}�g���b�N�X
OCEAN					g_ocean;
int						g_nNumVerTexOcean;		// ���_��
int						g_nNumIndexOcean;		// �C���f�b�N�X��
int						g_nNumPolygonOcean;		// �|���S����

//=============================================================================
// ����������
//=============================================================================
void InitOcean(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, OCEAN_TEXTURE_NAME, &g_pTextureOcean);

	// ���_���̍쐬
	MakeVertexOcean(pDevice);

	// �|���S���̏���ݒ�
	g_ocean.pos = D3DXVECTOR3(0.0f, 25.0f, 13000.0f);
	g_ocean.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_ocean.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitOcean(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureOcean != NULL)
	{
		g_pTextureOcean->Release();
		g_pTextureOcean = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffOcean != NULL)
	{
		g_pVtxBuffOcean->Release();
		g_pVtxBuffOcean = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffOcean != NULL)
	{
		g_pIdxBuffOcean->Release();
		g_pIdxBuffOcean = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateOcean(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawOcean(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldOcean);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ocean.rot.y, g_ocean.rot.x, g_ocean.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldOcean, &g_mtxWorldOcean, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_ocean.pos.x, g_ocean.pos.y, g_ocean.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldOcean, &g_mtxWorldOcean, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldOcean);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffOcean, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffOcean);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureOcean);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nNumVerTexOcean, 0, g_nNumPolygonOcean);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexOcean(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;

	// ���_��
	g_nNumVerTexOcean = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// �C���f�b�N�X��
	g_nNumIndexOcean = (POLYGON_X + 1) * (POLYGON_Z + 1)
		+ (2 * (POLYGON_Z - 1))
		+ (POLYGON_X + 1) * (POLYGON_Z - 1);

	// �|���S����
	g_nNumPolygonOcean = g_nNumIndexOcean - 2;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nNumVerTexOcean,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOcean,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nNumIndexOcean,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,						// 16�r�b�g�̃f�[�^���m��
		D3DPOOL_MANAGED,
		&g_pIdxBuffOcean,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffOcean->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < POLYGON_Z + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
		{
			// ���_���W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3(-OCEAN_SIZE_X + (nCntVtxX * OCEAN_SIZE_X), 0.0f, OCEAN_SIZE_Z - (nCntVtxZ * OCEAN_SIZE_Z));
			// �@���̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].tex = D3DXVECTOR2(0.0f + (nCntVtxX * (10.0f / POLYGON_X)), 0.0f + (nCntVtxZ * (50.0f / POLYGON_Z)));
		}
		nVtxCounter += POLYGON_X;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOcean->Unlock();

	WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffOcean->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < POLYGON_Z; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < POLYGON_X + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + POLYGON_X + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < POLYGON_Z - 1 && nCntIdxX == POLYGON_X)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (POLYGON_X + 1) + 1;
				pIdx += 2;
			}
		}
	}

	// �C���f�b�N�X�̐ݒ�
	/*pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;*/	/*������*/

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffOcean->Unlock();
}
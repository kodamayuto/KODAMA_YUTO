//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshField.cpp]
// Author : ���R���
//
//=============================================================================
#include "meshField.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\grass.jpg"	// �n�ʂ̃e�N�X�`����
#define MESHFIELD_SIZE_X		(40000.0f)						// �n�ʑ傫��
#define MESHFIELD_SIZE_Z		(40000.0f)						// �n�ʑ傫��
#define POLYGON_X				(2)								// �|���S���̐��iX�j
#define POLYGON_Z				(2)								// �|���S���̐��iZ�j

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffMeshField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffMeshField = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXMATRIX				g_mtxWorldMeshField;		// ���[���h�}�g���b�N�X
MESHFIELD				g_meshField;
int						g_nNumVerTexMeshField;		// ���_��
int						g_nNumIndexMeshField;		// �C���f�b�N�X��
int						g_nNumPolygonMeshField;		// �|���S����

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

												// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &g_pTextureMeshField);

	// ���_���̍쐬
	MakeVertexMeshField(pDevice);

	// �|���S���̏���ݒ�
	g_meshField.pos = D3DXVECTOR3(0.0f, -500.0f, 13000.0f);
	g_meshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_meshField.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

									// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshField.rot.y, g_meshField.rot.x, g_meshField.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_meshField.pos.x, g_meshField.pos.y, g_meshField.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nNumVerTexMeshField, 0, g_nNumPolygonMeshField);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;

	// ���_��
	g_nNumVerTexMeshField = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// �C���f�b�N�X��
	g_nNumIndexMeshField = (POLYGON_X + 1) * (POLYGON_Z + 1)
		+ (2 * (POLYGON_Z - 1))
		+ (POLYGON_X + 1) * (POLYGON_Z - 1);

	// �|���S����
	g_nNumPolygonMeshField = g_nNumIndexMeshField - 2;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nNumVerTexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nNumIndexMeshField,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,						// 16�r�b�g�̃f�[�^���m��
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < POLYGON_Z + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
		{
			// ���_���W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3(-MESHFIELD_SIZE_X + (nCntVtxX * MESHFIELD_SIZE_X), 0.0f, MESHFIELD_SIZE_Z - (nCntVtxZ * MESHFIELD_SIZE_Z));
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
	g_pVtxBuffMeshField->Unlock();

	WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^

				// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();
}
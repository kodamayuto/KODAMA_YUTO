//=============================================================================
//
// �O���̏��� [meshOrbit.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "orbit.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ORBIT_TEXTURE_NAME   "data/TEXTURE/COMMON/gradation000.jpg" // �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexOrbit(LPDIRECT3DDEVICE9 pDevice, int nIdxOrbit);
void MakeIndexOrbit(LPDIRECT3DDEVICE9 pDevice, int nIdxOrbit);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureOrbit[MAX_ORBIT] = {};  // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOrbit[MAX_ORBIT] = {};  // ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffOrbit[MAX_ORBIT] = {};  // �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Orbit                   g_Orbit[MAX_ORBIT];               // �O���̏��

														  //=============================================================================
														  // ����������
														  //=============================================================================
void InitOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   // �f�o�C�X�̎擾

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{// �O���̐������J��Ԃ�
		g_Orbit[nCntOrbit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ���W��������
		g_Orbit[nCntOrbit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ������������

		g_Orbit[nCntOrbit].XBlock = ORBIT_BLOCK;        // ���̕�������ݒ�
		g_Orbit[nCntOrbit].YBlock = 1;                  // �c�̕�������ݒ�
		g_Orbit[nCntOrbit].nNumVertex = (g_Orbit[nCntOrbit].XBlock + 1) * (g_Orbit[nCntOrbit].YBlock + 1); // ���_����ݒ�
		g_Orbit[nCntOrbit].nNumIndex = ((g_Orbit[nCntOrbit].XBlock + 1) * (g_Orbit[nCntOrbit].YBlock + 1)) + (2 * (g_Orbit[nCntOrbit].YBlock - 1)) + (g_Orbit[nCntOrbit].XBlock + 1) * (g_Orbit[nCntOrbit].YBlock - 1) - (g_Orbit[nCntOrbit].YBlock - 1);  // �C���f�b�N�X����ݒ�
		g_Orbit[nCntOrbit].nNumPolygon = ((g_Orbit[nCntOrbit].XBlock * g_Orbit[nCntOrbit].YBlock) * 2) + ((g_Orbit[nCntOrbit].YBlock - 1) * 4);  // �`�悷��|���S������ݒ�

		for (int nCntOrbit = 0; nCntOrbit < g_Orbit[nCntOrbit].XBlock + 1; nCntOrbit++)
		{// ���̕����������J��Ԃ�
			g_Orbit[nCntOrbit].orbit[nCntOrbit].posUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].posoldUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].posDown = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].posoldDown = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].colUp = D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].colDown = D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f);
			g_Orbit[nCntOrbit].orbit[nCntOrbit].radius = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ORBIT_TEXTURE_NAME,
			&g_pTextureOrbit[nCntOrbit]);

		// ���_���̍쐬
		MakeVertexOrbit(pDevice, nCntOrbit);

		// �C���f�b�N�X���̍쐬
		MakeIndexOrbit(pDevice, nCntOrbit);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitOrbit(void)
{
	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{// �O���̐������J��Ԃ�
	 // �e�N�X�`���̊J��
		if (g_pTextureOrbit[nCntOrbit] != NULL)
		{
			g_pTextureOrbit[nCntOrbit]->Release();
			g_pTextureOrbit[nCntOrbit] = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if (g_pVtxBuffOrbit[nCntOrbit] != NULL)
		{
			g_pVtxBuffOrbit[nCntOrbit]->Release();
			g_pVtxBuffOrbit[nCntOrbit] = NULL;
		}

		// �C���f�b�N�X�o�b�t�@�̊J��
		if (g_pIdxBuffOrbit[nCntOrbit] != NULL)
		{
			g_pIdxBuffOrbit[nCntOrbit]->Release();
			g_pIdxBuffOrbit[nCntOrbit] = NULL;
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateOrbit(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	for (int nCntOrbit1 = 0; nCntOrbit1 < MAX_ORBIT; nCntOrbit1++)
	{// �O���̐������J��Ԃ�
	 // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffOrbit[nCntOrbit1]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntOrbit = 1; nCntOrbit < g_Orbit[nCntOrbit1].XBlock + 1; nCntOrbit++)
		{// �ݒ肵�Ȃ����_�̕������J��Ԃ�
		 // �O��̈ʒu�ۑ�
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].posoldUp = g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp;
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].posoldDown = g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown;

			// ���݂̍��W�����炷
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp = g_Orbit[nCntOrbit1].orbit[nCntOrbit - 1].posoldUp;
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown = g_Orbit[nCntOrbit1].orbit[nCntOrbit - 1].posoldDown;

			// ���_���W�̍X�V
			pVtx[nCntOrbit].pos = D3DXVECTOR3(g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp.x, g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp.y, g_Orbit[nCntOrbit1].orbit[nCntOrbit].posUp.z);
			pVtx[nCntOrbit + g_Orbit[nCntOrbit1].XBlock + 1].pos = D3DXVECTOR3(g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown.x, g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown.y, g_Orbit[nCntOrbit1].orbit[nCntOrbit].posDown.z);

			// �F���ڂ�
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].colUp = g_Orbit[nCntOrbit1].orbit[nCntOrbit - 1].colUp;
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].colDown = g_Orbit[nCntOrbit1].orbit[nCntOrbit - 1].colDown;

			// �����x�����炷
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].colUp.a -= 0.02f;
			g_Orbit[nCntOrbit1].orbit[nCntOrbit].colDown.a -= 0.02f;

			// ���_�J���[�̍X�V
			pVtx[nCntOrbit].col = g_Orbit[nCntOrbit1].orbit[nCntOrbit].colUp;
			pVtx[nCntOrbit + g_Orbit[nCntOrbit1].XBlock + 1].col = g_Orbit[nCntOrbit1].orbit[nCntOrbit].colDown;
		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffOrbit[nCntOrbit1]->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;                // �v�Z�p�}�g���b�N�X

												// �J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// �J�����O���Ȃ�

															// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{// �O���̑������J��Ԃ�
	 // ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Orbit[nCntOrbit].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Orbit[nCntOrbit].rot.y, g_Orbit[nCntOrbit].rot.x, g_Orbit[nCntOrbit].rot.z);
		D3DXMatrixMultiply(&g_Orbit[nCntOrbit].mtxWorld, &g_Orbit[nCntOrbit].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Orbit[nCntOrbit].pos.x, g_Orbit[nCntOrbit].pos.y, g_Orbit[nCntOrbit].pos.z);
		D3DXMatrixMultiply(&g_Orbit[nCntOrbit].mtxWorld, &g_Orbit[nCntOrbit].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Orbit[nCntOrbit].mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffOrbit[nCntOrbit], 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetIndices(g_pIdxBuffOrbit[nCntOrbit]);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

#if 1
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureOrbit[nCntOrbit]);
#endif

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Orbit[nCntOrbit].nNumVertex, 0, g_Orbit[nCntOrbit].nNumPolygon);
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �J�����O�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	// ���ʂ��J�����O
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexOrbit(LPDIRECT3DDEVICE9 pDevice, int nIdxOrbit)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Orbit[nIdxOrbit].nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOrbit[nIdxOrbit],
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffOrbit[nIdxOrbit]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < g_Orbit[nIdxOrbit].YBlock + 1; nCntV++)
	{// �c�̕��������J��Ԃ�
		for (int nCntH = 0; nCntH < g_Orbit[nIdxOrbit].XBlock + 1; nCntH++)
		{// ���̕��������J��Ԃ�
		 // ���_���W
			pVtx[nCntH].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �@��
			pVtx[nCntH].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

			// ���_�J���[
			pVtx[nCntH].col = g_Orbit[nIdxOrbit].orbit[nCntH].colUp;

			// �e�N�X�`�����W
			pVtx[nCntH].tex = D3DXVECTOR2(nCntH * (1.0f / g_Orbit[nIdxOrbit].XBlock), nCntV * (1.0f / g_Orbit[nIdxOrbit].YBlock));
		}
		pVtx += g_Orbit[nIdxOrbit].XBlock + 1; // ���̕��������|�C���^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOrbit[nIdxOrbit]->Unlock();
}
//=============================================================================
// �C���f�b�N�X���̍쐬
//=============================================================================
void MakeIndexOrbit(LPDIRECT3DDEVICE9 pDevice, int nIdxOrbit)
{
	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_Orbit[nIdxOrbit].nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffOrbit[nIdxOrbit],
		NULL);

	WORD *pIdx;      // �C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx = 0; // �C���f�b�N�X�ԍ�

					 // �C���f�b�N�X�o�b�t�@�����b�N��,�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffOrbit[nIdxOrbit]->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY < g_Orbit[nIdxOrbit].YBlock; nCntIdxY++)
	{// �c�̕��������J��Ԃ�
		for (int nCntIdxX = 0; nCntIdxX < g_Orbit[nIdxOrbit].XBlock + 1; nCntIdxX++, nCntIdx++)
		{// ���̕�����+�P�J��Ԃ�
		 // �㉺�̓���C���f�b�N�X�ԍ���ݒ�
			pIdx[0] = nCntIdx + g_Orbit[nIdxOrbit].XBlock + 1; // ����
			pIdx[1] = nCntIdx;                      // �㑤

			pIdx += 2;  // 2���i�߂�
			if (nCntIdxY < g_Orbit[nIdxOrbit].YBlock && nCntIdxX > g_Orbit[nIdxOrbit].XBlock)
			{// 1 , �������c�̕������̍ŉ��w�ł͂Ȃ�
			 // 2 , ���̕��������ݒ肪�I�����
				pIdx[0] = nCntIdx;                            // �㑤
				pIdx[1] = nCntIdx + (g_Orbit[nIdxOrbit].XBlock + 1) + 1; // ���̉���

				pIdx += 2; // 2���i�߂�
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffOrbit[nIdxOrbit]->Unlock();
}
//=============================================================================
// �O���̐ݒ�
//=============================================================================
void SetOrbit(D3DXVECTOR3 mtx1, D3DXVECTOR3 mtx2, D3DXCOLOR colUp, D3DXCOLOR colDown, int nIdxOrbit)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffOrbit[nIdxOrbit]->Lock(0, 0, (void**)&pVtx, 0);

	// ���[�̒��_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(mtx1.x, mtx1.y, mtx1.z);
	pVtx[g_Orbit[nIdxOrbit].XBlock + 1].pos = D3DXVECTOR3(mtx2.x, mtx2.y, mtx2.z);

	// ���_�J���[
	pVtx[0].col = colUp;
	pVtx[g_Orbit[nIdxOrbit].XBlock + 1].col = colDown;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOrbit[nIdxOrbit]->Unlock();

	// ���W��ۑ�
	g_Orbit[nIdxOrbit].orbit[0].posUp = mtx1;
	g_Orbit[nIdxOrbit].orbit[0].posoldUp = mtx1;

	g_Orbit[nIdxOrbit].orbit[0].posDown = mtx2;
	g_Orbit[nIdxOrbit].orbit[0].posoldDown = mtx2;

	// �F��ݒ�
	g_Orbit[nIdxOrbit].orbit[0].colUp = colUp;
	g_Orbit[nIdxOrbit].orbit[0].colDown = colDown;

}
//=============================================================================
// �O���̍��W�ݒ�
//=============================================================================
void SetPosiotionOrbit(D3DXVECTOR3 mtx1, D3DXVECTOR3 mtx2, int nIdxOrbit)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffOrbit[nIdxOrbit]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntOrbit = 0; nCntOrbit < g_Orbit[nIdxOrbit].XBlock + 1; nCntOrbit++)
	{// �ݒ肵�Ȃ����_�̕������J��Ԃ�
	 // ���_���W��ݒ�
		pVtx[nCntOrbit].pos = D3DXVECTOR3(mtx1.x, mtx1.y, mtx1.z);
		pVtx[nCntOrbit + g_Orbit[nIdxOrbit].XBlock + 1].pos = D3DXVECTOR3(mtx2.x, mtx2.y, mtx2.z);
		g_Orbit[nIdxOrbit].orbit[nCntOrbit].posUp = mtx1;
		g_Orbit[nIdxOrbit].orbit[nCntOrbit].posoldUp = mtx1;
		g_Orbit[nIdxOrbit].orbit[nCntOrbit].posDown = mtx2;
		g_Orbit[nIdxOrbit].orbit[nCntOrbit].posoldDown = mtx2;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffOrbit[nIdxOrbit]->Unlock();
}
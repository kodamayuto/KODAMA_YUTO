//=============================================================================
//
// �|���S������ [MeshWall.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "meshWall.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHWALL_FILENAME0 "data/TEXTURE/wall000.jpg"
#define MAX_MESHWALL (200)

#define MESH_BLOCK_WIDTH (4)
#define MESH_BLOCK_HAIGHT (4)

#define MESH_WIDTH (1000.0f)
#define MESH_HAIGHT (50.0f)

//****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall[MAX_MESHWALL] = {};	//���_�o�b�t�@�ւ̃|�C���^	(�ǂ̖��������)
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall[MAX_MESHWALL] = {};
LPDIRECT3DTEXTURE9 g_pTextureMeshWall= NULL;	    //�e�N�X�`���ւ̃|�C���^

MESHWALL g_MeshWall[MAX_MESHWALL];

//=============================================================================
// ����������
//=============================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXCreateTextureFromFile(pDevice, MESHWALL_FILENAME0, &g_pTextureMeshWall);

	//�\���̂̏�����
	for (int nCntMesh = 0; nCntMesh < MAX_MESHWALL; nCntMesh++)
	{
		g_MeshWall[nCntMesh].nMeshBlockWidth = 4;
		g_MeshWall[nCntMesh].nMeshBlockHaight = 4;
		g_MeshWall[nCntMesh].fMeshSizeW = 100.0f;
		g_MeshWall[nCntMesh].fMeshSizeH = 50.0f;

		g_MeshWall[nCntMesh].bUse = false;
		g_MeshWall[nCntMesh].nNumVertex = (g_MeshWall[nCntMesh].nMeshBlockHaight + 1) * (g_MeshWall[nCntMesh].nMeshBlockWidth + 1);
		g_MeshWall[nCntMesh].nNumIndex = (g_MeshWall[nCntMesh].nMeshBlockWidth * g_MeshWall[nCntMesh].nMeshBlockHaight * 2) + (4 * (g_MeshWall[nCntMesh].nMeshBlockHaight - 1)) + 2;
	}

	MakeVertexMeshWall(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
		if (g_pTextureMeshWall != NULL)
		{
			g_pTextureMeshWall->Release();
			g_pTextureMeshWall = NULL;
		}
	//���_�o�b�t�@�̔j��
		for (int nCntBuff = 0; nCntBuff < MAX_MESHWALL; nCntBuff++)
		{
			if (g_pVtxBuffMeshWall[nCntBuff] != NULL)
			{
				g_pVtxBuffMeshWall[nCntBuff]->Release();
				g_pVtxBuffMeshWall[nCntBuff] = NULL;
			}


			//�C���f�b�N�X�o�b�t�@�̔j��
			if (g_pIdxBuffMeshWall[nCntBuff] != NULL)
			{
				g_pIdxBuffMeshWall[nCntBuff]->Release();
				g_pIdxBuffMeshWall[nCntBuff] = NULL;
			}

		}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_MESHWALL; nCntMesh++)
	{

		g_MeshWall[nCntMesh].aPos.x = g_MeshWall[nCntMesh].pos.x + 
		sinf(g_MeshWall[nCntMesh].rot.y - (D3DX_PI * 0.5f))* g_MeshWall[nCntMesh].fMeshSizeW;

		g_MeshWall[nCntMesh].aPos.z = g_MeshWall[nCntMesh].pos.z +
			cosf(g_MeshWall[nCntMesh].rot.y - (D3DX_PI * 0.5f))* g_MeshWall[nCntMesh].fMeshSizeW;


		g_MeshWall[nCntMesh].bPos.x = g_MeshWall[nCntMesh].pos.x +
			sinf(g_MeshWall[nCntMesh].rot.y + (D3DX_PI * 0.5f))* g_MeshWall[nCntMesh].fMeshSizeW;

		g_MeshWall[nCntMesh].bPos.z = g_MeshWall[nCntMesh].pos.z +
			cosf(g_MeshWall[nCntMesh].rot.y + (D3DX_PI * 0.5f))* g_MeshWall[nCntMesh].fMeshSizeW;

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (int nCntMesh = 0; nCntMesh < MAX_MESHWALL; nCntMesh++)
	{
		if (g_MeshWall[nCntMesh].bUse == true)
		{

		g_MeshWall[nCntMesh].nNumPolygon = (g_MeshWall[nCntMesh].nMeshBlockWidth * g_MeshWall[nCntMesh].nMeshBlockHaight * 2) + (4 * (g_MeshWall[nCntMesh].nMeshBlockHaight - 1));
		// ���[���h�}�g���b�N�X�̏�����
		// �|���S���̕`��
		D3DXMatrixIdentity(&g_MeshWall[nCntMesh].g_mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_MeshWall[nCntMesh].rot.y,
			g_MeshWall[nCntMesh].rot.x,
			g_MeshWall[nCntMesh].rot.z);

		D3DXMatrixMultiply(&g_MeshWall[nCntMesh].g_mtxWorld,
			&g_MeshWall[nCntMesh].g_mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_MeshWall[nCntMesh].pos.x,
			g_MeshWall[nCntMesh].pos.y,
			g_MeshWall[nCntMesh].pos.z);

		D3DXMatrixMultiply(&g_MeshWall[nCntMesh].g_mtxWorld,
			&g_MeshWall[nCntMesh].g_mtxWorld,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntMesh].g_mtxWorld);

		pDevice->SetStreamSource(0, g_pVtxBuffMeshWall[nCntMesh], 0, sizeof(VERTEX_3D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshWall[nCntMesh]);

		pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

			// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshWall);//�e�N�X�`���̐ݒ�

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			g_MeshWall[nCntMesh].nNumVertex,
			0,
			g_MeshWall[nCntMesh].nNumPolygon);
		}
	}
}


//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{	
	for (int nCntMesh = 0; nCntMesh < MAX_MESHWALL; nCntMesh++)
	{
		//���_�o�b�t�@�̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshWall[nCntMesh].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshWall[nCntMesh],
			NULL);

		//���_�C���f�b�N�X�̍쐬
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_MeshWall[nCntMesh].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshWall[nCntMesh],
			NULL);


		//�ϐ��錾
		VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffMeshWall[nCntMesh]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntHaight = 0; nCntHaight < g_MeshWall[nCntMesh].nMeshBlockHaight + 1; nCntHaight++)
		{
			for (int nCntWidth = 0; nCntWidth < g_MeshWall[nCntMesh].nMeshBlockWidth + 1; nCntWidth++)
			{
				pVtx[nCntWidth].pos = D3DXVECTOR3(-g_MeshWall[nCntMesh].fMeshSizeW + ((g_MeshWall[nCntMesh].fMeshSizeW / (g_MeshWall[nCntMesh].nMeshBlockWidth / 2.0f)) * nCntWidth),
					((g_MeshWall[nCntMesh].fMeshSizeH / (g_MeshWall[nCntMesh].nMeshBlockHaight / 2.0f))* nCntHaight),
					0.0f);

				pVtx[nCntWidth].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[nCntWidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntWidth].tex = D3DXVECTOR2(nCntWidth * 1.0f, nCntHaight * 1.0f);
			}
			pVtx += (g_MeshWall[nCntMesh].nMeshBlockWidth + 1);

		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffMeshWall[nCntMesh]->Unlock();


		//�C���f�b�N�X�f�[�^�̐ݒ�
		WORD *Idx;			//�C���f�b�N�X�f�[�^�ւ̃|�C���^
		bool flag = false;
		//�C���f�b�N�X�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffMeshWall[nCntMesh]->Lock(0, 0, (void**)&Idx, 0);

		for (int nCntIdxHaight = 0; nCntIdxHaight < g_MeshWall[nCntMesh].nMeshBlockHaight; nCntIdxHaight++)
		{
			for (int nCntIdxWidth = 0; nCntIdxWidth < g_MeshWall[nCntMesh].nMeshBlockWidth +1 ; nCntIdxWidth++)
			{
				Idx[0] = nCntIdxWidth + ((g_MeshWall[nCntMesh].nMeshBlockWidth + 1) * (nCntIdxHaight + 1));

				if (flag == true)
				{//�k�ރ|���S���̏����i���j
					Idx[1] = Idx[0];
					Idx[2] = nCntIdxWidth + ((g_MeshWall[nCntMesh].nMeshBlockWidth + 1) * (nCntIdxHaight));
					Idx += 3;
					flag = false;
				}
				else
				{//�k�ރ|���S���łȂ����

					Idx[1] = nCntIdxWidth + ((g_MeshWall[nCntMesh].nMeshBlockWidth + 1) * (nCntIdxHaight));
					Idx += 2;
				}

				if (Idx[-1] % (g_MeshWall[nCntMesh].nMeshBlockWidth + 1) == g_MeshWall[nCntMesh].nMeshBlockWidth && flag == false)
				{//�k�ރ|���S���̏����i��j
					Idx[0] = Idx[-1];
					Idx += 1;
					flag = true;
				}

			}

		}
		//�C���f�b�N�X�o�b�t�@���A�����b�N����
		g_pIdxBuffMeshWall[nCntMesh]->Unlock();
	}
	
}

//=======================================================================================
// �O�ς�p�����ǂ̓����蔻��
//---------------------------------------------------------------------------------------
//								[�����蔻��̒�`]
//
//	�e�̌����W�ƑO���W(pPos,pPosOld)�� a,b�Ƃ��A�ǂ̎n�_�ƏI�_(bPos,aPos)�� c,d�Ƃ����
//
//						����ab�Ɛ���cd���������Ă��āA����
//						����ab�ƒ���cd���������Ă����Ԃł���B
//
//=======================================================================================
bool CollisionMeshWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld)
{
		D3DXVECTOR3 VecA, VecB, VecC, VecD, VecE, VecF;	//���ꂼ��̃x�N�g���������Œ�`

	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse == true)
		{

			VecA = g_MeshWall[nCntWall].aPos - g_MeshWall[nCntWall].bPos;	//�ǂ̃x�N�g��
			VecB = *pPosOld - g_MeshWall[nCntWall].bPos;					//�ǂ̎n�_�ƒe�̑O���W�����񂾃x�N�g��
			VecC = *pPos - g_MeshWall[nCntWall].bPos;						//�ǂ̎n�_�ƒe�̌����W�����񂾃x�N�g��

			VecD = *pPos - *pPosOld;										//�e�̃x�N�g��
			VecE = g_MeshWall[nCntWall].bPos - *pPosOld;					//�e�̑O���W�ƕǂ̎n�_�����񂾃x�N�g��
			VecF = g_MeshWall[nCntWall].aPos - *pPosOld;					//�e�̑O���W�ƕǂ̏I�_�����񂾃x�N�g��

			if ((VecD.z * VecE.x) - (VecD.x * VecE.z) < 0 &&
				(VecD.z * VecF.x) - (VecD.x * VecF.z) > 0)
			{//pPos��pPosOld��ʂ钼���ƁA�ǂ̐���(aPos�`bPos)���������Ă��邩
				if ((VecA.z * VecC.x) - (VecA.x * VecC.z) < 0 &&
					(VecA.z * VecB.x) - (VecA.x * VecB.z) > 0)
				{//aPos��bPos��ʂ钼���ƁA�e�̐���(pPos�`pPosOld)���������Ă��邩
					return true;
				}

			}
		}
	}
	return false;
}

//=============================================================================
// �ǂ̍��W�ݒ�
//=============================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_MESHWALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse == false)
		{
			g_MeshWall[nCntWall].pos = pos;
			g_MeshWall[nCntWall].rot = rot;

			g_MeshWall[nCntWall].bUse = true;
			break;
		}
	}
}


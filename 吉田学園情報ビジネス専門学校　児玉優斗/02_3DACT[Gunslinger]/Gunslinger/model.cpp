//=============================================================================
//
// ���f������ [model.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "model.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_FILENAME "data/MODEL/3d_001_OBJ.x"
#define MODEL_MOVE_SPEED (0.7f)
#define MODEL_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_MODEL (1)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshModel[MAX_NUM_MODEL] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel[MAX_NUM_MODEL] = {};//�}�e���A�����ւ̃|�C���^

MODEL g_Model[MAX_NUM_MODEL];
//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_NUM_MODEL; nCntModel++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_FILENAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatModel[nCntModel],
			NULL,
			&g_Model[nCntModel].NumMatModel,
			&g_pMeshModel[nCntModel]);

		/*�����蔻��̐ݒ�*/
		SetModelVertex(nCntModel);
		//���_���̎擾

		// �ʒu�E�����̏����ݒ�
		g_Model[nCntModel].pos = D3DXVECTOR3(-900.0f, 0.0f, 900.0f);
		g_Model[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�ړ��ʁE��]�ʂ̏�����
		g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntModel].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Model[nCntModel].bUse = true;

	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_MODEL; nCntMesh++)
	{
		// ���b�V���̉��
		if (g_pMeshModel[nCntMesh] != NULL)
		{
			g_pMeshModel[nCntMesh]->Release();
			g_pMeshModel[nCntMesh] = NULL;
		}
		/*�e�N�X�`���̉��*/
		//�}�e���A���̉��
		if (g_pBuffMatModel[nCntMesh] != NULL)
		{
			g_pBuffMatModel[nCntMesh]->Release();
			g_pBuffMatModel[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	for (int nCntModel = 0; nCntModel < MAX_NUM_MODEL; nCntModel++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Model[nCntModel].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Model[nCntModel].rot.y,
			g_Model[nCntModel].rot.x,
			g_Model[nCntModel].rot.z);

		D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorld,
			&g_Model[nCntModel].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_Model[nCntModel].pos.x,
			g_Model[nCntModel].pos.y,
			g_Model[nCntModel].pos.z);

		D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorld,
			&g_Model[nCntModel].mtxWorld,
			&mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntModel].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCntModel]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Model[nCntModel].NumMatModel; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			/*�e�N�X�`���̐ݒ�*/
			pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

			// ���f��(�p�[�c)�̕`��
			g_pMeshModel[nCntModel]->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// �����蔻��̏���
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//�ϐ��錾
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_NUM_MODEL; nCntData++)
	{
		if (g_Model[nCntData].bUse == true)
		{
			if (g_Model[nCntData].VtxMin.z + g_Model[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_Model[nCntData].VtxMax.z + g_Model[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_Model[nCntData].VtxMin.x + g_Model[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_Model[nCntData].VtxMin.x + g_Model[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//������E
					pPos->x = g_Model[nCntData].VtxMin.x + g_Model[nCntData].pos.x - pVtxMax->x;
					pMove->x = 0.0f;
				}
				if (g_Model[nCntData].VtxMax.x + g_Model[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_Model[nCntData].VtxMax.x + g_Model[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//�E���獶
					pPos->x = g_Model[nCntData].VtxMax.x + g_Model[nCntData].pos.x - pVtxMin->x;
					pMove->x = 0.0f;
				}
			}

			if (g_Model[nCntData].VtxMin.x + g_Model[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_Model[nCntData].VtxMax.x + g_Model[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_Model[nCntData].VtxMin.z + g_Model[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Model[nCntData].VtxMin.z + g_Model[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//��O���牜
					pPos->z = g_Model[nCntData].VtxMin.z + g_Model[nCntData].pos.z - pVtxMax->z;
					pMove->z = 0.0f;
				}
				if (g_Model[nCntData].VtxMax.z + g_Model[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_Model[nCntData].VtxMax.z + g_Model[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//�������O
					pPos->z = g_Model[nCntData].VtxMax.z + g_Model[nCntData].pos.z - pVtxMin->z;
					pMove->z = 0.0f;
				}
			}
		}
		
		if (((pPos->x - g_Model[nCntData].pos.x) * (pPos->x - g_Model[nCntData].pos.x)) +
			((pPos->z - g_Model[nCntData].pos.z) * (pPos->z - g_Model[nCntData].pos.z)) <=
			10000.0f)
		{
			return true;
		}
	}
	return bLand;

}
//=============================================================================
// �ő�E�ŏ��̒��_���W���擾
//=============================================================================
void SetModelVertex(int nCntModel)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	g_Model[nCntModel].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Model[nCntModel].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//���_���̎擾
	nNumVtx = g_pMeshModel[nCntModel]->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel[nCntModel]->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshModel[nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

													//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
													//x
		if (g_Model[nCntModel].VtxMin.x > vtx.x)
		{
			g_Model[nCntModel].VtxMin.x = vtx.x;
		}
		if (g_Model[nCntModel].VtxMax.x < vtx.x)
		{
			g_Model[nCntModel].VtxMax.x = vtx.x;
		}

		//y
		if (g_Model[nCntModel].VtxMin.y > vtx.y)
		{
			g_Model[nCntModel].VtxMin.y = vtx.y;
		}
		if (g_Model[nCntModel].VtxMax.y < vtx.y)
		{
			g_Model[nCntModel].VtxMax.y = vtx.y;
		}

		//z
		if (g_Model[nCntModel].VtxMin.z > vtx.z)
		{
			g_Model[nCntModel].VtxMin.z = vtx.z;
		}
		if (g_Model[nCntModel].VtxMax.z < vtx.z)
		{
			g_Model[nCntModel].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
	}
	//�A�����b�N
	g_pMeshModel[nCntModel]->UnlockVertexBuffer();

}
//=============================================================================
// ���f���̏����擾
//=============================================================================
MODEL *GetModel(void)
{
	return g_Model;
}
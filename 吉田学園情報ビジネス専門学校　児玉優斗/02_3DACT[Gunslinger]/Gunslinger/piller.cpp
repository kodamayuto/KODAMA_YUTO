//=============================================================================
//
// ������ [piller.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "piller.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PILLER_FILENAME "data/MODEL/piller000.x"
#define PILLER_MOVE_SPEED (0.7f)
#define PILLER_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_PILLER (250)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshPiller[MAX_NUM_PILLER] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPiller[MAX_NUM_PILLER] = {};//�}�e���A�����ւ̃|�C���^

PILLER g_Piller[MAX_NUM_PILLER];
//=============================================================================
// ����������
//=============================================================================
void InitPiller(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPiller = 0; nCntPiller < MAX_NUM_PILLER; nCntPiller++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(PILLER_FILENAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatPiller[nCntPiller],
			NULL,
			&g_Piller[nCntPiller].NumMatModel,
			&g_pMeshPiller[nCntPiller]);

		/*�����蔻��̐ݒ�*/
		//���_���̎擾
		SetPillerVertex(nCntPiller);

		g_Piller[nCntPiller].bUse = false;
		g_Piller[nCntPiller].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitPiller(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_PILLER; nCntMesh++)
	{
		// ���b�V���̉��
		if (g_pMeshPiller[nCntMesh] != NULL)
		{
			g_pMeshPiller[nCntMesh]->Release();
			g_pMeshPiller[nCntMesh] = NULL;
		}
		/*�e�N�X�`���̉��*/
		//�}�e���A���̉��
		if (g_pBuffMatPiller[nCntMesh] != NULL)
		{
			g_pBuffMatPiller[nCntMesh]->Release();
			g_pBuffMatPiller[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePiller(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPiller(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	for (int nCntPiller = 0; nCntPiller < MAX_NUM_PILLER; nCntPiller++)
	{
		if (g_Piller[nCntPiller].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Piller[nCntPiller].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Piller[nCntPiller].rot.y,
				g_Piller[nCntPiller].rot.x,
				g_Piller[nCntPiller].rot.z);

			D3DXMatrixMultiply(&g_Piller[nCntPiller].mtxWorld,
				&g_Piller[nCntPiller].mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Piller[nCntPiller].pos.x,
				g_Piller[nCntPiller].pos.y,
				g_Piller[nCntPiller].pos.z);

			D3DXMatrixMultiply(&g_Piller[nCntPiller].mtxWorld,
				&g_Piller[nCntPiller].mtxWorld,
				&mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Piller[nCntPiller].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatPiller[nCntPiller]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Piller[nCntPiller].NumMatModel; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*�e�N�X�`���̐ݒ�*/
				pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

				// ���f��(�p�[�c)�̕`��
				g_pMeshPiller[nCntPiller]->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=============================================================================
// �����蔻��̏���
//=============================================================================
bool CollisionPiller(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//�ϐ��錾
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_NUM_PILLER; nCntData++)
	{
		if (g_Piller[nCntData].bUse == true)
		{
			if (g_Piller[nCntData].VtxMin.z + g_Piller[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_Piller[nCntData].VtxMax.z + g_Piller[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_Piller[nCntData].VtxMin.x + g_Piller[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_Piller[nCntData].VtxMin.x + g_Piller[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//������E
					pPos->x = g_Piller[nCntData].VtxMin.x + g_Piller[nCntData].pos.x - pVtxMax->x;
					pMove->x = 0.0f;
				}
				if (g_Piller[nCntData].VtxMax.x + g_Piller[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_Piller[nCntData].VtxMax.x + g_Piller[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//�E���獶
					pPos->x = g_Piller[nCntData].VtxMax.x + g_Piller[nCntData].pos.x - pVtxMin->x;
					pMove->x = 0.0f;
				}
			}

			if (g_Piller[nCntData].VtxMin.x + g_Piller[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_Piller[nCntData].VtxMax.x + g_Piller[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_Piller[nCntData].VtxMin.z + g_Piller[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Piller[nCntData].VtxMin.z + g_Piller[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//��O���牜
					pPos->z = g_Piller[nCntData].VtxMin.z + g_Piller[nCntData].pos.z - pVtxMax->z;
					pMove->z = 0.0f;
				}
				if (g_Piller[nCntData].VtxMax.z + g_Piller[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_Piller[nCntData].VtxMax.z + g_Piller[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//�������O
					pPos->z = g_Piller[nCntData].VtxMax.z + g_Piller[nCntData].pos.z - pVtxMin->z;
					pMove->z = 0.0f;
				}
			}
		}
		
	}
	return bLand;

}
//=============================================================================
// �ő�E�ŏ��̒��_���W���擾
//=============================================================================
void SetPillerVertex(int nCntPiller)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	g_Piller[nCntPiller].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Piller[nCntPiller].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//���_���̎擾
	nNumVtx = g_pMeshPiller[nCntPiller]->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPiller[nCntPiller]->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshPiller[nCntPiller]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

													//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
													//x
		if (g_Piller[nCntPiller].VtxMin.x > vtx.x)
		{
			g_Piller[nCntPiller].VtxMin.x = vtx.x;
		}
		if (g_Piller[nCntPiller].VtxMax.x < vtx.x)
		{
			g_Piller[nCntPiller].VtxMax.x = vtx.x;
		}

		//y
		if (g_Piller[nCntPiller].VtxMin.y > vtx.y)
		{
			g_Piller[nCntPiller].VtxMin.y = vtx.y;
		}
		if (g_Piller[nCntPiller].VtxMax.y < vtx.y)
		{
			g_Piller[nCntPiller].VtxMax.y = vtx.y;
		}

		//z
		if (g_Piller[nCntPiller].VtxMin.z > vtx.z)
		{
			g_Piller[nCntPiller].VtxMin.z = vtx.z;
		}
		if (g_Piller[nCntPiller].VtxMax.z < vtx.z)
		{
			g_Piller[nCntPiller].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
	}
	//�A�����b�N
	g_pMeshPiller[nCntPiller]->UnlockVertexBuffer();

}

//=============================================================================
// ���f���̈ʒu���
//=============================================================================
void SetPiller(D3DXVECTOR3 pos)
{
	for (int nCntPiller = 0; nCntPiller < MAX_NUM_PILLER; nCntPiller++)
	{
		if (g_Piller[nCntPiller].bUse == false)
		{
			g_Piller[nCntPiller].pos = pos;
			g_Piller[nCntPiller].bUse = true;

			break;
		}
	}
}

//=============================================================================
// ���f���̏����擾
//=============================================================================
PILLER *GetPiller(void)
{
	return g_Piller;
}
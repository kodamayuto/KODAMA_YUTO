//=============================================================================
//
// ���f������ [object.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "object.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBJECT_FILENAME1 "data/MODEL/3d_001_Chain0.x"
#define OBJECT_FILENAME2 "data/MODEL/3d_001_Mace2.x"
#define OBJECT_FILENAME3 "data/MODEL/3d_001_Box0.x"
#define OBJECT_FILENAME4 "data/MODEL/3d_001_Stone0.x"
#define OBJECT_FILENAME5 "data/MODEL/3d_001_Stone1.x"
#define OBJECT_FILENAME6 "data/MODEL/3d_001_Stone2.x"

#define OBJECT_MOVE_SPEED (0.7f)
#define OBJECT_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_OBJECT (17)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshObject[MAX_NUM_OBJECT] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject[MAX_NUM_OBJECT] = {};//�}�e���A�����ւ̃|�C���^

OBJECT g_Object[MAX_NUM_OBJECT];
//=============================================================================
// ����������
//=============================================================================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�̏����ݒ�
	g_Object[0].FireName = OBJECT_FILENAME1;
	g_Object[0].pos = D3DXVECTOR3(998.0f, 70.0f, -800.0f);
	g_Object[0].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);

	g_Object[1].FireName = OBJECT_FILENAME2;
	g_Object[1].pos = D3DXVECTOR3(730.0f, 10.0f, -620.0f);
	g_Object[1].rot = D3DXVECTOR3(-0.1f, 0.0f, D3DX_PI * 0.15f);

	g_Object[2].FireName = OBJECT_FILENAME3;
	g_Object[2].pos = D3DXVECTOR3(400.0f, 0.0f, 500.0f);
	g_Object[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Object[3].FireName = OBJECT_FILENAME3;
	g_Object[3].pos = D3DXVECTOR3(-950.0f, 0.0f, -950.0f);
	g_Object[3].rot = D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f);

	g_Object[4].FireName = OBJECT_FILENAME1;
	g_Object[4].pos = D3DXVECTOR3(0.0f, 70.0f, -198.0f);
	g_Object[4].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

	g_Object[5].FireName = OBJECT_FILENAME4;
	g_Object[5].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Object[6].FireName = OBJECT_FILENAME5;
	g_Object[6].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
	g_Object[6].rot = D3DXVECTOR3(0.0f, 0.1f, 0.0f);

	g_Object[7].FireName = OBJECT_FILENAME6;
	g_Object[7].pos = D3DXVECTOR3(-250.0f, 0.0f, 0.0f);
	g_Object[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	g_Object[8].FireName = OBJECT_FILENAME5;
	g_Object[8].pos = D3DXVECTOR3(-350.0f, 0.0f, 0.0f);
	g_Object[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Object[9].FireName = OBJECT_FILENAME6;
	g_Object[9].pos = D3DXVECTOR3(-650.0f, 0.0f, -200.0f);
	g_Object[9].rot = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	g_Object[10].FireName = OBJECT_FILENAME4;
	g_Object[10].pos = D3DXVECTOR3(-500.0f, 0.0f, -350.0f);
	g_Object[10].rot = D3DXVECTOR3(0.0f, -0.5f, 0.0f);

	g_Object[11].FireName = OBJECT_FILENAME6;
	g_Object[11].pos = D3DXVECTOR3(140.0f, 0.0f, -320.0f);
	g_Object[11].rot = D3DXVECTOR3(0.0f, 0.7f, 0.0f);

	g_Object[12].FireName = OBJECT_FILENAME5;
	g_Object[12].pos = D3DXVECTOR3(280.0f, 0.0f, -380.0f);
	g_Object[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Object[13].FireName = OBJECT_FILENAME4;
	g_Object[13].pos = D3DXVECTOR3(380.0f, 0.0f, -290.0f);
	g_Object[13].rot = D3DXVECTOR3(0.0f, 0.4f, 0.0f);

	g_Object[14].FireName = OBJECT_FILENAME5;
	g_Object[14].pos = D3DXVECTOR3(800.0f, 0.0f, -600.0f);
	g_Object[14].rot = D3DXVECTOR3(0.0f, 0.4f, 0.0f);

	g_Object[15].FireName = OBJECT_FILENAME6;
	g_Object[15].pos = D3DXVECTOR3(900.0f, 0.0f, -850.0f);
	g_Object[15].rot = D3DXVECTOR3(0.0f, 0.4f, 0.0f);

	g_Object[16].FireName = OBJECT_FILENAME5;
	g_Object[16].pos = D3DXVECTOR3(900.0f, 0.0f, 0.0f);
	g_Object[16].rot = D3DXVECTOR3(0.0f, 0.7f, 0.0f);

	for (int nCntObject = 0; nCntObject < MAX_NUM_OBJECT; nCntObject++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(g_Object[nCntObject].FireName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatObject[nCntObject],
			NULL,
			&g_Object[nCntObject].NumMatModel,
			&g_pMeshObject[nCntObject]);

		/*�����蔻��̐ݒ�*/
		//���_���̎擾
		SetObjectVertex(nCntObject);

		g_Object[nCntObject].bUse = true;

	}


}

//=============================================================================
// �I������
//=============================================================================
void UninitObject(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_OBJECT; nCntMesh++)
	{
		// ���b�V���̉��
		if (g_pMeshObject[nCntMesh] != NULL)
		{
			g_pMeshObject[nCntMesh]->Release();
			g_pMeshObject[nCntMesh] = NULL;
		}
		/*�e�N�X�`���̉��*/
		//�}�e���A���̉��
		if (g_pBuffMatObject[nCntMesh] != NULL)
		{
			g_pBuffMatObject[nCntMesh]->Release();
			g_pBuffMatObject[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObject(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	for (int nCntObject = 0; nCntObject < MAX_NUM_OBJECT; nCntObject++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Object[nCntObject].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Object[nCntObject].rot.y,
			g_Object[nCntObject].rot.x,
			g_Object[nCntObject].rot.z);

		D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorld,
			&g_Object[nCntObject].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_Object[nCntObject].pos.x,
			g_Object[nCntObject].pos.y,
			g_Object[nCntObject].pos.z);

		D3DXMatrixMultiply(&g_Object[nCntObject].mtxWorld,
			&g_Object[nCntObject].mtxWorld,
			&mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCntObject].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntObject]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Object[nCntObject].NumMatModel; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			/*�e�N�X�`���̐ݒ�*/
			pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

			// ���f��(�p�[�c)�̕`��
			g_pMeshObject[nCntObject]->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// �����蔻��̏���
//=============================================================================
bool CollisionObject(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//�ϐ��錾
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_NUM_OBJECT; nCntData++)
	{
		if (g_Object[nCntData].bUse == true)
		{
			if (g_Object[nCntData].VtxMin.z + g_Object[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_Object[nCntData].VtxMax.z + g_Object[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_Object[nCntData].VtxMin.x + g_Object[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_Object[nCntData].VtxMin.x + g_Object[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//������E
					pPos->x = g_Object[nCntData].VtxMin.x + g_Object[nCntData].pos.x - pVtxMax->x;
					pMove->x = 0.0f;
				}
				if (g_Object[nCntData].VtxMax.x + g_Object[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_Object[nCntData].VtxMax.x + g_Object[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//�E���獶
					pPos->x = g_Object[nCntData].VtxMax.x + g_Object[nCntData].pos.x - pVtxMin->x;
					pMove->x = 0.0f;
				}
			}

			if (g_Object[nCntData].VtxMin.x + g_Object[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_Object[nCntData].VtxMax.x + g_Object[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_Object[nCntData].VtxMin.z + g_Object[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Object[nCntData].VtxMin.z + g_Object[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//��O���牜
					pPos->z = g_Object[nCntData].VtxMin.z + g_Object[nCntData].pos.z - pVtxMax->z;
					pMove->z = 0.0f;
				}
				if (g_Object[nCntData].VtxMax.z + g_Object[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_Object[nCntData].VtxMax.z + g_Object[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//�������O
					pPos->z = g_Object[nCntData].VtxMax.z + g_Object[nCntData].pos.z - pVtxMin->z;
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
void SetObjectVertex(int nCntObject)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	g_Object[nCntObject].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Object[nCntObject].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//���_���̎擾
	nNumVtx = g_pMeshObject[nCntObject]->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[nCntObject]->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshObject[nCntObject]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

													//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
													//x
		if (g_Object[nCntObject].VtxMin.x > vtx.x)
		{
			g_Object[nCntObject].VtxMin.x = vtx.x;
		}
		if (g_Object[nCntObject].VtxMax.x < vtx.x)
		{
			g_Object[nCntObject].VtxMax.x = vtx.x;
		}

		//y
		if (g_Object[nCntObject].VtxMin.y > vtx.y)
		{
			g_Object[nCntObject].VtxMin.y = vtx.y;
		}
		if (g_Object[nCntObject].VtxMax.y < vtx.y)
		{
			g_Object[nCntObject].VtxMax.y = vtx.y;
		}

		//z
		if (g_Object[nCntObject].VtxMin.z > vtx.z)
		{
			g_Object[nCntObject].VtxMin.z = vtx.z;
		}
		if (g_Object[nCntObject].VtxMax.z < vtx.z)
		{
			g_Object[nCntObject].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
	}
	//�A�����b�N
	g_pMeshObject[nCntObject]->UnlockVertexBuffer();

}
//=============================================================================
// ���f���̏����擾
//=============================================================================
OBJECT *Getobject(void)
{
	return g_Object;
}
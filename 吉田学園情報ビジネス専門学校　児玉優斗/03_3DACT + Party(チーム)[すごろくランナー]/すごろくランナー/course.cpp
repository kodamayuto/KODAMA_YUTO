//=============================================================================
//
// �R�[�X�̏��� [course.cpp]
// Author : ���R���
//
//=============================================================================
#include "course.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COURSE_TEXTURE_NAME	"data\\TEXTURE\\course000.jpg"	// �n�ʂ̃e�N�X�`����
#define COURSE_SIZE_X		(50.0f)							// �n�ʑ傫��
#define COURSE_SIZE_Z		(200.0f)						// �n�ʑ傫��
#define MAX_COURSE			(126)							// �R�[�X�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexCourse(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffCourse = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureCourse = NULL;	// �e�N�X�`���ւ̃|�C���^
COURSE					g_aCourse[MAX_COURSE];

//=============================================================================
// ����������
//=============================================================================
void InitCourse(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

												// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, COURSE_TEXTURE_NAME, &g_pTextureCourse);

	// ���_���̍쐬
	MakeVertexCourse(pDevice);

	for (int nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{// �R�[�X�̐������J��Ԃ�
		// �|���S���̏���ݒ�
		g_aCourse[nCntCourse].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aCourse[nCntCourse].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aCourse[nCntCourse].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_aCourse[nCntCourse].fDepth = 0.0f;						// ���s
		g_aCourse[nCntCourse].fWidth = 0.0f;						// ��
		for(int nCntVer = 0;nCntVer < 4;nCntVer++)
		{// ���_���̐������J��Ԃ�
			g_aCourse[nCntCourse].Vertex[nCntVer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aCourse[nCntCourse].Vertex[nCntVer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		g_aCourse[nCntCourse].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitCourse(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureCourse != NULL)
	{
		g_pTextureCourse->Release();
		g_pTextureCourse = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCourse != NULL)
	{
		g_pVtxBuffCourse->Release();
		g_pVtxBuffCourse = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCourse(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCourse(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aCourse[nCntCourse].mtxWorldCourse);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCourse[nCntCourse].rot.y, g_aCourse[nCntCourse].rot.x, g_aCourse[nCntCourse].rot.z);
		D3DXMatrixMultiply(&g_aCourse[nCntCourse].mtxWorldCourse, &g_aCourse[nCntCourse].mtxWorldCourse, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aCourse[nCntCourse].pos.x, g_aCourse[nCntCourse].pos.y, g_aCourse[nCntCourse].pos.z);
		D3DXMatrixMultiply(&g_aCourse[nCntCourse].mtxWorldCourse, &g_aCourse[nCntCourse].mtxWorldCourse, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aCourse[nCntCourse].mtxWorldCourse);

		for (int nCntVer = 0; nCntVer < 4; nCntVer++)
		{// ���_���̐������J��Ԃ�
		    // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCourse[nCntCourse].Vertex[nCntVer].rot.y, g_aCourse[nCntCourse].Vertex[nCntVer].rot.x, g_aCourse[nCntCourse].Vertex[nCntVer].rot.z);
			D3DXMatrixMultiply(&g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aCourse[nCntCourse].Vertex[nCntVer].pos.x, g_aCourse[nCntCourse].Vertex[nCntVer].pos.y, g_aCourse[nCntCourse].Vertex[nCntVer].pos.z);
			D3DXMatrixMultiply(&g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &mtxTrans);

			// �e�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &g_aCourse[nCntCourse].Vertex[nCntVer].mtxWorld, &g_aCourse[nCntCourse].mtxWorldCourse);
		}

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffCourse, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCourse);

		if (g_aCourse[nCntCourse].bUse == true)	// �e���g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntCourse,
				2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexCourse(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_COURSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCourse,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCourse->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aCourse[nCntCourse].fWidth, 0.0f, g_aCourse[nCntCourse].fDepth);
		pVtx[1].pos = D3DXVECTOR3(g_aCourse[nCntCourse].fWidth, 0.0f, g_aCourse[nCntCourse].fDepth);
		pVtx[2].pos = D3DXVECTOR3(-g_aCourse[nCntCourse].fWidth, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCourse[nCntCourse].fWidth, 0.0f, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCourse->Unlock();
}

//=============================================================================
// �R�[�X�̐ݒ�
//=============================================================================
void SetCourse(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth)
{
	int nCntCourse;

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCourse->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{
		if (g_aCourse[nCntCourse].bUse == false)
		{
			g_aCourse[nCntCourse].fWidth = fWidth;
			g_aCourse[nCntCourse].fDepth = fDepth;
			g_aCourse[nCntCourse].pos = pos;
			g_aCourse[nCntCourse].rot = rot;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aCourse[nCntCourse].fWidth, 0.0f, g_aCourse[nCntCourse].fDepth);
			pVtx[1].pos = D3DXVECTOR3(g_aCourse[nCntCourse].fWidth, 0.0f, g_aCourse[nCntCourse].fDepth);
			pVtx[2].pos = D3DXVECTOR3(-g_aCourse[nCntCourse].fWidth, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aCourse[nCntCourse].fWidth, 0.0f, 0.0f);


			for (int nCntVer = 0; nCntVer < 4; nCntVer++)
			{// ���_���̐������J��Ԃ�
				g_aCourse[nCntCourse].Vertex[nCntVer].pos = pVtx[nCntVer].pos;
			}

			g_aCourse[nCntCourse].bUse = true;
			break;
		}
		pVtx += 4;	// �Y���̈ʒu�܂Ői�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCourse->Unlock();
}
//=============================================================================
// �R�[�X�Ƃ̓����蔻��
//=============================================================================
bool CollisionCourse(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius)
{
	// �R�[�X�ɏ����������Ă��Ȃ���
	bool bLand = false;

	// �O�ς̓����蔻��p
	D3DXVECTOR3 vecA, vecC;
	D3DXVECTOR3 aVerPos[4];
	int nCntVec = 0;

	for (int nCntCourse = 0; nCntCourse < MAX_COURSE; nCntCourse++)
	{// �R�[�X�̐������J��Ԃ�
		if (g_aCourse[nCntCourse].bUse == true)
		{// �R�[�X���g�p����Ă���
			if (pPosOld->y >= g_aCourse[nCntCourse].pos.y && pPos->y < g_aCourse[nCntCourse].pos.y)
			{// �R�[�X����ɂ����̂ɗ����Ă���
				nCntVec = 0;
				// ���̃R�[�X�̒��_���W���擾
				aVerPos[0] = D3DXVECTOR3(g_aCourse[nCntCourse].Vertex[0].mtxWorld._41, g_aCourse[nCntCourse].Vertex[0].mtxWorld._42, g_aCourse[nCntCourse].Vertex[0].mtxWorld._43);
				aVerPos[1] = D3DXVECTOR3(g_aCourse[nCntCourse].Vertex[1].mtxWorld._41, g_aCourse[nCntCourse].Vertex[1].mtxWorld._42, g_aCourse[nCntCourse].Vertex[1].mtxWorld._43);
				aVerPos[3] = D3DXVECTOR3(g_aCourse[nCntCourse].Vertex[2].mtxWorld._41, g_aCourse[nCntCourse].Vertex[2].mtxWorld._42, g_aCourse[nCntCourse].Vertex[2].mtxWorld._43);
				aVerPos[2] = D3DXVECTOR3(g_aCourse[nCntCourse].Vertex[3].mtxWorld._41, g_aCourse[nCntCourse].Vertex[3].mtxWorld._42, g_aCourse[nCntCourse].Vertex[3].mtxWorld._43);
				for (int nCntVer = 0; nCntVer < 4; nCntVer++)
				{// ���_���̐������J��Ԃ�
					vecC = *pPos - aVerPos[nCntVer];
					vecA = aVerPos[(nCntVer + 1) % 4] - aVerPos[nCntVer];

					if ((vecA.z * vecC.x) - (vecA.x * vecC.z) < 0)
					{// ���̃x�N�g���̊O���ɂ���
						nCntVec++;
					}
				}
				if (nCntVec == 0)
				{// ��x���x�N�g���̊O���ɂ��Ȃ�����
					pPos->y = g_aCourse[nCntCourse].pos.y;
					pMove->y = 0.0f;
					bLand = true;
				}
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCourse->Unlock();

	return bLand;
}
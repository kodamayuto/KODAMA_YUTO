//=============================================================================
//
// �����L���O��� [ranking.cpp]
// Author : �������D
//
//=============================================================================
#include "ranking.h"
#include "fade.h"
#include "input.h"
#include "rankingscore.h"
#include "camera.h"
#include "light.h"
#include "sky.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_MODEL	"data\\MODEL\\board1.x"		// �ǂݍ��ރ��f���t�@�C����1
#define RANKING_MODEL1	"data\\MODEL\\board2.x"		// �ǂݍ��ރ��f���t�@�C����2
#define RANKING_MODEL2	"data\\MODEL\\board3.x"		// �ǂݍ��ރ��f���t�@�C����3
#define RANKING_MODEL3	"data\\MODEL\\board4.x"		// �ǂݍ��ރ��f���t�@�C����4
#define RANKING_MODEL4	"data\\MODEL\\board5.x"		// �ǂݍ��ރ��f���t�@�C����5

#define MODEL_L			"data\\MODEL\\boardL.x"		// �ǂݍ��ރ��f���t�@�C����

#define MAX_TEXTURE		(5)							// �e�N�X�`���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_nCntRanking;												// ���b��Ƀt�F�[�h
LPDIRECT3DTEXTURE9*		g_pTextureRanking[MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
RankingModel g_RankingModel[10];								// ���f���̏��
D3DXVECTOR3 g_vtxMinRanking, g_vtxMaxRanking;					// ���f���̍ŏ��l�E�ő�l
RankingOld g_RankingOld = RANKINGOLD_TITLE;
int g_nCntRankingMove = 1;										//�����L���O�ł̃J�����ړ�
int g_nRankingMoveCount = 4;									//�����L���O���̃J��������Ǘ�


//=============================================================================
// �����L���O��ʂ̏���������
//=============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	// ������
	g_nCntRanking = 0;


	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//�n�ʂ̏���������
	InitPolygon();

	//��̏���������
	InitSky();

	// �����L���O�X�R�A�̏���������
	InitRankingscore();

	SetPolygon(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), POLYGONTYPE_GRASS, 10000.0f, 10000.0f);


	// X�t�@�C���̓ǂݍ���5
	D3DXLoadMeshFromX(RANKING_MODEL4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[0].pBuffMat,
		NULL,
		&g_RankingModel[0].nNumMat,
		&g_RankingModel[0].pMesh);

	// �}�e���A����񂩂�e�N�X�`���������o��
	D3DXMATERIAL *pMat4 = (D3DXMATERIAL*)g_RankingModel[0].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff4 = new D3DMATERIAL9[g_RankingModel[0].nNumMat];
	g_pTextureRanking[0] = new LPDIRECT3DTEXTURE9[g_RankingModel[0].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[0].nNumMat; nCntRanking++)
	{// �}�e���A������ǂݍ���
		pMatBuff4[nCntRanking] = pMat4[nCntRanking].MatD3D;

		// �e�N�X�`������������
		g_pTextureRanking[0][nCntRanking] = NULL;

		// �e�N�X�`������ǂݍ���
		if (pMat4[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat4[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat4[nCntRanking].pTextureFilename,
				&g_pTextureRanking[0][nCntRanking]);
		}
	}
	// X�t�@�C���̓ǂݍ���4
	D3DXLoadMeshFromX(RANKING_MODEL3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[1].pBuffMat,
		NULL,
		&g_RankingModel[1].nNumMat,
		&g_RankingModel[1].pMesh);

	// �}�e���A����񂩂�e�N�X�`���������o��
	D3DXMATERIAL *pMat3 = (D3DXMATERIAL*)g_RankingModel[1].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff3 = new D3DMATERIAL9[g_RankingModel[1].nNumMat];
	g_pTextureRanking[1] = new LPDIRECT3DTEXTURE9[g_RankingModel[1].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[1].nNumMat; nCntRanking++)
	{// �}�e���A������ǂݍ���
		pMatBuff3[nCntRanking] = pMat3[nCntRanking].MatD3D;

		// �e�N�X�`������������
		g_pTextureRanking[1][nCntRanking] = NULL;

		// �e�N�X�`������ǂݍ���
		if (pMat3[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat3[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat3[nCntRanking].pTextureFilename,
				&g_pTextureRanking[1][nCntRanking]);
		}
	}


	// X�t�@�C���̓ǂݍ���3
	D3DXLoadMeshFromX(RANKING_MODEL2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[2].pBuffMat,
		NULL,
		&g_RankingModel[2].nNumMat,
		&g_RankingModel[2].pMesh);

	// �}�e���A����񂩂�e�N�X�`���������o��
	D3DXMATERIAL *pMat2 = (D3DXMATERIAL*)g_RankingModel[2].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff2 = new D3DMATERIAL9[g_RankingModel[2].nNumMat];
	g_pTextureRanking[2] = new LPDIRECT3DTEXTURE9[g_RankingModel[2].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[2].nNumMat; nCntRanking++)
	{// �}�e���A������ǂݍ���
		pMatBuff2[nCntRanking] = pMat2[nCntRanking].MatD3D;

		// �e�N�X�`������������
		g_pTextureRanking[2][nCntRanking] = NULL;

		// �e�N�X�`������ǂݍ���
		if (pMat2[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat2[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat2[nCntRanking].pTextureFilename,
				&g_pTextureRanking[2][nCntRanking]);
		}
	}

	// X�t�@�C���̓ǂݍ���2
	D3DXLoadMeshFromX(RANKING_MODEL1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[3].pBuffMat,
		NULL,
		&g_RankingModel[3].nNumMat,
		&g_RankingModel[3].pMesh);

	// �}�e���A����񂩂�e�N�X�`���������o��
	D3DXMATERIAL *pMat1 = (D3DXMATERIAL*)g_RankingModel[3].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff1 = new D3DMATERIAL9[g_RankingModel[3].nNumMat];
	g_pTextureRanking[3] = new LPDIRECT3DTEXTURE9[g_RankingModel[3].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[3].nNumMat; nCntRanking++)
	{// �}�e���A������ǂݍ���
		pMatBuff1[nCntRanking] = pMat1[nCntRanking].MatD3D;

		// �e�N�X�`������������
		g_pTextureRanking[3][nCntRanking] = NULL;

		// �e�N�X�`������ǂݍ���
		if (pMat1[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat1[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat1[nCntRanking].pTextureFilename,
				&g_pTextureRanking[3][nCntRanking]);
		}
	}


	// X�t�@�C���̓ǂݍ���1
	D3DXLoadMeshFromX(RANKING_MODEL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[4].pBuffMat,
		NULL,
		&g_RankingModel[4].nNumMat,
		&g_RankingModel[4].pMesh);

	// �}�e���A����񂩂�e�N�X�`���������o��
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_RankingModel[4].pBuffMat->GetBufferPointer();
	D3DMATERIAL9 *pMatBuff = new D3DMATERIAL9[g_RankingModel[4].nNumMat];
	g_pTextureRanking[4] = new LPDIRECT3DTEXTURE9[g_RankingModel[4].nNumMat];

	for (DWORD nCntRanking = 0; nCntRanking < g_RankingModel[4].nNumMat; nCntRanking++)
	{// �}�e���A������ǂݍ���
		pMatBuff[nCntRanking] = pMat[nCntRanking].MatD3D;

		// �e�N�X�`������������
		g_pTextureRanking[4][nCntRanking] = NULL;

		// �e�N�X�`������ǂݍ���
		if (pMat[nCntRanking].pTextureFilename != NULL &&
			lstrlen(pMat[nCntRanking].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntRanking].pTextureFilename,
				&g_pTextureRanking[4][nCntRanking]);
		}
	}

	// X�t�@�C���̓ǂݍ���(�X�R�A�Ŕ�)1
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[5].pBuffMat,
		NULL,
		&g_RankingModel[5].nNumMat,
		&g_RankingModel[5].pMesh);

	// X�t�@�C���̓ǂݍ���(�X�R�A�Ŕ�)2
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[6].pBuffMat,
		NULL,
		&g_RankingModel[6].nNumMat,
		&g_RankingModel[6].pMesh);

	// X�t�@�C���̓ǂݍ���(�X�R�A�Ŕ�)3
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[7].pBuffMat,
		NULL,
		&g_RankingModel[7].nNumMat,
		&g_RankingModel[7].pMesh);

	// X�t�@�C���̓ǂݍ���(�X�R�A�Ŕ�)4
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[8].pBuffMat,
		NULL,
		&g_RankingModel[8].nNumMat,
		&g_RankingModel[8].pMesh);

	// X�t�@�C���̓ǂݍ���(�X�R�A�Ŕ�)5
	D3DXLoadMeshFromX(MODEL_L,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_RankingModel[9].pBuffMat,
		NULL,
		&g_RankingModel[9].nNumMat,
		&g_RankingModel[9].pMesh);

	// ������
	for (int nCntRanking = 0; nCntRanking < MAX_MODEL; nCntRanking++)
	{
		g_RankingModel[nCntRanking].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_RankingModel[nCntRanking].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	}

	// ���ʊŔ�
	g_RankingModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 400.0f);
	g_RankingModel[1].pos = D3DXVECTOR3(40.0f, 0.0f, 300.0f);
	g_RankingModel[2].pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);
	g_RankingModel[3].pos = D3DXVECTOR3(40.0f, 0.0f, 100.0f);
	g_RankingModel[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �X�R�A�Ŕ�
	g_RankingModel[5].pos = D3DXVECTOR3(40.0f, 0.0f, 0.0f);
	g_RankingModel[6].pos = D3DXVECTOR3(80.0f, 0.0f, 100.0f);
	g_RankingModel[7].pos = D3DXVECTOR3(40.0f, 0.0f, 200.0f);
	g_RankingModel[8].pos = D3DXVECTOR3(80.0f, 0.0f, 300.0f);
	g_RankingModel[9].pos = D3DXVECTOR3(40.0f, 0.0f, 400.0f);

	//�^�C�}�[�̏�����
	g_nRankingMoveCount = 4;		//�����L���O���̃J��������Ǘ�


}

//=============================================================================
// �����L���O��ʂ̏I������
//=============================================================================
void UninitRanking(void)
{

	// �J�����̏I������
	UninitCamera();

	//�n�ʂ̏I������
	UninitPolygon();

	// ���C�g�̏I������
	UninitLight();

	//��̏I������
	UninitSky();

	// �����L���O�X�R�A�̏I������
	UninitRankingscore();

	for (int nCntRanking = 0; nCntRanking < MAX_MODEL; nCntRanking++)
	{
		// ���b�V���̊J��
		if (g_RankingModel[nCntRanking].pMesh != NULL)
		{
			g_RankingModel[nCntRanking].pMesh->Release();
			g_RankingModel[nCntRanking].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_RankingModel[nCntRanking].pBuffMat != NULL)
		{
			g_RankingModel[nCntRanking].pBuffMat->Release();
			g_RankingModel[nCntRanking].pBuffMat = NULL;
		}

		// �e�N�X�`���̊J��
		if (nCntRanking <= 4)
		{
			for (DWORD nCntMat = 0; nCntMat < g_RankingModel[nCntRanking].nNumMat; nCntMat++)
			{
				if (g_pTextureRanking[nCntRanking][nCntMat] != NULL)
				{
					g_pTextureRanking[nCntRanking][nCntMat]->Release();
					g_pTextureRanking[nCntRanking][nCntMat] = NULL;
				}
			}
		}
		else
		{
			if (g_pTextureRanking[nCntRanking] != NULL)
			{
				g_pTextureRanking[nCntRanking] = NULL;
			}
		}
	}
}

//=============================================================================
// �����L���O��ʂ̍X�V����
//=============================================================================
void UpdateRanking(void)
{
	FADE g_fade;

	g_fade = GetFade();

	g_nCntRanking++;

	// �J�����擾
	Camera *pCamera = GetCamera();

	// �J�����̍X�V����
	g_nCntRankingMove = (g_nCntRankingMove + 1) % 200;
	pCamera->SelectModelpos[4] = D3DXVECTOR3(20.0f, 20.0f, -80.0f);
	pCamera->SelectModelpos[3] = D3DXVECTOR3(60.0f, 20.0f, 20.0f);
	pCamera->SelectModelpos[2] = D3DXVECTOR3(20.0f, 20.0f, 120.0f);
	pCamera->SelectModelpos[1] = D3DXVECTOR3(60.0f, 20.0f, 220.0f);
	pCamera->SelectModelpos[0] = D3DXVECTOR3(20.0f, 20.0f, 320.0f);

	if (g_nCntRankingMove % 200 == 0)
	{
		if (g_nRankingMoveCount == 0)
		{
			switch (g_RankingOld)
			{
			case RANKINGOLD_TITLE:
				SetFade(MODE_TITLE);
				break;

			case RANKINGOLD_SELECT:
				SetFade(MODE_SELECT);
				break;
			}
		}
		else
		{
			if (GetFade() == FADE_NONE)
			{
				g_nRankingMoveCount = (g_nRankingMoveCount + 4) % 5;
			}
		}
	}
	pCamera->posRDest = D3DXVECTOR3(pCamera->SelectModelpos[g_nRankingMoveCount].x - pCamera->posR.x,
		0.0f,
		(pCamera->SelectModelpos[g_nRankingMoveCount].z + 80.0f) - pCamera->posR.z);
	pCamera->posR.x += pCamera->posRDest.x * 0.04f;
	pCamera->posR.z += pCamera->posRDest.z * 0.04f;

	pCamera->posVDest = pCamera->SelectModelpos[g_nRankingMoveCount];
	pCamera->posV += (pCamera->posVDest - pCamera->posV) * 0.04f;

	// ���C�g�̍X�V����
	UpdateLight();

	//�n�ʂ̍X�V����
	UpdatePolygon();

	//��̍X�V����
	UpdateSky();

	// �����L���O�X�R�A�̍X�V����
	UpdateRankingscore();

	// ����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_2, 0) == true)
	{
		if (g_fade != FADE_OUT)
		{
			//���[�h�ݒ�
			switch (g_RankingOld)
			{
			case RANKINGOLD_TITLE:
				SetFade(MODE_TITLE);
				break;

			case RANKINGOLD_SELECT:
				SetFade(MODE_SELECT);
				break;
			}

			SetDrawScore(4);
			//PlaySound(SOUND_LABEL_SE_BOTAN001);
		}
	}
}

//=============================================================================
// �����L���O��ʂ̕`�揈��
//=============================================================================
void DrawRanking(void)
{
	// �J�����̐ݒ�
	SetCamera();

	//�n�ʂ̕`�揈��
	DrawPolygon();

	//��̕`�揈��
	DrawSky();

	int nCntRanking = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntRanking = 0; nCntRanking < MAX_MODEL; nCntRanking++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_RankingModel[nCntRanking].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_RankingModel[nCntRanking].rot.y, g_RankingModel[nCntRanking].rot.x, g_RankingModel[nCntRanking].rot.z);
		D3DXMatrixMultiply(&g_RankingModel[nCntRanking].mtxWorld, &g_RankingModel[nCntRanking].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_RankingModel[nCntRanking].pos.x, g_RankingModel[nCntRanking].pos.y, g_RankingModel[nCntRanking].pos.z);
		D3DXMatrixMultiply(&g_RankingModel[nCntRanking].mtxWorld, &g_RankingModel[nCntRanking].mtxWorld, &mtxTrans);

		//// �֘A�t��
		//D3DXMatrixMultiply(&g_RankingModel[nCntRanking].mtxWorld, &g_RankingModel[nCntRanking].mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_RankingModel[nCntRanking].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_RankingModel[nCntRanking].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_RankingModel[nCntRanking].nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (nCntRanking <= 4)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureRanking[nCntRanking][nCntMat]);
			}
			else
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
			}

			// �v���C���[(�p�[�c)�̕`��
			g_RankingModel[nCntRanking].pMesh->DrawSubset(nCntMat);

		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
	// �J�����̐ݒ�
	//SetCamera();
	//pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �����L���O�X�R�A�̕`�揈��
	DrawRankingscore();

}

//=============================================================================
// �����L���O��ʂ̕`�揈��
//=============================================================================
void SetRankingOld(RankingOld ranking)
{
	g_RankingOld = ranking;
}
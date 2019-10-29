//=============================================================================
//
// ���ʉ�ʏ��� [result.cpp]
// Author : Niwa Hodaka, Miyu Takahashi
//
//=============================================================================
#include "result.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "meshField.h"
#include "ocean.h"
#include "sky.h"
#include "sound.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_MODELDATA	"data\\MODEL\\wood4.x"			// �ǂݍ��ރ��f���t�@�C��(��)
#define RESULT_MODELDATA2	"data\\MODEL\\lake.x"			// �ǂݍ��ރ��f���t�@�C��(�I�A�V�X)

#define RESULT_BOARD1		"data\\MODEL\\board1.x"			// �ǂݍ��ރ��f���t�@�C��(��ʊŔ�)
#define RESULT_BOARD2		"data\\MODEL\\board2.x"			// �ǂݍ��ރ��f���t�@�C��(��ʊŔ�)
#define RESULT_BOARD3		"data\\MODEL\\resultwood.x"		// �ǂݍ��ރ��f���t�@�C��(���U���g�Ŕ�)
#define RESULT_BOARD4		"data\\MODEL\\resultwood2.x"	// �ǂݍ��ރ��f���t�@�C��(GAMEOVER�Ŕ�)

#define MAX_TEXTURE			(4)								// �e�N�X�`���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9* g_pTextureResult[MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
ResultModel g_ResultModel[RESULT_MODELC];				// ���f���̏��
D3DXVECTOR3 g_vtxMinResult, g_vtxMaxResult;				// ���f���̍ŏ��l�E�ő�l
int    g_nCounterResult;								// �^�C�g����ʂɑJ�ڂ���^�C�~���O

//=============================================================================
// ����������
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	MODE g_Mode;

	g_nCounterResult = 0;			// �J�E���^�[��0��

									//�f�o�C�X�̎擾
	pDevice = GetDevice();
	g_Mode = GetMode();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �e�̏�����
	InitShadow();

	// ���b�V���t�B�[���h�̏���������
	InitMeshField();

	// �C�̏��̏���������
	InitOcean();

	// ��̏���������
	InitSky();

	// �v���C���[�̏���������
	InitPlayer();

	if (g_Mode == MODE_CLEAR)
	{// �Q�[���N���A

	 // X�t�@�C���̓ǂݍ���(��ʊŔ�)
		D3DXLoadMeshFromX(RESULT_BOARD1,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_ResultModel[0].pBuffMat,
			NULL,
			&g_ResultModel[0].nNumMat,
			&g_ResultModel[0].pMesh);

		// �}�e���A����񂩂�e�N�X�`���������o��
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_ResultModel[0].pBuffMat->GetBufferPointer();
		D3DMATERIAL9 *pMatBuff = new D3DMATERIAL9[g_ResultModel[0].nNumMat];
		g_pTextureResult[0] = new LPDIRECT3DTEXTURE9[g_ResultModel[0].nNumMat];

		for (DWORD nCntRanking = 0; nCntRanking < g_ResultModel[0].nNumMat; nCntRanking++)
		{// �}�e���A������ǂݍ���
			pMatBuff[nCntRanking] = pMat[nCntRanking].MatD3D;

			// �e�N�X�`������������
			g_pTextureResult[0][nCntRanking] = NULL;

			// �e�N�X�`������ǂݍ���
			if (pMat[nCntRanking].pTextureFilename != NULL &&
				lstrlen(pMat[nCntRanking].pTextureFilename) > 0)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntRanking].pTextureFilename,
					&g_pTextureResult[0][nCntRanking]);
			}

			// X�t�@�C���̓ǂݍ���(��ʊŔ�)
			D3DXLoadMeshFromX(RESULT_BOARD2,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[1].pBuffMat,
				NULL,
				&g_ResultModel[1].nNumMat,
				&g_ResultModel[1].pMesh);

			// �}�e���A����񂩂�e�N�X�`���������o��
			D3DXMATERIAL *pMat1 = (D3DXMATERIAL*)g_ResultModel[1].pBuffMat->GetBufferPointer();
			D3DMATERIAL9 *pMatBuff1 = new D3DMATERIAL9[g_ResultModel[1].nNumMat];
			g_pTextureResult[1] = new LPDIRECT3DTEXTURE9[g_ResultModel[1].nNumMat];

			for (DWORD nCntRanking = 0; nCntRanking < g_ResultModel[1].nNumMat; nCntRanking++)
			{// �}�e���A������ǂݍ���
				pMatBuff1[nCntRanking] = pMat1[nCntRanking].MatD3D;

				// �e�N�X�`������������
				g_pTextureResult[1][nCntRanking] = NULL;

				// �e�N�X�`������ǂݍ���
				if (pMat1[nCntRanking].pTextureFilename != NULL &&
					lstrlen(pMat1[nCntRanking].pTextureFilename) > 0)
				{
					D3DXCreateTextureFromFile(pDevice,
						pMat1[nCntRanking].pTextureFilename,
						&g_pTextureResult[1][nCntRanking]);
				}
			}

			// X�t�@�C���̓ǂݍ���(���U���g�Ŕ�)
			D3DXLoadMeshFromX(RESULT_BOARD3,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[2].pBuffMat,
				NULL,
				&g_ResultModel[2].nNumMat,
				&g_ResultModel[2].pMesh);

			// �}�e���A����񂩂�e�N�X�`���������o��
			D3DXMATERIAL *pMat2 = (D3DXMATERIAL*)g_ResultModel[2].pBuffMat->GetBufferPointer();
			D3DMATERIAL9 *pMatBuff2 = new D3DMATERIAL9[g_ResultModel[2].nNumMat];
			g_pTextureResult[2] = new LPDIRECT3DTEXTURE9[g_ResultModel[2].nNumMat];

			for (DWORD nCntRanking = 0; nCntRanking < g_ResultModel[2].nNumMat; nCntRanking++)
			{// �}�e���A������ǂݍ���
				pMatBuff2[nCntRanking] = pMat2[nCntRanking].MatD3D;

				// �e�N�X�`������������
				g_pTextureResult[2][nCntRanking] = NULL;

				// �e�N�X�`������ǂݍ���
				if (pMat2[nCntRanking].pTextureFilename != NULL &&
					lstrlen(pMat2[nCntRanking].pTextureFilename) > 0)
				{
					D3DXCreateTextureFromFile(pDevice,
						pMat2[nCntRanking].pTextureFilename,
						&g_pTextureResult[2][nCntRanking]);
				}
			}

			// X�t�@�C���̓ǂݍ���(��)
			D3DXLoadMeshFromX(RESULT_MODELDATA,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[3].pBuffMat,
				NULL,
				&g_ResultModel[3].nNumMat,
				&g_ResultModel[3].pMesh);

			// X�t�@�C���̓ǂݍ���(��)
			D3DXLoadMeshFromX(RESULT_MODELDATA,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[4].pBuffMat,
				NULL,
				&g_ResultModel[4].nNumMat,
				&g_ResultModel[4].pMesh);

			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(RESULT_MODELDATA2,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ResultModel[5].pBuffMat,
				NULL,
				&g_ResultModel[5].nNumMat,
				&g_ResultModel[5].pMesh);
		}

		// ���ʊŔ̈ʒu
		g_ResultModel[0].pos = D3DXVECTOR3(-58.0f, 10.0f, -1577.0f);	// ���
		g_ResultModel[1].pos = D3DXVECTOR3(54.0f, 13.0f, -1560.0f);		// ���
		g_ResultModel[2].pos = D3DXVECTOR3(1.0f, 91.0f, -1530.0f);		// ���U���g

																		// �؂̈ʒu
		g_ResultModel[3].pos = D3DXVECTOR3(-90.0f, 0.0f, -1110.0f);		// ��
		g_ResultModel[4].pos = D3DXVECTOR3(60.0f, 0.0f, -990.0f);		// ��
		g_ResultModel[5].pos = D3DXVECTOR3(0.0f, -60.0f, -900.0f);		// �I�A�V�X

	}
	else if (g_Mode == MODE_OVER)
	{// �Q�[���I�[�o�[

	 // X�t�@�C���̓ǂݍ���(GAMEOVER�Ŕ�)
		D3DXLoadMeshFromX(RESULT_BOARD4,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_ResultModel[0].pBuffMat,
			NULL,
			&g_ResultModel[0].nNumMat,
			&g_ResultModel[0].pMesh);

		// �}�e���A����񂩂�e�N�X�`���������o��
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_ResultModel[0].pBuffMat->GetBufferPointer();
		D3DMATERIAL9 *pMatBuff = new D3DMATERIAL9[g_ResultModel[0].nNumMat];
		g_pTextureResult[0] = new LPDIRECT3DTEXTURE9[g_ResultModel[0].nNumMat];

		for (DWORD nCntRanking = 0; nCntRanking < g_ResultModel[0].nNumMat; nCntRanking++)
		{// �}�e���A������ǂݍ���
			pMatBuff[nCntRanking] = pMat[nCntRanking].MatD3D;

			// �e�N�X�`������������
			g_pTextureResult[0][nCntRanking] = NULL;

			// �e�N�X�`������ǂݍ���
			if (pMat[nCntRanking].pTextureFilename != NULL &&
				lstrlen(pMat[nCntRanking].pTextureFilename) > 0)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntRanking].pTextureFilename,
					&g_pTextureResult[0][nCntRanking]);
			}
		}

		// GAMEOVER�Ŕ̈ʒu
		g_ResultModel[0].pos = D3DXVECTOR3(1.0f, 108.0f, -1550.0f);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	int nCntResult;

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshField();

	// �C�̏��̏I������
	UninitOcean();

	// ��̏I������
	UninitSky();

	// �v���C���[�̏I������
	UninitPlayer();

	// �e�̏I��
	UninitShadow();

	for (nCntResult = 0; nCntResult < RESULT_MODELC; nCntResult++)
	{
		// ���b�V���̊J��
		if (g_ResultModel[nCntResult].pMesh != NULL)
		{
			g_ResultModel[nCntResult].pMesh->Release();
			g_ResultModel[nCntResult].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_ResultModel[nCntResult].pBuffMat != NULL)
		{
			g_ResultModel[nCntResult].pBuffMat->Release();
			g_ResultModel[nCntResult].pBuffMat = NULL;
		}

		// �e�N�X�`���̊J��
		if (nCntResult <= 2)
		{
			for (DWORD nCntMat = 0; nCntMat < g_ResultModel[nCntResult].nNumMat; nCntMat++)
			{
				if (g_pTextureResult[nCntResult][nCntMat] != NULL)
				{
					g_pTextureResult[nCntResult][nCntMat]->Release();
					g_pTextureResult[nCntResult][nCntMat] = NULL;
				}
			}
		}
		else
		{
			if (g_pTextureResult[nCntResult] != NULL)
			{
				g_pTextureResult[nCntResult] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	g_nCounterResult++;

	// �J�����擾
	Camera *pCamera = GetCamera();

	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	// ���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	// �C�̏��̍X�V����
	UpdateOcean();

	// ��̍X�V����
	UpdateSky();

	// �v���C���[�̍X�V����
	UpdatePlayer();

	// �e�̍X�V
	UpdateShadow();

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE || GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE && GetFade() == FADE_NONE || g_nCounterResult % 300 == 0 && GetFade() == FADE_NONE)
	{// ����{�^���������ꂽ
		if (GetMode() == MODE_CLEAR)
		{// �N���A������
			SetFade(MODE_RANKING);
		}
		else if (GetMode() == MODE_OVER)
		{// �Q�[���I�[�o�[��������
			SetFade(MODE_SELECT);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// ��̕`�揈��
	DrawSky();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �e�̕`��
	DrawShadow();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	MODE g_Mode;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	g_Mode = GetMode();

	if (g_Mode == MODE_CLEAR)
	{
		// ���b�V���t�B�[���h�̕`�揈��
		DrawMeshField();

		for (int nCntResult = 0; nCntResult < RESULT_MODELC; nCntResult++)
		{
			if (nCntResult == 2)
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_ResultModel[nCntResult].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ResultModel[nCntResult].rot.y, g_ResultModel[nCntResult].rot.x, g_ResultModel[nCntResult].rot.z);
			D3DXMatrixMultiply(&g_ResultModel[nCntResult].mtxWorld, &g_ResultModel[nCntResult].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_ResultModel[nCntResult].pos.x, g_ResultModel[nCntResult].pos.y, g_ResultModel[nCntResult].pos.z);
			D3DXMatrixMultiply(&g_ResultModel[nCntResult].mtxWorld, &g_ResultModel[nCntResult].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_ResultModel[nCntResult].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_ResultModel[nCntResult].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ResultModel[nCntResult].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (nCntResult <= 2)
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureResult[nCntResult][nCntMat]);
				}
				else
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, NULL);
				}

				// �v���C���[(�p�[�c)�̕`��
				g_ResultModel[nCntResult].pMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);

			if (nCntResult == 2)
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}
	else if (g_Mode == MODE_OVER)
	{// �Q�[���I�[�o�[

	 // �C�̏��̕`�揈��
		DrawOcean();

		for (int nCntResult = 0; nCntResult < RESULT_MODELO; nCntResult++)
		{
			if (nCntResult == 0)
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_ResultModel[nCntResult].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ResultModel[nCntResult].rot.y, g_ResultModel[nCntResult].rot.x, g_ResultModel[nCntResult].rot.z);
			D3DXMatrixMultiply(&g_ResultModel[nCntResult].mtxWorld, &g_ResultModel[nCntResult].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_ResultModel[nCntResult].pos.x, g_ResultModel[nCntResult].pos.y, g_ResultModel[nCntResult].pos.z);
			D3DXMatrixMultiply(&g_ResultModel[nCntResult].mtxWorld, &g_ResultModel[nCntResult].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_ResultModel[nCntResult].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_ResultModel[nCntResult].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ResultModel[nCntResult].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (nCntResult <= 0)
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureResult[nCntResult][nCntMat]);
				}
				else
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, NULL);
				}

				// �v���C���[(�p�[�c)�̕`��
				g_ResultModel[nCntResult].pMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);

			if (nCntResult == 0)
			{
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}
}
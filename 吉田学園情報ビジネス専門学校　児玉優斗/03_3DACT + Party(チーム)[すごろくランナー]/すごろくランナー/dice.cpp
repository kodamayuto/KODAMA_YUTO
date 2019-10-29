//=============================================================================
//
// ���f������ [dice.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "dice.h"
#include "camera.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "timer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DICE_FILENAME "data/MODEL/dice.x"
#define DICE_MOVE_SPEED (0.7f)
#define DICE_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_DICE (2)
#define DICE_MOVE_INTERVAL (2)		//�_�C�X�̉�]���x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeDebugFont(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshDice[MAX_NUM_DICE] = {};		// ���b�V�����ւ̃|�C���^[���f���̍ő吔]
LPD3DXBUFFER g_pBuffMatDice[MAX_NUM_DICE] = {};	// �}�e���A�����ւ̃|�C���^[���f���̍ő吔]

DICE g_Dice[MAX_NUM_DICE];						// ���f���̏��[���f���̍ő吔]

bool g_bTimerFlag = false;		//�^�C�}�[�̃Z�b�g�Ǘ�
int g_nMaxNumDice;				// �_�C�X�̏o�ڂ̍��v�l

LPD3DXFONT	pDiceFont = NULL;	// �t�H���g�I�u�W�F�N�g�̃|�C���^
D3DXCOLOR g_DiceFontColor;		// �t�H���g�̐F
char g_DiceNumber[256];			// ������i�[�p[256�ŌŒ�]

RECT g_NumRect = {				// ������u���͈�
	50,		// �����X���W
	500,	// �����Y���W
	200,	// �E����X���W
	650		// �E����Y���W
};

//=============================================================================
// ����������
//=============================================================================
void InitDice(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntDice = 0; nCntDice < MAX_NUM_DICE; nCntDice++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(DICE_FILENAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatDice[nCntDice],
			NULL,
			&g_Dice[nCntDice].NumMatDice,
			&g_pMeshDice[nCntDice]);

		// �ʒu�E�����̏����ݒ�
		g_Dice[nCntDice].rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f);

		//�ړ��ʁE��]�ʂ̏�����
		g_Dice[nCntDice].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Dice[nCntDice].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���̑��ϐ��̏�����
		g_Dice[nCntDice].bUse = false;
		g_Dice[nCntDice].nCntDiceMove = 0;
		g_Dice[nCntDice].nNumDice = 0;
		g_Dice[nCntDice].DiceMotion = DICEMOTION_NONE;
	}

	//�ʒu�̐ݒ�(��ŏ���)
	g_Dice[0].pos = D3DXVECTOR3(50.0f, -10.0f, 40.0f);
	g_Dice[0].oldPos = g_Dice[0].pos;
	g_Dice[1].pos = D3DXVECTOR3(-50.0f, -10.0f, 40.0f);
	g_Dice[1].oldPos = g_Dice[1].pos;

	//�O���[�o���ϐ��̏�����
	g_bTimerFlag = true;
	g_DiceFontColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�t�H���g�̍쐬
	MakeDebugFont(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitDice(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_DICE; nCntMesh++)
	{
		// ���b�V���̉��
		if (g_pMeshDice[nCntMesh] != NULL)
		{
			g_pMeshDice[nCntMesh]->Release();
			g_pMeshDice[nCntMesh] = NULL;

		}
		/*�e�N�X�`���̉��*/
		//�}�e���A���̉��
		if (g_pBuffMatDice[nCntMesh] != NULL)
		{
			g_pBuffMatDice[nCntMesh]->Release();
			g_pBuffMatDice[nCntMesh] = NULL;

		}

	}

	//�t�H���g�̉��
	if (pDiceFont != NULL)
	{
		pDiceFont->Release();
		pDiceFont = NULL;

	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDice(void)
{
	for (int nCntDice = 0; nCntDice < MAX_NUM_DICE; nCntDice++)
	{

		if (g_Dice[nCntDice].bUse == true)
		{//�g���Ă�����
			switch (g_Dice[nCntDice].DiceMotion)
			{
			case DICEMOTION_NONE://����
				break;
			case DICEMOTION_MOVE://��ʒu�ŉ�]
				g_Dice[nCntDice].nCntDiceMove++;
				if (g_Dice[nCntDice].nCntDiceMove % DICE_MOVE_INTERVAL == 0)
				{
					g_Dice[nCntDice].rot.x += (rand() % 40 + 40) * 0.01f;
					g_Dice[nCntDice].rot.y += D3DX_PI * 0.125f;
					g_Dice[nCntDice].rot.z += (rand() % 40 + 40) * 0.01f;

					g_Dice[nCntDice].rot.x = RotOverwhelming(g_Dice[nCntDice].rot.x);
					g_Dice[nCntDice].rot.y = RotOverwhelming(g_Dice[nCntDice].rot.y);
					g_Dice[nCntDice].rot.z = RotOverwhelming(g_Dice[nCntDice].rot.z);
				}
				break;
			case DICEMOTION_THROW://��ɑł������������
				if (g_Dice[nCntDice].pos.y >= g_Dice[nCntDice].oldPos.y)
				{
					g_Dice[nCntDice].move.y -= 0.75f;

					g_Dice[nCntDice].rot.x += (rand() % 40 + 40) * 0.01f;
					g_Dice[nCntDice].rot.y += D3DX_PI * 0.125f;
					g_Dice[nCntDice].rot.z += (rand() % 40 + 40) * 0.01f;

					g_Dice[nCntDice].rot.x = RotOverwhelming(g_Dice[nCntDice].rot.x);
					g_Dice[nCntDice].rot.y = RotOverwhelming(g_Dice[nCntDice].rot.y);
					g_Dice[nCntDice].rot.z = RotOverwhelming(g_Dice[nCntDice].rot.z);

				}
				else
				{
					g_Dice[nCntDice].DiceMotion = DICEMOTION_STOP;
				}
				g_Dice[nCntDice].move.z += (0.0f - g_Dice[nCntDice].move.z) * 0.1f;
				g_Dice[nCntDice].pos.z += g_Dice[nCntDice].move.z;
				g_Dice[nCntDice].move.y += (0.0f - g_Dice[nCntDice].move.y) * 0.1f;
				g_Dice[nCntDice].pos.y += g_Dice[nCntDice].move.y;

				break;
			case DICEMOTION_STOP://�����ĐÎ~
				g_Dice[nCntDice].pos.y = g_Dice[nCntDice].oldPos.y;

				switch (g_Dice[nCntDice].nNumDice)
				{//�o�ڂɊp�x�����킹��
				case 1:
					g_Dice[nCntDice].rot.x = D3DX_PI * 0.5f;
					g_Dice[nCntDice].rot.z = 0.0f;
					break;
				case 2:
					g_Dice[nCntDice].rot.x = 0.0f;
					g_Dice[nCntDice].rot.z = 0.0f;
					break;
				case 3:
					g_Dice[nCntDice].rot.x = 0.0f;
					g_Dice[nCntDice].rot.z = D3DX_PI * -0.5f;
					break;
				case 4:
					g_Dice[nCntDice].rot.x = 0.0f;
					g_Dice[nCntDice].rot.z = D3DX_PI * 0.5f;
					break;
				case 5:
					g_Dice[nCntDice].rot.x = D3DX_PI;
					g_Dice[nCntDice].rot.z = 0.0f;
					break;
				case 6:
					g_Dice[nCntDice].rot.x = D3DX_PI * -0.5f;
					g_Dice[nCntDice].rot.z = 0.0f;
					break;
				}
				//g_Dice[nCntDice].rot.y = D3DX_PI * 0.25f;

				if (g_bTimerFlag == true)
				{
					g_bTimerFlag = false;
					SetTurnState(TURNSTATE_COUNTDOWN);
					SetTimer(g_nMaxNumDice);

				}

				//�o�͂��镶���̏㏑��
				wsprintf(g_DiceNumber, "%d", g_nMaxNumDice);

				break;
			}

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_1, GetIdxPlayer()) == TRUE)
			{//�T�C�R���𓊂���
				if (g_Dice[nCntDice].DiceMotion == DICEMOTION_MOVE)
				{
					g_Dice[nCntDice].nNumDice = rand() % 6 + 1;
					g_Dice[nCntDice].move.z += (rand() % 6 - 3) * 1.0f;
					g_Dice[nCntDice].move.y += 25.0f;

					g_bTimerFlag = true;
					g_Dice[nCntDice].DiceMotion = DICEMOTION_THROW;
					g_Dice[nCntDice].pos = g_Dice[nCntDice].oldPos;

					g_Dice[nCntDice].nCntDiceMove = 0;
				}
			}

			g_Dice[nCntDice].move.z += (0.0f - g_Dice[nCntDice].move.z) * 0.1f;
			g_Dice[nCntDice].pos.z += g_Dice[nCntDice].move.z;
			g_Dice[nCntDice].move.y += (0.0f - g_Dice[nCntDice].move.y) * 0.1f;
			g_Dice[nCntDice].pos.y += g_Dice[nCntDice].move.y;

		}

	}

	if (g_nMaxNumDice != (g_Dice[0].nNumDice + g_Dice[1].nNumDice))
	{//�o�ڂ��X�V�����Ȃ�
		g_nMaxNumDice = (g_Dice[0].nNumDice + g_Dice[1].nNumDice);

	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawDice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^


	for (int nCntDice = 0; nCntDice < MAX_NUM_DICE; nCntDice++)
	{
		if (g_Dice[nCntDice].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Dice[nCntDice].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Dice[nCntDice].rot.y,
				g_Dice[nCntDice].rot.x,
				g_Dice[nCntDice].rot.z);

			D3DXMatrixMultiply(&g_Dice[nCntDice].mtxWorld,
				&g_Dice[nCntDice].mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Dice[nCntDice].pos.x,
				g_Dice[nCntDice].pos.y,
				g_Dice[nCntDice].pos.z);

			D3DXMatrixMultiply(&g_Dice[nCntDice].mtxWorld,
				&g_Dice[nCntDice].mtxWorld,
				&mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Dice[nCntDice].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatDice[nCntDice]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Dice[nCntDice].NumMatDice; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*�e�N�X�`���̐ݒ�*/
				pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

											 // ���f��(�p�[�c)�̕`��
				g_pMeshDice[nCntDice]->DrawSubset(nCntMat);

			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

	//�t�H���g�̕`��
	pDiceFont->DrawText(
		NULL,								// NULL
		g_DiceNumber,						// �`�悷��e�L�X�g
		-1,									// �`�悷�镶����(-1�ŏ�̃e�L�X�g�̕��������擾���Ă����)
		&g_NumRect,							// �`��͈�(��Œ�`����RECT�^�̕ϐ��̃|�C���^������)
		DT_VCENTER | DT_CENTER,				// �`��I�v�V����
		g_DiceFontColor						// �F�w��
	);

}

//===========================================================
//	�t�H���g�̍쐬
//===========================================================
void MakeDebugFont(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFont(
		pDevice,					// �f�o�C�X�̃|�C���^
		192,							// ����
		80,							// ��
		FW_ULTRABOLD,				// �t�H���g�̑���
		NULL,						// ����
		FALSE,						// �Α�(TRUE��on,FALSE��off)
		SHIFTJIS_CHARSET,			// �����Z�b�g
		OUT_DEFAULT_PRECIS,			// �o�͐��x(OUT_DEFAULT_PRECIS�ŌŒ�)
		PROOF_QUALITY,				// �����̕i��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~���̃C���f�b�N�X
		TEXT("Meiryo UI"),			// �t�H���g��(�󔒁A�啶�����܂߂Đ��m�ɓ��͂��邱��)
		&pDiceFont);					// �t�H���g�̃|�C���^

}
//===========================================================
//	�_�C�X�̐ݒ�
//===========================================================
void SetDice(int nNumDice)
{
	Camera *pCamera;
	pCamera = GetCamera();

	Player *pPlayer;
	pPlayer = GetPlayer();


	switch (nNumDice)
	{//�T�C�R�����ɉ����Ĉʒu�������
	case 1:
		g_Dice[0].pos = D3DXVECTOR3(pPlayer->pos.x - 100.0f, -20.0f, pPlayer->pos.z + 40.0f);
		g_Dice[0].oldPos = g_Dice[0].pos;
		g_Dice[0].bUse = true;
		g_Dice[0].DiceMotion = DICEMOTION_MOVE;
		break;
	case 2:
		g_Dice[0].pos = D3DXVECTOR3(pPlayer->pos.x - 150.0f, -20.0f, pPlayer->pos.z + 40.0f);
		g_Dice[0].oldPos = g_Dice[0].pos;
		g_Dice[0].bUse = true;
		g_Dice[0].DiceMotion = DICEMOTION_MOVE;

		g_Dice[1].pos = D3DXVECTOR3(pPlayer->pos.x - 50.0f, -20.0f, pPlayer->pos.z + 40.0f);
		g_Dice[1].oldPos = g_Dice[1].pos;
		g_Dice[1].bUse = true;
		g_Dice[1].DiceMotion = DICEMOTION_MOVE;
		break;
	}
}
//===========================================================
//	�_�C�X�̏���
//===========================================================
void DeleteDice(int nNumDice)
{
	switch (nNumDice)
	{
	case 1:
		g_Dice[0].bUse = false;
		g_Dice[0].DiceMotion = DICEMOTION_NONE;
		break;
	case 2:
		g_Dice[0].bUse = false;
		g_Dice[0].DiceMotion = DICEMOTION_NONE;
		g_Dice[1].bUse = false;
		g_Dice[1].DiceMotion = DICEMOTION_NONE;

		break;
	}

}

//==================================================
//�T�C�R���̍��v�l��Ԃ��֐�
//==================================================
int  GetNumDice(void)
{
	if (g_nMaxNumDice <= 1)
	{
		return -1;
	}
	else
	{
		return g_nMaxNumDice;
	}

}
//=============================================================================
//
// ���f������ [Player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER g_Player;
int g_nCntBullet;
//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Player.aModel[0].FireName = PLAYER_FILENAME0;
	g_Player.aModel[1].FireName = PLAYER_FILENAME1;
	g_Player.aModel[2].FireName = PLAYER_FILENAME2;
	g_Player.aModel[3].FireName = PLAYER_FILENAME3;
	g_Player.aModel[4].FireName = PLAYER_FILENAME4;
	g_Player.aModel[5].FireName = PLAYER_FILENAME5;
	g_Player.aModel[6].FireName = PLAYER_FILENAME6;
	g_Player.aModel[7].FireName = PLAYER_FILENAME7;
	g_Player.aModel[8].FireName = PLAYER_FILENAME8;
	g_Player.aModel[9].FireName = PLAYER_FILENAME9;
	g_Player.aModel[10].FireName = PLAYER_FILENAME10;

	// X�t�@�C���̓ǂݍ���
	for (int nCntParts = 0; nCntParts < PARTS_NUM_PLAYER; nCntParts++)
	{
		D3DXLoadMeshFromX(g_Player.aModel[nCntParts].FireName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntParts].pBuffMat,
			NULL,
			&g_Player.aModel[nCntParts].nNumMat,
			&g_Player.aModel[nCntParts].pMesh);
	}

	/*�����蔻��̐ݒ�*/
	SetPlayerVertex();

	// �ʒu�E�����̏����ݒ�
	g_Player.pos = D3DXVECTOR3(900.0f, 0.0f, -900.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);

	//�ړ��ʁE��]�ʂ̏�����
	g_Player.move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���f���̍��W�ݒ�
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 16.0f, 0.0f);//��
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 14.5f, 0.0f);//��
	g_Player.aModel[2].pos = D3DXVECTOR3(-5.0f, 11.5f, 0.0f);//�E�r
	g_Player.aModel[3].pos = D3DXVECTOR3(-13.0f, 0.0f, 0.0f);//�E��
	g_Player.aModel[4].pos = D3DXVECTOR3(5.0f, 11.5f, 0.0f);//���r
	g_Player.aModel[5].pos = D3DXVECTOR3(13.0f, 0.0f, 0.0f);//����
	g_Player.aModel[6].pos = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);//�E��
	g_Player.aModel[7].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);//�E��
	g_Player.aModel[8].pos = D3DXVECTOR3(3.0f, 0.0f, 0.0f);  //����
	g_Player.aModel[9].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);//����
	g_Player.aModel[10].pos = D3DXVECTOR3(2.0f, 0.0f, 0.0f);//����

	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E�r
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���r
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����

	g_Player.aModel[0].nIdxModelParent = -1;//��
	g_Player.aModel[1].nIdxModelParent = 0;//��
	g_Player.aModel[2].nIdxModelParent = 0;//�E�r
	g_Player.aModel[3].nIdxModelParent = 2;//�E��
	g_Player.aModel[4].nIdxModelParent = 0;//���r
	g_Player.aModel[5].nIdxModelParent = 4;//����
	g_Player.aModel[6].nIdxModelParent = 0;//�E��
	g_Player.aModel[7].nIdxModelParent = 6;//�E��
	g_Player.aModel[8].nIdxModelParent = 0;//����
	g_Player.aModel[9].nIdxModelParent = 8;//����
	g_Player.aModel[10].nIdxModelParent = 5;//����

	g_Player.nIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x,1.0f, g_Player.pos.z),D3DXVECTOR3(0.0f,0.0f,0.0f));
	SetArrow(D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_Player.nChargeTime = 0;
	g_Player.bUse = true;

	g_Player.aModel[0].motion.motion0[0] = {D3DXVECTOR3(-0.27f, -0.16f, 0.00f)};
	g_Player.aModel[1].motion.motion0[0] = { D3DXVECTOR3(0.09f, -0.25f, 0.00f) };
	g_Player.aModel[2].motion.motion0[0] = { D3DXVECTOR3(1.51f, 0.00f, 1.09f) };
	g_Player.aModel[3].motion.motion0[0] = { D3DXVECTOR3(0.00f, -1.09f, 0.00f) };
	g_Player.aModel[4].motion.motion0[0] = { D3DXVECTOR3(-1.51f, 0.00f, -1.09f) };
	g_Player.aModel[5].motion.motion0[0] = { D3DXVECTOR3(0.00f, 1.09f, 0.00f) };
	g_Player.aModel[6].motion.motion0[0] = { D3DXVECTOR3(-1.06f, 0.00f, 0.00f) };
	g_Player.aModel[7].motion.motion0[0] = { D3DXVECTOR3(-0.97f, 0.00f, 0.00f) };
	g_Player.aModel[8].motion.motion0[0] = { D3DXVECTOR3(1.16f, 0.00f, 0.00f) };
	g_Player.aModel[9].motion.motion0[0] = { D3DXVECTOR3(0.00f, 0.00f, 0.00f) };
	g_Player.aModel[10].motion.motion0[0] = { D3DXVECTOR3(0.00f, 0.00f, 1.45f) };

	g_Player.aModel[0].motion.motion0[1] = { D3DXVECTOR3(-0.27f, 0.14f, 0.00f) };
	g_Player.aModel[1].motion.motion0[1] = { D3DXVECTOR3(0.10f, 0.25f, 0.00f) };
	g_Player.aModel[2].motion.motion0[1] = { D3DXVECTOR3(-1.52f, 0.00f, 1.09f) };
	g_Player.aModel[3].motion.motion0[1] = { D3DXVECTOR3(0.00f, -1.09f, 0.00f) };
	g_Player.aModel[4].motion.motion0[1] = { D3DXVECTOR3(1.52f, 0.00f, -1.09f) };
	g_Player.aModel[5].motion.motion0[1] = { D3DXVECTOR3(0.00f, 1.09f, 0.00f) };
	g_Player.aModel[6].motion.motion0[1] = { D3DXVECTOR3(1.16f, 0.00f, 0.00f) };
	g_Player.aModel[7].motion.motion0[1] = { D3DXVECTOR3(-0.05f, 0.00f, 0.00f) };
	g_Player.aModel[8].motion.motion0[1] = { D3DXVECTOR3(-1.07f, 0.00f, 0.00f) };
	g_Player.aModel[9].motion.motion0[1] = { D3DXVECTOR3(-0.92f, 0.00f, 0.00f) };
	g_Player.aModel[10].motion.motion0[1] = { D3DXVECTOR3(0.50f, 0.00f, -0.97f) };

	g_Player.aModel[0].motion.nKeyFrame = 20;
	g_Player.aModel[1].motion.nKeyFrame = 20;
	g_Player.aModel[2].motion.nKeyFrame = 20;
	g_Player.aModel[3].motion.nKeyFrame = 20;
	g_Player.aModel[4].motion.nKeyFrame = 20;
	g_Player.aModel[5].motion.nKeyFrame = 20;
	g_Player.aModel[6].motion.nKeyFrame = 20;
	g_Player.aModel[7].motion.nKeyFrame = 20;
	g_Player.aModel[8].motion.nKeyFrame = 20;
	g_Player.aModel[9].motion.nKeyFrame = 20;
	g_Player.aModel[10].motion.nKeyFrame = 20;

	g_nCntBullet = 0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	// ���b�V���̉��
	for (int nCntMat = 0; nCntMat < PARTS_NUM_PLAYER; nCntMat++)
	{
		if (g_Player.aModel[nCntMat].pMesh != NULL)
		{
			g_Player.aModel[nCntMat].pMesh->Release();
			g_Player.aModel[nCntMat].pMesh = NULL;
		}
		/*�e�N�X�`���̉��*/
		//�}�e���A���̉��
		if (g_Player.aModel[nCntMat].pBuffMat != NULL)
		{
			g_Player.aModel[nCntMat].pBuffMat->Release();
			g_Player.aModel[nCntMat].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//�ϐ��錾
	Camera *pCamera;
	pCamera = GetCamera();


	if (g_Player.bUse == true)
	{
		//OldPos�ɑO���Pos����
		g_Player.OldPos = g_Player.pos;

		//���f���̈ړ��Ɖ�]
		if (GetKeyboardPress(DIK_A) == true)//��
		{
			if (GetKeyboardPress(DIK_S) == true)//��
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * 0.25f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * -0.75f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * -0.75f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_W) == true)//��
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * 0.75f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * -0.25f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * -0.25f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
			else
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * 0.5f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * -0.5f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * -0.5f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)//��
		{
			if (GetKeyboardPress(DIK_S) == true)//��
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * -0.25f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_W) == true)//��
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * -0.75f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
			else
			{
				g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI * -0.5f) - g_Player.rot.y);
				g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)//��
		{
			g_Player.rotMove.y = (pCamera->rot.y - g_Player.rot.y);
			g_Player.move.x += sinf((D3DX_PI)+pCamera->rot.y) * PLAYER_MOVE_SPEED;
			g_Player.move.z += cosf((D3DX_PI)+pCamera->rot.y) * PLAYER_MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_W) == true)//��
		{
			g_Player.rotMove.y = (pCamera->rot.y + (D3DX_PI)-g_Player.rot.y);
			g_Player.move.x += sinf((0.0f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
			g_Player.move.z += cosf((0.0f) + pCamera->rot.y) * PLAYER_MOVE_SPEED;
		}

		//�ړ��W���̉��Z
		g_Player.move += (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - g_Player.move) * 0.05f;

		if (g_Player.pos.x < -1000.0f && g_Player.move.x < 0 ||
			g_Player.pos.x > 1000.0f && g_Player.move.x > 0)
		{
			g_Player.move.x = 0.0f;
		}
		if (g_Player.pos.z < -1000.0f && g_Player.move.z < 0 ||
			g_Player.pos.z > 1000.0f && g_Player.move.z > 0)
		{
			g_Player.move.z = 0.0f;
		}
		if (g_Player.pos.y < 0.0f && g_Player.move.y < 0)
		{
			g_Player.move.y = 0.0f;
		}

		//�G�t�F�N�g�ݒu
		if (g_Player.move.x > 0.5f ||
			g_Player.move.x < -0.5f ||
			g_Player.move.z > 0.5f ||
			g_Player.move.z < -0.5f)
		{
			SetEffect(D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.y) * 7.0f, g_Player.pos.y, g_Player.pos.z + cosf(g_Player.rot.y) * 7.0f),
				g_Player.rot,
				D3DXCOLOR(0.0f, 0.7f, 1.0f, 1.0f),
				3.0f,
				2.0f);
		}

		//move�̗ʂ���pos�𓮂���
		g_Player.pos += g_Player.move;
		if (CollisionMeshWall(&g_Player.pos, &g_Player.OldPos) == true)
		{
			g_Player.pos = g_Player.OldPos;
			//g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		//��]���x�̊ۂߍ���
		g_Player.rotMove.y = RotOverwhelming(g_Player.rotMove.y);

		//��]�ʂ̉��Z
		g_Player.rot.y += g_Player.rotMove.y * PLAYER_ROTMOVE_COEFFICIENT;
		g_Player.rot.y = RotOverwhelming(g_Player.rot.y);

		//��]�ʂ̃��Z�b�g
		g_Player.rotMove.y = 0.0f;

		/*�����蔻��*/
		if (CollisionNpc(&g_Player.pos,
			&g_Player.OldPos,
			&g_Player.move,
			&g_Player.VtxMin,
			&g_Player.VtxMax) == true)
		{

		}
		if (CollisionModel(&g_Player.pos,
			&g_Player.OldPos,
			&g_Player.move,
			&g_Player.VtxMin,
			&g_Player.VtxMax) == true)
		{
			g_Player.nChargeTime++;
		}
		else
		{
			g_Player.nChargeTime = 0;

		}

		if (g_Player.nChargeTime == 50)
		{
			SetGameState(GAMESTATE_END);
			//g_Player.nChargeTime = 0;
		}

		if (CollisionPiller(&g_Player.pos, &g_Player.OldPos, &g_Player.move, &g_Player.VtxMin, &g_Player.VtxMax) == true)
		{

		}

		//�e�̍X�V
		SetPositionShadow(g_Player.nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
		SetSizeShadow(g_Player.nIdxShadow, g_Player.pos.y, 20.0f);

		//���̍X�V
		SetPositionArrow(D3DXVECTOR3(g_Player.pos.x, 10.0f, g_Player.pos.z));

		//�e�̔���
		if (GetKeyboardTrigger(DIK_RETURN) == true ||
			GetKeyboardTrigger(DIK_SPACE) == true )
		{
			SetBullet(D3DXVECTOR3(g_Player.pos.x - sinf(g_Player.rot.y) * 15.0f, g_Player.pos.y + 20.0f, g_Player.pos.z - cosf(g_Player.rot.y) * 15.0f),
				g_Player.rot,
				D3DXVECTOR3(5.0f, 0.0f, 5.0f),
				3.0f,
				3.0f,
				BULLETTYPE_PLAYER);
			SetBullet(D3DXVECTOR3(g_Player.pos.x - sinf(g_Player.rot.y) * 15.0f, g_Player.pos.y + 20.0f, g_Player.pos.z - cosf(g_Player.rot.y) * 15.0f),
				D3DXVECTOR3(g_Player.rot.x, g_Player.rot.y + 0.1f, g_Player.rot.z),
				D3DXVECTOR3(5.0f, 0.0f, 5.0f),
				3.0f,
				3.0f,
				BULLETTYPE_PLAYER);
			SetBullet(D3DXVECTOR3(g_Player.pos.x - sinf(g_Player.rot.y) * 15.0f, g_Player.pos.y + 20.0f, g_Player.pos.z - cosf(g_Player.rot.y) * 15.0f),
				D3DXVECTOR3(g_Player.rot.x, g_Player.rot.y - 0.1f, g_Player.rot.z),
				D3DXVECTOR3(5.0f, 0.0f, 5.0f),
				3.0f,
				3.0f,
				BULLETTYPE_PLAYER);

			PlaySound(SOUND_LABEL_SE000);
		}



		//�A�j���[�V����
		if (fabs(g_Player.move.x) >= 0.1f ||
			fabs(g_Player.move.z) >= 0.1f)
		{
			for (int nCntModel = 0; nCntModel < PARTS_NUM_PLAYER; nCntModel++)
			{
				g_Player.aModel[nCntModel].nMotionCount++;

				if (g_Player.aModel[nCntModel].nMotionCount % g_Player.aModel[nCntModel].motion.nKeyFrame == 0)
				{
					g_Player.aModel[nCntModel].nMotionNum = (g_Player.aModel[nCntModel].nMotionNum + 1) % 2;

				}
				g_Player.aModel[nCntModel].rot +=
					((g_Player.aModel[nCntModel].motion.motion0[g_Player.aModel[nCntModel].nMotionNum]
						- g_Player.aModel[nCntModel].rot) / (g_Player.aModel[nCntModel].motion.nKeyFrame * 1.0f));

				RotOverwhelming(g_Player.aModel[nCntModel].rot.x);
				RotOverwhelming(g_Player.aModel[nCntModel].rot.y);
				RotOverwhelming(g_Player.aModel[nCntModel].rot.z);

			}
		}
		else
		{
			g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��
			g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��
			g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 1.0f);//�E�r
			g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
			g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, -1.0f);//���r
			g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
			g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
			g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
			g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
			g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
			g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans,mtxParent;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	if (g_Player.bUse == true)
	{


		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player.rot.y,
			g_Player.rot.x,
			g_Player.rot.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld,
			&g_Player.mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_Player.pos.x,
			g_Player.pos.y,
			g_Player.pos.z);

		D3DXMatrixMultiply(&g_Player.mtxWorld,
			&g_Player.mtxWorld,
			&mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

		for (int nCntModel = 0; nCntModel < PARTS_NUM_PLAYER; nCntModel++)
		{
			if (g_Player.aModel[nCntModel].nIdxModelParent == -1)
			{//�e���f�����Ȃ����
				mtxParent = g_Player.mtxWorld;
			}
			else
			{
				mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Player.aModel[nCntModel].rot.y,
				g_Player.aModel[nCntModel].rot.x,
				g_Player.aModel[nCntModel].rot.z);

			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
				&g_Player.aModel[nCntModel].mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Player.aModel[nCntModel].pos.x,
				g_Player.aModel[nCntModel].pos.y,
				g_Player.aModel[nCntModel].pos.z);

			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
				&g_Player.aModel[nCntModel].mtxWorld,
				&mtxTrans);

			//�e�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
				&g_Player.aModel[nCntModel].mtxWorld,
				&mtxParent);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				/*�e�N�X�`���̐ݒ�*/
				pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

											 // ���f��(�p�[�c)�̕`��
				g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);

		}
	}
}
//=============================================================================
// �\���̂̎擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

//=============================================================================
// �ő�E�ŏ��̒��_���W���擾
//=============================================================================
void SetPlayerVertex(void)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	g_Player.VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Player.VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//���_���̎擾
	for (int nCntParts = 0; nCntParts < PARTS_NUM_PLAYER; nCntParts++)
	{
		nNumVtx = g_Player.aModel[nCntParts].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntParts].pMesh->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_Player.aModel[nCntParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	/*	pVtxBuff += */
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

														//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
														//x
			if (g_Player.VtxMin.x > vtx.x)
			{
				g_Player.VtxMin.x = vtx.x;
			}
			if (g_Player.VtxMax.x < vtx.x)
			{
				g_Player.VtxMax.x = vtx.x;
			}

			//y
			if (g_Player.VtxMin.y > vtx.y)
			{
				g_Player.VtxMin.y = vtx.y;
			}
			if (g_Player.VtxMax.y < vtx.y)
			{
				g_Player.VtxMax.y = vtx.y;
			}

			//z
			if (g_Player.VtxMin.z > vtx.z)
			{
				g_Player.VtxMin.z = vtx.z;
			}
			if (g_Player.VtxMax.z < vtx.z)
			{
				g_Player.VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//�T�C�Y���|�C���^��i�߂�
		}
		//�A�����b�N
		g_Player.aModel[nCntParts].pMesh->UnlockVertexBuffer();


	}
}

bool CollisionPlayer(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	if (g_Player.bUse == true)
	{


		if (g_Player.VtxMin.z + g_Player.pos.z <= pPos->z + pVtxMax->z&&
			g_Player.VtxMax.z + g_Player.pos.z >= pPos->z + pVtxMin->z)
		{
			if (g_Player.VtxMin.x + g_Player.pos.x <= pPos->x + pVtxMax->x&&
				g_Player.VtxMin.x + g_Player.pos.x >= pOldPos->x + pVtxMax->x)
			{//������E
				SetExplosion(g_Player.pos,
					g_Player.rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					6.0f,
					6.0f);

				return true;
			}
			if (g_Player.VtxMax.x + g_Player.pos.x >= pPos->x + pVtxMin->x&&
				g_Player.VtxMax.x + g_Player.pos.x <= pOldPos->x + pVtxMin->x)
			{//�E���獶
				SetExplosion(g_Player.pos,
					g_Player.rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					6.0f,
					6.0f);

				return true;
			}
		}

		if (g_Player.VtxMin.x + g_Player.pos.x <= pPos->x + pVtxMax->x&&
			g_Player.VtxMax.x + g_Player.pos.x >= pPos->x + pVtxMin->x)
		{
			if (g_Player.VtxMin.z + g_Player.pos.z <= pPos->z + pVtxMax->z&&
				g_Player.VtxMin.z + g_Player.pos.z >= pOldPos->z + pVtxMax->z)
			{//��O���牜
				SetExplosion(g_Player.pos,
					g_Player.rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					6.0f,
					6.0f);

				return true;
			}
			if (g_Player.VtxMax.z + g_Player.pos.z >= pPos->z + pVtxMin->z&&
				g_Player.VtxMax.z + g_Player.pos.z <= pOldPos->z + pVtxMin->z)
			{//�������O
				SetExplosion(g_Player.pos,
					g_Player.rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					6.0f,
					6.0f);

				return true;
			}
		}
	}
			return false;
}

//=============================================================================
// �����������֐�
//=============================================================================
void DeletePlayer(void)
{
	g_Player.bUse = false;
	SetExplosion(g_Player.pos,
		g_Player.rot,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		20.0f,
		20.0f);

	PlaySound(SOUND_LABEL_SE005);

}
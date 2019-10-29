//=============================================================================
//
// ���f������ [npc.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "npc.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshNPC[MAX_NUM_NPC] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatNPC[MAX_NUM_NPC] = {};	//�}�e���A�����ւ̃|�C���^

NPC g_NPC[MAX_NUM_NPC];
//=============================================================================
// ����������
//=============================================================================
void InitNpc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int nCntNpc = 0; nCntNpc < MAX_NUM_NPC; nCntNpc++)
	{

		g_NPC[nCntNpc].aModel[0].FireName = NPC_FILENAME0;
		g_NPC[nCntNpc].aModel[1].FireName = NPC_FILENAME1;
		g_NPC[nCntNpc].aModel[2].FireName = NPC_FILENAME2;
		g_NPC[nCntNpc].aModel[3].FireName = NPC_FILENAME3;
		g_NPC[nCntNpc].aModel[4].FireName = NPC_FILENAME4;
		g_NPC[nCntNpc].aModel[5].FireName = NPC_FILENAME5;
		g_NPC[nCntNpc].aModel[6].FireName = NPC_FILENAME6;
		g_NPC[nCntNpc].aModel[7].FireName = NPC_FILENAME7;
		g_NPC[nCntNpc].aModel[8].FireName = NPC_FILENAME8;
		g_NPC[nCntNpc].aModel[9].FireName = NPC_FILENAME9;
		g_NPC[nCntNpc].aModel[10].FireName = NPC_FILENAME10;

		for (int nCntParts = 0; nCntParts < PARTS_NUM_NPC; nCntParts++)
		{
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(g_NPC[nCntNpc].aModel[nCntParts].FireName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_NPC[nCntNpc].aModel[nCntParts].pBuffMat,
				NULL,
				&g_NPC[nCntNpc].aModel[nCntParts].nNumMat,
				&g_NPC[nCntNpc].aModel[nCntParts].pMesh);
		}
		/*�����蔻��̐ݒ�*/
		SetNpcVertex(nCntNpc);
		// �ʒu�E�����̏����ݒ�
		//g_NPC[nCntNpc].pos = D3DXVECTOR3(20.0f, 0.0f, 0.0f);
		g_NPC[nCntNpc].rot = D3DXVECTOR3(0.0f, (rand() % 628 - 314) * 0.01f, 0.0f);
		g_NPC[nCntNpc].bUse = true;
		//�ړ��ʁE��]�ʂ̏�����
		g_NPC[nCntNpc].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_NPC[nCntNpc].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_NPC[nCntNpc].state = NPCSTATE_MOVE;
		g_NPC[nCntNpc].nCntMove = 0;
		g_NPC[nCntNpc].npcAI = AI_CHASE;
		g_NPC[nCntNpc].nIdxShadow = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_NPC[nCntNpc].nCntBullet = 0;
		g_NPC[nCntNpc].aModel[0].pos = D3DXVECTOR3(0.0f, 16.0f, 0.0f);//��
		g_NPC[nCntNpc].aModel[1].pos = D3DXVECTOR3(0.0f, 14.5f, 0.0f);//��
		g_NPC[nCntNpc].aModel[2].pos = D3DXVECTOR3(-5.0f, 11.5f, 0.0f);//�E�r
		g_NPC[nCntNpc].aModel[3].pos = D3DXVECTOR3(-13.0f, 0.0f, 0.0f);//�E��
		g_NPC[nCntNpc].aModel[4].pos = D3DXVECTOR3(5.0f, 11.5f, 0.0f);//���r
		g_NPC[nCntNpc].aModel[5].pos = D3DXVECTOR3(13.0f, 0.0f, 0.0f);//����
		g_NPC[nCntNpc].aModel[6].pos = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);//�E��
		g_NPC[nCntNpc].aModel[7].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);//�E��
		g_NPC[nCntNpc].aModel[8].pos = D3DXVECTOR3(3.0f, 0.0f, 0.0f);  //����
		g_NPC[nCntNpc].aModel[9].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);//����
		g_NPC[nCntNpc].aModel[10].pos = D3DXVECTOR3(2.0f, 0.0f, 0.0f);//����

		g_NPC[nCntNpc].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��
		g_NPC[nCntNpc].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��
		g_NPC[nCntNpc].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E�r
		g_NPC[nCntNpc].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
		g_NPC[nCntNpc].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���r
		g_NPC[nCntNpc].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_NPC[nCntNpc].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
		g_NPC[nCntNpc].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
		g_NPC[nCntNpc].aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_NPC[nCntNpc].aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_NPC[nCntNpc].aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����

		g_NPC[nCntNpc].aModel[0].nIdxModelParent = -1;//��
		g_NPC[nCntNpc].aModel[1].nIdxModelParent = 0;//��
		g_NPC[nCntNpc].aModel[2].nIdxModelParent = 0;//�E�r
		g_NPC[nCntNpc].aModel[3].nIdxModelParent = 2;//�E��
		g_NPC[nCntNpc].aModel[4].nIdxModelParent = 0;//���r
		g_NPC[nCntNpc].aModel[5].nIdxModelParent = 4;//����
		g_NPC[nCntNpc].aModel[6].nIdxModelParent = 0;//�E��
		g_NPC[nCntNpc].aModel[7].nIdxModelParent = 6;//�E��
		g_NPC[nCntNpc].aModel[8].nIdxModelParent = 0;//����
		g_NPC[nCntNpc].aModel[9].nIdxModelParent = 8;//����
		g_NPC[nCntNpc].aModel[10].nIdxModelParent = 5;//����

		g_NPC[nCntNpc].aModel[0].motion.motion0[0] = { D3DXVECTOR3(-0.27f, -0.16f, 0.00f) };
		g_NPC[nCntNpc].aModel[1].motion.motion0[0] = { D3DXVECTOR3(0.09f, -0.25f, 0.00f) };
		g_NPC[nCntNpc].aModel[2].motion.motion0[0] = { D3DXVECTOR3(1.51f, 0.00f, 1.09f) };
		g_NPC[nCntNpc].aModel[3].motion.motion0[0] = { D3DXVECTOR3(0.00f, -1.09f, 0.00f) };
		g_NPC[nCntNpc].aModel[4].motion.motion0[0] = { D3DXVECTOR3(-1.51f, 0.00f, -1.09f) };
		g_NPC[nCntNpc].aModel[5].motion.motion0[0] = { D3DXVECTOR3(0.00f, 1.09f, 0.00f) };
		g_NPC[nCntNpc].aModel[6].motion.motion0[0] = { D3DXVECTOR3(-1.06f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[7].motion.motion0[0] = { D3DXVECTOR3(-0.97f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[8].motion.motion0[0] = { D3DXVECTOR3(1.16f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[9].motion.motion0[0] = { D3DXVECTOR3(0.00f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[10].motion.motion0[0] = { D3DXVECTOR3(0.00f, 0.00f, 1.45f) };

		g_NPC[nCntNpc].aModel[0].motion.motion0[1] = { D3DXVECTOR3(-0.27f, 0.14f, 0.00f) };
		g_NPC[nCntNpc].aModel[1].motion.motion0[1] = { D3DXVECTOR3(0.10f, 0.25f, 0.00f) };
		g_NPC[nCntNpc].aModel[2].motion.motion0[1] = { D3DXVECTOR3(-1.52f, 0.00f, 1.09f) };
		g_NPC[nCntNpc].aModel[3].motion.motion0[1] = { D3DXVECTOR3(0.00f, -1.09f, 0.00f) };
		g_NPC[nCntNpc].aModel[4].motion.motion0[1] = { D3DXVECTOR3(1.52f, 0.00f, -1.09f) };
		g_NPC[nCntNpc].aModel[5].motion.motion0[1] = { D3DXVECTOR3(0.00f, 1.09f, 0.00f) };
		g_NPC[nCntNpc].aModel[6].motion.motion0[1] = { D3DXVECTOR3(1.16f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[7].motion.motion0[1] = { D3DXVECTOR3(-0.05f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[8].motion.motion0[1] = { D3DXVECTOR3(-1.07f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[9].motion.motion0[1] = { D3DXVECTOR3(-0.92f, 0.00f, 0.00f) };
		g_NPC[nCntNpc].aModel[10].motion.motion0[1] = { D3DXVECTOR3(0.50f, 0.00f, -0.97f) };

		g_NPC[nCntNpc].aModel[0].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[1].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[2].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[3].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[4].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[5].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[6].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[7].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[8].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[9].motion.nKeyFrame = 20;
		g_NPC[nCntNpc].aModel[10].motion.nKeyFrame = 20;


	}
	g_NPC[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_NPC[1].pos = D3DXVECTOR3(-300.0f, 0.0f, -300.0f);
	g_NPC[2].pos = D3DXVECTOR3(-700.0f, 0.0f, -500.0f);
	g_NPC[3].pos = D3DXVECTOR3(-400.0f, 0.0f, 900.0f);



}

//=============================================================================
// �I������
//=============================================================================
void UninitNpc(void)
{
	// ���b�V���̉��
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_NPC; nCntMesh++)
	{
		if (g_pMeshNPC[nCntMesh] != NULL)
		{
			g_pMeshNPC[nCntMesh]->Release();
			g_pMeshNPC[nCntMesh] = NULL;
		}
		/*�e�N�X�`���̉��*/
		//�}�e���A���̉��
		if (g_pBuffMatNPC[nCntMesh] != NULL)
		{
			g_pBuffMatNPC[nCntMesh]->Release();
			g_pBuffMatNPC[nCntMesh] = NULL;
		}
	}
	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateNpc(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	for (int nCntNpc = 0; nCntNpc < MAX_NUM_NPC; nCntNpc++)
	{
		if (g_NPC[nCntNpc].bUse == true)
		{
			if (pPlayer->bUse == true)
			{
				//���݂�pos��posOld�Ɋi�[
				g_NPC[nCntNpc].posOld = g_NPC[nCntNpc].pos;
				switch (g_NPC[nCntNpc].state)
				{//���
				case NPCSTATE_MOVE:			//��������
					//�ړ��A���S���Y��
					switch (g_NPC[nCntNpc].npcAI)
					{
					case AI_RANDOM://�����_��
						g_NPC[nCntNpc].move.x = sinf(g_NPC[nCntNpc].rot.y + D3DX_PI) * NPC_MOVE_SPEED;
						g_NPC[nCntNpc].move.z = cosf(g_NPC[nCntNpc].rot.y + D3DX_PI) * NPC_MOVE_SPEED;

						//�ړ��W���̉��Z
						g_NPC[nCntNpc].move.x += (0.0f - g_NPC[nCntNpc].move.x) * 0.2f;
						g_NPC[nCntNpc].move.z += (0.0f - g_NPC[nCntNpc].move.z) * 0.2f;

						if (g_NPC[nCntNpc].pos.x < -1000.0f && g_NPC[nCntNpc].move.x < 0 ||
							g_NPC[nCntNpc].pos.x > 1000.0f && g_NPC[nCntNpc].move.x > 0)
						{
							g_NPC[nCntNpc].move.x = 0.0f;
							g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
						}
						if (g_NPC[nCntNpc].pos.z < -1000.0f && g_NPC[nCntNpc].move.z < 0 ||
							g_NPC[nCntNpc].pos.z > 1000.0f && g_NPC[nCntNpc].move.z > 0)
						{
							g_NPC[nCntNpc].move.z = 0.0f;
							g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
						}

						g_NPC[nCntNpc].nMoveCount++;
						if (g_NPC[nCntNpc].nMoveCount % ((rand() % 10) + 200) == 0)
						{
							g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
						}

						g_NPC[nCntNpc].rot.y = RotOverwhelming(g_NPC[nCntNpc].rot.y);

						break;
					case AI_CHASE://�ǐ�
						if ((fabs(pPlayer->pos.x - g_NPC[nCntNpc].pos.x) <= CHASE_RANGE ||
							fabs(pPlayer->pos.z - g_NPC[nCntNpc].pos.z) <= CHASE_RANGE) &&
							CollisionMeshWall(&g_NPC[nCntNpc].pos, &pPlayer->pos) == false)
						{
							float rotY = 
								atan2f(pPlayer->OldPos.x - g_NPC[nCntNpc].pos.x, pPlayer->OldPos.z - g_NPC[nCntNpc].pos.z);

							g_NPC[nCntNpc].move.x = sinf(rotY) * NPC_MOVE_SPEED;
							g_NPC[nCntNpc].move.z = cosf(rotY) * NPC_MOVE_SPEED;
							g_NPC[nCntNpc].rot.y = rotY + D3DX_PI;
							//�e�̔���
							g_NPC[nCntNpc].nCntBullet++;
							if (g_NPC[nCntNpc].nCntBullet % 100 == 0)
							{
								SetBullet(D3DXVECTOR3(g_NPC[nCntNpc].pos.x, 15.0f, g_NPC[nCntNpc].pos.z),
									g_NPC[nCntNpc].rot,
									D3DXVECTOR3(5.0f, 0.0f, 5.0f),
									3.0f,
									3.0f,
									BULLETTYPE_ENEMY);

							}

						}
						else
						{
							g_NPC[nCntNpc].nCntBullet = -1;

							g_NPC[nCntNpc].move.x = sinf(g_NPC[nCntNpc].rot.y + D3DX_PI) * NPC_MOVE_SPEED;
							g_NPC[nCntNpc].move.z = cosf(g_NPC[nCntNpc].rot.y + D3DX_PI) * NPC_MOVE_SPEED;

							//�ړ��W���̉��Z
							g_NPC[nCntNpc].move.x += (0.0f - g_NPC[nCntNpc].move.x) * 0.2f;
							g_NPC[nCntNpc].move.z += (0.0f - g_NPC[nCntNpc].move.z) * 0.2f;

							if (g_NPC[nCntNpc].pos.x < -1000.0f && g_NPC[nCntNpc].move.x < 0 ||
								g_NPC[nCntNpc].pos.x > 1000.0f && g_NPC[nCntNpc].move.x > 0)
							{
								g_NPC[nCntNpc].move.x = 0.0f;
								g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
							}
							if (g_NPC[nCntNpc].pos.z < -1000.0f && g_NPC[nCntNpc].move.z < 0 ||
								g_NPC[nCntNpc].pos.z > 1000.0f && g_NPC[nCntNpc].move.z > 0)
							{
								g_NPC[nCntNpc].move.z = 0.0f;
								g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
							}

							g_NPC[nCntNpc].nMoveCount++;
							if (g_NPC[nCntNpc].nMoveCount % ((rand() % 10) + 200) == 0)
							{
								g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;
							}

							g_NPC[nCntNpc].rot.y = RotOverwhelming(g_NPC[nCntNpc].rot.y);
						}

						break;
					}

					//move�̗ʂ���pos�𓮂���
					g_NPC[nCntNpc].pos += g_NPC[nCntNpc].move;

					if (CollisionMeshWall(&g_NPC[nCntNpc].pos, &g_NPC[nCntNpc].posOld) == true)
					{//���ǂ̓����蔻��
						g_NPC[nCntNpc].pos = g_NPC[nCntNpc].posOld;
						g_NPC[nCntNpc].rot.y += (rand() % 314 - 157) * 0.01f;

					}

					break;

				case NPCSTATE_DAMAGE:			//�_���[�W���
					g_NPC[nCntNpc].move.x = 0.0f;
					g_NPC[nCntNpc].move.z = 0.0f;
					g_NPC[nCntNpc].nCntMove++;

					if (g_NPC[nCntNpc].nCntMove >= 150)
					{
						g_NPC[nCntNpc].state = NPCSTATE_MOVE;
						g_NPC[nCntNpc].nCntMove = 0;
						float rotY =
							atan2f(pPlayer->OldPos.x - g_NPC[nCntNpc].pos.x, pPlayer->OldPos.z - g_NPC[nCntNpc].pos.z);
						g_NPC[nCntNpc].rot.y = rotY + D3DX_PI;


					}
					break;
				}

				//�e�̍X�V
				SetPositionShadow(g_NPC[nCntNpc].nIdxShadow, D3DXVECTOR3(g_NPC[nCntNpc].pos.x, 0.0f, g_NPC[nCntNpc].pos.z));
				SetSizeShadow(g_NPC[nCntNpc].nIdxShadow, g_NPC[nCntNpc].pos.y, 5.0f);

				//�A�j���[�V����
				if (fabs(g_NPC[nCntNpc].move.x) >= 0.1f ||
					fabs(g_NPC[nCntNpc].move.z) >= 0.1f)
				{
					for (int nCntModel = 0; nCntModel < PARTS_NUM_NPC; nCntModel++)
					{
						g_NPC[nCntNpc].aModel[nCntModel].nMotionCount++;

						if (g_NPC[nCntNpc].aModel[nCntModel].nMotionCount % g_NPC[nCntNpc].aModel[nCntModel].motion.nKeyFrame == 0)
						{
							g_NPC[nCntNpc].aModel[nCntModel].nMotionNum = (g_NPC[nCntNpc].aModel[nCntModel].nMotionNum + 1) % 2;

						}

						g_NPC[nCntNpc].aModel[nCntModel].rot +=
							(g_NPC[nCntNpc].aModel[nCntModel].motion.motion0[g_NPC[nCntNpc].aModel[nCntModel].nMotionNum]
								- g_NPC[nCntNpc].aModel[nCntModel].rot) / (g_NPC[nCntNpc].aModel[nCntModel].motion.nKeyFrame * 1.0f);
					}
				}
				else
				{
					g_NPC[nCntNpc].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��
					g_NPC[nCntNpc].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��
					g_NPC[nCntNpc].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 1.0f);//�E�r
					g_NPC[nCntNpc].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
					g_NPC[nCntNpc].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, -1.0f);//���r
					g_NPC[nCntNpc].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
					g_NPC[nCntNpc].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
					g_NPC[nCntNpc].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��
					g_NPC[nCntNpc].aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
					g_NPC[nCntNpc].aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
					g_NPC[nCntNpc].aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����

				}
			}

			//// ���C�g�̕����̐ݒ�
			//D3DXVECTOR3 vecDir;
			//D3DXVec3Normalize(&vecDir, &g_NPC[nCntNpc].rot);
			//g_NPC[nCntNpc].light.Direction = vecDir;


		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawNpc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	for (int nCntNpc = 0; nCntNpc < MAX_NUM_NPC; nCntNpc++)
	{
		if (g_NPC[nCntNpc].bUse == true)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_NPC[nCntNpc].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_NPC[nCntNpc].rot.y,
				g_NPC[nCntNpc].rot.x,
				g_NPC[nCntNpc].rot.z);

			D3DXMatrixMultiply(&g_NPC[nCntNpc].mtxWorld,
				&g_NPC[nCntNpc].mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_NPC[nCntNpc].pos.x,
				g_NPC[nCntNpc].pos.y,
				g_NPC[nCntNpc].pos.z);

			D3DXMatrixMultiply(&g_NPC[nCntNpc].mtxWorld,
				&g_NPC[nCntNpc].mtxWorld,
				&mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_NPC[nCntNpc].mtxWorld);

			for (int nCntModel = 0; nCntModel < PARTS_NUM_PLAYER; nCntModel++)
			{
				if (g_NPC[nCntNpc].aModel[nCntModel].nIdxModelParent == -1)
				{//�e���f�����Ȃ����
					mtxParent = g_NPC[nCntNpc].mtxWorld;
				}
				else
				{
					mtxParent = g_NPC[nCntNpc].aModel[g_NPC[nCntNpc].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_NPC[nCntNpc].aModel[nCntModel].rot.y,
					g_NPC[nCntNpc].aModel[nCntModel].rot.x,
					g_NPC[nCntNpc].aModel[nCntModel].rot.z);

				D3DXMatrixMultiply(&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans,
					g_NPC[nCntNpc].aModel[nCntModel].pos.x,
					g_NPC[nCntNpc].aModel[nCntModel].pos.y,
					g_NPC[nCntNpc].aModel[nCntModel].pos.z);

				D3DXMatrixMultiply(&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&mtxTrans);

				//�e�̃}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&g_NPC[nCntNpc].aModel[nCntModel].mtxWorld,
					&mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_NPC[nCntNpc].aModel[nCntModel].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_NPC[nCntNpc].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_NPC[nCntNpc].aModel[nCntModel].nNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					/*�e�N�X�`���̐ݒ�*/
					pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

					 // ���f��(�p�[�c)�̕`��
					g_NPC[nCntNpc].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);

			}
		}
	}

}
//=============================================================================
// �e�ȊO�Ƃ̓����蔻��̏���
//=============================================================================
bool CollisionNpc(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldPos, D3DXVECTOR3 *pMove,D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
{
	//�ϐ��錾
	bool bLand = false;

	for (int nCntData = 0; nCntData < MAX_NUM_NPC; nCntData++)
	{
		if (g_NPC[nCntData].bUse == true)
		{
			if (g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//������E
					pPos->x = g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x - pVtxMax->x;
					pMove->x = 0.0f;
				}
				if (g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//�E���獶
					pPos->x = g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x - pVtxMin->x;
					pMove->x = 0.0f;
				}
			}

			if (g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//��O���牜
					pPos->z = g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z - pVtxMax->z;
					pMove->z = 0.0f;
				}
				if (g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//�������O
					pPos->z = g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z - pVtxMin->z;
					pMove->z = 0.0f;
				}
			}
		}
	}
	return bLand;
}

//=============================================================================
// �e�Ƃ̓����蔻��̏���
//=============================================================================

int CollisionBullet(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pOldPos,D3DXVECTOR3 *pMove,D3DXVECTOR3 *pVtxMin,D3DXVECTOR3 *pVtxMax, int *pDeleteIdxNpc)
{
	for (int nCntData = 0; nCntData < MAX_NUM_NPC; nCntData++)
	{
		if (g_NPC[nCntData].bUse == true)
		{
			if (g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//������E
					pDeleteIdxNpc = (int*)nCntData;

					return nCntData;

				}
				if (g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//�E���獶
					pDeleteIdxNpc = (int*)nCntData;

					return nCntData;

				}
			}

			if (g_NPC[nCntData].VtxMin.x + g_NPC[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_NPC[nCntData].VtxMax.x + g_NPC[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_NPC[nCntData].VtxMin.z + g_NPC[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//��O���牜
					pDeleteIdxNpc = (int*)nCntData;

					return nCntData;

				}
				if (g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_NPC[nCntData].VtxMax.z + g_NPC[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//�������O
					pDeleteIdxNpc = (int*)nCntData;

					return nCntData;
				}
			}
		}
	}
	return -1;
}

//=============================================================================
// �ő�E�ŏ��̒��_���W���擾
//=============================================================================
void SetNpcVertex(int nCntNpc)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	g_NPC[nCntNpc].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_NPC[nCntNpc].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);
	for (int nCntParts = 0; nCntParts < PARTS_NUM_NPC; nCntParts++)
	{

		//���_���̎擾
		nNumVtx = g_NPC[nCntNpc].aModel[nCntParts].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_NPC[nCntNpc].aModel[nCntParts].pMesh->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_NPC[nCntNpc].aModel[nCntParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

			//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
			//x
			if (g_NPC[nCntNpc].VtxMin.x > vtx.x)
			{
				g_NPC[nCntNpc].VtxMin.x = vtx.x;
			}
			if (g_NPC[nCntNpc].VtxMax.x < vtx.x)
			{
				g_NPC[nCntNpc].VtxMax.x = vtx.x;
			}

			//y
			if (g_NPC[nCntNpc].VtxMin.y > vtx.y)
			{
				g_NPC[nCntNpc].VtxMin.y = vtx.y;
			}
			if (g_NPC[nCntNpc].VtxMax.y < vtx.y)
			{
				g_NPC[nCntNpc].VtxMax.y = vtx.y;
			}

			//z
			if (g_NPC[nCntNpc].VtxMin.z > vtx.z)
			{
				g_NPC[nCntNpc].VtxMin.z = vtx.z;
			}
			if (g_NPC[nCntNpc].VtxMax.z < vtx.z)
			{
				g_NPC[nCntNpc].VtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}
		//�A�����b�N
		g_NPC[nCntNpc].aModel[nCntParts].pMesh->UnlockVertexBuffer();
	}
}

//=============================================================================
// npc����������
//=============================================================================
void DeleteNpc(int nIdxNpc)
{
	//g_NPC[nIdxNpc].bUse = false;
	//DeleteShadow(g_NPC[nIdxNpc].nIdxShadow);
	g_NPC[nIdxNpc].state = NPCSTATE_DAMAGE;
	g_NPC[nIdxNpc].nCntMove = 0;
	PlaySound(SOUND_LABEL_SE004);
}

//=============================================================================
// npc�̐��𒲂ׂ鏈��
//=============================================================================
bool CountUseNpc(void)
{
	int nCntNumNpc = 0;
	for (int nCntData = 0; nCntData < MAX_NUM_NPC; nCntData++)
	{
		if (g_NPC[nCntData].bUse == true)
		{
			nCntNumNpc++;
		}
	}

	if (nCntNumNpc != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//
//
//
NPC *GetNPC(void)
{
	return &g_NPC[0];
}
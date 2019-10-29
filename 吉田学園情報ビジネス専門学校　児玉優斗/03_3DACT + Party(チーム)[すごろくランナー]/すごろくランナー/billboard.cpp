//=============================================================================
//
// �r���{�[�h�̏��� [billboard.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"
#include "wall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BILLBOARD_TEXTURE_NAME   "data/TEXTURE/ivy000.png"          // �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureBillboard = NULL;  // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;  // ���_�o�b�t�@�ւ̃|�C���^
Billboard               g_aBillboard[MAX_BILLBOARD]; // �r���{�[�h�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_���̍쐬
	MakeVertexBillboard(pDevice);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// �r���{�[�h�̑������J��Ԃ�
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ʒu��������
		g_aBillboard[nCntBillboard].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �ړ��ʂ�������
		g_aBillboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // ������������
		g_aBillboard[nCntBillboard].fWidth = 0.0f;                          // ����������
		g_aBillboard[nCntBillboard].fHeight = 0.0f;                         // ������������
		g_aBillboard[nCntBillboard].bUse = false;                           // �g�p���Ă��Ȃ���Ԃɂ���
		g_aBillboard[nCntBillboard].nIdxShadow = 0;                         // �e�̔ԍ���������
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// �r���{�[�h�̑������J��Ԃ�
		if (g_aBillboard[nCntBillboard].bUse == true)
		{// �r���{�[�h���g�p����Ă���
			SetPositionShadow(g_aBillboard[nCntBillboard].nIdxShadow, D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x, 0.0f, g_aBillboard[nCntBillboard].pos.z));
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	// �J�����O���Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);    // �L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);              // �����x��0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER); // ���傫�����̂�`�悷��

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// �r���{�[�h�̑������J��Ԃ�
		if (g_aBillboard[nCntBillboard].bUse == true)
		{// �r���{�[�h���g�p����Ă���
		    // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBillboard[nCntBillboard].rot.y, g_aBillboard[nCntBillboard].rot.x, g_aBillboard[nCntBillboard].rot.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillboard);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, NUM_POLYGON);
		}
	}

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �J�����O�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		BILLBOARD_TEXTURE_NAME,
		&g_pTextureBillboard);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// �r���{�[�h�̑������J��Ԃ�
	    // ���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth, g_aBillboard[nCntBillboard].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth, g_aBillboard[nCntBillboard].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth, -g_aBillboard[nCntBillboard].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth, -g_aBillboard[nCntBillboard].fHeight, 0.0f);

		// �@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		pVtx[1].nor = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		pVtx[2].nor = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		pVtx[3].nor = D3DXVECTOR3(0.22f, -0.87f, 0.44f);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();
}
//=============================================================================
// �r���{�[�h�̐ݒ�
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float width, float height)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// �r���{�[�h�̑������J��Ԃ�
		if (g_aBillboard[nCntBillboard].bUse == false)
		{// �r���{�[�h���g�p����Ă��Ȃ�
			g_aBillboard[nCntBillboard].pos = pos;        // �ʒu��ݒ�
			g_aBillboard[nCntBillboard].move = move;      // �ړ��ʂ�ݒ�
			g_aBillboard[nCntBillboard].rot = rot;        // ������ݒ�
			g_aBillboard[nCntBillboard].fWidth = width;   // ����ݒ�
			g_aBillboard[nCntBillboard].fHeight = height; // ������ݒ�

			pVtx[0].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth, g_aBillboard[nCntBillboard].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth, g_aBillboard[nCntBillboard].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth, -g_aBillboard[nCntBillboard].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth, -g_aBillboard[nCntBillboard].fHeight, 0.0f);

			g_aBillboard[nCntBillboard].nIdxShadow = SetShadow(D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x, 0.0f, g_aBillboard[nCntBillboard].pos.z), g_aBillboard[nCntBillboard].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.21f), 5, 5); // �e�̔ԍ���ݒ�
			g_aBillboard[nCntBillboard].bUse = true;
			break;
		}
		pVtx += 4;  // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();
}
//=============================================================================
// �r���{�[�h�Ƃ̓����蔻��
//=============================================================================
bool CollisionBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 radius)
{
	bool Col = false;  // �����������ǂ���
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{// �r���{�[�h�̑������J��Ԃ�
		if (g_aBillboard[nCntBillboard].bUse == true)
		{// �r���{�[�h���g�p����Ă���
			if (pos.y + radius.y <= g_aBillboard[nCntBillboard].pos.y + g_aBillboard[nCntBillboard].fHeight
				&& pos.y + 30.0f >= g_aBillboard[nCntBillboard].pos.y - g_aBillboard[nCntBillboard].fHeight)
			{// Y���W�̒��ɂ���
				if (pos.x - radius.x <= g_aBillboard[nCntBillboard].pos.x + 5.0f
					&& pos.x + radius.x >= g_aBillboard[nCntBillboard].pos.x - 5.0f)
				{// X���W�̒��ɂ���
					if (pos.z - radius.z <= g_aBillboard[nCntBillboard].pos.z + 5.0f
						&& pos.z + radius.z >= g_aBillboard[nCntBillboard].pos.z - 5.0f)
					{// Z���W�̒��ɂ���
						Col = true;
					}
				}
			}
		
		}
	}

	return Col;
}
Billboard *GetBillboard(void)
{
	return &g_aBillboard[0];
}
//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "effect.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_TEXTURE_NAME   "data/TEXTURE/effect000.jpg"          // �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureEffect = NULL;  // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;  // ���_�o�b�t�@�ւ̃|�C���^
Effect                  g_aEffect[MAX_EFFECT];    // �G�t�F�N�g�̏��

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

    // ���_���̍쐬
	MakeVertexEffect(pDevice);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g�̑������J��Ԃ�
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ʒu��������
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // ������������
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f); // �F��������
		g_aEffect[nCntEffect].fRadius = 0.0f;                         // ���a��������
		g_aEffect[nCntEffect].bUse = false;                           // �g�p���Ă��Ȃ���Ԃɂ���
		g_aEffect[nCntEffect].nIdxShadow = 0;                         // �e�̔ԍ���������
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g�̑������J��Ԃ�
		if (g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p����Ă���
			g_aEffect[nCntEffect].nLife--;          // ���������
			g_aEffect[nCntEffect].fRadius -= 0.5f;  // ���a�����炷
  			g_aEffect[nCntEffect].col.r -= 0.01f;   // �Ԃ����炷
			g_aEffect[nCntEffect].col.g -= 0.01f;   // �΂����炷
			g_aEffect[nCntEffect].col.b -= 0.01f;   // �����炷
			g_aEffect[nCntEffect].col.a -= 0.07f;   // �����x�����炷

			// �傫�����X�V
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[���X�V
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			// �e�̈ʒu�X�V
			SetPositionShadow(g_aEffect[nCntEffect].nIdxShadow, D3DXVECTOR3(g_aEffect[nCntEffect].pos.x, 0.0f, g_aEffect[nCntEffect].pos.z));
			
			if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fRadius <= 0 || g_aEffect[nCntEffect].col.a <= 0)
			{// �������Ȃ��Ȃ���
				g_aEffect[nCntEffect].bUse = false;              // �g�p���Ă��Ȃ���Ԃ�
				DeleteShadow(g_aEffect[nCntEffect].nIdxShadow);  // �e������
			}
		}
		pVtx += 4;   // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxView, mtxTrans;               // �v�Z�p�}�g���b�N�X

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); // �[�x�o�b�t�@�̏������ݐݒ�𖳌���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);// ���ׂĕ`�悷��

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);     // �L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);               // �����x��0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // ���傫�����̂�`�悷��

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g�̑������J��Ԃ�
		if (g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p����Ă���
		    // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			// �������J�����̐��ʂɐݒ�
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, NUM_POLYGON);
		}
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z�e�X�g�𖳌��ɂ���(�f�t�H���g�̒l��)
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);      // �[�x�o�b�t�@�ւ̏������݂�L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL); // �ȉ��̂��̂�`�悷��
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		EFFECT_TEXTURE_NAME,
		&g_pTextureEffect);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect= 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g�̑������J��Ԃ�
	    // ���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

		// �@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[1].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[2].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[3].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

		// ���_�J���[
		pVtx[0].col = g_aEffect[nCntEffect].col;
		pVtx[1].col = g_aEffect[nCntEffect].col;
		pVtx[2].col = g_aEffect[nCntEffect].col;
		pVtx[3].col = g_aEffect[nCntEffect].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float radius, int life)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g�̑������J��Ԃ�
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�
			g_aEffect[nCntEffect].pos = pos;          // �ʒu��ݒ�
			g_aEffect[nCntEffect].rot = rot;          // ������ݒ�
			g_aEffect[nCntEffect].col = col;          // �F��ݒ�
			g_aEffect[nCntEffect].fRadius = radius;   // ���a��ݒ�
			g_aEffect[nCntEffect].nLife = life;       // ������ݒ�

			// �傫���ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			// �F�ݒ�
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].nIdxShadow = SetShadow(D3DXVECTOR3(g_aEffect[nCntEffect].pos.x, 0.0f, g_aEffect[nCntEffect].pos.z), g_aEffect[nCntEffect].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.05f), 5, 5); // �e�̔ԍ���ݒ�
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;  // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
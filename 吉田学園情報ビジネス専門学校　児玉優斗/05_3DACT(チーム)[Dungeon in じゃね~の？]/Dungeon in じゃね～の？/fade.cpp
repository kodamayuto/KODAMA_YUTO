//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "fade.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_POLYGON (2)
#define BG_WIDTH		(SCREEN_WIDTH)				//�w�i�̕�
#define BG_HEIGHT		(SCREEN_HEIGHT)				//�w�i�̍���
#define BG_POS_X		(0)							//�w�i����X���W
#define BG_POS_Y		(0)							//�w�i����Y���W
#define PATTERN_ANIM (11)	//�e�N�X�`���p�^�[����

#define ANIMATION_SPEED (4)	//�A�j���[�V�����X�s�[�h

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		CFade::m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9  CFade::m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
CFade::FADE CFade::m_fade = FADE_NONE;
D3DXCOLOR CFade::m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;
int CFade::m_nPatternAnim = 0;
int CFade::m_nCounterAnim = 0;
int CFade ::m_nTex_Y = 1;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_nPatternAnim = 10;	//�A�j���[�V�����p�^�[��
	m_nCounterAnim = 0;//�A�j���[�V�����J�E���^�[
	m_nTex_Y = 1;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(CManager::MODE modeNext)
{
	m_nPatternAnim = 10;	//�A�j���[�V�����p�^�[��
	m_nCounterAnim = 0;//�A�j���[�V�����J�E���^�[
	m_nTex_Y = 1;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// �l�̏�����
	m_fade = FADE_IN;
	m_modeNext = modeNext;
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//������ʂɂ��Ă���

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/fade_tex.png", &m_pTexture);


	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^
					// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�̏���ݒ�
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);


	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	SetTexture(0.8f, 1.0f, 0.5f, 1.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			SetTexture(0.8f, 1.0f, 0.5f, 1.0f);


			m_nCounterAnim++;

			if (m_nCounterAnim % ANIMATION_SPEED == 0)
			{
				m_nPatternAnim = (m_nPatternAnim - 1) % PATTERN_ANIM;//�p�^�[��No.�X�V
				if (m_nPatternAnim == 4)
				{
					m_nTex_Y--;
				}
				if (m_nPatternAnim == 0)
				{
					m_fade = FADE_NONE;//�������Ă��Ȃ����
					m_nPatternAnim = 0;
				}
			}

		}
		else if (m_fade == FADE_OUT)
		{
			SetTexture(0.0f, 0.2f, 0.0f, 0.5f);

			m_nCounterAnim++;
			if (m_nCounterAnim % ANIMATION_SPEED == 0)
			{
				m_nPatternAnim = (m_nPatternAnim + 1) % PATTERN_ANIM;//�p�^�[��No.�X�V
				if (m_nPatternAnim == 5)
				{
					m_nTex_Y++;
				}
				if (m_nPatternAnim == 10)
				{
					m_fade = FADE_IN;//�������Ă��Ȃ����
					m_nPatternAnim = 9;
					CManager::SetMode(m_modeNext);
				}
			}
		}


		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[
		pVtx[0].col = m_color;
		pVtx[1].col = m_color;
		pVtx[2].col = m_color;
		pVtx[3].col = m_color;

		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0 + (0.2f * m_nPatternAnim), (0.5f * m_nTex_Y));
		pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * m_nPatternAnim), (0.5f * m_nTex_Y));
		pVtx[2].tex = D3DXVECTOR2(0 + (0.2f * m_nPatternAnim), 0.5f * (m_nTex_Y + 1));
		pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * m_nPatternAnim), 0.5f * (m_nTex_Y + 1));

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}


}

//=============================================================================
// �^�C�g�����
//=============================================================================
void CFade::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}



//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_color = m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//������ʂɂ��Ă���(����)


}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

void CFade::SetTexture(float fTex_X_0, float fTex_X_1, float fTex_Y_0, float fTex_Y_1)
{

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(fTex_X_0, fTex_Y_0);
	pVtx[1].tex = D3DXVECTOR2(fTex_X_1, fTex_Y_0);
	pVtx[2].tex = D3DXVECTOR2(fTex_X_0, fTex_Y_1);
	pVtx[3].tex = D3DXVECTOR2(fTex_X_1, fTex_Y_1);


	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

void CFade::AddTex()
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^


	if (m_fade != FADE_NONE)
	{
		m_nPatternAnim++;
		if (m_nCounterAnim % ANIMATION_SPEED == 0)
		{
			m_nPatternAnim = (m_nPatternAnim + 1) % PATTERN_ANIM;//�p�^�[��No.�X�V
			if (m_nPatternAnim == 5)
			{
				m_nTex_Y++;
			}
			if (m_nPatternAnim == 10)
			{
				m_fade = FADE_IN;//�������Ă��Ȃ����
				m_nPatternAnim = 9;
				CManager::SetMode(CManager::MODE_RESULT);
			}


		}



	}


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0 + (0.2f * m_nPatternAnim), (0.5f * m_nTex_Y));
	pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * m_nPatternAnim), (0.5f * m_nTex_Y));
	pVtx[2].tex = D3DXVECTOR2(0 + (0.2f * m_nPatternAnim), 0.5f * (m_nTex_Y + 1));
	pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * m_nPatternAnim), 0.5f * (m_nTex_Y + 1));

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();




}



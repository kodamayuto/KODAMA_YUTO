//=============================================================================
//
// UI�̏���[2D�|���S��] [ui.cpp]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================5
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "ui_result.h"
#include "timer.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COIN_WIDTH (200)			//�R�C���|���S���̕�
#define COIN_HEIGHT (90)			//�R�C���|���S����Y�̍���

#define KEY_WIDTH (200)				//�J�M�|���S���̕�
#define KEY_HEIGHT (90)				//�J�M�|���S����Y�̍���

#define SLASH_WIDTH (30)			//�X���b�V���|���S���̕�
#define SLASH_HEIGHT (70)			//�X���b�V���|���S����Y�̍���

#define MINUTES_WIDTH (60)			//���|���S���̕�
#define MINUTES_HEIGHT (90)			//���|���S����Y�̍���

#define DOT_WIDTH (30)				//�h�b�g�|���S���̕�
#define DOT_HEIGHT (30)				//�h�b�g�|���S����Y�̍���

#define EMOTE_WIDTH (100)			//�v�l�|���S���̕�
#define EMOTE_HEIGHT (100)			//�v�l�|���S����Y�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CUiResult::m_pTexture[MAX_TEXTURE_UI_RESULT] = {}; //���L�e�N�X�`���̃|�C���^
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CUiResult::CUiResult(int nPriority, OBJTYPE type) : CScene(nPriority, type)
{//�N���A�Ȓl����

}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CUiResult::~CUiResult()
{


}

//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CUiResult::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/result.png", &m_pTexture[0]);		// ���U���g
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/watch.png", &m_pTexture[1]);		// �J�M
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_COLON.png", &m_pTexture[2]);	// ��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_DOT.png", &m_pTexture[3]);		// �h�b�g


	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CUiResult::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE_UI_RESULT; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}


//=============================================================================
//�w�i�̐���
//=============================================================================
CUiResult *CUiResult::Create(void)
{
	//�w�i�̐���
	CUiResult *pUi;
	pUi = new CUiResult;

	if (pUi != NULL)
	{
		//�w�i�̏���������
		pUi->Init();
	}

	return pUi;
}


//=============================================================================
//����������
//=============================================================================
HRESULT CUiResult::Init(void)
{
	//�F���ݒ�
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCntColor = 0;

	for (int nCntScene2D = 0; nCntScene2D < MAX_UI_RESULT; nCntScene2D++)
	{
		switch (nCntScene2D)
		{
		case UI_TYPE_RESULT:// ���U���g
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(150.0f, 90.0f, 0.0f), COIN_WIDTH, COIN_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UI_TYPE_RESULT]);
			break;
		case UI_TYPE_WATCH:// ���v
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2 - 300.0f, SCREEN_HEIGHT/ 2 - 150.0f, 0.0f), KEY_WIDTH, KEY_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UI_TYPE_WATCH]);
			break;

		case UI_TYPE_MINUTES://��
							 //2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(700.0f, 210.0f, 0.0f), MINUTES_WIDTH, MINUTES_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UI_TYPE_MINUTES]);
			break;

		case UI_TYPE_DOT://�ǂ���
							 //2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(930.0f, 230.0f, 0.0f), DOT_WIDTH, DOT_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UI_TYPE_DOT]);
			break;
		}
		m_pScene2D[nCntScene2D]->SetObjType(CScene::OBJTYPE_UI);
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CUiResult::Uninit(void)
{
	for (int nCntScene2D = 0; nCntScene2D < MAX_UI_RESULT; nCntScene2D++)
	{
		if (m_pScene2D != NULL)
		{//�V�[��2D���󂶂�Ȃ��Ƃ�
		 //2D�V�[���̏I������
			m_pScene2D[nCntScene2D]->Uninit();
			//delete m_pScene2D[nCntScene2D];
			m_pScene2D[nCntScene2D] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CUiResult::Update(void)
{
	for (int nCntScene2D = 0; nCntScene2D < MAX_UI_RESULT; nCntScene2D++)
	{
		if (m_pScene2D[nCntScene2D] != NULL)
		{//�V�[��2D���󂶂�Ȃ��Ƃ�
			D3DXVECTOR3 posBg = m_pScene2D[nCntScene2D]->GetPosPolygon();	//�v���C���[�̈ʒu���

																			//�ʒu���̐ݒ�
			m_pScene2D[nCntScene2D]->SetPosPolygon(posBg);
		}
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CUiResult::Draw(void)
{

}


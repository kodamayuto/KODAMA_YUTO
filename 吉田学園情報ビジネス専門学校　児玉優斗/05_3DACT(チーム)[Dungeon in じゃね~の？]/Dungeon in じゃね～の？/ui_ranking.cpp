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
#include "ui_ranking.h"
#include "timer.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_WIDTH (200)			//�����L���O�|���S���̕�
#define RANKING_HEIGHT (90)			//�����L���O�|���S����Y�̍���

#define RANK_WIDTH (180)			//�����N�|���S���̕�
#define RANK_HEIGHT (620)			//�����N�|���S����Y�̍���

#define MINUTES_WIDTH (40)			//���|���S���̕�
#define MINUTES_HEIGHT (90)			//���|���S����Y�̍���

#define DOT_WIDTH (20)				//�h�b�g�|���S���̕�
#define DOT_HEIGHT (20)				//�h�b�g�|���S����Y�̍���

#define MINUTES_POS_X (640.0f)		//���̈ʒu(X)
#define DOT_POS_X (830.0f)		//���̈ʒu(X)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CUiRanking::m_pTexture[MAX_TEXTURE_UI_RANKING] = {}; //���L�e�N�X�`���̃|�C���^
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CUiRanking::CUiRanking(int nPriority, OBJTYPE type) : CScene(nPriority, type)
{//�N���A�Ȓl����

}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CUiRanking::~CUiRanking()
{


}

//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CUiRanking::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ranking.png", &m_pTexture[0]);		// ���U���g
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_RANKING.png", &m_pTexture[1]);		// �J�M
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_COLON.png", &m_pTexture[2]);	// ��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_DOT.png", &m_pTexture[3]);		// �h�b�g


	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CUiRanking::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE_UI_RANKING; nCntTex++)
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
CUiRanking *CUiRanking::Create(void)
{
	//�w�i�̐���
	CUiRanking *pUi;
	pUi = new CUiRanking;

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
HRESULT CUiRanking::Init(void)
{
	//�F���ݒ�
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCntColor = 0;

	for (int nCntScene2D = 0; nCntScene2D < MAX_UI_RANKING; nCntScene2D++)
	{
		switch (nCntScene2D)
		{
		case UI_TYPE_RANKING:// �����L���O
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(150.0f, 90.0f, 0.0f), RANKING_WIDTH, RANKING_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_RANKING]);
			break;
		case UI_TYPE_RANK:// ���v
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 250.0f, SCREEN_HEIGHT / 2 -30.0f, 0.0f), RANK_WIDTH, RANK_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_RANK]);
			break;

		case UI_TYPE_FIRSTMINUTES://1st��
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(MINUTES_POS_X, 100.0f, 0.0f), MINUTES_WIDTH, MINUTES_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_MINUTES]);
			break;

		case UI_TYPE_FIRSTDOT://1st�h�b�g
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(DOT_POS_X, 130.0f, 0.0f), DOT_WIDTH, DOT_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_DOT]);
			break;

		case UI_TYPE_SECONDMINUTES://2nd��
			 //2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(MINUTES_POS_X, 220.0f, 0.0f), MINUTES_WIDTH, MINUTES_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_MINUTES]);
			break;

		case UI_TYPE_SECONDDOT://2nd�h�b�g
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(DOT_POS_X, 250.0f, 0.0f), DOT_WIDTH, DOT_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_DOT]);
			break;

		case UI_TYPE_THIRDMINUTES://3rd��
			 //2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(MINUTES_POS_X, 340.0f, 0.0f), MINUTES_WIDTH, MINUTES_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_MINUTES]);
			break;

		case UI_TYPE_THIRDDOT://3rd�h�b�g
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(DOT_POS_X, 360.0f, 0.0f), DOT_WIDTH, DOT_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_DOT]);
			break;
		case UI_TYPE_FORTHMINUTES://4th��
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(MINUTES_POS_X, 450.0f, 0.0f), MINUTES_WIDTH, MINUTES_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_MINUTES]);
			break;

		case UI_TYPE_FORTHDOT://4th�h�b�g
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(DOT_POS_X, 480.0f, 0.0f), DOT_WIDTH, DOT_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_DOT]);
			break;
		case UI_TYPE_FIFTHMINUTES://5th��
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(MINUTES_POS_X, 570.0f, 0.0f), MINUTES_WIDTH, MINUTES_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_MINUTES]);
			break;

		case UI_TYPE_FIFTHDOT://4th�h�b�g
			//2D�|���S���̐���
			m_pScene2D[nCntScene2D] = CScene2D::Create(D3DXVECTOR3(DOT_POS_X, 600.0f, 0.0f), DOT_WIDTH, DOT_HEIGHT);
			//�e�N�X�`���̊��蓖��
			m_pScene2D[nCntScene2D]->BindTexture(m_pTexture[UITEX_DOT]);
			break;

		}
		m_pScene2D[nCntScene2D]->SetObjType(CScene::OBJTYPE_UI);
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CUiRanking::Uninit(void)
{
	for (int nCntScene2D = 0; nCntScene2D < MAX_UI_RANKING; nCntScene2D++)
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
void CUiRanking::Update(void)
{
	for (int nCntScene2D = 0; nCntScene2D < MAX_UI_RANKING; nCntScene2D++)
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
void CUiRanking::Draw(void)
{

}


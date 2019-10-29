//=============================================================================
//
// �|�[�Y��ʃN���X���� [pause.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "pause.h"
#include "Manager.h"
#include "fade.h"

//=============================================================================
//	�R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CPause::CPause()
{
	m_pVtxBuff = NULL;
	for (int nCntTex = 0; nCntTex < PAUSE_POLYGON_NUM; nCntTex++)
	{
		m_apTexture[nCntTex] = NULL;
	}
}

CPause::~CPause()
{

}

//=============================================================================
//	����������
//=============================================================================
HRESULT CPause::Init(void)
{
	//�ϐ��錾
	VERTEX_2D* pVtx;

	//�f�o�C�X�擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//�e�N�X�`���K�p
	m_apTexture[0] = CTexture::GetTexture("PAUSE_BG");
	m_apTexture[1] = CTexture::GetTexture("PAUSE_TUTORIAL");
	m_apTexture[2] = CTexture::GetTexture("PAUSE_MENU_CONTINUE");
	m_apTexture[3] = CTexture::GetTexture("PAUSE_MENU_QUIT");

	//������
	m_nSelectMenu = 0;
	m_SelectColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_POLYGON_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	/*�o�b�N�X�N���[��*/
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[	��
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	/*�������*/
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 350.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 350.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;


	/*�|�[�YUI*/
	for (int nCntPausePolygon = 0; nCntPausePolygon < 2; nCntPausePolygon++)
	{

		pVtx[0].pos = D3DXVECTOR3(350.0f, 140.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(780.0f, 140.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(350.0f, 190.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(780.0f, 190.0f + (250 * nCntPausePolygon), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void CPause::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	for (int nCntTex = 0; nCntTex < PAUSE_POLYGON_NUM; nCntTex++)
	{
		m_apTexture[nCntTex] = NULL;
	}
}

//=============================================================================
//	�X�V����
//=============================================================================
void CPause::Update(void)
{
	CFade* pFade = CManager::GetFade();
	//���[�h�I��(keyboard)
	if (CCommand::GetCommand("PAUSE_MENU_UP"))//��
	{
		m_nSelectMenu = (m_nSelectMenu + 1) % SELECT_NUM;//0��1��0
	}
	else if (CCommand::GetCommand("PAUSE_MENU_DOWN"))//��
	{
		m_nSelectMenu = (m_nSelectMenu + (SELECT_NUM - 1)) % SELECT_NUM;//0��1��0
	}

	if (CCommand::GetCommand("ENTER"))
	{//�������Ƃ���g_nSerectPauseMenu�̈ʒu�ɉ����ċ��������߂�
		switch (m_nSelectMenu)
		{
		case 0://�ĊJ
			CManager::ChangePauseFlag();
			break;
		case 1://�I��
			if (*pFade->GetFade() != CFade::FADE_OUT)
			{
				pFade->SetFade(CManager::MODE_TITLE, CFade::COLOR_WHITE);
				CManager::ChangePauseFlag();
				m_nSelectMenu = 0;
				//BGM��������SE��炷
			}
			break;
		}


	}


	//�F�ύX
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^

	for (int nCntPausePolygon = 2; nCntPausePolygon < PAUSE_POLYGON_NUM; nCntPausePolygon++)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntPausePolygon;

		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * (m_nSelectMenu + 2);

	pVtx[0].col = m_SelectColor;
	pVtx[1].col = m_SelectColor;
	pVtx[2].col = m_SelectColor;
	pVtx[3].col = m_SelectColor;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�`�揈��
//=============================================================================
void CPause::Draw(void)
{
	//�f�o�C�X�擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�`��
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

		//�|���S���̕`��
	for (int nCntPausePolygon = 0; nCntPausePolygon < PAUSE_POLYGON_NUM; nCntPausePolygon++)
	{
		// �e�N�X�`���̐ݒ�
		if (m_apTexture[nCntPausePolygon] != NULL)
		{
			pDevice->SetTexture(0, m_apTexture[nCntPausePolygon]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��		    //�v���~�e�B�u == �|���S��
			4 * nCntPausePolygon,				   //�J�n���钸�_�̃C���f�b�N�X(��{�O)
			2);		   							   //�v���~�e�B�u�̐�

	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
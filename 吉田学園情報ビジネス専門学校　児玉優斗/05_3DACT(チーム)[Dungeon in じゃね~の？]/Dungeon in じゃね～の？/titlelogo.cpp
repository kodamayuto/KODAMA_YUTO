//=============================================================================
//
// �^�C�g�����S����[2D�|���S��] [titlelogo.cpp]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "titlelogo.h"
#include "fade.h"
#include "sound.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOGO_WIDTH (650.0f)	//�^�C�g�����S�̕�
#define LOGO_HEIGHT (250.0f) //�^�C�g�����S��Y�̍���
#define PRESS_WIDTH (350.0f) //PressEnter�̕�
#define PRESS_HEIGHT (120.0f) //PressEnter�̍���

#define PATTERN_ANIM (5)	//�e�N�X�`���p�^�[����

#define ANIMATION_SPEED (4)	//�A�j���[�V�����X�s�[�h
#define TEX_X (0.25f)	//�e�N�X�`�����W_X
#define TEX_Y (0.25f)//�e�N�X�`�����W_Y

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitleLogo::m_apTexture[MAX_TITLE_TEXTURE] = {}; //���L�e�N�X�`���̃|�C���^
CScene2D *CTitleLogo::m_apScene2D[MAX_TITLE_NUM] = {};//�V�[��2D�̃|�C���^
D3DXCOLOR CTitleLogo::m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�F���
int CTitleLogo::m_nJumpRankingFrame = 0;//�����L���O��ʂ֑J�ڂ���Ƃ��̃t���[���J�E���^

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTitleLogo::CTitleLogo() : CScene(5)
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTitleLogo::~CTitleLogo()
{

}

//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CTitleLogo::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_TITLE.png", &m_apTexture[0]);//�^�C�g�����S[�p�^�[��1]
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter2.png", &m_apTexture[1]);//�^�C�g�����S[�p�^�[��2]

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CTitleLogo::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TITLE_TEXTURE; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}



//=============================================================================
//�^�C�g�����S�̐���
//=============================================================================
CTitleLogo *CTitleLogo::Create(void)
{
	//�^�C�g�����S�̃C���X�^���X����
	CTitleLogo *pTitle;
	pTitle = new CTitleLogo;
	if (pTitle != NULL)
	{
		//�^�C�g�����S�̏���������
		pTitle->Init();
	}

	return pTitle;
}


//=============================================================================
//����������
//=============================================================================
HRESULT CTitleLogo::Init(void)
{
	//�t���[���̏�����
	m_nJumpRankingFrame = 0;
	m_nCntFrame = 0;
	//�F���̏�����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE_NUM; nCntTitle++)
	{
		switch (nCntTitle)
		{
		case TITLETYPE_LOGO:
			//2D�|���S���̐���
			m_apScene2D[nCntTitle] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 170.0f, 0.0f), LOGO_WIDTH, LOGO_HEIGHT);
			//�^�C�g���̎�ނ̐ݒ�
			m_type = TITLETYPE_LOGO;
			m_state = TITLESTATE_NONE;
			//�e�N�X�`���̊��蓖��
			m_apScene2D[nCntTitle]->BindTexture(m_apTexture[0]);
			break;
		case TITLETYPE_PRESS:
			//2D�|���S���̐���
			m_apScene2D[nCntTitle] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 250.0f, 0.0f), PRESS_WIDTH, PRESS_HEIGHT);
			m_type = TITLETYPE_PRESS;
			m_state = TITLESTATE_NORMAL;
			//�e�N�X�`���̊��蓖��
			m_apScene2D[nCntTitle]->BindTexture(m_apTexture[1]);
			break;
		}

			//�^�C�g�����S�̃I�u�W�F�N�g�̐ݒ�
			SetObjType(CScene::OBJTYPE_TITLELOGO);
	}
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CTitleLogo::Uninit(void)
{
	for (int nCntTitle = 0; nCntTitle < MAX_TITLE_NUM; nCntTitle++)
	{
		if (m_apScene2D[nCntTitle] != NULL)
		{
			//2D�V�[���̏I������
			m_apScene2D[nCntTitle]->Uninit();
			m_apScene2D[nCntTitle] = NULL;

		}

	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CTitleLogo::Update(void)
{
	CInputX::InputJoyState JoyState = CInputX::GetJoystate();
	bool bConnect = CInputX::GetbConnect();			//�W���C�p�b�h�̐ڑ����

	//���
	XINPUT_STATE state;
	XInputGetState(0, &state);



	//�����L���O�փW�����v����t���[���̃J�E���g
	m_nJumpRankingFrame++;

	//�t�F�[�h�̎擾
	CFade::FADE pFade;
	pFade = CFade::GetFade();

	//�f�o�C�X�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	D3DXVECTOR3 posTitle[MAX_TITLE_NUM];//�e��ʒu���


	if (pFade == CFade::FADE_NONE)
	{
		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && bConnect == true))
		{//RETURN�L�[�������ꂽ�Ƃ�
			if (JoyState == CInputX::INPUT_JOYSTATE_NOTPUSH)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
				m_state = TITLESTATE_USE;//�g�p��Ԃ�
				CFade::SetFade(CManager::MODE_TUTORIAL);//���j���[�ֈڍs
			}
			JoyState = CInputX::INPUT_JOYSTATE_PUSH;
		}
		if (m_nJumpRankingFrame % 600 == 0)
		{
			CManager::SetTimer(9, 9, 9, 9, 9, 9);
			CFade::SetFade(CManager::MODE_RANKING);//�����L���O�ւֈڍs

		}
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE_NUM; nCntTitle++)
	{
		posTitle[nCntTitle] = m_apScene2D[nCntTitle]->GetPosPolygon();	//�ʒu���̎擾

		switch (m_type)
		{
		case TITLETYPE_LOGO:
			break;
		case TITLETYPE_PRESS:
			if (m_state == TITLESTATE_NORMAL)
			{//�ʏ��Ԃ̂Ƃ�
				m_nCntFrame++;
				m_nCntFrame = m_nCntFrame % 280;
				if (m_nCntFrame < 140)
				{
					m_col.a -= 0.01f;
				}
				if (m_nCntFrame > 140)
				{
					m_col.a += 0.01f;
				}
				//�F���̔��f
				m_apScene2D[1]->SetColor(m_col);
			}
			else if (m_state == TITLESTATE_USE)
			{//�{�^���������ꂽ�Ƃ�
				m_nCntFrame++;
				m_nCntFrame = m_nCntFrame % 6;
				if (m_nCntFrame < 3)
				{
					m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�F�𔒂�
				}
				if (m_nCntFrame > 3)
				{
					m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�F��Ԃ�
				}
				//�F���̔��f
				m_apScene2D[1]->SetColor(m_col);
			}
			break;
		}

		//�ʒu���̐ݒ�
		m_apScene2D[nCntTitle]->SetPosPolygon(posTitle[nCntTitle]);

	}

	if (JoyState == CInputX::INPUT_JOYSTATE_PUSH)
	{
		JoyState = CInputX::INPUT_JOYSTATE_NONE;
	}
	else if (JoyState == CInputX::INPUT_JOYSTATE_NONE)
	{
		JoyState = CInputX::INPUT_JOYSTATE_NOTPUSH;
	}

}

//=============================================================================
//�`�揈��
//=============================================================================
void CTitleLogo::Draw(void)
{


}


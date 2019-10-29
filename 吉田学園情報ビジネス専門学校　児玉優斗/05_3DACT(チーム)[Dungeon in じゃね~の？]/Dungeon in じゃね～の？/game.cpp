//=============================================================================
//
// �}�l�[�W������ [manager.cpp]
// Author :�ݓc��(Kishida Rei)
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "scene3D.h"
#include "scene_billboard.h"
#include "sceneX.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "ui.h"
#include "scene_meshcylinder.h"
#include "itemcounter.h"
#include "number.h"
#include "meshfield.h"
#include "object.h"
#include "timer.h"
#include "fade.h"
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CGame *CGame::m_pGame = NULL;					//�Q�[��
CPlayer *CGame::m_pPlayer = NULL;				//�v���C���[
CEnemy *CGame::m_pEnemy[15] = {};				//�G
CModel *CGame::m_pModel = {};					//���f��
CObject *CGame::m_pObject = NULL;				//�I�u�W�F�N�g
CMeshCylinder *CGame::m_pMeshCylinder = NULL;	//�V�����_�[
CUi *CGame::m_pUi = NULL;						//UI
CItemCounter *CGame::m_pItemCounter = NULL;		//�A�C�e���J�E���^
CNumber *CGame::m_pNumber = NULL;				//����
CTimer *CGame::m_pTimer = NULL;					//�^�C�}�[
CMeshField *CGame::m_pMeshField = NULL;			//���b�V���t�B�[���h
//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CGame::~CGame()
{

}




//=============================================================================
// �֐����F�Q�[���̏���������
// �֐��̊T�v�F�g�p����e�N�X�`���⃂�f���̓ǂݍ���
//=============================================================================
HRESULT CGame::Init(void)
{


	//===============================================
	//�e�N�X�`���E�p�[�c�̓ǂݍ���
	//===============================================
	//�v���C���[�̃p�[�c�ǂݍ���
	m_pModel->Load();

	//UI�̃e�N�X�`���ǂݍ���
	m_pUi->Load();

	//�����e�N�X�`���̓ǂݍ���
	m_pNumber->Load();

	//�z�u����I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();

	//�v���C���[�̃e�N�X�`���̓ǂݍ���
	m_pPlayer->Load();

	//�G�̃e�N�X�`���̓ǂݍ���
	CEnemy::Load();

	//===============================================
	// �Q�[�����Ŏg�p���鏈���̐���
	//===============================================
	//UI�̐���
	m_pUi = CUi::Create();

	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���b�V���V�����_�[�̐���
	m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�A�C�e���J�E���^�[�̐���
	m_pItemCounter = CItemCounter::Create();


	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(150.0f, 0.0f, -1250.0f));

	//�G�̐���
	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(600.0f, 0.0f, -800.0f), CEnemy::ENEMYTYPE_LOITERING_X);
	m_pEnemy[1] = CEnemy::Create(D3DXVECTOR3(350.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_CHASE);
	m_pEnemy[2] = CEnemy::Create(D3DXVECTOR3(450.0f, 0.0f,-300.0f), CEnemy::ENEMYTYPE_LOITERING_Z);
	m_pEnemy[3] = CEnemy::Create(D3DXVECTOR3(200.0f, 0.0f, -900.0f), CEnemy::ENEMYTYPE_LOITERING_Z);
	m_pEnemy[4] = CEnemy::Create(D3DXVECTOR3(400, 0.0f, -1200.0f), CEnemy::ENEMYTYPE_LOITERING_Z);
	m_pEnemy[5] = CEnemy::Create(D3DXVECTOR3(600, 0.0f, -1250.0f), CEnemy::ENEMYTYPE_CHASE);
	m_pEnemy[6] = CEnemy::Create(D3DXVECTOR3(600, 0.0f, -150.0f), CEnemy::ENEMYTYPE_CHASE);

	//�g�p����I�u�W�F�N�g���f���̓ǂݍ��݁E�I�u�W�F�N�g����
	m_pObject->LoadModelText();

	//�^�C�}�[����
	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 -130.0f, 80.0f, 0.0f), CTimer::TIMEMODE_GAME);

	return S_OK;

}
//=============================================================================
// �֐����F�^�C�g���̏I������
// �֐��̊T�v�F�g�p����e�N�X�`���⃂�f���̔j���A�V�[���̔j��
//=============================================================================
void CGame::Uninit()
{
	//�V�[���̔j��
	CScene::ReleaseSceneAll();

	//�v���C���[�̃p�[�c�j��
	m_pModel->Unload();

	//UI�̃e�N�X�`���j��
	m_pUi->Unload();

	//�����e�N�X�`���̔j��
	m_pNumber->Unload();

	//�z�u����I�u�W�F�N�g�̃e�N�X�`���̔j��
	m_pObject->Unload();

	//�v���C���[�̃e�N�X�`���̔j��
	m_pPlayer->Unload();

	//�G�̃e�N�X�`���̔j��
	CEnemy::Unload();


}
//=============================================================================
// �֐����F�Q�[���̍X�V����
// �֐��̊T�v�F--
//=============================================================================
void CGame::Update()
{
	//�t�F�[�h�̎擾
	CFade::FADE pFade;
	pFade = CFade::GetFade();


	//�f�o�C�X�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	//if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true)
	//{//R�L�[�������ꂽ�Ƃ�
	//	if (pFade == CFade::FADE_NONE)
	//	{
	//		CFade::SetFade(CManager::MODE_RESULT);//���U���g�ֈڍs
	//	}
	//}
}

//=============================================================================
// �֐����F�^�C�g���̕`�揈��
// �֐��̊T�v�F--
//=============================================================================
void CGame::Draw()
{

}



//=============================================================================
// �֐����F�V�[�����b�V���t�B�[���h�N���X�̎擾
// �֐��̊T�v�F�V�[�����b�V���t�B�[���h�N���X��Ԃ�
//=============================================================================
CMeshField *CGame::GetSceneMeshField(void)
{
	return m_pMeshField;
}

//=============================================================================
// �֐����F�v���C���[�N���X�̎擾
// �֐��̊T�v�F�v���C���[�N���X��Ԃ�
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// �֐����F�G�N���X�̎擾
// �֐��̊T�v�F�G�N���X��Ԃ�
//=============================================================================
CEnemy * CGame::GetEnemy(int nIndex)
{
	return m_pEnemy[nIndex];
}


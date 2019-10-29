//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "Time.h"

//==================================================================
// �}�N����`
//==================================================================
#define MOVE_SPEED		 (3.5f)		//�ړ����x
#define MOVE_COEFFICIENT (0.35f)	//�����W��
#define HIT_SIZE		 (22.5f)	//�e�̓����蔻��̃T�C�Y
#define INIT_TRANSTIME	 (120)		//�o�ꎞ�̓�������
#define DAMAGE_TRANSTIME (10)		//�_���[�W�󂯂��Ƃ��̓�������
#define BULLET_SHOTRATE  (8)		//�e���ˊԊu
#define BULLET_SPEED	 (14.0f)	//�e�X�s�[�h
//
//
//
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[TEX_NUM];				//���L�e�N�X�`���ւ̃|�C���^
int				   CPlayer::m_nStock = MAX_STOCK;				//�ő�c�@��
//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CPlayer::CPlayer() : CScene2D(PLAYER_PRIORITY)
{
	m_pShadow = NULL;
	m_pBarrier = NULL;

	m_fElementGauge[0] = 10.0f;
	m_fElementGauge[1] = 10.0f;
	m_fElementGauge[2] = 10.0f;
	m_UnionTimer = NULL;
}
CPlayer::~CPlayer()
{
	CScene2D::~CScene2D();
}
//==================================================================
// ��������
//==================================================================
CPlayer* CPlayer::Create(void)
{
	int nAll = m_nNumAll;

	CPlayer* pPlayer = NULL;
	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
		pPlayer->BindTexture(m_apTexture[0]);
	}

	return pPlayer;
}

//==================================================================
// ���L�e�N�X�`���̓ǂݍ���&���
//==================================================================
HRESULT CPlayer::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PC_triFalcon_Color.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PCunion_TriFalcon000.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Effect_p028.png", &m_apTexture[2]);


	return S_OK;
}
void CPlayer::Unload(void)
{
	for (int nCntTex = 0; nCntTex < TEX_NUM; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}

}

//==================================================================
// ����������
//==================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::Init();
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f);

	SetPosition(pos);
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	ELEMENT Element = ELEMENT_RED;
	SetElement(Element);
	m_fSize = 25.0f;
	m_fHitSize = HIT_SIZE;
	m_nHP = MAX_VITALITY;
	m_PlayerState = STATE_TRANSPARENT;
	m_nCntTransParent = INIT_TRANSTIME;
	CPlayerUI* pPlayerUI = NULL;

	if (CManager::GetMode() == CManager::MODE_GAME_CARAVAN)
	{
		pPlayerUI = CGame::GetPlayerUI();
		pPlayerUI->SetLife(m_nHP);
		pPlayerUI->SetStock(m_nStock);
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		pPlayerUI = CTutorial::GetPlayerUI();
		pPlayerUI->SetLife(m_nHP);
		pPlayerUI->SetStock(m_nStock);
	}

	SetObjType(CScene::OBJTYPE_PLAYER);

	switch (Element)
	{
	case ELEMENT_RED:
		SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.5f, 0.5f));
		break;
	case ELEMENT_BLUE:
		SetUV(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.5f, 1.0f));
		break;
	case ELEMENT_GREEN:
		SetUV(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
		break;
	}

	//�e�ݒ�
	m_pShadow = CScene2D::Create(2);
	m_pShadow->SetPosition(pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f),m_fSize);
	m_pShadow->SetColor(D3DXCOLOR(0.0f,0.0f,0.0f,0.75f));
	m_pShadow->BindTexture(m_apTexture[0]);
	m_pShadow->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.5f, 0.5f));

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CPlayer::Uninit(void)
{
	CGame::SetRespawnTimer();
	m_pShadow = NULL;
	CScene2D::Uninit();

}

//==================================================================
// �X�V����
//==================================================================
void CPlayer::Update(void)
{
	CInputKeyboard*		pInputKeyboard = CManager::GetInputKeyboard();
	CDInputController*	pController = CManager::GetController();
	CSound*				pSound = CManager::GetSound();

	if (CManager::GetMode() == CManager::MODE_TUTORIAL && m_element != ELEMENT_SUPER)
	{
		for (int nCntGauge = 0; nCntGauge < ELEMENT_SUPER; nCntGauge++)
		{
			m_fElementGauge[nCntGauge] = 100.0f;
		}
	}
	CPlayerUI* pPlayerUI = NULL;
	if (CManager::GetMode() == CManager::MODE_GAME_CARAVAN)
	{
		pPlayerUI = CGame::GetPlayerUI();
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		pPlayerUI = CTutorial::GetPlayerUI();
	}
	m_nCount++;

	D3DXVECTOR3 pos = GetPosition();
	//�ړ�
	pos = Move(pos);


	//�e
	if (pInputKeyboard->GetPress(DIK_SPACE) == true ||pController != NULL && pController->GetPress(CDInputController::DIJS_BUTTON_0) == true)
	{
		if (m_nCntBullet % BULLET_SHOTRATE == 0)
		{
			CBullet::Create(pos + D3DXVECTOR3(-10.0f, 0.0f, 0.0f),
				BULLET_SPEED,
				D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
				m_element,
				CBullet::TYPE_BULLET_NORMAL,
				CBullet::AUTHOR_PLAYER,
				false);
			CBullet::Create(pos + D3DXVECTOR3(10.0f, 0.0f, 0.0f),
				BULLET_SPEED,
				D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
				m_element,
				CBullet::TYPE_BULLET_NORMAL,
				CBullet::AUTHOR_PLAYER,
				false);

			if (m_element == ELEMENT_SUPER)
			{
				CBullet::Create(pos + D3DXVECTOR3(-10.0f, 0.0f, 0.0f),
					BULLET_SPEED,
					D3DXVECTOR3(0.0f, D3DX_PI * -0.95f, 0.0f),
					m_element,
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_PLAYER,
					false);
				CBullet::Create(pos + D3DXVECTOR3(10.0f, 0.0f, 0.0f),
					BULLET_SPEED,
					D3DXVECTOR3(0.0f, D3DX_PI * 0.95f, 0.0f),
					m_element,
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_PLAYER,
					false);

				CBullet::Create(pos + D3DXVECTOR3(-10.0f, 0.0f, 0.0f),
					BULLET_SPEED,
					D3DXVECTOR3(0.0f, D3DX_PI * 0.75f, 0.0f),
					m_element,
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_PLAYER,
					false);
				CBullet::Create(pos + D3DXVECTOR3(10.0f, 0.0f, 0.0f),
					BULLET_SPEED,
					D3DXVECTOR3(0.0f, D3DX_PI * -0.75f, 0.0f),
					m_element,
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_PLAYER,
					false);

				CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					BULLET_SPEED,
					D3DXVECTOR3(0.0f, D3DX_PI * 0.1f, 0.0f),
					m_element,
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_PLAYER,
					false);
				CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					BULLET_SPEED,
					D3DXVECTOR3(0.0f, D3DX_PI * -0.1f, 0.0f),
					m_element,
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_PLAYER,
					false);

			}
			pSound->Play(CSound::SOUND_LABEL_SE_000);
		}
		m_nCntBullet++;
	}
	else
	{
		m_nCntBullet = 0;
	}

	//�����؂�ւ�
	if (m_element != ELEMENT_SUPER)
	{
		if (pInputKeyboard->GetTrigger(DIK_Q) == true || pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_4) == true)
		{
			SetElement((CScene::ELEMENT)((m_element + (ELEMENT_SUPER - 1)) % ELEMENT_SUPER));
		}
		if (pInputKeyboard->GetTrigger(DIK_E) == true || pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_5) == true)
		{
			SetElement((CScene::ELEMENT)((m_element + 1) % ELEMENT_SUPER));
		}
	}


	CScene2D::Update();

	//�Q�[�W�̒���
	for (int nCntGauge = 0; nCntGauge < ELEMENT_SUPER; nCntGauge++)
	{
		if (m_fElementGauge[nCntGauge] > 100)
		{
			m_fElementGauge[nCntGauge] = 100;
		}

		if (pPlayerUI != NULL)
		{
			pPlayerUI->SetGauge((ELEMENT)nCntGauge, m_fElementGauge[nCntGauge]);
		}
	}

	//����
	if (pInputKeyboard->GetTrigger(DIK_H) == true || pController != NULL && pController->GetTrigger(CDInputController::DIJS_BUTTON_6) == true)
	{
		if (m_fElementGauge[ELEMENT_RED] == 100 &&
			m_fElementGauge[ELEMENT_GREEN] == 100 &&
			m_fElementGauge[ELEMENT_BLUE] == 100)
		{
			//������ݒ�
			m_UnionElement = m_element;
			m_element = ELEMENT_SUPER;

			//�e�̃e�N�X�`���ύX
			m_pShadow->BindTexture(m_apTexture[1]);
			m_pShadow->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

			//�^�C�}�[�ݒ�
			m_UnionTimer = CTime::Create(D3DXVECTOR3(170.0f,400.0f,0.0f),false);
			m_UnionTimer->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
			m_UnionTimer->SetTime(20);

			pSound->Play(CSound::SOUND_LABEL_SE_002);

			m_pBarrier = CScene2D::Create(3);
			m_pBarrier->SetPosition(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35.0f);
			m_pBarrier->BindTexture(m_apTexture[2]);
			m_pBarrier->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pBarrier->SetUV(D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2((1.0f / 8.0f) * (m_nCount % 8), 1.0f));
		}
	}
	switch (GetElement())
	{
	case ELEMENT_RED:
		BindTexture(m_apTexture[0]);
		SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.5f, 0.5f));

		break;
	case ELEMENT_BLUE:
		BindTexture(m_apTexture[0]);
		SetUV(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.5f, 1.0f));

		break;
	case ELEMENT_GREEN:
		BindTexture(m_apTexture[0]);
		SetUV(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));

		break;
	case ELEMENT_SUPER:
		BindTexture(m_apTexture[1]);
		SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
		break;
	}

	//�^�C�v����
	switch (m_PlayerState)
	{
	case STATE_NONE:
		break;
	case STATE_TRANSPARENT:
		m_nCntTransParent--;
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, (((m_nCntTransParent / 2) + 1) % 2) * 1.0f));

		if (m_nCntTransParent <= 0)
		{
			m_PlayerState = STATE_NORMAL;
			m_nCntTransParent = 0;
		}
		break;
	case STATE_NORMAL:
		HitCheck(pos);
		break;
	}

	//���̒��̏���
	if (m_element == ELEMENT_SUPER)
	{
		for (int nCntGauge = 0; nCntGauge < ELEMENT_SUPER; nCntGauge++)
		{
			if (m_fElementGauge[nCntGauge] > 0.0f)
			{
				m_fElementGauge[nCntGauge] -= 5.0f;
			}
			else
			{
				m_fElementGauge[nCntGauge] = 0.0f;
			}
		}

		m_pBarrier->SetUV(D3DXVECTOR2((1.0f / 8.0f) * ((m_nCount - 1) % 8), 0.0f), D3DXVECTOR2((1.0f / 8.0f) * (m_nCount % 8), 1.0f));

		if (m_UnionTimer->GetTime() <= 0)
		{//�������Ԃ�������߂�
			m_element = m_UnionElement;
			m_UnionTimer->Uninit();
			m_UnionTimer = NULL;
			m_PlayerState = STATE_TRANSPARENT;
			m_nCntTransParent = INIT_TRANSTIME;
			m_pShadow->BindTexture(m_apTexture[0]);
			m_pShadow->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.5f, 0.5f));


			//�o���A����
			if (m_pBarrier != NULL)
			{
				m_pBarrier->Uninit();
				m_pBarrier = NULL;
			}
		}
	}


}

//==================================================================
// �`�揈��
//==================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//==================================================================
// �ړ�����
//==================================================================
D3DXVECTOR3 CPlayer::Move(D3DXVECTOR3 pos)
{
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CDInputController* pController = CManager::GetController();

	D3DXVECTOR3 Pos = pos;
	float fMoveSpeed;

	//�ᑬ��
	if (pInput->GetPress(DIK_C) == true ||
		pController != NULL &&
		pController->GetPress(CDInputController::DIJS_BUTTON_1) == true)
	{
		fMoveSpeed = MOVE_SPEED - 2.0f;
	}
	else
	{
		fMoveSpeed = MOVE_SPEED;
	}


	//�ړ�
	if (pInput->GetPress(DIK_A) == true ||
		pController != NULL &&
		(pController->GetPress(CDInputController::DIJS_BUTTON_21) == true || pController->GetPress(CDInputController::DIJS_BUTTON_13) == true))
	{
		if (pInput->GetPress(DIK_W) == true ||
			pController != NULL &&
			(pController->GetPress(CDInputController::DIJS_BUTTON_18) == true || pController->GetPress(CDInputController::DIJS_BUTTON_10) == true))
		{
			m_Move.x += sinf(D3DX_PI * -0.75f) * fMoveSpeed;
			m_Move.y += cosf(D3DX_PI * -0.75f) * fMoveSpeed;
		}
		else if (pInput->GetPress(DIK_S) == true ||
			pController != NULL &&
			(pController->GetPress(CDInputController::DIJS_BUTTON_19) == true || pController->GetPress(CDInputController::DIJS_BUTTON_11) == true))
		{
			m_Move.x += sinf(D3DX_PI * -0.25f) * fMoveSpeed;
			m_Move.y += cosf(D3DX_PI * -0.25f) * fMoveSpeed;
		}
		else
		{
			m_Move.x += sinf(D3DX_PI * -0.5f) * fMoveSpeed;
			m_Move.y += cosf(D3DX_PI * -0.5f) * fMoveSpeed;
		}
	}
	else if (pInput->GetPress(DIK_D) == true ||
		pController != NULL &&
		(pController->GetPress(CDInputController::DIJS_BUTTON_20) == true || pController->GetPress(CDInputController::DIJS_BUTTON_12) == true))
	{
		if (pInput->GetPress(DIK_W) == true ||
			pController != NULL &&
			(pController->GetPress(CDInputController::DIJS_BUTTON_18) == true || pController->GetPress(CDInputController::DIJS_BUTTON_10) == true))
		{
			m_Move.x += sinf(D3DX_PI * 0.75f) * fMoveSpeed;
			m_Move.y += cosf(D3DX_PI * 0.75f) * fMoveSpeed;
		}
		else if (pInput->GetPress(DIK_S) == true ||
			pController != NULL &&
			(pController->GetPress(CDInputController::DIJS_BUTTON_19) == true || pController->GetPress(CDInputController::DIJS_BUTTON_11) == true))
		{
			m_Move.x += sinf(D3DX_PI * 0.25f) * fMoveSpeed;
			m_Move.y += cosf(D3DX_PI * 0.25f) * fMoveSpeed;
		}
		else
		{
			m_Move.x += sinf(D3DX_PI * 0.5f) * fMoveSpeed;
			m_Move.y += cosf(D3DX_PI * 0.5f) * fMoveSpeed;
		}
	}
	else if (pInput->GetPress(DIK_W) == true ||
		pController != NULL &&
		(pController->GetPress(CDInputController::DIJS_BUTTON_18) == true || pController->GetPress(CDInputController::DIJS_BUTTON_10) == true))
	{
		m_Move.x += sinf(D3DX_PI * 1.0f) * fMoveSpeed;
		m_Move.y += cosf(D3DX_PI * 1.0f) * fMoveSpeed;
	}
	else if (pInput->GetPress(DIK_S) == true ||
		pController != NULL &&
		(pController->GetPress(CDInputController::DIJS_BUTTON_19) == true || pController->GetPress(CDInputController::DIJS_BUTTON_11) == true))
	{
		m_Move.x += sinf(D3DX_PI * 0.0f) * fMoveSpeed;
		m_Move.y += cosf(D3DX_PI * 0.0f) * fMoveSpeed;
	}

	if (Pos.x - m_fSize <= MOVESTOP_RANGE && m_Move.x < 0.0f)
	{
		Pos.x = MOVESTOP_RANGE + m_fSize;
		m_Move.x = 0.0f;
	}
	if (Pos.x + m_fSize >= SCREEN_WIDTH - MOVESTOP_RANGE && m_Move.x > 0.0f)
	{
		Pos.x = SCREEN_WIDTH - MOVESTOP_RANGE - m_fSize;
		m_Move.x = 0.0f;
	}

	if (Pos.y - m_fSize <= 0 && m_Move.y < 0.0f)
	{
		Pos.y = m_fSize;
		m_Move.y = 0.0f;
	}
	if (Pos.y + m_fSize >= SCREEN_HEIGHT - 0 && m_Move.y > 0.0f)
	{
		Pos.y = SCREEN_HEIGHT - m_fSize;
		m_Move.y = 0.0f;

	}

	Pos += m_Move;

	m_Move.x += (0.0f - m_Move.x) * MOVE_COEFFICIENT;
	m_Move.y += (0.0f - m_Move.y) * MOVE_COEFFICIENT;

	SetPosition(Pos);
	//�e���W�E�o���A���W�X�V
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	}
	if (m_pBarrier != NULL)
	{
		m_pBarrier->SetPosition(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return Pos;
}

//==================================================================
// �����蔻�菈��
//==================================================================
void CPlayer::HitCheck(D3DXVECTOR3 pos)
{
	CScore*    pScore = CGame::GetScore();
	CSound*				pSound = CManager::GetSound();

	//�����蔻��
	int nNumAll = CScene::GetNumAll();
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCntIdx = 0; nCntIdx < MAX_SCENE; nCntIdx++)
		{
			CScene* pScene = CScene::GetScene(nCntPri, nCntIdx);		//�I�u�W�F�N�g�̎擾

			if (pScene != NULL)
			{//NULL�`�F�b�N
				CScene::OBJTYPE type = pScene->GetObjType();//�I�u�W�F�N�g�̃^�C�v�擾

				if (type == OBJTYPE_BULLET && ((CBullet*)(pScene))->GetAuthor() == CBullet::AUTHOR_ENEMY)
				{//�v���C���[�ƓG�̒e�̏ꍇ
					D3DXVECTOR3 BulletPos = ((CScene2D*)(pScene))->GetPosition();

					if (sqrtf(((BulletPos.x - pos.x) * (BulletPos.x - pos.x))) +
						((BulletPos.y - pos.y)*(BulletPos.y - pos.y)) < ((CScene2D*)(pScene))->GetSize() + m_fHitSize)
					{
						int nDamage = 1;
						CScene* pSceneClone = pScene;
						ELEMENT elem = ((CBullet*)(pSceneClone))->GetElement();
						if (m_element == ELEMENT_SUPER/* && m_nHP <= 1*/)
						{
							nDamage = 0;
							pScore->AddScore(20);
						}
						else if (m_element == elem)
						{//�����������Ȃ�
							nDamage = 0;
							m_fElementGauge[(int)m_element] += 4.0f;
							pScore->AddScore(10);
							pSound->Play(CSound::SOUND_LABEL_SE_001);
						}
						else
						{
							m_PlayerState = STATE_TRANSPARENT;
							m_nCntTransParent = DAMAGE_TRANSTIME;
						}

						//���S����
						if (Damage(nDamage) == true)
						{
							//���������@���@���@�폜�@���@�e�폜
							CExplosion::Create(pos,
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								100.0f,
								CExplosion::TYPE_NORMAL);

							//pScene->Uninit();
							CScene::ReleaseAll(CScene::OBJTYPE_BULLET);
							Uninit();

							return;
						}
						else
						{//HP��0�ȏ�Ȃ�e��������
							CExplosion::TYPE type = CExplosion::TYPE_NORMAL;
							if (nDamage == 0)
							{
								type = CExplosion::TYPE_ABSORB;
							}

							CExplosion::Create(BulletPos,
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								20.0f,
								type);

							pScene->Uninit();
						}
						break;
					}
				}
				else if (type == OBJTYPE_ENEMY)
				{
					D3DXVECTOR3 EnemyPos = ((CScene2D*)(pScene))->GetPosition();

					if (sqrtf(((EnemyPos.x - pos.x) * (EnemyPos.x - pos.x))) +
						((EnemyPos.y - pos.y)*(EnemyPos.y - pos.y)) < ((CScene2D*)(pScene))->GetSize() + m_fHitSize)
					{
						int nDamage = 1;
						if (m_element == ELEMENT_SUPER/* && m_nHP <= 1*/)
						{
							nDamage = 0;
						}


						//���S����
						if (Damage(nDamage) == true)
						{
							//���������@���@���@�폜
							CExplosion::Create(pos,
								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								100.0f,
								CExplosion::TYPE_NORMAL);

							Uninit();
							return;

						}

							break;
					}
				}
			}
		}
	}
}

//==================================================================
// �_���[�W����
//==================================================================
bool CPlayer::Damage(int nDamage)
{
	m_nHP -= nDamage;
	CPlayerUI* pPlayerUI = NULL;
	if (CManager::GetMode() == CManager::MODE_GAME_CARAVAN)
	{
		pPlayerUI = CGame::GetPlayerUI();
		pPlayerUI->SetLife(m_nHP);
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		pPlayerUI = CTutorial::GetPlayerUI();
		pPlayerUI->SetLife(m_nHP);
	}
	if (m_nHP <= 0)
	{
		m_nStock--;
		if (pPlayerUI != NULL)
		{
			pPlayerUI->SetStock(m_nStock);
		}

		if (m_pShadow != NULL)
		{
			m_pShadow->Uninit();
		}
		return true;
	}
	else
	{
		return false;
	}
}

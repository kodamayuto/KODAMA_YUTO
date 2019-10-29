//=============================================================================
//
// �G���� [enemy.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "enemy.h"
#include "game.h"
#include "bullet.h"
#include "explosion.h"
#include "Score.h"

//==================================================================
// �}�N����`
//==================================================================
#define MOVE_COEFFICIENT (0.35f)	//�����W��
#define CIRCLEBULLET_SHOTTIME (120)

//==================================================================
// �ÓI�����o�ϐ��錾
//==================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[CScene2D::ELEMENT_MAX][CEnemy::TYPE_MAX];				//���L�e�N�X�`���ւ̃|�C���^

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CEnemy::CEnemy() : CScene2D(3)
{
	m_pShadow = NULL;
}
CEnemy::~CEnemy()
{
	CScene2D::~CScene2D();
}

//==================================================================
// ���L�e�N�X�`���̓ǂݍ���&���
//==================================================================
HRESULT CEnemy::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon000.png", &m_apTexture[ELEMENT_RED][TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon001.png", &m_apTexture[ELEMENT_GREEN][TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon002.png", &m_apTexture[ELEMENT_BLUE][TYPE_NORMAL]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon003.png", &m_apTexture[ELEMENT_RED][TYPE_LIGHT]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon004.png", &m_apTexture[ELEMENT_GREEN][TYPE_LIGHT]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon005.png", &m_apTexture[ELEMENT_BLUE][TYPE_LIGHT]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon000.png", &m_apTexture[ELEMENT_RED][TYPE_NORMAL_SECOND]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon001.png", &m_apTexture[ELEMENT_GREEN][TYPE_NORMAL_SECOND]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon002.png", &m_apTexture[ELEMENT_BLUE][TYPE_NORMAL_SECOND]);

	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon003.png", &m_apTexture[ELEMENT_RED][TYPE_LIGHT_SECOND]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon004.png", &m_apTexture[ELEMENT_GREEN][TYPE_LIGHT_SECOND]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ENEMY/Enemy_triFalcon005.png", &m_apTexture[ELEMENT_BLUE][TYPE_LIGHT_SECOND]);

	return S_OK;
}

void CEnemy::Unload(void)
{
	for (int nCntTex2 = 0; nCntTex2 < CEnemy::TYPE_MAX; nCntTex2++)
		for (int nCntTex1 = 0; nCntTex1 < CScene2D::ELEMENT_MAX; nCntTex1++)
	{
		if (m_apTexture[nCntTex1][nCntTex2] != NULL)
		{
			m_apTexture[nCntTex1][nCntTex2]->Release();
			m_apTexture[nCntTex1][nCntTex2] = NULL;
		}
	}
}

//==================================================================
// ��������
//==================================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size, ELEMENT element, TYPE type)
{
	int nAll = m_nNumAll;

	CEnemy* pEnemy = NULL;
	pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		pEnemy->SetElement(element);
		pEnemy->Init(pos,move,size,type);
		pEnemy->BindTexture(m_apTexture[element][type]);
	}

	return pEnemy;
}

//==================================================================
// ����������
//==================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_ENEMY);
	CEGenerator::GetCntEnemy()++;//�G���J�E���g
	return S_OK;
}
void CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSize, TYPE type)
{
	Init();
	m_fSize = fSize;
	m_Type = type;

	switch (type)
	{
	case TYPE_NORMAL:
		m_nHP = 18;
		break;
	case TYPE_LIGHT:
		m_nHP = 14;
		break;
	case TYPE_NORMAL_SECOND:
		m_nHP = 22;
		break;
	}

	SetPosition(pos);

	m_State = STATE_MOVE;
	m_Move = move;

	//�e�ݒ�
	m_pShadow = CScene2D::Create(2);
	m_pShadow->SetPosition(pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), m_fSize);
	m_pShadow->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f));
	m_pShadow->BindTexture(m_apTexture[m_element][type]);
	m_pShadow->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

}
//==================================================================
// �I������
//==================================================================
void CEnemy::Uninit(void)
{
	m_pShadow = NULL;
	CEGenerator::GetCntEnemy()--;//�G���J�E���g
	CScene2D::Uninit();
}

//==================================================================
// �X�V����
//==================================================================
void CEnemy::Update(void)
{
	m_nCount++;

	//�ړ�
	D3DXVECTOR3 pos = GetPosition();

	pos += m_Move;
	SetPosition(pos);

	switch (m_Type)
	{
	case TYPE_NORMAL:
		if (m_nCount % 60 == 0)
		{
			m_pTargetPlayer = GetTargetPlayer();
			if (m_pTargetPlayer != NULL)
			{
				float fBulletAngle = atan2f(m_pTargetPlayer->GetPosition().x - pos.x,
					m_pTargetPlayer->GetPosition().y - pos.y);
				CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					4.5f,
					D3DXVECTOR3(0.0f, fBulletAngle + 0.05f, 0.0f),
					GetElement(),
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_ENEMY,
					true);

				CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					4.5f,
					D3DXVECTOR3(0.0f, fBulletAngle - 0.05f, 0.0f),
					GetElement(),
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_ENEMY,
					true);
			}
		}

		break;
	case TYPE_LIGHT:
		if (m_nCount % CIRCLEBULLET_SHOTTIME == 0)
		{
			//�ǔ��e
			m_pTargetPlayer = GetTargetPlayer();
			if (m_pTargetPlayer != NULL)
			{
				float fBulletAngle = atan2f(m_pTargetPlayer->GetPosition().x - pos.x,
					m_pTargetPlayer->GetPosition().y - pos.y);

				float fRandRot = fBulletAngle + ((rand() % 100) + 100) / 100;
				CBullet* pBullet;
				pBullet = CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					3.0f,
					D3DXVECTOR3(0.0f, fRandRot, 0.0f),
					GetElement(),
					CBullet::TYPE_BULLET_HOMING,
					CBullet::AUTHOR_ENEMY,
					true);
				pBullet->SetTarget(m_pTargetPlayer);
			}
		}
		break;
	case TYPE_NORMAL_SECOND:
		//�~�e��
		if (m_nCount % CIRCLEBULLET_SHOTTIME == 0)
		{
			int nBullet = 40;
			for (int nCnt = 0; nCnt < nBullet; nCnt++)
			{
				CBullet::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					1.5f,
					D3DXVECTOR3(0.0f, (D3DX_PI / (nBullet * 0.5f)) * nCnt, 0.0f),
					GetElement(),
					CBullet::TYPE_BULLET_NORMAL,
					CBullet::AUTHOR_ENEMY,
					false);
			}

		}
		break;
	}


	//�e���W�X�V
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	}


	switch (m_State)
	{
	case STATE_NORMAL:
		break;
	case STATE_DAMAGE:
		m_nDamageCounter++;

		if (m_nDamageCounter > 2)
		{
			m_State = STATE_NORMAL;
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//�����蔻��
	HitCheck(pos);

	if (pos.y > 1000.0f || pos.y < -200.0f ||
		pos.x > 1500.0f || pos.x < -200.0f)
	{
		Uninit();
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//==================================================================
// �_���[�W����
//==================================================================
bool CEnemy::Damage(int nDamage)
{
	m_nHP -= nDamage;

	if (m_nHP <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//==================================================================
// �^�[�Q�b�g�擾����
//==================================================================
CPlayer* CEnemy::GetTargetPlayer(void)
{
		for (int nCntIdx = 0; nCntIdx < MAX_SCENE; nCntIdx++)
		{
			CScene* pScene = CScene::GetScene(PLAYER_PRIORITY, nCntIdx);		//�I�u�W�F�N�g�̎擾

			if (pScene != NULL)
			{//NULL�`�F�b�N
				CScene::OBJTYPE type = pScene->GetObjType();//�I�u�W�F�N�g�̃^�C�v�擾
				if (type == OBJTYPE_PLAYER)
				{//�G�ƃv���C���[�̒e�̏ꍇ
					return (CPlayer*)pScene;
				}
			}
		}

	return NULL;
}

//==================================================================
// �����蔻�菈��
//==================================================================
void CEnemy::HitCheck(D3DXVECTOR3 pos)
{
	//�����蔻��
	int nNumAll = CScene::GetNumAll();
	CPlayer* pPlayer = NULL;

	for (int nCntIdx = 0; nCntIdx < MAX_SCENE; nCntIdx++)
	{
		CScene* pScene = CScene::GetScene(BULLET_PRIORITY, nCntIdx);		//�e�̎擾

		if (pScene != NULL)
		{//NULL�`�F�b�N
			CScene::OBJTYPE type = pScene->GetObjType();//�I�u�W�F�N�g�̃^�C�v�擾
			if (type == OBJTYPE_BULLET && ((CBullet*)(pScene))->GetAuthor() == CBullet::AUTHOR_PLAYER)
			{//�G�ƃv���C���[�̒e�̏ꍇ
				D3DXVECTOR3 BulletPos = ((CBullet*)(pScene))->GetPosition();
				float fBulletSize = ((CBullet*)(pScene))->GetSize();

				if (sqrtf(((pos.x - BulletPos.x) * (pos.x - BulletPos.x)) +
					((pos.y - BulletPos.y)*(pos.y - BulletPos.y))) < fBulletSize + m_fSize)
				{
					int nDamage = 2;
					/*===================================
					//�����ő����Ԃł̃_���[�W�v�Z���s��
					//=================================*/
					CBullet::ELEMENT elem = ((CBullet*)(pScene))->GetElement();

					if ((elem + 1) % ELEMENT_BLUE == m_element)
					{//��_�Ȃ�_���[�W�Q�{
						nDamage *= 2;
					}

					//���������@���@�G�폜�@���@�e�폜
					if (Damage(nDamage) == true)
					{//HP��0�ɂȂ��������
						CExplosion::Create(GetPosition(),
							D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							100.0f,
							CExplosion::TYPE_NORMAL);

						//�e�̑����̃Q�[�W�����Z
						pPlayer = this->GetTargetPlayer();
						if (pPlayer != NULL)
						{
							if (pPlayer->GetElement() != ELEMENT_SUPER)
							{
								pPlayer->SetGauge(GetElement(), 5.0f);
							}
						}

						CScore* pScore = CGame::GetScore();

						int nScore = 1000;
						if (pPlayer->GetElement() == ELEMENT_SUPER)
						{
							nScore *= 10;
						}
						pScore->AddScore(nScore);

						//�e����
						if (m_pShadow != NULL)
						{
							m_pShadow->Uninit();
						}

						Uninit();




						return;
					}
					else
					{//HP��0�ȏ�Ȃ�e��������
						CExplosion::Create(BulletPos,
							D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							20.0f,
							CExplosion::TYPE_NORMAL);
					}

					m_State = STATE_DAMAGE;
					SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					m_nDamageCounter = 0;

					pScene->Uninit();
				}
			}
		}
	}
}
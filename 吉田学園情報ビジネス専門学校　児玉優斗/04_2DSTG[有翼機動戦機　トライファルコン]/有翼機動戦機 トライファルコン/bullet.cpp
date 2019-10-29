//=============================================================================
//
// �v���C���[���� [bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "bullet.h"
#include "game.h"
#include "input.h"

//==================================================================
// �}�N����`
//==================================================================
#define MOVE_SPEED		(5.0f)		//�ړ����x
#define HOMING_ACCURACY (0.03f)		//�z�[�~���O���x
#define BOMBER_COUNT	(60)		//�j��܂ł̎���
#define DELETE_LENGTH (50.0f)
//==================================================================
// �ÓI�����o�ϐ��錾
//==================================================================
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[CBullet::TYPE_MAX];				//���L�e�N�X�`���ւ̃|�C���^

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CBullet::CBullet() : CScene2D(BULLET_PRIORITY)
{

}
CBullet::~CBullet()
{
	CScene2D::~CScene2D();
}

//==================================================================
// ���L�e�N�X�`���̓ǂݍ���&���
//==================================================================
HRESULT CBullet::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bullet_001.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Bullet_002.png", &m_apTexture[1]);


	return S_OK;
}
void CBullet::Unload(void)
{
	for (int nCntTex = 0; nCntTex < CBullet::TYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//==================================================================
// ��������
//==================================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, float fMove, D3DXVECTOR3 rot,
	CScene2D::ELEMENT element,CBullet::TYPE type,CBullet::AUTHORITY author, bool bEffectUse)
{
	CBullet* pBullet = NULL;
	pBullet = new CBullet;

	if (pBullet != NULL)
	{
		if (author == AUTHOR_ENEMY)
		{
			switch (element)
			{
			case CScene2D::ELEMENT_RED:
				pBullet->m_Col = D3DXCOLOR(1.0f, 0.2f, 0.1f, 1.0f);
				break;
			case CScene2D::ELEMENT_GREEN:
				pBullet->m_Col = D3DXCOLOR(0.1f, 1.0f, 0.2f, 1.0f);
				break;
			case CScene2D::ELEMENT_BLUE:
				pBullet->m_Col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
				break;
			case CScene2D::ELEMENT_SUPER:
				pBullet->m_Col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
				break;

			}
		}
		else if (author == AUTHOR_PLAYER)
		{
			switch (element)
			{
			case CScene2D::ELEMENT_RED:
				pBullet->m_Col = D3DXCOLOR(1.0f, 0.4f, 0.2f, 1.0f);
				break;
			case CScene2D::ELEMENT_GREEN:
				pBullet->m_Col = D3DXCOLOR(0.4f, 1.0f, 0.4f, 1.0f);
				break;
			case CScene2D::ELEMENT_BLUE:
				pBullet->m_Col = D3DXCOLOR(0.2f, 0.4f, 1.0f, 1.0f);
				break;
			case CScene2D::ELEMENT_SUPER:
				pBullet->m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}
		}

		pBullet->Init(pos, fMove,rot, pBullet->m_Col);				//�I�[�o�[���[�h����Init�ŏ�����
		pBullet->BindTexture(m_apTexture[type]);	//�e�N�X�`�����蓖��
		pBullet->m_Author = author;					//�e�̎�����ݒ�
		pBullet->m_type = type;
		pBullet->SetElement(element);				//�e�̑����ݒ�
		pBullet->m_bEffectFlag = bEffectUse;		//�G�t�F�N�g�ݒ�
	}

	return pBullet;
}

//==================================================================
// ����������
//==================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();
	m_fSize = 6.5f;
	SetObjType(CScene::OBJTYPE_BULLET);//�I�u�W�F�N�g�̎�ސݒ�

	return S_OK;
}
void CBullet::Init(D3DXVECTOR3 pos, float fMove, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	Init();
	m_Rot = rot;
	m_fMove = fMove;
	SetPosition(pos);
	SetColor(col);
}

//==================================================================
// �I������
//==================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// �X�V����
//==================================================================
void CBullet::Update(void)
{
	m_nCount++;

	D3DXVECTOR3 pos = GetPosition();	//���݂̈ʒu���擾
	//�ړ�
	pos += D3DXVECTOR3(sinf(m_Rot.y) * m_fMove, cosf(m_Rot.y) * m_fMove, 0.0f);
	//pos += m_move;
	SetPosition(pos);					//�ʒu�X�V

	CScene2D::Update();

	//�G�t�F�N�g
	if (m_bEffectFlag == true)
	{
		CEffect::Create(pos, (CEffect::AUTHORITY)m_Author, m_fSize * 1.1f, m_Col);
	}

	switch (m_type)
	{
	case TYPE_BULLET_HOMING:

		if (m_pTarget != NULL)
		{
			if (m_nCount < 300)
			{
				D3DXVECTOR3 TargetPos = m_pTarget->GetPosition();

				float fTargetAngle = atan2f(TargetPos.x - pos.x,
					TargetPos.y - pos.y);

				if ((fTargetAngle + D3DX_PI) - (m_Rot.y + D3DX_PI) > HOMING_ACCURACY)
				{
					if ((fTargetAngle + D3DX_PI) - (m_Rot.y + D3DX_PI) > D3DX_PI)
					{
						m_Rot.y -= HOMING_ACCURACY;
					}
					else
					{
						m_Rot.y += HOMING_ACCURACY;
					}
				}
				else if ((fTargetAngle + D3DX_PI) - (m_Rot.y + D3DX_PI) < -HOMING_ACCURACY)
				{
					if ((fTargetAngle + D3DX_PI) - (m_Rot.y + D3DX_PI) < -D3DX_PI)
					{
						m_Rot.y += HOMING_ACCURACY;
					}
					else
					{
						m_Rot.y -= HOMING_ACCURACY;
					}
				}

				if (m_Rot.y > D3DX_PI)
				{
					m_Rot.y -= D3DX_PI * 2.0f;
				}
				else if (m_Rot.y < -D3DX_PI)
				{
					m_Rot.y += D3DX_PI * 2.0f;

				}

			}
		}
		break;
	}



	if (pos.y <= -DELETE_LENGTH || pos.y >= (SCREEN_HEIGHT + DELETE_LENGTH) ||
		pos.x <= (MOVESTOP_RANGE - DELETE_LENGTH) || pos.x >= (SCREEN_WIDTH + DELETE_LENGTH) - MOVESTOP_RANGE)
	{//��ʘg(+�I�t�Z�b�g)����͂ݏo�����������
		Uninit();
	}
 	else if (m_nCount >= 1000)
	{//�����ԉ�ʏ�ɂ���Ə�����(�������s���΍��p)
		Uninit();
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}


//=============================================================================
//
// �v���C���[���� [effect.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "effect.h"
#include "Manager.h"
#include "input.h"

//==================================================================
// �}�N����`
//==================================================================
#define EFFECT_LIFE (30)

//==================================================================
// �ÓI�����o�ϐ��錾
//==================================================================
LPDIRECT3DTEXTURE9 CEffect::m_apTexture[2];				//���L�e�N�X�`���ւ̃|�C���^

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CEffect::CEffect() : CScene2D(2)
{

}
CEffect::~CEffect()
{
	CScene2D::~CScene2D();
}

//==================================================================
// ���L�e�N�X�`���̓ǂݍ���&���
//==================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_apTexture[0]);

	return S_OK;
}
void CEffect::Unload(void)
{
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
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
CEffect* CEffect::Create(D3DXVECTOR3 pos, AUTHORITY author, float fSize, D3DXCOLOR col)
{
	CEffect* pEffect = NULL;
	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		pEffect->Init(pos, col,fSize);				//�I�[�o�[���[�h����Init�ŏ�����
		pEffect->BindTexture(m_apTexture[0]);	//�e�N�X�`�����蓖��
		pEffect->m_Author = author;
	}

	return pEffect;
}

//==================================================================
// ����������
//==================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_EFFECT);//�I�u�W�F�N�g�̎�ސݒ�

	return S_OK;
}
void CEffect::Init(D3DXVECTOR3 pos,D3DXCOLOR col, float fSize)
{
	Init();
	m_fSize = fSize;
	SetPosition(pos);
	m_Col = col;
	SetColor(col);
}

//==================================================================
// �I������
//==================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//==================================================================
// �X�V����
//==================================================================
void CEffect::Update(void)
{
	m_nCount++;

	SetColor(D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b,(EFFECT_LIFE - m_nCount) * (1.0f / EFFECT_LIFE)));
	if (m_nCount == EFFECT_LIFE)
	{
		Uninit();
	}
}

//==================================================================
// �`�揈��
//==================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}


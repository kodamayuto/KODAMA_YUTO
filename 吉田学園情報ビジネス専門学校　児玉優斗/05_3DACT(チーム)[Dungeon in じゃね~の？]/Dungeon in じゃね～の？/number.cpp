//=============================================================================
//
// �V�[������[2D�|���S��] [scene2D.cpp]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ANIMATION_SPEED (8)	//�A�j���[�V�����̃X�s�[�h
#define TEX_X (0.25f)	//�e�N�X�`�����W_X
#define TEX_Y (1.0f)	//�e�N�X�`�����W_Y

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL; //���L�e�N�X�`���̃|�C���^


//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CNumber::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI_NUMBER.png", &m_pTexture);

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CNumber::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	m_rotNumber = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�p�x
	m_posNumber = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
	m_fNumberWidth = 0.0f;	//�|���S���̕�
	m_fNumberHeight = 0.0f;	//�|���S���̍���
	m_pVtxBuff = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
//2D�V�[���̐���
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float width, float height)
{
	CNumber  *pNumber;
	pNumber = new CNumber;//�V�[���N���X�̐���
	if (pNumber != NULL)
	{
		pNumber->m_posNumber = pos;
		pNumber->m_fNumberWidth = width;
		pNumber->m_fNumberHeight = height;
		pNumber->Init();
	}
	return pNumber;
}


//=============================================================================
//����������
//=============================================================================
HRESULT CNumber::Init(void)
{


	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	// ���_����ݒ�
	VERTEX_2D *pVtx; // ���_���̍쐬

	////�|���S���̒���
	m_fLengthNumber = sqrtf((m_fNumberWidth / 2 + m_fNumberWidth / 2) * (m_fNumberHeight / 2 + m_fNumberHeight / 2));

	//�|���S���̊p�x
	m_fAngleNumber = atan2f(m_fNumberWidth / 2, m_fNumberHeight / 2);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(m_posNumber.x - m_fNumberWidth, m_posNumber.y - m_fNumberHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posNumber.x + m_fNumberWidth, m_posNumber.y - m_fNumberHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posNumber.x - m_fNumberWidth, m_posNumber.y + m_fNumberHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posNumber.x + m_fNumberWidth, m_posNumber.y + m_fNumberHeight, 0.0f);


	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CNumber::Uninit(void)
{

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//=============================================================================
//�X�V����
//=============================================================================
void CNumber::Update(void)
{



}

//=============================================================================
//�`�揈��
//=============================================================================
void CNumber::Draw(void)
{

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	// �f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�(�g��Ȃ��Ă������I)
	pDevice->SetTexture(0, m_pTexture);


	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}


//=============================================================================
//�|���S���̈ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CNumber::GetPosNumber(void)
{
	return m_posNumber;
}

//=============================================================================
//�|���S���̈ʒu�̐ݒ�
//=============================================================================
void CNumber::SetPosNumber(D3DXVECTOR3 pos)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	//�ʒu������
	m_posNumber = pos;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_posNumber.x + sinf(-D3DX_PI + m_fAngleNumber + m_rotNumber.x) * m_fLengthNumber,
		m_posNumber.y + cosf(-D3DX_PI + m_fAngleNumber + m_rotNumber.y) * m_fLengthNumber,
		0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posNumber.x + sinf(D3DX_PI - m_fAngleNumber + m_rotNumber.x) * m_fLengthNumber,
		m_posNumber.y + cosf(D3DX_PI - m_fAngleNumber + m_rotNumber.y) * m_fLengthNumber,
		0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posNumber.x + sinf(-m_fAngleNumber + m_rotNumber.x) * m_fLengthNumber,
		m_posNumber.y + cosf(-m_fAngleNumber + m_rotNumber.y) * m_fLengthNumber,
		0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posNumber.x + sinf(m_fAngleNumber + m_rotNumber.x) * m_fLengthNumber,
		m_posNumber.y + cosf(m_fAngleNumber + m_rotNumber.y) * m_fLengthNumber,
		0.0f);


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�|���S���̊p�x�̎擾
//=============================================================================
D3DXVECTOR3 CNumber::GetRotNumber(void)
{
	return m_rotNumber;
}

//=============================================================================
//�|���S���̊p�x�̐ݒ�
//=============================================================================
void CNumber::SetRotNumber(D3DXVECTOR3 rot)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	m_rotNumber = rot;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_posNumber.x + sinf(-D3DX_PI + m_fAngleNumber + m_rotNumber.x) * m_fLengthNumber,
		m_posNumber.y + cosf(-D3DX_PI + m_fAngleNumber + m_rotNumber.y) * m_fLengthNumber,
		0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posNumber.x + sinf(D3DX_PI - m_fAngleNumber + m_rotNumber.x) * m_fLengthNumber,
		m_posNumber.y + cosf(D3DX_PI - m_fAngleNumber + m_rotNumber.y) * m_fLengthNumber,
		0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posNumber.x + sinf(-m_fAngleNumber + m_rotNumber.x) * m_fLengthNumber,
		m_posNumber.y + cosf(-m_fAngleNumber + m_rotNumber.y) * m_fLengthNumber,
		0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posNumber.x + sinf(m_fAngleNumber + m_rotNumber.x) * m_fLengthNumber,
		m_posNumber.y + cosf(m_fAngleNumber + m_rotNumber.y) * m_fLengthNumber,
		0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�|���S���̒����̎擾
//=============================================================================
float CNumber::GetLengthNumber(void)
{
	return m_fLengthNumber;
}

//=============================================================================
//�|���S���̒����̐ݒ�
//=============================================================================
void CNumber::SetLengthNumber(float fLength)
{
	m_fLengthNumber = fLength;
}

//=============================================================================
//�|���S���̒����̐ݒ�
//=============================================================================
void CNumber::SetNumberWidth(float fWidth)
{
	m_fNumberWidth = fWidth;
}
//=============================================================================
//�|���S���̒����̐ݒ�
//=============================================================================
void CNumber::SetNumberHeight(float fHeight)
{
	m_fNumberHeight = fHeight;

}
//=============================================================================
//�e�N�X�`���̊��蓖��
//=============================================================================
void CNumber::BindTexture(LPDIRECT3DTEXTURE9 tex)
{
	m_pTexture = tex;

}

//=============================================================================
//�e�N�X�`���̐ݒ�
//=============================================================================
void CNumber::SetTexture(float fTex_X, float fTex_Y)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	VERTEX_2D *pVtx; // ���_���̍쐬

					 // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTex_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, fTex_Y);
	pVtx[3].tex = D3DXVECTOR2(fTex_X, fTex_Y);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
//�e�N�X�`���̐ݒ�
//=============================================================================
void CNumber::SetTextureAnim(float fTex_X, float fTex_Y, int nPatternAnim)
{
	//�����_���[�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	VERTEX_2D *pVtx; // ���_���̍쐬


	 // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0 + (fTex_X*nPatternAnim), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTex_X + (fTex_X * nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0 + (fTex_X * nPatternAnim), fTex_Y);
	pVtx[3].tex = D3DXVECTOR2(fTex_X + (fTex_X * nPatternAnim), fTex_Y);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================================================================
//�F�̐ݒ�
//============================================================================================
void CNumber::SetColor(D3DXCOLOR col)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx; // ���_���̍쐬

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


}

//============================================================================================
//�����̐ݒ�
//============================================================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;

	// ���_����ݒ�
	VERTEX_2D *pVtx; // ���_���̍쐬


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * m_nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * m_nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * m_nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * m_nNumber), 1.0f);
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
//============================================================================================
//���̎擾
//============================================================================================
float CNumber::GetWidthNumber(void)
{
	return m_fNumberWidth;
}
//============================================================================================
//���̎擾
//============================================================================================
float CNumber::GetHeightNumber(void)
{
	return m_fNumberHeight;

}



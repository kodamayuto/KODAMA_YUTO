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
#include "debugproc.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_WIDTH (50.0f)
#define POLYGON_HEIGHT (50.0f)

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CManager *CScene2D::m_pManager = NULL;

//=============================================================================
// �֐����F2D�V�[���̐���
// �֐��̊T�v�F2D�V�[���𐶐�����
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScene2D  *pScene2D;
	pScene2D = new CScene2D;//�V�[���N���X�̐���
	if (pScene2D != NULL)
	{
		pScene2D->m_posPolygon = pos;//�ʒu���̑��
		pScene2D->m_fPolygonWidth = fWidth;
		pScene2D->m_fPolygonHeight = fHeight;
		pScene2D->Init();
	}
	return pScene2D;
}

//=============================================================================
// �֐����F�R���X�g���N�^
// �֐��̊T�v�F�������ꂽ�Ƃ��ɌĂяo�����B�l�̃N���A
//=============================================================================
CScene2D::CScene2D(int nPriority, OBJTYPE type) :  CScene(nPriority, type)
{
	m_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�p�x
	m_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
	m_fPolygonWidth = 0.0f;	//�|���S���̕�
	m_fPolygonHeight = 0.0f;	//�|���S���̍���
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_nNumScene2D++;
}

//=============================================================================
// �֐����F�f�X�g���N�^
// �֐��̊T�v�F�Ō�ɌĂяo�����
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// �֐����F2D�V�[���̏���������
// �֐��̊T�v�F�|���S���̐ݒ�
//=============================================================================
HRESULT CScene2D::Init(void)
{


	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D *pVtx; // ���_���̍쐬
	m_fLengthPolygon = sqrtf((m_fPolygonWidth / 2 + m_fPolygonWidth / 2) * (m_fPolygonHeight / 2 + m_fPolygonHeight / 2));

	m_fAnglePolygon = atan2f(m_fPolygonWidth / 2, m_fPolygonHeight / 2);

	// ���_���W�̐ݒ�
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-D3DX_PI + m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(-D3DX_PI + m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);

	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + sinf(D3DX_PI + m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(D3DX_PI + m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);

	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(-m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);

	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);


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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


	return S_OK;
}

//=============================================================================
// �֐����F2D�V�[���̏I������
// �֐��̊T�v�F�e�N�X�`���A���_�o�b�t�@�̔j���A���g�̔j��
//=============================================================================
void CScene2D::Uninit(void)
{

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g(�������g)�̔j��
	Release();

}

//=============================================================================
// �֐����F2D�V�[���̍X�V����
// �֐��̊T�v�F--
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �֐����F2D�V�[���̕`�揈��
// �֐��̊T�v�F--
//=============================================================================
void CScene2D::Draw(void)
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
// �֐����F�G�t�F�N�g�`�揈��
// �֐��̊T�v�F--
//=============================================================================
void CScene2D::DrawEffect(void)
{

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice;
	// �f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�(�g��Ȃ��Ă������I)
	pDevice->SetTexture(0, m_pTexture);


	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// �֐����F2D�V�[���̑������擾
// �֐��̊T�v�F2D�V�[���̑�����Ԃ�
//=============================================================================
int CScene2D::GetNum2DSceneAll(void)
{
	return m_nNumScene2D;
}

//=============================================================================
// �֐����F�|���S���̈ʒu���擾
// �֐��̊T�v�F�|���S���̈ʒu��Ԃ�
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosPolygon(void)
{
	return m_posPolygon;
}

//=============================================================================
// �֐����F�|���S���̈ʒu��ݒ�
// �֐��̊T�v�F�|���S���̈ʒu��ݒ肷��
//=============================================================================
void CScene2D::SetPosPolygon(D3DXVECTOR3 pos)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	//�ʒu������
	m_posPolygon = pos;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-D3DX_PI + m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(-D3DX_PI + m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + sinf(D3DX_PI - m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(D3DX_PI - m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(-m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + sinf(m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �֐����F�|���S���̊p�x���擾
// �֐��̊T�v�F�|���S���̊p�x��Ԃ�
//=============================================================================
D3DXVECTOR3 CScene2D::GetRotPolygon(void)
{
	return m_rotPolygon;
}

//=============================================================================
// �֐����F�|���S���̊p�x��ݒ�
// �֐��̊T�v�F�|���S���̊p�x��ݒ�
//=============================================================================
void CScene2D::SetRotPolygon(D3DXVECTOR3 rot)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	m_rotPolygon = rot;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-D3DX_PI + m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(-D3DX_PI + m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x + sinf(D3DX_PI - m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(D3DX_PI - m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + sinf(-m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(-m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + sinf(m_fAnglePolygon + m_rotPolygon.x) * m_fLengthPolygon,
		m_posPolygon.y + cosf(m_fAnglePolygon + m_rotPolygon.y) * m_fLengthPolygon,
		0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �֐����F�|���S���̒������擾
// �֐��̊T�v�F�|���S���̒�����Ԃ�
//=============================================================================
float CScene2D::GetLengthPolygon(void)
{
	return m_fLengthPolygon;
}

//=============================================================================
// �֐����F�|���S���̒�����ݒ�
// �֐��̊T�v�F�|���S���̒�����ݒ肷��
//=============================================================================
void CScene2D::SetLengthPolygon(float fLength)
{
	m_fLengthPolygon = fLength;
}

//=============================================================================
// �֐����F�|���S���̕���ݒ�
// �֐��̊T�v�F�|���S���̕���ݒ肷��
//=============================================================================
void CScene2D::SetPolygonWidth(float fWidth)
{
	m_fPolygonWidth = fWidth;
}
//=============================================================================
// �֐����F�|���S���̍�����ݒ�
// �֐��̊T�v�F�|���S���̍�����ݒ肷��
//=============================================================================
void CScene2D::SetPolygonHeight(float fHeight)
{
	m_fPolygonHeight = fHeight;

}
//=============================================================================
// �֐����F�e�N�X�`���̐ݒ�
// �֐��̊T�v�F�e�N�X�`�������蓖�Ă�
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 tex)
{
	m_pTexture = tex;

}

//=============================================================================
// �֐����F�e�N�X�`���̍��W�ݒ�
// �֐��̊T�v�F�e�N�X�`���̍��W��ݒ肷��
//=============================================================================
void CScene2D::SetTexture(float fTex_X, float fTex_Y)
{

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
// �֐����F�e�N�X�`���A�j���[�V����
// �֐��̊T�v�F�A�j���[�V�����𓮂���
//=============================================================================
void CScene2D::SetTextureAnim(float fTex_X, float fTex_Y, int nPatternAnim)
{
	//�f�o�C�X�̎擾
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


//=============================================================================
// �֐����F�e�N�X�`���A�j���[�V����(Y��)
// �֐��̊T�v�F�A�j���[�V�����𓮂���
//=============================================================================
void CScene2D::SetTextureAnimY(float fTex_X, float fTex_Y, int nPatternAnim, int nTex_Y)
{

	// ���_����ݒ�
	VERTEX_2D *pVtx; // ���_���̍쐬


					 // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0 + (fTex_X*nPatternAnim), (fTex_Y * nTex_Y));
	pVtx[1].tex = D3DXVECTOR2(fTex_X + (fTex_X * nPatternAnim), (fTex_Y * nTex_Y));
	pVtx[2].tex = D3DXVECTOR2(0 + (fTex_X * nPatternAnim), fTex_Y * (nTex_Y + 1));
	pVtx[3].tex = D3DXVECTOR2(fTex_X + (fTex_X * nPatternAnim), fTex_Y * (nTex_Y + 1));

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
// �֐����F�w�i�X�N���[��
// �֐��̊T�v�F�e�N�X�`������������
//=============================================================================
void CScene2D::ScrollBg(D3DXVECTOR2 Scroll_0, D3DXVECTOR2 Scroll_1, D3DXVECTOR2 Scroll_2, D3DXVECTOR2 Scroll_3)
{

	// ���_����ݒ�
	VERTEX_2D *pVtx; // ���_���̍쐬


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = Scroll_0;
	pVtx[1].tex = Scroll_1;
	pVtx[2].tex = Scroll_2;
	pVtx[3].tex = Scroll_3;


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �֐����F�|���S���̐F�ݒ�
// �֐��̊T�v�F�|���S���̐F��ݒ肷��
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
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

//=============================================================================
// �֐����F�D�揇�ʂ̐ݒ�
// �֐��̊T�v�F�`�揇��ݒ肷��
//=============================================================================
void CScene2D::SetPriority(int nPriority)
{
	m_nPriority = nPriority;
}
//=============================================================================
// �֐����F�|���S���̕����擾
// �֐��̊T�v�F�|���S���̕���Ԃ�
//=============================================================================
float CScene2D::GetWidthPolygon(void)
{
	return m_fPolygonWidth;
}
//=============================================================================
// �֐����F�|���S���̂������擾
// �֐��̊T�v�F�|���S���̕���Ԃ�
//=============================================================================
float CScene2D::GetHeightPolygon(void)
{
	return m_fPolygonHeight;

}





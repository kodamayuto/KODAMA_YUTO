//=============================================================================
//
// �V�[��2D����[2D �|���S��] [scene2D.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
//*****************************************************************************
// �V�[��2D�̃N���X�\����
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D::CScene2D(int nPriority = 6, OBJTYPE type = OBJTYPE_SCENE2D);	//�R���X�g���N�^
	CScene2D::~CScene2D();	//�f�X�g���N�^
	static CScene2D *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);//�G�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	void DrawEffect(void); //�`�揈��
	int GetNum2DSceneAll(void);	//2D�V�[�����̎擾
	void BindTexture(LPDIRECT3DTEXTURE9 tex);//�e�N�X�`���̊��蓖��
	void SetTexture(float fTex_X, float fTex_Y);//�e�N�X�`���̐ݒ�
	void SetColor(D3DXCOLOR col);	//�F�̐ݒ�
	void SetPriority(int nPriority);//�D�揇��

	//�w�i�X�N���[��
	void ScrollBg(D3DXVECTOR2 Scroll_0, D3DXVECTOR2 Scroll_1, D3DXVECTOR2 Scroll_2, D3DXVECTOR2 Scroll_3);

	//�e�N�X�`���A�j���[�V����
	void SetTextureAnim(float fTex_X, float fTex_Y, int nPatternAnim);
	void SetTextureAnimY(float fTex_X, float fTex_Y, int nPatternAnim, int nTex_Y);

	//�|���S���̑傫���̎擾�A�ݒ�
	void SetPolygonWidth(float fWidth);
	void SetPolygonHeight(float fWidth);

	//�|���S���̈ʒu���̎擾�A�ݒ�
	D3DXVECTOR3 GetPosPolygon(void);
	void SetPosPolygon(D3DXVECTOR3 pos);

	//�|���S���̊p�x���̐ݒ�A�ݒ�
	D3DXVECTOR3 GetRotPolygon(void);
	void SetRotPolygon(D3DXVECTOR3 rot);

	//�|���S���̒����̎擾�A�ݒ�
	float GetLengthPolygon(void);
	void SetLengthPolygon(float fLength);

	//�|���S���̑傫���̎擾�A�ݒ�
	float GetWidthPolygon(void);
	float GetHeightPolygon(void);


protected:

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_posPolygon;			// �|���S���̈ʒu
	D3DXVECTOR3				m_rotPolygon;			// �|���S���̉�]
	float m_fLengthPolygon;	//�|���S���̒���
	float m_fAnglePolygon;	//�|���S���̊p�x
	float m_fPolygonWidth;	//�|���S���̕�
	float m_fPolygonHeight;	//�|���S���̍���
	int m_nCntflame;		//�J�E���g
	int m_nNumScene2D;	//2D�|���S����
	static CManager *m_pManager;//�}�l�[�W��
	int m_nPriority;
};

#endif
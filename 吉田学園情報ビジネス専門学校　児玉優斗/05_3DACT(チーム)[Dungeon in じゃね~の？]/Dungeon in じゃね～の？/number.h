//=============================================================================
//
// ��������[2D �|���S��] [number.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
class CNumber
{
public:

	CNumber();	//�R���X�g���N�^
	~CNumber();	//�f�X�g���N�^
	static CNumber *Create(D3DXVECTOR3 pos, float width, float height);//�G�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	static HRESULT Load(void);
	static void Unload(void);
	void BindTexture(LPDIRECT3DTEXTURE9 tex);//�e�N�X�`���̊��蓖��
	void SetTexture(float fTex_X, float fTex_Y);//�e�N�X�`���̐ݒ�
	void SetColor(D3DXCOLOR col);	//�F�̐ݒ�

	void SetNumber(int nNumber);


	//�e�N�X�`���A�j���[�V����
	void SetTextureAnim(float fTex_X, float fTex_Y, int nPatternAnim);

	//�|���S���̑傫���̎擾�A�ݒ�
	void SetNumberWidth(float fWidth);
	void SetNumberHeight(float fWidth);

	//�|���S���̈ʒu���̎擾�A�ݒ�
	D3DXVECTOR3 GetPosNumber(void);
	void SetPosNumber(D3DXVECTOR3 pos);

	//�|���S���̊p�x���̐ݒ�A�ݒ�
	D3DXVECTOR3 GetRotNumber(void);
	void SetRotNumber(D3DXVECTOR3 rot);

	//�|���S���̒����̎擾�A�ݒ�
	float GetLengthNumber(void);
	void SetLengthNumber(float fLength);

	//�|���S���̑傫���̎擾�A�ݒ�
	float GetWidthNumber(void);
	float GetHeightNumber(void);



private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	 LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_posNumber;			// �|���S���̈ʒu
	D3DXVECTOR3				m_rotNumber;			// �|���S���̉�]
	float m_fLengthNumber;	//�|���S���̒���
	float m_fAngleNumber;	//�|���S���̊p�x
	float m_fNumberWidth;	//�|���S���̕�
	float m_fNumberHeight;	//�|���S���̍���
	int m_nNumber;
};

#endif
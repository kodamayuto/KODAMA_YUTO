//=============================================================================
//
// �^�C�g������[2D �|���S��] [title.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
//*****************************************************************************
// �^�C�g����ʂ̃N���X�\����
//*****************************************************************************
class CTitleLogo;
class CTitle
{
public:
	CTitle();	//�R���X�g���N�^
	~CTitle();	//�f�X�g���N�^
	//static CTitle *Create(void);	//�^�C�g���̐���
	static HRESULT Init(void);	//����������
	static void Uninit(void);	//�I������
	static void Update(void);	//�X�V����
	static void Draw(void);	//�`�揈��
private:
	static CTitleLogo *m_pTitleLogo;//�^�C�g�����S
	static CObject *m_pObject;				//�I�u�W�F�N�g
	static CMeshField *m_pMeshField;		//���b�V���t�B�[���h
};

#endif
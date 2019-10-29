//=============================================================================
//
// ���C�g���� [light.h]
// Author :
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

#define MAX_LIGHT (3)
//*****************************************************************************
// �J�����̃N���X�\����
//*****************************************************************************
class CLight
{
public:
	CLight();	//�R���X�g���N�^
	~CLight();	//�f�X�g���N�^
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
private:
	static CManager *m_pManager;//�}�l�[�W��
	D3DLIGHT9 m_Light[MAX_LIGHT];	//���C�g

};


#endif

//=============================================================================
//
// �`���[�g���A������[2D �|���S��] [tutorial.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY (50)
#define MAX_TUTORIAL_UI (12)

#include "main.h"
class CTutoLogo;
class CTutorial
{
public:

	CTutorial();	//�R���X�g���N�^
	~CTutorial();	//�f�X�g���N�^
	static HRESULT Init(void);	//����������
	static void Uninit(void);	//�I������
	static void Update(void);	//�X�V����
	static void Draw(void);	//�`�揈��
private:
	static CTutoLogo *m_pTutoLogo;
};

#endif
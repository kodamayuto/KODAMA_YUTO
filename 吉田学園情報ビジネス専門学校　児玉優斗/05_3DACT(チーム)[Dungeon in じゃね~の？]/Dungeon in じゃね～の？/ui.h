//=============================================================================
//
// �w�i����[2D �|���S��] [bg.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE_UI (5)	//�e�N�X�`����
#define MAX_UI (5)			//UI��

//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
class CUi : public CScene
{
public:
	typedef enum
	{
		UI_TYPE_COIN = 0,		// �R�C��
		UI_TYPE_KEY,			// �J�M
		UI_TYPE_SLASH,			// �X���b�V��
		UI_TYPE_MINUTES,		// ��
		UI_TYPE_DOT,			// �h�b�g
		UI_TYP_MAX				//UI�̍ő吔
	}UITYPE;//UI�̎��
	CUi(int nPriority = 6, OBJTYPE type = OBJTYPE_UI);	//�R���X�g���N�^
	~CUi();	//�f�X�g���N�^
	static CUi *Create(void);	//�w�i�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	static HRESULT Load(void);//�e�N�X�`���̓ǂݍ���
	static void Unload(void);//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_UI]; //���L�e�N�X�`���̃|�C���^
	D3DXCOLOR m_Color;
	int m_nCntColor;	//�J���[�J�E���g�p
	CScene2D *m_pScene2D[MAX_UI];
	UITYPE m_Type;	//�w�i�̃^�C�v
};

#endif
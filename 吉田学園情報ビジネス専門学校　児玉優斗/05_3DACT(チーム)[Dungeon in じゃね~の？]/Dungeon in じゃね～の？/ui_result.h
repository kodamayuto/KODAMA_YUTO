//=============================================================================
//
// �w�i����[2D �|���S��] [bg.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _UIRESULT_H_
#define _UIRESULT_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE_UI_RESULT (4)	//�e�N�X�`����
#define MAX_UI_RESULT (4)			//UI��

//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
class CUiResult : public CScene
{
public:
	typedef enum
	{
		UI_TYPE_RESULT = 0,		// ���U���g
		UI_TYPE_WATCH,			// ���v
		UI_TYPE_MINUTES,		// ��
		UI_TYPE_DOT,			// �h�b�g
		UI_TYP_MAX				//UI�̍ő吔
	}UITYPE;//UI�̎��
	CUiResult(int nPriority = 6, OBJTYPE type = OBJTYPE_UIRESULT);	//�R���X�g���N�^
	~CUiResult();	//�f�X�g���N�^
	static CUiResult *Create(void);	//�w�i�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	static HRESULT Load(void);//�e�N�X�`���̓ǂݍ���
	static void Unload(void);//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_UI_RESULT]; //���L�e�N�X�`���̃|�C���^
	D3DXCOLOR m_Color;
	int m_nCntColor;	//�J���[�J�E���g�p
	CScene2D *m_pScene2D[MAX_UI_RESULT];
	UITYPE m_Type;	//�w�i�̃^�C�v
};

#endif
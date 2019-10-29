//=============================================================================
//
// �w�i����[2D �|���S��] [bg.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _UIRANKING_H_
#define _UIRANKING_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE_UI_RANKING (4)	//�e�N�X�`����
#define MAX_UI_RANKING (12)			//UI��

//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
class CUiRanking : public CScene
{
public:
	typedef enum
	{
		UITEX_RANKING = 0,		//�����L���O
		UITEX_RANK,				//����
		UITEX_MINUTES,			//��
		UITEX_DOT,				//�h�b�g
		UITEX_MAX				//UI�̍ő吔
	}UITEX;//UI�̎��

	typedef enum
	{
		UI_TYPE_RANKING = 0,		// ���U���g
		UI_TYPE_RANK,				// ���v
		UI_TYPE_FIRSTMINUTES,		// 1st��
		UI_TYPE_FIRSTDOT,			// 1st�h�b�g
		UI_TYPE_SECONDMINUTES,		// 2nd��
		UI_TYPE_SECONDDOT,			// 2nd�h�b�g
		UI_TYPE_THIRDMINUTES,		// 3rd��
		UI_TYPE_THIRDDOT,			// 3rd�h�b�g
		UI_TYPE_FORTHMINUTES,		// 4th��
		UI_TYPE_FORTHDOT,			// 4h�h�b�g
		UI_TYPE_FIFTHMINUTES,		// 5th��
		UI_TYPE_FIFTHDOT,			// 5th�h�b�g
		UI_TYPE_MAX				//UI�̍ő吔
	}UITYPE;//UI�̎��
	CUiRanking(int nPriority = 6, OBJTYPE type = OBJTYPE_UIRESULT);	//�R���X�g���N�^
	~CUiRanking();	//�f�X�g���N�^
	static CUiRanking *Create(void);	//�w�i�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	static HRESULT Load(void);//�e�N�X�`���̓ǂݍ���
	static void Unload(void);//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_UI_RANKING]; //���L�e�N�X�`���̃|�C���^
	D3DXCOLOR m_Color;
	int m_nCntColor;	//�J���[�J�E���g�p
	CScene2D *m_pScene2D[MAX_UI_RANKING];
	UITYPE m_Type;	//�w�i�̃^�C�v
};

#endif
//=============================================================================
//
// ���S�̏���[2D �|���S��] [logo.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TITLE_NUM (2)
#define MAX_TITLE_TEXTURE (2)

//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
class CTitleLogo : public CScene
{
public:
	typedef enum
	{
		TITLESTATE_NONE = 0,	//��̏��
		TITLESTATE_NORMAL,		//�ʏ���
		TITLESTATE_USE,			//�G���^�[�������ꂽ���
		TITLESTATE_MAX			//��Ԃ̍ő吔
	}TITLESTATE;
	typedef enum
	{
		TITLETYPE_LOGO = 0,		//�^�C�g�����S
		TITLETYPE_PRESS,		//�v���X�G���^�[
		TITLETYPE_MAX			//�^�C�g���̎�ނ̍ő吔
	}TITLETYPE;
	CTitleLogo();				//�R���X�g���N�^
	~CTitleLogo();				//�f�X�g���N�^
	static HRESULT Load(void);	//�e�N�X�`���̓ǂݍ���
	static void Unload(void);	//�e�N�X�`���̔j��
	static CTitleLogo *Create(void);	//�G�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TITLE_TEXTURE]; //���L�e�N�X�`���̃|�C���^
	static CScene2D *m_apScene2D[MAX_TITLE_NUM];//�V�[��2D
	static D3DXCOLOR m_col; //�F���
	int m_nCntFrame;//�t���[�����̃J�E���g
	float m_fWidth;//��
	float m_fHeight;//����
	TITLESTATE m_state;//���
	TITLETYPE m_type;//�^�C�g���̎��
	int m_TexNum;	//�e�N�X�`���̔ԍ�
	static int m_nJumpRankingFrame;//�����L���O��ʂ֑J�ڂ���Ƃ��̃t���[���J�E���^
};

#endif
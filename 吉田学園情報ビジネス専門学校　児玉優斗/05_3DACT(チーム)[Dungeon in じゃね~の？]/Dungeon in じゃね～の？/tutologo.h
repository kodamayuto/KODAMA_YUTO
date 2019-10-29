//=============================================================================
//
// ���S�̏���[2D �|���S��] [logo.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _TUTOLOGO_H_
#define _TUTOLOGO_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TUTO_NUM (2)
#define MAX_TIUTO_TEXTURE (2)


//�O���錾 --�X�y���~�X�ɒ��ӁI(�Ȃ�ł��ʂ邩��I)
class CTutoLogo : public CScene
{
public:
	typedef enum
	{
		TUTOSTATE_NONE = 0,	//��̏��
		TUTOSTATE_NORMAL,		//�ʏ���
		TUTOSTATE_USE,			//�G���^�[�������ꂽ���
		TUTOSTATE_MAX			//��Ԃ̍ő吔
	}TUTOSTATE;
	typedef enum
	{
		TIUTOTYPE_LOGO = 0,		//�^�C�g�����S
		TIUTOTYPE_PRESS,		//�v���X�G���^�[
		TIUTOTYPE_MAX			//�^�C�g���̎�ނ̍ő吔
	}TIUTOTYPE;
	CTutoLogo();				//�R���X�g���N�^
	~CTutoLogo();				//�f�X�g���N�^
	static HRESULT Load(void);	//�e�N�X�`���̓ǂݍ���
	static void Unload(void);	//�e�N�X�`���̔j��
	static CTutoLogo *Create(void);	//�G�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TIUTO_TEXTURE]; //���L�e�N�X�`���̃|�C���^
	static CScene2D *m_apScene2D[MAX_TUTO_NUM];//�V�[��2D
	static D3DXCOLOR m_col; //�F���
	int m_nCntFrame;//�t���[�����̃J�E���g
	float m_fWidth;//��
	float m_fHeight;//����
	TUTOSTATE m_state;//���
	TIUTOTYPE m_type;//�^�C�g���̎��
	int m_TexNum;	//�e�N�X�`���̔ԍ�
	static int m_nJumpRankingFrame;//�����L���O��ʂ֑J�ڂ���Ƃ��̃t���[���J�E���^
};

#endif
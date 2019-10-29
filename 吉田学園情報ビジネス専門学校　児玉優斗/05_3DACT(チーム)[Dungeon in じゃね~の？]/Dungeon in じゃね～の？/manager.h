//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//�O���錾(���̂ɒ��ӁI�Ȃ�ł��ʂ邩��I)
class CScene2D;
class CScene3D;
class CScene;
class CSceneX;
class CSceneBillBoard;
class CMeshField;
class CSound;
class CLight;
class CCamera;
class CDebugProc;
class CPlayer;
class CEnemy;
class CModel;
class CObject;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CRanking;
class CSound;
class CInputX;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �}�l�[�W���[�̃N���X�\����
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	}MODE;
	CManager();	//�R���X�g���N�^
	~CManager();//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

	//�ÓI�����o�֐�
	static CInputKeyboard *GetInputKeyboard(void);	//�L�[�{�[�h�̎擾
	static CRenderer *GetRenderer(void);			//�����_���[�̎擾
	static CCamera *GetCamera(void);				//�J�����̎擾
	static CScene3D *GetScene3D(void);				//�V�[��3D�̎擾
	static CSound *GetSound(void);					//�T�E���h�̎擾
	static CInputX *GetInput(void);					//�W���C�p�b�h
	static void SetMode(MODE mode);					//���[�h�̐ݒ�
	static MODE GetMode(void);						//���[�h�̎擾


	// �^�C�}�[�Ŏg�p
	static void SetTimer(int nTenMinutes, int nOneMinutes, int nTenSeconds, int nOneSeconds, int nTenComma, int nOneComma);
	static int GetTimer(void);
	static int GetTenMinutes(void) { return m_nTenMinutes; }			//10����
	static int GetOneMinutes(void) { return m_nOneMinutes; }		  //1����
	static int GetTenSeconds(void) { return m_nTenSeconds; }		  //10�b��
	static int GetOneSeconds(void) { return m_nOneSeconds; }		 //10�b��
	static int GetTenComma(void) { return m_nTenComma; }			 //�R���}�b
	static int GetOneComma(void) { return m_nOneComma; }		//�R���}�b


private:
	static CTitle *m_pTitle;					//�^�C�g��
	static CTutorial *m_pTutorial;				//�`���[�g���A��
	static CGame *m_pGame;						//�Q�[��
	static CResult *m_pResult;					//���U���g
	static CRanking *m_pRanking;				//�����L���O
	static CSound *m_pSound; //�T�E���h�̃|�C���^
	static CRenderer *m_pRenderer;				//�����_���̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^
	static MODE m_mode;							//���[�h
	static CScene3D *m_pScene3D;				//3D�V�[��
	static CDebugProc *m_pDebugProc;			//�f�o�b�O�\��
	static CCamera *m_pCamera;					//�J����
	static CLight *m_pLight;					//���C�g
	static CInputX *m_pInputX;					//�W���C�p�b�h
	bool m_bDebug;								//�f�o�b�O�p


	// �^�C�}�[�̒l��ۑ�����ׂɎg�p
	static int m_nTimer;							//�^�C�}�[
	static int m_nTenMinutes;						//10����
	static int m_nOneMinutes;						//1����
	static int m_nTenSeconds;						//10�b��
	static int m_nOneSeconds;						//10�b��
	static int m_nTenComma;							//�R���}�b
	static int m_nOneComma;							//�R���}�b

	// �R�C���̒l��ۑ�����ׂɎg�p
	static int m_nCoin;									// �R�C���ɒl��Ԃ�
};


#endif
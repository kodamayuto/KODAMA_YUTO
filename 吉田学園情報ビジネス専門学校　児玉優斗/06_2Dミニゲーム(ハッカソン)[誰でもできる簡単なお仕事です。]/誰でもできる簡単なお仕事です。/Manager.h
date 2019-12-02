//=============================================================================
//
// �Ǘ��N���X���� [Manager.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "InputKeyboard.h"
#include "camera.h"
#include "light.h"
#include "DebugProc.h"
#include "texture.h"
#include "Command.h"
#include "sound.h"
#include "InputXPad.h"

#include "UtilityMath.h"
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CRanking;
class CFade;
class CPause;
//==================================================================
//	�N���X�̒�`
//==================================================================
//�Ǘ��N���X
class CManager
{
public:
	typedef enum
	{
		DIR_UP,
		DIR_RIGHT,
		DIR_LEFT,
		DIR_DOWN,
		DIR_MAX
	}DIRECTION;

	typedef enum
	{//��ʂ̒�`
		MODE_NONE = 0,	//���[�h��(�����l)
		MODE_LOGO,		//���S�\�����
		MODE_TITLE,		//�^�C�g�����
		MODE_SELECT,	//�Z���N�g���
		MODE_TUTORIAL,	//�`���[�g���A�����
		MODE_GAME,		//�Q�[�����
		MODE_RESULT,	//���U���g���
		MODE_RANKING,	//�����L���O���
		MODE_OPTION,	//�I�v�V�������
		MODE_MAX
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);


	static CRenderer*		GetRenderer(void) { return m_pRenderer; };
	static CInputKeyboard*  GetInputKeyboard(void) { return m_pInputKeyboard; };
	static CCamera*  GetCamera(void) { return m_pCamera; };
	static CLight*  GetLight(void) { return m_pLight; };
	static CDebugProc* GetDebugProc(void) { return m_pDebugProc; };
	static CFade* GetFade(void) { return m_pFade; };
	static CPause* GetPause(void) { return m_pPause; };
	static CSound* GetSound(void) { return m_pSound; };
	static CInputXPad* GetXInput(void) { return m_pXInput; };

	static CGame* GetGame(void) { return m_pGame; };
	static HRESULT SetMode(MODE mode);
	static LPCSTR GetModeName(void);

	static bool GetPauseFlag(void) { return m_bPauseFlag; };
	static void ChangePauseFlag(void) { m_bPauseFlag ^= 1; };		//�t���O���]

private:
	static CRenderer*		m_pRenderer;
	static CInputKeyboard*	m_pInputKeyboard;
	static CCamera*			m_pCamera;
	static CLight*			m_pLight;
	static CDebugProc*		m_pDebugProc;
	static CPause*			m_pPause;
	static CSound*			m_pSound;
	static CInputXPad*		m_pXInput;

	static CFade*			m_pFade;
	//��ԑJ�ڗp�|�C���^
	static CTitle*			m_pTitle;			//�^�C�g��
	static CTutorial*		m_pTutorial;		//�`���[�g���A��
	static CGame*			m_pGame;			//�Q�[��
	static CResult*			m_pResult;			//���U���g
	static CRanking*		m_pRanking;			//�����L���O


	//���̑��ϐ�
	static MODE m_Mode;		//���݂̉�ʏ��
	static MODE m_OrgMode;	//��O�̉�ʏ��

	static bool m_bPauseFlag;		//�|�[�Y����

};

//==================================================================================================//
//     �e���v���[�g��`(Scene�n�ȊO�̐���)
//==================================================================================================//
template<class T> bool Create(T *&pObj)
{
	pObj = NULL;
	pObj = new T;
	if (pObj != NULL) { pObj->Init(); return true; }
	return false;
}

//==================================================================================================//
//     �e���v���[�g��`(Scene�n�ȊO�̉��)
//==================================================================================================//
template<class T> bool Release(T *&pObj)
{
	if (pObj != NULL)
	{
		pObj->Uninit();
		delete pObj;
		pObj = NULL;
		return true;
	}
	return false;
}

#endif // !_MANAGER_H_


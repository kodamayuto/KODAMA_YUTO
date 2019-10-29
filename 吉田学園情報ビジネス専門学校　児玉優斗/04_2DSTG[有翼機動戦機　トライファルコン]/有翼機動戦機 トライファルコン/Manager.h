//=============================================================================
//
// 管理クラス処理 [Manager.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "InputKeyboard.h"
#include "DinputController.h"
#include "sound.h"
#include "pause.h"

class CFade;
class CGame;
class CTitle;
class CModeSelect;
class CTutorial;
class CResult;
class CRanking;
//==================================================================
// マクロ定義
//==================================================================
#define MOVESTOP_RANGE (330.0f) //端からの移動出来ない範囲
#define RESPAWN_INTERVAL (120)	//再出撃までの時間

//==================================================================
//	クラスの定義
//==================================================================
//管理クラス
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_SELECT,
		MODE_GAME_CARAVAN,
		MODE_RESULT,
		MODE_RANKING,
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
	static CDInputController* GetController(void) { return m_pDInputController; };
	static CSound*			GetSound(void) { return m_pSound; };
	static CFade*			GetFade(void) { return m_pFade; };
	static CPause*			GetPause(void) { return m_pPause; };

	static HRESULT SetMode(MODE mode);
	static MODE    GetMode(void) { return m_Mode; };

	static void PauseModeChange(void);
	static void PauseModeChange(bool bMode) { m_bPauseFrag = bMode; };

	static bool GetPauseFrag(void) { return m_bPauseFrag; };
private:
	static bool					m_bPauseFrag;
	//各種ポインタ
	static CRenderer*			m_pRenderer;
	static CInputKeyboard*		m_pInputKeyboard;
	static CDInputController*	m_pDInputController;
	static CSound*			    m_pSound;
	static CFade*			    m_pFade;
	static CPause*				m_pPause;

	//画面遷移用ポインタ
	static CTitle*          m_pTitle;
	static CModeSelect*     m_pModeSelect;
	static CTutorial*		m_pTutorial;
	static CGame*           m_pGame;
	static CResult*         m_pResult;
	static CRanking*        m_pRanking;

	//画面遷移用の列挙
	static MODE                    m_Mode;
};
#endif // !_MANAGER_H_


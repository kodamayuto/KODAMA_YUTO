//=============================================================================
//
// �Q�[����ʊǗ��N���X���� [game.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "Manager.h"

#include "life.h"
#include "endcall.h"
#include "ControlUI.h"
#include "gameUI.h"

#include "Baggage.h"
#include "JudgeBaggage.h"
#include "Score.h"
#include "truck.h"
#include "StartCall.h"
#include "worker.h"

class CSound;
class CScene2D;

//===================================================================
//	�N���X�̒�`
//===================================================================
class CGame
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CScore* GetScore(void) { return m_pScore; };
	static CLife* GetLife(void) { return m_pLife; };

	void SetCountFlag(bool bFlag);

	void SetClearFlag(void) { m_bClear = true; };

	//	---<<�ǉ�>>---
	void TimeCount(int nNumSplit);	//	TimeCount(��������)
	//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��


private:
	CBaggage* m_pBaggage;
	static CScore* m_pScore;

	static CLife* m_pLife;
	CEndCall* m_pEndCall;
	CControlUI* m_pControlUI;
	CGameUI* m_pGameUI;
	CStartCall* m_pStateCall;	//	�X�^�[�g�R�[��
	CWoker* m_pWoker[3];		//	��ƈ�
	//	---<<�ǉ�>>---
	static CSound *m_pSound;
	CScene2D * m_pScene2D;
	bool m_bCntFlag;		//	�J�E���g�J�n�̃t���O����
	int m_nCnt;				//	�^�C���J�E���g��i�߂�
	//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��


	bool m_bClear;
	int m_nCntClearTimer;

};
#endif // !_GAME_H_

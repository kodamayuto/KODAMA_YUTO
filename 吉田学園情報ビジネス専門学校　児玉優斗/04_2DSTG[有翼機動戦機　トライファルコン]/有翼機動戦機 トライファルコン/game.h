//=============================================================================
//
// ゲーム画面管理クラス処理 [game.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "Manager.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "BG.h"
#include "enemy.h"
#include "Score.h"
#include "number.h"
#include "PlayerUI.h"
#include "effect.h"
#include "Gauge.h"
#include "Time.h"
#include "enemyGenerator.h"


class CGame
{
public:
	CGame();
	~CGame();

	static CGame* Create(void);
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CPlayer*			GetPlayer(void) { return m_pPlayer; };
	static CScore*			GetScore(void) { return m_pScore; };
	static CPlayerUI*		GetPlayerUI(void) { return m_pPlayerUI; };
	static CTime*			GetTimer(void) { return m_pTime; };
	static CEGenerator*     GetGenerator(void) { return m_pEGenerator; };
	static void SetRespawnTimer(void) { m_nRespawnTimer = RESPAWN_INTERVAL; };

	static void				AddNumAbsorb(void) { m_nNumAbsorb++; };
	//リザルトへの受け渡し用
	static int				GetOldScore(void) { return m_nScore; };
	static int				GetNumAbsorb(void) { return m_nNumAbsorb; };
private:
	static CPlayer*			m_pPlayer;
	static CScore*          m_pScore;
	static CPlayerUI*       m_pPlayerUI;
	static CTime*			m_pTime;
	static CEGenerator*     m_pEGenerator;
	static int m_nRespawnTimer;

	//リザルトへの受け渡し用
	static int m_nScore;
	static int m_nNumAbsorb;
};
#endif // !_GAME_H_

//=============================================================================
//
// ÉQÅ[ÉÄâÊñ ä«óùÉNÉâÉXèàóù [game.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
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


class CTutorial
{
public:
	CTutorial();
	~CTutorial();

	static HRESULT Load(void);
	static void Unload(void);

	static CTutorial* Create(void);
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CPlayer*			GetPlayer(void) { return m_pPlayer; };
	static CPlayerUI*		GetPlayerUI(void) { return m_pPlayerUI; };
	static void SetRespawnTimer(void) { m_nRespawnTimer = RESPAWN_INTERVAL; };

private:
	static CPlayer*			m_pPlayer;
	static CPlayerUI*       m_pPlayerUI;
	static int m_nRespawnTimer;

	CScene2D*		m_pTutorial;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif // !_TUTORIAL_H_

//=============================================================================
//
// 敵出現クラス処理 [enemyGenerator.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ENEMY_GENERATOR_H_
#define _ENEMY_GENERATOR_H_

#include "main.h"
#include "scene.h"
#include "enemy.h"

//
//
//

//
//
//
class CEGenerator : public CScene
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TUTORIAL,
		MODE_3MIN_CARAVAN,
		MODE_MAX
	}GENERATE_MODE;

	CEGenerator();
	~CEGenerator();

	static CEGenerator* Create(GENERATE_MODE GMode);
	static int &GetCntEnemy(void) { return m_nCntEnemy; };
	HRESULT Init(void);
	HRESULT Init(GENERATE_MODE GMode);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

private:
	void	Generate(void);
	void    PatternChange(void);

	static int  m_nCntEnemy;
	GENERATE_MODE m_GMode;			//生成モード
	int			  m_nGenPattern;	//生成カウンタ

protected:
};
#endif // !_ENEMY_GENERATOR_H_

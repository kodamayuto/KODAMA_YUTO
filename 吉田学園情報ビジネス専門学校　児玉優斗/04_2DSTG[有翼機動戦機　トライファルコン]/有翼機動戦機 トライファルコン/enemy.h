//=============================================================================
//
// 敵クラス処理 [enemy.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene2D.h"
#include "player.h"
//==================================================================
//	クラスの定義
//==================================================================
//プレイヤークラス
class CEnemy : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_LIGHT,
		TYPE_NORMAL_SECOND,
		TYPE_MAX,
	}TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_MOVE,
		STATE_DAMAGE,
		STATE_REPEAL,
		STATE_MAX
	}STATE;

	static HRESULT Load(void);
	static void    Unload(void);

	//コンストラクタ&デストラクタ
	CEnemy();
	~CEnemy();

	HRESULT Init(void);
	void    Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSize, TYPE type);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CEnemy* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,float size,ELEMENT element,TYPE type);

	bool Damage(int nDamage);
	void SetElement(ELEMENT element) { m_element = element; };
	ELEMENT GetElement(void) { return m_element; };

private:
	CPlayer* GetTargetPlayer(void);
	void     HitCheck(D3DXVECTOR3 pos);

	CScene::ELEMENT m_element;
	STATE           m_State;
	TYPE			m_Type;
	static LPDIRECT3DTEXTURE9 m_apTexture[ELEMENT_MAX][TYPE_MAX];				//共有テクスチャへのポインタ

	D3DXVECTOR3				m_PosDest;					//目標の座標
	int						m_nCntBullet = 0;			//弾カウンタ
	float					m_fRot = D3DX_PI * 0.25f;	//回転
	D3DXVECTOR3				m_Move;						//移動量
	D3DXVECTOR3				m_OriginPos;				//基準位置
	int						m_nHP;						//体力
	CPlayer*				m_pTargetPlayer;			//追尾のターゲット設定用
	int						m_nDamageCounter;			//ダメージ時の点滅用カウンター

	//影用
	CScene2D*               m_pShadow;

protected:
};
#endif // !_ENEMY_H_

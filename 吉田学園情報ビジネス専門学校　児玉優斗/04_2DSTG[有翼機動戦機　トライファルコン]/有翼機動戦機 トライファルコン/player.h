//=============================================================================
//
// プレイヤークラス処理 [player.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2D.h"


#define TEX_NUM			 (3)		//テクスチャ数
#define MAX_VITALITY     (12)		//最大HP
#define MAX_STOCK		 (3)		//最大残機数
#define PLAYER_PRIORITY (4)
class CInputKeyboard;
class CTime;
//==================================================================
//	クラスの定義
//==================================================================
//プレイヤークラス
class CPlayer : public CScene2D
{
public:

	typedef enum
	{
		STATE_NONE = 0,
		STATE_TRANSPARENT,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	//コンストラクタ&デストラクタ
	CPlayer();
	~CPlayer();

	//メンバ関数
	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CPlayer* Create(void);
	static void     SetStock(int nStock = MAX_STOCK) { m_nStock = nStock; };
	static int      GetStock(void){ return m_nStock; };
	bool Damage(int nDamage);
	int GetHP(void) { return m_nHP; };

	void SetElement(ELEMENT element) { m_element = element; };
	ELEMENT GetElement(void) { return m_element; };

	void SetGauge(ELEMENT element, float fAddGauge) { m_fElementGauge[element] += fAddGauge; };

private:
	//メンバ関数
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void		HitCheck(D3DXVECTOR3 pos);
	//メンバ変数
	CScene::ELEMENT m_element;							//属性
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_NUM];		//共有テクスチャへのポインタ
	static int				  m_nStock;					//残機

	D3DXVECTOR3				m_Move;						//移動量
	int						m_nCntBullet = 0;			//弾用カウンタ
	int						m_nCntTransParent;			//透明用カウンタ
	int						m_nHP;						//体力
	float					m_fRot = D3DX_PI * 0.25f;	//回転
	float					m_fHitSize;					//弾の当たり判定のサイズ
	float					m_fElementGauge[3];			//属性ごとのゲージ
	STATE					m_PlayerState;				//プレイヤーの状態
	ELEMENT					m_UnionElement;				//合体後に戻る属性
	CTime*					m_UnionTimer;				//合体タイマー
	//影用
	CScene2D*               m_pShadow;

	//バリア用
	CScene2D*				m_pBarrier;

protected:
};
#endif // !_PLAYER_H_

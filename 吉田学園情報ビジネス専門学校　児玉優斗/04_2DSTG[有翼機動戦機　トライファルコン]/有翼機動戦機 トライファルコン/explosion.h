//=============================================================================
//
// 爆発クラス処理 [explosion.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "scene2D.h"

//==================================================================
//	クラスの定義
//==================================================================
//プレイヤークラス
class CExplosion : public CScene2D
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_ABSORB,
		TYPE_MAX
	}TYPE;
	//コンストラクタ&デストラクタ
	CExplosion();
	~CExplosion();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);
	void Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CExplosion* Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fSize,TYPE type);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];				//共有テクスチャへのポインタ

	int m_nAnim;				//爆発の表示時間
	int m_nAnimInterval;		//アニメーションの遷移時間
protected:
};
#endif // !_EXPLOSION_H_

//=============================================================================
//
// 弾クラス処理 [effect.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "scene2D.h"

//==================================================================
//	クラスの定義
//==================================================================
//プレイヤークラス
class CEffect : public CScene2D
{
public:

	typedef enum
	{//弾の管理者分け用
		AUTHOR_NONE,
		AUTHOR_PLAYER,
		AUTHOR_ENEMY,
	}AUTHORITY;

	//コンストラクタ&デストラクタ
	CEffect();
	~CEffect();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);
	void Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CEffect* Create(D3DXVECTOR3 pos,AUTHORITY author,float fSize,D3DXCOLOR col);
	AUTHORITY GetAuthor(void) { return m_Author; };


private:
	static LPDIRECT3DTEXTURE9 m_apTexture[2];	//共有テクスチャへのポインタ
	AUTHORITY				m_Author;					//弾の権利者
	D3DXCOLOR				m_Col;
protected:
};
#endif // !_PLAYER_H_

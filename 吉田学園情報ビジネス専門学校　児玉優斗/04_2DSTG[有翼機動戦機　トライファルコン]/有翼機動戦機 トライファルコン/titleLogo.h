//=============================================================================
//
// 爆発クラス処理 [titleLogo.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "scene.h"
#include "scene2D.h"

//==================================================================
// マクロ定義
//==================================================================

//==================================================================
//	クラスの定義
//==================================================================
//プレイヤークラス
class CTitleLogo : public CScene
{
public:
	//コンストラクタ&デストラクタ
	CTitleLogo();
	~CTitleLogo();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CTitleLogo* Create();

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//共有テクスチャへのポインタ
	CScene2D* m_pLogo;


protected:
};
#endif // !_TITLELOGO_H_

//=============================================================================
//
// 爆発クラス処理 [BG.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "scene.h"
#include "scene2D.h"

//==================================================================
// マクロ定義
//==================================================================
#define MAIN_BG_NUM (2)
#define SIDE_BG_NUM (2)

//==================================================================
//	クラスの定義
//==================================================================
//プレイヤークラス
class CBg : public CScene
{
public:
	typedef enum
	{
		TYPE_0 = 0,
		TYPE_1,
		TYPE_2,
		TYPE_MAX
	}TYPE;
	//コンストラクタ&デストラクタ
	CBg();
	~CBg();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CBg* Create();

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];				//共有テクスチャへのポインタ
	CScene2D* m_apMainBG[MAIN_BG_NUM];
	CScene2D* m_apSideBG[SIDE_BG_NUM];

protected:
};
#endif // !_BG_H_

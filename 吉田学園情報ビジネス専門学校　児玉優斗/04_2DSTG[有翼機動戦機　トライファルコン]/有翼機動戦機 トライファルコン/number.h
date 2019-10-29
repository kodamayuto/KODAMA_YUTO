//=============================================================================
//
// 番号クラス処理 [number.h]
// Author : Kodama Yuto
//
//=============================================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//==================================================================
// クラスの定義
//==================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void    Unload(void);

	static CNumber* Create(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect,int nNum);// 座標、サイズ、番号をInitに渡す
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nNum);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void SetNumber(int nNum);
	void SetPosition(D3DXVECTOR3 pos);
	void SetColor(D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;					// テクスチャへのポインタ		// BindTextureは使わない
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXVECTOR3						m_pos;						// ポリゴンの位置
	D3DXVECTOR2						m_polygonRect;				// ポリゴンの大きさ
	D3DXCOLOR						m_col;						// 色
	int  m_nNumber;												// 番号
};
#endif // !_NUMBER_H_

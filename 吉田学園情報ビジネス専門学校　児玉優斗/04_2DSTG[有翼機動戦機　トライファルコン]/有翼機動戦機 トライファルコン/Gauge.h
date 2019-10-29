//=============================================================================
//
// 番号クラス処理 [Gauge.h]
// Author : Kodama Yuto
//
//=============================================================================

#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"
#include "scene.h"
//==================================================================
// クラス
//==================================================================
class CGauge
{
public:
	CGauge();
	~CGauge();

	static HRESULT Load(void);
	static void    Unload(void);

	static CGauge* Create(D3DXVECTOR3 pos, float fSizeY,float fLength,CScene::ELEMENT elem);// 座標、サイズをInitに渡す
	HRESULT Init(D3DXVECTOR3 pos, float fSizeY, float fLength, CScene::ELEMENT elem);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void SetGauge(float fElementGauge);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;					// テクスチャへのポインタ		// BindTextureは使わない
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXVECTOR3						m_pos;						// ポリゴンの位置
	float							m_fSizeY;					// ゲージの幅

	float							m_fElementGauge;			// ゲージの長さ
	CScene::ELEMENT					m_Element;					// ゲージの属性

	int								m_nCntTime;				    // カウンタ
	D3DXCOLOR						m_OrgColor;					// 色保存用
};
#endif
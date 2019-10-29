//=============================================================================
//
// 弾クラス処理 [bullet.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene2D.h"

//==================================================================
//	マクロ定義
//==================================================================
#define BULLET_PRIORITY (3)
//==================================================================
//	クラスの定義
//==================================================================
//プレイヤークラス
class CBullet : public CScene2D
{
public:
	typedef enum
	{//弾の形と移動ルーチン分け用
		TYPE_BULLET_NORMAL = 0,
		TYPE_BULLET_HOMING,
		TYPE_MAX
	}TYPE;

	typedef enum
	{//弾の管理者分け用
		AUTHOR_NONE,
		AUTHOR_PLAYER,
		AUTHOR_ENEMY,
	}AUTHORITY;

	//コンストラクタ&デストラクタ
	CBullet();
	~CBullet();

	static HRESULT Load(void);
	static void    Unload(void);

	HRESULT Init(void);
	void Init(D3DXVECTOR3 pos, float fMove, D3DXVECTOR3 rot, D3DXCOLOR col);

	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	static CBullet* Create(D3DXVECTOR3 pos,float fMove,D3DXVECTOR3 rot,ELEMENT element,TYPE type,AUTHORITY author,bool bEffectUse);

	AUTHORITY GetAuthor(void) { return m_Author; };

	void SetElement(ELEMENT element) { m_element = element; };
	ELEMENT GetElement(void) { return m_element; };
	void SetTarget(CScene2D* pTarget) { m_pTarget = pTarget; };
private:
	CScene::ELEMENT m_element;
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//共有テクスチャへのポインタ
	AUTHORITY				m_Author;					//弾の権利者
	TYPE					m_type;						//弾のタイプ
	D3DXVECTOR3				m_Rot;						//回転
	float					m_fMove;					//移動量
	bool					m_bEffectFlag;				//エフェクト使用の可否
	D3DXCOLOR				m_Col;						//色
	CScene2D*				m_pTarget;					//追尾対象
	D3DXVECTOR3				m_TargetPosOld;
protected:
};
#endif // !_PLAYER_H_

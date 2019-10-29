//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//
//
//
#define NUM_PRIORITY (8)
#define MAX_SCENE    (20000)

//
//
//

class CScene
{
public:
	//オブジェクトの種類列挙
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOSION,
		OBJTYPE_BG,
		OBJTYPE_EFFECT,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;
	typedef enum
	{
		ELEMENT_RED = 0,
		ELEMENT_GREEN,
		ELEMENT_BLUE,
		ELEMENT_SUPER,
		ELEMENT_MAX
	}ELEMENT;

	CScene(int nPriority = 3);
	virtual ~CScene() {}

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void ReleaseAll(OBJTYPE type);
	static void UpdateAll(void);
	static void DrawAll(void);

	static int  GetNumAll(void);

	void		SetObjType(OBJTYPE type);
	OBJTYPE		GetObjType(void);
	static CScene* GetScene(int nPriority, int nIdx);


private:
	static CScene* m_apScene[NUM_PRIORITY][MAX_SCENE];
	int		m_nID;
	OBJTYPE m_objType;		//オブジェクトの種類

	int		m_nPriority;

protected:
	void Release(void);

	static int	   m_nNumAll;
	int						m_nCount = 0;				//カウンタ


};
#endif // !_SCENE_H_


//=============================================================================
//
// ���[�h�I����ʊǗ��N���X���� [ranking.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MODESELECT_H_
#define _MODESELECT_H_

#include "main.h"
#include "scene2D.h"
//
//
//
#define TILE_NUM (4)
#define TILE_TEX (2)
#define MAX_BG (3)

//
//
//

class CModeSelect
{
public:
	CModeSelect();
	~CModeSelect();

	static CModeSelect* Create(void);

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TILE_TEX];				//���L�e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexBG[MAX_BG];					//���L�e�N�X�`���ւ̃|�C���^(BG)

	CScene2D* m_apModeSelectTile[TILE_NUM];
	CScene2D* m_pBG[MAX_BG];

	static int		  m_nSelectTile;
	int		  m_nCount;
};
#endif // !_MODESELECT_H_

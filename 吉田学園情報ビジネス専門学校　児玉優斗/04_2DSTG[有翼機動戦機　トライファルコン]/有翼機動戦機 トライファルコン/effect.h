//=============================================================================
//
// �e�N���X���� [effect.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "scene2D.h"

//==================================================================
//	�N���X�̒�`
//==================================================================
//�v���C���[�N���X
class CEffect : public CScene2D
{
public:

	typedef enum
	{//�e�̊Ǘ��ҕ����p
		AUTHOR_NONE,
		AUTHOR_PLAYER,
		AUTHOR_ENEMY,
	}AUTHORITY;

	//�R���X�g���N�^&�f�X�g���N�^
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
	static LPDIRECT3DTEXTURE9 m_apTexture[2];	//���L�e�N�X�`���ւ̃|�C���^
	AUTHORITY				m_Author;					//�e�̌�����
	D3DXCOLOR				m_Col;
protected:
};
#endif // !_PLAYER_H_

//=============================================================================
//
// �I�u�W�F�N�g2D���� [scene2D.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "scene.h"

//==================================================================
//	�N���X�̒�`
//==================================================================
//�I�u�W�F�N�g2D�N���X
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority);
	~CScene2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene2D* Create(int nPriority);

	void SetColor(D3DXCOLOR col);
	void SetUV(D3DXVECTOR2 MinRect,D3DXVECTOR2 MaxRect);

	void        SetPosition(D3DXVECTOR3 pos);
	void        SetPosition(D3DXVECTOR3 pos,float fSize);
	void        SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 MinOffset,D3DXVECTOR3 MaxOffset);

	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	float GetSize(void) { return m_fSize; };

	void		BindTexture(LPDIRECT3DTEXTURE9 pTexture);

protected:
	float					m_fSize;					//�T�C�Y�ύX�p

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;						// �|���S���̈ʒu

};


#endif // !_SCENE2D_H_


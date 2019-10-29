//=============================================================================
//
// �I�u�W�F�N�g3D���� [scene3D.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "scene.h"

//==================================================================
//	�N���X�̒�`
//==================================================================
//�I�u�W�F�N�g3D�N���X
class CScene3D : public CScene
{
public:


	CScene3D(int priority = 4, OBJTYPE type = OBJTYPE_SCENE3D);

	~CScene3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene3D* Create(void);

	void        SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };

	void        SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void) { return m_rot; };

	void        SetColor(D3DXCOLOR col);
	void		SetSize(float fSize);
	void		BindTexture(LPDIRECT3DTEXTURE9 pTexture);

protected:

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3				m_rot;						//�p�x
	D3DXCOLOR				m_Color;					//�F
	D3DXMATRIX				m_mtxWorld;					//�|���S���̃}�g���b�N�X
	float					m_fSize;
};


#endif // !_SCENE2D_H_


//=============================================================================
//
// �ԍ��N���X���� [number.h]
// Author : Kodama Yuto
//
//=============================================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//==================================================================
// �N���X�̒�`
//==================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void    Unload(void);

	static CNumber* Create(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect,int nNum);// ���W�A�T�C�Y�A�ԍ���Init�ɓn��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nNum);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void SetNumber(int nNum);
	void SetPosition(D3DXVECTOR3 pos);
	void SetColor(D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;					// �e�N�X�`���ւ̃|�C���^		// BindTexture�͎g��Ȃ�
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3						m_pos;						// �|���S���̈ʒu
	D3DXVECTOR2						m_polygonRect;				// �|���S���̑傫��
	D3DXCOLOR						m_col;						// �F
	int  m_nNumber;												// �ԍ�
};
#endif // !_NUMBER_H_

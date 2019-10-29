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

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nNum,D3DXCOLOR Col);
	HRESULT Init(void);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void SetNumber(int nNum);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	D3DXCOLOR GetColor(void) { return m_Col; };
	D3DXVECTOR2 GetRect(void) { return m_polygonRect; };
	int GetNumber(void) { return m_nNumber; };

private:
	LPDIRECT3DTEXTURE9				m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3						m_pos;						// �|���S���̈ʒu(����)
	D3DXCOLOR						m_Col;						// �F
	D3DXVECTOR2						m_polygonRect;				// �|���S���̑傫��
	int								m_nNumber;					// �ԍ�
};
#endif // !_NUMBER_H_

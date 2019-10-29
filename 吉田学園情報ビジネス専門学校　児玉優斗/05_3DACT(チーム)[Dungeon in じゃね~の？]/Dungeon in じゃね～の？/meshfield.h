//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshField.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "scene.h"

#define MESH_X (35)		//x
#define MESH_Z (60)		//z
#define NUM_POLYGON ((MESH_X * MESH_Z)+(MESH_X * MESH_Z))
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshField : public CScene
{
public:
	//�����o�֐�
	CMeshField(int nPriority = 1, OBJTYPE objtype = OBJTYPE_MESHFIELD);
	~CMeshField();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SaveHeight(void);
	void LoadHeight(void);
	float GetHeight(D3DXVECTOR3 pos);
	void SetHeight(D3DXVECTOR3 pos, float fValue, float fRange);
	//�ÓI�����o�֐�
	static CMeshField *Create(D3DXVECTOR3 pos);

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9			m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9		m_pIdxBuff;					//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX					m_mtxWorld;					//���[���h�}�g���b�N�X�i�s��)

	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_vecA,m_vecC;				//�x�N�g��
	D3DXVECTOR3					m_aNor[50000];				//�@��
	D3DXCOLOR					m_col;						//�F
	D3DXVECTOR3					m_rot;						//����
	int							m_nNumVartex;				//���_��
	int							m_nNumIdx;					//�C���f�b�N�X��
	int							m_nNumPolygon;				//�|���S����
	int							m_aVartex;					//���_
	float						m_fAddLength;
	float						m_fLength;
	float						m_fWidth;
	float						m_fHeight;
};
#endif
//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.h]
// Author :
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"

//*****************************************************************************
// ���b�V���t�B�[���h�N���X�̍\����
//*****************************************************************************
class CMeshCylinder : public CScene
{
public:
	CMeshCylinder(int nPriority = 2, OBJTYPE type = OBJTYPE_CYLINDER);
	~CMeshCylinder();
	static CMeshCylinder *Create(D3DXVECTOR3 pos);//�G�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;			//�ʒu(���S���W)
	D3DXVECTOR3 m_rot;			//����
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXCOLOR m_col;			//�F���
	D3DXVECTOR2 m_TexPos;		//�e�N�X�`�����W
	int m_nMesh_H;				//�����̕���
	int m_nMesh_V;				//�����̕���
	int m_nVertexNum;			//���_��
	int m_nIndexNum;			//�C���f�b�N�X��
	int m_nPolygonNum;			//�|���S����
	static int m_nSquareNum;	//�l�p�ʂ̐�
	static int m_nVecNum;		//�͂��x�N�g���̐�
	float m_fMeshWidth;			//���b�V���t�B�[���h�̕�
	float m_fMeshDepth;			//���b�V���t�B�[���h�̉��s��
};

#endif

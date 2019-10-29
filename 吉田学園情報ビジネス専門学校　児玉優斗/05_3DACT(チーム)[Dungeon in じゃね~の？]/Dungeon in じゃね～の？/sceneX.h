//=============================================================================
//
// X�t�@�C������[3D �|���S��] [sceneX.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �V�[��3D�̃N���X�\����
//*****************************************************************************
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 4, OBJTYPE type = OBJTYPE_SCENEX);	//�R���X�g���N�^
	~CSceneX();	//�f�X�g���N�^
	static CSceneX *Create(D3DXVECTOR3 pos);//�G�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	void BindFileName(char *cFileName);
	void BindBuff(LPD3DXBUFFER Buff);//�o�b�t�@��񊄂蓖��
	void BindMesh(LPD3DXMESH Mesh);//���b�V�����̊��蓖��
	void BindNumMat(DWORD NumMat);//�}�e���A���̏��̐��̊��蓖��
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetVtxMax(void);
	D3DXVECTOR3 GetVtxMin(void);
	void BindTexture(LPDIRECT3DTEXTURE9 tex);//�e�N�X�`���̊��蓖��

private:
	char *m_pAddressModel;	//���f���̖��O

	 PDIRECT3DTEXTURE9	m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH m_pMesh;					//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuff;				//�}�e���A�����ւ̃|�C���^
	DWORD m_nNumMat;					//�}�e���A���̏��̐�
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//����
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_VtxMax;				//���f���̍ő咸�_���W
	D3DXVECTOR3 m_VtxMin;				//���f���̍ŏ����_���W


};

#endif
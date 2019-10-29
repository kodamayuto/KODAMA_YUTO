//=============================================================================
//
// X�t�@�C������[3D �|���S��] [sceneX.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PARTS (29)
#define MAX_TEXTURE (2)
//*****************************************************************************
// �V�[��3D�̃N���X�\����
//*****************************************************************************
class CModel
{
public:
	typedef enum
	{
		MODELTYPE_PLAYER = 0,	//�v���C���[
		MODELTYPE_ENEMY,		//�G
		MODELTYPE_MAX			//���f���̎�ނ̍ő吔
	}MODELTYPE;
	CModel();	//�R���X�g���N�^
	~CModel();	//�f�X�g���N�^
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumParts, MODELTYPE type);//�G�̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	void SetPos(D3DXVECTOR3 pos);	//�ʒu���̑��
	void SetRot(D3DXVECTOR3 rot);	//�p�x���̑��
	void SetMtx(D3DXMATRIX mtx);	//�p�x���̑��
	D3DXMATRIX GetMatrix(void);//�}�g���b�N�X�̂����Ƃ�
	void Load(void);//�g�p����p�[�c�̓ǂݍ���
	void Unload(void);//�g�p����p�[�c�̔j��
	void SetParent(CModel *pModel);//�e�q�֌W�̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 tex);//�e�N�X�`���̊��蓖��

private:
	static char						 m_acFileName[MAX_PARTS][256];		// �ǂݍ���
	//static LPDIRECT3DTEXTURE9		 *m_apTexture[MAX_TEXTURE];		// �e�N�X�`���ւ̃|�C���^
	 LPDIRECT3DTEXTURE9				 m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH				 m_apMesh[MAX_PARTS];			//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER				 m_apBuffMat[MAX_PARTS];		//�}�e���A�����ւ̃|�C���^
	static DWORD					 m_aNumMat[MAX_PARTS];			//�}�e���A���̏��̐�
	CModel							*m_pParent;						//�e���f���̃|�C���^
	int m_nNumParts;
	int m_nMaxParts;
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	MODELTYPE m_type;	//���f���̎��
};

#endif
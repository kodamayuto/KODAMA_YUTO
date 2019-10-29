//=============================================================================
//
// ���U���g����[2D �|���S��] [result.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
class CUiResult;
class CResult
{
public:
	CResult();	//�R���X�g���N�^
	~CResult();	//�f�X�g���N�^
	//static CResult *Create();	//���U���g�̐���
	static HRESULT Init(void);	//����������
	static void Uninit(void);	//�I������
	static void Update(void);	//�X�V����
	static void Draw(void);	//�`�揈��
private:

	static CUiResult *m_pUiResult;
	static CObject *m_pObject;				//�I�u�W�F�N�g
	static CMeshField *m_pMeshField;		//���b�V���t�B�[���h

};

#endif
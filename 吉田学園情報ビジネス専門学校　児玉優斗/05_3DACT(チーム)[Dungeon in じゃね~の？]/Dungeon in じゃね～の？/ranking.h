//=============================================================================
//
// �����L���O����[2D �|���S��] [ranking.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

class CUiRanking;
#include "main.h"

class CRanking
{
public:
	CRanking();	//�R���X�g���N�^
	~CRanking();	//�f�X�g���N�^
				//static CRanking *Create();	//���U���g�̐���
	static HRESULT Init(void);	//����������
	static void Uninit(void);	//�I������
	static void Update(void);	//�X�V����
	static void Draw(void);	//�`�揈��
private:
	static int m_nCntFlame;

	static CUiRanking *m_pUiRanking;
	static CObject *m_pObject;				//�I�u�W�F�N�g
	static CMeshField *m_pMeshField;		//���b�V���t�B�[���h
	static int m_nJumpTitleFrame;			//�^�C�g����ʂ֑J�ڂ���Ƃ��̃t���[���J�E���^

};

#endif
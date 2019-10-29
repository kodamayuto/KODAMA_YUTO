//=============================================================================
//
// �Q�[������[2D �|���S��] [game.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
class CModel;
class CMeshCylinder;
class CItemCounter;
class CUi;
class CNumber;
class CTimer;
//*****************************************************************************
// �Q�[���̃N���X�\����
//*****************************************************************************
class CGame
{
public:
	CGame();										//�R���X�g���N�^
	~CGame();										//�f�X�g���N�^
	 HRESULT Init(void);							//����������
	 void Uninit(void);								//�I������
	 void Update(void);								//�X�V����
	 void Draw(void);								//�`�揈��
	 static CMeshField *GetSceneMeshField(void);	//���b�V���t�B�[���h�V�[���̎擾
	 static CPlayer *GetPlayer(void);				//�v���C���[�̎擾
	 static CEnemy *GetEnemy(int nIndex);			//�G�̎擾


private:
	static CGame *m_pGame;					//�Q�[��
	static CMeshField *m_pMeshField;		//���b�V���t�B�[���h
	static CMeshCylinder *m_pMeshCylinder;	//�V�����_�[
	static CPlayer *m_pPlayer;				//�v���C���[
	static CEnemy *m_pEnemy[15];			//�G
	static CModel *m_pModel;				//���f��
	static CObject *m_pObject;				//�I�u�W�F�N�g
	static CItemCounter *m_pItemCounter;	//�A�C�e���J�E���^
	static CUi *m_pUi;	//�A�C�e���J�E���^
	static CNumber *m_pNumber;//����
	static CTimer *m_pTimer;//����
	static CCamera *m_pCamera;					//�J����
	static CLight *m_pLight;					//���C�g

};

#endif
//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene.h"

//===================================================================
//	�ÓI�����o�ϐ��錾
//===================================================================
CScene* CScene::m_apScene[NUM_PRIORITY][MAX_SCENE] = {};
int     CScene::m_nNumAll = 0;

//===================================================================
//	�R���X�g���N�^
//===================================================================
CScene::CScene(int nPriority)
{
		for (int nCnt = 0; nCnt < MAX_SCENE; nCnt++)
		{
			if (m_apScene[nPriority][nCnt] == NULL)
			{
				m_apScene[nPriority][nCnt] = this;
				m_nID = nCnt;			//�����̔ԍ���ݒ�
				m_nPriority = nPriority;
				m_nNumAll++;
				break;
			}
		}
	m_nCount = 0;
	m_objType = OBJTYPE_NONE;
}

void CScene::SetObjType(OBJTYPE type)
{
	m_objType = type;
}
CScene::OBJTYPE	CScene::GetObjType(void)
{
	return m_objType;
}
CScene* CScene::GetScene(int nPriority, int nIdx)
{
	return m_apScene[nPriority][nIdx];
}

//===================================================================
//	�ʃ��������
//===================================================================
void CScene::Release(void)
{
	int nID = m_nID;	//ID����������ϐ��Ɋi�[(delete�ŏ����Ă��܂�����)
	int nPriority = m_nPriority;

		if (m_apScene[nPriority][nID] != NULL)
		{//NULL�`�F�b�N

		 //�w�肳�ꂽID�̕������������
			delete m_apScene[nPriority][nID];
			m_apScene[nPriority][nID] = NULL;

			//��������
			m_nNumAll--;
		}

}

//===================================================================
//	�ꊇ���������
//===================================================================
void CScene::ReleaseAll(void)
{

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCnt = 0; nCnt < MAX_SCENE; nCnt++)
		{
			if (m_apScene[nCntPri][nCnt] != NULL)
			{
				if (m_apScene[nCntPri][nCnt]->m_objType != OBJTYPE_FADE)
				{
					m_apScene[nCntPri][nCnt]->Uninit();

					delete m_apScene[nCntPri][nCnt];
					m_apScene[nCntPri][nCnt] = NULL;
				}
			}
		}

	}
}

//===================================================================
//	�^�C�v���Ƃ̃��������
//===================================================================
void CScene::ReleaseAll(OBJTYPE type)
{

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCnt = 0; nCnt < MAX_SCENE; nCnt++)
		{
			if (m_apScene[nCntPri][nCnt] != NULL)
			{
				if (m_apScene[nCntPri][nCnt]->m_objType == type)
				{
					m_apScene[nCntPri][nCnt]->Uninit();

					delete m_apScene[nCntPri][nCnt];
					m_apScene[nCntPri][nCnt] = NULL;
				}
			}
		}

	}
}

//===================================================================
//	�ꊇ�X�V
//===================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCnt = 0; nCnt < MAX_SCENE; nCnt++)
		{
			if (m_apScene[nCntPri][nCnt] != NULL)
			{
				m_apScene[nCntPri][nCnt]->Update();
			}
		}

	}
}
//===================================================================
//	�ꊇ�`��
//===================================================================
void CScene::DrawAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCnt = 0; nCnt < MAX_SCENE; nCnt++)
		{
			if (m_apScene[nCntPri][nCnt] != NULL)
			{
				m_apScene[nCntPri][nCnt]->Draw();
			}
		}
	}

}
int CScene::GetNumAll(void)
{
	return m_nNumAll;
}

//���ۃN���X�����Ă�̂ł���ȍ~�͏����Ȃ�
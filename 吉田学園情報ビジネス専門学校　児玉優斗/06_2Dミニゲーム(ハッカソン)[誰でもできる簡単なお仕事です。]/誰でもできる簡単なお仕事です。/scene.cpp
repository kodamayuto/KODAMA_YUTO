//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene.h"
#include "DebugProc.h"

//===================================================================
//	�ÓI�����o�ϐ��錾
//===================================================================
int     CScene::m_nNumAll[PRIORITY_MAX] = {};
CScene* CScene::m_apTop[PRIORITY_MAX] = {};
CScene* CScene::m_apCur[PRIORITY_MAX] = {};

//===================================================================
//	�R���X�g���N�^
//===================================================================
CScene::CScene(PRIORITY pri, OBJTYPE type)
{
	CScene* pScene = this;

	pScene->AddList(pri);

	m_Priority = pri;
	m_objType = type;
	m_bDeath = false;
}

//===================================================================
//	���S�t���O����
//===================================================================
void CScene::Release(void)
{
	m_bDeath = true; //���S�t���O
}

//===================================================================
//	�ꊇ���������
//===================================================================
void CScene::ReleaseAll(bool bFadeRelease)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene* pScene = m_apTop[nCntPri];
		if (pScene != NULL)
		{
			do
			{
				CScene* pSceneNext = pScene->m_pNext;
				if (bFadeRelease == false)
				{//�t�F�[�h�͏����Ȃ��Ȃ�
					if (pScene->GetObjType() != OBJTYPE_FADE)
					{//�I�u�W�F�N�g���t�F�[�h�|���S���łȂ����
						pScene->Uninit();
					}
				}
				else
				{
					pScene->Uninit();
				}
					pScene = pSceneNext;
			} while (pScene != NULL);
		}

		if (m_nNumAll[nCntPri] <= 0)
		{
			m_apTop[nCntPri] = NULL;
			m_apCur[nCntPri] = NULL;
		}

		DeadCheck((PRIORITY)nCntPri);

		m_nNumAll[nCntPri] = 0;
	}

}

//===================================================================
//	�ꊇ�X�V
//===================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene* pScene = m_apTop[nCntPri];
		if (pScene != NULL)
		{
			do
			{
				CScene* pSceneNext = pScene->m_pNext;		//��������ޔ�������
				pScene->Update();
				pScene = pSceneNext;
			} while (pScene != NULL); //(pScene)�� ����Ɠ���������
		}

		DeadCheck((PRIORITY)nCntPri);
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		DeadCheck((PRIORITY)nCntPri);
	}


}

//===================================================================
//	�ꊇ�`��
//===================================================================
void CScene::DrawAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene* pScene = m_apTop[nCntPri];
		if (pScene != NULL)
		{
			do
			{
				CScene* pSceneNext = pScene->m_pNext;
				pScene->Draw();
				pScene = pSceneNext;
			} while (pScene != NULL);
		}
	}

#ifdef _DEBUG
	//�f�o�b�O
	int  nSum = 0;
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CDebugProc::Print("OBJECT_%d:%d\n",nCntPri, m_nNumAll[nCntPri]);
		nSum += m_nNumAll[nCntPri];
	}
	CDebugProc::Print("OBJECT_SUM:%d\n",nSum);
#endif

}

//===================================================================
//	���X�g�ɒǉ�
//===================================================================
void CScene::AddList(CScene::PRIORITY pri)
{
	//��[�Ɩ��[�����߂�
	if (m_apTop[pri] == NULL)
	{//1�ڂ̏ꍇ
		m_apTop[pri] = this;
		m_apCur[pri] = this;
	}
	else
	{//����ȍ~�̏ꍇ
		CScene* pScene = m_apCur[pri];		//��������ޔ�

		m_apCur[pri] = this;
		m_apCur[pri]->m_pPrev = pScene;
		m_apCur[pri]->m_pNext = NULL;
		pScene->m_pNext = m_apCur[pri];
	}

	//m_nID = m_nNumAll[pri];
	m_nNumAll[pri]++;
}

//===================================================================
//	���X�g����폜
//===================================================================
void CScene::DeleteList(CScene::PRIORITY pri)
{
	//�ޔ�
	CScene* pScene = this;
	CScene* pScenePrev = pScene->m_pPrev;
	CScene* pSceneNext = pScene->m_pNext;

	if (pScene == m_apTop[pri])
	{//���̃I�u�W�F�N�g����[�Ȃ�
		m_apTop[pri] = pSceneNext;
		if (m_apTop[pri] != NULL)
		{
			m_apTop[pri]->m_pPrev = NULL;
		}
	}
	else if (pScene == m_apCur[pri])
	{//���̃I�u�W�F�N�g�����[�Ȃ�
		m_apCur[pri] = pScenePrev;
		if (m_apTop[pri] != NULL)
		{
			m_apCur[pri]->m_pNext = NULL;
		}
	}
	else
	{//����ȊO�Ȃ�
		pScenePrev->m_pNext = pSceneNext;
		pSceneNext->m_pPrev = pScenePrev;
	}

	m_nNumAll[pri]--;
}

//===================================================================
//	���S�`�F�b�N(���S�t���O�������Ă�����̂���������)
//===================================================================
void CScene::DeadCheck(CScene::PRIORITY pri)
{
	CScene* pScene = m_apTop[pri];
	if (pScene != NULL)
	{
		do
		{
			CScene* pSceneNext = pScene->m_pNext;		//��������ޔ�������
			if (pScene->m_bDeath == true)
			{
				pScene->DeleteList(pri);
				//�폜
				delete pScene;
				pScene = NULL;
			}
			pScene = pSceneNext;
		} while (pScene != NULL); //(pScene)�� ����Ɠ���������
	}
}

//===================================================================
//	�D�揇��(���C���[)�̕ύX
//===================================================================
void CScene::SetPriority(PRIORITY pri)
{
	CScene* pScene = this;	//�������񓦂���
	PRIORITY priority = pScene->GetPriority();

	pScene->DeleteList(priority);	//���݂̃��X�g�������

	pScene->m_Priority = pri;					//�D�揇�ʕύX

	pScene->AddList(pri);						//�V�������X�g�ɒǉ�


}
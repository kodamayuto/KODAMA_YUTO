//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene.h"

//===================================================================
//	静的メンバ変数宣言
//===================================================================
CScene* CScene::m_apScene[NUM_PRIORITY][MAX_SCENE] = {};
int     CScene::m_nNumAll = 0;

//===================================================================
//	コンストラクタ
//===================================================================
CScene::CScene(int nPriority)
{
		for (int nCnt = 0; nCnt < MAX_SCENE; nCnt++)
		{
			if (m_apScene[nPriority][nCnt] == NULL)
			{
				m_apScene[nPriority][nCnt] = this;
				m_nID = nCnt;			//自分の番号を設定
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
//	個別メモリ解放
//===================================================================
void CScene::Release(void)
{
	int nID = m_nID;	//IDをいったん変数に格納(deleteで消えてしまうため)
	int nPriority = m_nPriority;

		if (m_apScene[nPriority][nID] != NULL)
		{//NULLチェック

		 //指定されたIDの部分を解放する
			delete m_apScene[nPriority][nID];
			m_apScene[nPriority][nID] = NULL;

			//総数調整
			m_nNumAll--;
		}

}

//===================================================================
//	一括メモリ解放
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
//	タイプごとのメモリ解放
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
//	一括更新
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
//	一括描画
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

//抽象クラス化してるのでこれ以降は書かない
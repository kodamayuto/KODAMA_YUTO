//=============================================================================
//
// �����L���O��ʊǗ��N���X���� [ranking.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"
#include "Manager.h"

class CSound;
class CScore;
class CScene2D;

//===================================================================
//	�}�N����`
//===================================================================
#define MAX_RANKING (5)
#define MAX_RANKING_TEX (5)

//===================================================================
//	�N���X�̒�`
//===================================================================
class CRanking
{
public:
	CRanking();
	~CRanking();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static void SetRankScore(int nScore);
private:
	static int m_aRankingScore[MAX_RANKING];

	static CScore* m_pRanking[MAX_RANKING];

	//	---<<�ǉ�>>---
	static CSound *m_pSound;
	CScene2D * m_pScene2D[MAX_RANKING_TEX];
	int m_nCnt;				//	�^�C���J�E���g��i�߂�
	//	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��	��


};
#endif // !_RANKING_H_

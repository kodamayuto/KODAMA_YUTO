//=============================================================================
//
// �X�R�A���� [Score.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "scene.h"

class CNumber;

//==================================================================
// �}�N����`
//==================================================================
#define MAX_DIGIT	   (8)			//�X�R�A�̍ő包��
#define SCORECOUNT_MAX (99999999)	//�X�R�A�̍ő�l

//==================================================================
// �N���X�̒�`
//==================================================================
class CScore : public CScene
{
public:
	CScore();
	CScore(CScene::PRIORITY);
	~CScore();

	void Set(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect,
		int nScore = 00000000,D3DXCOLOR col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),int nScoreDigit = 8);//nScoreDigit = �X�R�A�̌���(1�`8)

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3& GetPosition(void) { return m_Pos; };
	D3DXCOLOR& GetColor(void) { return m_Color; };
	D3DXVECTOR2& GetRect(void) { return m_PolygonRect; };
	int GetScore(void) { return m_nScore; };
	void SetScore(int nScore);
	void AddScore(int nValue);
private:
	int m_nScore;			//�X�R�A

	D3DXVECTOR3 m_Pos;				//�ʒu(��ԉE�ɒu����鐔���̍��W)
	D3DXCOLOR m_Color;				//�F
	D3DXVECTOR2 m_PolygonRect;		//�����̃T�C�Y

	std::vector<CNumber*> m_vecNumber;//�����N���X�̃|�C���^�������I�z��
};
#endif// !_SCORE_H_

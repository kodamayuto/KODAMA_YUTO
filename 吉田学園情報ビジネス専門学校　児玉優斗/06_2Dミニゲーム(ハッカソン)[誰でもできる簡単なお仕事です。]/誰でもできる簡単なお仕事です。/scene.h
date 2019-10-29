//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//===================================================================
//	�}�N����`
//===================================================================
#define NUM_PRIORITY (8)	//���C���[��

//===================================================================
//	�N���X�̒�`
//===================================================================
class CScene
{
public:
	//�I�u�W�F�N�g�̎�ޗ�
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_2D,
		OBJTYPE_3D,
		OBJTYPE_XFILE,
		OBJTYPE_BILLBOARD,
		OBJTYPE_FADE,
		OBJTYPE_BAGGAGE,
		OBJTYPE_MAX
	}OBJTYPE;

	typedef enum
	{
		PRIORITY_1,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4,
		PRIORITY_5,
		PRIORITY_6,
		PRIORITY_7,
		PRIORITY_8,
		PRIORITY_MAX
	}PRIORITY;	//���C���[�ԍ�(���������������ɏ��������)

	CScene() {};
	CScene(PRIORITY pri = PRIORITY_3,OBJTYPE type = OBJTYPE_NONE);

	virtual ~CScene() {}

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(bool bFadeRelease);			//�ꊇ�I��

	static void UpdateAll(void);			//�ꊇ�X�V
	static void DrawAll(void);				//�ꊇ�`��
	static void DeadCheck(PRIORITY pri);	//���S�t���O�`�F�b�N

	void AddList(PRIORITY pri);				//���X�g�ɒǉ�
	void DeleteList(PRIORITY pri);			//���X�g����폜

	static CScene* GetTop(PRIORITY pri) { return m_apTop[pri]; };
	CScene* GetNext(void) { return m_pNext; };

	void	 SetPriority(PRIORITY pri);
	PRIORITY GetPriority(void) { return m_Priority; };

	void		SetObjType(OBJTYPE type) { m_objType = type; };
	OBJTYPE		GetObjType(void) { return m_objType; };

private:
	static CScene* m_apTop[PRIORITY_MAX];
	static CScene* m_apCur[PRIORITY_MAX];
	CScene* m_pPrev;
	CScene* m_pNext;

	bool m_bDeath;
protected:
	void Release(void);						//�폜

	static int	   m_nNumAll[PRIORITY_MAX];	//�I�u�W�F�N�g��(�D�揇�ʕ�)
	int			m_nCount = 0;				//�J�E���^
	PRIORITY	   m_Priority;				//�D�揇��(���C���[�ԍ�)
	OBJTYPE m_objType;						//�I�u�W�F�N�g�̎��
};

//==================================================================================================//
//     �e���v���[�g(Scene�n�̃I�u�W�F�N�g�̐���)
//==================================================================================================//
template<class T> T* SceneCreate(T *&pScene, CScene::PRIORITY Priority)
{
	pScene = NULL;
	pScene = new T(Priority);
	if (pScene != NULL) { pScene->Init(); return pScene; }

	return NULL;
}


#endif // !_SCENE_H_


//=============================================================================
//
// �I�u�W�F�N�g�̔z�u����[3D �|���S��] [object.h]
// Author :�ݓc��(KishidaRei)
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "sceneX.h"
//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAXMODEL_TYPE		(20)						//���f���̎�ނ̍ő吔
#define MAX_TEXTURE_OBJ		(9)
//*****************************************************************************
// ���f���N���X�̍\����
//*****************************************************************************
class CObject : public CSceneX
{
public:
	typedef enum
	{
		OBJECTTYPE_COIN = 0,	//�R�C��
		OBJECTTYPE_KEY,			//�J�M
		OBJECTTYPE_WOOD,		//��
		OBJECTTYPE_SKY,			//��
		OBJECTTYPE_CLOUD,		//�_
		OBJECTTYPE_SCAFFOLD,	//����
		OBJECTTYPE_DUNGEON,		//�_���W����
		OBJECTTYPE_GOAL,		//�S�[��
		OBJECTTYPE_SCAFFOLD_S,	//����
		OBJECTTYPE_MAX
	}OBJECTTYPE;
	CObject(int nPriority = 4, OBJTYPE type = OBJTYPE_OBJECT);
	~CObject();
	static HRESULT Load(void);
	static void Unload(void);
	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);//���f���̐���
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	static void LoadModelText(void);// ���f�����ǂݍ���
	bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadius);
	bool CObject::CollisionGoal(D3DXVECTOR3 *pos, D3DXVECTOR3 *move, D3DXVECTOR3 *rot);
private:
	//	�ǂݍ��ރ��f���̃f�[�^
	static char *m_pModelName[MAXMODEL_TYPE];		// ���f���̃A�h���X�i�[�p
	D3DXVECTOR3			m_vtxMin;					// ���f���̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					// ���f���̍ő�l
	float m_fHeight;						//�G�̍���

	// ���f���̊�{���
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE_OBJ]; //���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3			m_pos;						// �ʒu
	D3DXVECTOR3			m_move;						// �ʒu�̈ړ���
	D3DXVECTOR3			m_rot;						// ����
	D3DXVECTOR3			m_rotDest;					// �ړI�̌���
	D3DXMATRIX			m_mtxWorld;					// ���[���h�}�g���b�N�X
	int					m_nIdxShadow;				// �e�̔ԍ�
	int					m_nTypeModel;				// �g�p���郂�f��
	static int			m_nMaxModelNum;				// ���f���̐�
	int					m_nMaxTextureNum;			// �e�N�X�`���̐�
	OBJECTTYPE			m_Objecttype;
};

#endif

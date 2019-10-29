//=============================================================================
//
// �e�N�X�`���N���X [texture.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v:
//	�E�O���t�@�C���ɏ����ꂽ����ێ����A�K�v�Ȏ���
//	�@�ǂݍ��񂾏������Ƀe�N�X�`���𐶐�����
//	�E��x�ǂݍ��񂾂��͕̂ێ����Ă����A�ēx�K�v�ɂȂ�������
//	  ���ɂ���e�N�X�`�������̂܂ܓn��
//	�E�e�N�X�`���͊O���t�@�C���ŕύX�ł���ID�ƃ^�O�ŊǗ�����A
//	�@�g�p�҂�ID�������̓^�O�������ɓ���邱�ƂŕK�v�ȃe�N�X�`�����擾����
//
//	���A�g�p����Ƃ���main.h��<stdio.h>�ƌx�������������邱��!!
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

class CTexture
{
public:
	//�e�N�X�`���f�[�^�̍\����
	struct TexData
	{
		int	 nID;							//ID
		char TexAddress[256];				//�e�N�X�`���̃A�h���X
		char TexNameTag[256];				//�e�N�X�`���̗���
		LPDIRECT3DTEXTURE9 pTexture;		//�e�N�X�`���̃|�C���^
		bool operator == (const int ID)
		{
			return (nID == ID);
		}
		bool operator == (const LPCSTR Tag)
		{
			return (strcmp(TexNameTag, Tag) == 0);
		}
	};

	//�R���X�g���N�^&�f�X�g���N�^
	CTexture() {};
	~CTexture() {};

	//�ǂݍ���&�폜
	static HRESULT Load(void);
	static void Unload(void);

	//�e�N�X�`���擾
	static LPDIRECT3DTEXTURE9 GetTexture(const int nID);
	static LPDIRECT3DTEXTURE9 GetTexture(const LPCSTR Tag);

	//�g��Ȃ��Ȃ����e�N�X�`���̉��
	static void Release(const int nID);
	static void Release(const LPCSTR Tag);


	//�e�N�X�`�����J�E���g
	static int GetTexNum(bool bCreate);
private:
	static void Create(LPCSTR address, LPDIRECT3DTEXTURE9 &pTexture);

	//�ϐ�
	static std::vector<TexData> m_TexData;	//�e�N�X�`���f�[�^�̔z��
};

#endif // !_TEXTURE_H_

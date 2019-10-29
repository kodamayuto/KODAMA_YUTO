//=============================================================================
//
// CCommand::�R�}���h���� [Command.cpp]
// Author : Kodama Yuto
//	�N���X�̊T�v:
//	�E����Ȃǂŉ����{�^���𖼑O�ŊǗ��ł���N���X
//	�EResistCommand�֐����g���ăR�}���h��o�^���AGetCommand�֐��Ŏ擾����
//
//=============================================================================
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "main.h"
#include "InputKeyboard.h"
#include "InputXPad.h"

//�R�}���h�N���X
class CCommand
{
public:
	typedef enum
	{
		INPUTTYPE_KEYBOARD,				//�L�[�{�[�h
		INPUTTYPE_CONTROLLER_DIRECT,	//DIRECTINPUT
		INPUTTYPE_CONTROLLER_X,			//XINPUT
		INPUTTYPE_MAX
	}INPUT_TYPE;		//���̓^�C�v

	typedef enum
	{
		INPUTSTATE_PRESS,				//�v���X(�����Ă��)
		INPUTSTATE_TRIGGER,				//�g���K�[(�������u��)
		INPUTSTATE_RELEASE,				//�����[�X(�������u��)
		INPUTSTATE_HOLD,				//�z�[���h(n�t���[���ԃv���X�����㗣���܂�)
		INPUTSTATE_REPEAT,				//���s�[�g(�v���X���Ă����n�t���[�����Ƃ�)
		INPUTSTATE_NOTPRESS,			//�m�b�g�v���X(�����ĂȂ���)
		INPUTSTATE_MAX
	}INPUT_STATE;		//���͂̑���

	typedef enum
	{
		COMMAND_ALL_TRUE,				//�S�ẴR�}���h��������Ă�����
		COMMAND_EACH_TRUE,				//�ǂꂩ�̃R�}���h��������Ă�����
		COMMAND_MAX
	}GET_COMMAND_OPTION;
	typedef struct
	{
		INPUT_TYPE type;		//���̓^�C�v
		INPUT_STATE state;		//���͂̑���
		int nKey;				//�L�[�ԍ�
	}KeyType;			//�L�[�̏��

	struct CommandState
	{
		LPCSTR CommandName;					//�R�}���h�̖��O
		std::vector<KeyType> vec_KeyType;	//�L�[���̔z��
		bool operator ==(const LPCSTR &command)
		{
			return (CommandName == command);
		}
	};	//�R�}���h�̏��

	static void RegistCommand(LPCSTR CommandName, INPUT_TYPE InputType, INPUT_STATE InputState, int nKey);			//�R�}���h���o�^(�쐬)
	static bool GetCommand(LPCSTR CommandName, int nPlayerID = 0, GET_COMMAND_OPTION option = COMMAND_EACH_TRUE);	//�R�}���h�Ăяo��(PlayerID = �R���g���[���̎��ʗp)
	static void ResetCommandAll(void);
	static bool ResetCommand(LPCSTR CommandName);

	//�R���g���[���[�̃X�e�B�b�N�̌X�����擾
	static float GetXPadStickRotation(bool LorR,bool XorY,int nPlayerID);//LorR = true��L�X�e�B�b�N�Afalse��R�X�e�B�b�N�̔��� || XorY = true��X���Afalse��Y���̔���
private:
	static bool CheckKey_Keyboard(CInputKeyboard* pInputK,INPUT_STATE InputState, int nKey);
	static bool CheckKey_XController(CInputXPad* pInputX,INPUT_STATE InputState, int nKey);

	static std::vector<CommandState> m_Command;		//�R�}���h
};

#endif // !_COMMAND_H_

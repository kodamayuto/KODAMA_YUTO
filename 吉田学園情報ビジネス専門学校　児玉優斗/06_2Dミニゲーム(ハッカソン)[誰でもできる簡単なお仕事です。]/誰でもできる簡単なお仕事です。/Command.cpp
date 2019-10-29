//=============================================================================
//
// CCommand::�R�}���h���� [Command.cpp]
// Author : Kodama Yuto
//
//
//	����ɕҏW���Ȃ����ƁI�I(�R�����g��OK)
//
//=============================================================================
#include "Command.h"
#include "Manager.h"

//===================================================================
//	�ÓI�����o�ϐ��錾
//===================================================================
std::vector<CCommand::CommandState> CCommand::m_Command;

//===================================================================
//	�R�}���h�o�^����
//===================================================================
void CCommand::RegistCommand(LPCSTR CommandName, INPUT_TYPE InputType, INPUT_STATE InputState, int nKey)
{
	CommandState One_Command;//�R�}���h���i�[�p
	KeyType One_KeyType;	 //�L�[���i�[�p

	//���X�g���̒T��(�R�}���h������`����Ă��邩�T��)
	auto result = std::find(m_Command.begin(), m_Command.end(), CommandName);

	if (result == m_Command.end())
	{//�R�}���h�������X�g���Ŗ���`�̏ꍇ

	 /*�R�}���h���ݒ�*/
	 //�R�}���h���ݒ�
		One_Command.CommandName = CommandName;

		//�L�[���ݒ�
		One_KeyType.type  = InputType;
		One_KeyType.state = InputState;
		One_KeyType.nKey  = nKey;

		One_Command.vec_KeyType.emplace_back(One_KeyType);

		//�R�}���h�o�^
		m_Command.emplace_back(One_Command);
	}
	else
	{//�R�}���h�������ɒ�`����Ă���ꍇ
	 //�L�[���ݒ�
		One_KeyType.type  = InputType;
		One_KeyType.state = InputState;
		One_KeyType.nKey  = nKey;

		(*result).vec_KeyType.emplace_back(One_KeyType);
	}
}

//===================================================================
//	�R�}���h�Ăяo������
//===================================================================
bool CCommand::GetCommand(LPCSTR CommandName, int nPlayerID, GET_COMMAND_OPTION option)
{
	CInputKeyboard* pInputK = CManager::GetInputKeyboard();	//�L�[�{�[�h�̃|�C���^
	CInputXPad* pInputX = CManager::GetXInput();
	bool bCommand_ETrue = false;		//COMMAND_EACH_TRUE�Ŏg�p����Ԃ�l
	bool bCommand_ATrue = true;			//COMMAND_ALL_TRUE�Ŏg�p����Ԃ�l

	//���X�g���̒T��
	auto result = std::find(m_Command.begin(), m_Command.end(), CommandName);

	if (result != m_Command.end())
	{//�R�}���h������`����Ă�����
		for (auto itr = (*result).vec_KeyType.begin(); itr != (*result).vec_KeyType.end(); itr++)
		{
			//true���ǂ����̔�����s��
			switch ((*itr).type)
			{
			case INPUTTYPE_KEYBOARD:
				bCommand_ETrue = CheckKey_Keyboard(pInputK,(*itr).state, (*itr).nKey);
				break;
			case INPUTTYPE_CONTROLLER_DIRECT:
				break;
			case INPUTTYPE_CONTROLLER_X:
				bCommand_ETrue = CheckKey_XController(pInputX,(*itr).state, (*itr).nKey);
				break;
			}

			if (bCommand_ETrue == true && option == COMMAND_EACH_TRUE)
			{//��ł������Ă���΋����I�ɏ������甲����(COMMAND_EACH_TRUE�̂�)
				return bCommand_ETrue;
			}

			if (bCommand_ETrue == false)
			{//��ł������ĂȂ���΂��̕ϐ���false�ɂ���
				bCommand_ATrue = false;
			}
		}

	}
	else
	{//�R�}���h���o�^����Ă��Ȃ����false��Ԃ�
		return false;
	}

	return bCommand_ATrue;	//�S�Ă����Ă����true��Ԃ�(COMMAND_ALL_TRUE�̂�)
}
//===================================================================
//	�R�}���h�S��������
//===================================================================
void CCommand::ResetCommandAll(void)
{
	for (auto itrCommand = m_Command.begin(); itrCommand != m_Command.end(); itrCommand++)
	{
		(*itrCommand).vec_KeyType.clear();
	}

	//������
	m_Command.clear();
}

//===================================================================
//	�R�}���h��������
//===================================================================
bool CCommand::ResetCommand(LPCSTR CommandName)
{
	auto result = std::find(m_Command.begin(), m_Command.end(), CommandName);
	if (result == m_Command.end())
	{//�R�}���h������`����Ă��Ȃ����
		return false;
	}
	else
	{//��`����Ă����

		//�L�[�̍폜
		(*result).vec_KeyType.clear();
	}
	return true;
}

//===================================================================
//	�L�[�Ăяo������(Keyboard)
//===================================================================
bool  CCommand::CheckKey_Keyboard(CInputKeyboard* pInputK, INPUT_STATE InputState, int nKey)
{
	bool bCommand = false;									//�֐��̕Ԃ�l
	if (pInputK != NULL)
	{
		switch (InputState)
		{
		case INPUTSTATE_PRESS:	//�v���X
			bCommand = pInputK->GetPress(nKey);
			break;
		case INPUTSTATE_TRIGGER://�g���K�[
			bCommand = pInputK->GetTrigger(nKey);
			break;
		case INPUTSTATE_RELEASE://�����[�X
			bCommand = pInputK->GetRelease(nKey);
			break;
		case INPUTSTATE_NOTPRESS://�m�b�g�v���X(�����ĂȂ���)
			bCommand = !(pInputK->GetPress(nKey));
			break;
		case INPUTSTATE_REPEAT://���s�[�g
			bCommand = pInputK->GetRepeat(nKey);
			break;

		}
	}
	return bCommand;
}
bool  CCommand::CheckKey_XController(CInputXPad* pInputX, INPUT_STATE InputState, int nKey)
{
	bool bCommand = false;									//�֐��̕Ԃ�l
	if (nKey >= CInputXPad::XPAD_MAX)
	{
		return false;
	}
	if (pInputX != NULL)
	{
		switch (InputState)
		{
		case INPUTSTATE_PRESS:	//�v���X
			bCommand = pInputX->GetPress((CInputXPad::XPAD_KEY)nKey);
			break;
		case INPUTSTATE_TRIGGER://�g���K�[
			bCommand = pInputX->GetTrigger((CInputXPad::XPAD_KEY)nKey);
			break;
		case INPUTSTATE_RELEASE://�����[�X
			bCommand = pInputX->GetRelease((CInputXPad::XPAD_KEY)nKey);
			break;
		case INPUTSTATE_NOTPRESS://�m�b�g�v���X(�����ĂȂ���)
			bCommand = !(pInputX->GetPress((CInputXPad::XPAD_KEY)nKey));
			break;
		case INPUTSTATE_REPEAT://���s�[�g
			bCommand = pInputX->GetRepeat((CInputXPad::XPAD_KEY)nKey);
			break;
		}
	}

	return bCommand;

}

//===================================================================
//�R���g���[���[�̃X�e�B�b�N�̌X�����擾����
//===================================================================
float CCommand::GetXPadStickRotation(bool LorR, bool XorY, int nPlayerID)
{
	float fResult = 0.0f;
	SHORT sRot = 0;
	CInputXPad* pInputX = CManager::GetXInput();
	if (pInputX != NULL)
	{
		if (LorR == true)
		{//L
			if (XorY == true)
			{//X
				sRot = pInputX->GetLStickRotX();
			}
			else
			{//Y

				sRot = pInputX->GetLStickRotY();
			}
		}
		else
		{//R
			if (XorY == true)
			{//X
				sRot = pInputX->GetRStickRotX();
			}
			else
			{//Y
				sRot = pInputX->GetRStickRotY();
			}
		}
		fResult = ((float)sRot) / 32767.0f;

	}
	return fResult;
}
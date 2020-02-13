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
std::vector<CCommand::CommandState> CCommand::m_Command;		//�R�}���h�̃f�[�^�x�[�X�ϐ�

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
		auto vec = std::find(result->vec_KeyType.begin(),result->vec_KeyType.end(),nKey);
		if (vec == result->vec_KeyType.end())
		{
			//�L�[���ݒ�
			One_KeyType.type = InputType;
			One_KeyType.state = InputState;
			One_KeyType.nKey = nKey;

			(*result).vec_KeyType.emplace_back(One_KeyType);
		}
	}
}

//===================================================================
//	�R�}���h�Ăяo������
//===================================================================
bool CCommand::GetCommand(LPCSTR CommandName, int nPlayerID, GET_COMMAND_OPTION option)
{
	CInputKeyboard* pInputK = CManager::GetInputKeyboard();	//�L�[�{�[�h�̃|�C���^
	CInputXPad* pInputX = CManager::GetXInput(nPlayerID);

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
			case INPUTTYPE_KEYBOARD:	//�L�[�{�[�h
				bCommand_ETrue = CheckKey_Keyboard(pInputK,(*itr).state, (*itr).nKey);
				break;
			case INPUTTYPE_PAD_X://XPad
				bCommand_ETrue = CheckKey_XPad(pInputX,(*itr).state, (*itr).nKey);
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
	{//���Ԃɏ���
		(*itrCommand).vec_KeyType.clear();
	}

	//������&���������k
	m_Command.clear();
	m_Command.shrink_to_fit();
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

	//�L�[�̐����ɑ傫�����鐔���������Ă����ꍇ�͏������甲����
	if (nKey >= DIK_SLEEP)
	{
		return false;
	}

	if (pInputK != NULL)
	{//�L�[�{�[�h�N���X����������Ă�����
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
			bCommand = !(pInputK->GetPress(nKey));	//�v���X�̋t���Ƃ�
			break;
		case INPUTSTATE_REPEAT://���s�[�g
			bCommand = pInputK->GetRepeat(nKey);
			break;
		case INPUTSTATE_HOLD://�z�[���h
			bCommand = pInputK->GetHold(nKey);
			break;

		}
	}
	return bCommand;
}

//===================================================================
//	�L�[�Ăяo������(XPad)
//===================================================================
bool  CCommand::CheckKey_XPad(CInputXPad* pInputX, INPUT_STATE InputState, int nKey)
{
	bool bCommand = false;									//�֐��̕Ԃ�l

	//�L�[�̐����ɑ傫�����鐔���������Ă����ꍇ�͏������甲����
	if (nKey >= CInputXPad::XPAD_MAX)
	{
		return false;
	}

	if (pInputX != NULL)
	{//XPad�N���X����������Ă�����
		if (pInputX->GetConnect() == true)
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
			case INPUTSTATE_HOLD://�z�[���h
				bCommand = pInputX->GetHold((CInputXPad::XPAD_KEY)nKey);
				break;
			}
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
	CInputXPad* pInputX = CManager::GetXInput(nPlayerID);
	if (pInputX != NULL)
	{
		//�ϐ��Ŏw�肵���p�x���擾
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

		//�擾�����p�x��-1.0f����+1.0f�̊Ԃɕ␳
		fResult = CUtilityMath::Mapping(((float)sRot), -32767.0f,32767.0f,-1.0f,1.0f);
	}
	return fResult;
}
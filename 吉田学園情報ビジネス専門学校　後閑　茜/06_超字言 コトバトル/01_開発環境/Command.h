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
		INPUTTYPE_PAD_X,			//XINPUT
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
		bool operator ==(const int& nKEY)
		{
			return (nKey == nKEY);
		}
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

	//�ÓI�����o�֐�
	static void RegistCommand(LPCSTR CommandName, INPUT_TYPE InputType, INPUT_STATE InputState, int nKey);			//�R�}���h���o�^(�쐬)
	static bool GetCommand(LPCSTR CommandName, int nPlayerID = 0, GET_COMMAND_OPTION option = COMMAND_EACH_TRUE);	//�R�}���h�Ăяo��(PlayerID = �R���g���[���̎��ʗp)
	static void ResetCommandAll(void);														//�S�ẴR�}���h��񃊃Z�b�g
	static bool ResetCommand(LPCSTR CommandName);											//�R�}���h���Ƃ̏�񃊃Z�b�g

	//�R���g���[���[�̃X�e�B�b�N�̌X����(-1.0f�`1.0f)�擾
	static float GetXPadStickRotation(bool LorR,bool XorY,int nPlayerID);//LorR = true��L�X�e�B�b�N�Afalse��R�X�e�B�b�N�̔��� || XorY = true��X���Afalse��Y���̔���
private:
	//���͂̎�ނ��Ƃ̃`�F�b�N�֐�
	static bool CheckKey_Keyboard(CInputKeyboard* pInputK,INPUT_STATE InputState, int nKey);	//�L�[�{�[�h
	static bool CheckKey_XPad(CInputXPad* pInputX,INPUT_STATE InputState, int nKey);		//XPad

	static std::vector<CommandState> m_Command;		//�R�}���h
};

#endif // !_COMMAND_H_

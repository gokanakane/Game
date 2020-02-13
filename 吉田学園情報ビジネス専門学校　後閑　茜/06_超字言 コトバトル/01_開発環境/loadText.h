//=============================================================================
//
// Text�ǂݍ��ݏ��� [loadText.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _LOADTEXT_H_
#define _LOADTEXT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CLoadText
{
public:
	CLoadText();	// �R���X�g���N�^
	~CLoadText();	// �f�X�g���N�^

	static void LoadFile(void);
	static char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	static char *GetLineTop(char *pStr);			//�s�̐擪���擾
	static int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�

private:
};

#endif
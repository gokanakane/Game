//=============================================================================
//
// �w�i���� [PauseQuit.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSEQUIT_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PAUSEQUIT_

#include "main.h"

typedef enum
{
	QUITSTATE_SELECT = 0,
	QUITSTATE_NOSELECT,
	QUITSTATE_MAX

} QUITSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseQuit(void);
void UninitPauseQuit(void);
void UpdatePauseQuit(void);
void DrawPauseQuit(void);

void SetQuit(QUITSTATE state);

#endif
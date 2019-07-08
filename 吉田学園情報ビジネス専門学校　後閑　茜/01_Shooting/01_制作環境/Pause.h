//=============================================================================
//
// �|�[�Y���� [Pause.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _PAUSE_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PAUSE_H_

#include "main.h"

typedef enum
{
	PAUSESTATE_NONE = 0,
	PAUSESTATE_CONTINUE,
	PAUSESTATE_RETRY,
	PAUSESTATE_QUIT,
	PAUSESTATE_MAX

} PAUSESTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif

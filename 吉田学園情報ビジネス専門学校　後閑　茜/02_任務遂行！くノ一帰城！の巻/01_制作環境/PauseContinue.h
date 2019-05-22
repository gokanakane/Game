//=============================================================================
//
// �w�i���� [PauseContinue.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSECONRINUE_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PAUSECONRINUE_

#include "main.h"

typedef enum
{
	CONTINUSTATE_SELECT = 0,
	CONTINUSTATE_NOSELECT,
	CONTINUSTATE_MAX

} CONTINUSTATE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseContinue(void);
void UninitPauseContinue(void);
void UpdatePauseContinue(void);
void DrawPauseContinue(void);

void SetContinu(CONTINUSTATE state);

#endif

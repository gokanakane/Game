//=============================================================================
//
// �w�i���� [PauseRetry.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSERETRY_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PAUSERETRY_

#include "main.h"

typedef enum
{
	RETRYSTATE_SELECT = 0,
	RETRYSTATE_NOSELECT,
	RETRYSTATE_MAX

} RETRYSTATE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseRetry(void);
void UninitPauseRetry(void);
void UpdatePauseRetry(void);
void DrawPauseRetry(void);

void SetRetry(RETRYSTATE state);
#endif

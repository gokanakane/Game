//=============================================================================
//
// �w�i���� [Select_Yes.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TITLE_SELECTH_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TITLE_SELECT

#include "main.h"
#include "Game.h"

typedef enum
{
	COLSTATE_GAMESTATE = 0,
	COLSTATE_TUTORIAL,
	COLSTATE_MAX

}Colstate;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTitleSelect(void);
void UninitTitleSelect(void);
void UpdateTitleSelect(void);
void DrawTitleSelect(void);

#endif

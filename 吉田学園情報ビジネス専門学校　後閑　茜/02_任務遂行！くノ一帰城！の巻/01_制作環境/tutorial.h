//=============================================================================
//
// �w�i���� [TUTORIAL.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TUTORIAL_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TUTORIAL_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIAL_POS_X (0)					   //�w�i����X
#define TUTORIAL_POS_Y (0)					   //�w�i����Y
#define TUTORIAL_WIDTH (SCREEN_WIDTH)			   //�w�i�̕�
#define TUTORIAL_HEIGHT (SCREEN_HEIGHT)		   //�w�i����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
#endif

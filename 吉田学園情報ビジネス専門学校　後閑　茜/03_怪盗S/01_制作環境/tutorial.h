//=============================================================================
//
// �`���[�g���A������ [Tutorial.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _TUTORIAL_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TUTORIAL_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_POS_X (0)												  //�w�i����X
#define BG_POS_Y (0)												 //�w�i����Y
#define TUTOTIAL_TEXTUER0 " "
#define TUTOTIAL_TEXTUER "data\\TEXTURE\\Tutorial\\Tutorial204.png"
#define TUTOTIAL_TEXTUER1 "data\\TEXTURE\\Tutorial\\Tutorial001.png"
#define TUTOTIAL_TEXTUER2 "data\\TEXTURE\\Tutorial\\Tutorial002-5.png"
#define MAX_TUTORIALTEX  (4)												   //�e�N�X�`���̖���
#define MAX_ANIM (4)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
#endif

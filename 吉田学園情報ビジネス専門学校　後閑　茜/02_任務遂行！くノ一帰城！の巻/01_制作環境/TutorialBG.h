//=============================================================================
//
// �w�i���� [TutorialBG.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TUTORIALBG_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TUTORIALBG_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_POS_X (0)					   //�w�i����X
#define BG_POS_Y (300)					   //�w�i����Y
#define MAX_TUTORIALBGTEX  (4)					   //�e�N�X�`���̖���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	TUTORIALSTATE_NONE = 0,
	TUTORIALSTATE_FADEIN,
	TUTORIALSTATE_FADEOUT,
	TUTORIALTATE_MAX

}TutorialState;
typedef struct
{
	D3DXCOLOR col;
	float nChangeArpha;//�����x�ύX

}TutorialCol;


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TUTOTIALTEXTUER  "data\\TEXTURE\\Tutorial\\Tutorial003.png" //�ǂݍ��ރe�N�X�`��
#define BG_TUTOTIALTEXTUER1 "data\\TEXTURE\\Tutorial\\Tutorial001.png" //�ǂݍ��ރe�N�X�`��
#define BG_TUTOTIALTEXTUER2 "data\\TEXTURE\\Tutorial\\Tutorial002.png" //�ǂݍ��ރe�N�X�`��
#define BG_TUTOTIALTEXTUER3 "data\\TEXTURE\\Tutorial\\Tutorial004.png" //�ǂݍ��ރe�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTutorialBG(void);
void UninitTutorialBG(void);
void UpdateTutorialBG(void);
void DrawTutorialBG(void);
#endif

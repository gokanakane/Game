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
#define BG_TEXTUER  "data\\TEXTURE\\Tutorial\\Tutorial003.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTUER1 "data\\TEXTURE\\Tutorial\\Tutorial001.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTUER2 "data\\TEXTURE\\Tutorial\\Tutorial002.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTUER3 "data\\TEXTURE\\Tutorial\\Tutorial004.png" //�ǂݍ��ރe�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTutorialBG(void);
void UninitTutorialBG(void);
void UpdateTutorialBG(void);
void DrawTutorialBG(void);
#endif

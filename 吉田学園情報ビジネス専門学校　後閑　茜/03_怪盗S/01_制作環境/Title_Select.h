//=============================================================================
//
// �w�i���� [Title_Select.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _TITLE_SELECTH_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TITLE_SELECT

#include "main.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLESELECT_TEXTUER  "data\\TEXTURE\\UI\\GAMESTART.png"		//�ǂݍ��ރe�N�X�`��
#define TITLESELECT_TEXTUER1  "data\\TEXTURE\\UI\\Tutorial100.png"	//�ǂݍ��ރe�N�X�`��
#define TITLESELECT_TEXTUER2  "data\\TEXTURE\\UI\\cursor.png"			//�ǂݍ��ރe�N�X�`��

#define MAX_TEX (2)
#define TITLESELECT_POS_X (320)												//�|�[�Y�����iYES�j����X
#define TITLESELECT_POS_Y (300)												//�|�[�Y�����iYES�j����Y
#define TITLESELECT_WIDTH (990)												//�|�[�Y�����iYES�j�̕�
#define TITLESELECT_HEIGHT (500)												//�|�[�Y�����iYES�j����

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

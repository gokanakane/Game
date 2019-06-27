//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : 
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_POLYGON (2)
#define VTX_POS_X (0)
#define VTX_POS_Y (0)
#define LOAD_TEX " "
#define LOAD_TEX1 "data\\TEXTURE\\UI\\Load000.png"
#define LOAD_TEX2 "data\\TEXTURE\\UI\\Load001.png"
#define MAX_FADETEX (3)
#define MAX_ANIM (4)

//*************************************
// �t�F�[�h�̏��
//*************************************
typedef enum
{
	FADE_NONE = 0,		// �������Ă��Ȃ����
	FADE_IN,			// �t�F�[�h�C�����
	FADE_OUT,			// �t�F�[�h�A�E�g���
	FADE_MAX
} FADE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(MODE modeNext);
FADE GetFade(void);

#endif

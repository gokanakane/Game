//=============================================================================
//
// �^�C�g������ [Title.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _TITLE_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _TITLE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTUER "data\\TEXTURE\\BG\\BG01.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTUER1 "data\\TEXTURE\\UI\\press_enter.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTUER2 "data\\TEXTURE\\UI\\Title.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_POS_X (0)					   //�^�C�g������X
#define TITLE_POS_Y (0)					   //�^�C�g������Y
#define TITLE_WIDTH (SCREEN_WIDTH)			   //�^�C�g���̕�
#define TITLE_HEIGHT (SCREEN_HEIGHT)		   //�^�C�g������
#define MAX_TITLETEX (3)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif

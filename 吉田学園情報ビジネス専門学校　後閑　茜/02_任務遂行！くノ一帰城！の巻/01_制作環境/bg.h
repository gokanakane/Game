//=============================================================================
//
// �w�i���� [bg.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _BG_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _BG_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEXTUER  "data\\TEXTURE\\BG\\sky001.jpg" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTUER1 "data\\TEXTURE\\BG\\cloud.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTUER2 "data\\TEXTURE\\BG\\BG000.png" //�ǂݍ��ރe�N�X�`��
#define BG_POS_X (0)					   //�w�i����X
#define BG_POS_Y (300)					   //�w�i����Y
#define BG_WIDTH (SCREEN_WIDTH)			   //�w�i�̕�
#define BG_HEIGHT (SCREEN_HEIGHT)		   //�w�i����
#define MAX_TEX  (3)					   //�e�N�X�`���̖���
#define BG_MOVE (3.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
#endif

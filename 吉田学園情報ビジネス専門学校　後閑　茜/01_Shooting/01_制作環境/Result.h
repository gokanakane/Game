//=============================================================================
//
// ���U���g���� [Result.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _RESULT_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _RESULT_H_

#include "main.h"
#include "Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_TEXTUER "data\\TEXTURE\\BG\\Bg111.jpg" //�ǂݍ��ރe�N�X�`��
#define RESULT_OVER "data\\TEXTURE\\BG\\Bg110.png" //�ǂݍ��ރe�N�X�`��
#define RESULT_TEXTUER1 "data\\TEXTURE\\UI\\gameclear_logo.png" //�ǂݍ��ރe�N�X�`��
#define RESULT_TEXTUER2 "data\\TEXTURE\\UI\\gameover_logo.png" //�ǂݍ��ރe�N�X�`��
#define RESULT_POS_X (0)					   //���U���g����X
#define RESULT_POS_Y (0)					   //���U���g����Y
#define RESULT_WIDTH (SCREEN_WIDTH)			   //���U���g�̕�
#define RESULT_HEIGHT (SCREEN_HEIGHT)		   //���U���g����
#define MAX_RESULTTEX (2)							   //�e�N�X�`���̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif

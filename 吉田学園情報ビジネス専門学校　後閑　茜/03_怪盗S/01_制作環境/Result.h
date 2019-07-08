//=============================================================================
//
// �w�i���� [Result.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _RESULT_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _RESULT_

#include "main.h"
#include "Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_TEXTUER "data\\TEXTURE\\Result\\GameClear001.png"		//�ǂݍ��ރe�N�X�`��
#define RESULT_OVER "data\\TEXTURE\\Object\\Wall008.png"				//�ǂݍ��ރe�N�X�`��
#define RESULT_TEXTUER1 "data\\TEXTURE\\Result\\GameClear000.png"		//�ǂݍ��ރe�N�X�`��
#define RESULT_TEXTUER2 "data\\TEXTURE\\Result\\gameover000.png"		//�ǂݍ��ރe�N�X�`��
#define RESULT_CLIAR "data\\TEXTURE\\BG\\GameClear002.png"				//�ǂݍ��ރe�N�X�`��

#define RESULT_POS_X (0)												//���U���g����X
#define RESULT_POS_Y (0)												//���U���g����Y
#define RESULT_WIDTH (SCREEN_WIDTH)										//���U���g�̕�
#define RESULT_HEIGHT (SCREEN_HEIGHT)									//���U���g����
#define MAX_OVER_TEX (2)												//�e�N�X�`���̍ő吔
#define MAX_CLIAR_TEX (3)												//�Q�[���N���A�̃e�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif

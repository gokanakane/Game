//=============================================================================
//
// �w�i���� [PauseQuit.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PAUSEQUIT_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PAUSEQUIT_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSE_TEXTUER  "data\\TEXTURE\\Quit.png" //�ǂݍ��ރe�N�X�`��
#define PAUSE_POS_X (280 + 150)					    //�|�[�Y�w�i����X
#define PAUSE_POS_Y (280 - 80)					    //�|�[�Y�w�i����Y
#define PAUSE_WIDTH (640 + 150)					    //�|�[�Y�w�i�̕�
#define PAUSE_HEIGHT (640 - 80)					    //�|�[�Y�w�i����

//*****************************************************************************
// �N�C�b�g�̏��
//*****************************************************************************
typedef enum
{
	QUITSTATE_SELECT = 0,
	QUITSTATE_NOSELECT,
	QUITSTATE_MAX

} QUITSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseQuit(void);
void UninitPauseQuit(void);
void UpdatePauseQuit(void);
void DrawPauseQuit(void);

void SetQuit(QUITSTATE state);

#endif
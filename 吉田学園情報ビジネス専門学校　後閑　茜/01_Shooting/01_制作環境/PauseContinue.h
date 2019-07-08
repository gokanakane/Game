//=============================================================================
//
// �R���e�j���[�A�C�R������ [PauseContinue.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _PAUSECONRINUE_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PAUSECONRINUE_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSECONRINUE_TEXTUER  "data\\TEXTURE\\Pause\\pause000.png" //�ǂݍ��ރe�N�X�`��
#define PAUSE_POS_X (280 + 150)					    //�|�[�Y�w�i����X
#define PAUSE_POS_Y (280 - 80)					    //�|�[�Y�w�i����Y
#define PAUSE_WIDTH (640 + 150)					    //�|�[�Y�w�i�̕�
#define PAUSE_HEIGHT (640 - 80)					    //�|�[�Y�w�i����

//*****************************************************************************
// �R���e�j���[�̏��
//*****************************************************************************
typedef enum
{
	CONTINUSTATE_SELECT = 0,
	CONTINUSTATE_NOSELECT,
	CONTINUSTATE_MAX

} CONTINUSTATE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseContinue(void);
void UninitPauseContinue(void);
void UpdatePauseContinue(void);
void DrawPauseContinue(void);

void SetContinu(CONTINUSTATE state);

#endif

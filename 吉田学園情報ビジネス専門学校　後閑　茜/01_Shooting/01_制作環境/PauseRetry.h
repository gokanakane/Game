//=============================================================================
//
// ���g���C�A�C�R������ [PauseRetry.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _PAUSERETRY_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _PAUSERETRY_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSERETRY_TEXTUER  "data\\TEXTURE\\Pause\\pause001.png" //�ǂݍ��ރe�N�X�`��
#define PAUSERETRY_POS_X (280 + 150)					    //�|�[�Y�w�i����X
#define PAUSERETRY_POS_Y (280 - 80)					    //�|�[�Y�w�i����Y
#define PAUSERETRY_WIDTH (640 + 150)					    //�|�[�Y�w�i�̕�
#define PAUSERETRY_HEIGHT (640 - 80)					    //�|�[�Y�w�i����

//*****************************************************************************
// ���g���C�̏��
//*****************************************************************************
typedef enum
{
	RETRYSTATE_SELECT = 0,
	RETRYSTATE_NOSELECT,
	RETRYSTATE_MAX

} RETRYSTATE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseRetry(void);
void UninitPauseRetry(void);
void UpdatePauseRetry(void);
void DrawPauseRetry(void);

void SetRetry(RETRYSTATE state);
#endif

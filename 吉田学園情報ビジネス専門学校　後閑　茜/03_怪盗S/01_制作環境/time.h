//=============================================================================
//
// �^�C������ [Time.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIME "data\\TEXTURE\\UI\\number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TIME2 "data\\TEXTURE\\UI\\Clock000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TIME (3)
#define TIME_RIMIT (60*90)							//��������
#define MAX_TIMETEX (2)									//�e�N�X�`���̍ő吔

//*****************************************************************************
// �\����
//*****************************************************************************
typedef enum
{
	TIMESTATE_NONE=0,
	TIMESTATE_NOMAL,
	TIMESTATE_END,
	TIMESTATE_MAX

}TIMESTATE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void AddTime(void);

void SetTimeState(TIMESTATE state);
int GetTime(void);
#endif

//=============================================================================
//
// �����L���O���� [Ranking.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _RANKING_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_TEXTURE "data\\TEXTURE\\UI\\Ranking000.png" //�����L���O����
#define RANKING_TEXTURE0 "data\\TEXTURE\\BG\\Sky001.jpg"	//�w�i
#define RANKING_TEXTURE2 "data\\TEXTURE\\UI\\Ranking001.png"//����
#define Ranking_POS_X (300)									//�^�C�g������X
#define Ranking_POS_Y (500)									//�^�C�g������Y
#define Ranking_WIDTH (SCREEN_WIDTH)						//�^�C�g���̕�
#define Ranking_HEIGHT (SCREEN_HEIGHT)						//�^�C�g������
#define MAX_TEX (3)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
#endif

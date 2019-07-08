//=============================================================================
//
// �w�i���� [Ranking.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _RANKING_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _RANKING_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_TEXTURE "data\\TEXTURE\\Ranking\\Ranking000.png"	//�����L���O����
#define RANKING_TEXTURE0 "�@"										//�w�i
#define RANKING_TEXTURE1 "data\\TEXTURE\\BG\\Dot.png"				//�h�b�g�i�X�N���[���j
#define RANKING_TEXTURE2 "data\\TEXTURE\\Ranking\\Ranking001.png"	//����
#define RANKING_TEXTURE3 "data\\TEXTURE\\Ranking\\Ranking002.png"	//����
#define RANKING_TEXTURE4 "data\\TEXTURE\\Ranking\\Ranking003.png"	//�y���_���g�i�A�j���[�V�����j
#define Ranking_POS_X (300)											//�^�C�g������X
#define Ranking_POS_Y (500)											//�^�C�g������Y
#define Ranking_WIDTH (SCREEN_WIDTH)								//�^�C�g���̕�
#define Ranking_HEIGHT (SCREEN_HEIGHT)								//�^�C�g������
#define MAX_RANKINGTEX (6)
#define MAX_ANIM (4)												//�A�j���[�V�����p�^�[��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
#endif

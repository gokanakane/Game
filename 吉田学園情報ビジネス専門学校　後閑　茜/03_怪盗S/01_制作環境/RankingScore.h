//=============================================================================
//
// �����L���O�X�R�A���� [RankingScore.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RANKINGSCORE "data\\TEXTURE\\UI\\number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_RANKINGSCORE (8)							    //�X�R�A�̌���
#define MAX_RANKINGSCORE_HEIGTH (5)							//�X�R�A�̒i��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRankingScore(void);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);

void SetHighScore(int nScore);

#endif

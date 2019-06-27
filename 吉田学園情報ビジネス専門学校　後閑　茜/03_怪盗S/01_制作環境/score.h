//=============================================================================
//
// �X�R�A���� [score.h]
// Author : Gokan akane
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data\\TEXTURE\\UI\\number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SCORE1		"data\\TEXTURE\\UI\\Score000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_SCORE (8)
#define MAX_SCORETEX (2)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue);
int GetScore(void);
#endif

//=============================================================================
//
// �A�C�e��UI���� [ItemUI.h]
// Author : Gokan akane
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ITEMUI "data\\TEXTURE\\UI\\Item000.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMUI1 "data\\TEXTURE\\UI\\Item005.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_HEIGTH (6)										//����ςލ���
#define MAX_ITEMUITEX (2)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItemUI(void);
void UninitItemUI(void);
void UpdateItemUI(void);
void DrawItemUI(void);
#endif

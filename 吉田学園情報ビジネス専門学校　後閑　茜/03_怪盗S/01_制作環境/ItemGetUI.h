//=============================================================================
//
// �A�C�e���擾UI���� [ItemGet.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _ITEMGET_H_
#define _ITEMGET_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ITEMGET "data\\TEXTURE\\Object\\Item001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMGET1 "data\\TEXTURE\\Object\\Item002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMGET2 "data\\TEXTURE\\Object\\Item003.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMGET3 "data\\TEXTURE\\Object\\Item004.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ITEMGET4 "data\\TEXTURE\\Object\\Key004.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_ITEMGETTEX (5)

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	bool bUse;
	int nType;
	int nIdxItem;
}ItemUI;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItemGetUI(void);
void UninitItemGetUI(void);
void UpdateItemGetUI(void);
void DrawItemGetUI(void);

ItemUI*GetItemUI(void);
int SetItemGetUI(int nType);
void DeleteItemGetUI(int nType);
#endif

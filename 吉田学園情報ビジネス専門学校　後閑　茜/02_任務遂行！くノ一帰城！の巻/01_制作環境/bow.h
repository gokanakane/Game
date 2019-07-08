//=============================================================================
//
// �G�|���� [Bow.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _BOW_H_
#define _BOW_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BOW		(120)		// �e�̍ő吔
#define BOW_TEXTUER "data\\TEXTURE\\Object\\bow.png"
#define BOW_TEXTUER1 "data\\TEXTURE\\Object\\bow001.png"

#define POS_Y (620)
#define BOW_MOVE (1.0f)
#define BOW_PATTERN		(5)
#define MAX_BOW_TYPE (2)
#define MAX_TEX (2)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int type;
	int nLife;//�|�̎���
	bool bUse;//�g���Ă��邩�ǂ���

}Bow;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBow(void);
void UninitBow(void);
void UpdateBow(void);
void DrawBow(void);
void SetBow(D3DXVECTOR3 pos, D3DXVECTOR3 move,int type);

Bow*GetBow(void);
#endif

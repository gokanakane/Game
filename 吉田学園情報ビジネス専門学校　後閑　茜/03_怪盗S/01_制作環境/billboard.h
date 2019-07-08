//=============================================================================
//
// �r���{�[�h���� [Billboard.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef BILLBOARD_H_
#define BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BILLBOARD (128)		//�ǂ̍ő�l
#define MAX_TEX (4)

#define KEY_TEXTUER "data\\TEXTURE\\Key000.png"
#define KEY_TEXTUER1 "data\\TEXTURE\\Key001.png"
#define KEY_TEXTUER2 "data\\TEXTURE\\Key002.png"
#define KEY_TEXTUER3 "data\\TEXTURE\\Key003.png"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒuz
	D3DXVECTOR3 rot;		//��]
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int IdxShadow;			//�e�ԍ�
	int Type;
	bool bUse;				//�g�p��
}Billboard;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

void SetBillboard(D3DXVECTOR3 pos,int Type);
#endif

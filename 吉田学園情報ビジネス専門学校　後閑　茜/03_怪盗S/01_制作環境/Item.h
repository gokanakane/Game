//=============================================================================
//
// �A�C�e������ [Item.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef ITEM_H_
#define ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM_TEXTURE1 "data\\TEXTURE\\Object\\Item001.png"
#define ITEM_TEXTURE2 "data\\TEXTURE\\Object\\Item002.png"
#define ITEM_TEXTURE3 "data\\TEXTURE\\Object\\Item003.png"
#define ITEM_TEXTURE4 "data\\TEXTURE\\Object\\Item004.png"
#define ITEM_TEXTURE5 "data\\TEXTURE\\Object\\Key004.png"

#define MAX_ITEMTEX (5)
#define MAX_ITEM (128)		//�ǂ̍ő�l

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒuz
	D3DXVECTOR3 rot;		//��]
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int IdxShadow;			//�e�ԍ�
	int IdxItem;			//�A�C�e���ԍ�
	int Type;
	bool bUse;				//�g�p��
}Item;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

Item *GetItem(void);
void SetItem(D3DXVECTOR3 pos,int Type);
void DeleteItem(int nType);
#endif

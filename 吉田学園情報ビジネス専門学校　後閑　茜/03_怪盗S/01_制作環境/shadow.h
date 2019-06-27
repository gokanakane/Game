//=============================================================================
//
// �e���� [Shadow.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef _SHADOW_H__
#define _SHADOW_H__

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SHADOW (128)	//�e�̍ő吔
#define SHADOW_TEXTUER "data\\TEXTURE\\Effect\\shadow000.jpg"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//��]
	D3DXCOLOR col;				//�F
	D3DXMATRIX g_mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;					//�g�p��

}Shadow;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int IdxShadow, D3DXVECTOR3 pos);
void DeleteShadow(int nIdxShadow);
#endif

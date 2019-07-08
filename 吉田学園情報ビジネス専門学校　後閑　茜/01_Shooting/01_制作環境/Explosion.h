//=============================================================================
//
// �������� [Explosion.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _EXPLOSON_H_
#define _EXPLOSION_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION		(128)		// �e�̍ő吔
#define EXPLOSION_TEXTUER "data\\TEXTURE\\Effect\\explosion000.png"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct MyStruct
{
	D3DXVECTOR3 pos; //�ʒu 
	D3DXCOLOR col;	 //�F
	int nCntAnim;	 //�A�j���[�V�����J�E���^�[
	int nPatternAnim;//�p�^�[��No
	bool bUse;		 //�g���Ă��邩�ǂ���

}Explosion;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif

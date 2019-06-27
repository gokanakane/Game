//=============================================================================
//
// �|���S������ [Explosion.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_EXPLOSION (128)		//�ǂ̍ő�l
#define EXPLOSION_TEXTUER "data\\TEXTURE\\Effect\\explosion000.png"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒuz
	D3DXVECTOR3 rot;		//��]
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nPatturnAnim;		//�A�j���[�V�����p�^�[��
	int nCntAnim;			//�A�j���[�V�����J�E���^�[
	bool bUse;				//�g�p��
}Explosion;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

void SetExplosion(D3DXVECTOR3 pos);
#endif

//=============================================================================
//
// �|���S������ [Bullet.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef BULLET_H_
#define BULLET_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BULLET (128)		//�e�̍ő�l
#define BULLET_POS_X (3.0f)		//�e��X
//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//��]
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 VecA;		//�x�N�g��A
	D3DXVECTOR3 VecC;		//�x�N�g��C
	int nIdxShadow;			//�e�̔ԍ�
	int nIdxEffect;			//�G�t�F�N�g�̔ԍ�
	bool bUse;				//�g�p��

}Bullet;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Bullet*GetBullet(void);
#endif

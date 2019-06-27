//=============================================================================
//
// ���f������ [DisPlay.h]
// Author : 
//
//=============================================================================
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "main.h"

#define MAX_DISPLAY (128) //���f���̍ő吔
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DISPLAY_TEXTURE " "
#define DISPLAY_1 "data\\Model\\Obj\\DisPlay000.x"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	LPD3DXBUFFER pBuffMat;		//�}�e���A�����ւ̃|�C���^
	LPD3DXMESH pMesh;			//���b�V�����i���_���j�̃|�C���^
	DWORD nNumMat;				//�}�e���A�����̐�
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//��]
	D3DXCOLOR col;				//�F
	D3DXVECTOR3 vtxMin;			//���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;			//���f���̍ő�l
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int nIdxShadow;				//�e�ԍ�
	int nType;					//�^�C�v
	bool bUse;					//�g�p��
}DisPlay;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitDisPlay(void);
void UninitDisPlay(void);
void UpdateDisPlay(void);
void DrawDisPlay(void);

DisPlay*GetDisPlay(void);
void CollisionDisPlay(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
void SetDisPlay(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
#endif

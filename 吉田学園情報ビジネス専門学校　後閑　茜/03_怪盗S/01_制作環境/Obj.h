//=============================================================================
//
// �I�u�W�F�N�g���� [Obj.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _OBJ_H_
#define _OBJ_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBJ_TEXTURE " "
#define OBJ_1 "data\\Model\\Obj\\Treasure.x"
#define OBJ_MOVR (1.0f)

#define MAX_OBJ (5) //���f���̍ő吔

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
}Obj;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitObj(void);
void UninitObj(void);
void UpdateObj(void);
void DrawObj(void);

Obj*GetObj(void);
bool CollisionObj(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
void SetObj(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
#endif

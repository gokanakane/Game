//=============================================================================
//
// ���f������ [Player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYERMODEL (15)			//���f���̐�

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMesh;			//���b�V�����i���_���j�̃|�C���^
	LPD3DXBUFFER pBuffMat;		//�}�e���A�����ւ̃|�C���^
	DWORD NumMat;				//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//��]
	int nIdxModel;				//���f���̃C���f�b�N�X

}PlayerModel;

typedef struct
{
	LPD3DXMESH pMesh;			//���b�V�����i���_���j�̃|�C���^
	LPD3DXBUFFER pBuffMat;		//�}�e���A�����ւ̃|�C���^
	DWORD NumMat;				//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXVECTOR3 rot;			//��]
	D3DXVECTOR3 move;			//�ړ���
	D3DXVECTOR3 VecA;		//�x�N�g��A
	D3DXVECTOR3 VecC;		//�x�N�g��C
	D3DXCOLOR col;				//�F
	D3DXVECTOR3 vtxMin;			//���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;			//���f���̍ő�l
	int nIdxShadow;				//�e�ԍ�
	PlayerModel aModel[MAX_PLAYERMODEL];	//[�@]�����f���̐�
}Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player*GetPlayer(void);
void CollisionStagePL(void);

#endif

//=============================================================================
//
// ���f������ [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMYMODEL (2)			//���f���̐�
#define MAX_ENEMY (128)				//�G�̍ő吔
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

}EnemyModel;

typedef struct
{
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXVECTOR3 rot;			//��]
	D3DXVECTOR3 move;			//�ړ���
	D3DXCOLOR col;				//�F
	D3DXVECTOR3 vtxMin;			//���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;			//���f���̍ő�l
	D3DXVECTOR3 VecA;		//�x�N�g��A
	D3DXVECTOR3 VecC;		//�x�N�g��C
	int nIdxShadow;				//�e�ԍ�
	float nCntMove;				//�ړ��J�E���^�[
	float nChengeMove;			//�ړ���
	int nType;					//0:���ړ��@1:�c�ړ�
	bool bUse;					//�g�p��
	EnemyModel aModel;	//[�@]�����f���̐�
}Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

Enemy*GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float ChengeMove, int Type);
void CollisionStageEN(void);
bool CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
#endif

//=============================================================================
//
// �|���S������ [MeshFild.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef WALL_H_
#define WALL_H_

#include "main.h"
#include "Game.h"

#define MAX_WALL (62)		//�X�e�[�W1���\������t�B�[���h�̕�����
#define MAX_VEC (4)
//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXVECTOR3 VecA;
	D3DXVECTOR3 VecC;
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	int Width;						//��
	int Heidth;						//�c
	bool bUse;						//�g�p��
	int VertexStage;				//�o�[�e�b�N�X
	int IndexStage;					//�C���f�b�N�X
	int PolygonStage;				//�|���S����
	int nTexType;					//�e�N�X�`���̃^�C�v
	D3DXVECTOR3 aPos[MAX_VEC];			//�x�N�g��
}Wall;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

Wall*GetWall(void);
void SetWall(int Width, int Heidth, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int TexType);
void CollisionWall_WIDTH_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);
void CollisionWall_HEIDTH_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);
bool CollisionWall_WIDTH_ENE(D3DXVECTOR3 *pos, D3DXVECTOR3 aPos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *rot);
bool CollisionWall_HEIDTH_ENE(D3DXVECTOR3 *pos, D3DXVECTOR3 aPos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *rot);

#endif

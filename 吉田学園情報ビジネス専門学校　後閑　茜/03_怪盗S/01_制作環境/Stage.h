//=============================================================================
//
// �|���S������ [MeshFild.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef STAGE1_H_
#define STAGE1_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_VECSTAGE (4)
#define MESHFIELD_TEXTUER "data\\TEXTURE\\BG\\Field000.jpg"
#define STAGE_SPLIT (1)	//�X�e�[�W1���\������t�B�[���h�̕�����
#define STAGE_X (50.0f)
#define STAGE_Z (50.0f)

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int Width;					//��
	int Heidth;					//�c
	bool bUse;					//�g�p��
	int VertexStage;			//�o�[�e�b�N�X
	int IndexStage;				//�C���f�b�N�X
	int PolygonStage;			//�|���S����

}Stage;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);

Stage*GetStage(void);
void SetStageMap(int Width, int Heidth, D3DXVECTOR3 pos);
#endif

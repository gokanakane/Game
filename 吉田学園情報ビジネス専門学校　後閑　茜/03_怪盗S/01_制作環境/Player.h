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
#define PLAYER_TEXTUER " "
#define PLAYER_1 "data\\MODEL\\PC\\00_Upper Body.x"		//�㔼�g[0]
#define PLAYER_2 "data\\MODEL\\PC\\01_Lower Body.x"		//�����g[1]
#define PLAYER_3 "data\\MODEL\\PC\\02_Fase.x"			//��[2]
#define PLAYER_4 "data\\MODEL\\PC\\03_Second_Arm_R.x"	//�E��̘r[3]
#define PLAYER_5 "data\\MODEL\\PC\\04_Arm_R.x"			//�E�r[4]
#define PLAYER_6 "data\\MODEL\\PC\\05_Hand_R.x"			//�E��[5]
#define PLAYER_7 "data\\MODEL\\PC\\06_Second_Arm_L.x"	//����̘r[6]
#define PLAYER_8 "data\\MODEL\\PC\\07_Arm_L.x"			//���r[7]
#define PLAYER_9 "data\\MODEL\\PC\\08_Hand_L.x"			//����[8]
#define PLAYER_10 "data\\MODEL\\PC\\09_Thugus_R.x"		//�E������[9]
#define PLAYER_11 "data\\MODEL\\PC\\10_Calf_R.x"		//�E�ӂ���͂�[10]
#define PLAYER_12 "data\\MODEL\\PC\\11_Foot_R.x"		//�E��[11]
#define PLAYER_13 "data\\MODEL\\PC\\12_Thugus_L.x"		//��������[12]
#define PLAYER_14 "data\\MODEL\\PC\\13_Calf_L.x"		//���ӂ���͂�[13]
#define PLAYER_15 "data\\MODEL\\PC\\14_Foot_L.x"		//����[14]
#define PLAYER_MOVR (1.0f)


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

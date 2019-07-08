//=============================================================================
//
// �u���b�N���� [Block.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BLOCKTEX	(5)
#define BLOCK_MOVE (3.0f) //�u���b�N�̈ړ���
#define PLAYER_POS_X (25.0f)	//�v���C���[��Pos.x
#define PLAYER_POS_Y (90.0f)	//�v���C���[��Pos.y

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct 
{
	D3DXVECTOR3 pos; //�ʒu 
	D3DXVECTOR3 move; //�ړ��� 
	float fWidth;    //��
	float fHeight;	 //����
	bool bUse;		 //�g���Ă��邩�ǂ���
	bool bLand;		//������̎g�p��
	int nType;		//�u���b�N�̃^�C�v	0->�n�ʁ@1->�ʏ�u���b�N�@2->�ړ��u���b�N�@3->�R���x�A�[
	int Cntmove;	//�ړ��J�E���^�[
	int ChengeMove; //�ړ���

}Block;

typedef struct
{
	D3DXVECTOR3 pos; //�ʒu 
	float fWidth;    //��
	float fHeight;	 //����
	int nType;		//�u���b�N�̃^�C�v	0->�n�ʁ@1->�ʏ�u���b�N�@2->�ړ��u���b�N�@3->�R���x�A�[
	int Cntmove;	//�ړ��J�E���^�[
	int ChengeMove; //�ړ���

}BlockInfo;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BLOCK		(128)		// �u���b�N�̍ő吔
#define BLOCK_TEXTUER "data\\TEXTURE\\Object\\block000.jpg"
#define BLOCK_TEXTUER1 "data\\TEXTURE\\Object\\block001.png"
#define BLOCK_TEXTUER2 "data\\TEXTURE\\Object\\block002.png"
#define BLOCK_TEXTUER3 "data\\TEXTURE\\Object\\block003.png"
#define BLOCK_TEXTUER4 "data\\TEXTURE\\Object\\block004.png"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType,int ChengeMove);

bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
Block*GetBlock(void);
#endif

//=============================================================================
//
// �h�A���� [Door.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _DOOR_H_
#define _DOOR_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DOOR_MOVE (3.0f) //�u���b�N�̈ړ���
#define DOORANIM_PATTURN (4)
#define DOOR_WIDTH (200)
#define DOOR_HEIGTH (250)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//�񋓌^
	DOORSTATE_CLOSE = 0, //�h�A�i0�j
	DOORSTATE_OPENSTART,//�h�A�J���͂���(1)
	DOORSTATE_OPEN,		//�h�A�J�i2�j
	DOORSTATE_MAX		 //�h�A�̏�Ԃ̑����i3�j

}DOORSTATE;

typedef struct 
{
	D3DXVECTOR3 pos; //�ʒu 
	DOORSTATE state;			//�h�A�̏��
	bool bUse;		 //�g���Ă��邩�ǂ���


}Door;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DOOR_TEXTUER "data\\TEXTURE\\UI\\DOOR003.png"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitDoor(void);
void UninitDoor(void);
void UpdateDoor(void);
void DrawDoor(void);
void SetDoor(D3DXVECTOR3 pos);

bool CollisionDoor(D3DXVECTOR3 *pPos);
Door*GetDoor(void);
#endif

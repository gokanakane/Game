//=============================================================================
//
// 弾処理 [Door.h]
// Author :
//
//=============================================================================
#ifndef _DOOR_H_
#define _DOOR_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//列挙型
	DOORSTATE_CLOSE = 0, //ドア閉（0）
	DOORSTATE_OPENSTART,//ドア開きはじめ(1)
	DOORSTATE_OPEN,		//ドア開（2）
	DOORSTATE_MAX		 //ドアの状態の総数（3）

}DOORSTATE;

typedef struct 
{
	D3DXVECTOR3 pos; //位置 
	DOORSTATE state;			//ドアの状態
	bool bUse;		 //使っているかどうか


}Door;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DOOR_TEXTUER "data\\TEXTURE\\DOOR003.png"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitDoor(void);
void UninitDoor(void);
void UpdateDoor(void);
void DrawDoor(void);
void SetDoor(D3DXVECTOR3 pos);

bool CollisionDoor(D3DXVECTOR3 *pPos);
Door*GetDoor(void);
#endif

//=============================================================================
//
// 弾処理 [bullet.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET		(128)		// 弾の最大数
#define BULLET_TEXTUER "data\\TEXTURE\\UI\\honou.png"
#define BULLET_TEXTUER1 "data\\TEXTURE\\UI\\honou2.png"
#define POS_Y (620)
#define BULLET_MOVE (1.0f)
#define BULLET_PATTERN		(5)
#define MAX_BULLET_TYPE (2)

//*****************************************************************************
// 弾の種類
//*****************************************************************************
typedef enum
{//列挙型
	BULLETTYPE_PLAYER = 0,//プレイヤーの弾
	BULLETTYPE_EMEMY,	 //敵の弾
	BULLET_MAX
}BULLETTYPE;
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	int nLife; //弾の寿命
	BULLETTYPE type;
	bool bUse;//使っているかどうか

}Bullet;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type,int Life);

#endif

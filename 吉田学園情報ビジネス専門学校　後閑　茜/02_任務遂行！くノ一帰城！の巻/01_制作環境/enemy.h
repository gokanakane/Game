//=============================================================================
//
// 敵処理 [enemy.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ENEMY	(128)	// 敵の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//列挙型
	ENEMYSTATE_NOMAL = 0, //通常状態（0）
	ENEMYSTATE_DAMAGE,	  //ダメージ状態（1）
	ENEMYSTATE_MAX		  //敵の状態の総数（2）

}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//位置
	ENEMYSTATE state;//敵の状態
	int nType;
	int nCntState;	//状態の管理
	int nLife;		//体力
	bool bUse;		//使用しているかどうか
}Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);

Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif

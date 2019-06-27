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
#define	MAX_TYPE_ENEMY		(4)												// 敵の種類
#define ENEMY_TEXTURE0		"data\\TEXTURE\\Charactor\\enemy000_a.png"		// 敵のテクスチャの名前0
#define ENEMY_TEXTURE1		"data\\TEXTURE\\Charactor\\enemy001_a.png"		// 敵のテクスチャの名前1
#define ENEMY_TEXTURE2		"data\\TEXTURE\\Charactor\\enemy002_a.png"		// 敵のテクスチャの名前2
#define ENEMY_TEXTURE3		"data\\TEXTURE\\Charactor\\enemy003_a.png"		// 敵のテクスチャの名前3
#define PLAYER_PATTERN		(2)

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
	int nType;		//種類
	ENEMYSTATE state;//敵の状態
	int nCntState;	//状態の管理
	int nLife;		//体力
	int nCnt;
	bool bUse;		//使用しているかどうか
	int Cntmove;	//敵の移動カウンター
	int ChengeMove;	//移動量

}Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType, int ChengeMove,int Life);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif

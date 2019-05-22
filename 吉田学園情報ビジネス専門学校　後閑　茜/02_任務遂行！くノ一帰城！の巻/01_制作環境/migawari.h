//=============================================================================
//
// 弾処理 [Migawari.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _MIGAWARI_H_
#define _MIGAWARI_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MIGAWARI_MAX_LIFE (5)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//列挙型
	MIGAWARISTATE_NOMAL = 0, //通常状態（0）
	MIGAWARISTATE_DAMAGE,	  //ダメージ状態（1）
	MIGAWARISTATE_DEATH,	  //死亡
	MIGAWARISTATE_MAX		  //敵の状態の総数（2）

}MigawariState;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posold;	//前回の位置
	D3DXVECTOR3 move;	//移動
	MigawariState state;//身代わりの状態
	int nCntState;		//状態の管理
	int type;			//種類
	int nLife;			//耐久値
	bool bUse;			//使っているかどうか

}Migawari;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMigawari(void);
void UninitMigawari(void);
void UpdateMigawari(void);
void DrawMigawari(void);
void HitMigawari(int nDamage);
void SetMigawari(D3DXVECTOR3 pos,int Type);

Migawari*GetMigawari(void);
#endif

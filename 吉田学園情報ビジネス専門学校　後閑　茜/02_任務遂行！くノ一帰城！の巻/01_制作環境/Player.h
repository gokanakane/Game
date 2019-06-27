//=============================================================================
//
// プレイヤー処理 [Player.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PLAYER_H_ //二十インクルード防止のマクロ定義
#define _PLAYER_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAXPLAYER_LIFE (3)
#define PLAYER_MOVE (4.0f)
#define PLAYER_PATTERN (4)
#define PLAYER_TEXTUER "data\\TEXTURE\\Charactor\\player001.png"
#define PLAYER_TEXTUER1 "data\\TEXTURE\\Charactor\\player002.png"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//列挙型
	PLAYERSTATE_APPEAR = 0,//出現状態,（0）
	PLAYERSTATE_NOMAL, //通常状態（1）
	PLAYERSTATE_DAMAGE,	  //ダメージ状態（2）
	PLAYERSTEAT_DEATH,//敵の死亡状態（3）
	PLAYERSTATE_MAX		  //敵の状態の総数（4）

}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	D3DXVECTOR3 posold;	//前回の位置
	D3DXVECTOR3 move;	//移動
	int nLife;			//体力
	int nPatternAnim;	//アニメーションパターン
	int nCntAnim;		//アニメーションカウンター
	int nCntState;		//プレイヤーの状態カウンター
	int nDirectionMove; //0:右向き　1：左向き
	int CntColor;		//点滅のカウンタ
	int ChengeColor;	//点滅の透明度
	bool bJump;			//ジャンプの使用状況
	bool bDisp;			//プレイヤーの使用状況
	bool bWalk;			//歩行判定
	PLAYERSTATE state;  //プレイヤーの状態


}Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void HitPlayer(int nDamage);
Player*GetPlayer(void);
#endif

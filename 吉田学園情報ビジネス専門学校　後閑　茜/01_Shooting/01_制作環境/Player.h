//=============================================================================
//
// DirectX雛型処理 [Player.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _PLAYER_H_ //二十インクルード防止のマクロ定義
#define _PLAYER_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAXPLAYER_LIFE (3)//最大体力
#define PLAYER_TEXTUER "data\\TEXTURE\\Charactor\\player000_a.png" //読み込むテクスチャ
#define PLAYER_MOVE (6.0f)							  //プレイヤーの移動量

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
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;//プレイヤーの状況
	int nCntState;
	int nLife;
	bool bDisp;//表示するかしないか

}Player;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player *GetPlayer(void);
void HitPlayer(int nDamage);

#endif

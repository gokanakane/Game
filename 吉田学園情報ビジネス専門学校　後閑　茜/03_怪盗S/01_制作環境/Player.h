//=============================================================================
//
// モデル処理 [Player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYERMODEL (15)			//モデルの数
#define PLAYER_TEXTUER " "
#define PLAYER_1 "data\\MODEL\\PC\\00_Upper Body.x"		//上半身[0]
#define PLAYER_2 "data\\MODEL\\PC\\01_Lower Body.x"		//下半身[1]
#define PLAYER_3 "data\\MODEL\\PC\\02_Fase.x"			//顔[2]
#define PLAYER_4 "data\\MODEL\\PC\\03_Second_Arm_R.x"	//右二の腕[3]
#define PLAYER_5 "data\\MODEL\\PC\\04_Arm_R.x"			//右腕[4]
#define PLAYER_6 "data\\MODEL\\PC\\05_Hand_R.x"			//右手[5]
#define PLAYER_7 "data\\MODEL\\PC\\06_Second_Arm_L.x"	//左二の腕[6]
#define PLAYER_8 "data\\MODEL\\PC\\07_Arm_L.x"			//左腕[7]
#define PLAYER_9 "data\\MODEL\\PC\\08_Hand_L.x"			//左手[8]
#define PLAYER_10 "data\\MODEL\\PC\\09_Thugus_R.x"		//右太もも[9]
#define PLAYER_11 "data\\MODEL\\PC\\10_Calf_R.x"		//右ふくらはぎ[10]
#define PLAYER_12 "data\\MODEL\\PC\\11_Foot_R.x"		//右足[11]
#define PLAYER_13 "data\\MODEL\\PC\\12_Thugus_L.x"		//左太もも[12]
#define PLAYER_14 "data\\MODEL\\PC\\13_Calf_L.x"		//左ふくらはぎ[13]
#define PLAYER_15 "data\\MODEL\\PC\\14_Foot_L.x"		//左足[14]
#define PLAYER_MOVR (1.0f)


//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMesh;			//メッシュ情報（頂点情報）のポインタ
	LPD3DXBUFFER pBuffMat;		//マテリアル情報へのポインタ
	DWORD NumMat;				//マテリアル情報の数
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//回転
	int nIdxModel;				//モデルのインデックス

}PlayerModel;

typedef struct
{
	LPD3DXMESH pMesh;			//メッシュ情報（頂点情報）のポインタ
	LPD3DXBUFFER pBuffMat;		//マテリアル情報へのポインタ
	DWORD NumMat;				//マテリアル情報の数
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 rot;			//回転
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 VecA;		//ベクトルA
	D3DXVECTOR3 VecC;		//ベクトルC
	D3DXCOLOR col;				//色
	D3DXVECTOR3 vtxMin;			//モデルの最小値
	D3DXVECTOR3 vtxMax;			//モデルの最大値
	int nIdxShadow;				//影番号
	PlayerModel aModel[MAX_PLAYERMODEL];	//[　]＝モデルの数
}Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

Player*GetPlayer(void);
void CollisionStagePL(void);

#endif

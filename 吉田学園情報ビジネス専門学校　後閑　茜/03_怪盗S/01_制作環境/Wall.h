//=============================================================================
//
// ポリゴン処理 [MeshFild.h]
// Author : 後閑茜
//
//=============================================================================
#ifndef WALL_H_
#define WALL_H_

#include "main.h"
#include "Game.h"

#define MAX_WALL (62)		//ステージ1を構成するフィールドの分割数
#define MAX_VEC (4)
//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXVECTOR3 VecA;
	D3DXVECTOR3 VecC;
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int Width;						//横
	int Heidth;						//縦
	bool bUse;						//使用状況
	int VertexStage;				//バーテックス
	int IndexStage;					//インデックス
	int PolygonStage;				//ポリゴン数
	int nTexType;					//テクスチャのタイプ
	D3DXVECTOR3 aPos[MAX_VEC];			//ベクトル
}Wall;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

Wall*GetWall(void);
void SetWall(int Width, int Heidth, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int TexType);
void CollisionWall_WIDTH_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);
void CollisionWall_HEIDTH_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);
bool CollisionWall_WIDTH_ENE(D3DXVECTOR3 *pos, D3DXVECTOR3 aPos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *rot);
bool CollisionWall_HEIDTH_ENE(D3DXVECTOR3 *pos, D3DXVECTOR3 aPos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *rot);

#endif

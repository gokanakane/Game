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
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WALL_TEXTUER "data\\TEXTURE\\Object\\Wall000.jpg"
#define WALL_TEXTUER1 "data\\TEXTURE\\Object\\Wall001.jpg"
#define WALL_TEXTUER2 "data\\TEXTURE\\Object\\Wall002.jpg"
#define WALL_TEXTUER3 "data\\TEXTURE\\Object\\Wall003.jpg"
#define WALL_TEXTUER4 "data\\TEXTURE\\Object\\Wall008.png"
#define WALL_TEXTUER5 "data\\TEXTURE\\Object\\Wall009.png"

#define WALLVTX_X (50.0f)		//頂点を置く横間隔
#define WALLVTX_Y (50.0f)		//頂点を置く高さ間隔
#define MAX_WALL (62)		//ステージ1を構成するフィールドの分割数
#define MAX_WALLVEC (4)
#define MAX_WALLTEX (6)
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
	D3DXVECTOR3 aPos[MAX_WALLVEC];			//ベクトル
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

//=============================================================================
//
// ポリゴン処理 [MeshFild.h]
// Author : 後閑茜
//
//=============================================================================
#ifndef STAGE1_H_
#define STAGE1_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_VECSTAGE (4)
#define MESHFIELD_TEXTUER "data\\TEXTURE\\BG\\Field000.jpg"
#define STAGE_SPLIT (1)	//ステージ1を構成するフィールドの分割数
#define STAGE_X (50.0f)
#define STAGE_Z (50.0f)

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	int Width;					//横
	int Heidth;					//縦
	bool bUse;					//使用状況
	int VertexStage;			//バーテックス
	int IndexStage;				//インデックス
	int PolygonStage;			//ポリゴン数

}Stage;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);

Stage*GetStage(void);
void SetStageMap(int Width, int Heidth, D3DXVECTOR3 pos);
#endif

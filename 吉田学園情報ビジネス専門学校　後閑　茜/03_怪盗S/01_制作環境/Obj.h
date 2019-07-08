//=============================================================================
//
// オブジェクト処理 [Obj.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _OBJ_H_
#define _OBJ_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBJ_TEXTURE " "
#define OBJ_1 "data\\Model\\Obj\\Treasure.x"
#define OBJ_MOVR (1.0f)

#define MAX_OBJ (5) //モデルの最大数

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	LPD3DXBUFFER pBuffMat;		//マテリアル情報へのポインタ
	LPD3DXMESH pMesh;			//メッシュ情報（頂点情報）のポインタ
	DWORD nNumMat;				//マテリアル情報の数
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//回転
	D3DXCOLOR col;				//色
	D3DXVECTOR3 vtxMin;			//モデルの最小値
	D3DXVECTOR3 vtxMax;			//モデルの最大値
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	int nIdxShadow;				//影番号
	int nType;					//タイプ
	bool bUse;					//使用状況
}Obj;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitObj(void);
void UninitObj(void);
void UpdateObj(void);
void DrawObj(void);

Obj*GetObj(void);
bool CollisionObj(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
void SetObj(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
#endif

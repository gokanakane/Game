//=============================================================================
//
// モデル処理 [DisPlay.h]
// Author : 
//
//=============================================================================
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "main.h"

#define MAX_DISPLAY (128) //モデルの最大数
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DISPLAY_TEXTURE " "
#define DISPLAY_1 "data\\Model\\Obj\\DisPlay000.x"

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
}DisPlay;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitDisPlay(void);
void UninitDisPlay(void);
void UpdateDisPlay(void);
void DrawDisPlay(void);

DisPlay*GetDisPlay(void);
void CollisionDisPlay(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
void SetDisPlay(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
#endif

//=============================================================================
//
// ブロック処理 [Block.h]
// Author :Gokan Akane
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BLOCKTEX	(5)
#define BLOCK_MOVE (3.0f) //ブロックの移動量
#define PLAYER_POS_X (25.0f)	//プレイヤーのPos.x
#define PLAYER_POS_Y (90.0f)	//プレイヤーのPos.y

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct 
{
	D3DXVECTOR3 pos; //位置 
	D3DXVECTOR3 move; //移動量 
	float fWidth;    //幅
	float fHeight;	 //高さ
	bool bUse;		 //使っているかどうか
	bool bLand;		//横判定の使用状況
	int nType;		//ブロックのタイプ	0->地面　1->通常ブロック　2->移動ブロック　3->コンベアー
	int Cntmove;	//移動カウンター
	int ChengeMove; //移動量

}Block;

typedef struct
{
	D3DXVECTOR3 pos; //位置 
	float fWidth;    //幅
	float fHeight;	 //高さ
	int nType;		//ブロックのタイプ	0->地面　1->通常ブロック　2->移動ブロック　3->コンベアー
	int Cntmove;	//移動カウンター
	int ChengeMove; //移動量

}BlockInfo;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BLOCK		(128)		// ブロックの最大数
#define BLOCK_TEXTUER "data\\TEXTURE\\Object\\block000.jpg"
#define BLOCK_TEXTUER1 "data\\TEXTURE\\Object\\block001.png"
#define BLOCK_TEXTUER2 "data\\TEXTURE\\Object\\block002.png"
#define BLOCK_TEXTUER3 "data\\TEXTURE\\Object\\block003.png"
#define BLOCK_TEXTUER4 "data\\TEXTURE\\Object\\block004.png"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType,int ChengeMove);

bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
Block*GetBlock(void);
#endif

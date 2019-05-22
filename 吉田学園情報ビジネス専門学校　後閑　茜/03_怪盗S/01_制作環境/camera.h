//=============================================================================
//
// カメラ処理 [camera.h]
// Author :後閑茜 
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;		 // 現在の位置視点
	D3DXVECTOR3 posR;	 	 // 現在の注視点
	D3DXVECTOR3 posVDest;	 // 現在の位置視点
	D3DXVECTOR3 posRDest; 	 // 現在の注視点
	D3DXVECTOR3 posU;	 	 // 現在の上方向ベクトル
	D3DXVECTOR3 rot;		 //回転
	D3DXVECTOR3 rotDest;	 //目的の回転
	D3DXMATRIX mtxProjextion;//プロジェクションマトリックス
	D3DXMATRIX mtxView;		 //ビューマトリックス
	float fDistance;		 //距離
} Camera;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

Camera*GetCamera(void);

#endif

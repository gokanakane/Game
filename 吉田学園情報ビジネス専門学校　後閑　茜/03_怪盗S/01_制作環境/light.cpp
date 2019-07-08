//=============================================================================
//
// ライト処理 [light.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_Ligth[MAX_LIGHT];

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXVECTOR3 vecDir[MAX_LIGHT];				//設定方向ベクトル

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		// ライトをクリアする
		ZeroMemory(&g_Ligth[nCnt], sizeof(D3DLIGHT9));
		// ライトの種類を設定
		g_Ligth[nCnt].Type = D3DLIGHT_DIRECTIONAL;

	}


	// ライトの拡散光を設定
	g_Ligth[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Ligth[1].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	g_Ligth[2].Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);


	// ライトの方向の設定[0]
	vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);//正規化
	g_Ligth[0].Direction = vecDir[0];


	// ライトの方向の設定[1]
	vecDir[1] = D3DXVECTOR3(-0.5f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);//正規化
	g_Ligth[1].Direction = vecDir[1];



	// ライトの方向の設定[2]
	vecDir[2] = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);//正規化
	g_Ligth[2].Direction = vecDir[2];

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		// ライトを設定する
		pDevice->SetLight(nCnt, &g_Ligth[nCnt]);

		// ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);
	}

}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{

}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{

}


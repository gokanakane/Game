//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 後閑茜
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "Player.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_Camera;			//カメラの情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	//構造体の初期化
	g_Camera.posV = D3DXVECTOR3(400.0f, 100.0f, -200.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f,D3DX_PI, 0.0f);
	g_Camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fDistance = 40;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	//float fDesAngle=0;	//目的の角度
	//float fMoveAngle=0;	//現在の角度

	Player*pPlayer;
	MODE g_MODE;
	pPlayer = GetPlayer();
	g_MODE = GetMode();
	int nCnt = 0;//秒数

	//g_Camera.posV = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y+50, pPlayer->pos.z+120);
	//g_Camera.posR = pPlayer->pos;

	if (g_MODE == MODE_GAME)
	{
		////プレイヤーが移動したら追従
		//if (pPlayer->posOld != pPlayer->pos)
		//{
			//カメラの追従------------------------------------
			//目的の注視点
		g_Camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * -pPlayer->move.x;
		g_Camera.posRDest.y = pPlayer->pos.y;
		g_Camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * -pPlayer->move.z;

		//目的の視点
		g_Camera.posVDest.x = pPlayer->pos.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posVDest.y = pPlayer->pos.y + 20.0f;
		g_Camera.posVDest.z = pPlayer->pos.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

		////注視点
		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * 0.2f;
		g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y) * 0.2f;
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * 0.2f;

		//視点
		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * 0.07f;
		g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y) * 0.07f;
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * 0.07f;
	}
		//	//リセット--------------------------------
		//	if (GetKeyboardPress(DIK_RETURN) == true)
		//	{
		//		InitCamera();
		//	}
		//}


		//}
		//else
		//{
			//目的の注視点
			//g_Camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * -10.0f;
			//g_Camera.posRDest.y = pPlayer->pos.y;
			//g_Camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * -10.0f;

			////目的の視点
			//g_Camera.posVDest.x = pPlayer->pos.x + sinf(g_Camera.rotDest.y) * g_Camera.fDistance;
			//g_Camera.posVDest.y = pPlayer->pos.y + 20.0f;
			//g_Camera.posVDest.z = pPlayer->pos.z + cosf(g_Camera.rotDest.y) * g_Camera.fDistance;

			////注視点
			//g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * 0.2f;
			//g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y) * 0.2f;
			//g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * 0.2f;

			////視点
			//g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * 0.07f;
			//g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y) * 0.07f;
			//g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * 0.07f;
		//	//nCnt++;
		//	//if (nCnt>=120)
		//	//{//2秒経ったら


		//	//	nCnt = 0;
		//	//}
		//}


		////カメラ移動-----------------------------------
	//	if (GetKeyboardPress(DIK_A) == true)
	//	{//左移動
	//		g_Camera.posV.x += sinf(D3DX_PI * -0.5f + g_Camera.rot.y)*CAMERA_MOVR;
	//		g_Camera.posV.z += cosf(D3DX_PI * -0.5f + g_Camera.rot.y)*CAMERA_MOVR;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(0.0f + g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(0.0f + g_Camera.rot.y) * g_Camera.fDistance;
	//	}

	//	if (GetKeyboardPress(DIK_D) == true)
	//	{//右移動
	//		g_Camera.posV.x += sinf(D3DX_PI * 0.5f + g_Camera.rot.y)* CAMERA_MOVR;
	//		g_Camera.posV.z += cosf(D3DX_PI * 0.5f + g_Camera.rot.y)* CAMERA_MOVR;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(0.0f + g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(0.0f + g_Camera.rot.y) * g_Camera.fDistance;

	//	}

	//	if (GetKeyboardPress(DIK_W) == true)
	//	{//上移動
	//		g_Camera.posV.x += sinf(0.0f + g_Camera.rot.y)*CAMERA_MOVR;
	//		g_Camera.posV.z += cosf(0.0f + g_Camera.rot.y)*CAMERA_MOVR;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(0.0f+ g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(0.0f+ g_Camera.rot.y) * g_Camera.fDistance;
	//	}

	//	if (GetKeyboardPress(DIK_S) == true)
	//	{//下移動
	//		g_Camera.posV.x += sinf(D3DX_PI+ g_Camera.rot.y)*CAMERA_MOVR;
	//		g_Camera.posV.z += cosf(D3DX_PI+ g_Camera.rot.y)*CAMERA_MOVR;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(0.0f+ g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(0.0f+ g_Camera.rot.y) * g_Camera.fDistance;
	//	}

	//	//視点移動--------------------------------
	//	if (GetKeyboardPress(DIK_Y) == true)
	//	{
	//		g_Camera.posV.x += sinf(0.0f)*CAMERA_MOVR;
	//		g_Camera.posV.y += cosf(0.0f)*CAMERA_MOVR;
	//	}
	//	else if (GetKeyboardPress(DIK_N) == true)
	//	{
	//		g_Camera.posV.x += sinf(D3DX_PI)*CAMERA_MOVR;
	//		g_Camera.posV.y += cosf(D3DX_PI)*CAMERA_MOVR;
	//	}
	//	if (GetKeyboardPress(DIK_Z) == true)
	//	{//左旋回
	//		g_Camera.rot.y += 0.05f;

	//		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;
	//		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;

	//	}
	//	else if (GetKeyboardPress(DIK_C) == true)
	//	{//右旋回
	//		g_Camera.rot.y -= 0.05f;

	//		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;
	//		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;

	//	}

	//	//注視点移動--------------------------------
	//	if (GetKeyboardPress(DIK_T) == true)
	//	{
	//		g_Camera.posR.x += sinf(0.0f)*CAMERA_MOVR;
	//		g_Camera.posR.y += cosf(0.0f)*CAMERA_MOVR;
	//	}
	//	if (GetKeyboardPress(DIK_B) == true)
	//	{
	//		g_Camera.posR.x += sinf(D3DX_PI)*CAMERA_MOVR;
	//		g_Camera.posR.y += cosf(D3DX_PI)*CAMERA_MOVR;
	//	}
	//	if (GetKeyboardPress(DIK_Q) == true)
	//	{
	//		g_Camera.rot.y -= 0.05f;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

	//	}
	//	if (GetKeyboardPress(DIK_E) == true)
	//	{
	//		g_Camera.rot.y += 0.05f;

	//		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
	//		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;

	//	}
	//}
	if (g_MODE == MODE_TITLE)
	{
		g_Camera.rot.y += 0.01f;

		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;
		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y - D3DX_PI) * g_Camera.fDistance;

	}

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjextion);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjextion,
							D3DXToRadian(45.0f),//視野角
							(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,//画面サイズ（比率）
							10.0f,//手前の位置
							1000.0f);//奥の位置

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjextion);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView, 
						&g_Camera.posV,
						&g_Camera.posR, 
						&g_Camera.posU);
		
	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

}
//=============================================================================
// カメラの取得
//=============================================================================
Camera*GetCamera(void)
{
	return &g_Camera;
}
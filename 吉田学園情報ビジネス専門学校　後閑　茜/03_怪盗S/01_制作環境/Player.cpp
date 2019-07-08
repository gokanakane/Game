//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Player.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "Stage.h"
#include "Obj.h"
#include "DisPlay.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Enemy.h"
#include "fade.h"
#include "Wall.h"
#include "score.h"
#include "sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//テクスチャへのポインタ
Player g_Player;								//モデルの情報
bool g_bPlaying;						//ゲーム中かどうか（trueだったら更新を続ける）
//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//頂点数
	DWORD sizeFVF;						//頂点フォーマットのサイズ
	BYTE *pVtxBuff;						//頂点バッファのポインタ
	g_Player.vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_Player.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	for (int nCnt = 0; nCnt < MAX_PLAYERMODEL; nCnt++)
	{
		g_Player.aModel[nCnt].NumMat = 0;
	}
	// Xファイルの読み込み
	D3DXLoadMeshFromX(PLAYER_1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMat,
		NULL,
		&g_Player.aModel[0].NumMat,
		&g_Player.aModel[0].pMesh);

	D3DXLoadMeshFromX(PLAYER_2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMat,
		NULL,
		&g_Player.aModel[1].NumMat,
		&g_Player.aModel[1].pMesh);

	D3DXLoadMeshFromX(PLAYER_3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[2].pBuffMat,
		NULL,
		&g_Player.aModel[2].NumMat,
		&g_Player.aModel[2].pMesh);

	D3DXLoadMeshFromX(PLAYER_4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[3].pBuffMat,
		NULL,
		&g_Player.aModel[3].NumMat,
		&g_Player.aModel[3].pMesh);

	D3DXLoadMeshFromX(PLAYER_5,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[4].pBuffMat,
		NULL,
		&g_Player.aModel[4].NumMat,
		&g_Player.aModel[4].pMesh);

	D3DXLoadMeshFromX(PLAYER_6,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[5].pBuffMat,
		NULL,
		&g_Player.aModel[5].NumMat,
		&g_Player.aModel[5].pMesh);

	D3DXLoadMeshFromX(PLAYER_7,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[6].pBuffMat,
		NULL,
		&g_Player.aModel[6].NumMat,
		&g_Player.aModel[6].pMesh);

	D3DXLoadMeshFromX(PLAYER_8,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[7].pBuffMat,
		NULL,
		&g_Player.aModel[7].NumMat,
		&g_Player.aModel[7].pMesh);

	D3DXLoadMeshFromX(PLAYER_9,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[8].pBuffMat,
		NULL,
		&g_Player.aModel[8].NumMat,
		&g_Player.aModel[8].pMesh);

	D3DXLoadMeshFromX(PLAYER_10,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[9].pBuffMat,
		NULL,
		&g_Player.aModel[9].NumMat,
		&g_Player.aModel[9].pMesh);

	D3DXLoadMeshFromX(PLAYER_11,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[10].pBuffMat,
		NULL,
		&g_Player.aModel[10].NumMat,
		&g_Player.aModel[10].pMesh);

	D3DXLoadMeshFromX(PLAYER_12,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[11].pBuffMat,
		NULL,
		&g_Player.aModel[11].NumMat,
		&g_Player.aModel[11].pMesh);

	D3DXLoadMeshFromX(PLAYER_13,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[12].pBuffMat,
		NULL,
		&g_Player.aModel[12].NumMat,
		&g_Player.aModel[12].pMesh);

	D3DXLoadMeshFromX(PLAYER_14,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[13].pBuffMat,
		NULL,
		&g_Player.aModel[13].NumMat,
		&g_Player.aModel[13].pMesh);

	D3DXLoadMeshFromX(PLAYER_15,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[14].pBuffMat,
		NULL,
		&g_Player.aModel[14].NumMat,
		&g_Player.aModel[14].pMesh);

	for (int nCnt2 = 0; nCnt2 < MAX_PLAYERMODEL; nCnt2++)
	{
	//頂点数の取得
	nNumVtx = g_Player.aModel[nCnt2].pMesh->GetNumVertices();
	sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCnt2].pMesh->GetFVF());

		//頂点バッファのロック
		g_Player.aModel[nCnt2].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
		{//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (g_Player.vtxMin.x > vtx.x)
			{//Xの最小値の書き換え
				g_Player.vtxMin.x = vtx.x;
			}
			if (g_Player.vtxMin.z > vtx.z)
			{//Zの最小値の書き換え
				g_Player.vtxMin.z = vtx.z;
			}
			if (g_Player.vtxMax.x < vtx.x)
			{//Xの最小値の書き換え
				g_Player.vtxMax.x = vtx.x;
			}
			if (g_Player.vtxMax.z < vtx.z)
			{//Zの最小値の書き換え
				g_Player.vtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//サイズ分ポインタを進める
		}
		//頂点バッファのアンロック
		g_Player.aModel[nCnt2].pMesh->UnlockVertexBuffer();
	}

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTUER, &g_pTexturePlayer);

	//上半身
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].nIdxModel = -1;	//親：自分

										//下半身
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].nIdxModel = 0;	//親：上半身

										//顔
	g_Player.aModel[2].pos = D3DXVECTOR3(0.0f, 2.8f, 0.0f);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[2].nIdxModel = 0;	//親：上半身

										//二の腕右
	g_Player.aModel[3].pos = D3DXVECTOR3(-1.5f, 2.0f, -0.2f);
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[3].nIdxModel = 0;	//親：上半身

										//腕右
	g_Player.aModel[4].pos = D3DXVECTOR3(-3.7f, 1.8f, -0.2f);
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[4].nIdxModel = 3;	//親：二の腕

										//右手
	g_Player.aModel[5].pos = D3DXVECTOR3(-5.0f, 1.7f, -0.25f);
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[5].nIdxModel = 4;	//親：上半身

										//二の腕左
	g_Player.aModel[6].pos = D3DXVECTOR3(1.5f, 2.0f, -0.2f);
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[6].nIdxModel = 0;	//親：上半身

										//腕左
	g_Player.aModel[7].pos = D3DXVECTOR3(3.7f, 1.8f, -0.2f);
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[7].nIdxModel = 6;	//親：二の腕

										//左手
	g_Player.aModel[8].pos = D3DXVECTOR3(5.4f, 1.6f, -0.25f);
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[8].nIdxModel = 7;	//親：腕

										//右太もも
	g_Player.aModel[9].pos = D3DXVECTOR3(-0.8f, -1.5f, -1.0f);
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[9].nIdxModel = 1;	//親：下半身

										//右脹脛
	g_Player.aModel[10].pos = D3DXVECTOR3(-1.25f, -3.8f, -0.75f);
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[10].nIdxModel = 9;	//親：太もも

										//右足
	g_Player.aModel[11].pos = D3DXVECTOR3(-1.5f, -6.1f, -0.7f);
	g_Player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[11].nIdxModel = 10;	//親：脹脛

										//左太もも
	g_Player.aModel[12].pos = D3DXVECTOR3(0.8f, -1.6f, 0.0f);
	g_Player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[12].nIdxModel = 1;	//親：下半身

										//左脹脛
	g_Player.aModel[13].pos = D3DXVECTOR3(1.2f, -3.8f, -0.6f);
	g_Player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[13].nIdxModel = 12;	//親：太もも

										//左足
	g_Player.aModel[14].pos = D3DXVECTOR3(1.5f, -6.1f, -0.7f);
	g_Player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[14].nIdxModel = 13;	//親：脹脛


	// 位置・向き・色の初期設定
	g_Player.pos = D3DXVECTOR3(570.0f, 8.0f, -570.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	g_Player.nIdxShadow = SetShadow(g_Player.pos, g_Player.rot);
	g_bPlaying = true;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYERMODEL; nCnt++)
	{
		// メッシュの開放
		if (g_Player.aModel[nCnt].pMesh != NULL)
		{
			g_Player.aModel[nCnt].pMesh->Release();
			g_Player.aModel[nCnt].pMesh = NULL;
		}
		// マテリアルの開放
		if (g_Player.aModel[nCnt].pBuffMat != NULL)
		{
			g_Player.aModel[nCnt].pBuffMat->Release();
			g_Player.aModel[nCnt].pBuffMat = NULL;
		}
	}
	//テクスチャの初期化
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	Camera*pCamera = GetCamera();
	Obj*pObj = GetObj();
	FADE g_Fade = GetFade();
	g_Player.posOld = g_Player.pos;
	if (g_bPlaying == true)
	{
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_Player.rot.y = 0.0f + pCamera->rot.y;
			g_Player.move.x += sinf(D3DX_PI + pCamera->rot.y)*PLAYER_MOVR;
			g_Player.move.z += cosf(D3DX_PI + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.x += sinf(D3DX_PI + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.z += cosf(D3DX_PI + pCamera->rot.y)*PLAYER_MOVR;

		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_Player.rot.y = D3DX_PI + pCamera->rot.y;
			g_Player.move.x += sinf(0.0f + pCamera->rot.y)*PLAYER_MOVR;
			g_Player.move.z += cosf(0.0f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.x += sinf(0.0f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.z += cosf(0.0f + pCamera->rot.y)*PLAYER_MOVR;

		}
		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.rot.y = D3DX_PI * -0.5f + pCamera->rot.y;

			g_Player.move.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y)*PLAYER_MOVR;
			g_Player.move.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y)*PLAYER_MOVR;

			//g_Player.pos.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y)*PLAYER_MOVR;

		}
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.rot.y = D3DX_PI * 0.5f + pCamera->rot.y;

			g_Player.move.x += sinf(D3DX_PI * -0.5f + pCamera->rot.y)*PLAYER_MOVR;
			g_Player.move.z += cosf(D3DX_PI * -0.5f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.x += sinf(D3DX_PI * -0.5f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.z += cosf(D3DX_PI * -0.5f + pCamera->rot.y)*PLAYER_MOVR;

		}

		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{//左旋回
			g_Player.rot.y -= 0.5f;
		}
		if (GetKeyboardPress(DIK_RSHIFT) == true)
		{//左旋回
			g_Player.rot.y += 0.5f;
		}
		//位置更新
		g_Player.pos += g_Player.move;

		//減速
		g_Player.move.x += (0.0f - g_Player.move.x)*0.6f;
		g_Player.move.y += (0.0f - g_Player.move.y)*0.6f;
		g_Player.move.z += (0.0f - g_Player.move.z)*0.6f;


		//ステージのあたり判定
		CollisionStagePL();

		//中の壁とのあたり判定
		CollisionWall_WIDTH_PL(&g_Player.pos, &g_Player.posOld);
		CollisionWall_HEIDTH_PL(&g_Player.pos, &g_Player.posOld);

		//モデルとのあたり判定
		if (CollisionObj(&g_Player.pos, &g_Player.posOld, g_Player.vtxMin, g_Player.vtxMax) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				AddScore(2000);
				SetGameState(GAMESTATE_CLEAR);
			}
		}

		//敵とのあたり判定
		if (CollisionEnemy(g_Player.pos, g_Player.vtxMin, g_Player.vtxMax) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				SetGameState(GAMESTATE_OVER);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
		}

		CollisionDisPlay(&g_Player.pos, &g_Player.posOld, g_Player.vtxMin, g_Player.vtxMax);
		//影の設置
		SetPositionShadow(g_Player.nIdxShadow, g_Player.pos);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス
	D3DMATERIAL9 matDef;					//現在のマテリアルの保存用
	D3DXMATERIAL *pMat;						//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;

	//zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//プレイヤーの描画------------------------------------
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);


	for (int nCnt = 0; nCnt < MAX_PLAYERMODEL; nCnt++)
	{
		//親モデルのインデックスが"-1"
		if (g_Player.aModel[nCnt].nIdxModel == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aModel[0].mtxWorld;
		}

		//モデルの描画------------------------------------
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCnt].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCnt].rot.y, g_Player.aModel[nCnt].rot.x, g_Player.aModel[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCnt].pos.x, g_Player.aModel[nCnt].pos.y, g_Player.aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxTrans);

		//親のモデルと関連付け
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat <= (int)g_Player.aModel[nCnt].NumMat; nCntMat++)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePlayer);

			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// モデル(パーツ)の描画
			g_Player.aModel[nCnt].pMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}


	////モデル[1]の描画------------------------------------
	//// ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&g_Player.aModel[1].mtxWorld);

	//// 回転を反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[1].rot.y, g_Player.aModel[1].rot.x, g_Player.aModel[1].rot.z);
	//D3DXMatrixMultiply(&g_Player.aModel[1].mtxWorld, &g_Player.aModel[1].mtxWorld, &mtxRot);

	//// 移動を反映
	//D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[1].pos.x, g_Player.aModel[1].pos.y, g_Player.aModel[1].pos.z);
	//D3DXMatrixMultiply(&g_Player.aModel[1].mtxWorld, &g_Player.aModel[1].mtxWorld, &mtxTrans);

	////親のモデルと関連付け
	//D3DXMatrixMultiply(&g_Player.aModel[1].mtxWorld, &g_Player.aModel[1].mtxWorld, &g_Player.aModel[0].mtxWorld);

	//// ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[1].mtxWorld);

	//// 現在のマテリアルを取得
	//pDevice->GetMaterial(&matDef);

	//// マテリアルデータへのポインタを取得
	//pMat = (D3DXMATERIAL*)g_Player.aModel[1].pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat <= (int)g_Player.aModel[1].NumMat; nCntMat++)
	//{
	//	// テクスチャの設定
	//	pDevice->SetTexture(0, g_pTexturePlayer);

	//	// マテリアルの設定
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

	//	// モデル(パーツ)の描画
	//	g_Player.aModel[1].pMesh->DrawSubset(nCntMat);
	//}

	//// マテリアルをデフォルトに戻す
	//pDevice->SetMaterial(&matDef);

	//zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}
//=============================================================================
// モデルの取得
//=============================================================================
Player*GetPlayer(void)
{
	return &g_Player;
}
//=============================================================================
// ステージ1の辺り判定
//=============================================================================
void CollisionStagePL(void)
{
	float VecLine[4];		//あたり判定の計算結果
	D3DXVECTOR3 aPos[4];

	aPos[0] = D3DXVECTOR3(-40.0f, 0.0f, 40.0f);
	aPos[1] = D3DXVECTOR3(590.0f, 0.0f, 40.0f);
	aPos[2] = D3DXVECTOR3(590.0f, 0.0f, -590.0f);
	aPos[3] = D3DXVECTOR3(-40.0f, 0.0f, -590.0f);
	
	//上壁あたり判定--------------------------------------------------------------
	//ベクトル計算
	g_Player.VecA = aPos[0] - aPos[1];
	g_Player.VecC = g_Player.pos - aPos[0];

	//あたり判定計算
	VecLine[0] = (g_Player.VecA.z*g_Player.VecC.x) - (g_Player.VecA.x*g_Player.VecC.z);

	if (VecLine[0] >= 0)
	{//負だったら左側
		g_Player.pos.z = aPos[0].z + g_Player.vtxMin.z + 5.0f;
	}
	//下壁あたり判定--------------------------------------------------------------
	//ベクトル計算
	g_Player.VecA = aPos[2] - aPos[3];
	g_Player.VecC = g_Player.pos - aPos[2];

	//あたり判定計算
	VecLine[1] = (g_Player.VecA.z*g_Player.VecC.x) - (g_Player.VecA.x*g_Player.VecC.z);

	if (VecLine[1] >= 0)
	{//負だったら左側
		g_Player.pos.z = aPos[2].z + g_Player.vtxMax.z - 5.0f;
	}

	//右壁あたり判定--------------------------------------------------------------
	//ベクトル計算
	g_Player.VecA = aPos[1] - aPos[2];
	g_Player.VecC = g_Player.pos - aPos[1];

	//あたり判定計算
	VecLine[2] = (g_Player.VecA.z*g_Player.VecC.x) - (g_Player.VecA.x*g_Player.VecC.z);

	if (VecLine[2] >= 0)
	{//負だったら左側
		g_Player.pos.x = aPos[2].x + g_Player.vtxMax.x - 5.0f;
	}

	//左壁あたり判定--------------------------------------------------------------
	//ベクトル計算
	g_Player.VecA = aPos[3] - aPos[0];
	g_Player.VecC = g_Player.pos - aPos[3];

	//あたり判定計算
	VecLine[3] = (g_Player.VecA.z*g_Player.VecC.x) - (g_Player.VecA.x*g_Player.VecC.z);

	if (VecLine[3] >= 0)
	{//負だったら左側
		g_Player.pos.x = aPos[3].x + g_Player.vtxMin.x + 5.0f;
	}

}


//=============================================================================
//
// モデル処理 [Enemy.cpp]
// Author : 後閑　茜
//
//=============================================================================
#include "Enemy.h"
#include "input.h"
#include "shadow.h"
#include "Stage.h"
#include "Player.h"
#include "Wall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_TEXTUER " "
#define ENEMY_1 "data\\MODEL\\Enemy\\00_Body.x"		//体[0]

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;//テクスチャへのポインタ
Enemy g_Enemy[MAX_ENEMY];								//モデルの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//頂点数
	DWORD sizeFVF;						//頂点フォーマットのサイズ
	BYTE *pVtxBuff;						//頂点バッファのポインタ

	for (int nCnt1 = 0; nCnt1 < MAX_ENEMY; nCnt1++)
	{
		g_Enemy[nCnt1].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Enemy[nCnt1].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);

		g_Enemy[nCnt1].aModel.NumMat = 0;

		// Xファイルの読み込み
		D3DXLoadMeshFromX(ENEMY_1,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Enemy[nCnt1].aModel.pBuffMat,
			NULL,
			&g_Enemy[nCnt1].aModel.NumMat,
			&g_Enemy[nCnt1].aModel.pMesh);

		//頂点数の取得
		nNumVtx = g_Enemy[nCnt1].aModel.pMesh->GetNumVertices();
		sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCnt1].aModel.pMesh->GetFVF());

		//頂点バッファのロック
		g_Enemy[nCnt1].aModel.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCnt = 0; nCnt <= nNumVtx; nCnt++)
		{//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (g_Enemy[nCnt1].vtxMin.x > vtx.x)
			{//Xの最小値の書き換え
				g_Enemy[nCnt1].vtxMin.x = vtx.x;
			}
			if (g_Enemy[nCnt1].vtxMin.z > vtx.z)
			{//Zの最小値の書き換え
				g_Enemy[nCnt1].vtxMin.z = vtx.z;
			}
			if (g_Enemy[nCnt1].vtxMax.x < vtx.x)
			{//Xの最小値の書き換え
				g_Enemy[nCnt1].vtxMax.x = vtx.x;
			}
			if (g_Enemy[nCnt1].vtxMax.z < vtx.z)
			{//Zの最小値の書き換え
				g_Enemy[nCnt1].vtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//サイズ分ポインタを進める
		}
		//頂点バッファのアンロック
		g_Enemy[nCnt1].aModel.pMesh->UnlockVertexBuffer();

		//テクスチャの設定
		D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTUER, &g_pTextureEnemy);

		// 位置・向き・色の初期設定
		g_Enemy[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].VecA= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].VecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].nType = 0;
		g_Enemy[nCnt1].bUse = false;

		//上半身
		g_Enemy[nCnt1].aModel.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt1].aModel.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int nCnt2 = 0; nCnt2 < MAX_ENEMY; nCnt2++)
	{
		// メッシュの開放
		if (g_Enemy[nCnt2].aModel.pMesh != NULL)
		{
			g_Enemy[nCnt2].aModel.pMesh->Release();
			g_Enemy[nCnt2].aModel.pMesh = NULL;
		}
		// マテリアルの開放
		if (g_Enemy[nCnt2].aModel.pBuffMat != NULL)
		{
			g_Enemy[nCnt2].aModel.pBuffMat->Release();
			g_Enemy[nCnt2].aModel.pBuffMat = NULL;
		}
	}
	//テクスチャの初期化
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	Stage*pField;
	pField = GetStage();
	Player*pPlayer = GetPlayer();
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		g_Enemy[nCnt].posOld = g_Enemy[nCnt].pos;

		if (g_Enemy[nCnt].bUse == true)
		{
			if (g_Enemy[nCnt].nType == 0)
			{
				//前回の位置書き換え
				g_Enemy[nCnt].nCntMove += g_Enemy[nCnt].nChengeMove;
				g_Enemy[nCnt].pos.x += g_Enemy[nCnt].nChengeMove;

				if (CollisionWall_HEIDTH_ENE(&g_Enemy[nCnt].pos, g_Enemy[nCnt].pos, &g_Enemy[nCnt].posOld, &g_Enemy[nCnt].rot) == true)
				{
					g_Enemy[nCnt].nChengeMove *= -1.0f;
				}
			}

			//ステージのあたり判定
			CollisionStageEN();

			SetPositionShadow(g_Enemy[nCnt].nIdxShadow, g_Enemy[nCnt].pos);
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス
	D3DMATERIAL9 matDef;					//現在のマテリアルの保存用
	D3DXMATERIAL *pMat;						//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;

	//zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//プレイヤーの描画------------------------------------
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorld);

			//親モデルのインデックスが"-1"
			mtxParent = g_Enemy[nCntEnemy].mtxWorld;

			//モデルの描画------------------------------------
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].aModel.mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].aModel.rot.y, g_Enemy[nCntEnemy].aModel.rot.x, g_Enemy[nCntEnemy].aModel.rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel.mtxWorld, &g_Enemy[nCntEnemy].aModel.mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].aModel.pos.x, g_Enemy[nCntEnemy].aModel.pos.y, g_Enemy[nCntEnemy].aModel.pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel.mtxWorld, &g_Enemy[nCntEnemy].aModel.mtxWorld, &mtxTrans);

			//親のモデルと関連付け
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel.mtxWorld, &g_Enemy[nCntEnemy].aModel.mtxWorld, &mtxParent);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].aModel.mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Enemy[nCntEnemy].aModel.pBuffMat->GetBufferPointer();

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemy);


			for (int nCntMat = 0; nCntMat <= (int)g_Enemy[nCntEnemy].aModel.NumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// モデル(パーツ)の描画
				g_Enemy[nCntEnemy].aModel.pMesh->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
	//zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}
//=============================================================================
// モデルの取得
//=============================================================================
Enemy*GetEnemy(void)
{
	return &g_Enemy[0];
}

//=============================================================================
// モデルの設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float ChengeMove,int Type)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_Enemy[nCnt].bUse == false)
		{
			g_Enemy[nCnt].pos = pos;
			g_Enemy[nCnt].rot = rot;
			g_Enemy[nCnt].nChengeMove = ChengeMove;
			g_Enemy[nCnt].nType = Type;
			g_Enemy[nCnt].bUse = true;

			g_Enemy[nCnt].nIdxShadow = SetShadow(g_Enemy[nCnt].pos, g_Enemy[nCnt].rot);
			break;
		}
	}
}
//=============================================================================
// ステージ1の辺り判定
//=============================================================================
void CollisionStageEN(void)
{
	float VecLine[4];		//あたり判定の計算結果
	D3DXVECTOR3 aPos[4];

	aPos[0] = D3DXVECTOR3(-40.0f, 0.0f, 40.0f);
	aPos[1] = D3DXVECTOR3(590.0f, 0.0f, 40.0f);
	aPos[2] = D3DXVECTOR3(590.0f, 0.0f, -590.0f);
	aPos[3] = D3DXVECTOR3(-40.0f, 0.0f, -590.0f);

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_Enemy[nCnt].bUse == true)
		{
			//上壁あたり判定--------------------------------------------------------------
			//ベクトル計算
			g_Enemy[nCnt].VecA = aPos[0] - aPos[1];
			g_Enemy[nCnt].VecC = g_Enemy[nCnt].pos - aPos[0];


			//あたり判定計算
			VecLine[0] = (g_Enemy[nCnt].VecA.z*g_Enemy[nCnt].VecC.x) - (g_Enemy[nCnt].VecA.x*g_Enemy[nCnt].VecC.z);

			if (VecLine[0] >= 0)
			{//負だったら左側
				g_Enemy[nCnt].rot.y = 0.0f;
				g_Enemy[nCnt].nChengeMove *= -1.0f;

			}
			//下壁あたり判定--------------------------------------------------------------
			//ベクトル計算
			g_Enemy[nCnt].VecA = aPos[2] - aPos[3];
			g_Enemy[nCnt].VecC = g_Enemy[nCnt].pos - aPos[2];


			//あたり判定計算
			VecLine[1] = (g_Enemy[nCnt].VecA.z*g_Enemy[nCnt].VecC.x) - (g_Enemy[nCnt].VecA.x*g_Enemy[nCnt].VecC.z);

			if (VecLine[1] >= 0)
			{//負だったら左側
				g_Enemy[nCnt].rot.y = D3DX_PI;
				g_Enemy[nCnt].nChengeMove *= -1.0f;

			}

			//右壁あたり判定--------------------------------------------------------------
			//ベクトル計算
			g_Enemy[nCnt].VecA = aPos[1] - aPos[2];
			g_Enemy[nCnt].VecC = g_Enemy[nCnt].pos - aPos[1];


			//あたり判定計算
			VecLine[2] = (g_Enemy[nCnt].VecA.z*g_Enemy[nCnt].VecC.x) - (g_Enemy[nCnt].VecA.x*g_Enemy[nCnt].VecC.z);

			if (VecLine[2] >= 0)
			{//負だったら左側
				g_Enemy[nCnt].rot.y = D3DX_PI*0.5f;
				g_Enemy[nCnt].nChengeMove *= -1.0f;

			}
			//左壁あたり判定--------------------------------------------------------------
			//ベクトル計算
			g_Enemy[nCnt].VecA = aPos[3] - aPos[0];
			g_Enemy[nCnt].VecC = g_Enemy[nCnt].pos - aPos[3];


			//あたり判定計算
			VecLine[3] = (g_Enemy[nCnt].VecA.z*g_Enemy[nCnt].VecC.x) - (g_Enemy[nCnt].VecA.x*g_Enemy[nCnt].VecC.z);

			if (VecLine[3] >= 0)
			{//負だったら左側
				g_Enemy[nCnt].rot.y = D3DX_PI*0.5f;
				g_Enemy[nCnt].nChengeMove *= -1.0f;

			}
		}
	}
}
//=============================================================================
// 敵とプレイヤーのあたり判定
//=============================================================================
bool CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	bool bLand = false;

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_Enemy[nCnt].bUse == true)
		{
			bLand = false;

			if (g_Enemy[nCnt].pos.x + g_Enemy[nCnt].vtxMax.x > pos.x + vtxMax.x &&
				g_Enemy[nCnt].pos.x + g_Enemy[nCnt].vtxMin.x < pos.x + vtxMin.x)
			{
				if (g_Enemy[nCnt].pos.z + g_Enemy[nCnt].vtxMax.z > pos.z + vtxMax.z &&
					g_Enemy[nCnt].pos.z + g_Enemy[nCnt].vtxMin.z < pos.z + vtxMin.z)
				{
					bLand = true;
					break;
				}
			}
		}
	}
	return bLand;
}
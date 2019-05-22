//=============================================================================
//
// ブロック処理 [block.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "block.h"			// ブロック
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "sound.h"			// サウンド
#include "game.h"			// ゲーム
#include "input.h"			// 入力
#include "font.h"			// フォント
#include "camera.h"			// カメラ
#include "meshField.h"		// メッシュフィールド
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME_0	"data\\MODEL\\Object\\box.x"		// 通常ブロック
#define MODEL_NAME_1	"data\\MODEL\\Object\\PBrock.x"		// 壊れるブロック
#define MODEL_NAME_2	"data\\MODEL\\Object\\rock.x"		// 木
#define MODEL_NAME_3	"data\\MODEL\\Object\\obj_tree.x"	// 背景用木
#define MODEL_NAME_4	"data\\MODEL\\Object\\Airblock.x"	// 空中床(正式採用視野)
#define MODEL_NAME_5	"data\\MODEL\\Object\\Airblock2.x"	// 空中床
#define MODEL_NAME_6	"data\\MODEL\\Object\\Slipblock.x"	// 滑る床(調整中)
#define MODEL_NAME_7	"data\\MODEL\\Object\\log.x"		// 丸太(調整中)
#define MODEL_NAME_8	"data\\MODEL\\Object\\seesaw.x"		// シーソー(調整中)
#define MODEL_NAME_9	"data\\MODEL\\Object\\ivy.x"		// ツタ
#define MODEL_NAME_10	"data\\MODEL\\Object\\obj_ivy.x"	// 背景用ツタ
#define MODEL_NAME_11	"data\\MODEL\\Object\\box3.x"		// 通常ブロック4つ分
#define MODEL_NAME_12	"data\\MODEL\\Object\\Wood.x"		// 背景木2
#define MODEL_NAME_13	"data\\MODEL\\Object\\Wood2.x"		// 背景木3
#define MODEL_NAME_14	"data\\MODEL\\Object\\Wood3.x"		// 背景木4
#define MODEL_NAME_15	"data\\MODEL\\Object\\Wood4.x"		// 背景木5
#define MODEL_NAME_16	"data\\MODEL\\Object\\grass.x"		// 草
#define MODEL_NAME_17	"data\\MODEL\\Object\\goal.x"		// ゴール
//#define MODEL_NAME_11	"data\\MODEL\\Object\\stone.x"		// 岩(?)
//#define MODEL_NAME_12	"data\\MODEL\\Object\\rock.x"		// 岩
//#define MODEL_NAME_13	"data\\MODEL\\Object\\rock2.x"		// 岩2
//#define MODEL_NAME_14	"data\\MODEL\\Object\\rock3.x"		// 岩3
//#define MODEL_NAME_15	"data\\MODEL\\Object\\rock4.x"		// 岩4
//#define MODEL_NAME_16	"data\\MODEL\\Object\\rock5.x"		// 岩5

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		*CBlock::m_pTexture[m_MaxModel] = {};		// テクスチャ情報へのポインタ
LPD3DXMESH				CBlock::m_pMesh[m_MaxModel] = {};			// メッシュ情報へのポインタ
LPD3DXBUFFER			CBlock::m_pBuffMat[m_MaxModel] = {};		// マテリアル情報へのポインタ
DWORD					CBlock::m_nNumMat[m_MaxModel] = {};			// マテリアル情報の数

//=============================================================================
// コンストラクタ									(public)	*** CBlock ***
//=============================================================================
CBlock::CBlock() : CSceneX(CScene::PRIORITY_3, CScene::OBJTYPE_BLOCK)
{
	m_modelType = MODELTYPE_BOX_R;
	m_colType = COLTYPE_NONE;
	m_colHitType = COLTYPE_NONE;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bHit[0] = false;
	m_bHit[1] = false;
	m_bHit[2] = false;
	m_bHit[3] = false;

	m_shadowHeight = 0.0f;
}

//=============================================================================
// デストラクタ										(public)	*** CBlock ***
//=============================================================================
CBlock::~CBlock()
{

}

//=============================================================================
// ロード処理							(public)	*** CBullet ***
//=============================================================================
HRESULT CBlock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		// デバイス取得

	char cName[256];

	for (int nCntParnet = 0; nCntParnet < m_MaxModel; nCntParnet++)
	{
		switch (nCntParnet)
		{
		case MODELTYPE_BOX_R:
			wsprintf(cName, MODEL_NAME_0);
			break;
		case MODELTYPE_BOX_W_1:
			wsprintf(cName, MODEL_NAME_2);
			break;
		case MODELTYPE_BOX_W_2:
			wsprintf(cName, MODEL_NAME_3);
			break;
		case MODELTYPE_SKY:
			wsprintf(cName, MODEL_NAME_4);
			break;
		case MODELTYPE_ICE:
			wsprintf(cName, MODEL_NAME_6);
			break;
		case MODELTYPE_LOG:
			wsprintf(cName, MODEL_NAME_7);
			break;
		case MODELTYPE_SEESAW:
			wsprintf(cName, MODEL_NAME_8);
			break;
		case MODELTYPE_IVY:
			wsprintf(cName, MODEL_NAME_9);
			break;
		case MODELTYPE_IVY_2:
			wsprintf(cName, MODEL_NAME_10);
			break;
		case MODELTYPE_BOX_W_3:
			wsprintf(cName, MODEL_NAME_11);
			break;
		case MODELTYPE_TREE:
			wsprintf(cName, MODEL_NAME_12);
			break;
		case MODELTYPE_TREE2:
			wsprintf(cName, MODEL_NAME_13);
			break;
		case MODELTYPE_TREE3:
			wsprintf(cName, MODEL_NAME_14);
			break;
		case MODELTYPE_TREE4:
			wsprintf(cName, MODEL_NAME_15);
			break;
		case MODELTYPE_GRASS:
			wsprintf(cName, MODEL_NAME_16);
			break;
		case MODELTYPE_GOAL:
			wsprintf(cName, MODEL_NAME_17);
			break;
		case MODELTYPE_PBROCK:
			wsprintf(cName, MODEL_NAME_1);
			break;
		default:
			wsprintf(cName, MODEL_NAME_0);
			break;
		}

		// Xファイルの読み込み
		D3DXLoadMeshFromX(cName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[nCntParnet], NULL, &m_nNumMat[nCntParnet], &m_pMesh[nCntParnet]);

		D3DXMATERIAL *pmat;							// マテリアルデータへのポインタ
		D3DMATERIAL9 *matDef;						// 現在のマテリアル保存用
		pmat = (D3DXMATERIAL*)m_pBuffMat[nCntParnet]->GetBufferPointer();
		matDef = new D3DMATERIAL9[m_nNumMat[nCntParnet]];
		m_pTexture[nCntParnet] = new LPDIRECT3DTEXTURE9[m_nNumMat[nCntParnet]];

		for (DWORD tex = 0; tex < m_nNumMat[nCntParnet]; tex++)
		{// カウント
			matDef[tex] = pmat[tex].MatD3D;
			matDef[tex].Ambient = matDef[tex].Diffuse;
			m_pTexture[nCntParnet][tex] = NULL;
			if (pmat[tex].pTextureFilename != NULL &&
				lstrlen(pmat[tex].pTextureFilename) > 0)
			{// テクスチャを使用している
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					pmat[tex].pTextureFilename,
					&m_pTexture[nCntParnet][tex])))
				{
					//MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
				}
			}
		}

		delete[] matDef;
		matDef = NULL;
	}

	return S_OK;
}

//=============================================================================
// アンロード処理								(public)	*** CBullet ***
//=============================================================================
void CBlock::Unload(void)
{
	for (int nCntParnet = 0; nCntParnet < m_MaxModel; nCntParnet++)
	{
		// テクスチャの破棄
		for (DWORD tex = 0; tex < m_nNumMat[nCntParnet]; tex++)
		{// カウント
			if (m_pTexture[nCntParnet][tex] != NULL)
			{// NULL以外の場合
				m_pTexture[nCntParnet][tex]->Release();		// 解放
				m_pTexture[nCntParnet][tex] = NULL;			// NULLへ
			}
		}

		delete[] m_pTexture[nCntParnet];
		m_pTexture[nCntParnet] = NULL;

		// マテリアルの開放
		if (m_pBuffMat[nCntParnet] != NULL)
		{// NULL以外の場合
			m_pBuffMat[nCntParnet]->Release();				// 解放
			m_pBuffMat[nCntParnet] = NULL;					// NULLへ
		}

		// マテリアルの開放
		if (m_pMesh[nCntParnet] != NULL)
		{// NULL以外の場合
			m_pMesh[nCntParnet]->Release();					// 解放
			m_pMesh[nCntParnet] = NULL;						// NULLへ
		}

		m_nNumMat[nCntParnet] = 0;				// 初期化
	}
}

//=============================================================================
// 確保処理											(public)	*** CBlock ***
//=============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, MODELTYPE modelType, COLTYPE coltype)
{
	CBlock *pBlock = NULL;			// ポインタ

	if (pBlock == NULL)
	{// NULLの場合
		pBlock = new CBlock;			// メモリ確保

		if (pBlock != NULL)
		{// NULL以外の場合
			pBlock->Init(pos, modelType, coltype);		// 初期化処理
		}
	}

	return pBlock;			// 値を返す
}

//=============================================================================
// 初期化処理										(public)	*** CBlock ***
//=============================================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, MODELTYPE modelType, COLTYPE coltype)
{
	CSceneX::SetInitAll(m_pTexture[modelType], m_pMesh[modelType], m_pBuffMat[modelType], m_nNumMat[modelType], pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSceneX::Init();
	CSceneX::Setpos(CSceneX::Getpos() + D3DXVECTOR3(0.0f, -CSceneX::Getsize(1).y, 0.0f));

	if (coltype == COLTYPE_FALL)
	{
		CSceneX::Setrot(CSceneX::Getrot() + D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f));
	}
	else if (coltype == COLTYPE_SEESAW)
	{
		CSceneX::Setrot(D3DXVECTOR3(0.0f, 0.0f, 0.5f));
	}
	else if (coltype == COLTYPE_NONE)
	{
		if (modelType == MODELTYPE_BOX_W_2 || modelType == MODELTYPE_IVY_2 || (MODELTYPE_TREE <= modelType && modelType <= MODELTYPE_GRASS))
		{
			CSceneX::Setrot(D3DXVECTOR3(0.0f, (-314.0f + (float)(rand() % 628)) * 0.01f, 0.0f));
		}
	}

	m_modelType = modelType;
	m_colType = coltype;

	return S_OK;
}

//=============================================================================
// 終了処理											(public)	*** CBlock ***
//=============================================================================
void CBlock::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理											(public)	*** CBlock ***
//=============================================================================
void CBlock::Update(void)
{
	D3DXVECTOR3 posVDest = CManager::GetCamera()->GetPosVDest();	// 視点取得
	CManager::MODE pMode = CManager::GetMode();

	m_bHit[0] = false;
	m_bHit[1] = false;
	m_bHit[2] = false;
	m_bHit[3] = false;

	D3DXVECTOR3 pos = CSceneX::Getpos();
	D3DXVECTOR3 rot = CSceneX::Getrot();
	D3DXVECTOR3 sizeMax = CSceneX::Getsize(0);
	D3DXVECTOR3 sizeMin = CSceneX::Getsize(1);

	int nMeshNum = 0;
	bool bMesh = false;

	if (pMode == CManager::MODE_GAME)
	{

		for (int nCount = 0; nCount < CGame::m_MeshFieldMax; nCount++)
		{
			if (CGame::GetMeshField(nCount) != NULL)
			{
				if (CGame::GetMeshField(nCount)->ColInMesh(pos + sizeMax))
				{
					nMeshNum = nCount;
					bMesh = true;
					break;
				}
				else if (CGame::GetMeshField(nCount)->ColInMesh(pos))
				{
					nMeshNum = nCount;
					bMesh = true;
					break;
				}
				else if (CGame::GetMeshField(nCount)->ColInMesh(pos + sizeMin))
				{
					nMeshNum = nCount;
					bMesh = true;
					break;
				}
			}
		}

		float fHeight = CGame::GetMeshField(nMeshNum)->GetHeight(pos);

		m_posOld = pos;

		pos += m_move;

		CScene *pScene = CScene::GetScene(CScene::PRIORITY_3);
		CScene *pSceneNext = NULL;

		while (pScene != NULL)
		{
			pSceneNext = pScene->GetSceneNext();
			if (pScene != this && pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
			{
				CBlock *pBlock = (CBlock*)pScene;
				if (pBlock->OtherBlockCollision(&pos, &m_posOld, &m_move, CSceneX::Getsize(0), CSceneX::Getsize(1)))
				{
					if (m_move.x != 0.0f)
						pBlock->Setpos(pBlock->Getpos() + m_move);
				}
			}
			pScene = pSceneNext;
		}

		if (m_colType == COLTYPE_FALL)
		{
			if (rot.z <= D3DX_PI * 0.3f)
			{
				if (0.0f < rot.z)
				{
					rot.z += -0.03f;
				}
				else
				{
					rot.z = 0.0f;
				}
			}
			else
			{
				if (rot.z < D3DX_PI * 0.5f)
				{
					rot.z += 0.003f;
				}
				else
				{
					rot.z = D3DX_PI * 0.5f;
				}
			}
		}

		if (pos.y + sizeMin.y < fHeight && bMesh == true)
		{
			pos.y = fHeight - sizeMin.y;
			m_move.y = 0.0f;
		}

		if ((fHeight < pos.y + sizeMin.y || bMesh == false) && m_colType == COLTYPE_PUSH)
		{
			m_move.y -= 0.7f;
		}
	}

	m_move.x = 0.0f;

	CSceneX::Setpos(pos);
	CSceneX::Setrot(rot);

	if (pos.y < -100.0f || pos.x + sizeMax.x < posVDest.x - 800.0f)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理											(public)	*** CBlock ***
//=============================================================================
void CBlock::Draw(void)
{
	CSceneX::Draw();
	CShadow::SetShadow(CSceneX::GetmtxWorld(), m_pMesh[m_modelType], m_nNumMat[m_modelType], D3DXVECTOR3(CSceneX::Getpos().x, m_shadowHeight + 1.0f, CSceneX::Getpos().y));
}

//=============================================================================
// 当たり判定処理											(public)	*** CBlock ***
//=============================================================================
void CBlock::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, float *fDownSpeed, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	m_bHit[0] = false;
	m_bHit[1] = false;
	m_bHit[2] = false;
	m_bHit[3] = false;

	//bool bLand[4] = { false };
	bool bHit = false;

	D3DXVECTOR3 BlockPos = CSceneX::Getpos();
	D3DXVECTOR3 BlockSizeMax = CSceneX::Getsize(0);
	D3DXVECTOR3 BlockSizeMin = CSceneX::Getsize(1);

	if (m_colType != COLTYPE_NONE)
	{
		if (m_colType != COLTYPE_SEESAW && m_colType != COLTYPE_CLIMB && m_colType != COLTYPE_FALL && m_colType != COLTYPE_WALLJUMP)
		{
			if ((BlockPos.x + BlockSizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.x))
			{// X範囲確認
				if ((pos->y + sizeMin.y) <= (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMax.y) <= (posOld->y + sizeMin.y))
				{// 上からの当たり判定
					m_bHit[0] = true;
					bHit = true;

					pos->y = BlockPos.y + BlockSizeMax.y + (-sizeMin.y);
					move->y = 0.0f;

					switch (m_colType)
					{
					case COLTYPE_BOX:
					case COLTYPE_PUSH:
					case COLTYPE_BREAK:
						break;
					case COLTYPE_SKY:
						break;
					case COLTYPE_ICE:
						break;
					}
				}
				else if ((BlockPos.y + BlockSizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (BlockPos.y + BlockSizeMin.y))
				{// 下からの当たり判定
					if (m_colType != COLTYPE_SKY)
					{
						m_bHit[1] = true;
						bHit = true;

						pos->y = BlockPos.y + BlockSizeMin.y + (-sizeMax.y);
						move->y = 0.0f;
					}
				}
			}
			if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y))
			{// Y範囲確認
				if ((BlockPos.x + BlockSizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (BlockPos.x + BlockSizeMin.x))
				{// 左からの当たり判定
					m_bHit[2] = true;
					bHit = true;

					if (m_colType != COLTYPE_SKY)
					{
						pos->x = BlockPos.x + BlockSizeMin.x + (-sizeMax.x);
					}

					move->x -= move->x / 9;

					switch (m_colType)
					{
					case COLTYPE_BOX:
						break;
					case COLTYPE_PUSH:
						pos->x -= 0.1f;
						m_move.x = move->x;
						break;
					case COLTYPE_BREAK:
						break;
					case COLTYPE_SKY:
						break;
					case COLTYPE_ICE:
						break;
					}
				}
				else if ((pos->x + sizeMin.x) <= (BlockPos.x + BlockSizeMax.x) && (BlockPos.x + BlockSizeMax.x) <= (posOld->x + sizeMin.x))
				{// 右からの当たり判定
					m_bHit[3] = true;
					bHit = true;

					if (m_colType != COLTYPE_SKY)
					{
						pos->x = BlockPos.x + BlockSizeMax.x + (-sizeMin.x);
					}

					move->x -= move->x / 9;

					switch (m_colType)
					{
					case COLTYPE_BOX:
						break;
					case COLTYPE_PUSH:
						pos->x += 0.1f;
						m_move.x = move->x;
						break;
					case COLTYPE_BREAK:
						break;
					case COLTYPE_SKY:
						break;
					case COLTYPE_ICE:
						break;
					}
				}
			}
		}
		else
		{
			if (m_colType == COLTYPE_FALL)
			{
				if ((BlockPos.x + BlockSizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.x))
				{// X範囲確認
					if ((pos->y + sizeMin.y) <= (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMax.y) <= (posOld->y + sizeMin.y))
					{// 上からの当たり判定
						m_bHit[0] = true;
						bHit = true;

						pos->y = BlockPos.y + BlockSizeMax.y + (-sizeMin.y);
						move->y = 0.0f;
					}
					else if ((BlockPos.y + BlockSizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (BlockPos.y + BlockSizeMin.y))
					{// 下からの当たり判定
						if (m_colType != COLTYPE_SKY)
						{
							m_bHit[1] = true;
							bHit = true;

							pos->y = BlockPos.y + BlockSizeMin.y + (-sizeMax.y);
							move->y = 0.0f;
						}
					}
				}
				if (CSceneX::Getrot().z == 0.0f)
				{
					if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y))
					{// Y範囲確認
						if ((BlockPos.x + BlockSizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (BlockPos.x + BlockSizeMin.x))
						{// 左からの当たり判定
							m_bHit[2] = true;
							bHit = true;

							pos->x = BlockPos.x + BlockSizeMin.x + (-sizeMax.x);
							move->x /= 2;
						}
						else if ((pos->x + sizeMin.x) <= (BlockPos.x + BlockSizeMax.x) && (BlockPos.x + BlockSizeMax.x) <= (posOld->x + sizeMin.x))
						{// 右からの当たり判定
							m_bHit[3] = true;
							bHit = true;

							pos->x = BlockPos.x + BlockSizeMax.x + (-sizeMin.x);
							move->x /= 2;
						}
					}
				}
				else
				{
					if ((pos->y + sizeMax.y) < (BlockPos.y + BlockSizeMax.y) + 100.0f)
					{// Y範囲確認
						if ((BlockPos.x + BlockSizeMin.x - BlockSizeMax.y) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (BlockPos.x + BlockSizeMin.x - BlockSizeMax.y))
						{// 左からの当たり判定
							m_bHit[2] = true;
							bHit = true;

							pos->x = BlockPos.x + BlockSizeMin.x - BlockSizeMax.y + (-sizeMax.x);
							move->x /= 2;
						}
						else if ((pos->x + sizeMin.x) <= (BlockPos.x + BlockSizeMax.x) && (BlockPos.x + BlockSizeMax.x) <= (posOld->x + sizeMin.x))
						{// 右からの当たり判定
							m_bHit[3] = true;
							bHit = true;
						}
					}
				}
			}
			else if (m_colType == COLTYPE_SEESAW)
			{
				CFont *pFont = CRenderer::GetFont(CFont::FONTNUM_TEST);

				D3DXVECTOR3 VtxPos[6];
				float frot;
				frot = -atan2f(BlockSizeMin.x + BlockPos.x, 0.0f);

				VtxPos[0].x = BlockPos.x + sinf(frot + CSceneX::Getrot().z) * ((-BlockSizeMin.x + BlockPos.x - BlockPos.x)* 1.0f);
				VtxPos[0].y = cosf(frot + CSceneX::Getrot().z) * -((-BlockSizeMin.x + BlockPos.x - BlockPos.x) * 1.0f);
				VtxPos[0].z = BlockSizeMax.z;
				VtxPos[3].x = BlockPos.x + sinf(frot + CSceneX::Getrot().z) * ((-BlockSizeMin.x + BlockPos.x - BlockPos.x) * 1.0f);
				VtxPos[3].y = cosf(frot + CSceneX::Getrot().z) * -((-BlockSizeMin.x + BlockPos.x - BlockPos.x) * 1.0f);
				VtxPos[3].z = BlockSizeMin.z;

				VtxPos[1].x = BlockPos.x;
				VtxPos[1].y = 0.0f;
				VtxPos[1].z = BlockSizeMax.z;
				VtxPos[4].x = BlockPos.x;
				VtxPos[4].y = 0.0f;
				VtxPos[4].z = BlockSizeMin.z;

				frot = -atan2f(BlockSizeMax.x - BlockPos.x, 0.0f);

				VtxPos[2].x = BlockPos.x + sinf(frot + CSceneX::Getrot().z) * (BlockSizeMax.x + BlockPos.x - BlockPos.x) * 1.0f;
				VtxPos[2].y = cosf(frot + CSceneX::Getrot().z) * -(BlockSizeMax.x + BlockPos.x - BlockPos.x) * 1.0f;
				VtxPos[2].z = BlockSizeMax.z;
				VtxPos[5].x = BlockPos.x + sinf(frot + CSceneX::Getrot().z) * ((BlockSizeMax.x + BlockPos.x - BlockPos.x) * 1.0f);
				VtxPos[5].y = cosf(frot + CSceneX::Getrot().z) * -(BlockSizeMax.x + BlockPos.x - BlockPos.x) * 1.0f;
				VtxPos[5].z = BlockSizeMin.z;

				pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f\n", (BlockSizeMax.x + BlockPos.x - BlockPos.x));
				pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f\n", (-BlockSizeMin.x + BlockPos.x - BlockPos.x));

				pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f, %.2f, %.2f\n", VtxPos[0].x, VtxPos[0].y, VtxPos[0].z);
				pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f, %.2f, %.2f\n\n", VtxPos[3].x, VtxPos[3].y, VtxPos[3].z);

				pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f, %.2f, %.2f\n", VtxPos[1].x, VtxPos[1].y, VtxPos[1].z);
				pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f, %.2f, %.2f\n\n", VtxPos[4].x, VtxPos[4].y, VtxPos[4].z);

				pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f, %.2f, %.2f\n", VtxPos[2].x, VtxPos[2].y, VtxPos[2].z);
				pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f, %.2f, %.2f\n\n", VtxPos[5].x, VtxPos[5].y, VtxPos[5].z);

				D3DXVECTOR3 vecA, vecC;

				// ベクトル計算
				vecA = VtxPos[0] - VtxPos[3];
				vecC = *pos - VtxPos[3];

				if (0 <= ((vecA.z * vecC.x) - (vecA.x * vecC.z)))
				{// 範囲内（右側）にいることを確認
				 // ベクトル計算
					vecA = VtxPos[5] - VtxPos[2];
					vecC = *pos - VtxPos[2];

					if (0 <= ((vecA.z * vecC.x) - (vecA.x * vecC.z)))
					{// 範囲内（右側）にいることを確認
					 // ベクトル計算
						vecA = VtxPos[1] - VtxPos[4];
						vecC = *pos - VtxPos[4];

						//pFont->SetMessage(CFont::SETTYPE_ADD, "true\n");

						if (0 <= ((vecA.z * vecC.x) - (vecA.x * vecC.z)))
						{// 範囲内（右側）にいることを確認
						 //pFont->SetMessage(CFont::SETTYPE_ADD, "right\n");
							bHit = true;

							D3DXVECTOR3 nor, vec[2];

							//
							vec[0] = VtxPos[1] - VtxPos[4];
							vec[1] = VtxPos[5] - VtxPos[4];

							// 内積計算
							D3DXVec3Cross(&nor, &vec[0], &vec[1]);
							// 正規化
							D3DXVec3Normalize(&nor, &nor);

							// ベクトル計算
							D3DXVECTOR3 vecP;
							float fHeight, fHeightOld;

							// 高さ計算
							vecP = *pos - VtxPos[4];
							fHeight = (((nor.x * vecP.x) + (nor.z * vecP.z)) / -nor.y);

							vecP = *posOld - VtxPos[4];
							fHeightOld = (((nor.x * vecP.x) + (nor.z * vecP.z)) / -nor.y);

							if ((pos->y + sizeMin.y) < (fHeight + BlockSizeMax.y + BlockPos.y/*- sizeMin.y*/) /*&& (fHeightOld - sizeMin.y) <= (posOld->y + sizeMin.y)*/)
							{// 上からの当たり判定
								m_bHit[0] = true;

								pos->y = fHeight + (-sizeMin.y) + BlockSizeMax.y + BlockPos.y;
								move->y = 0.0f;

								//pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f\n", fHeight);

								if (0.0f < CSceneX::Getrot().z)
								{
									float fDistance = (pos->x - BlockPos.x) / ((BlockPos.x + BlockSizeMin.x) - BlockPos.x);

									CSceneX::Setrot(CSceneX::Getrot() + D3DXVECTOR3(0.0f, 0.0f, -0.008f * -fDistance));
								}
							}
						}
						else
						{
							//pFont->SetMessage(CFont::SETTYPE_ADD, "left\n");
							bHit = true;

							// ベクトル計算
							D3DXVECTOR3 vecP = *pos - VtxPos[1];
							float fHeight;

							D3DXVECTOR3 nor, vec[2];

							//
							vec[0] = VtxPos[4] - VtxPos[1];
							vec[1] = VtxPos[0] - VtxPos[1];

							// 内積計算
							D3DXVec3Cross(&nor, &vec[0], &vec[1]);
							// 正規化
							D3DXVec3Normalize(&nor, &nor);

							// 高さ計算
							fHeight = (((nor.x * vecP.x) + (nor.z * vecP.z)) / -nor.y);

							if ((pos->y + sizeMin.y) < (fHeight + BlockSizeMax.y + BlockPos.y)/* && (fHeight) <= (posOld->y + sizeMin.y)*/)
							{// 上からの当たり判定
								m_bHit[0] = true;

								pos->y = fHeight + (-sizeMin.y) + BlockSizeMax.y + BlockPos.y;
								move->y = 0.0f;

								//pFont->SetMessage(CFont::SETTYPE_ADD, "%.2f\n", fHeight);

								/*if (CSceneX::Getrot().z < 0.3f)
								{
								float fDistance = (pos->x - BlockPos.x) / ((BlockPos.x + BlockSizeMin.x) - BlockPos.x);

								CSceneX::Setrot(CSceneX::Getrot() + D3DXVECTOR3(0.0f, 0.0f, 0.005f * fDistance));
								}*/
							}
						}
					}
				}

				/*
				if ((BlockPos.x + BlockSizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.x))
				{// X範囲確認
				if ((pos->y + sizeMin.y) <= (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMax.y) <= (posOld->y + sizeMin.y))
				{// 上からの当たり判定
				m_bHit = true;

				pos->y = BlockPos.y + BlockSizeMax.y + (-sizeMin.y);
				move->y = 0.0f;

				if (pos->x < BlockPos.x && CSceneX::Getrot().z < 0.3f)
				{
				float fDistance = (pos->x - BlockPos.x) / ((BlockPos.x + BlockSizeMin.x) - BlockPos.x);

				CSceneX::Setrot(CSceneX::Getrot() + D3DXVECTOR3(0.0f, 0.0f, 0.005f * fDistance));
				}
				else if (BlockPos.x < pos->x && -0.3f < CSceneX::Getrot().z)
				{
				float fDistance = (pos->x - BlockPos.x) / ((BlockPos.x + BlockSizeMin.x) - BlockPos.x);

				CSceneX::Setrot(CSceneX::Getrot() + D3DXVECTOR3(0.0f, 0.0f, -0.005f * -fDistance));
				}
				}
				else if ((BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) < (BlockPos.y + BlockSizeMin.y))
				{// 下からの当たり判定
				m_bHit = true;

				pos->y = BlockPos.y + BlockSizeMin.y + (-sizeMax.y);
				move->y = 0.0f;
				}
				}
				*/

				if (m_bHit == false)
				{
					D3DXVECTOR3 RL;

					if (pos->x < BlockPos.x) RL = VtxPos[3];
					else RL = VtxPos[5];

					if ((pos->y + sizeMin.y) < (RL.y + BlockSizeMax.y + BlockPos.y))
					{// Y範囲確認
						if ((VtxPos[3].x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (VtxPos[3].x))
						{// 左からの当たり判定
							m_bHit[2] = true;
							bHit = true;

							pos->x = VtxPos[3].x + (-sizeMax.x);
							move->x = 0.0f;
						}
						else if ((pos->x + sizeMin.x) <= (VtxPos[5].x) && (VtxPos[5].x) <= (posOld->x + sizeMin.x))
						{// 右からの当たり判定
							m_bHit[3] = true;
							bHit = true;

							pos->x = VtxPos[5].x + (-sizeMin.x);
							move->x = 0.0f;
						}
					}
				}
			}
			else if (m_colType == COLTYPE_CLIMB)
			{
				if ((BlockPos.x + BlockSizeMin.x) <= (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) <= (BlockPos.x + BlockSizeMax.x))
				{// X範囲確認
					if ((pos->y + sizeMin.y) <= (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMax.y) <= (posOld->y + sizeMin.y))
					{// 上からの当たり判定
						m_bHit[0] = true;
						bHit = true;

						pos->y = BlockPos.y + BlockSizeMax.y + (-sizeMin.y);
						move->y = 0.0f;

					}
					else if ((BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) < (BlockPos.y + BlockSizeMin.y))
					{// 下からの当たり判定
						m_bHit[1] = true;
						bHit = true;

						pos->y = BlockPos.y + BlockSizeMin.y + (-sizeMax.y);
						move->y = 0.0f;
					}
				}

				if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) <= (pos->y + sizeMax.y))
				{// Y範囲確認
					if ((BlockPos.x + BlockSizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (BlockPos.x + BlockSizeMin.x))
					{// 左からの当たり判定
						m_bHit[2] = true;
						bHit = true;

						pos->x = BlockPos.x + BlockSizeMin.x + (-sizeMax.x);
						move->x = 0.0f;
					}
					else if ((pos->x + sizeMin.x) <= (BlockPos.x + BlockSizeMax.x) && (BlockPos.x + BlockSizeMax.x) <= (posOld->x + sizeMin.x))
					{// 右からの当たり判定
						m_bHit[3] = true;
						bHit = true;

						pos->x = BlockPos.x + BlockSizeMax.x + (-sizeMin.x);
						move->x = 0.0f;
					}
				}
			}
			else if (m_colType == COLTYPE_WALLJUMP)
			{
				if ((BlockPos.x + BlockSizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.x))
				{// X範囲確認
					if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMax.y) < (posOld->y + sizeMin.y))
					{// 上からの当たり判定
						m_bHit[0] = true;
						bHit = true;

						pos->y = BlockPos.y + BlockSizeMax.y + (-sizeMin.y + 0.0001f);
						move->y = 0.0f;

					}
					else if ((BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) < (BlockPos.y + BlockSizeMin.y))
					{// 下からの当たり判定
						m_bHit[1] = true;
						bHit = true;

						pos->y = BlockPos.y + BlockSizeMin.y + (-sizeMax.y);
						move->y = 0.0f;
					}
				}

				if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) <= (pos->y + sizeMax.y))
				{// Y範囲確認
					if ((BlockPos.x + BlockSizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (BlockPos.x + BlockSizeMin.x))
					{// 左からの当たり判定
						m_bHit[2] = true;
						bHit = true;

						pos->x = BlockPos.x + BlockSizeMin.x + (-sizeMax.x);
						move->x = 0.0f;
					}
					else if ((pos->x + sizeMin.x) <= (BlockPos.x + BlockSizeMax.x) && (BlockPos.x + BlockSizeMax.x) <= (posOld->x + sizeMin.x))
					{// 右からの当たり判定
						m_bHit[3] = true;
						bHit = true;

						pos->x = BlockPos.x + BlockSizeMax.x + (-sizeMin.x);
						move->x = 0.0f;
					}
				}
			}
		}
	}

	if (bHit == true)
	{
		switch (m_colType)
		{
		case COLTYPE_BOX:
			m_colHitType = COLTYPE_BOX;
			break;
		case COLTYPE_PUSH:
			m_colHitType = COLTYPE_PUSH;
			break;
		case COLTYPE_BREAK:
			m_colHitType = COLTYPE_BREAK;
			break;
		case COLTYPE_SKY:
			m_colHitType = COLTYPE_SKY;
			break;
		case COLTYPE_ICE:
			m_colHitType = COLTYPE_ICE;
			break;
		case COLTYPE_FALL:
			m_colHitType = COLTYPE_FALL;
			break;
		case COLTYPE_SEESAW:
			m_colHitType = COLTYPE_SEESAW;
			break;
		case COLTYPE_CLIMB:
			m_colHitType = COLTYPE_CLIMB;
			break;
		}
	}
	else
	{
		m_colHitType = COLTYPE_NONE;
	}

	//return &bLand[0];
}

//=============================================================================
// 当たり判定処理											(public)	*** CBlock ***
//=============================================================================
bool CBlock::OtherBlockCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bLand = false;
	bool bBreak = false;

	D3DXVECTOR3 BlockPos = CSceneX::Getpos();
	D3DXVECTOR3 BlockSizeMax = CSceneX::Getsize(0);
	D3DXVECTOR3 BlockSizeMin = CSceneX::Getsize(1);

	if (m_colType != COLTYPE_NONE)
	{
		if ((BlockPos.x + BlockSizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.x))
		{// X範囲確認
			if ((pos->y + sizeMin.y) <= (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMax.y) <= (posOld->y + sizeMin.y))
			{// 上からの当たり判定
				//bLand = true;

				pos->y = BlockPos.y + BlockSizeMax.y + (-sizeMin.y) + 0.1f;
				move->y = 0.0f;
			}
			else if ((BlockPos.y + BlockSizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (BlockPos.y + BlockSizeMin.y))
			{// 下からの当たり判定
				bLand = true;

				pos->y = BlockPos.y + BlockSizeMin.y + (-sizeMax.y) - 0.1f;
				move->y = 0.0f;
			}
		}

		if ((pos->y + sizeMin.y) <= (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) <= (pos->y + sizeMax.y))
		{// Y範囲確認
			if ((BlockPos.x + BlockSizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (BlockPos.x + BlockSizeMin.x))
			{// 左からの当たり判定
			 //bLand = true;

				pos->x = BlockPos.x + BlockSizeMin.x + (-sizeMax.x);
				move->x = 0.0f;
			}
			else if ((pos->x + sizeMin.x) <= (BlockPos.x + BlockSizeMax.x) && (BlockPos.x + BlockSizeMax.x) <= (posOld->x + sizeMin.x))
			{// 右からの当たり判定
			 //bLand = true;

				pos->x = BlockPos.x + BlockSizeMax.x + (-sizeMin.x);
				move->x = 0.0f;
			}
		}
	}

	return bLand;
}
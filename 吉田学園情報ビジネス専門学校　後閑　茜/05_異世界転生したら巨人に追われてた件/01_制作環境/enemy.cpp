//=============================================================================
//
// 敵(巨人)処理 [player.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"			// プレイヤー
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "sound.h"			// サウンド
#include "game.h"			// ゲーム
#include "input.h"			// 入力
#include "model.h"			// モデル
#include "motion.h"			// モーション
#include "camera.h"			// カメラ
#include "meshField.h"		// メッシュフィールド
#include "block.h"			// ブロック
#include "item.h"			// アイテム
#include "effect.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ANIM_NAME		"data\\TEXT\\giantmodeldata.txt"		// モーションデータ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
int						CEnemy::m_MaxModel = 0;
int						CEnemy::m_MaxAnim = 0;

LPDIRECT3DTEXTURE9		**CEnemy::m_pTexture = NULL;		// テクスチャ情報へのポインタ
LPD3DXMESH				*CEnemy::m_pMesh = NULL;			// メッシュ情報へのポインタ
LPD3DXBUFFER			*CEnemy::m_pBuffMat = NULL;		// マテリアル情報へのポインタ
DWORD					*CEnemy::m_nNumMat = NULL;			// マテリアル情報の数

CEnemy::MODEL_INFO		*CEnemy::m_ModelInfo = NULL;
CMotion::ANIM_INFO		*CEnemy::m_AnimInfo = NULL;

//=============================================================================
// コンストラクタ									(public)	*** CPlayer ***
//=============================================================================
CEnemy::CEnemy() : CScene(CScene::PRIORITY_3, CScene::OBJTYPE_ENEMY)
{
	m_bStart = true;
	m_nCntStart = 0;

	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_frotDest = 0.0f;
	m_bJump = false;
	m_bSlip = false;
	m_fDownSpeed = 0.2f;
	m_nWallJump = 5;
	m_bWallJump = false;
	m_bWallJumpmove = 0.0f;
	m_bmoveUp = false;
	m_nMoveCounter = 0;

	m_shadowHeight = 0.0f;
}

//=============================================================================
// デストラクタ										(public)	*** CPlayer ***
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// ロード処理							(public)	*** CBullet ***
//=============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		// デバイス取得

	FILE *pFile = NULL;

	pFile = fopen(ANIM_NAME, "r");

	if (pFile != NULL)
	{
		int nCntModel = 0;
		int nCntMotion = 0;
		int nCntKey = 0;

		char *pStrCut;		// 文字列の先頭へのポインタ
		char aLine[256];	// 文字列読み取り用（１行分）
		char aStr[256];		// 文字列抜き出し用

		pStrCut = ReadFile(pFile, &aLine[0]);
		strcpy(aStr, pStrCut);

		if (memcmp(aStr, "SCRIPT", strlen("SCRIPT")) == 0)
		{
			do
			{
				pStrCut = ReadFile(pFile, &aLine[0]);
				strcpy(aStr, pStrCut);

				if (memcmp(aStr, "NUM_MODEL", strlen("NUM_MODEL")) == 0)
				{
					pStrCut += strlen("NUM_MODEL");
					strcpy(aStr, PopString(pStrCut));
					m_MaxModel = atoi(aStr);

					if (m_ModelInfo == NULL)
					{
						m_ModelInfo = new MODEL_INFO[m_MaxModel];
					}
				}
				else if (memcmp(aStr, "MODEL_FILENAME", strlen("MODEL_FILENAME")) == 0)
				{
					pStrCut += strlen("MODEL_FILENAME");
					strcpy(aStr, PopString(pStrCut));
					strcpy(m_ModelInfo[nCntModel].cFileName, aStr);

					nCntModel++;
				}
				else if (memcmp(aStr, "CHARACTERSET", strlen("CHARACTERSET")) == 0)
				{
					nCntModel = 0;

					do
					{
						pStrCut = ReadFile(pFile, &aLine[0]);
						strcpy(aStr, pStrCut);

						if (memcmp(aStr, "PARTSSET", strlen("PARTSSET")) == 0)
						{
							do
							{
								pStrCut = ReadFile(pFile, &aLine[0]);
								strcpy(aStr, pStrCut);

								if (memcmp(aStr, "INDEX", strlen("INDEX")) == 0)
								{
									pStrCut += strlen("INDEX");
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].nIndex = atoi(aStr);
								}
								else if (memcmp(aStr, "PARENT", strlen("PARENT")) == 0)
								{
									pStrCut += strlen("PARENT");
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].nIndex = atoi(aStr);
								}
								else if (memcmp(aStr, "POS", strlen("POS")) == 0)
								{
									pStrCut += strlen("POS");
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].pos.x = (float)atof(aStr);
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].pos.y = (float)atof(aStr);
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].pos.z = (float)atof(aStr);
								}
								else if (memcmp(aStr, "ROT", strlen("ROT")) == 0)
								{
									pStrCut += strlen("ROT");
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].rot.x = (float)atof(aStr);
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].rot.y = (float)atof(aStr);
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].rot.z = (float)atof(aStr);
								}
							} while (memcmp(aStr, "END_PARTSSET", strlen("END_PARTSSET")) != 0);
							nCntModel++;
						}
					} while (memcmp(aStr, "END_CHARACTERSET", strlen("END_CHARACTERSET")) != 0);
				}

				if (memcmp(aStr, "NUM_MOTION", strlen("NUM_MOTION")) == 0)
				{
					pStrCut += strlen("NUM_MOTION");
					strcpy(aStr, PopString(pStrCut));
					m_MaxAnim = atoi(aStr);

					if (m_AnimInfo == NULL)
					{
						m_AnimInfo = new CMotion::ANIM_INFO[m_MaxAnim];

						for (int nCount = 0; nCount < m_MaxAnim; nCount++)
						{
							m_AnimInfo[nCount].aKeyInfo = NULL;
						}
					}
				}
				else if (memcmp(aStr, "MOTIONSET", strlen("MOTIONSET")) == 0)
				{
					nCntKey = 0;

					do
					{
						pStrCut = ReadFile(pFile, &aLine[0]);
						strcpy(aStr, pStrCut);

						if (memcmp(aStr, "LOOP", strlen("LOOP")) == 0)
						{
							pStrCut += strlen("LOOP");
							strcpy(aStr, PopString(pStrCut));
							m_AnimInfo[nCntMotion].bLoop = atoi(aStr);
						}
						else if (memcmp(aStr, "NUM_KEY", strlen("NUM_KEY")) == 0)
						{
							pStrCut += strlen("NUM_KEY");
							strcpy(aStr, PopString(pStrCut));
							m_AnimInfo[nCntMotion].nKeyMax = atoi(aStr);

							if (m_AnimInfo[nCntMotion].aKeyInfo == NULL)
							{
								m_AnimInfo[nCntMotion].aKeyInfo = new CMotion::KEY_INFO[m_AnimInfo[nCntMotion].nKeyMax];

								for (int nCount = 0; nCount < m_AnimInfo[nCntMotion].nKeyMax; nCount++)
								{
									m_AnimInfo[nCntMotion].aKeyInfo[nCount].aKey = NULL;
								}
							}
						}
						else if (memcmp(aStr, "BLEND_FRAME", strlen("BLEND_FRAME")) == 0)
						{
							pStrCut += strlen("BLEND_FRAME");
							strcpy(aStr, PopString(pStrCut));
							m_AnimInfo[nCntMotion].nBrendFrame = atoi(aStr);
						}
						else if (memcmp(aStr, "KEYSET", strlen("KEYSET")) == 0)
						{
							nCntModel = 0;

							if (nCntKey < m_AnimInfo[nCntMotion].nKeyMax)
							{
								if (m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey == NULL)
								{
									m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey = new CMotion::KEY[m_MaxModel];
								}
							}

							do
							{
								pStrCut = ReadFile(pFile, &aLine[0]);
								strcpy(aStr, pStrCut);

								if (memcmp(aStr, "FRAME", strlen("FRAME")) == 0)
								{
									pStrCut += strlen("FRAME");
									strcpy(aStr, PopString(pStrCut));
									m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = atoi(aStr);
								}
								else if (memcmp(aStr, "KEY", strlen("KEY")) == 0)
								{
									do
									{
										pStrCut = ReadFile(pFile, &aLine[0]);
										strcpy(aStr, pStrCut);

										if (memcmp(aStr, "POS", strlen("POS")) == 0)
										{
											pStrCut += strlen("POS");
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.x = (float)atof(aStr);
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.y = (float)atof(aStr);
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.z = (float)atof(aStr);
										}
										else if (memcmp(aStr, "ROT", strlen("ROT")) == 0)
										{
											pStrCut += strlen("ROT");
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.x = (float)atof(aStr);
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.y = (float)atof(aStr);
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.z = (float)atof(aStr);
										}
									} while (memcmp(aStr, "END_KEY", strlen("END_KEY")) != 0);
									nCntModel++;
								}
							} while (memcmp(aStr, "END_KEYSET", strlen("END_KEYSET")) != 0);
							nCntKey++;
						}
					} while (memcmp(aStr, "END_MOTIONSET", strlen("END_MOTIONSET")) != 0);
					nCntMotion++;
				}
			} while (memcmp(aStr, "END_SCRIPT", strlen("END_SCRIPT")) != 0);
		}
	}

	if (m_pTexture == NULL) m_pTexture = new LPDIRECT3DTEXTURE9*[m_MaxModel];
	if (m_pMesh == NULL)	m_pMesh = new LPD3DXMESH[m_MaxModel];
	if (m_pBuffMat == NULL) m_pBuffMat = new LPD3DXBUFFER[m_MaxModel];
	if (m_nNumMat == NULL)	m_nNumMat = new DWORD[m_MaxModel];

	char cName[256];

	for (int nCntParnet = 0; nCntParnet < m_MaxModel; nCntParnet++)
	{
		wsprintf(cName, m_ModelInfo[nCntParnet].cFileName);

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
void CEnemy::Unload(void)
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

	if (m_pTexture != NULL) { delete[] m_pTexture; m_pTexture = NULL; }
	if (m_pMesh != NULL) { delete[] m_pMesh; m_pMesh = NULL; }
	if (m_pBuffMat != NULL) { delete[] m_pBuffMat; m_pBuffMat = NULL; }
	if (m_nNumMat != NULL) { delete[] m_nNumMat; m_nNumMat = NULL; }

	if (m_ModelInfo != NULL)
	{
		delete[] m_ModelInfo;
		m_ModelInfo = NULL;
	}

	if (m_AnimInfo != NULL)
	{
		for (int nCntAnim = 0; nCntAnim < m_MaxAnim; nCntAnim++)
		{
			for (int nCntKey = 0; nCntKey < m_AnimInfo[nCntAnim].nKeyMax; nCntKey++)
			{
				delete[] m_AnimInfo[nCntAnim].aKeyInfo[nCntKey].aKey;
				m_AnimInfo[nCntAnim].aKeyInfo[nCntKey].aKey = NULL;
			}
			delete[] m_AnimInfo[nCntAnim].aKeyInfo;
			m_AnimInfo[nCntAnim].aKeyInfo = NULL;
		}

		delete[] m_AnimInfo;
		m_AnimInfo = NULL;
	}
}

//=============================================================================
// 確保処理											(public)	*** CEnemy ***
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = NULL;			// ポインタ

	if (pEnemy == NULL)
	{// NULLの場合
		pEnemy = new CEnemy;			// メモリ確保
	}

	if (pEnemy != NULL)
	{// NULL以外の場合
		pEnemy->m_pModel = new CModel[m_MaxModel];

		for (int nCntModel = 0; nCntModel < m_MaxModel; nCntModel++)
		{
			pEnemy->m_pModel[nCntModel].SetInitAll(m_pTexture[nCntModel], m_pMesh[nCntModel], m_pBuffMat[nCntModel], m_nNumMat[nCntModel], m_ModelInfo[nCntModel].pos, m_ModelInfo[nCntModel].rot);
			pEnemy->m_pModel[nCntModel].Init();

			if (0 <= m_ModelInfo[nCntModel].nIndex)
			{
				pEnemy->m_pModel[nCntModel].SetParent(&pEnemy->m_pModel[m_ModelInfo[nCntModel].nIndex]);
			}
		}

		pEnemy->m_pos = pos;
		pEnemy->m_rot = rot;
		pEnemy->m_frotDest = rot.y;
		pEnemy->Init();					// 初期化処理
	}

	return pEnemy;			// 値を返す
}

//=============================================================================
// 初期化処理										(public)	*** CEnemy ***
//=============================================================================
HRESULT CEnemy::Init()
{
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}

	m_vtxMax = D3DXVECTOR3(50.0f, 1000.0f, 50.0f);
	m_vtxMin = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);

	return S_OK;
}

//=============================================================================
// 終了処理											(public)	*** CEnemy ***
//=============================================================================
void CEnemy::Uninit(void)
{
	if (m_pModel != NULL)
	{
		for (int nCntModel = 0; nCntModel < m_MaxModel; nCntModel++)
		{
			m_pModel[nCntModel].Uninit();
		}
		delete[] m_pModel;
		m_pModel = NULL;
	}

	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	CGame::SetEnemy();

	CScene::SetDeath();						// 終了処理
}

//=============================================================================
// 更新処理											(public)	*** CEnemy ***
//=============================================================================
void CEnemy::Update(void)
{
	bool bMeshField = false;			// メッシュフィールド有無
	CMeshField *pMeshField = NULL;
	CSound *pSound = CManager::GetSound();

	for (int nCount = 0; nCount < CGame::m_MeshFieldMax; nCount++)
	{// フィールドカウンタ
		pMeshField = CGame::GetMeshField(nCount);

		if (pMeshField != NULL)
		{// NULL以外の場合
			if (pMeshField->ColInMesh(m_pos + m_vtxMax))
			{// 判定内にいるか
				bMeshField = true;			// メッシュ有り
				break;
			}
			else if (pMeshField->ColInMesh(m_pos))
			{// 判定内にいるか
				bMeshField = true;			// メッシュ有り
				break;
			}
			else if (pMeshField->ColInMesh(m_pos + m_vtxMin))
			{// 判定内にいるか
				bMeshField = true;			// メッシュ有り
				break;
			}
		}
	}

	float fHeight = -500.0f;
	float fUpDown = 0.0f;

	if (bMeshField == true)
	{
		fHeight = pMeshField->GetHeight(m_pos);
	}
	m_shadowHeight = fHeight;

	m_posOld = m_pos;		// 位置保存

	if (m_bStart == true)
	{
		if (m_pos.x < -300.0f)
		{
			if (m_pos.x < -420.0f)
			{
				m_pos.y = 300.0f;
			}
			else
			{
				if (m_pos.y == 300.0f)
				{
					if (m_pMotion->GetAnimNum() != 3)
					{
						m_pMotion->SetAnimNum(3);	//	歩くモーション
					}
				}
				m_pos.y -= 20.0f;
			}

			// 移動処理
			m_frotDest = -D3DX_PI * 0.5f;
			m_move.x += sinf(-m_frotDest) * ((0.8f - m_bWallJumpmove) + (0.8f * fUpDown));
			m_move.z += cosf(-m_frotDest) * ((0.8f - m_bWallJumpmove) + (0.8f * fUpDown));
		}
		else
		{
			m_nCntStart++;

			if (m_nCntStart == 180)
			{
				m_bStart = false;
				m_nCntStart = 0;
			}
		}
	}
	else
	{
		// 移動処理
		m_frotDest = -D3DX_PI * 0.5f;
		m_move.x += sinf(-m_frotDest) * ((1.0f - m_bWallJumpmove) + (1.0f * fUpDown));
		m_move.z += cosf(-m_frotDest) * ((1.0f - m_bWallJumpmove) + (1.0f * fUpDown));

		m_pMotion->SetAnimNum(1);	//	歩くモーション
	}

	m_pos += m_move;

	bool bBlock = false;

	CScene *pScene = CScene::GetScene(CScene::PRIORITY_3);
	CScene *pSceneNext = NULL;

	while (pScene != NULL)
	{
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
		{//	オブジェクトがモデルだったら
			CBlock *pBlock = (CBlock*)pScene;
			pBlock->Collision(&m_pos, &m_posOld, &m_move, &m_fDownSpeed, m_vtxMax, m_vtxMin);
			bool *bLand = pBlock->GetHit();
			for (int nCount = 0; nCount < 4; nCount++)
			{
				if (bLand[nCount] == true)
				{
					bBlock = true;
					if (bBlock == true)
					{
						pBlock->Uninit();
						bBlock = false;
						bLand[nCount] = false;
						D3DXVECTOR3 posblock = pBlock->Getpos();
						CEffect::Create(posblock, 5, 1);//　テクスチャ　テキスト
						CEffect::Create(posblock, 2, 3);//　テクスチャ　テキスト
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE032);
					}
				}
			}
		}
		pScene = pSceneNext;
	}

	if (m_pos.y < fHeight)
	{
		m_pos.y = fHeight;
		m_move.y = 0.0f;
		m_fDownSpeed = 0.2f;
		m_nWallJump = 5;
		m_bWallJumpmove = 0.0f;
		m_bJump = false;
	}


	if (0.65f < m_bWallJumpmove)
	{
		m_rot.y += ((m_frotDest - m_rot.y) / 5.0f) * ((0.65f - (m_bWallJumpmove / 2.0f)) / 0.65f);
	}
	else
	{
		m_rot.y += ((m_frotDest - m_rot.y) / 5.0f);
	}
	m_move.x -= (m_move.x - 0.0f) * 0.2f;
	//m_move.y -= 0.7f;
	m_move.z -= (m_move.z - 0.0f) * 0.2f;

	if (m_bStart == false || (m_bStart == true && m_nCntStart < 60))
	{
		m_pMotion->Update(m_MaxModel, &m_AnimInfo[0], &m_pModel[0], m_ModelInfo[0].pos);		// モーション更新
	}

	CFont *pFont = CRenderer::GetFont(CFont::FONTNUM_TEST);
	pFont->SetMessage(CFont::SETTYPE_ADD, "Enemy : 位置　[%.2f, %.2f, %.2f]\n", m_pos.x, m_pos.y, m_pos.z);
	pFont->SetMessage(CFont::SETTYPE_ADD, "Enemy : fHeight　[%.2f]\n", fHeight);
	pFont->SetMessage(CFont::SETTYPE_ADD, "Enemy : bMesh　[%d]\n", bMeshField);

	if (m_pos.x >= 12260)
	{
		m_move.y -= 0.02f;
	}
	if (m_pos.x >= 12780)
	{//	敵を消す処理
		CEffect::Create(m_pos + D3DXVECTOR3(0.0f, 80.0f, 0.0f), 3, 10);//　テクスチャ　テキスト
		CEffect::Create(m_pos + D3DXVECTOR3(0.0f, 80.0f, 0.0f), 6, 9);//　テクスチャ　テキスト
		Uninit();
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE028);
	}
}

//=============================================================================
// 描画処理											(public)	*** CEnemy ***
//=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		// デバイス取得
	D3DXMATRIX mtxRot, mtxTrans, matScale;			// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//拡大縮小行列の作成
	D3DXMatrixScaling(&matScale, m_fScaleX, m_fScaleY, m_fScaleZ);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &matScale);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntModel = 0; nCntModel < m_MaxModel; nCntModel++)
	{
		if (m_pModel != NULL)
		{
			m_pModel[nCntModel].Draw();
			CShadow::SetShadow(m_pModel[nCntModel].GetmtxWorld(), m_pMesh[nCntModel], m_nNumMat[nCntModel], D3DXVECTOR3(m_pos.x, m_shadowHeight, m_pos.z));
		}
	}
}
//=============================================================================
//	敵の当たり判定									(public)	*** CEnemy ***
//=============================================================================
bool CEnemy::CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;

	if (m_pos.x + (m_vtxMax.x / 2) > pPos->x + sizeMin.x && //　右
		m_pos.x + (m_vtxMin.x / 2) < pPos->x + sizeMax.x && //　左
		m_pos.z + (m_vtxMax.z / 2) > pPos->z + sizeMin.z && //　奥
		m_pos.z + (m_vtxMin.z / 2) < pPos->z + sizeMax.z && //　手前
		m_pos.y + (m_vtxMax.y / 2) > pPos->y + sizeMin.y && //　奥
		m_pos.y + (m_vtxMin.y / 2) < pPos->y + sizeMax.y)	//　手前
	{
		bHit = true;
		pMove->x += 200.0f;
		pMove->y += 10.0f;
	}
	return bHit;
}
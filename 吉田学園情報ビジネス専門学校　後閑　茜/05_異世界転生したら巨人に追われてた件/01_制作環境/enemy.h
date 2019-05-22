//=============================================================================
//
// 敵(巨人)処理 [enemy.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scene.h"		// シーン
#include "motion.h"		// モーション

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;			// モデル
class CMotion;			// モーション

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy : public CScene
{// プレイヤー（親：CScene）
public:
	typedef struct
	{
		char cFileName[256];
		int nIndex;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}MODEL_INFO;

	CEnemy();										// コンストラクタ
	~CEnemy();										// デストラクタ

	static HRESULT Load(void);						// ロード
	static void Unload(void);						// アンロード
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成

	HRESULT Init(void);											// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 Getpos(void) { return m_pos; }
	// 敵の当たり判定
	bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);

	static char *ReadFile(FILE *pFile, char *pDest)
	{
		fgets(pDest, 256, pFile);

		if (memcmp(pDest, "#", strlen("#")) == 0 || memcmp(pDest, "\n", strlen("\n")) == 0)
		{
			ReadFile(pFile, pDest);
		}
		else
		{
			do
			{
				if (memcmp(pDest, "#", strlen("#")) == 0 || memcmp(pDest, "\n", strlen("\n")) == 0)
				{
					ReadFile(pFile, pDest);
				}
				else if (memcmp(pDest, " ", strlen(" ")) == 0)
				{
					wsprintf(&pDest[0], &pDest[strlen(" ")]);
				}
				else if (memcmp(pDest, "\t", strlen("\t")) == 0)
				{
					wsprintf(&pDest[0], &pDest[strlen("\t")]);
				}
				else if (memcmp(pDest, "　", strlen("　")) == 0)
				{
					wsprintf(&pDest[0], &pDest[strlen("　")]);
				}
			} while (
				memcmp(pDest, "#", strlen("#")) == 0 || memcmp(pDest, "\n", strlen("\n")) == 0 ||
				memcmp(pDest, " ", strlen(" ")) == 0 || memcmp(pDest, "\t", strlen("\t")) == 0 ||
				memcmp(pDest, "　", strlen("　")) == 0);
		}

		return pDest;
	}
	static char *PopString(char *pSrc)
	{
		do
		{
			if (memcmp(pSrc, "=", strlen("=")) == 0)
			{
				wsprintf(&pSrc[0], &pSrc[strlen("=")]);
			}
			else if (memcmp(pSrc, " ", strlen(" ")) == 0)
			{
				wsprintf(&pSrc[0], &pSrc[strlen(" ")]);
			}
			else if (memcmp(pSrc, "\t", strlen("\t")) == 0)
			{
				wsprintf(&pSrc[0], &pSrc[strlen("\t")]);
			}
			else if (memcmp(pSrc, "　", strlen("　")) == 0)
			{
				wsprintf(&pSrc[0], &pSrc[strlen("　")]);
			}
		} while (
			memcmp(pSrc, "=", strlen("=")) == 0 ||
			memcmp(pSrc, " ", strlen(" ")) == 0 || memcmp(pSrc, "\t", strlen("\t")) == 0 ||
			memcmp(pSrc, "　", strlen("　")) == 0);

		int nCntEnd = 0;
		char cStr[256];
		strcpy(cStr, pSrc);

		do
		{
			if (memcmp(cStr, "#", strlen("#")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen("#")]);
			}
			else if (memcmp(cStr, "\n", strlen("\n")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen("\n")]);
			}
			else if (memcmp(cStr, " ", strlen(" ")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen(" ")]);
			}
			else if (memcmp(cStr, "\t", strlen("\t")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen("\t")]);
			}
			else if (memcmp(cStr, "　", strlen("　")) == 0)
			{
				wsprintf(&cStr[0], &cStr[strlen("　")]);
			}
			else
			{
				wsprintf(&cStr[0], &cStr[1]);
			}

			nCntEnd++;
		} while (
			memcmp(cStr, "#", strlen("#")) != 0 && memcmp(cStr, "\n", strlen("\n")) != 0 &&
			memcmp(cStr, " ", strlen(" ")) != 0 && memcmp(cStr, "\t", strlen("\t")) != 0 &&
			memcmp(cStr, "　", strlen("　")) != 0);

		strcpy(cStr, pSrc);
		wsprintf(&pSrc[0], &pSrc[nCntEnd]);
		cStr[nCntEnd] = '\0';

		return cStr;
	}

private:
	static int					m_MaxModel;			// モデル数
	static int					m_MaxAnim;			// アニメーション数

	static LPDIRECT3DTEXTURE9	**m_pTexture;		// テクスチャ情報へのポインタ
	static LPD3DXMESH			*m_pMesh;			// メッシュ情報へのポインタ
	static LPD3DXBUFFER			*m_pBuffMat;		// マテリアル情報へのポインタ
	static DWORD				*m_nNumMat;			// マテリアル情報の数

	static MODEL_INFO			*m_ModelInfo;
	static CMotion::ANIM_INFO	*m_AnimInfo;

	D3DXMATRIX					m_mtxWorld;			// ワールドマトリックス
	CModel						*m_pModel;			// モデル
	CMotion						*m_pMotion;			// モーション

	bool						m_bStart;			// スタート
	int							m_nCntStart;

	D3DXVECTOR3					m_vtxMax;
	D3DXVECTOR3					m_vtxMin;
	D3DXVECTOR3					m_pos;				// 位置現在
	D3DXVECTOR3					m_posOld;			// 位置前回
	D3DXVECTOR3					m_rot;				// 向き
	D3DXVECTOR3					m_move;				// 移動量
	float						m_frotDest;
	bool						m_bJump;
	bool						m_bSlip;
	float						m_fSliprot;
	float						m_fDownSpeed;
	int							m_nWallJump;
	bool						m_bWallJump;
	float						m_bWallJumpmove;

	bool						m_bmoveUp;			// アイテムでスピードが上がっていいるかどうか
	int							m_nMoveCounter;		// スピードUPする時間のカウンター
	FLOAT						m_fScaleX = 1.0f, m_fScaleY = 1.0f, m_fScaleZ = 1.0f;   //拡大縮小用変数

	float						m_shadowHeight;

protected:

};

#endif
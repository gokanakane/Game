//=============================================================================
//
// ブロック処理 [block.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scenex.h"		// シーンx

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBlock : public CSceneX
{// ブロック親：CSceneX）
public:
	typedef enum
	{
		MODELTYPE_BOX_R = 0,	// 岩(ブロック)
		MODELTYPE_BOX_W_1,		// 木
		MODELTYPE_BOX_W_2,		// 木(背景用)
		MODELTYPE_SKY,			// 空中床(正式採用視野)
		MODELTYPE_ICE,			// 滑る床
		MODELTYPE_LOG,			// 丸太
		MODELTYPE_SEESAW,		// シーソー
		MODELTYPE_IVY,			// ツタ
		MODELTYPE_IVY_2,		// ツタ(背景用)
		MODELTYPE_BOX_W_3,		// 木ブロック4つ分
		MODELTYPE_TREE,			// 背景の木
		MODELTYPE_TREE2,		// 背景の木2
		MODELTYPE_TREE3,		// 背景の木2
		MODELTYPE_TREE4,		// 背景の木2
		MODELTYPE_GRASS,		// 草
		MODELTYPE_GOAL,			// ゴール
		MODELTYPE_PBROCK,		// ゴール
		MODELTYPE_MAX
	}MODELTYPE;

	typedef enum
	{
		COLTYPE_NONE = 0,
		COLTYPE_BOX,
		COLTYPE_PUSH,
		COLTYPE_BREAK,
		COLTYPE_SKY,
		COLTYPE_ICE,
		COLTYPE_FALL,
		COLTYPE_SEESAW,
		COLTYPE_CLIMB,
		COLTYPE_WALLJUMP,
		COLTYPE_MAX
	}COLTYPE;

	const static int m_MaxModel = MODELTYPE_MAX;			// モデル数

	CBlock();										// コンストラクタ
	~CBlock();										// デストラクタ

	static HRESULT Load(void);						// ロード
	static void Unload(void);						// アンロード
	static CBlock *Create(D3DXVECTOR3 pos, MODELTYPE modelType, COLTYPE coltype);		// 生成

	HRESULT Init(D3DXVECTOR3 pos, MODELTYPE modelType, COLTYPE coltype);				// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

	void Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, float *fDownSpeed, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	bool OtherBlockCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);

	COLTYPE GetType(void) { return m_colType; }
	COLTYPE GetHitType(void) { COLTYPE coltype = m_colHitType; m_colHitType = COLTYPE_NONE; return coltype; }

	bool *GetHit(void) { return m_bHit; }

private:
	static LPDIRECT3DTEXTURE9	*m_pTexture[m_MaxModel];	// テクスチャ情報へのポインタ
	static LPD3DXMESH			m_pMesh[m_MaxModel];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat[m_MaxModel];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat[m_MaxModel];		// マテリアル情報の数

	MODELTYPE					m_modelType;
	COLTYPE						m_colType;			// 種類
	COLTYPE						m_colHitType;
	D3DXVECTOR3					m_posOld;			// 移動量
	D3DXVECTOR3					m_move;				// 移動量
	bool						m_bHit[4];

	float						m_shadowHeight;

protected:

};

#endif
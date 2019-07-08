//=============================================================================
//
// ランキング処理 [Ranking.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_POLYGON_RANKING (7)
#define MAX_TEXTURE_RANKING (3)
#define DEFALT_COL_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))
#define TEXTURE_RANKING_SUBTITLE	"data\\TEXTURE\\Ranking\\Ranking_SubTitle.png"
#define TEXTURE_RANKING_CHARAICON	"data\\TEXTURE\\Ranking\\RankingTex000.png"
#define TEXTURE_RANKING_RANK		"data\\TEXTURE\\Ranking\\Ranking001.png"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CScore;
class CManager;
class CScene2D;
//*****************************************************************************
// クラス
//*****************************************************************************
class CRanking
{
public:
	typedef enum
	{
		PRESSSTATE_NONE=0,
		PRESSSTATE_FLASHING,
		PRESSSTATE_MAX
	}PRESSSTATE;

	CRanking();
	~CRanking();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_RANKING];	//共有テクスチャへのポインタ
	static CScene2D *m_apScene2D[MAX_POLYGON_RANKING];
	static CBg *m_pBG;
	static CScore *m_pScore;
	PRESSSTATE m_State;
	D3DXCOLOR m_col;
	float m_fChangeAlpha;
	int m_nCntFade;
	int m_nChangeMode;
};
#endif
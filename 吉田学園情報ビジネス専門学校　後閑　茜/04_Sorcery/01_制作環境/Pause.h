//=============================================================================
//
// ポーズ処理 [Pause.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PAUSEBG						"data\\TEXTURE\\Pause\\PauseBG.png"
#define TEXTURE_PAUSE_ITEM				"data\\TEXTURE\\Pause\\Pause_Item.png"

#define MAX_PAUSETEXTURE (3)
#define MAX_PAUSEMENU (5)
#define MAX_PAUSEPOLYGON (7)
#define PAUSE_WIDTH (280.0f)
#define PAUSE_HEIGHT (220.0f)
#define PAUSE_MASK (D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CPause : public CScene
{
public:
	/* ポーズのタイプ */
	typedef enum
	{
		PAUSETYPE_NONE = 0,
		PAUSETYPE_CONTINUE,
		PAUSETYPE_QUIT,
		PAUSETYPE_RETRY,
		PAUSETYPE_STAGESELECT,
		PAUSETYPE_CHARACTORSELECT,
		PAUSETYPE_MAX
	}PAUSE_TYPE;

	/* 色と座標 */
	typedef enum
	{
		PAUSECOL_NONE = 0,
		PAUSECOL_CONTINUE,
		PAUSECOL_QUIT,
		PAUSECOL_RETRY,
		PAUSECOL_STAGESELECT,
		PAUSECOL_CHARACTORSELECT,
		PAUSECOL_MAX
	}PAUSE_COLOR;

	CPause();
	~CPause();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPause *Create(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static void SetPause(bool bPause);
	static bool GetPause(void) { return m_bPause; }
	void SetMove(int nNum);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PAUSETEXTURE];	//共有テクスチャへのポインタ
	static CScene2D *m_apScene2D[MAX_PAUSEPOLYGON];
	int m_nCntBG;
	static bool m_bPause;
	static int m_nSelectNum;
	PAUSE_COLOR m_PauseCol;
	PAUSE_TYPE m_PauseType;
	float m_fCntMove,m_fChengeMove;
	D3DXVECTOR3 m_pos,m_posOld[MAX_PAUSEMENU];
};

#endif

//=============================================================================
//
// 弾処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXTURE_TITLE (4)
#define TEXTURE_TITLE_LOGO			"data\\TEXTURE\\Title\\Logo_Title.png"
#define TEXTURE_TITLE_CONCRETE		"data\\TEXTURE\\Title\\Title_Concrete.png"
#define TEXTURE_TITLE_ANIMATION		"data\\TEXTURE\\Title\\Title_Anim.png"
#define TEXTURE_TITLE_PRESS			"data\\TEXTURE\\UI\\PRESS_ENTER.png"
#define MAX_TITLEANIM (2)
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
//*****************************************************************************
// クラス
//*****************************************************************************
class CTitle
{
public:
	typedef enum
	{//PRESSENTERの状態
		PRESSSTATE_NONE = 0,
		PRESSSTATE_FLASHING,
		PRESSSTATE_MAX
	}PRESSSTATE;

	typedef enum
	{//ロゴの状態
		LOGOSTATE_NONE = 0,
		LOGOSTATE_FADEIN,
		LOGOSTATE_MAX
	}LogoState;

	typedef enum
	{//キャラ周りの状態
		GRAPHICSTATE_NONE = 0,
		GRAPHICSTATE_ALPHA_0,
		GRAPHICSTATE_FADEIN,
		GRAPHICSTATE_MAX
	}GraphicState;

	CTitle();
	~CTitle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_TITLE];	//共有テクスチャへのポインタ
	static CScene2D *m_apScene2D[MAX_TEXTURE_TITLE];
	static CBg *m_pBG;
	PRESSSTATE m_State;
	D3DXCOLOR m_col,m_colLogo;
	LogoState m_LogoState;
	GraphicState m_GraphicState;
	float m_fChangeAlpha;
	int m_nCntFade,m_nChangeMode,m_nCntAnim,m_nPatternAnim;
};
#endif
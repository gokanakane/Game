//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_STAGE1			"data\\TEXTURE\\BG\\Bg_Stage1.jpg"
#define TEXTURE_STAGE2			"data\\TEXTURE\\BG\\mori_hiru.jpg"
#define TEXTURE_STAGE3			"data\\TEXTURE\\BG\\Bg_Stage3.jpg"
#define TEXTURE_STAGE4			"data\\TEXTURE\\BG\\Bg_Stage4.jpg"
#define TEXTURE_SMOKE			"data\\TEXTURE\\BG\\mist.png"
#define TEXTURE_RAIN			"data\\TEXTURE\\BG\\BgMask_Stage1.jpg"
#define TEXTURE_TITLE			"data\\TEXTURE\\BG\\Bg_Title.jpg"
#define TEXTURE_RESULT			"data\\TEXTURE\\BG\\result000.jpg"
#define TEXTURE_STAGESELECT		"data\\TEXTURE\\BG\\StageSelectBg.png"
#define TEXTURE_CHARACTERSELECT "data\\TEXTURE\\BG\\CharactorSelect_Bg.jpg"
#define TEXTURE_TUTORIAL		"data\\TEXTURE\\BG\\tutorial_BG.jpg"
#define TEXTURE_TUTORIAL_SCROLL "data\\TEXTURE\\BG\\Tutorial_Scroll.png"
#define TEXTURE_RANKING			"data\\TEXTURE\\BG\\Ranking_BG.png"
#define MAX_TEXTURE (2)
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CBg : public CScene
{
public:
	CBg();
	~CBg();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg *Create(void);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャへのポインタ
	CScene2D *m_apScene2D[MAX_TEXTURE];
	int m_nCntBG;

};

#endif

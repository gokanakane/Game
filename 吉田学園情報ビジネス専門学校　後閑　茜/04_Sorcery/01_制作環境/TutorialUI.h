//=============================================================================
//
// UI処理 [uiBase.h]
// Author : 
//
//=============================================================================
#ifndef _TUTORIALUI_H__
#define _TUTORIALUI_H__

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// クラス（派生）：チュートリアルUI
//*****************************************************************************
class CTutorialUi :CScene2D
{
public:
	typedef enum
	{//UIの種類
		TUTORIALUITYPE_NONE = 0,
		TUTORIALUITYPE_ENTER_OR_A,
		TUTORIALUITYPE_MAX
	}TutorialUiType;

	CTutorialUi();
	~CTutorialUi();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTutorialUi *Create(CTutorialUi::TutorialUiType type);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetType(TutorialUiType type) { m_Type = type; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAXTEXTURE_TUTORIALUI];	//共有テクスチャへのポインタ
	TutorialUiType m_Type;

};

#endif
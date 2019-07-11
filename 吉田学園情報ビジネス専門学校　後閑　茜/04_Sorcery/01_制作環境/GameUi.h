//=============================================================================
//
// ゲームUI処理 [GameUi.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _GameUi_H__
#define _GameUi_H__

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAGICBUTTON_NORMAL	"data\\TEXTURE\\UI\\MagicButton000.png"
#define MAGICBUTTON_KIWAME	"data\\TEXTURE\\UI\\MagicButton001.png"
#define UI_HPFREAM			"data\\TEXTURE\\UI\\HPframe.png"
#define DESTINYLINE_COL (D3DXCOLOR(1.0f,0.5f,0.0f,1.0f))
#define MAX_UITEXTURE (2)

#define LIFEGAUGECOL_MARGIN (D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))
#define LIFEGAUGECOL_HARF (D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f))
#define LIFEGAUGECOL_PINTH (D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))
#define LIFEGAUGEPOS_CENTER (D3DXVECTOR3(55.0f, 60.0f, 0.0f))
#define LIFEGAUGE_TEXTURE	"data\\TEXTURE\\UI\\HPGauge.png"

#define BUTTONCOL_PUSH (D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))
#define BUTTONCOL_NOPUSH (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))

#define MAXTEXTURE_TUTORIALUI (1)
#define TUTORIALTEXTURE_ENTER_OR_A	"data\\TEXTURE\\Tutorial\\Tutorial_Button.png"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;
class CLifeGauge;
class CButton;
class CTime;

//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CUi : public CScene
{
public:
	typedef enum
	{
		BUTTONTYPE_NORMAL = 0,	//魔法ボタン
		BUTTONTYPE_KIWAME,		//極魔法ボタン
		BUTTONTYPE_PRESS_A,		//コントローラーAかキーボードN押す（チュートリアル）
		BUTTONTYPE_MAX
	}Buttontype;

	CUi();
	~CUi();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUi *Create(void);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_UITEXTURE];	//共有テクスチャへのポインタ
	static CLifeGauge *m_pLifeGauge;
	static CButton *m_pButton;
	CScene2D *m_apScene2D[MAX_UITEXTURE];
};

#endif

//=============================================================================
//
// フォント処理 [font.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#ifndef _FONT_H_
#define _FONT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "manager.h"	// マネージャー
#include "scene.h"		// シーン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MESSAGE		(1024)

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFont
{// フォント
public:
	typedef enum
	{// フォント番号
		FONTNUM_COMMAND = 0,
		FONTNUM_LOG,
		FONTNUM_DATA,
		FONTNUM_DEBUG,
		FONTNUM_TEST,
		FONTNUM_MAX
	}FONTNUM;

	typedef enum
	{// セットタイプ
		SETTYPE_NEW = 0,
		SETTYPE_ADD,
		SETTYPE_LOG,
		SETTYPE_MAX
	}SETTYPE;

	CFont();						// コンストラクタ
	~CFont();						// デストラクタ

	static CFont *Create(int nHeight, int nWidth, int nWeight, RECT rect, UINT uFormat, D3DXCOLOR col);		// クリエイト

	static void ReleaseAll(void);				// 全破棄
	static void DrawAll(void);					// 全描画

	static bool GetDispAll(void) { return m_bDispAll; }			// フォント描画

	static void SetMessageData(CScene::OBJTYPE objType, SETTYPE nSetType, char *aMessage, ...);		// 文字設定
	static void *GetMessageData(CScene::OBJTYPE objType) { return m_MessageData[objType]; }

	HRESULT Init(int nHeight, int nWidth, int nWeight, RECT rect, UINT uFormat, D3DXCOLOR col);				// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	void SetMessage(SETTYPE nSetType, char *aMessage, ...);		// 文字設定
	char *GetMessage(void) { return m_Message; }				// 文字取得

	void SetDisp(bool bDisp) { m_bDisp = bDisp; }
	bool GetDisp(void) { return m_bDisp; }

private:
	static CFont *m_apFont[FONTNUM_MAX];		// シーン
	static bool m_bDispAll;						// 表示
	static char m_MessageData[CScene::OBJTYPE_MAX][MAX_MESSAGE];

	int m_nID;									// ID番号
	LPD3DXFONT	m_pFont = NULL;					// フォントへのポインタ

	bool m_bDisp;								// 表示
	char m_Message[MAX_MESSAGE];
	RECT m_rect;
	UINT m_uFormat;
	D3DXCOLOR m_col;

protected:
	void Release(void);							// 開放処理

};

#endif
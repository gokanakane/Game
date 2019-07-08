//=============================================================================
//
// フェード処理 [Fade.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_SPEED (0.03f)
#define FADETEXTURE_NOWLOADING "data\\TEXTURE\\UI\\NowLoading.png"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CManager;
class CScene2D;

//*****************************************************************************
// クラス
//*****************************************************************************
class CFade : public CScene
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// 何もしていない状態
		FADE_IN,			// フェードイン状態
		FADE_OUT,			// フェードアウト状態
		FADE_MAX
	} FADEMODE;

	CFade();
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetFade(CManager::MODE modeNext);
	static FADEMODE GetFade(void) { return m_fade; }
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static FADEMODE m_fade;				// フェード状態
	static D3DXCOLOR m_colFade;		// フェード色
	static CManager::MODE m_modeNext;	// 次のモード
	CScene2D *m_pScene2D;
};
#endif
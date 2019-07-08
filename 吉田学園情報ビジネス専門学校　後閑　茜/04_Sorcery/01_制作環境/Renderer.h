//=============================================================================
//
// レンダラー処理 [Renderer.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }/* ポインタ返すだけの時 */
	static int m_nNumGet;

#ifdef _DEBUG
	void DrawFPS(void);
#endif

private:
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)

	float m_fAngle, m_fLenge, m_fChange;
#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
#endif
};

#endif

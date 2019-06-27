//=============================================================================
//
// コントローラー入力処理 [DirectInput.h]
// Author : 後閑茜
//
//=============================================================================
#ifndef DIRECTINPUT_H_
#define DIRECTINPUT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p)=NULL; } }

//*****************************************************************************
// 構造体
//*****************************************************************************
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitDirectInput(void);
void UninitDirectInput(void);
void UpdateDirectInput(void);
void DrawDirectInput(void);
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
#endif

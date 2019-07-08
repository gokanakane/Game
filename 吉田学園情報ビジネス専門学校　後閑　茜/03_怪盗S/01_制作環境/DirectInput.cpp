//=============================================================================
//
// コントローラー入力処理 [DirectInput.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "DirectInput.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
HWND                  g_hWnd;
HINSTANCE             g_Inst;
LPDIRECTINPUT8        g_pDInput = NULL;     // DirectInput
LPDIRECTINPUTDEVICE8  g_pDIDev = NULL;     // DirectInput デバイス
POINT                 Pos, WPos;
DIDEVCAPS             g_diDevCaps;          // ジョイスティックの能力

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitDirectInput(void)
{
	HRESULT hr;

	// DirectInputの作成
	hr = DirectInput8Create(g_Inst, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pDInput, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "DirectInput8オブジェクトの作成に失敗", "Direct Input Error", MB_OK);
		return hr;
	}
	// デバイスを列挙して作成
	hr = g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
		NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr) || g_pDIDev == NULL)
	{
		MessageBox(NULL, "DirectInputDevice8オブジェクトの作成に失敗", "Direct Input Error", MB_OK);
		return hr;
	}
	// データ形式を設定
	hr = g_pDIDev->SetDataFormat(&c_dfDIJoystick2);
	if (FAILED(hr))
	{
		MessageBox(NULL, "c_dfDIJoystick2形式の設定に失敗", "Direct Input Error", MB_OK);
		return hr;
	}
	//モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDev->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォアグラウンド＆非排他モードの設定に失敗", "Direct Input Error", MB_OK);
		return hr;
	}
	// コールバック関数を使って各軸のモードを設定
	hr = g_pDIDev->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS);
	if (FAILED(hr))
	{
		MessageBox(NULL, "軸モードの設定に失敗", "Direct Input Error", MB_OK);
		return hr;
	}
	// 入力制御開始
	g_pDIDev->Acquire();
	return S_OK;

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitDirectInput(void)
{

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateDirectInput(void)
{
	DIJOYSTATE2 dijs;
	HRESULT     hr;

	hr = g_pDIDev->GetDeviceState(sizeof(DIJOYSTATE2), &dijs);
	if (SUCCEEDED(hr))
	{
		if (dijs.rgbButtons[0] & 0x80)  //Yボタン
		{
			PostMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
		if (dijs.rgbButtons[1] & 0x80)//Xボタン
		{
			PostMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
		if (dijs.lX) //スティック
		{
			Pos.x += dijs.lX / 1000;
		}
		if (dijs.lY) //スティック
		{
			Pos.y += dijs.lY / 1000;
		}
	}
	else if (hr == DIERR_INPUTLOST)  g_pDIDev->Acquire();

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawDirectInput(void)
{
	HDC     hdc;
	RECT    rect;

	if (Pos.x == WPos.x && Pos.y == WPos.y) return;
	GetWindowRect(g_hWnd, &rect);
	rect.right -= rect.left;
	rect.bottom -= rect.top;
	rect.left = rect.top = 0;
	hdc = GetDC(g_hWnd);
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	Ellipse(hdc, Pos.x, Pos.y, Pos.x + 50, Pos.y + 50);
	ReleaseDC(g_hWnd, hdc);
	WPos = Pos;

}
//=============================================================================
// ジョイスティックを列挙する関数
//=============================================================================
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;

	// 列挙されたジョイスティックへのインターフェイスを取得する。
	hr = g_pDInput->CreateDevice(pdidInstance->guidInstance, &g_pDIDev, NULL);
	if (FAILED(hr))     return DIENUM_CONTINUE;
	// ジョイスティックの能力を調べる
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = g_pDIDev->GetCapabilities(&g_diDevCaps);
	if (FAILED(hr))
	{   // ジョイスティック能力の取得に失敗
		SAFE_RELEASE(g_pDIDev);
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;

}
//=============================================================================
// ジョイスティックの軸を列挙する関数
//=============================================================================
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	HRESULT hr;

	// 軸の値の範囲を設定（-1000～1000）
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj = lpddoi->dwType;
	diprg.diph.dwHow = DIPH_BYID;
	diprg.lMin = -1000;
	diprg.lMax = +1000;
	hr = g_pDIDev->SetProperty(DIPROP_RANGE, &diprg.diph);
	if (FAILED(hr))     return DIENUM_STOP;
	return DIENUM_CONTINUE;
}


//=============================================================================
//
// 入力処理 [Input.cpp]
// Author : 
//
//=============================================================================
#include "Input.h"

//*****************************************************************************
// グローバル変数/静的メンバ変数
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;

bool CDirectXInput::m_bConnectionJoypad = false;
CDirectXInput::InputJoyState CDirectXInput::m_nState = INPUT_JOYSTATE_NOTPUSH;
//*****************************************************************************
//						クラス：CInput
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CInput::CInput() { m_pDevice = NULL; }
//=============================================================================
// デストラクタ
//=============================================================================
CInput::~CInput() {}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{//一個しか作らないようにする（NULLチェック）
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;

 }
//=============================================================================
// 終了処理
//=============================================================================
void CInput::Uninit(void)
{
	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();//アクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//*****************************************************************************
//						クラス：CInputKeyboard
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CInputKeyBoard::CInputKeyBoard()
{
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		if (m_aKeyState[nCnt] != 0)
		{
			m_aKeyState[nCnt] = 0;
		}
		if (m_aKeyStateTrigger[nCnt] != 0)
		{
			m_aKeyStateTrigger[nCnt] = 0;
		}
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CInputKeyBoard::~CInputKeyBoard() {}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//親クラスの初期化処理
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CInputKeyBoard::Uninit(void)
{
	//親クラスの終了処理
	CInput::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[MAX_KEY];

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{//キーボードの入力情報を保存
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();//キーボードアクセス権を獲得
	}
}
//=============================================================================
// プレス処理
//=============================================================================
bool CInputKeyBoard::GetKeyboardPress(int nkey)
{
	return(m_aKeyState[nkey] & 0x80) ? true : false;
}
//=============================================================================
// トリガー処理
//=============================================================================
bool CInputKeyBoard::GetKeyboardTrigger(int nkey)
{
	return(m_aKeyStateTrigger[nkey] & 0x80) ? true : false;

}

//*****************************************************************************
//class CDirectXInput
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CDirectXInput::CDirectXInput() {}
//=============================================================================
// デストラクタ
//=============================================================================
CDirectXInput::~CDirectXInput() {}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CDirectXInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//親クラスの初期化処理
	CInput::Init(hInstance, hWnd);

	m_nState = INPUT_JOYSTATE_NOTPUSH;
	m_bConnectionJoypad = false;

	DWORD dwResult;
	for (DWORD dCnt = 0; dCnt < MAX_CONTROLLERS; dCnt++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// XInputからコントローラの状態を取得する
		dwResult = XInputGetState(dCnt, &state);

		if (dwResult == ERROR_SUCCESS)
		{
#ifdef _DEBUG
			//MessageBox(0, "コントローラーが接続されています", "", MB_OK);
#endif // _DEBUG
			// デッドゾーンの設定
			if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbLX = 0;
				state.Gamepad.sThumbLY = 0;
			}

			if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbRX = 0;
				state.Gamepad.sThumbRY = 0;
			}

			m_bConnectionJoypad = true;
		}
		else
		{
#ifdef _DEBUG
			//MessageBox(0, "コントローラーが接続されていません", "", MB_OK);
#endif // _DEBUG

			m_bConnectionJoypad = false;
		}
	}
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CDirectXInput::Uninit(void)
{
	XInputEnable(false);

	//親クラスの終了処理
	CInput::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CDirectXInput::Update(void) {}
//=============================================================================
// インプットの状態の設定
//=============================================================================
void CDirectXInput::SetInputJoyState(CDirectXInput::InputJoyState state)
{
	m_nState = state;
}
//=============================================================================
// インプットの状態のリセット
//=============================================================================
void CDirectXInput::ResetInputJoyState(CDirectXInput::InputJoyState state)
{
	if (state == CDirectXInput::INPUT_JOYSTATE_PUSH)
	{
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_NONE);
	}
	else if (state == CDirectXInput::INPUT_JOYSTATE_NONE)
	{
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_NOTPUSH);
	}
}
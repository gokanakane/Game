//=============================================================================
// 入力処理 [Input.h]
// Author : 
//=============================================================================
#ifndef INPUT_H_
#define INPUT_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_KEY (256)

#define MAX_CONTROLLERS			(1)		//コントローラーの最大数
#define	NUM_JOYKEY_MAX			(128)	//キーの最大数
//*****************************************************************************
// インプットクラス
//*****************************************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;

};
//*****************************************************************************
// インプットキーボードクラス
//*****************************************************************************
class CInputKeyBoard : public CInput
{
public:
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyboardPress(int nkey);
	bool GetKeyboardTrigger(int nkey);

private:
	BYTE m_aKeyState[MAX_KEY];			//キーボード情報[Press]
	BYTE m_aKeyStateTrigger[MAX_KEY];	//キーボード情報[Trigger]
};
//*****************************************************************************
// コントローラークラス
//*****************************************************************************
class CDirectXInput : public CInput
{
public:
	typedef enum
	{//ボタンの押し状況
		INPUT_JOYSTATE_NOTPUSH = 0,
		INPUT_JOYSTATE_PUSH,
		INPUT_JOYSTATE_NONE,
	}InputJoyState;

	CDirectXInput();
	~CDirectXInput();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	static void SetInputJoyState(InputJoyState state);
	static bool GetConnectionJoypad(void) { return m_bConnectionJoypad; }
	static InputJoyState GetInputJoyState(void) { return m_nState; }
	static void ResetInputJoyState(InputJoyState state);

private:
	static InputJoyState m_nState;								//ジョイパッドの状態
	static bool m_bConnectionJoypad;			//ジョイパッドの接続状態
	LPDIRECTINPUTDEVICE8 m_pDevJoyPad = NULL;			//入力デバイス(ジョイパッド)へのポインタ
	BYTE m_aJoyKeyState[NUM_JOYKEY_MAX];				//ジョイパッドの入力情報(プレス情報)
	BYTE m_aJoyKeyStateTrigger[NUM_JOYKEY_MAX];			//ジョイパッドの入力情報(トリガー情報)
};
#endif // INPUT_H_
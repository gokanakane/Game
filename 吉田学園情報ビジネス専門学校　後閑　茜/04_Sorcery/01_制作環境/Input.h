//=============================================================================
// ���͏��� [Input.h]
// Author : 
//=============================================================================
#ifndef INPUT_H_
#define INPUT_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_KEY (256)

#define MAX_CONTROLLERS			(1)		//�R���g���[���[�̍ő吔
#define	NUM_JOYKEY_MAX			(128)	//�L�[�̍ő吔
//*****************************************************************************
// �C���v�b�g�N���X
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
// �C���v�b�g�L�[�{�[�h�N���X
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
	BYTE m_aKeyState[MAX_KEY];			//�L�[�{�[�h���[Press]
	BYTE m_aKeyStateTrigger[MAX_KEY];	//�L�[�{�[�h���[Trigger]
};
//*****************************************************************************
// �R���g���[���[�N���X
//*****************************************************************************
class CDirectXInput : public CInput
{
public:
	typedef enum
	{//�{�^���̉�����
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
	static InputJoyState m_nState;								//�W���C�p�b�h�̏��
	static bool m_bConnectionJoypad;			//�W���C�p�b�h�̐ڑ����
	LPDIRECTINPUTDEVICE8 m_pDevJoyPad = NULL;			//���̓f�o�C�X(�W���C�p�b�h)�ւ̃|�C���^
	BYTE m_aJoyKeyState[NUM_JOYKEY_MAX];				//�W���C�p�b�h�̓��͏��(�v���X���)
	BYTE m_aJoyKeyStateTrigger[NUM_JOYKEY_MAX];			//�W���C�p�b�h�̓��͏��(�g���K�[���)
};
#endif // INPUT_H_
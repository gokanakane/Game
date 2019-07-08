//=============================================================================
//
// �R���g���[���[���͏��� [DirectInput.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "DirectInput.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
HWND                  g_hWnd;
HINSTANCE             g_Inst;
LPDIRECTINPUT8        g_pDInput = NULL;     // DirectInput
LPDIRECTINPUTDEVICE8  g_pDIDev = NULL;     // DirectInput �f�o�C�X
POINT                 Pos, WPos;
DIDEVCAPS             g_diDevCaps;          // �W���C�X�e�B�b�N�̔\��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitDirectInput(void)
{
	HRESULT hr;

	// DirectInput�̍쐬
	hr = DirectInput8Create(g_Inst, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pDInput, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "DirectInput8�I�u�W�F�N�g�̍쐬�Ɏ��s", "Direct Input Error", MB_OK);
		return hr;
	}
	// �f�o�C�X��񋓂��č쐬
	hr = g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
		NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr) || g_pDIDev == NULL)
	{
		MessageBox(NULL, "DirectInputDevice8�I�u�W�F�N�g�̍쐬�Ɏ��s", "Direct Input Error", MB_OK);
		return hr;
	}
	// �f�[�^�`����ݒ�
	hr = g_pDIDev->SetDataFormat(&c_dfDIJoystick2);
	if (FAILED(hr))
	{
		MessageBox(NULL, "c_dfDIJoystick2�`���̐ݒ�Ɏ��s", "Direct Input Error", MB_OK);
		return hr;
	}
	//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = g_pDIDev->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�A�O���E���h����r�����[�h�̐ݒ�Ɏ��s", "Direct Input Error", MB_OK);
		return hr;
	}
	// �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
	hr = g_pDIDev->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�����[�h�̐ݒ�Ɏ��s", "Direct Input Error", MB_OK);
		return hr;
	}
	// ���͐���J�n
	g_pDIDev->Acquire();
	return S_OK;

}
//=============================================================================
// �I������
//=============================================================================
void UninitDirectInput(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateDirectInput(void)
{
	DIJOYSTATE2 dijs;
	HRESULT     hr;

	hr = g_pDIDev->GetDeviceState(sizeof(DIJOYSTATE2), &dijs);
	if (SUCCEEDED(hr))
	{
		if (dijs.rgbButtons[0] & 0x80)  //Y�{�^��
		{
			PostMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
		if (dijs.rgbButtons[1] & 0x80)//X�{�^��
		{
			PostMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
		if (dijs.lX) //�X�e�B�b�N
		{
			Pos.x += dijs.lX / 1000;
		}
		if (dijs.lY) //�X�e�B�b�N
		{
			Pos.y += dijs.lY / 1000;
		}
	}
	else if (hr == DIERR_INPUTLOST)  g_pDIDev->Acquire();

}
//=============================================================================
// �`�揈��
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
// �W���C�X�e�B�b�N��񋓂���֐�
//=============================================================================
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����B
	hr = g_pDInput->CreateDevice(pdidInstance->guidInstance, &g_pDIDev, NULL);
	if (FAILED(hr))     return DIENUM_CONTINUE;
	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	g_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = g_pDIDev->GetCapabilities(&g_diDevCaps);
	if (FAILED(hr))
	{   // �W���C�X�e�B�b�N�\�͂̎擾�Ɏ��s
		SAFE_RELEASE(g_pDIDev);
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;

}
//=============================================================================
// �W���C�X�e�B�b�N�̎���񋓂���֐�
//=============================================================================
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	HRESULT hr;

	// ���̒l�͈̔͂�ݒ�i-1000�`1000�j
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


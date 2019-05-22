//=============================================================================
//
// �R���g���[���[���͏��� [DirectInput.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef DIRECTINPUT_H_
#define DIRECTINPUT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\����
//*****************************************************************************
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitDirectInput(void);
void UninitDirectInput(void);
void UpdateDirectInput(void);
void DrawDirectInput(void);
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
#endif

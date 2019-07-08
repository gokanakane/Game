//=============================================================================
//
// �����_���[���� [Renderer.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
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
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }/* �|�C���^�Ԃ������̎� */
	static int m_nNumGet;

#ifdef _DEBUG
	void DrawFPS(void);
#endif

private:
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)

	float m_fAngle, m_fLenge, m_fChange;
#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
#endif
};

#endif

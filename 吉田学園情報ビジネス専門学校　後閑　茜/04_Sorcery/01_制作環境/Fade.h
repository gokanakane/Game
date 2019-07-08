//=============================================================================
//
// �t�F�[�h���� [Fade.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_SPEED (0.03f)
#define FADETEXTURE_NOWLOADING "data\\TEXTURE\\UI\\NowLoading.png"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CManager;
class CScene2D;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CFade : public CScene
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
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
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static FADEMODE m_fade;				// �t�F�[�h���
	static D3DXCOLOR m_colFade;		// �t�F�[�h�F
	static CManager::MODE m_modeNext;	// ���̃��[�h
	CScene2D *m_pScene2D;
};
#endif
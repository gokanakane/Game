//=============================================================================
//
// UI���� [uiBase.h]
// Author : 
//
//=============================================================================
#ifndef _BUTTON_H__
#define _BUTTON_H__

#include "main.h"
#include "scene.h"
#include "uiBase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �N���X�i�h���j�F�{�^��
//*****************************************************************************
class CButton :CScene2D
{
public:
	typedef enum
	{//�{�^���̏��
		BUTTONSTATE_NONE = 0,
		BUTTONSTATE_NORMAL,		//�ʏ햂�@�������ꂽ
		BUTTONSTATE_KIWAME,		//�ɖ��@�������ꂽ
		BUTTONSTATE_MAX
	}ButtonState;

	typedef enum
	{//�v���C���[���ǂ������������
		PLAYERPUSH_NONE = 0,
		PLAYERPUSH_NORMAL,
		PLAYERPUSH_KIWAME,
		PLAYERPUSH_MAX
	}PlayerPushButton;

	CButton();
	~CButton();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CButton *Create(CUi::Buttontype type);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetButtonType(CUi::Buttontype type);
	CUi::Buttontype GetBottunType(void) { return m_type; }
	static void SetButtonPush(bool bPush, PlayerPushButton Push);
	static bool GetPlayerPush(void) { return m_bPlayerPush; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_UITEXTURE];	//���L�e�N�X�`���ւ̃|�C���^
	ButtonState m_State;
	static int m_nMaxLife;
	static bool m_bPlayerPush;								//�v���C���[���{�^�����g�p���������肷��B
	static PlayerPushButton m_PlayerPush;
	bool m_bPushNormal, m_bPushKIWAME;
	float m_fNowLifeGauge;
	CUi::Buttontype m_type;
	int nCntWait;
};

#endif
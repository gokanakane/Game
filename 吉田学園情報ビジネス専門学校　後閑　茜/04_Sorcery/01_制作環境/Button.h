//=============================================================================
//
// UI処理 [uiBase.h]
// Author : 
//
//=============================================================================
#ifndef _BUTTON_H__
#define _BUTTON_H__

#include "main.h"
#include "scene.h"
#include "uiBase.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// クラス（派生）：ボタン
//*****************************************************************************
class CButton :CScene2D
{
public:
	typedef enum
	{//ボタンの状態
		BUTTONSTATE_NONE = 0,
		BUTTONSTATE_NORMAL,		//通常魔法が押された
		BUTTONSTATE_KIWAME,		//極魔法が押された
		BUTTONSTATE_MAX
	}ButtonState;

	typedef enum
	{//プレイヤーがどちらを押したか
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
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_UITEXTURE];	//共有テクスチャへのポインタ
	ButtonState m_State;
	static int m_nMaxLife;
	static bool m_bPlayerPush;								//プレイヤーがボタンを使用したか判定する。
	static PlayerPushButton m_PlayerPush;
	bool m_bPushNormal, m_bPushKIWAME;
	float m_fNowLifeGauge;
	CUi::Buttontype m_type;
	int nCntWait;
};

#endif
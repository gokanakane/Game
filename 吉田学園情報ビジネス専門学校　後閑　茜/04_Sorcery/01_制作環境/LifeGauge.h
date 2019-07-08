//=============================================================================
//
// 体力ゲージ処理 [LifeGauge.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _LIFEGAUGE_H__
#define _LIFEGAUGE_H__

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;
class CLifeGauge;
class CButton;
class CTime;

//*****************************************************************************
// クラス（派生）：ライフゲージ
//*****************************************************************************
class CLifeGauge :CScene2D
{
public:
	typedef enum
	{//体力の状態
		LIFESTATE_NONE = 0,
		LIFESTATE_MARGIN,		//体力50%以上
		LIFESTATE_HALF,			//体力50%以下
		LIFESTATE_PINCH,		//体力30%以下
		LIFESTATE_MAX
	}LifeState;

	CLifeGauge();
	~CLifeGauge();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CLifeGauge *Create();
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャへのポインタ
	static LifeState m_State;
	static int m_nMaxLife;
	float m_fNowLifeGauge;
};

#endif
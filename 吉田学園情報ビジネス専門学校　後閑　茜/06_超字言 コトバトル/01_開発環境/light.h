//=============================================================================
//
// ライト処理 [light.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT	(5)

//========================================
// クラスの定義
//========================================
//=====================
// ライトクラス
//=====================
class CLight
{
public:
	CLight();		// コンストラクタ
	~CLight();		// デストラクタ

	void Init(void);
	void Uninit(void);
	void Update(void);

	static void SetLight(int nNum,D3DLIGHT9 light) { m_light[nNum] = light; }
	static D3DLIGHT9 GetLight(int nNum) { return m_light[nNum]; }
private:
	static D3DLIGHT9 m_light[MAX_LIGHT];	// ライトの情報
};

#endif
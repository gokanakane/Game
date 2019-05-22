//=============================================================================
//
// カットイン処理 [cutin.h]
// Author : 
//
//=============================================================================
#ifndef _CUTINBASE_H_
#define _CUTINBASE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_CUTINTEX (2)
#define CUTINTEX_KIWAME "data\\TEXTURE\\Cutin\\CutIn_KIWAME.png"
#define CUTINTEX_NORMAL "data\\TEXTURE\\Cutin\\CutIn_NORMAL.png"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス
//*****************************************************************************
class CCutIn :public CScene2D
{
public:
	typedef enum
	{
		CUTINTYPE_NONE =0,
		CUTINTYPE_NORMAL,
		CUTINTYPE_KIWAME,
		CUTINTYPE_MAX
	}CutinType;

	CCutIn();
	~CCutIn();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCutIn *Create(CutinType type, CManager::CHARACTORSELECT_STATE state);
	static HRESULT Load(void);
	static void UnLoad(void);

protected:
	int m_nCntPlayCutImNormal,m_nCntPlayCutInKIWAME;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_CUTINTEX];	//共有テクスチャへのポインタ
};
#endif // _CUTIN_H_


//=============================================================================
//
// シーン2Dポリゴン処理 [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _NUBER_H
#define _NUBER_H

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NUMBER "data\\TEXTURE\\UI\\Number000.png"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber*Create(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos, int nCnt, float SizeX, float SizeY);
	void SetCol(D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
};

#endif

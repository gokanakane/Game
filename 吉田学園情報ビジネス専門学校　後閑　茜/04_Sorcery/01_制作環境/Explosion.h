//=============================================================================
//
// 爆発処理 [Explosion.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_EXPLOSION "data\\TEXTURE\\Effect\\explosion000.png"
#define MAX_ANIMATION (8)
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CExplosion *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャへのポインタ
	D3DXVECTOR3 m_pos;
	int m_nCntAnim;							//アニメーションカウンター
	int m_nPatturnAnim;						//アニメーションパターン数
};

#endif

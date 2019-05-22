//=============================================================================
//
// シーン2Dポリゴン処理 [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _SCENE2D_H
#define _SCENE2D_H

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_SIZE (15.0f)
//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D*Create(void);
	void SetScene2D(D3DXVECTOR3 pos, float sizeW, float sizeH);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void);
	void BindTexture(LPDIRECT3DTEXTURE9 Texture);
	void SetScroll(int nCnt,float fSpeed);
	void SetAlpha(D3DXCOLOR col);
	void SetColor(D3DXCOLOR col);
	void SetAnimX(int MaxPattarn, int MaxPattarnY, int nPattarn);	//X軸でのみ移動するアニメーション
	void SetAnimY(int MaxPattarn, int MaxPattarnY, int nPattarn);	//Y軸でのみ移動するアニメーション
	void SetCharaAnim(int nPattarn, float TexsliceY);
	void SetSize(float sizeW, float sizeH);
	void SetScene2DLeftCenter(D3DXVECTOR3 pos, float sizeW, float sizeH);//左を中心座標にするポリゴンの位置設定
	void SetRotation(float sizeW, float sizeH, float Angle);

protected:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// 頂点バッファへのポインタ

private:
	D3DXVECTOR3	m_pos;				// ポリゴンの位置、回転
	int m_TexNum;
	float m_fWidth, m_fHeight, m_fAngle, m_fLenge;		//横幅、縦幅、角度、距離
};

#endif

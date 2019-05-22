//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_MOVE (10.0f)
#define TEXTURE_BULLET "data\\TEXTURE\\Bullet\\bullet000.png"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEffect;

//*****************************************************************************
// クラス（派生）
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	typedef enum
	{//弾の種類タイプ
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER,		//通常弾
		BULLETTYPE_DRAIN,		//吸血弾
		BULLETTYPE_ENEMY,
		BULLETTYPE_MAX,
	}BULLETTYPE;

	CBullet();
	~CBullet();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos, BULLETTYPE type,float direction);
	void SetBullet(D3DXVECTOR3 pos, int nLife);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;					//共有テクスチャへのポインタ
	D3DXVECTOR3 m_pos;										//位置
	int m_nLife;											//弾の飛ぶ長さ
	float m_moveDirection;									//移動方向
	BULLETTYPE m_BulletType;								//弾の種類
	CEffect *m_pEffect;										//エフェクト
	float m_pos_x, m_pos_y, m_fAngle, m_move_x, m_move_y;	//Xの長さ・Yの長さ・角度・Xの移動量・Yの移動量
};

#endif

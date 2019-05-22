//=============================================================================
//
// オプション [option.h]
// Author : 
//
//=============================================================================
#ifndef _OPTIONBASE_H_
#define _OPTIONBASE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_OPTION_SHIELD "data\\TEXTURE\\Option\\Option000.png"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class COption :public CScene2D
{
public:
	typedef enum
	{
		OPTIONTYPE_NONE = 0,
		OPTIONTYPE_SHIELD,		//カーネリアン盾
		OPTIONTYPE_ABYSSGATE,	//ビビアン奈落門
		OPTIONTYPE_PUTBULLET,	//リリィカルト設置弾
		OPTIONTYPE_BEAM,		//蓮華ビーム
		OPTIONTYPE_MAX
	}OptionType;


	COption();
	~COption();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static COption *Create(OptionType type, D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void UnLoad(void);

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャへのポインタ

};
#endif
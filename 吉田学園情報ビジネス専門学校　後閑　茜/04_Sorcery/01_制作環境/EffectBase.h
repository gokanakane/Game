//=============================================================================
//
// �G�t�F�N�g��Տ��� [EffectBase.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _EFFECTBASE_H
#define _EFFECTBASE_H

#include "main.h"
#include "scene2D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAGICTEAM "data\\TEXTURE\\Effect\\Magicteam000.jpg"
#define TEXTURE_BULLETEFFECT "data\\TEXTURE\\Effect\\effect000.jpg"
#define TEXTURE_STAR "data\\TEXTURE\\Effect\\effect001.jpg"
#define MAX_EFFECTTEX (3)
#define MAX_MAGICEFFECTCREATE (8)

#define EFFECTCOL_DORAGON (D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define EFFECTCOL_KARNERIAN (D3DXCOLOR(1.0f,0.5f,0.0f,1.0f))
#define EFFECTCOL_VIVIAN (D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))
#define EFFECTCOL_AREISTA (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define EFFECTCOL_RENGE (D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define EFFECTCOL_LILIY (D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))
#define EFFECTCOL_ENEMY (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CEffect:public CScene2D
{
public:

	typedef enum
	{
		EFFECTTYPE_NONE = 0,
		EFFECTTYPE_BULLET,		//�e
		EFFECTTYPE_FALL,		//�~��
		EFFECTTYPE_MAGIC,		//���@�g�p��
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffect(int Priority = 2);
	virtual ~CEffect();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static CEffect*Create(D3DXVECTOR3 pos, EFFECTTYPE eftype, D3DXCOLOR col);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetEffect(D3DXVECTOR3 pos, float sizeW, float sizeH,EFFECTTYPE type);

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EFFECTTEX];	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;										// �ʒu���W
	float m_fSizeW, m_fSizeH;								// �����ƕ�
	EFFECTTYPE m_EffectType;								// �G�t�F�N�g�̃^�C�v
	int m_nLife;											// ����
};
#endif

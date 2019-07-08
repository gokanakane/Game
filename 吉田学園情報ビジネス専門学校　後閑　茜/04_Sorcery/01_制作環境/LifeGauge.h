//=============================================================================
//
// �̗̓Q�[�W���� [LifeGauge.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _LIFEGAUGE_H__
#define _LIFEGAUGE_H__

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;
class CLifeGauge;
class CButton;
class CTime;

//*****************************************************************************
// �N���X�i�h���j�F���C�t�Q�[�W
//*****************************************************************************
class CLifeGauge :CScene2D
{
public:
	typedef enum
	{//�̗͂̏��
		LIFESTATE_NONE = 0,
		LIFESTATE_MARGIN,		//�̗�50%�ȏ�
		LIFESTATE_HALF,			//�̗�50%�ȉ�
		LIFESTATE_PINCH,		//�̗�30%�ȉ�
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
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`���ւ̃|�C���^
	static LifeState m_State;
	static int m_nMaxLife;
	float m_fNowLifeGauge;
};

#endif
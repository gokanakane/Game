//=============================================================================
//
// UI���� [uiBase.h]
// Author : 
//
//=============================================================================
#ifndef _TUTORIALUI_H__
#define _TUTORIALUI_H__

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �N���X�i�h���j�F�`���[�g���A��UI
//*****************************************************************************
class CTutorialUi :CScene2D
{
public:
	typedef enum
	{//UI�̎��
		TUTORIALUITYPE_NONE = 0,
		TUTORIALUITYPE_ENTER_OR_A,
		TUTORIALUITYPE_MAX
	}TutorialUiType;

	CTutorialUi();
	~CTutorialUi();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTutorialUi *Create(CTutorialUi::TutorialUiType type);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetType(TutorialUiType type) { m_Type = type; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAXTEXTURE_TUTORIALUI];	//���L�e�N�X�`���ւ̃|�C���^
	TutorialUiType m_Type;

};

#endif
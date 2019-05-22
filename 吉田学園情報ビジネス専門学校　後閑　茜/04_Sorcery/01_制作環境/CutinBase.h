//=============================================================================
//
// �J�b�g�C������ [cutin.h]
// Author : 
//
//=============================================================================
#ifndef _CUTINBASE_H_
#define _CUTINBASE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_CUTINTEX (2)
#define CUTINTEX_KIWAME "data\\TEXTURE\\Cutin\\CutIn_KIWAME.png"
#define CUTINTEX_NORMAL "data\\TEXTURE\\Cutin\\CutIn_NORMAL.png"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X
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
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_CUTINTEX];	//���L�e�N�X�`���ւ̃|�C���^
};
#endif // _CUTIN_H_


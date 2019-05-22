//=============================================================================
//
// �e���� [title.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURERESULT (2)
#define TEXTURE_RESULT_LOGO		"data\\TEXTURE\\Result\\Resul_Logo.png"
#define TEXTURE_RESULT_SCORE	"data\\TEXTURE\\Result\\Resul_Score.png"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;
class CScene2D;
class CScore;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CResult
{
public:
	typedef enum
	{
		RESULTLOGOSTATE_NONE = 0,
		RESULTLOGOSTATE_FADEIN,
		RESULTLOGOSTATE_MAX
	}ResultLogoState;

	CResult();
	~CResult();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURERESULT];	// �e�N�X�`���ւ̃|�C���^
	static CBg *m_pBG;
	ResultLogoState m_state;
	CScene2D *m_apScene2D[MAX_TEXTURERESULT];
	int m_nCntMode;
	float m_LogoMove,m_LogoAlpha,m_ScoreMove,m_ScoreAlpha;
	D3DXVECTOR3 m_Logopos, m_GoalLogopos,m_Scorepos,m_GoalScorepos;
	D3DXCOLOR m_Col,m_Scorecol;
	static bool m_MakeScore;

};
#endif
//=============================================================================
//
// �e���� [title.h]
// Author : 
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_STAGEICON_STAGEICON	"data\\TEXTURE\\StageSelect\\StageIcon_Item.png"
#define TEXTURE_STAGESUBTITLES		"data\\TEXTURE\\StageSelect\\StageSelect_subtitles.png"
#define TEXTURE_STAGECOMMENTWINDOW	"data\\TEXTURE\\StageSelect\\StageCommentary.png"
#define TEXTURE_STAGECOMMENT		"data\\TEXTURE\\StageSelect\\StageComment.png"
#define TEXTURE_STAGEICON_CURSOR	"data\\TEXTURE\\UI\\cursor000.png"
#define TEXTURE_STAGEICON_CURSORUI	"data\\TEXTURE\\UI\\cursor001.png"
#define MAX_TEXTURE_STAGESELECT (6)
#define MAX_STAGESELECT_POLYGON (10)
#define MAX_SELECTSTAGE (4)
#define DEFAULT_ICONSIZE (80.0f)
#define EXPANSION_ICONSIZE (180.0f)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CStageSelect
{
public:
	typedef enum
	{//�I���X�e�[�W�̐F
		STAGESELECTCOL_NONE = 0,
		STAGESELECTCOL_STAGE1,
		STAGESELECTCOL_STAGE2,
		STAGESELECTCOL_STAGE3,
		STAGESELECTCOL_STAGE4,
		STAGESELECTCOL_MAX
	}StageSelectCol;

	CStageSelect();
	~CStageSelect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetMove(int nNum);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_STAGESELECT];	//���L�e�N�X�`���ւ̃|�C���^
	static CBg *m_pBG;
	static CScene2D *m_apScene2D[MAX_TEXTURE_STAGESELECT];
	int m_nSelectNum;
	CManager::StageSelectState m_StageSelectState;
	StageSelectCol m_StageSelectCol;
	D3DXVECTOR3 m_pos, m_posOld[MAX_SELECTSTAGE + 2];
	float m_fCntMove, m_fChengeMove;
};
#endif
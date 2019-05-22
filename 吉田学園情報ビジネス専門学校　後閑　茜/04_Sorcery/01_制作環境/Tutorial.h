//=============================================================================
//
// 弾処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _TUTORIAL_H
#define _TUTORIAL_H

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TUTORIALTEX (6)
#define MAXTUTORIALPOLYGON (7)
#define TEXTURE_DESXRIPTIONBOOK		"data\\TEXTURE\\Tutorial\\Tutorial_Description-1.png"
#define TEXTURE_NARRATOR			"data\\TEXTURE\\Tutorial\\Tutorial_Sagetu.png"
#define TEXTURE_NARRATORSUBTITLE	"data\\TEXTURE\\Tutorial\\Tutorial_Narrator.png"
#define TEXTURE_SKIP				"data\\TEXTURE\\Tutorial\\Tutorial_Skip.png"
#define TEXTURE_LECTURE				"data\\TEXTURE\\Tutorial\\Tutorial_lecture.png"
#define TEXTURE_CHARACTORSKILL		"data\\TEXTURE\\Tutorial\\CharactorSelext_Status001.png"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CScene2D;
class CEnemy;
//*****************************************************************************
// クラス
//*****************************************************************************
class CTutorial
{
public:
	typedef enum
	{//ナレーションの状態
		NARRATORSTATE_STEP1 = 0,	//挨拶
		NARRATORSTATE_STEP2,		//スキップについて
		NARRATORSTATE_STEP3,		//移動について
		NARRATORSTATE_STEP4,		//敵について
		NARRATORSTATE_STEP5,		//弾発射について
		NARRATORSTATE_STEP6,		//スコアについて
		NARRATORSTATE_STEP7,		//体力について
		NARRATORSTATE_STEP8,		//運命線について
		NARRATORSTATE_STEP9,		//魔法について
		NARRATORSTATE_STEP10,		//魔法の注意事項
		NARRATORSTATE_STEP11,		//ポーズについて
		NARRATORSTATE_STEP12,		//困ったら見てね
		NARRATORSTATE_STEP13,		//行ってらっしゃい
		NARRATORSTATE_MAX
	}NarratorState;

	typedef enum
	{//マスクの状態
		MASKALPHASTATE_NONE = 0,
		MASKALPHASTATE_FADEIN,
		MASKALPHASTATE_FADEOUT,
		MASKALPHASTATE_MAX
	}MaskAlphaState;

	typedef enum
	{//説明文
		LECTURESTATE_NONE = 0,
		LECTURESTATE_APPEARANCE,		//登場
		LECTURESTATE_EXIT,				//退場
		LECTURESTATE_MAX
	}LectureState;

	typedef enum
	{//説明文
		CHARACTORSKILLSTATE_NONE = 0,
		CHARACTORSKILLSTATE_APPEARANCE,		//登場
		CHARACTORSKILLSTATE_EXIT,			//退場
		CHARACTORSKILLSTATE_MAX
	}CharactorSkillState;

	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static NarratorState GetNarratorState(void) { return m_state; }
	static void SetMake(bool Make) { m_bMake = Make; }
	static void SetSkillUSe(bool Use) { m_SkillUse = Use; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TUTORIALTEX];	//共有テクスチャへのポインタ
	static CBg *m_pBG;
	static NarratorState m_state;
	static MaskAlphaState m_MaskState;
	static LectureState m_LectureState;
	static CharactorSkillState m_CharactorSkill;
	static bool m_SkillUse;
	static bool m_bMake,m_ButtonMake,m_bdisplay;
	D3DXVECTOR3 m_pos,m_Goalpos,m_StartPos;
	CScene2D *m_apScene2D[MAX_TUTORIALTEX];
	D3DXCOLOR m_col,m_MaskCol,m_LectureCol;
	float m_fChangeAlpha,m_fMaskAlpha,m_fLectureAlpha,m_fLecturepos;
	int m_nCntRandomEnemyMake;
};
#endif
//=============================================================================
//
// 弾処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _CHARACTERSELECT_H_
#define _CHARACTERSELECT_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXTURE_CHARACTORSELECT (10)
#define MAX_CHARACTORPOLYGON (12)
#define TEXTURE_CHARACTORNAME_PC6		 "data\\TEXTURE\\CharactorSelect\\CharactorSelect_Name000.png"
#define TEXTURE_CHARACTORNAME_PC3		 "data\\TEXTURE\\CharactorSelect\\CharactorSelect_Name001.png"
#define TEXTURE_CHARACTORSTATUS_PC6		 "data\\TEXTURE\\CharactorSelect\\CharactorSelext_Status001.png"
#define TEXTURE_CHARACTORSTATUS_PC3		 "data\\TEXTURE\\CharactorSelect\\CharactorSelext_Status2001.png"
#define TEXTURE_CHARACTORSELECT_SUBTITLE "data\\TEXTURE\\CharactorSelect\\CharactorSelect_subtitles.png"
#define TEXTURE_PLAYERICON_DRAGON		 "data\\TEXTURE\\Player\\player000.png"
#define TEXTURE_PLAYERICON_KARNERIAN	 "data\\TEXTURE\\Player\\Player001.png"
#define TEXTURE_PLAYERICON_VIVIAN		 "data\\TEXTURE\\Player\\Player002.png"
#define TEXTURE_PLAYERICON_AREISTA		 "data\\TEXTURE\\Player\\player003.png"
#define TEXTURE_PLAYERICON_RENGE		 "data\\TEXTURE\\Player\\player004.png"
#define TEXTURE_PLAYERICON_LILIY		 "data\\TEXTURE\\Player\\player005.png"
#define TEXTURE_CHARACTORMASK			 "data\\TEXTURE\\CharactorSelect\\CharactorSelect_DontSelect.png"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
//*****************************************************************************
// クラス
//*****************************************************************************
class CCharactorSelect
{
public:
	typedef enum
	{//色と位置
		CHARACTORSELECTCOL_NONE = 0,
		CHARACTORSTATECOL_DORAGON,		//ドラグーン
		CHARACTORSTATECOL_KARNERIAN,	//カーネリアン
		CHARACTORSTATECOL_VIVIAN,		//ビビアン
		CHARACTORSTATECOL_AREISTA,		//アレイスタ
		CHARACTORSTATECOL_RENGE,		//蓮華
		CHARACTORSTATECOL_LILIY,		//リリィカルト
		CHARACTORSTATECOL_MAX
	}CHARACTORSELECT_COL;

	CCharactorSelect();
	~CCharactorSelect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	void CharactorAnimation(int nNum);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_CHARACTORSELECT];	//共有テクスチャへのポインタ
	static CBg *m_pBG;
	int nCntFade, m_nSelectNum,m_nCntAnim,m_nPattarnAnim;
	static CScene2D *m_apScene2D[MAX_CHARACTORPOLYGON];
	CManager::CHARACTORSELECT_STATE m_SelectState;
	static CManager::StageSelectState m_SelectStage;
	CHARACTORSELECT_COL m_SelectCol;
};
#endif
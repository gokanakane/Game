//=============================================================================
//
// ステージセレクトの処理 [StageSelect.h]
// Author : 目黒未来也
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CFade;
class CManager;
class CSetObject;
class CMeshField;
class CWall;
class CPlayerSelect;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_STAGESELECT		(2)
#define MAX_STAGESELECT_TEX (7)

class CStageSelect
{
public:
	CStageSelect();
	~CStageSelect();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CStageSelect *Create(void);
	static int GetStageState(void) { return m_nSelect; }

private:
	/* ポリゴンの種類 */
	typedef enum
	{
		STAGESELECTTYPE_BG = 0,			//背景
		STAGESELECTTYPE_BAND_L,			//帯：左
		STAGESELECTTYPE_BAND_R,			//帯：右
		STAGESELECTTYPE_FRAME,			//字幕枠
		STAGESELECTTYPE_EXPLANATION,	//字幕
		STAGESELECTTYPE_UI_OPERATION,	//操作UI
		STAGESELECTTYPE_UI_DECISION,	//選択中UI
		STAGESELECTTYPE_MAX				//最大数
	}STAGESELECTTYPE;

	/* 選択状態 */
	typedef enum
	{
		SELECTTYPE_SELECT_MACHINE = 0,			//機械ステージ
		SELECTTYPE_SELECT_WEATHER,				//天候ステージ
		SELECTTYPE_MAX							//状態の総数
	}SELECTTYPE;

	/* ステージ読み込みの状態 */
	typedef enum
	{
		STAGELOAD_NONE = 0,
		STAGELOAD_LOAD,
		STAGELOAD_UNLOAD,
		STAGELOAD_MAX
	}STAGELOAD;

	/* マスクのフェード状態 */
	typedef enum
	{
		MASKFADE_NONE = 0,
		MASKFADE_IN,
		MASKFADE_OUT,
		MASKFADE_MAX
	}MASKFADE;

	void InitPolygon(void);												//ポリゴンの初期設定
	void ScrollMenu(STAGESELECTTYPE type, float fScroolSpeed);			//テクスチャスクロール処理
	void Selecttype(SELECTTYPE state, CFade *pFade, CManager *pManager);//選択状態の管理
	void ProductionIcon(SELECTTYPE type);								//選択肢の移動演出
	void SetStage(int nNumState);										//ステージ生成の処理
	void LoadStage(int nNum);											//ステージのロード処理
	void StageLoadState(STAGELOAD Load,int nSel);						//ステージロードの状態
	void MaskFade(void);												//マスクのフェード処理
	void InitPointer(void);												//ポインタの初期化処理
	void SetSelectAnimation(STAGESELECTTYPE type, int AnimType, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed);

	/* 変数 */
	static CScene2D *m_apScene2D[MAX_STAGESELECT_TEX];				//演出系2D
	static CScene2D *m_apSelect2D[MAX_STAGESELECT];					//選択肢2D
	static CScene2D *m_pMask2D;										//カメラマスク
	static int	m_nSelect;											// 選択している番号
	static CMeshField *m_pMeshField;								//床
	static CWall *m_pWall[4];										//壁
	SELECTTYPE m_type, m_typeOld;												//選択されている番号の状態
	char *m_pcStageSelect[MAX_STAGESELECT];							// ステージの名前保管
	CSetObject *m_pObj;

	/* 演出系変数 */
	int m_nCntScrool;												//スクロールのカウンター
	D3DXVECTOR3 m_SelectPos[MAX_STAGESELECT];						//セレクトの位置を保存
	float m_fWidth[MAX_STAGESELECT], m_fHeight[MAX_STAGESELECT];	//縦と横の形を保存しておく
	D3DXCOLOR m_IconCol[MAX_STAGESELECT];							//色を保存しておく
	D3DXVECTOR3 m_CameraRot, m_CameraPosV,m_CameraPosR;				//カメラ
	bool m_bLoad;													//ステージの読み込みを１回だけやるフラグ
	MASKFADE m_MaskFade;											//マスクのフェード処理
	float m_fMaskAlpha;
	int m_nCntAnim;													//アニメーションのカウンター
	int m_nPatturnAnim;												//アニメーションのパターン

#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif
};
#endif
//=============================================================================
//
// シーン処理 [scene.h]
// Author : 
//
//=============================================================================
#ifndef _SCENE_H
#define _SCENE_H

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_POLYGON (1000)				//ポリゴンの最大数
#define MAX_MYPRIORITY (8)				//優先順位(自分で設定した数)
//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス
//*****************************************************************************
class CScene
{
public:
	/* オブジェクトの種類（増えたら追加する） */
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_TUTORIAL,
		OBJTYPE_TITLE,
		OBJTYPE_RANKING,
		OBJTYPE_STAGESELECT,
		OBJTYPE_BG,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOTION,
		OBJTYPE_SCORE,
		OBJTYPE_EFFECT,
		OBJTYPE_FADE,
		OBJTYPE_PAUSE,
		OBJTYPE_UI,
		OBJTYPE_CUTIN,
		OBJTYPE_SHIELD,
		OBJTYPE_ABYSSGATE,
		OBJTYPE_PUTBULLET,
		OBJTYPE_MAX
	}OBJTYPE;

	/* 7:　6:フェード　5:UI系　4:プレイヤー　3:敵　2:エフェクト　1:BG　0: */
	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void ReleaseAllFade(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	void SetObjtype(OBJTYPE type);
	OBJTYPE GetObjtype(void) { return m_Objtype; }
	static CScene *GetScene(int nPriority,int nIdx);

protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_MYPRIORITY][MAX_POLYGON];
	static int m_nNumAll;
	int m_nId = 0;			//自分自身の番号
	OBJTYPE m_Objtype;
	int m_nPriority = 0;	//優先順位
};

#endif

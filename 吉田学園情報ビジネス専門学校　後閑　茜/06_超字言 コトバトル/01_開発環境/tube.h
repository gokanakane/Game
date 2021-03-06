//=============================================================================
//
// 文字保管UIの処理 [tube.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _TUBE_H_
#define _TUBE_H_

#include "scene2D.h"
#include "word_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CTube : public CScene2D
{
public:
	CTube(int nPriority = 3, OBJTYPE objType = OBJTYPE_UI);											// コンストラクタ
	~CTube();										// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos);				// 2Dオブジェクト初期化処理
	virtual void Uninit(void);							// 2Dオブジェクト終了処理
	virtual void Update(void);							// 2Dオブジェクト更新処理
	virtual void Draw(void);							// 2Dオブジェクト描画処理

	static CTube *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,LPCSTR Tag, int nPriority = 3);				// オブジェクトの生成

	//設定の関数
	void SetWordNum(int nWordNum, int nNum, int nStock);
	void SetPoint(int nPoint, int nNum, bool bPoint);
	void SetAnswer(int nAnswer, int nStock);
	void SetStockNum(int nStock) { m_nStockNum = nStock; }
	void AllDelete(int nNum);
	void UninitChack(bool bFlag);	// 終了しているかどうかの確認
	void SetID(int nID) { m_nID = nID; }	// 番号設定

	bool GetFlag(void) { return m_bCreateFlag; }
private:
	void Collect(void);		//文字を集めてTexを生成
	void Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNum);
	void Toward(void);		// 向かっていく処理
	void WordCreate2D(void);	// 文字の表示
	void SizeChange(D3DXVECTOR2 size);
	void WordUninit();		// 文字取得後、消えるまでのカウント

	D3DXVECTOR3 m_AnswerPos;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_sizeAnswer;
	CScene2D *m_apWord[MAX_WORD];
	CScene2D *m_pAnswerModel[MAX_WORD];
	CScene2D *m_pShootingStar[MAX_WORD];
	int			m_anAnswerNum[MAX_WORD];
	int		    m_nAnswer;
	int			m_nID;
	int			m_nCntUninit;	// 文字取得後消えるまでの時間

	bool	 m_bModelTexFlag;
	bool	 m_bCreateFlag;
	bool	 m_bTowardFlag;	// 目的の場所に向かう処理
	bool	 m_bSizeFlag;	// サイズ変化のフラグ
	bool	 m_bUninitFlag;	// 終了フラグ
	int m_nAnswerModelNum;	// 答えの番号
	int m_nStockNum;

};

#endif
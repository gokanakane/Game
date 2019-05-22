//=============================================================================
//
// フォント処理 [font.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "font.h"			// フォント
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "input.h"			// 入力

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CFont *CFont::m_apFont[FONTNUM_MAX] = {};		// シーン

#ifdef _DEBUG
bool CFont::m_bDispAll = true;					// 表示
#else
bool CFont::m_bDispAll = false;					// 表示
#endif

char CFont::m_MessageData[CScene::OBJTYPE_MAX][MAX_MESSAGE] = {};

//=============================================================================
// コンストラクタ									(public)	*** CFont ***
//=============================================================================
CFont::CFont()
{
	for (int nCntFont = 0; nCntFont < FONTNUM_MAX; nCntFont++)
	{// シーンカウント
		if (m_apFont[nCntFont] == NULL)
		{// NULLの場合
			m_apFont[nCntFont] = this;				// 自分を代入
			m_nID = nCntFont;
			m_bDisp = false;

			if (nCntFont == FONTNUM_COMMAND ||
				nCntFont == FONTNUM_DEBUG) { m_bDisp = true; }

#ifdef _DEBUG
			if (nCntFont == FONTNUM_TEST) { m_bDisp = true; }
#endif
			break;
		}
	}
}

//=============================================================================
// デストラクタ										(public)	*** CFont ***
//=============================================================================
CFont::~CFont()
{

}

//=============================================================================
// 全開放処理										(public)	*** CScene ***
//=============================================================================
void CFont::ReleaseAll(void)
{
	for (int nCntFont = 0; nCntFont < FONTNUM_MAX; nCntFont++)
	{// シーンカウント
		if (m_apFont[nCntFont] != NULL)
		{// NULL以外の場合
		 // ポリゴン更新処理
			m_apFont[nCntFont]->Uninit();

			delete m_apFont[nCntFont];
			m_apFont[nCntFont] = NULL;
		}
	}
}

//=============================================================================
// 全描画処理										(public)	*** CScene ***
//=============================================================================
void CFont::DrawAll(void)
{
	static int nCntPress = 0;

	if (CManager::GetInputKeyboard()->GetPress(DIK_F1) == true)
	{
		nCntPress++;
		if (nCntPress == 60)
		{
			m_bDispAll = m_bDispAll ? false : true;
		}
	}
	else
	{
		nCntPress = 0;
	}

	if (m_bDispAll == true)
	{
		for (int nCntFont = 0; nCntFont < FONTNUM_MAX; nCntFont++)
		{// シーンカウント
			if (m_apFont[nCntFont] != NULL)
			{// NULL以外の場合
			 // ポリゴン更新処理
				m_apFont[nCntFont]->Draw();
			}
		}
	}
}

//=============================================================================
// 文字設定処理											(public)	*** CFont ***
//=============================================================================
void CFont::SetMessageData(CScene::OBJTYPE objType, SETTYPE nSetType, char *aMessage, ...)
{
	char cMessage[MAX_MESSAGE], cMessageCat[MAX_MESSAGE + (MAX_MESSAGE / 2)];
	cMessage[0] = '\0';	cMessageCat[0] = '\0';

	va_list arg;
	va_start(arg, aMessage);
	vsprintf(cMessage, aMessage, arg);
	va_end(arg);

	// 文字列を代入
	if (nSetType == 0)
	{
		wsprintf(&m_MessageData[objType][0], "%s", &cMessage[0]);
	}
	else if (nSetType == 1)
	{
		wsprintf(&cMessageCat[0], "%s", &m_MessageData[objType][0]);

		strcat(&cMessageCat[0], &cMessage[0]);
		cMessageCat[MAX_MESSAGE - 1] = '\0';

		wsprintf(&m_MessageData[objType][0], "%s", &cMessageCat[0]);
	}
	else if (nSetType == 2)
	{
		wsprintf(&cMessageCat[0], "%s", &cMessage[0]);

		strcat(&cMessageCat[0], &m_MessageData[objType][0]);
		cMessageCat[MAX_MESSAGE - 1] = '\0';

		wsprintf(&m_MessageData[objType][0], "%s", &cMessageCat[0]);
	}
}

//=============================================================================
// クリエイト										(public)	*** CFont ***
//=============================================================================
CFont *CFont::Create(int nHeight, int nWidth, int nWeight, RECT rect, UINT uFormat, D3DXCOLOR col)
{
	CFont *pFont = NULL;			// ポインタ

	if (pFont == NULL)
	{// NULLの場合
		pFont = new CFont;			// メモリ確保
	}

	if (pFont != NULL)
	{// NULL以外の場合
		pFont->Init(nHeight, nWidth, nWeight, rect, uFormat, col);		// 初期化処理
	}

	return pFont;
}

//=============================================================================
// 初期化処理										(public)	*** CFont ***
//=============================================================================
HRESULT CFont::Init(int nHeight, int nWidth, int nWeight, RECT rect, UINT uFormat, D3DXCOLOR col)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateFont(pDevice, nHeight, nWidth, nWeight, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas", &m_pFont);

	m_rect = rect;
	m_uFormat = uFormat;
	m_col = col;

	return S_OK;
}

//=============================================================================
// 終了処理											(public)	*** CFont ***
//=============================================================================
void CFont::Uninit(void)
{
	if (m_pFont != NULL)
	{// NULL以外の場合
		m_pFont->Release();			// 解放
		m_pFont = NULL;				// NULLへ
	}
}

//=============================================================================
// 更新処理											(public)	*** CFont ***
//=============================================================================
void CFont::Update(void)
{

}

//=============================================================================
// 描画処理											(public)	*** CFont ***
//=============================================================================
void CFont::Draw(void)
{
	if (m_pFont != NULL)
	{
		if (m_bDisp == true)
		{
			// テキスト描画
			m_pFont->DrawText(NULL, m_Message, -1, &m_rect, m_uFormat, m_col);
		}
	}
}

//=============================================================================
// 文字設定処理											(public)	*** CFont ***
//=============================================================================
void CFont::SetMessage(SETTYPE nSetType, char *aMessage, ...)
{
	char cMessage[MAX_MESSAGE], cMessageCat[MAX_MESSAGE + (MAX_MESSAGE / 2)];
	cMessage[0] = '\0';	cMessageCat[0] = '\0';

	va_list arg;
	va_start(arg, aMessage);
	vsprintf(cMessage, aMessage, arg);
	va_end(arg);

	// 文字列を代入
	if (nSetType == 0)
	{
		wsprintf(&m_Message[0], "%s", &cMessage[0]);
	}
	else if (nSetType == 1)
	{
		wsprintf(&cMessageCat[0], "%s", &m_Message[0]);

		strcat(&cMessageCat[0], &cMessage[0]);
		cMessageCat[MAX_MESSAGE - 1] = '\0';

		wsprintf(&m_Message[0], "%s", &cMessageCat[0]);
	}
	else if (nSetType == 2)
	{
		wsprintf(&cMessageCat[0], "%s", &cMessage[0]);

		strcat(&cMessageCat[0], &m_Message[0]);
		cMessageCat[MAX_MESSAGE - 1] = '\0';

		wsprintf(&m_Message[0], "%s", &cMessageCat[0]);
	}
}

//=============================================================================
// 開放処理											(protected)	*** CScene ***
//=============================================================================
void CFont::Release(void)
{
	if (m_apFont[m_nID] != NULL)
	{// NUll以外の場合
		int nID = m_nID;					// IDを保存（データの不定防止）

		delete m_apFont[nID];		// メモリ開放
		m_apFont[nID] = NULL;		// NULLへ
	}
}
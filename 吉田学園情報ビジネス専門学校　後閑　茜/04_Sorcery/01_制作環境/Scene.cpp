//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "Pause.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CScene *CScene::m_apScene[MAX_MYPRIORITY][MAX_POLYGON] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
	{
		if (m_apScene[nPriority][nCnt] == NULL)
		{//空だったらクリエイトされているものを代入する
			m_apScene[nPriority][nCnt] = this;
			m_nNumAll++;
			m_nId = nCnt;
			m_nPriority = nPriority;
			break;
		}
	}

	m_Objtype = OBJTYPE_NONE;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}
//=============================================================================
// すべてのポリゴンの開放処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_MYPRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{//メモリが残っている
					/* 終了処理 */
				m_apScene[nCntPriority][nCnt]->Uninit();

				/* メモリの開放 */
				delete m_apScene[nCntPriority][nCnt];
				m_apScene[nCntPriority][nCnt] = NULL;
			}
		}
	}

	m_nNumAll = 0;
}
//=============================================================================
// すべてのポリゴンの開放処理
//=============================================================================
void CScene::ReleaseAllFade(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_MYPRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{//メモリが残っている
				CScene::OBJTYPE objtype;
				objtype = m_apScene[nCntPriority][nCnt]->GetObjtype();		//オブジェクトのタイプが何か確認できる

				if (objtype != OBJTYPE_FADE)
				{
					/* 終了処理 */
					m_apScene[nCntPriority][nCnt]->Uninit();

					/* メモリの開放 */
					delete m_apScene[nCntPriority][nCnt];
					m_apScene[nCntPriority][nCnt] = NULL;
				}
			}
		}
	}

	m_nNumAll = 0;
}
//=============================================================================
// すべてのポリゴンの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_MYPRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{//メモリが残っている
				CManager::MODE mode = CManager::GetMode();
				if (mode == CManager::MODE_GAME)
				{
					bool bPause = CPause::GetPause();
					if (bPause == false)
					{
						/* 更新処理 */
						m_apScene[nCntPriority][nCnt]->Update();
					}
				}
				else
				{
					/* 更新処理 */
					m_apScene[nCntPriority][nCnt]->Update();
				}
			}
		}
	}
}
//=============================================================================
// すべてのポリゴンの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_MYPRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{//メモリが残っている
			 /* 描画処理 */
				m_apScene[nCntPriority][nCnt]->Draw();
			}
		}
	}
}
//=============================================================================
// オブジェクトの破棄
//=============================================================================
void  CScene::Release(void)
{
	/* deleteするとシーンの中身がなくなる。
	m_nId,m_mPriorityも消えるためどこを参照するかわからなくなるので、一度ローカル変数に移してやる必要がある。*/
	int nId, nPriority;
	nId = m_nId;
	nPriority = m_nPriority;

	if (m_apScene[nPriority][nId] != NULL)//m_apScene[this->m_nId]とも書ける
	{//空じゃなかったら消去
#if 0
		/* これじゃダメ */
		delete m_apScene[m_nId];		//解放
		m_apScene[m_nId];
		m_nNumAll--;					//最大数を減らす
#endif
		delete m_apScene[nPriority][nId];
		m_apScene[nPriority][nId] = NULL;
		m_nNumAll--;					//最大数を減らす
	}
}
//=============================================================================
// オブジェクトタイプの設定
//=============================================================================
void CScene::SetObjtype(const OBJTYPE type)
{
	m_Objtype = type;
}
//=============================================================================
// シーンの取得
//=============================================================================
CScene *CScene::GetScene(int nPriority, int nIdx)
{
	return m_apScene[nPriority][nIdx];
}
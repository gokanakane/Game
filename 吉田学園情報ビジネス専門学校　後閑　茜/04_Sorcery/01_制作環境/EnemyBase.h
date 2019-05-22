//=============================================================================
//
// 敵の基盤処理 [enemyBase.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYBASE_H_
#define _ENEMYBASE_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEX (3)
#define TEXTURE_ENEMY "data\\TEXTURE\\Enemy\\book001.png"
#define TEXTURE_BOSSENEMY_AIHA "data\\TEXTURE\\Enemy\\BossEnemy000.png"
#define TEXTURE_BOSSENEMY_WAKATU "data\\TEXTURE\\Enemy\\BossEnemy001.png"
#define TEXTURE_BOSSENEMY_MAYDAY "data\\TEXTURE\\Enemy\\BossEnemy002.png"
#define TEXTURE_BOSSENEMY_HEBI "data\\TEXTURE\\Enemy\\BossEnemy003.png"
#define TEXTURE_ENEMYRELATIVE "data\\TEXTURE\\Enemy\\EnemyRelative.png"
#define NORMALENEMY_MAXANIM (3)
//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス（親）
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	typedef enum
	{//敵の種類
		ENEMYTYPE_NONE = 0,		//何もない
		ENEMYTYPE_NORMAL,		//通常
		ENEMYTYPE_BOSS,			//ボス
		ENEMYTYPE_TUTORIAL,		//チュートリアル用
		ENEMYTYPE_RELATIVE,		//ボス敵の眷属
		ENEMYTYPE_MAX
	}EnemyType;

	typedef enum
	{//敵の状態
		ENEMYSTATE_NONE = 0,	//何もない
		ENEMYSTATE_DAMAGE,		//ダメージ
		ENEMYSTATE_DEATH,		//死亡
		ENEMYSTATE_EMERGENCE,	//無敵
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	CEnemy();
	virtual ~CEnemy();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static CEnemy *Create(D3DXVECTOR3 pos, EnemyType type,int nLife);
	static HRESULT Load(void);
	static void UnLoad(void);
	static void SetFinishGame(bool bFinishGame) { m_bFinishGame = bFinishGame; }	//リトライ選択でゲームが終わったかフラグ
	static void SetMaxNormalEnemy(int nNumMax) { m_nNumEnemyNormal = nNumMax; }		//通常敵の最大数の設定
	static int GetMaxNormalEnemy(void) { return m_nNumEnemyNormal; }				//通常敵の最大数の取得
	static void SetMaxBossEnemy(int nNum) { m_nNumEnemyBoss = nNum; }				//ボス敵の最大数の設定
	static int GetMaxBossEnemy(void) { return m_nNumEnemyBoss; }					//ボス敵の最大数の取得
	void SetEnemyState(ENEMYSTATE state) { m_EnemyState = state; }					//敵の状態の設定
	ENEMYSTATE GetEnemyState(void) { return m_EnemyState; }							//敵の状態の取得
	void SetEnemyType(EnemyType type) { m_EnemyType = type; }						//敵の種類の設定
	EnemyType GetEnemyType(void) { return m_EnemyType; }							//敵の種類の取得
	void SetLife(int nLife) { m_nLife = nLife; }									//敵の体力の設定

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX];	//共有テクスチャへのポインタ
	static int m_nNumEnemyNormal;					//通常敵の最大数
	static int m_nNumEnemyBoss;						//ボス敵の最大数
	static bool m_bFinishGame;						//リトライ選択でゲームが終わったかのフラグ
	D3DXVECTOR3 m_pos;								//位置
	ENEMYSTATE m_EnemyState;						//敵の状態
	EnemyType m_EnemyType;							//敵の種類
	int m_nLife,m_nMaxLife;							//敵の現在の体力、最大体力
	D3DXCOLOR m_col;								//色
	float m_Changecol;
	int m_nCntState;
};
#endif

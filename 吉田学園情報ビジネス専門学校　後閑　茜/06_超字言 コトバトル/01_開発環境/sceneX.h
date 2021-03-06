//=============================================================================
//
// 3Dモデル処理 [sceneX.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"
#include "load.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CSceneX : public CScene
{
public:
	//モデルの種類
	typedef enum
	{
		COLLISIONTYPE_NONE = 0,	//無し
		COLLISIONTYPE_BOX,		//箱
		COLLSIONTYPE_CONVEYOR_FRONT,	// 当たり判定(ベルトコンベア 前方)
		COLLSIONTYPE_CONVEYOR_RIHHT,	// 当たり判定(ベルトコンベア 右)
		COLLSIONTYPE_CONVEYOR_BACK,		// 当たり判定(ベルトコンベア 後方)
		COLLSIONTYPE_CONVEYOR_LEFT,		// 当たり判定(ベルトコンベア 左)
		COLLSIONTYPE_KNOCKBACK_SMALL,	// 当たり判定(ノックバック 小)
		COLLSIONTYPE_KNOCKBACK_DURING,	// 当たり判定(ノックバック 中)
		COLLSIONTYPE_KNOCKBACK_BIG,		// 当たり判定(ノックバック 大)
		COLLSIONTYPE_SWITCH,			// 当たり判定(スイッチ)
		COLLSIONTYPE_BREAK,				// 当たり判定(壊れる)
		COLLSIONTYPE_ICEFLOOR,			// 当たり判定(滑る床)
		COLLSIONTYPE_FLOORCOLLSION,		// 当たり判定(床の箱の当たり判定)
		COLLSIONTYPE_BUSH,				// 当たり判定(草むら)
	}COLLISIONTYPE;

	CSceneX(int nPriority = SCENEX_PRIORITY, OBJTYPE objType = OBJTYPE_SCENEX);					// コンストラクタ
	~CSceneX();									// デストラクタ
	HRESULT Init(void) { return S_OK; };
	HRESULT Init(D3DXVECTOR3 pos);				// 3Dオブジェクト初期化処理

	void Uninit(void);							// 3Dオブジェクト終了処理
	void Update(void);							// 3Dオブジェクト更新処理
	void Draw(void);							// 3Dオブジェクト描画処理

	static CSceneX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scale, CLoad::MODEL model, int nCollision = 0);	// オブジェクトの生成

	D3DXVECTOR3 GetPosition(void);		 				// 位置の取得
	void SetPosition(D3DXVECTOR3 pos);					// 位置の設定

	D3DXVECTOR3 GetRot(void);						// 向きの取得
	void SetRot(D3DXVECTOR3 rot);					// 向きの設定

	D3DXVECTOR3 GetVtxMax(void);						// 最大値の取得
	void SetVtxMax(D3DXVECTOR3 VtxMax);					// 最大値の設定

	D3DXVECTOR3 GetVtxMin(void);						// 最小値の取得
	void SetVtxMin(D3DXVECTOR3 VtxMin);					// 最小値の設定

	void SetVtx(void);																// 頂点座標の設定
	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius,int nPlayer);	// 当たり判定

	bool CollisionIN(D3DXVECTOR3 pos,D3DXVECTOR3 radius);		// 当たり判定 (範囲内かどうか)


	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);	// モデルを割り当てる
	void BindTex(LPDIRECT3DTEXTURE9	*m_pTexture);	// テクスチャマテリアルを割り当てる

	void SetCollsionType(COLLISIONTYPE type) { m_CollisionType = type; }
	COLLISIONTYPE GetCollsionType(void) { return m_CollisionType; }		// 当たり判定の種類を取得

	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }				// スケールを設定
	D3DXVECTOR3 GetScale(void) { return m_Scale; }						// スケールの取得

	void SetModelType(CLoad::MODEL model) { m_ModelType = model; }		// モデルの種類設定
	CLoad::MODEL GetModelType(void) { return m_ModelType; }				// モデルの種類取得

	bool GetDrawFlag(void) { return m_bDraw; };
	void SetDrawFlag(bool bDraw) { m_bDraw = bDraw; };
	int GetCollsionNum(void) { return m_nCollsionNum; }
	void SetParent(D3DXMATRIX* pParent) { m_pParentMatrix = pParent; };
	void SetCameraNum(int nCamera) { m_nCamera = nCamera; };

	void SetSceneXNum(int nNumber) { m_nBushNum = nNumber; };
	int GetSceneXNum(void) {return m_nBushNum; };
	static void SetTranslucentBush(int nPlayer,int nNumber) { m_nTranslucentBush[nPlayer] = nNumber; };
private:
	LPDIRECT3DTEXTURE9		*m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	LPD3DXMESH				m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	LPD3DXBUFFER			m_pBuffMat;			// マテリアル情報へのポインタ
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	DWORD					m_nNumMat;			// マテリアル情報の数
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// モデルの最小値、最大値
	D3DXVECTOR3				m_pos;				// ポリゴンの位置
	D3DXVECTOR3				m_rot;				// 上方向ベクトル
	D3DXVECTOR3				m_Scale;			// スケール
	CLoad::MODEL			m_ModelType;		// モデル番号
	COLLISIONTYPE			m_CollisionType;	// 当たり判定
	int						m_nCollsionNum;		// 当たり判定を行った場所

	bool					m_bDraw;			//透明化フラグ(falseで消える)
	bool					m_bTranslucent[4];	//半透明化フラグ(trueで消える)
	D3DXMATRIX*				m_pParentMatrix;	//親マトリックス
	int						m_nCamera;			//カメラの番号
	int						m_nBushNum;			//草の番号
	static int				m_nTranslucentBush[4]; //透明な草の番号
};

#endif
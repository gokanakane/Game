//=============================================================================
//
// オブジェクトの処理 [oblect.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "object.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "load.h"
#include "player.h"
#include "game.h"
#include "time.h"
#include "scene3D.h"
#include "effect.h"
#include "word.h"
#include "PlayerNumSelect.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BELTCONVEYER_MOVE			(0.15f)			// ベルトコンベアの速度
#define KNOCKBACK_MOVE_SMALL		(4.0f)			// ノックバックの強度(小)
#define KNOCKBACK_MOVE_DURING		(6.0f)			// ノックバックの強度(中)
#define KNOCKBACK_MOVE_BIG			(9.0f)			// ノックバックの強度(大)
#define GEAR_ROT_Y					(0.1f)			// ギアの回転量　ベース情報
#define MODEL_MOVE_Y				(-2.0f)			// モデル移動時の移動速度
#define AFFECTED_LANDING			(15.0f)			// モデル着地時のノックバック影響量

#define ANIM_TIME					(5)				// アニメーション時間
#define ANIM_FRAME					(10)			// フレーム数
#define ICON_SIZE_X					(80.0f)
#define ICON_SIZE_Y					(40.0f)
#define VIBRATION					(2.0f)
#define VIBRATION_MOVE				(4.0f)

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
bool CObject::m_bCreateFlag = false;
bool  CObject::m_bSwitch = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject()
{
	m_bMoveFlag = false;		// 移動フラグ
	m_bCreateFlag = false;
	m_pIcon = NULL;				// ベルトコンベアのアイコン
	m_nCntAnim = 0;
	m_nCntPattan = 0;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_InitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MoveState = 0;
	m_bSwitch = false;
	m_nCounter = 0;
	m_nTypeGimmick = GIMMICK_NONE;

}

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, CSceneX::COLLISIONTYPE type, CLoad::MODEL model, CObject::GIMMICKTYPE realtime,int nNumber)
{
	CObject *pObject = NULL;
	if (pObject == NULL)
	{
		// オブジェクトクラスの生成
		pObject = new CObject;

		if (pObject != NULL)
		{
			pObject->m_nObjNumber = nNumber;	//オブジェクトの番号設定
			pObject->SetModelType(model);
			pObject->BindModel(CLoad::GetBuffMat(model), CLoad::GetNumMat(model), CLoad::GetMesh(model));		// モデルの割り当て
			pObject->SetScale(Scale);	// スケールの設定
			pObject->m_nTypeGimmick = realtime;
			pObject->Init(pos);			// 初期化
			pObject->SetRot(rot);		// 向きの設定
			pObject->SetCollsionType(type);	// コリジョンのタイプ設定
		}
	}
	return pObject;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObject::Init(D3DXVECTOR3 pos)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_SCENEX);

	if (m_nTypeGimmick == GIMMICK_MOYE_Y || m_nTypeGimmick == GIMMICK_MOYE_STAGE) { m_nRealTime = REALTIME_INITPOS; }
	else if (m_nTypeGimmick == GIMMICK_NONE) { m_nRealTime = REALTIME_NONE; }

	CSceneX::Init(pos);
	m_posOld = pos;
	m_InitPos = pos;
	if (CSceneX::GetModelType() == CLoad::MODEL_DRAWN_X)
	{//ドローンX移動
		m_MoveState = 1;
	}
	else if (CSceneX::GetModelType() == CLoad::MODEL_DRAWN_Z)
	{//ドローンZ移動
		m_MoveState = 1;
	}
	//	初期の大きさの保存
	m_InitScale = CSceneX::GetScale();
	// 番号を設定
	CSceneX::SetSceneXNum(m_nObjNumber);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject::Uninit(void)
{
	if (m_pIcon != NULL)
	{	// アイコンの破棄
		m_pIcon->Uninit();
		m_pIcon = NULL;
	}
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObject::Update(void)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	D3DXVECTOR3 pos = CSceneX::GetPosition();	// 位置取得

	BGModelMove(pos);				// 背景モデルの移動

	if (m_nRealTime == REALTIME::REALTIME_NONE) { Rot(CSceneX::GetModelType()); return; }		// 何もない場合は何も通さない


	ModelMove(Collsiontype, pos);	// モデルの移動

	if (m_pIcon != NULL) { AnimationIcon(); }


#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RSHIFT))
	{	// 移動Flag変化用
		m_nRealTime = REALTIME_ENDPOS;
	}
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject::Draw(void)
{
	if (m_pIcon != NULL)
	{
		m_pIcon->Draw();
	}

	if (CSceneX::GetModelType() != CLoad::MODEL_BOX)
	{
		CSceneX::Draw();
	}
}

//=============================================================================
// /スイッチの処理
//=============================================================================
void CObject::SwitchBeltConveyor(bool bSwitch)
{
	CSound *pSound = CManager::GetSound();		//	音の取得
	D3DXVECTOR3 pos = CSceneX::GetPosition();

	if (bSwitch == true)
	{//	SwitchON
		m_nCounter++;
		if (m_nCounter > 120)
		{
			m_bSwitch = m_bSwitch ? false : true;
			if (m_bSwitch == true)
			{//	SwitchON
				pSound->SetVolume(CSound::SOUND_LABEL_SE_SWITCHON, 3.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SWITCHON);
			}
			else if (m_bSwitch == false)
			{
				pSound->SetVolume(CSound::SOUND_LABEL_SE_SWITCHOFF, 3.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SWITCHOFF);
			}
			m_nCounter = 0;
		}
		pos = D3DXVECTOR3(0.0f, -20.0, 0.0f);
		if (m_bSwitch == false)
		{//	SwitchOFF
			m_nCounter++;
			pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		}
	}
	SetPosition(pos);
}

//=============================================================================
// ベルトコンベアの処理
//=============================================================================
void CObject::BeltConveyor(D3DXVECTOR3 *pMove, bool bSwitch)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();

	switch (bSwitch)
	{
	case false:
		if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT)
		{	// 前進する
			pMove->z += BELTCONVEYER_MOVE;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_BACK)
		{	// 後退する
			pMove->z += -BELTCONVEYER_MOVE;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
		{	// 右移動
			pMove->x += -BELTCONVEYER_MOVE;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
		{	// 左移動
			pMove->x += BELTCONVEYER_MOVE;
		}
		break;
	case true:
		break;
	}
}

//=============================================================================
// 背景モデルの挙動処理
//=============================================================================
void CObject::BGModelMove(D3DXVECTOR3 pos)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = {};
	NumPlayer = *CPlayerSelect::GetModeSelectMode();	// プレイヤー人数取得
	D3DXVECTOR2 size = {};

	if (NumPlayer == CPlayerSelect::SELECTPLAYER_1P || NumPlayer == CPlayerSelect::SELECTPLAYER_2P) { size = MAX_SIZE; }
	else if (NumPlayer == CPlayerSelect::SELECTPLAYER_4P || NumPlayer == CPlayerSelect::SELECTPLAYER_3P) { size = MAX_SIZE_3or4; }

	D3DXVECTOR3 scale = CSceneX::GetScale();
	if (CSceneX::GetModelType() == CLoad::MODEL_DRAWN_X)
	{//　X座標の移動をするドローン
		m_nCounter++;
		int nAnswer = rand() % 48;
		//	使っていない文字の例外処理
		if (nAnswer == 0 || nAnswer == 2 || nAnswer == 4 || nAnswer == 6 || nAnswer == 8 || nAnswer == 11) { nAnswer = 1; }
		else if (nAnswer == 13 || nAnswer == 14 || nAnswer == 16 || nAnswer == 17 || nAnswer == 18 || nAnswer == 21) { nAnswer = 7; }
		else if (nAnswer == 22 || nAnswer == 23 || nAnswer == 25 || nAnswer == 26 || nAnswer == 28 || nAnswer == 29) { nAnswer = 15; }
		else if (nAnswer == 31 || nAnswer == 32 || nAnswer == 33 || nAnswer == 34 || nAnswer == 36 || nAnswer == 37) { nAnswer = 30; }
		else if (nAnswer == 38 || nAnswer == 39 || nAnswer == 43 || nAnswer == 44 || nAnswer == 45 || nAnswer == 46) { nAnswer = 35; }
		else if (nAnswer == 47 || nAnswer == 48) { nAnswer = 17; }
		if (m_nCounter % 780 == 0)
		{//	文字を出す
			if (CManager::GetMode() == CManager::MODE_GAME)
			{

				CWord::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size.x, size.y, "WORD", nAnswer, 1, 45);
				scale.y = m_InitScale.y + 0.2f;
				pos.y = m_InitPos.y + 4.0f;
				m_nCounter = 0;
			}
		}
		if (m_nCounter > 20)
		{//	大きさを戻す
			scale.y = m_InitScale.y;
			pos.y = m_InitPos.y;
		}
		if (m_InitPos.x + 200 <= pos.x)
		{//	初期位置から+250以上離れた場合
			m_MoveState = 2;
		}
		else if (m_InitPos.x - 200 >= pos.x)
		{//	初期位置から-250以上離れた場合
			m_MoveState = 1;
		}
		switch (m_MoveState)
		{//	動きのステータス
		case 0:
			m_move.x = 0.0f;
			break;
		case 1:
			m_move.x = 1.0f;
			break;
		case 2:
			m_move.x = -1.0f;
			break;
		}
		pos += m_move;				//	動きの加算

	}
	else if (CSceneX::GetModelType() == CLoad::MODEL_DRAWN_Z)
	{//　X座標の移動をするドローン
		m_nCounter++;
		int nAnswer = rand() % 48;
		//	使っていない文字の例外処理
		if (nAnswer == 0 || nAnswer == 2 || nAnswer == 4 || nAnswer == 6 || nAnswer == 8 || nAnswer == 11) { nAnswer = 1; }
		else if (nAnswer == 13 || nAnswer == 14 || nAnswer == 16 || nAnswer == 17 || nAnswer == 18 || nAnswer == 21) { nAnswer = 7; }
		else if (nAnswer == 22 || nAnswer == 23 || nAnswer == 25 || nAnswer == 26 || nAnswer == 28 || nAnswer == 29) { nAnswer = 15; }
		else if (nAnswer == 31 || nAnswer == 32 || nAnswer == 33 || nAnswer == 34 || nAnswer == 36 || nAnswer == 37) { nAnswer = 30; }
		else if (nAnswer == 38 || nAnswer == 39 || nAnswer == 43 || nAnswer == 44 || nAnswer == 45 || nAnswer == 46) { nAnswer = 35; }
		else if (nAnswer == 47 || nAnswer == 48) { nAnswer = 17; }

		if (m_nCounter % 780 == 0)
		{//	文字を出す
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				CWord::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size.x, size.y, "WORD", nAnswer, 1, 45);
				scale.y = m_InitScale.y + 0.2f;
				pos.y = m_InitPos.y + 2.0f;
				m_nCounter = 0;
			}
		}
		if (m_nCounter > 20)
		{//	大きさを戻す
			scale.y = m_InitScale.y;
			pos.y = m_InitPos.y;
		}
		if (m_InitPos.z + 200 <= pos.z)
		{//	初期位置から+250以上離れた場合
			m_MoveState = 2;
		}
		else if (m_InitPos.z - 200 >= pos.z)
		{//	初期位置から-250以上離れた場合
			m_MoveState = 1;
		}
		switch (m_MoveState)
		{//	動きのステータス
		case 0:
			m_move.z = 0.0f;
			break;
		case 1:
			m_move.z = 1.0f;
			break;
		case 2:
			m_move.z = -1.0f;
			break;
		}
		pos += m_move;				//	動きの加算
	}

	if (CSceneX::GetModelType() == CLoad::MODEL_ALPHAMODEL00)
	{
		m_nCounter++;
		if (m_nCounter > 0 && m_nCounter < 360)
		{
			pos.y = 1000.0f;
			scale.x = 0.0f;
			scale.z = 0.0f;
		}
		else if (m_nCounter > 360 && m_nCounter < 360 * 2)
		{
			pos.y = 0.0f;
			//scale.x = m_InitScale.x;
			//scale.z = m_InitScale.z;
			scale.x = 0.0f;
			scale.z = 0.0f;
		}
		else  if (m_nCounter > 360 * 2)
		{
			m_nCounter = 0;
		}
		if (m_nCounter % 20 == 0)
		{//	雷エフェクト
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2, 1); }
		}
		else if (m_nCounter % 30 == 0)
		{//	雷エフェクト
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 2, 1); }
		}
		else if (m_nCounter % 40 == 0)
		{//	雷エフェクト
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), 2, 1); }
		}
	}
	else if (CSceneX::GetModelType() == CLoad::MODEL_ALPHAMODEL01)
	{
		m_nCounter++;
		if (m_nCounter > 0 && m_nCounter < 360)
		{
			pos.y = 0.0f;
			scale.x = 0.0f;
			scale.z = 0.0f;
		}
		else if (m_nCounter > 360 && m_nCounter < 360 * 2)
		{
			pos.y = 1000.0f;
			scale.x = 0.0f;
			scale.z = 0.0f;
		}
		else  if (m_nCounter >  360 * 2)
		{
			m_nCounter = 0;
		}
		if (m_nCounter % 20 == 0)
		{//	雷エフェクト
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 15.0f, 0.0f), 2, 1); }
		}
		else if (m_nCounter % 30 == 0)
		{//	雷エフェクト
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), 2, 1); }
		}
		else if (m_nCounter % 40 == 0)
		{//	雷エフェクト
			if (m_InitScale.x == 2.3f) { CEffect::Create(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), 2, 0); }
			else { CEffect::Create(pos + D3DXVECTOR3(0.0f, 25.0f, 0.0f), 2, 1); }
		}
	}

	if (CSceneX::GetModelType() == CLoad::MODEL_FSymbol)
	{
		m_nCounter++;
		if (m_nCounter % 6 == 0)
		{
			 CEffect::Create(pos + D3DXVECTOR3(0.0f, 65.0f, 0.0f), 3, 3);

		}
		int nAnswer = rand() % 48;
		int nAnswerB = rand() % 3;

		//	使っていない文字の例外処理
		if (nAnswer == 0 || nAnswer == 2 || nAnswer == 4 || nAnswer == 6 || nAnswer == 8 || nAnswer == 11) { nAnswer = 1; }
		else if (nAnswer == 13 || nAnswer == 14 || nAnswer == 16 || nAnswer == 17 || nAnswer == 18 || nAnswer == 21) { nAnswer = 7; }
		else if (nAnswer == 22 || nAnswer == 23 || nAnswer == 25 || nAnswer == 26 || nAnswer == 28 || nAnswer == 29) { nAnswer = 15; }
		else if (nAnswer == 31 || nAnswer == 32 || nAnswer == 33 || nAnswer == 34 || nAnswer == 36 || nAnswer == 37) { nAnswer = 30; }
		else if (nAnswer == 38 || nAnswer == 39 || nAnswer == 43 || nAnswer == 44 || nAnswer == 45 || nAnswer == 46) { nAnswer = 35; }
		else if (nAnswer == 47 || nAnswer == 48) { nAnswer = 17; }
		if (m_nCounter % 180 == 0)
		{//	文字を出す
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				if (nAnswerB == 0){CWord::Create(pos + D3DXVECTOR3(10.0f, 50.0f, 0.0f), D3DXVECTOR3(0.8f, 0.0f, 0.0f), size.x, size.y, "WORD", nAnswer, 1, 45);}
				else if (nAnswerB == 1) { CWord::Create(pos + D3DXVECTOR3(-10.0f, 50.0f, 0.0f), D3DXVECTOR3(-0.8f, 0.0f, 0.0f), size.x, size.y, "WORD", nAnswer, 1, 45); }
				else if (nAnswerB == 2) { CWord::Create(pos + D3DXVECTOR3(0.0f, 50.0f, 10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.8f), size.x, size.y, "WORD", nAnswer, 1, 45); }
				//else if (nAnswerB == 3) { CWord::Create(pos + D3DXVECTOR3(0.0f, 50.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, -0.8f), 12.0f, 12.0f, "WORD", nAnswer, 1, 45); }
				m_nCounter = 0;
			}
		}
	}
	CSceneX::SetPosition(pos);	//	位置の設定
	CSceneX::SetScale(scale);	//	大きさの設定
}

//=============================================================================
// ノックバックの処理
//=============================================================================
void CObject::KnockBack(D3DXVECTOR3 *pMove, int nID)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	float fknockBackMove = 0.0f;	// ノックバックの強度

	if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL)
	{	// ノックバックの威力が小さい
		fknockBackMove = KNOCKBACK_MOVE_SMALL;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING)
	{	// ノックバックの威力が中ぐらい
		fknockBackMove = KNOCKBACK_MOVE_DURING;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
	{	// ノックバックの威力が大きい
		fknockBackMove = KNOCKBACK_MOVE_BIG;
	}
	CSound *pSound = CManager::GetSound();		//	音の取得
												// プレイヤーの向きが方向転換するようになったら削除
	if (CSceneX::GetCollsionNum() == 0 || CSceneX::GetCollsionNum() == 1)
	{	// 左 又は 右 からの判定
		pMove->x *= -fknockBackMove;
	}
	else if (CSceneX::GetCollsionNum() == 2 || CSceneX::GetCollsionNum() == 3)
	{	// 前 又は 後ろ からの判定
		pMove->z *= -fknockBackMove;
	}
	if (CSceneX::GetModelType() == CLoad::MODEL_ALPHAMODEL00 || CSceneX::GetModelType() == CLoad::MODEL_ALPHAMODEL01)
	{
		pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET000, 3.0f);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET000);
	}

	// プレイヤーの向きが方向転換するようになったらコメントを外す
	/*float fPlayer = CGame::GetPlayer(nID)->GetRotation().y;
	pMove->x = sinf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);
	pMove->z = cosf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);*/
}

//=============================================================================
// モデル着地時の受ける影響の処理
//=============================================================================
void CObject::AffectedLanding(D3DXVECTOR3 *pMove, int nID)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		float fPlayer = CGame::GetPlayer(nID)->GetRotation().y;
		pMove->x = sinf(fPlayer + (D3DX_PI * 1.0f)) * (AFFECTED_LANDING);
		pMove->z = cosf(fPlayer + (D3DX_PI * 1.0f)) * (AFFECTED_LANDING);
	}
}

//=============================================================================
// モデルの移動関係の処理
//=============================================================================
void CObject::ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos)
{
	if (m_nRealTime == REALTIME_INITPOS)
	{	// 移動フラグがfalse 動かない場合
		float fMove = 0;

		// それぞれ移動値を決める
		if (CSceneX::GetModelType() == CLoad::MODEL_DODAI) { fMove = MODEL_MOVE_Y * -1; } // 土台の場合
			if(CSceneX::GetModelType() == CLoad::MODEL_STAGEFLOOR001 || CSceneX::GetModelType() == CLoad::MODEL_STAGEFLOOR002 ||
				CSceneX::GetModelType() == CLoad::MODEL_STAGEOUT) {
				fMove = MODEL_MOVE_Y * -1; } // 土台の場合
		else if (CSceneX::GetModelType() != CLoad::MODEL_DODAI) { fMove = MODEL_MOVE_Y; }	// 土台以外

																							// 振動の処理
		Vibration(&pos);

		ModelMove(Type, &pos, fMove);
		CSceneX::SetPosition(pos);
	}
	else if (m_nRealTime == REALTIME_NOTMOVE)
	{	// 動かない場合
		Rot(CSceneX::GetModelType());

		if (((CTime::GetStageTime() % 60) == 0) && CManager::GetGame()->GetChangeNum() < 2)
		{
			m_nRealTime = REALTIME_ENDPOS;
		}
	}
	else if (m_nRealTime == REALTIME_ENDPOS)
	{	// 移動フラグがtrue 動く場合
		pos.y += MODEL_MOVE_Y;						// 移動速度

													// 振動の処理
		Vibration(&pos);

		CSceneX::SetPosition(pos);

		if (pos.y + CSceneX::GetVtxMax().y < 0)
		{	// 地面より下の場合
			if (m_bCreateFlag == true) { m_bCreateFlag = false; }
			Uninit();
			return;
		}
	}
}

//=============================================================================
// アイコンのアニメーションの処理
//=============================================================================
void CObject::AnimationIcon(void)
{
	m_nCntAnim++;
	if (m_bSwitch == false)
	{//	SwitchがONだった場合
		if ((m_nCntAnim % ANIM_TIME) == 0)
		{
			m_nCntPattan++;
			m_pIcon->SetAnimation(m_nCntPattan, 0.1f, 1.0f);
		}
	}
}

//=============================================================================
// アイコンの生成処理
//=============================================================================
void CObject::IconCreate(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos)
{
	if (m_pIcon == NULL)
	{
		float fRot = 0.0f;		// 角度保管
		m_pIcon = CScene3D::Create(D3DXVECTOR3(pos.x, 1.0f, pos.z), "ベルトコンベア_アイコン");
		m_pIcon->SetSize(ICON_SIZE_X, ICON_SIZE_Y);
		m_pIcon->SetAnimation(0, 0.1f, 1.0f);

		if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT) { fRot = D3DX_PI * -0.5f; }
		else if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT) { fRot = D3DX_PI * 0.5f; }
		else if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT) { fRot = 0.0f; }
		else if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_BACK) { fRot = -D3DX_PI; }
		m_pIcon->SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));
	}
}

//=============================================================================
// 振動の処理
//=============================================================================
void CObject::Vibration(D3DXVECTOR3 *Pos)
{
	// 移動時に左右に動く
	if (m_bMoveFlag == false)
	{
		m_fMove += VIBRATION_MOVE;
		if (m_fMove > VIBRATION) { m_bMoveFlag = true; }
	}
	else if (m_bMoveFlag == true)
	{
		m_fMove -= VIBRATION_MOVE;
		if (m_fMove < -VIBRATION) { m_bMoveFlag = false; }
	}

	Pos->x += m_fMove;
	Pos->z += m_fMove;
}

//=============================================================================
// 回転の処理
//=============================================================================
void CObject::Rot(CLoad::MODEL mode)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();

	if (mode == CLoad::MODE_GEAR || mode == CLoad::MODEL_PROPELLER)
	{	// コリジョンタイプがノックバッ判定を持つなら向きの回転をさせる
		D3DXVECTOR3 rot = CSceneX::GetRot();

		if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL)
		{
			// 強弱の種類によって回転量を変化
			rot.y += GEAR_ROT_Y * 0.2f;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING)
		{
			// 強弱の種類によって回転量を変化
			rot.y += GEAR_ROT_Y * 0.5;
		}
		else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
		{
			// 強弱の種類によって回転量を変化
			rot.y += GEAR_ROT_Y * 1.0f;
		}
		else
		{
			// 強弱の種類によって回転量を変化
			rot.y += GEAR_ROT_Y * 1.5f;
		}
		CSceneX::SetRot(rot);
	}
}

//=============================================================================
// モデル移動の処理
//=============================================================================
void CObject::ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 *pos, float fMove)
{
	pos->y += fMove;						// 移動速度

	if (fMove < 0)
	{
		if (pos->y - CSceneX::GetVtxMin().y < 0)
		{	// 地面に着いた場合
			if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || Type == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
				Type == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT || Type == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
			{	// ベルトコンベアの場合
				pos->y = pos->y - CSceneX::GetVtxMin().y - 1.9f;
				pos->x = m_posOld.x;
				pos->z = m_posOld.z;
				CSceneX::SetPosition(*pos);
				m_nRealTime = REALTIME_NOTMOVE;

				IconCreate(Type, *pos);	// アイコンの生成
			}
			else if (Type != CSceneX::COLLSIONTYPE_CONVEYOR_FRONT && Type != CSceneX::COLLSIONTYPE_CONVEYOR_BACK &&
				Type != CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT && Type != CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
			{	// ベルトコンベア以外の場合
				pos->y = pos->y - CSceneX::GetVtxMin().y;
				pos->x = m_posOld.x;
				pos->z = m_posOld.z;

				CSceneX::SetPosition(*pos);
				m_nRealTime = REALTIME_NOTMOVE;
			}
		}
	}
	else if (fMove >= 0)
	{
		if (CSceneX::GetModelType() == CLoad::MODEL_STAGEFLOOR001 || CSceneX::GetModelType() == CLoad::MODEL_STAGEFLOOR002 ||
			CSceneX::GetModelType() == CLoad::MODEL_STAGEOUT)
		{
			if (CTime::GetSatgeNum() == 0)
			{
				pos->y = pos->y + CSceneX::GetVtxMin().y;
				pos->x = m_posOld.x;
				pos->z = m_posOld.z;

				CSceneX::SetPosition(*pos);
				m_nRealTime = REALTIME_NOTMOVE;
				if (m_bCreateFlag == false) {
					m_bCreateFlag = true;
				}
			}
			else if (CTime::GetSatgeNum() != 0)
			{
				if (pos->y > 0)
				{
					pos->y = -1.0f;
					pos->x = m_posOld.x;
					pos->z = m_posOld.z;

					CSceneX::SetPosition(*pos);
					m_nRealTime = REALTIME_NOTMOVE;
					if (m_bCreateFlag == false) {
						m_bCreateFlag = true;
					}
				}
			}
		}
		else if (CSceneX::GetModelType() == CLoad::MODEL_DODAI)
		{
			if (pos->y > 0)
			{
				pos->y = pos->y - CSceneX::GetVtxMin().y;
				pos->x = m_posOld.x;
				pos->z = m_posOld.z;

				CSceneX::SetPosition(*pos);
				m_nRealTime = REALTIME_NOTMOVE;
				if (m_bCreateFlag == false) {
					m_bCreateFlag = true;
				}
			}
		}
	}

}
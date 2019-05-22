//=============================================================================
//
// ステージ [Stage.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "StageBase.h"
#include "scene2D.h"
#include "bg.h"
#include "enemyBase.h"
#include "game.h"
#include "sound.h"
//=============================================================================
// 静的メンバ変数
//=============================================================================
CBg *CStage::m_pBg = NULL;
bool CStage::m_bBossEmergence = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CStage::CStage() { m_bBossEmergence = false; }
//=============================================================================
// デストラクタ
//=============================================================================
CStage::~CStage() {}
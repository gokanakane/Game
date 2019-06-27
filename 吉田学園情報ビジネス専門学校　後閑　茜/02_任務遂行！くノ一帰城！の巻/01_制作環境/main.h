//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author :Gokan akane
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"					 //描画処理に必要（一覧）
#define  DIRECTINPUT_VERSION (0x0800)//ビルド警告対処用
#include "dinput.h"					 //入力処理に必要
#include "xaudio2.h"				 //サウンド処理で必要

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")  //描画処理に必要（バイナリ）
#pragma comment(lib,"d3dx9.lib") //[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//DirectXコンポーネント（部品）の使用に必要
#pragma comment(lib,"winmm.lib")//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// ウインドウの幅
#define SCREEN_HEIGHT	(720)		// ウインドウの高さ
#define FVF_VERTEX_2D ( D3DFVF_XYZRHW| D3DFVF_DIFFUSE|D3DFVF_TEX1) //頂点フォーマット・テクスチャ座標

#define CLASS_NAME		"WindowClass"		// ウインドウクラスの名前
#define WINDOW_NAME		"任務遂行！くノ一帰城！の巻"	// ウインドウの名前(キャプション名)
#define MAX_VERTEX_DATA (4)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//列挙型
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX
}MODE;

typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;		//1.0fで固定
	D3DCOLOR col;	//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標

}VERTEX_2D;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif
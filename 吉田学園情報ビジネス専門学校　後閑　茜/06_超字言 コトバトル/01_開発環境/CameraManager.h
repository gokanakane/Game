//=============================================================================
//
// カメラ管理処理 [CameraManager.h]
// Author : Kodama Yuto
//
//	クラスの概要
//	・カメラを複数個動的配列で管理し、InitやUninit,Update,SetCameraを一括で行うクラス
//	・CreateCameraを呼ぶことでカメラを作成する(すでに作成されていれば初期情報の更新のみ行う)
//	・TextureクラスやCommandクラスと同様にTagで管理される
//
//=============================================================================
#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

#include "main.h"
#include "camera.h"

class C3DCharactor;

//===================================================================
// クラスの定義
//===================================================================
class CCameraManager
{
public:
	enum DRAW_PROPERTY
	{
		PROP_DEFAULT = 0, //通常設定(画面初期化)
		PROP_INIT_ZONLY,  //Zバッファのみ初期化(これまで描画されたものの上に描画される)
	};

	struct CAMERA_STATE
	{//カメラ情報の構造体
		CCamera* pCamera;			//カメラのポインタ
		D3DXCOLOR BackgroundColor;	//初期化するときの背景色
		DRAW_PROPERTY Property;		//描画時の設定
		LPCSTR CameraTag;			//カメラ識別用のタグ

		bool operator == (const LPCSTR Tag)
		{//タグ比較(同じならtrue)
			return (strcmp(CameraTag, Tag) == 0);
		}
	};


	CCameraManager();
	~CCameraManager();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);

	//カメラのセット
	bool SetCamera(LPCSTR Tag);

	//カメラ生成
	bool CreateCamera(LPCSTR Tag, CCamera::CAMERA_TYPE type, D3DXVECTOR3 pos,
		D3DXVECTOR3 rot, float fLength,DRAW_PROPERTY prop = PROP_DEFAULT);

	//カメラのビューポート設定
	bool SetCameraViewPort(LPCSTR Tag, int X, int Y, int Width, int Height, float MinZ = 0.0f, float MaxZ = 1.0f);

	//追従する対象の設定
	bool SetCameraHomingChara(LPCSTR Tag, C3DCharactor* pHomingChara);

	//ロックオンする対象の設定
	bool SetCameraLockOnChara(LPCSTR Tag, C3DCharactor* pLockOnChara);

	//カメラの画角の設定
	bool SetCameraAngle(LPCSTR Tag,float fAngle);

	//カメラの注視点設定
	bool SetCameraPosR(LPCSTR Tag,D3DXVECTOR3 posR,bool bLeap);

	//カメラの長さ設定
	bool SetCameraLength(LPCSTR Tag,float fLength);

	//背景色設定
	bool SetBackGroundColor(LPCSTR Tag, D3DXCOLOR col);

	//カメラ削除
	bool DeleteCamera(LPCSTR Tag);

	//カメラ取得
	CCamera* GetCamera(LPCSTR Tag);

	float GetLength(LPCSTR Tag);
	//現在セットしているカメラ名取得
	static LPCSTR GetCameraName(void) { return m_SetCamera; };

	int GetCameraNum(void) { return m_vecCameraState.size(); };
private:
	CCamera* CameraSearch(LPCSTR Tag);

	void WindowClear(LPDIRECT3DDEVICE9 pDev,DRAW_PROPERTY prop, D3DXCOLOR BG_Color);

	std::vector<CAMERA_STATE> m_vecCameraState;	//カメラ情報の動的配列

	static LPCSTR m_SetCamera;		//現在セットしているカメラの名前
};


#endif // !_CAMERA_MANAGER_H_

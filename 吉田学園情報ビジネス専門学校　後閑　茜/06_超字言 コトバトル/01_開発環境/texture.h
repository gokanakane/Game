//=============================================================================
//
// テクスチャクラス [texture.h]
// Author : Kodama Yuto
//
//	クラスの概要:
//	・外部ファイルに書かれた情報を保持し、必要な時に
//	　読み込んだ情報を元にテクスチャを生成する
//	・一度読み込んだものは保持しておき、再度必要になった時は
//	  既にあるテクスチャをそのまま渡す
//	・テクスチャは外部ファイルで変更できるIDとタグで管理され、
//	　使用者はIDもしくはタグを引数に入れることで必要なテクスチャを取得する
//	・new/deleteと派生を禁止するため、コンストラクタとデストラクタをprivate化し、
//	　クラス定義の末尾にfinalを付けた(消さないこと!!)
//
//	注::使用するときはmain.hに<stdio.h>と警告解除文を入れること!!
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

class CTexture final	//final = 継承を禁止する構文
{
public:
	//テクスチャデータの構造体
	struct TexData
	{
		int	 nID;							//ID
		char TexAddress[256];				//テクスチャのアドレス
		char TexNameTag[256];				//テクスチャの略称
		LPDIRECT3DTEXTURE9 pTexture;		//テクスチャのポインタ


		//std::findで検索するときに使う比較関数
		bool operator == (const int ID)
		{//IDで比較
			return (nID == ID);
		}
		bool operator == (const LPCSTR Tag)
		{//タグで比較
			return (strcmp(TexNameTag, Tag) == 0);
		}
	};


	//読み込み&削除
	static HRESULT Load(void);
	static void Unload(void);

	//テクスチャ取得
	static LPDIRECT3DTEXTURE9 GetTexture(const int nID);
	static LPDIRECT3DTEXTURE9 GetTexture(const LPCSTR Tag);

	//作られているテクスチャを全開放
	static void ReleaseAll(void);
	//使わなくなったテクスチャの解放
	static void Release(const int nID);
	static void Release(const LPCSTR Tag);

	//テクスチャ数
	static int GetTexNum(bool bCreate);
private:

	//コンストラクタ&デストラクタ (new/deleteを禁止するためにprivateに入れる)
	CTexture() {};
	~CTexture() {};

	//内部でのテクスチャ生成関数
	static void Create(LPCSTR address, LPDIRECT3DTEXTURE9 &pTexture);

	//変数
	static std::vector<TexData> m_TexData;	//テクスチャデータの配列
};

#endif // !_TEXTURE_H_

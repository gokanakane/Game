//=============================================================================
//
// Text読み込み処理 [loadText.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "loadText.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "manager.h"
#include "word_manager.h"
#include "bullet.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME				("data\\TEXT\\WordManager.txt")

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CLoadText::CLoadText()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CLoadText::~CLoadText()
{
}


//=============================================================================
// オブジェクトの配置情報を読み込み
//=============================================================================
void CLoadText::LoadFile(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile;			//ファイルポインタ
	char *pStrcur;			//現在の先頭の文字列
	char aLine[256];		//文字列
	char aStr[256];			//一時保存文字列
	int nIndex = 0;			//現在のインデックス
	int nWord = 0;			//ポップで返された値を保持
	int nNumModel = 0;		//モデルの数
	int nType = 0;			//モデルの種類
	D3DXVECTOR3 ModelPos;	//モデルの位置
	D3DXVECTOR3 ModelRot;
	D3DXVECTOR3 ModelScale;
	D3DXVECTOR3 AnswerNum;
	int			nCollisionType;
	int			nAnswerNum;
	int			nAnswerModel;
	int			nPoint;

	//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME, "r");
	//NULLチェック
	if (pFile != NULL)
	{
		while (1)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "ANSWERNUM = ", strlen("ANSWERNUM = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("ANSWERNUM = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				nAnswerNum = atoi(pStrcur);
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				CWordManager::SetWordAnswerNum(nAnswerNum);
			}
			//オブジェクト読み込み
			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//頭出し
				pStrcur += strlen("MODELSET");
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//種類
				if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("TYPE = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);
					//文字列抜き出し
					nType = atoi(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//位置
				if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("POS = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.X代入
					ModelPos.x = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Y代入
					ModelPos.y = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Z代入
					ModelPos.z = (float)atof(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//ROTを読み込み
				if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("ROT = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.x = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.y = (float)atof(pStrcur);

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.z = (float)atof(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					//角度を-π〜πに補正する
					CUtilityMath::RotateNormarizePI(ModelRot);
				}
				//SCALEを読み込み
				if (memcmp(pStrcur, "SCALE = ", strlen("SCALE = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("SCALE = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);

					//文字列変換
					ModelScale.x = fabsf((float)atof(pStrcur)); //マイナスが入らないように絶対値を使う

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelScale.y = fabsf((float)atof(pStrcur));//マイナスが入らないように絶対値を使う

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelScale.z = fabsf((float)atof(pStrcur));//マイナスが入らないように絶対値を使う
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//COLLISIONを読み込み
				if (memcmp(pStrcur, "BULLETTYPE = ", strlen("BULLETTYPE = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("BULLETTYPE = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					nCollisionType = (int)atoi(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					if (nCollisionType >= (int)CModelBullet::TYPE_MAX||
						nCollisionType < 0)
					{//弾タイプに変な数値が入っていた場合はノーマル弾に変える(エラー防止)
						nCollisionType = (int)CModelBullet::TYPE_NORMAL;
					}
				}
				//答えの数字
				if (memcmp(pStrcur, "ANSWER = ", strlen("ANSWER = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("ANSWER = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.X代入
					AnswerNum.x = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Y代入
					AnswerNum.y = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Z代入
					AnswerNum.z = (float)atof(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				if (memcmp(pStrcur, "ANSWERMODEL = ", strlen("ANSWERMODEL = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("ANSWERMODEL = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);
					//文字列抜き出し
					nAnswerModel = atoi(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				if (memcmp(pStrcur, "POINT = ", strlen("POINT = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("POINT = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);
					//文字列抜き出し
					nPoint = atoi(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
			}
			//モデルを生成
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				//CSetObject::Create(ModelPos, ModelRot, D3DXVECTOR3(0.0f, 0.0f, 0.0f)
				//	, (CSetObject::MODELTYPE)nType, CSetObject::MOVETYPE_NONE, 1);
				//CObject::Create(ModelPos, ModelRot, ModelScale, (CSceneX::COLLISIONTYPE)nCollisionType, (CLoad::MODEL)nType);
				CWordManager::SetWordLoad(nType, AnswerNum, ModelScale, ModelRot, nCollisionType, nAnswerModel, nPoint);
			}
			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);
}


//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CLoadText::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char * CLoadText::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CLoadText::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}

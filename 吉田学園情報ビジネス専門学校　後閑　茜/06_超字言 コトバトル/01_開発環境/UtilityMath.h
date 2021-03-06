//=============================================================================
//
// 汎用数学クラス [UtilityMath.h]
// Author : Kodama Yuto
//
//	クラスの概要:
//	・よく使う計算をクラス化してまとめた物
//	・基本的にすべての変数を参照かポインタで渡す
//	・本来はライブラリ化したほうがいいらしいが、編集を楽にするために今回はこのまま使う
//
//=============================================================================
#ifndef _UTILITY_MATH_H_
#define _UTILITY_MATH_H_

#include "main.h"

#define _PI ((FLOAT)3.1415926535f)		//π
#define _GRAVITY ((FLOAT)0.98f)			//重力
//=============================================================================
//	クラス定義(VECTOR_3D)
//
//  独自の３次元ベクトルクラス
//=============================================================================
class VECTOR_3D
{
public:
	float X;	//X軸の値
	float Y;	//Y軸の値
	float Z;	//Z軸の値

	//コンストラクタ(引数なし)
	VECTOR_3D()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
	}
	//コンストラクタ(引数float3個)
	VECTOR_3D(const float& X, const float& Y, const float& Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	//コンストラクタ(引数VECTOR_3D)
	VECTOR_3D(const VECTOR_3D& vec)
	{
		*this = vec;
	}

	//デストラクタ(デフォルト)
	~VECTOR_3D() {};

	//独自関数
	VECTOR_3D RotateNormalize(void);
	float VectorLength(void);
	/*オペレータ*/
	//代入
	void operator = (const VECTOR_3D& vec)
	{
		this->X = vec.X;
		this->Y = vec.Y;
		this->Z = vec.Z;
	}

	//足し算
	VECTOR_3D operator + (const VECTOR_3D& vec)
	{
		this->X = this->X + vec.X;
		this->Y = this->Y + vec.Y;
		this->Z = this->Z + vec.Z;

		return *this;
	}
	void operator += (const VECTOR_3D& vec)
	{
		this->X += vec.X;
		this->Y += vec.Y;
		this->Z += vec.Z;
	}

	//引き算
	VECTOR_3D operator - (const VECTOR_3D& vec)
	{
		this->X = this->X - vec.X;
		this->Y = this->Y - vec.Y;
		this->Z = this->Z - vec.Z;

		return *this;
	}
	void operator -= (const VECTOR_3D& vec)
	{
		this->X -= vec.X;
		this->Y -= vec.Y;
		this->Z -= vec.Z;
	}

	//掛け算
	VECTOR_3D operator * (const VECTOR_3D& vec)
	{
		this->X = this->X * vec.X;
		this->Y = this->Y * vec.Y;
		this->Z = this->Z * vec.Z;

		return *this;
	}
	void operator *= (const VECTOR_3D& vec)
	{
		this->X *= vec.X;
		this->Y *= vec.Y;
		this->Z *= vec.Z;
	}

	//割り算
	VECTOR_3D operator / (const VECTOR_3D& vec)
	{
		this->X = this->X / vec.X;
		this->Y = this->Y / vec.Y;
		this->Z = this->Z / vec.Z;

		return *this;
	}
	void operator /= (const VECTOR_3D& vec)
	{
		this->X /= vec.X;
		this->Y /= vec.Y;
		this->Z /= vec.Z;
	}

	//定数掛け算
	VECTOR_3D operator * (const float& fVal)
	{
		this->X = this->X * fVal;
		this->Y = this->Y * fVal;
		this->Z = this->Z * fVal;

		return *this;
	}

	//比較(コード短縮のために三項演算子を使う)
	bool operator == (const VECTOR_3D& vec)
	{// ==
		return (this->X == vec.X && this->Y == vec.Y && this->Z == vec.Z) ? true : false;
	}
	bool operator != (const VECTOR_3D& vec)
	{// !=
		return (this->X != vec.X && this->Y != vec.Y && this->Z != vec.Z) ? true : false;
	}
	bool operator > (const VECTOR_3D& vec)
	{// >
		return (this->X > vec.X && this->Y > vec.Y && this->Z > vec.Z) ? true : false;
	}
	bool operator >= (const VECTOR_3D& vec)
	{// >=
		return (this->X >= vec.X && this->Y >= vec.Y && this->Z >= vec.Z) ? true : false;
	}
	bool operator < (const VECTOR_3D& vec)
	{// <
		return (this->X < vec.X && this->Y < vec.Y && this->Z < vec.Z) ? true : false;
	}
	bool operator <= (const VECTOR_3D& vec)
	{// <=
		return (this->X <= vec.X && this->Y <= vec.Y && this->Z <= vec.Z) ? true : false;
	}
};

//=============================================================================
//	クラス定義(CEasingFunc)
//
//	概要　時間X(0.0f〜1.0f)を与えられた時の変化量Y(0.0f〜1.0f)を求める。
//		  X = 0の時Y = 0 かつ X = 1の時Y = 1になる
//		　様々な曲線を生成し、その曲線に沿う値を返す
//		  (0<X<1)の範囲外が渡されたときは範囲に収まるようにclampしてから処理する
//
//=============================================================================
class CEasingFunc final
{
public:
	enum EASE_TYPE
	{
		EASE_LINIAR,			//線形
		EASE_IN_QUAD,			//二次関数(IN)
		EASE_OUT_QUAD,			//二次関数(OUT)
		EASE_INOUT_QUAD,		//二次関数(IN&OUT)
		EASE_IN_CUBIC,			//三次関数(IN)
		EASE_OUT_CUBIC,			//三次関数(OUT)
		EASE_INOUT_CUBIC,		//三次関数(IN&OUT)
		EASE_IN_EXPO,			//指数関数(IN)
		EASE_OUT_EXPO,			//指数関数(OUT)
		EASE_INOUT_EXPO,		//指数関数(IN&OUT)
	};

	static float Easing(EASE_TYPE type,float& fTime);
private:
	CEasingFunc();
	~CEasingFunc() {};
};

//=============================================================================
//	クラス定義(CUtilityMath)
//=============================================================================
class CUtilityMath final
{
public:
	static D3DXMATRIX* CalWorldMatrix(D3DXMATRIX* pOut,const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXMATRIX* parent = NULL, const D3DXVECTOR3& scale = D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXMATRIX* pViewMtx = NULL);

	static float RotateNormarizePI(float* value);
	static D3DXVECTOR3 RotateNormarizePI(D3DXVECTOR3* RotateValue);
	static float FloatLeap(const float& fromValue,const float& toValue,const float fTime);

	static float Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget, bool bClamp = false);
	static D3DXVECTOR3 MoveCoeffient(D3DXVECTOR3& value,const float& coeffient);
	static float RoundF_n(float& fValue,const int nRound);

private:
	CUtilityMath();
	~CUtilityMath() {};
};
#endif // !_UTILITY_MATH_H_

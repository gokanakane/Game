//=============================================================================
//
// �ėp���w�N���X [UtilityMath.cpp](CUtilityMath)
// Author : Kodama Yuto
//
//=============================================================================
#include "UtilityMath.h"

//=============================================================================
//	���[���h�}�g���b�N�X�v�Z�֐�
//=============================================================================
D3DXMATRIX* CUtilityMath::CalWorldMatrix(D3DXMATRIX* pOut, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,
	const D3DXMATRIX* parent,const D3DXVECTOR3& scale, D3DXMATRIX* pViewMtx)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale,mtxInv, mtxParent;				// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pOut);

	// ��]�𔽉f
	if (pViewMtx != NULL)	//pViewMtx��NULL���ǂ����Ńr���{�[�h���𔻕ʂ���
	{//	�r���{�[�h�Ȃ�
		D3DXMatrixIdentity(&mtxInv);
		//�t�s���ݒ�
		mtxInv._11 = pViewMtx->_11;
		mtxInv._12 = pViewMtx->_21;
		mtxInv._13 = pViewMtx->_31;
		mtxInv._21 = pViewMtx->_12;
		mtxInv._22 = pViewMtx->_22;
		mtxInv._23 = pViewMtx->_32;
		mtxInv._31 = pViewMtx->_13;
		mtxInv._32 = pViewMtx->_23;
		mtxInv._33 = pViewMtx->_33;

		//�o�����s��ɉ�]�𔽉f���ă��[���h�}�g���b�N�X�ɓ����
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxRot, &mtxInv, &mtxRot);
	}
	else
	{//�r���{�[�h�łȂ��Ȃ�
		//���ʂɉ�]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	}
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);

	//�g��k���̔��f
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);


	if (parent != NULL)
	{
		//�e�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(pOut,pOut,parent);
	}

	return pOut;
}

//=============================================================================
//	�p�x�␳�֐�
//=============================================================================
float CUtilityMath::RotateNormarizePI(float* value)
{//float
	if (*value > D3DX_PI)
	{
		*value -= D3DX_PI * 2.0f;
	}
	else if (*value < -D3DX_PI)
	{
		*value += D3DX_PI * 2.0f;
	}

	return *value;
}
D3DXVECTOR3 CUtilityMath::RotateNormarizePI(D3DXVECTOR3* RotateValue)
{//D3DXVECTOR3(float3��)

	RotateNormarizePI(&RotateValue->x);
	RotateNormarizePI(&RotateValue->y);
	RotateNormarizePI(&RotateValue->z);

	return *RotateValue;
}

//=============================================================================
//	float�^�̐��`�⊮�֐�
//=============================================================================
float CUtilityMath::FloatLeap(const float& fromValue, const float& toValue, const float fTime)
{
	return (1.0f - fTime) * fromValue + fTime * toValue;
}

//=============================================================================
//	���l�̐��`�ʑ��֐�
//=============================================================================
float CUtilityMath::Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget,bool bClamp)
{
	float fResult = (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;

	if (bClamp == true)
	{//�N�����v
		if (fResult > toTarget) { fResult = toTarget; }
		else if (fResult < fromTarget) { fResult = fromTarget; }
	}
	return fResult;
}

//=============================================================================
//	�ړ��͂ɌW�����|����֐�
//=============================================================================
D3DXVECTOR3 CUtilityMath::MoveCoeffient(D3DXVECTOR3& value, const float& coeffient)
{
	value.x += (0.0f - value.x) * coeffient;
	value.y += (0.0f - value.y) * coeffient;
	value.z += (0.0f - value.z) * coeffient;

	return value;
}

//=============================================================================
//	�C�ӂ̌�����float���l�̌ܓ�����֐�
//=============================================================================
float CUtilityMath::RoundF_n(float& fValue, const int nRound)
{
	fValue *= powf(10.0f,(float)(nRound - 1));	//�l�̌ܓ��������l��10��(n-1)��{����B
	fValue = round(fValue);						//�����_�ȉ����l�̌ܓ�����B
	fValue /= powf(10.0f, (float)(nRound - 1));  //10��(n-1)��Ŋ���B

	return fValue;
}
//=============================================================================
//
// �C�[�W���O�N���X [UtilityMath.cpp](CEasingFunc)
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
//	�C�[�W���O�֐�
//	IN = ���߂̂ق��Ɋ|����@OUT = ���̂ق��Ɋ|����@INOUT = �����Ɋ|����
//	QUAD = �񎟊֐��̕ό`(QuadFunc.)�@CUBIC = �O���֐��̕ό`(CubicFunc.)�@
//	EXPO = �w���֐��̕ό`(ExpoFunc.)
//=============================================================================
float CEasingFunc::Easing(CEasingFunc::EASE_TYPE type, float& fTime)
{
	float fResult = 0.0f;

	//0�`1�̊Ԃ�clamp����
	if (fTime > 1.0f)
	{
		fTime = 1.0f;
	}
	else if (fTime < 0.0f)
	{
		fTime = 0.0f;
	}

	//�^�C�v���Ƃɏ����𕪂���
	switch (type)
	{
	case EASE_LINIAR://���`
		fResult = fTime;//X = Y
		break;
	case EASE_IN_QUAD://�񎟊֐�(IN)   f(x) = x^(2)
		fResult = fTime * fTime;
		break;
	case EASE_OUT_QUAD://�񎟊֐�(OUT) f(x) = -x*(x-2)
		fResult = -1.0f*fTime*(fTime - 2.0f);
		break;
	case EASE_INOUT_QUAD://�񎟊֐�(IN&OUT) ��Q�̕���
		fTime /= 0.5f;//0�`1��0�`2�ւƕ␳����(���0.5���|���đł�����)

		/*���ʂɂ���ď�����ς���*/
		if (fTime < 1)
		{//1�ȉ��Ȃ�ʏ�̓񎟊֐����g��
			fResult = fTime * fTime * 0.5f;
		}
		else
		{//����ȏ�Ȃ�X�����t�ɂȂ����񎟊֐����g��
			fTime = fTime - 1.0f;
			fResult = -0.5f * (fTime*(fTime - 2) - 1);
		}
		break;
	case EASE_IN_CUBIC://�O���֐�(IN)    f(x) = x^(3)
		fResult = fTime * fTime * fTime;
		break;
	case EASE_OUT_CUBIC://�O���֐�(OUT)  f(x) = (x-1)^(3)+1
		fTime = fTime - 1.0f;
		fResult = (fTime*fTime*fTime + 1);
		break;
	case EASE_INOUT_CUBIC://�O���֐�(IN&OUT) ��Q�̕���
		fTime /= 0.5f;

		/*���ʂɂ���ď�����ς���*/
		if (fTime < 1)
		{//1�ȉ��Ȃ�ʏ�̎O���֐����g��
			fResult = 0.5f*fTime*fTime*fTime;
		}
		else
		{//����ȏ�Ȃ�X�����t�ɂȂ����O���֐����g��
			fTime = fTime - 2;
			fResult = 0.5f * (fTime*fTime*fTime + 2);
		}
		break;
	case EASE_IN_EXPO:		//�w���֐�(IN)  f(x)=2^(10 (x-1))
		fResult = (float)exp2(10.0 * ((double)fTime - 1.0));
		break;
	case EASE_OUT_EXPO:		//�w���֐�(OUT) f(x)=-2^(-10x)+1
		fResult = (-((float)exp2(-10.0 * (double)fTime)) + 1);
		break;
	case EASE_INOUT_EXPO:	//�w���֐�(IN&OUT) ��Q�̕���
		fTime /= 0.5f;
		if (fTime < 1)
		{
			fResult = 0.5f * (float)exp2(10.0 * ((double)fTime - 1.0));
		}
		else
		{
			fTime -= 1.0f;
			fResult = 0.5f * (-((float)exp2(-10.0 * (double)fTime)) + 2.0f);
		}
		break;
	}

	//double pow2, bounce = 4.0;
	//while (fTime < ((pow2 = pow(2, --bounce)) - 1) / 11) {}
	//fResult =  float(1 / pow(4, 3 - bounce) - 7.5625 * pow((pow2 * 3 - 2) / 22 - x, 2));
	return fResult;
}

//=============================================================================
//
// �R�����x�N�g���N���X [UtilityMath.cpp](VECTOR_3D)
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
//	�p�x��@���Ƃ��Ďg����悤�ɐ��`�ʑ�����֐�
//=============================================================================
VECTOR_3D VECTOR_3D::RotateNormalize(void)
{
	//�p�x�𐳋K��
	//X
	if (this->X > _PI)
	{
		this->X -= _PI * 2.0f;
	}
	else if (this->X < -_PI)
	{
		this->X += _PI * 2.0f;
	}
	//Y
	if (this->Y > _PI)
	{
		this->Y -= _PI * 2.0f;
	}
	else if (this->Y < -_PI)
	{
		this->Y += _PI * 2.0f;
	}
	//Z
	if (this->Z > _PI)
	{
		this->Z -= _PI * 2.0f;
	}
	else if (this->Z < -_PI)
	{
		this->Z += _PI * 2.0f;
	}

	//-1.0f����1.0f�܂ł̐��l�ɒ���
	this->X = CUtilityMath::Mapping(this->X, -_PI, _PI, -1.0f, 1.0f, true);
	this->Y = CUtilityMath::Mapping(this->Y, -_PI, _PI, -1.0f, 1.0f, true);
	this->Z = CUtilityMath::Mapping(this->Z, -_PI, _PI, -1.0f, 1.0f, true);

	return *this;
}

//=============================================================================
//	�x�N�g���̒��������߂�֐�
//=============================================================================
float VECTOR_3D::VectorLength(void)
{
	VECTOR_3D pow2Vec = (*this)* (*this);//��悷��

	return sqrtf(pow2Vec.X + pow2Vec.Y + pow2Vec.Z);
}
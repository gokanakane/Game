//=============================================================================
//
// ���C�g���� [light.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT	(5)

//========================================
// �N���X�̒�`
//========================================
//=====================
// ���C�g�N���X
//=====================
class CLight
{
public:
	CLight();		// �R���X�g���N�^
	~CLight();		// �f�X�g���N�^

	void Init(void);
	void Uninit(void);
	void Update(void);

	static void SetLight(int nNum,D3DLIGHT9 light) { m_light[nNum] = light; }
	static D3DLIGHT9 GetLight(int nNum) { return m_light[nNum]; }
private:
	static D3DLIGHT9 m_light[MAX_LIGHT];	// ���C�g�̏��
};

#endif
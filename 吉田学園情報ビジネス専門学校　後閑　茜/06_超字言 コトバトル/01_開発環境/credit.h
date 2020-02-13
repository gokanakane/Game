//=============================================================================
//
// credit���� [credit.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _CREDIT_H_
#define _CREDIT_H_

#include "main.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*********************************************************************
//�Q�[���N���X�̒�`
//*********************************************************************
class CCredit : public CScene //�h���N���X
{
public:

	CCredit(int nPriority = 7);
	~CCredit();
	static CCredit *Create();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static HRESULT Load(void) { return S_OK; }													//�ǂݍ���
	static void UnLoad(void);																	//�j��

private:
	void SetInit(void);
	void Flash(void);	// �F�̓_��

	CScene2D *m_pCredit;
	CScene2D *m_pBack;

	int	m_nCntFlash;
};

#endif
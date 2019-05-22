//=============================================================================
//
// �I�v�V���� [option.h]
// Author : 
//
//=============================================================================
#ifndef _ABYSSGATE_H_
#define _ABYSSGATE_H_

#include "main.h"
#include "optionBase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`(�h��)�@�r�r�A���ޗ���
//*****************************************************************************
class CAbyssGate :public COption
{
public:
	typedef enum
	{
		ABYSSGATESTATE_NONE = 0,
		ABYSSGATESTATE_CATCH,
		ABYSSGATESTATE_MAX
	}AbyssGateState;

	CAbyssGate();
	~CAbyssGate();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetAbyssGateEmergence(bool Use) { m_bAbyssGateEmergence = Use; }
	static bool GetAbyssGateEmergence(void) { return m_bAbyssGateEmergence; }
	static void SetAbyssGateState(AbyssGateState state) { m_state = state; }

private:
	static bool m_bAbyssGateEmergence;
	static AbyssGateState m_state;
};
#endif

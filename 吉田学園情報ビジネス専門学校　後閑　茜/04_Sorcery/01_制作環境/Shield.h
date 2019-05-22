//=============================================================================
//
// �I�v�V���� [option.h]
// Author : 
//
//=============================================================================
#ifndef _SHIELD_H_
#define _SHIELD_H_

#include "main.h"
#include "optionBase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`(�h��)�@�J�[�l���A����
//*****************************************************************************
class CShield : public COption
{
public:
	typedef enum
	{
		SHIELDSTATE_NONE = 0,
		SHIELDSTATE_DAMAGE,
		SHIELDSTATE_BREAK,
		SHIELDSTATE_MAX
	}ShieldState;

	CShield();
	~CShield();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetDamage(int Damage);
	static bool GetShieldEmergence(void) { return m_bShieldEmergence; }

private:
	int m_nLife;				//���̑ϋv
	int m_nCntState;			//�F�ς�
	ShieldState m_state;		//���̏�
	static bool m_bShieldEmergence;	//���̎g�p��
};

#endif
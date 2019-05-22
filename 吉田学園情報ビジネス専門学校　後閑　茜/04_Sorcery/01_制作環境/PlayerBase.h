//=============================================================================
//
// �v���C���[�̊�Տ��� [playerBase.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYERBASE_H_
#define _PLAYERBASE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_MOVE (5.0f)
#define TEXTURE_PLAYER_DRAGON		"data\\TEXTURE\\Player\\player000.png"
#define TEXTURE_PLAYER_KARNERIAN	"data\\TEXTURE\\Player\\Player001.png"
#define TEXTURE_PLAYER_VIVIAN		"data\\TEXTURE\\Player\\Player002.png"
#define TEXTURE_PLAYER_AREISTA		"data\\TEXTURE\\Player\\player003.png"
#define TEXTURE_PLAYER_RENGE		"data\\TEXTURE\\Player\\player004.png"
#define TEXTURE_PLAYER_LILIY		"data\\TEXTURE\\Player\\player005.png"
#define MAX_ANIMPATTURM (4)
#define MAX_LIFE (100)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBullet;

//*****************************************************************************
// �N���X�i�h���j
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	typedef enum
	{//�v���C���[�̏��
		PLAYERSTATE_NONE = 0,
		PLAYERSTATE_INVINCIBLE,	//���G
		PLAYERSTATE_DAMAGE,		//�_���[�W
		PLAYERSTATE_DEATH,		//���S
		PLAYERSTATE_MAX
	}PlayerState;

	typedef enum
	{//�ʏ햂�@�g�p��
		PLAYERSKIL_NORMALL_FALSE = 0,
		PLAYERSKILL_NORMAL_TRUE,
		PLAUERSKIL_NORMALL_MAX
	}PlayerSkill_Normal;

	typedef enum
	{//�ɖ��@�g�p��
		PLAYERSKILL_KIWAME_FALSE = 0,
		PLAYERSKILL_KIWAME_TRUE,
		PLAUERSKILL_KIWAME_MAX
	}PlayerSkill_KIWAME;

	CPlayer();
	virtual ~CPlayer();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, CManager::CHARACTORSELECT_STATE state);
	static HRESULT Load(void);
	static void UnLoad(void);
	static CPlayer *GetPlayer(void);
	static int GetLife(void) { return m_nLife; }
	static void SetNormalSkill(PlayerSkill_Normal Use) { m_NormalSkillUse = Use; }
	static void SetKIWAMESkill(PlayerSkill_KIWAME Use) { m_KIWAMESkillUse = Use; }
	static PlayerSkill_Normal GetPlayerSkillUse(void) { return m_NormalSkillUse; }
	void SetPlayer(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPlayerPos(void);
	void SetLife(int Life) { m_nLife = Life; };
	void SetDamage(int Damage);
	void SetInvincible(void);
	void SetRecovery(int Recovery);
	void MoveRestriction(D3DXVECTOR3 pos);
	PlayerState GetState(void) { return m_state; }

protected:
	static PlayerSkill_Normal m_NormalSkillUse;
	static PlayerSkill_KIWAME m_KIWAMESkillUse;
	D3DXVECTOR3 m_pos;
	PlayerState m_state;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`���ւ̃|�C���^
	static CPlayer *pPlayer;
	static int  m_nLife;
	static CManager::CHARACTORSELECT_STATE m_SelectCharactor;
	int m_nCntAnim, m_nPatturnAnim, m_nCntFade, m_nCntState;
	D3DXCOLOR m_Col;
	float m_ChangeCol;
};
#endif

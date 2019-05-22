//=============================================================================
//
// �G�̊�Տ��� [enemyBase.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYBASE_H_
#define _ENEMYBASE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEX (3)
#define TEXTURE_ENEMY "data\\TEXTURE\\Enemy\\book001.png"
#define TEXTURE_BOSSENEMY_AIHA "data\\TEXTURE\\Enemy\\BossEnemy000.png"
#define TEXTURE_BOSSENEMY_WAKATU "data\\TEXTURE\\Enemy\\BossEnemy001.png"
#define TEXTURE_BOSSENEMY_MAYDAY "data\\TEXTURE\\Enemy\\BossEnemy002.png"
#define TEXTURE_BOSSENEMY_HEBI "data\\TEXTURE\\Enemy\\BossEnemy003.png"
#define TEXTURE_ENEMYRELATIVE "data\\TEXTURE\\Enemy\\EnemyRelative.png"
#define NORMALENEMY_MAXANIM (3)
//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X�i�e�j
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	typedef enum
	{//�G�̎��
		ENEMYTYPE_NONE = 0,		//�����Ȃ�
		ENEMYTYPE_NORMAL,		//�ʏ�
		ENEMYTYPE_BOSS,			//�{�X
		ENEMYTYPE_TUTORIAL,		//�`���[�g���A���p
		ENEMYTYPE_RELATIVE,		//�{�X�G���ő�
		ENEMYTYPE_MAX
	}EnemyType;

	typedef enum
	{//�G�̏��
		ENEMYSTATE_NONE = 0,	//�����Ȃ�
		ENEMYSTATE_DAMAGE,		//�_���[�W
		ENEMYSTATE_DEATH,		//���S
		ENEMYSTATE_EMERGENCE,	//���G
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	CEnemy();
	virtual ~CEnemy();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static CEnemy *Create(D3DXVECTOR3 pos, EnemyType type,int nLife);
	static HRESULT Load(void);
	static void UnLoad(void);
	static void SetFinishGame(bool bFinishGame) { m_bFinishGame = bFinishGame; }	//���g���C�I���ŃQ�[�����I��������t���O
	static void SetMaxNormalEnemy(int nNumMax) { m_nNumEnemyNormal = nNumMax; }		//�ʏ�G�̍ő吔�̐ݒ�
	static int GetMaxNormalEnemy(void) { return m_nNumEnemyNormal; }				//�ʏ�G�̍ő吔�̎擾
	static void SetMaxBossEnemy(int nNum) { m_nNumEnemyBoss = nNum; }				//�{�X�G�̍ő吔�̐ݒ�
	static int GetMaxBossEnemy(void) { return m_nNumEnemyBoss; }					//�{�X�G�̍ő吔�̎擾
	void SetEnemyState(ENEMYSTATE state) { m_EnemyState = state; }					//�G�̏�Ԃ̐ݒ�
	ENEMYSTATE GetEnemyState(void) { return m_EnemyState; }							//�G�̏�Ԃ̎擾
	void SetEnemyType(EnemyType type) { m_EnemyType = type; }						//�G�̎�ނ̐ݒ�
	EnemyType GetEnemyType(void) { return m_EnemyType; }							//�G�̎�ނ̎擾
	void SetLife(int nLife) { m_nLife = nLife; }									//�G�̗̑͂̐ݒ�

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX];	//���L�e�N�X�`���ւ̃|�C���^
	static int m_nNumEnemyNormal;					//�ʏ�G�̍ő吔
	static int m_nNumEnemyBoss;						//�{�X�G�̍ő吔
	static bool m_bFinishGame;						//���g���C�I���ŃQ�[�����I��������̃t���O
	D3DXVECTOR3 m_pos;								//�ʒu
	ENEMYSTATE m_EnemyState;						//�G�̏��
	EnemyType m_EnemyType;							//�G�̎��
	int m_nLife,m_nMaxLife;							//�G�̌��݂̗̑́A�ő�̗�
	D3DXCOLOR m_col;								//�F
	float m_Changecol;
	int m_nCntState;
};
#endif

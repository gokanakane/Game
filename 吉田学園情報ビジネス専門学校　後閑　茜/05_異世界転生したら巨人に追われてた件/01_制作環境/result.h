//*****************************************************************************
//
//				���U���g�̏���[result.h]
//				Auther : Shun Yokomichi
//
//*****************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "game.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;
class CPress;

//*****************************************************************************
//		�}�N����`
//*****************************************************************************
#define MAX_FALLINGMODE_TEXTURE			(7)			// ����ED�̍ő�e�N�X�`����
#define MAX_FALLINGMODE_POLYGON			(9)			// ����ED�̍ő�V�[����
#define MAX_PREYMODE_TEXTURE			(9)			// �ߐHED�̍ő�e�N�X�`����
#define MAX_PREYMODE_POLYGON			(10)		// �ߐHED�̍ő�V�[����
#define MAX_ESCAPEMODE_TEXTURE			(6)			// �ߐHED�̍ő�e�N�X�`����
#define MAX_ESCAPEMODE_POLYGON			(6)			// �ߐHED�̍ő�V�[����
#define MAX_FADERESTRICTION				(60*10)		// ���U���g���烉���L���O�֑J�ڂ��鎞��
#define MAX_PRESS_BUTTON				(2)			// �{�^���̐�

//*****************************************************************************
//		�N���X��`�i���U���g)
//*****************************************************************************
class CResult
{
public:
	CResult();
	virtual ~CResult();

	static CResult *Create(CGame::MODEGAME gameMode);

	virtual HRESULT Init();
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual HRESULT Load(void);	//	�ǂݍ��ފ֐�(�e�N�X�`��)
	virtual void Unload(void);	// �J������֐�(�e�N�X�`��)

								//	�ÓI�����o�֐�
	static void CntDownFadeTime(void);

private:
	static CResult *m_pResult;
	static int m_nCntfade;
};
//*****************************************************************************
//		�N���X��`�i����ED)
//*****************************************************************************
class CFallingEnd : public CResult
{
public:
	typedef enum
	{//�V�[���Ŏg���Ă�e�N�X�`���̎��
		SCENETYPE_MASK = 0,		//���w�i
		SCENETYPE_BLOCK,		//��
		SCENETYPE_PLAYER,		//�v���C���[
		SCENETYPE_SPEECH,		//�f����
		SCENETYPE_LIGHT,		//�Ɩ�
		SCENETYPE_SOUL,			//��
		SCENETYPE_LOGO,			//���S
		SCENETYPE_MENU_RETRY,	//���j���[�i���g���C�j
		SCENETYPE_MENU_QUIT,	//���j���[�i�N�C�b�g�j
		SCENETYPE_MAX
	}SceneType;

	typedef enum
	{// ����ED�̏��
		FALLINGMODE_NONE = 0,
		FALLINGMODE_MOVENOSTART,//�A�j���[�V�������J�n���
		FALLINGMODE_PLAYERFALL,	//�v���C���[�������Ă������
		FALLINGMODE_DEATH,		//�v���C���[�����񂾏��
		FALLINGMODE_LIGHTON,	//���C�g���t��
		FALLIMGMODE_MAX
	}FallingMode;

	typedef enum
	{// ���j���[�I���̏��
		MENUSTATE_NONE = 0,
		MENUSTATE_RETRY,
		MENUSTATE_QUIT,
		MENUSTATE_MAX
	}MenuState;

	typedef enum
	{// ���j���[�I����Ԃ̐F�ƈʒu
		MENUSTATECOLOR_NONE = 0,
		MENUSTATECOLOR_RETRY,
		MENUSTATECOLOR_QUIT,
		MENUSTATECOLOR_MAX
	}MenuStateCol;

	CFallingEnd();
	~CFallingEnd();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	HRESULT Load(void);										//	�ǂݍ��ފ֐�(�e�N�X�`��)
	void Unload(void);										// �J������֐�(�e�N�X�`��)

	void MoveScene(SceneType type);
	void SkipProduction(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_FALLINGMODE_TEXTURE];	// ���L�e�N�X�`���ւ̃|�C���^
	CScene2D *m_pScene[MAX_FALLINGMODE_POLYGON];					//�V�[���̃|�C���^�i�e�N�X�`���̍ő吔)
	FallingMode m_FallingMode;
	MenuState m_MenuState;
	MenuStateCol m_MenuCol;
	CPress *m_apPress[MAX_PRESS_BUTTON];
	float m_Scalvalue, m_fCntMove, m_fChengeMove;
	bool m_bSkipProduction;											//���o���΂����ǂ���
	int m_nSelectNum;
};
//*****************************************************************************
//		�N���X��`�i�ߐHED)
//*****************************************************************************
class CPreyEnd : public CResult
{
public:
	typedef enum
	{//�V�[���Ŏg���Ă�e�N�X�`���̎��
		SCENETYPE_SKY = 0,		//��
		SCENETYPE_WOOD,			//�X
		SCENETYPE_CLOUD,		//�_
		SCENETYPE_GROUND,		//�n��
		SCENETYPE_PLAYER,		//�v���C���[
		SCENETYPE_OPTION,		//�����L��
		SCENETYPE_SOUL,			//��
		SCENETYPE_LOGO,			//���S
		SCENETYPE_MENU_RETRY,	//���j���[�i���g���C�j
		SCENETYPE_MENU_QUIT,	//���j���[�i�N�C�b�g�j
		SCENETYPE_MAX
	}SceneType;

	typedef enum
	{// ����ED�̏��
		PREYMODE_NONE = 0,
		PREYMODE_MOVENOSTART,	//�A�j���[�V�������J�n���
		PREYMODE_PLAYERPREY,	//�v���C���[�����܂������
		PREYMODE_DEATH,			//�v���C���[�����񂾏��
		PREYMODE_MAX
	}PreyMode;

	typedef enum
	{// ���j���[�I���̏��
		MENUSTATE_NONE = 0,
		MENUSTATE_RETRY,
		MENUSTATE_QUIT,
		MENUSTATE_MAX
	}MenuState;

	typedef enum
	{// ���j���[�I����Ԃ̐F�ƈʒu
		MENUSTATECOLOR_NONE = 0,
		MENUSTATECOLOR_RETRY,
		MENUSTATECOLOR_QUIT,
		MENUSTATECOLOR_MAX
	}MenuStateCol;

	CPreyEnd();
	~CPreyEnd();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	HRESULT Load(void);									//	�ǂݍ��ފ֐�(�e�N�X�`��)
	void Unload(void);									// �J������֐�(�e�N�X�`��)

	void MoveScene(SceneType type);
	void SkipProduction(void);
	void ScrollCloud(float Scroll);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PREYMODE_TEXTURE];	// ���L�e�N�X�`���ւ̃|�C���^
	CScene2D *m_pScene[MAX_PREYMODE_POLYGON];					//�V�[���̃|�C���^�i�e�N�X�`���̍ő吔)
	PreyMode m_PreyEndMode;
	MenuState m_MenuState;
	MenuStateCol m_MenuCol;
	CPress *m_apPress[MAX_PRESS_BUTTON];
	int nCntframe;
	float m_fCntMove, m_fChengeMove;							//���̏c�ړ��p
	float m_fCntPlayerMove, m_fChangePlayerMove;				//�v���C���[�̏c�ړ��p
	float m_fCntWoodMove, m_fChangeWoodMove;					//�X�̏c�ړ��Ɏg��
	bool m_bSkipProduction;										//���o���΂����ǂ���
	float m_fOptionCol;											//�����L���̐F������Ɏg��
	int m_nSelectNum;
	float m_fCloudScroll;
};
//*****************************************************************************
//		�N���X��`�i����ED)
//*****************************************************************************
class CEscapeEnd : public CResult
{
public:
	typedef enum
	{//�V�[���Ŏg���Ă�e�N�X�`���̎��
		SCENETYPE_SKY = 0,		//��
		SCENETYPE_BG,			//�w�i
		SCENETYPE_CLOUD,		//�_
		SCENETYPE_ENEMY,		//�G
		SCENETYPE_PLAYER,		//�v���C���[
		SCENETYPE_LOGO,			//���S
		SCENETYPE_MAX
	}SceneType;

	CEscapeEnd();
	~CEscapeEnd();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	HRESULT Load(void);									//	�ǂݍ��ފ֐�(�e�N�X�`��)
	void Unload(void);									// �J������֐�(�e�N�X�`��)

	void ScrollCloud(float Scroll);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ESCAPEMODE_TEXTURE];	// ���L�e�N�X�`���ւ̃|�C���^
	CScene2D *m_pScene[MAX_ESCAPEMODE_POLYGON];						//�V�[���̃|�C���^�i�e�N�X�`���̍ő吔)
	float m_fScrollCloud;											//�_�X�N���[��
	float m_fCntMove, m_fChengeMove;								//�v���C���[�̍��E�h��
};

#endif

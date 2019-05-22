//=============================================================================
//
// �e���� [title.h]
// Author : 
//
//=============================================================================
#ifndef _TUTORIAL_H
#define _TUTORIAL_H

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TUTORIALTEX (6)
#define MAXTUTORIALPOLYGON (7)
#define TEXTURE_DESXRIPTIONBOOK		"data\\TEXTURE\\Tutorial\\Tutorial_Description-1.png"
#define TEXTURE_NARRATOR			"data\\TEXTURE\\Tutorial\\Tutorial_Sagetu.png"
#define TEXTURE_NARRATORSUBTITLE	"data\\TEXTURE\\Tutorial\\Tutorial_Narrator.png"
#define TEXTURE_SKIP				"data\\TEXTURE\\Tutorial\\Tutorial_Skip.png"
#define TEXTURE_LECTURE				"data\\TEXTURE\\Tutorial\\Tutorial_lecture.png"
#define TEXTURE_CHARACTORSKILL		"data\\TEXTURE\\Tutorial\\CharactorSelext_Status001.png"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;
class CScene2D;
class CEnemy;
//*****************************************************************************
// �N���X
//*****************************************************************************
class CTutorial
{
public:
	typedef enum
	{//�i���[�V�����̏��
		NARRATORSTATE_STEP1 = 0,	//���A
		NARRATORSTATE_STEP2,		//�X�L�b�v�ɂ���
		NARRATORSTATE_STEP3,		//�ړ��ɂ���
		NARRATORSTATE_STEP4,		//�G�ɂ���
		NARRATORSTATE_STEP5,		//�e���˂ɂ���
		NARRATORSTATE_STEP6,		//�X�R�A�ɂ���
		NARRATORSTATE_STEP7,		//�̗͂ɂ���
		NARRATORSTATE_STEP8,		//�^�����ɂ���
		NARRATORSTATE_STEP9,		//���@�ɂ���
		NARRATORSTATE_STEP10,		//���@�̒��ӎ���
		NARRATORSTATE_STEP11,		//�|�[�Y�ɂ���
		NARRATORSTATE_STEP12,		//�������猩�Ă�
		NARRATORSTATE_STEP13,		//�s���Ă�����Ⴂ
		NARRATORSTATE_MAX
	}NarratorState;

	typedef enum
	{//�}�X�N�̏��
		MASKALPHASTATE_NONE = 0,
		MASKALPHASTATE_FADEIN,
		MASKALPHASTATE_FADEOUT,
		MASKALPHASTATE_MAX
	}MaskAlphaState;

	typedef enum
	{//������
		LECTURESTATE_NONE = 0,
		LECTURESTATE_APPEARANCE,		//�o��
		LECTURESTATE_EXIT,				//�ޏ�
		LECTURESTATE_MAX
	}LectureState;

	typedef enum
	{//������
		CHARACTORSKILLSTATE_NONE = 0,
		CHARACTORSKILLSTATE_APPEARANCE,		//�o��
		CHARACTORSKILLSTATE_EXIT,			//�ޏ�
		CHARACTORSKILLSTATE_MAX
	}CharactorSkillState;

	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static NarratorState GetNarratorState(void) { return m_state; }
	static void SetMake(bool Make) { m_bMake = Make; }
	static void SetSkillUSe(bool Use) { m_SkillUse = Use; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TUTORIALTEX];	//���L�e�N�X�`���ւ̃|�C���^
	static CBg *m_pBG;
	static NarratorState m_state;
	static MaskAlphaState m_MaskState;
	static LectureState m_LectureState;
	static CharactorSkillState m_CharactorSkill;
	static bool m_SkillUse;
	static bool m_bMake,m_ButtonMake,m_bdisplay;
	D3DXVECTOR3 m_pos,m_Goalpos,m_StartPos;
	CScene2D *m_apScene2D[MAX_TUTORIALTEX];
	D3DXCOLOR m_col,m_MaskCol,m_LectureCol;
	float m_fChangeAlpha,m_fMaskAlpha,m_fLectureAlpha,m_fLecturepos;
	int m_nCntRandomEnemyMake;
};
#endif
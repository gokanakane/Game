//=============================================================================
//
// �����z�u���� [SetWord.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _SETWORD_H_
#define _SETWORD_H_

#include "main.h"
#include "scene.h"
#include "game.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CWord;
class CSceneBillBoard;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MATTEX	(20)

//*********************************************************************
//�v���C���[�N���X�̒�`
//*********************************************************************
class CSetWord : public CScene //�h���N���X
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		bool		bUse;	// �g���Ă��邩�ǂ���
		int			nCntPop;// �o������
	}Word_Pos;
	CSetWord();
	~CSetWord();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSetWord *Create();

	//*******************************
	// �擾 �ݒ� �̊֐�
	//*******************************
	void SetAnswer(int nNumAnswer) { m_nAnswer = nNumAnswer;}
	int GetPopNum(void) { return m_nNum; }						// �������鐔
	void SetCreateFlagr(bool bFlag) { m_bCreate = bFlag; }
	bool GetCreateFlag(void) { return m_bCreate; }

private:
	//�����o�ϐ�
public:
	//*******************************
	// Text�ǂݍ��ݗp
	//*******************************
	void LoadFile(char *pFileName);

	char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	char *GetLineTop(char *pStr);			//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�

	void WordCreate(void);			// �ʒu�̊��蓖�� 
	void WordUninit(void);			// �����l�����̏I��
	void PopWord(void);				// �����o��

	Word_Pos *m_pWordPos;
	D3DXVECTOR3 *m_AnswerNum;		// �����̃f�[�^���l
	int m_nAnswer;					// �����̑���
	int m_nRandAnswerNum;			// �����������_����
	int m_nNum;
	int m_nAnswerNumCount;			// �J�E���g
	bool m_bCreate;

	bool m_bUninitFlag;				// �X�e�[�W�ω����̃t���O
};

#endif
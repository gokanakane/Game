//=============================================================================
//
// �X�R�A��Տ��� [ScoreBase.h]
// Author : Gokan Akane
//
//=============================================================================
#ifndef _SCOREBASE_H
#define _SCOREBASE_H

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT (8)		//����

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;
//*****************************************************************************
// �N���X�i�h���j
//*****************************************************************************
class CScore : public CScene
{
public:
	typedef enum
	{//�X�R�A�̎��
		SCORETYPE_NONE = 0,
		SCORETYPE_GAME,
		SCORETYPE_RANKING,
		SCORETYPE_RESULT,
		SCORETYPE_MAX
	}ScoreType;

	CScore();
	virtual ~CScore();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static CScore*Create(ScoreType type);
	static void AddScore(int nValue);

protected:
	static int m_nScore;
	static int m_nScoreData[MAX_DIGIT];

private:

};
#endif

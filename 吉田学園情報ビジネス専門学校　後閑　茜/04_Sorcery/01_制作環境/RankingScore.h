//=============================================================================
//
// �V�[��2D�|���S������ [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _RANKINGSCORE_H
#define _RANKINGSCORE_H

#include "main.h"
#include "scoreBase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �N���X�i�h���j
//*****************************************************************************
class CRankingScore : public CScore
{
public:
	CRankingScore();
	~CRankingScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetHighScore(int nScore);

private:
	CNumber *m_apNumber[MAX_RANK_SCORE][MAX_DIGIT];
	int	g_nScore2, g_nRankingScore, g_aRankingScoreData[MAX_RANK_SCORE][MAX_DIGIT], m_nNewRank;
	//�n�C�X�R�A�A���u���ϐ��A���u���ϐ��A�ꌅ�ڂɖ߂�
	CManager::CHARACTORSELECT_STATE m_CharaSort, m_NewCharaSort;//����ւ��p

	bool bRank = true;
};

#endif
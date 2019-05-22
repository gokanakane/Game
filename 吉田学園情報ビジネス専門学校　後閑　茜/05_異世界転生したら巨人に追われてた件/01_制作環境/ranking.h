//*****************************************************************************
//
//				�����L���O�̏���[ranking.h]
//				Auther : Shun Yokomichi
//
//*****************************************************************************
#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"		// �V�[��
#include "score.h"		// �X�R�A

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;			// ����
class CRnkingLogo;		// �����L���O���S
class CUiPolygon;				// UI

//*****************************************************************************
//		�}�N����`
//*****************************************************************************
#define MAX_RANKING		(5)		// ����
#define MAX_RANK_LOGO	(6)		// �����L���O���S

//*****************************************************************************
//		�N���X��`(�����L���O)
//*****************************************************************************
class CRanking
{
public:
	CRanking();
	~CRanking();

	HRESULT Init(D3DXVECTOR3 pos);		// ������
	void	Uninit(void);				// �I������
	void	Update(void);				// �X�V����
	void	Draw(void);					// �`�揈��
	static void SaveRanking();			// �����L���O�̃Z�[�u
	static void LoadRanking();			// �����L���O�̓ǂݍ���

	// �ÓI�����o�ϐ�
	static CRanking *Create(D3DXVECTOR3 pos);
	static int GetPattern(void) { return m_Pattern; };
	static void SetPattern(int nPattern) { m_Pattern = nPattern; };

private:
	int		m_nTime;
	float   m_fColA;
	int		m_nSize;

	// �ÓI�����o�ϐ�
	static int m_Pattern;
	static CNumber2D *m_aRanking[MAX_RANKING][MAX_SCORE];
	static int m_nScore[MAX_RANKING];
	static CRnkingLogo *m_pLogo[MAX_RANK_LOGO];
	static CUiPolygon *m_apUi[MAX_RANKING];
	static int m_nNum;

};

#endif // !_RANKING_H_

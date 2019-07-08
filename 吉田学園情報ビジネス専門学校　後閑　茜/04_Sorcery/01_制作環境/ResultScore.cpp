//=============================================================================
//
// ���U���g�X�R�A���� [ResultScore.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "scoreBase.h"
#include "ResultScore.h"
#include "time.h"
#include "ranking.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//*****************************************************************************
// ��class CResultScore
//*****************************************************************************
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultScore::CResultScore()
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
	m_col = DEFALT_COL_WHITE;
	m_Alpha = 0.1f;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultScore::~CResultScore() {}
//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CResultScore::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create();
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(750.0f, 470.0f, 0.0f), nCnt, 30.0f, 60.0f);
		m_apNumber[nCnt]->SetCol(m_col);
		m_nScoreData[nCnt] = 0;
	}

	SetLastScore(CManager::GetScore());
	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CResultScore::Uninit(void)
{
	//�ŏI�X�R�A���}�l�[�W���[�ɓn���Ă���
	CManager::SetScore(m_nScore);

	//m_apNumber��j���i�|���S�����j�����ꂽ������Score���͔̂j������Ă��Ȃ��j
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}
}
//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CResultScore::Update(void)
{
	m_col.a += m_Alpha;
	if (m_col.a >= 1.0f)
	{
		m_col.a = 1.0f;
	}
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nScoreData[nCnt]);
		m_apNumber[nCnt]->SetCol(m_col);
	}
}
//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CResultScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}
//=============================================================================
// �ŏI�X�R�A�̕\��
//=============================================================================
void CResultScore::SetLastScore(int nScore)
{
	int nNum = 100000000;	//�X�R�A�̌���+1��
	int nNum1 = 10000000;	//�X�R�A�̌���

	m_nScore = nScore;

	/*�i�[���鐔�����v�Z*/
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_nScoreData[nCnt] = (m_nScore % nNum) / nNum1;

		//�������P�����炷
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}

}
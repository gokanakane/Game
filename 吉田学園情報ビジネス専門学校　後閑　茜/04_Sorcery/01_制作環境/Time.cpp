//=============================================================================
//
// ���ԏ��� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "time.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
int CTime::m_nTimeData[MAX_TIME] = {};
int CTime::m_nTime = 0;
CTime::TimeState CTime::m_Timestate = CTime::TIMESTATE_NONE;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime():CScene(5)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_nTimeData[nCnt] = 0;
		m_apNumber[nCnt] = NULL;
	}
	m_nTime = 0;
	m_Timestate = TIMESTATE_NONE;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime() {}
//=============================================================================
// ���Ԃ̐���
//=============================================================================
CTime *CTime::Create(void)
{
	CTime *pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;
		pTime->Init();
	}

	return pTime;
}
//=============================================================================
// ���Ԃ̏���������
//=============================================================================
HRESULT CTime::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create();
		m_apNumber[nCnt]->Init();
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(1150.0f, 100.0f, 0.0f), nCnt,20.0f,20.0f);
		m_nTimeData[nCnt] = 0;
	}

	m_nTime = 0;

	m_Timestate = TIMESTATE_NORMAL;

	AddTime();

	return S_OK;
}

//=============================================================================
// ���Ԃ̏I������
//=============================================================================
void CTime::Uninit(void)
{
	//m_apNumber��j���i�|���S�����j�����ꂽ������Time���͔̂j������Ă��Ȃ��j
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}

	//���Ԃ̔j��
	Release();
}
//=============================================================================
// ���Ԃ̍X�V����
//=============================================================================
void CTime::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt]->Update();
		m_apNumber[nCnt]->SetNumber(m_nTimeData[nCnt]);
	}

	if (m_Timestate == TIMESTATE_NORMAL)
	{
		m_nTime++;

		if ((m_nTime % 60) == 0)
		{
			for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
			{
				AddTime();

				m_apNumber[nCnt]->Update();
			}
		}
	}
}
//=============================================================================
// ���Ԃ̕`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}
//=============================================================================
// ���Ԃ̉��Z
//=============================================================================
void CTime::AddTime(void)
{
	int nNum = 1000;	//���Ԃ̌���+1��
	int nNum1 = 100;	//���Ԃ̌���
	int nTime;

	nTime = m_nTime/60;

	/*�i�[���鐔�����v�Z*/
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_nTimeData[nCnt] = (nTime % nNum) / nNum1;
		
		//�������P�����炷
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;

	}
}
//=============================================================================
// ���Ԃ̐ݒ�
//=============================================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;

}
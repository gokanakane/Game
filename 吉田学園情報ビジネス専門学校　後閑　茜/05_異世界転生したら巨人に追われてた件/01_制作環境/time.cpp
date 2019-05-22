//*****************************************************************************
//
//				�^�C���̏���[time.cpp]
//				Auther : Shun Yokomichi
//
//*****************************************************************************

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "time.h"		// �^�C��
#include "number.h"		// ����

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUMBER_WIDHT			(14.5f)		// ���̑傫��
#define	NUMBER_HIGHT			(14.5f)		// �����̑傫��
#define POS_X					(1257.0f)	// �ʒu���W(X��)
#define POS_Y					(69.0f)		// �ʒu���W(Y��)
#define POS_X_INTERVAL			(35.0f)		// �����Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int			CTime::m_nSecond = 0;
int			CTime::m_nMinute = 0;
int			CTime::m_nTime = 0;
CNumber2D	*CTime::m_apNumber[MAX_NUMBER] = {};

//*****************************************************************************
// �^�C���̐���
//*****************************************************************************
CTime *CTime::Create()
{
	CTime *pTime = NULL;		// �|�C���^�𐶐�

	if (pTime == NULL)
	{
		pTime = new CTime;
		if (pTime != NULL)
		{
			pTime->Init();
		}
	}

	return pTime;
}

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CTime::CTime() : CScene(PRIORITY_UI, OBJTYPE_NUMBER)
{
	// �f�t�H���g�l
	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{
		m_apNumber[nCntNum] = NULL;
	}
	m_nSecond = 0;
	m_nCntTime = 0;
	m_nMinute = 0;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTime::~CTime() {}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CTime::Init(void)
{
	CNumber::Load();		//�@�����̓ǂݍ���

	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{	// ����������
		m_apNumber[nCntNum] = new CNumber2D;
		if (nCntNum < MAX_NUMBER - 1)
		{	// �b�P�ʂ̈ʒu
			m_apNumber[nCntNum]->Init(D3DXVECTOR3(POS_X - (nCntNum * POS_X_INTERVAL), POS_Y, 0.0f), D3DXVECTOR3(NUMBER_WIDHT, NUMBER_HIGHT, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{	//�@���P�ʂ̈ʒu
			m_apNumber[nCntNum]->Init(D3DXVECTOR3(POS_X - (nCntNum * POS_X_INTERVAL + 20.0f), POS_Y, 0.0f), D3DXVECTOR3(NUMBER_WIDHT, NUMBER_HIGHT, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	// �ϐ��̏�����
	m_nSecond = 0;
	m_nMinute = 0;
	m_nCntTime = 0;
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CTime::Uninit(void)
{
	CNumber::Unload();		// Texture�̔j��

	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{	// �������̊J��
		if (m_apNumber[nCntNum] != NULL)
		{
			m_apNumber[nCntNum]->Uninit();
			m_apNumber[nCntNum] = NULL;
		}
	}

	CScene::SetDeath();		// ���S�t���O
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CTime::Update(void)
{
	m_nCntTime++;		// �J�E���^�[�̑���

	if ((m_nCntTime % 60) == 0)
	{	// 60�t���[�� 1�b
		AddTime(1);
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CTime::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_NUMBER; nCntNum++)
	{	// �������̕`��
		m_apNumber[nCntNum]->Draw();
	}
}

//*****************************************************************************
//		�^�C���̐ݒ�
//*****************************************************************************
void CTime::SetTime(int nTime)
{
	m_nSecond = nTime;

	if ((m_nSecond % 60) == 0)
	{	//60�b��������
		m_nMinute++;
		m_nSecond = 0;
	}

	int nTexData000 = m_nSecond;
	int nTexData001 = m_nMinute;

	for (int Number = 0; Number < MAX_NUMBER; Number++)
	{
		if (Number < MAX_NUMBER - 1)
		{	// �b�P��
			m_apNumber[Number]->SetTex((nTexData000 % 1), 1, D3DXVECTOR2((nTexData000 * 0.1f), 1.0f));
		}
		else
		{	// ���P��
			m_apNumber[Number]->SetTex((nTexData001 % 1), 1, D3DXVECTOR2((nTexData001 * 0.1f), 1.0f));
		}
		nTexData000 /= 10;
	}
}

//*****************************************************************************
//		�^�C���̉��Z
//*****************************************************************************
void CTime::AddTime(int nValue)
{
	m_nSecond += nValue;		// ���Z
	m_nTime += nValue;			// ���Z
	SetTime(m_nSecond);
}

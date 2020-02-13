//=============================================================================
//
// �o�H���̃r���{�[�h���� [waypoint.cpp]
// Author :�@�ڍ� ������
//
//=============================================================================
#include "waypoint.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "InputKeyboard.h"
#include "PlayerNumSelect.h"
#include "debugProc.h"

#include "sceneX.h"
#include "object.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CWaypoint::CWaypoint() : CScene(2)
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	m_nNumWayPoint = 0;
	m_nNumNowPoint = 0;
	m_FromHit = FROMHIT_NONE;
	m_bStageStart = false;
	m_bStageSetEnd = false;
	for (int nCntWP = 0; nCntWP < 8; nCntWP++)
	{
		m_pWayPointPos[nCntWP] = D3DXVECTOR3(0, 0, 0);
		m_nTargetNum[nCntWP] = 0;
	}
	m_nFlameCnt = 0;
}

//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CWaypoint::~CWaypoint()
{
}

//--------------------------------------------
// ����
//--------------------------------------------
CWaypoint *CWaypoint::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag)
{
	CWaypoint *pWaypoint = NULL;

	if (pWaypoint == NULL)
	{
		pWaypoint = new CWaypoint;

		if (pWaypoint != NULL)
		{
			//�l�̑��
			pWaypoint->m_size = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWaypoint->m_sizeOld = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			//�ݒ�
			pWaypoint->Init(/*pos*/);
			/*pWaypoint->BindTexture(Tag);*/
		}
	}
	return pWaypoint;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CWaypoint::Init(/*D3DXVECTOR3 pos*/)
{
	//CSceneBillBoard::Init(pos);
	D3DXVECTOR3 InitPos(0, 0, 0);
	D3DXVECTOR3 SetPos(0, 0, 0);
	m_PlayerPos = D3DXVECTOR3(0, 0, 0);
	//������
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		WayPoint[nCntWayPoint].pWayPoint = NULL;
		WayPoint[nCntWayPoint].WayPointPos = D3DXVECTOR3(0, 0, 0);
		WayPoint[nCntWayPoint].nWayPointNum = 9;
		WayPoint[nCntWayPoint].bInPlayer = false;
		WayPoint[nCntWayPoint].bBlock = false;
		WayPoint[nCntWayPoint].bAdjacent = false;
	}
	//����
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		SetPos = D3DXVECTOR3(-390.0f + InitPos.x, InitPos.y + InitPos.y, -390.0f + InitPos.z);

		WayPoint[nCntWayPoint].WayPointPos = SetPos;
		//WayPoint[nCntWayPoint].pWayPoint = CSceneBillBoard::Create(SetPos, 0, 0, "NUMBER");
		//WayPoint[nCntWayPoint].pWayPoint->Init(SetPos);
		//WayPoint[nCntWayPoint].pWayPoint->SetBillboard(SetPos, m_size.x, m_size.y);
		//WayPoint[nCntWayPoint].pWayPoint->SetTexture(0, 10, 1, 1);
		//X�����ɂ��炷
		InitPos.x += WAYPOINT_POS_WIDE;

		if (nCntWayPoint % SPLIT_WAYPOINT == SPLIT_WAYPOINT -1)
		{
			//X������߂�
			InitPos.x = 0;
			//Z�����ɂ��炷
			InitPos.z += WAYPOINT_POS_WIDE;
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWaypoint::Uninit(void)
{
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].pWayPoint != NULL)
		{
			WayPoint[nCntWayPoint].pWayPoint->Uninit();
			WayPoint[nCntWayPoint].pWayPoint = NULL;
		}
	}

	/*CSceneBillBoard::Uninit();*/
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWaypoint::Update(void)
{
	int nNowNumber = 0;		//������}�X�̔ԍ�
	int nAdjacent = 0;		//�אڂ��Ă���}�X�͉��}�X������Ă��邩
	bool bLand = false;		//�N�����}�X�ɏ���Ă���
	if (CGame::GetbStageSet() == false)
	{
		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			//WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
			WayPoint[nCntWayPoint].nWayPointNum = 9;
		}

		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			if (WayPoint[nCntWayPoint].bInPlayer == true)
			{	//������}�X�̔ԍ�����
				nNowNumber = nCntWayPoint;
				m_nNumNowPoint = nCntWayPoint;
				WayPoint[nCntWayPoint].nWayPointNum = 0;
				WayPoint[nCntWayPoint].bAdjacent = false;
				if (WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint != NULL)
				{
					//	WayPoint[nCntWayPoint].pWayPoint->SetTexture(1, 10, 1, 1);
				}
				bLand = true;
			}
		}

		//������}�X���牽�}�X������Ă��邩
		for (int nCntSplit = 1; nCntSplit < SPLIT_WAYPOINT + 3; nCntSplit++)
		{
			for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
			{
				//����8�}�X
#if 1
				if (nNowNumber - 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
					|| nNowNumber + 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != 0 && bLand == true
					|| nNowNumber + SPLIT_WAYPOINT == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT && bLand == true
					|| nNowNumber - SPLIT_WAYPOINT == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT && bLand == true
					|| nNowNumber - SPLIT_WAYPOINT + 1 == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT + 1 && (nCntWayPoint - SPLIT_WAYPOINT) % SPLIT_WAYPOINT != 0 && bLand == true
					|| nNowNumber - SPLIT_WAYPOINT - 1 == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT - 1 && (nCntWayPoint - SPLIT_WAYPOINT) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
					|| nNowNumber + SPLIT_WAYPOINT + 1 == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT + 1 && (nCntWayPoint + SPLIT_WAYPOINT) % SPLIT_WAYPOINT != 0 && bLand == true
					|| nNowNumber + SPLIT_WAYPOINT - 1 == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT - 1 && (nCntWayPoint + SPLIT_WAYPOINT) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true)
				{//�אڂ���}�X
					WayPoint[nCntWayPoint].nWayPointNum = 1;
					if (WayPoint[nCntWayPoint].pWayPoint != NULL)
					{
						//	WayPoint[nCntWayPoint].pWayPoint->SetTexture(2, 10, 1, 1);
					}
					WayPoint[nCntWayPoint].bAdjacent = true;
				}

				if (WayPoint[nCntWayPoint].nWayPointNum == nCntSplit && bLand == true && WayPoint[nCntWayPoint].bAdjacent != true)
				{//�אڃ}�X���痣��Ă���

					if ((nCntWayPoint + 1) % SPLIT_WAYPOINT != 0 && WayPoint[nCntWayPoint + 1].nWayPointNum > nCntSplit)
					{//�E���@�]�肪�o�Ȃ��}�X�͐܂�Ԃ��Ă���}�X�Ȃ̂Ō��Ȃ��悤�ɂ���
						WayPoint[nCntWayPoint + 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint + 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint + 1].bAdjacent = false;
					}
					if ((nCntWayPoint - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && WayPoint[nCntWayPoint - 1].nWayPointNum > nCntSplit)
					{//���� �]�肪������-1�̃}�X�͐܂�Ԃ��Ă���}�X�Ȃ̂Ō��Ȃ��悤�ɂ���
						WayPoint[nCntWayPoint - 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint - 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint - 1].bAdjacent = false;
					}
					if ((nCntWayPoint - SPLIT_WAYPOINT) >= 0 && WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
					{//�O ���������������Ƃ���0�ȉ��̎��͓���Ȃ�
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT].bAdjacent = false;
					}
					if ((nCntWayPoint + SPLIT_WAYPOINT) < MAX_WAYPOINT && WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
					{//��� �ő吔�ȏ�̎��͓���Ȃ�
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT].bAdjacent = false;
					}

					if (nNowNumber - nCntWayPoint == (SPLIT_WAYPOINT - 1) * nCntSplit && 0 <= nCntWayPoint - SPLIT_WAYPOINT + 1 && (nCntWayPoint - SPLIT_WAYPOINT + 1) % SPLIT_WAYPOINT != 0)
					{	//�E�O	��(5*5�Œ����ɂ���ꍇ)�@12 - 8 == ������ + 1 && 0�ȏ� && �܂�Ԃ��Ă��Ȃ�
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].bAdjacent = false;
					}
					if (nNowNumber - nCntWayPoint == (SPLIT_WAYPOINT + 1) * nCntSplit && 0 <= nCntWayPoint - SPLIT_WAYPOINT - 1 && (nCntWayPoint - SPLIT_WAYPOINT - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1)
					{	//���O	��(5*5�Œ����ɂ���ꍇ)�@12 - 6 == ������ - 1 && 0�ȏ� && �܂�Ԃ��Ă��Ȃ�
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].bAdjacent = false;
					}
					if (nCntWayPoint - nNowNumber == (SPLIT_WAYPOINT + 1) * nCntSplit  && MAX_WAYPOINT > nCntWayPoint + SPLIT_WAYPOINT + 1 && (nCntWayPoint + SPLIT_WAYPOINT + 1) % SPLIT_WAYPOINT != 0)
					{	//�E��	��(5*5�Œ����ɂ���ꍇ)�@18 - 12 == ������ + 1 && 25�ȓ� && �܂�Ԃ��Ă��Ȃ�
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].bAdjacent = false;
					}
					if (nCntWayPoint - nNowNumber == (SPLIT_WAYPOINT - 1) * nCntSplit  && MAX_WAYPOINT > nCntWayPoint + SPLIT_WAYPOINT - 1 && (nCntWayPoint + SPLIT_WAYPOINT - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1)
					{	//����	��(5*5�Œ����ɂ���ꍇ)�@16 - 12 == ������ - 1 && 25�ȓ� && �܂�Ԃ��Ă��Ȃ�
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].bAdjacent = false;
					}
				}
#endif
				//���͂S�}�X
#if 0
			//�ǂ����̃}�X�ɏ�����Ƃ�
				if (nNowNumber - 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
					|| nNowNumber + 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != 0 && bLand == true
					|| nNowNumber + SPLIT_WAYPOINT == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT && bLand == true
					|| nNowNumber - SPLIT_WAYPOINT == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT && bLand == true)
				{//�אڂ���}�X
					WayPoint[nCntWayPoint].nWayPointNum = 1;
					WayPoint[nCntWayPoint].pWayPoint->SetTexture(2, 10, 1, 1);
				}

				if (WayPoint[nCntWayPoint].nWayPointNum == nCntSplit && bLand == true)
				{//�אڃ}�X���痣��Ă���
				 //�������̌��ߕ�
				 //��������P�}�X���ꂽ�}�X�̉E���O������ė���Ă���}�X��������
					if (nCntWayPoint + 1 && (nCntWayPoint + 1) % SPLIT_WAYPOINT != 0 && WayPoint[nCntWayPoint + 1].nWayPointNum > nCntSplit)
					{//�E���@�]�肪�o�Ȃ��}�X�͐܂�Ԃ��Ă���}�X�Ȃ̂Ō��Ȃ��悤�ɂ���
						WayPoint[nCntWayPoint + 1].nWayPointNum = nCntSplit + 1;
						WayPoint[nCntWayPoint + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
					}
					if (nCntWayPoint - 1 && (nCntWayPoint - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && WayPoint[nCntWayPoint - 1].nWayPointNum > nCntSplit)
					{//���� �]�肪������-1�̃}�X�͐܂�Ԃ��Ă���}�X�Ȃ̂Ō��Ȃ��悤�ɂ���
						WayPoint[nCntWayPoint - 1].nWayPointNum = nCntSplit + 1;
						WayPoint[nCntWayPoint - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
					}
					if (nCntWayPoint - SPLIT_WAYPOINT && (nCntWayPoint - SPLIT_WAYPOINT) >= 0 && WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
					{//�O ���������������Ƃ���0�ȉ��̎��͓���Ȃ�
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
					}
					if (nCntWayPoint + SPLIT_WAYPOINT && (nCntWayPoint + SPLIT_WAYPOINT) < MAX_WAYPOINT && WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
					{//��� �ő吔�ȏ�̎��͓���Ȃ�
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
					}
				}
#endif
			}
		}

		if (CGame::GetbStageSet() == true && m_bStageSetEnd == false)
		{	//�X�e�[�W�؂�ւ�莞�ɓ����蔻��X�V
			m_bStageSetEnd = true;
		}
		else if (CGame::GetbStageSet() == false && m_bStageSetEnd == true)
		{
			CollisionObj();
			m_bStageSetEnd = false;
		}
		else
		{
			if (m_bStageStart == false)
			{	//�J�n���ɓ����蔻��X�V �ŏ��̂�
				CollisionObj();
				m_bStageStart = true;
			}
		}
	}


	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_B))
	{
		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			//WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
			WayPoint[nCntWayPoint].nWayPointNum = 9;
		}
	}

#ifdef _DEBUG
	int nNum2Cnt = 0;

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].nWayPointNum == 1)
		{
		//	CDebugProc::Print("cfcfcf", "2�̃}�X�̈ʒu : X ", WayPoint[nCntWayPoint].WayPointPos.x, " Y ", WayPoint[nCntWayPoint].WayPointPos.y, " Z ", WayPoint[nCntWayPoint].WayPointPos.z);
			nNum2Cnt++;
		}
	}

///	CDebugProc::Print("cn", "�Q�̃}�X�̐� :", nNum2Cnt);
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void CWaypoint::Draw(void)
{
}

//=============================================================================
// �ړ�����
//=============================================================================
D3DXVECTOR3 CWaypoint::Move(D3DXVECTOR3 pos)
{
	if (m_bMoveFlag == false)
	{
		if (pos.y > 30.0f)
		{	// �ʒu���w�肵���ꏊ���傫���ꍇ
			m_bMoveFlag = true;
		}
	}
	else if (m_bMoveFlag == true)
	{
		if (pos.y < 0.0f + m_size.y)
		{	// �ʒu���w�肵���ꏊ��菬�����ꍇ
			m_bMoveFlag = false;
		}
	}

	return pos;
}

//=============================================================================
// �g��k���̏���
//=============================================================================
void CWaypoint::ScaleSize(void)
{
	if (m_bScaleFlag == false)
	{	// �g�傷��
		m_size.x += 0.2f;
		m_size.y += 0.2f;
		if (m_size.x > 15.0f && m_size.y > 15.0f)
		{	// �k������t���O��
			m_bScaleFlag = true;
		}
	}
	else if (m_bScaleFlag == true)
	{	// �k������
		m_size.x -= 0.2f;
		m_size.y -= 0.2f;
		if (m_size.x < m_sizeOld.x && m_size.y < m_sizeOld.y)
		{	// �g�傷��t���O��
			m_bScaleFlag = false;
		}
	}
}

//=============================================================================
// �͈͓��̏���
//=============================================================================
void CWaypoint::InRange(D3DXVECTOR3 pos)
{
	//�v���C���[�̈ʒu�L��
	m_PlayerPos = pos;

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (pos.z <= WayPoint[nCntWayPoint].WayPointPos.z + WAYPOINT_HIT && pos.z >= WayPoint[nCntWayPoint].WayPointPos.z - WAYPOINT_HIT)
		{// z�͈̔͂̒�
			if (pos.x <= WayPoint[nCntWayPoint].WayPointPos.x + WAYPOINT_HIT && pos.x >= WayPoint[nCntWayPoint].WayPointPos.x - WAYPOINT_HIT)
			{// x�͈̔͂̒�
				//�v���C���[������Ă���
				//WayPoint[nCntWayPoint].pWayPoint->SetTexture(1, 10, 1, 1);
				WayPoint[nCntWayPoint].bInPlayer = true;
				WayPoint[nCntWayPoint].nWayPointNum = 0;
			}
			else
			{
				WayPoint[nCntWayPoint].bInPlayer = false;
			}
		}
		else
		{
			WayPoint[nCntWayPoint].bInPlayer = false;
		}
	}
}

//=============================================================================
// �ړ��\�Ȉʒu��Ԃ�����
//=============================================================================
D3DXVECTOR3 &CWaypoint::ReturnPointMove(void)
{
	m_nNumWayPoint = 0;

	for (int nCntWP = 0; nCntWP < 8; nCntWP++)
	{
		m_pWayPointPos[nCntWP] = D3DXVECTOR3(0, 0, 0);
		m_nTargetNum[nCntWP] = 0;
	}

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].bAdjacent == true && WayPoint[nCntWayPoint].bBlock == false)
		{	//���͂̃}�X�̈ʒu���Ɣԍ����L��
			m_pWayPointPos[m_nNumWayPoint] = WayPoint[nCntWayPoint].WayPointPos;
			m_nTargetNum[m_nNumWayPoint] = nCntWayPoint;
			m_nNumWayPoint++;

			if (m_nNumWayPoint == 8)
			{
				break;
			}
		}
	}
	return m_pWayPointPos[0];
}

//=============================================================================
// �ړ��\�Ȑ���Ԃ�����
//=============================================================================
int CWaypoint::CntWayPoint(void)
{
	return m_nNumWayPoint;
}

//=============================================================================
// �I�u�W�F�N�g���菈��
//=============================================================================
void CWaypoint::CollisionObj(void)
{
	int nCntHitObj = 0; //�������������J�E���g

	CScene *pScene = NULL;

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		// �擪�̃I�u�W�F�N�g���擾
		pScene = CScene::GetTop(SCENEX_PRIORITY);

		while (pScene != NULL)
		{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
		 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
			{// ���S�t���O�������Ă��Ȃ�����
			 // �I�u�W�F�N�g�̎�ނ��m���߂�
				CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneX�փL���X�g(�^�̕ύX)
				if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
				{
					if (pSceneX->GetCollsionType() != CSceneX::COLLSIONTYPE_FLOORCOLLSION)
					{
						bool  bLand = pSceneX->CollisionIN(WayPoint[nCntWayPoint].WayPointPos, D3DXVECTOR3(WAYPOINT_RADIUS, 0, WAYPOINT_RADIUS));
						//�I�u�W�F�N�g�ɓ�������
						if (bLand == true)
						{
							WayPoint[nCntWayPoint].bBlock = true;
							WayPoint[nCntWayPoint].nWayPointNum = 9;
							//break;
							//WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
						}
					}
				}
			}
			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}


	//�I�u�W�F�N�g�Ɠ������Ă��Ȃ��E�F�C�|�C���g���X�V
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].bBlock == true)
		{
			// �擪�̃I�u�W�F�N�g���擾
			pScene = CScene::GetTop(SCENEX_PRIORITY);
			while (pScene != NULL)
			{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
			 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
				CScene *pSceneNext = pScene->GetNext();
				if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
				{// ���S�t���O�������Ă��Ȃ�����
				 // �I�u�W�F�N�g�̎�ނ��m���߂�
					CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneX�փL���X�g(�^�̕ύX)
					if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
					{
						if (pSceneX->GetCollsionType() != CSceneX::COLLSIONTYPE_FLOORCOLLSION)
						{
							bool  bLand = pSceneX->CollisionIN(WayPoint[nCntWayPoint].WayPointPos, D3DXVECTOR3(WAYPOINT_RADIUS, 0, WAYPOINT_RADIUS));
							CObject *pSceneObj = ((CObject*)pSceneX);
							if (bLand == true)
							{//�������Ă��Ȃ�
								nCntHitObj++;
							}
						}
					}
				}
				// ���̃V�[���ɐi�߂�
				pScene = pSceneNext;
			}

			if (nCntHitObj == 0)
			{//��x���I�u�W�F�N�g�ɓ������Ă��Ȃ�
				WayPoint[nCntWayPoint].bBlock = false;
			}
		}
	}
}


//=============================================================================
// �I�u�W�F�N�g���菈��
//=============================================================================
CWaypoint::WAYPOINT &CWaypoint::GetWayPoint(void)
{
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		//�I�u�W�F�N�g�Ɠ������Ă���
		if (WayPoint[nCntWayPoint].bBlock == true)
		{

		}
	}

	return WayPoint[0];
}

//=============================================================================
// �s�����Ƃ��Ă���}�X�ԍ����擾
//=============================================================================
int CWaypoint::GetNumTargetPoint(int nWayPoint)
{
	if (nWayPoint > MAX_WAYPOINT)
	{
		nWayPoint = 0;
	}
	if (nWayPoint < 0)
	{
		nWayPoint = 0;
	}

	return m_nTargetNum[nWayPoint];
}

//=============================================================================
// �ׂ̃}�X��ڕW�ɂ���
//=============================================================================
D3DXVECTOR3 CWaypoint::GetNextWayPoint(int nWayPoint)
{
	int nReturnNum = nWayPoint;
	int nRightNum = nWayPoint;
	int nLeftNum = nWayPoint;

	int nParallel = 0;	//���s�ړ�
	int nRouteCnt[2] = { 0,0 };	//���}�X�ňړ��ł��邩
	bool bEndRoute = false;
	bool bRouteSearchEnd[2] = { false ,false };

	m_FromHit = FROMHIT_NONE;

	//�s�����Ƃ��Ă���}�X���u���b�N������
	if (WayPoint[nReturnNum].bBlock == true)
	{
		if (m_nNumNowPoint - nWayPoint == SPLIT_WAYPOINT)
		{//��O�Ɉړ����悤�Ƃ��Ă���
			nParallel += SPLIT_WAYPOINT;
			m_FromHit = FROMHIT_BACK;
		}
		else if (m_nNumNowPoint - nWayPoint == -SPLIT_WAYPOINT)
		{//���Ɉړ����悤�Ƃ��Ă���
			nParallel -= SPLIT_WAYPOINT;
			m_FromHit = FROMHIT_FRONT;
		}
		else if (m_nNumNowPoint - nWayPoint == -1)
		{//�E�Ɉړ����悤�Ƃ��Ă���
			nParallel -= 1;
			m_FromHit = FROMHIT_LEFT;
		}
		else if (m_nNumNowPoint - nWayPoint == 1)
		{//���Ɉړ����悤�Ƃ��Ă���
			nParallel += 1;
			m_FromHit = FROMHIT_RIGHT;
		}
		else if (m_nNumNowPoint - nWayPoint == 0)
		{//������}�X���u���b�N
			nParallel += 0;
			m_FromHit = FROMHIT_IN;
		}
	}

	while (bEndRoute == false)
	{
		if (nRightNum >= MAX_WAYPOINT || nLeftNum >= MAX_WAYPOINT
			|| nRightNum < 0 || nLeftNum < 0)
		{
			bEndRoute = true;
			nRightNum = MAX_WAYPOINT / 2;
			nLeftNum = MAX_WAYPOINT / 2;
		}

		switch (m_FromHit)
		{
		case FROMHIT_FRONT:
			//�E��胋�[�g
			if (WayPoint[nRightNum].bBlock == true && bRouteSearchEnd[0] == false)
			{//�ڕW�̃}�X���u���b�N �E���@������x�E���̃u���b�N������
				nRightNum = nRightNum + 1;
				nRouteCnt[0]++;
			}
			if (WayPoint[nRightNum].bBlock == false && bRouteSearchEnd[0] == false)
			{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �E���@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
				nRightNum = nRightNum + nParallel;
				bRouteSearchEnd[0] = true;
			}

			//����胋�[�g
			if (WayPoint[nLeftNum].bBlock == true && bRouteSearchEnd[1] == false)
			{//�ڕW�̃}�X���u���b�N �����@������x�����̃u���b�N������
				nLeftNum = nLeftNum - 1;
				nRouteCnt[1]++;
			}
			if (WayPoint[nLeftNum].bBlock == false && bRouteSearchEnd[1] == false)
			{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �����@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
				nLeftNum = nLeftNum + nParallel;
				bRouteSearchEnd[1] = true;
			}
			//�E��荶���̃��[�g�𒲂׏I�����
			if (bRouteSearchEnd[0] == true && bRouteSearchEnd[1] == true)
			{
				bEndRoute = true;
			}

			break;
		case FROMHIT_BACK:

			//�E��胋�[�g
			if (WayPoint[nRightNum].bBlock == true && bRouteSearchEnd[0] == false)
			{//�ڕW�̃}�X���u���b�N �E���@������x�E���̃u���b�N������
				nRightNum = nRightNum - 1;
				nRouteCnt[0]++;
			}
			if (WayPoint[nRightNum].bBlock == false && bRouteSearchEnd[0] == false)
			{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �E���@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
				nRightNum = nRightNum + nParallel;
				bRouteSearchEnd[0] = true;
			}
			if (WayPoint[nLeftNum].bBlock == true && bRouteSearchEnd[1] == false)
			{//�ڕW�̃}�X���u���b�N �����@������x�����̃u���b�N������
				nLeftNum = nLeftNum + 1;
				nRouteCnt[1]++;
			}
			if (WayPoint[nLeftNum].bBlock == false && bRouteSearchEnd[1] == false)
			{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �����@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
				nLeftNum = nLeftNum + nParallel;
				bRouteSearchEnd[1] = true;
			}
			//�E��荶���̃��[�g�𒲂׏I�����
			if (bRouteSearchEnd[0] == true && bRouteSearchEnd[1] == true)
			{
				bEndRoute = true;
			}

			break;
		case FROMHIT_RIGHT:
			//�E��胋�[�g
			if (WayPoint[nRightNum].bBlock == true && bRouteSearchEnd[0] == false)
			{//�ڕW�̃}�X���u���b�N �E���@������x�E���̃u���b�N������
				nRightNum = nRightNum + SPLIT_WAYPOINT;
				nRouteCnt[0]++;
			}
			if (WayPoint[nRightNum].bBlock == false && bRouteSearchEnd[0] == false)
			{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �E���@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
				nRightNum = nRightNum + nParallel;
				bRouteSearchEnd[0] = true;
			}
			//����胋�[�g
			if (WayPoint[nLeftNum].bBlock == true && bRouteSearchEnd[1] == false)
			{//�ڕW�̃}�X���u���b�N �E���@������x�E���̃u���b�N������
				nLeftNum = nLeftNum - SPLIT_WAYPOINT;
				nRouteCnt[1]++;
			}
			if (WayPoint[nLeftNum].bBlock == false && bRouteSearchEnd[1] == false)
			{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �E���@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
				nLeftNum = nLeftNum + nParallel;
				bRouteSearchEnd[1] = true;
			}
			//�E��荶���̃��[�g�𒲂׏I�����
			if (bRouteSearchEnd[0] == true && bRouteSearchEnd[1] == true)
			{
				bEndRoute = true;
			}
			break;
		case FROMHIT_LEFT:
			//�E��胋�[�g
			if (WayPoint[nRightNum].bBlock == true && bRouteSearchEnd[0] == false)
			{//�ڕW�̃}�X���u���b�N �E���@������x�E���̃u���b�N������
				nRightNum = nRightNum - SPLIT_WAYPOINT;
				nRouteCnt[0]++;
			}
			if (WayPoint[nRightNum].bBlock == false && bRouteSearchEnd[0] == false)
			{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �E���@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
				nRightNum = nRightNum + nParallel;
				bRouteSearchEnd[0] = true;
			}
			//����胋�[�g
			if (WayPoint[nLeftNum].bBlock == true && bRouteSearchEnd[1] == false)
			{//�ڕW�̃}�X���u���b�N �E���@������x�E���̃u���b�N������
				nLeftNum = nLeftNum + SPLIT_WAYPOINT;
				nRouteCnt[1]++;
			}
			if (WayPoint[nLeftNum].bBlock == false && bRouteSearchEnd[1] == false)
			{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �E���@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
				nLeftNum = nLeftNum + nParallel;
				bRouteSearchEnd[1] = true;
			}
			//�E��荶���̃��[�g�𒲂׏I�����
			if (bRouteSearchEnd[0] == true && bRouteSearchEnd[1] == true)
			{
				bEndRoute = true;
			}

			break;
		case FROMHIT_IN:

			if (m_PlayerPos.x > WayPoint[nReturnNum].WayPointPos.x && m_PlayerPos.z > WayPoint[nReturnNum].WayPointPos.z)
			{//�E�O
				if (WayPoint[nReturnNum + 1].bBlock == false)
				{//�E
					nReturnNum = nReturnNum + 1;
				}
				else if (WayPoint[nReturnNum - SPLIT_WAYPOINT].bBlock == false)
				{//�O
					nReturnNum = nReturnNum - SPLIT_WAYPOINT;
				}
				else if (WayPoint[nReturnNum - SPLIT_WAYPOINT + 1].bBlock == false)
				{//�΂߉E�O
					nReturnNum = nReturnNum - SPLIT_WAYPOINT + 1;
				}
			}
			else if (m_PlayerPos.x < WayPoint[nReturnNum].WayPointPos.x && m_PlayerPos.z > WayPoint[nReturnNum].WayPointPos.z)
			{//���O
				if (WayPoint[nReturnNum - 1].bBlock == false)
				{//��
					nReturnNum = nReturnNum - 1;
				}
				else if (WayPoint[nReturnNum - SPLIT_WAYPOINT].bBlock == false)
				{//�O
					nReturnNum = nReturnNum - SPLIT_WAYPOINT;
				}
				else if (WayPoint[nReturnNum - SPLIT_WAYPOINT - 1].bBlock == false)
				{//�΂ߍ��O
					nReturnNum = nReturnNum - SPLIT_WAYPOINT -1;
				}
			}
			else if (m_PlayerPos.x > WayPoint[nReturnNum].WayPointPos.x && m_PlayerPos.z < WayPoint[nReturnNum].WayPointPos.z)
			{//�E��
				if (WayPoint[nReturnNum + 1].bBlock == false)
				{//�E
					nReturnNum = nReturnNum + 1;
				}
				else if (WayPoint[nReturnNum + SPLIT_WAYPOINT].bBlock == false)
				{//��
					nReturnNum = nReturnNum + SPLIT_WAYPOINT;
				}
				else if (WayPoint[nReturnNum + SPLIT_WAYPOINT + 1].bBlock == false)
				{//�΂߉E��
					nReturnNum = nReturnNum + SPLIT_WAYPOINT + 1;
				}
			}
			else if (m_PlayerPos.x < WayPoint[nReturnNum].WayPointPos.x && m_PlayerPos.z < WayPoint[nReturnNum].WayPointPos.z)
			{//����
				if (WayPoint[nReturnNum - 1].bBlock == false)
				{//��
					nReturnNum = nReturnNum - 1;
				}
				else if (WayPoint[nReturnNum + SPLIT_WAYPOINT].bBlock == false)
				{//��
					nReturnNum = nReturnNum + SPLIT_WAYPOINT;
				}
				else if (WayPoint[nReturnNum + SPLIT_WAYPOINT - 1].bBlock == false)
				{//�΂ߍ���
					nReturnNum = nReturnNum + SPLIT_WAYPOINT - 1;
				}
			}
			bEndRoute = true;
			break;
		default:
			bEndRoute = true;
			break;
		}
	}

	//�ŒZ���[�g�̃}�X
	if (nRouteCnt[0] <= nRouteCnt[1] && m_FromHit != FROMHIT_IN)
	{
		nReturnNum = nRightNum;
	}
	else if (nRouteCnt[0] > nRouteCnt[1] && m_FromHit != FROMHIT_IN)
	{
		nReturnNum = nLeftNum;
	}
	else if (m_FromHit == FROMHIT_IN)
	{
		nReturnNum = nReturnNum;
	}
	else
	{
		nReturnNum = nRightNum;
	}
	return WayPoint[nReturnNum].WayPointPos;
}



#if 0
if (WayPoint[nReturnNum].bBlock == true)
{//�ڕW�̃}�X���u���b�N �E���@������x�E���̃u���b�N������
	nReturnNum = nReturnNum + 1;
	nRouteCnt++;
}
if (WayPoint[nReturnNum].bBlock == false)
{//�ڕW�̃}�X���u���b�N�ł͂Ȃ� �E���@�u���b�N�ł͂Ȃ��}�X�̔ԍ����L��
	nReturnNum = nReturnNum - nParallel;
	bEndRoute = true;
	break;
}
#endif
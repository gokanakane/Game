//=============================================================================
//
// �V�[������ [scene.h]
// Author : �ڍ� ������
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "sceneX.h"
#include "debugProc.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "player.h"
#include "tutorial.h"
#include "game.h"
#include "avoidui.h"

#include "point.h"
#include "word.h"
#include "CameraManager.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CScene::m_nNumAll = 0;
int CScene::m_nNumPriority[NUM_PRIORITY] = {};
CScene *CScene::m_apTop[NUM_PRIORITY] = {};
CScene *CScene::m_apCur[NUM_PRIORITY] = {};
bool    CScene::m_bPause = false;
bool    CScene::m_bDebug2Ddraw = false;
//=============================================================================
// �V�[���N���X�̃R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objType)
{
	// �l�̃N���A
	m_nID = 0;
	m_pPrev = NULL;
	m_pNext = NULL;
	m_bDeath = false;
	m_bPause = false;

	if (m_apCur[nPriority] == NULL)
	{// �J�����g��NULL�Ȃ猻�݂̈ʒu���擪
		m_apTop[nPriority] = this;
	}
	else
	{// �J�����g��NULL����Ȃ�������
	 // �O���Scene��m_pNext�ɍ������Scene������
		m_apCur[nPriority]->m_pNext = this;
	}

	m_pPrev = m_apCur[nPriority];	// �������Scene��m_pPrev�ɑO���Scene������
	m_pNext = NULL;					// ���̃V�[���͂܂�����Ă��Ȃ�����NULL
	m_apCur[nPriority] = this;		// �J�����g�̈ʒu���������Scene�Ɉړ�����
	m_nPriority = nPriority;		// �v���C�I���e�B��ۑ�
	m_objType = objType;			// �I�u�W�F�N�g�̎�ނ�ۑ�
	m_nNumPriority[nPriority]++;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̉������
//=============================================================================
void CScene::ReleseAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
	 // �擪���擾����
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// ��ɂȂ�܂ŃA�b�v�f�[�g����
		 // Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;

			// �X�V
			pScene->Uninit();

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
		pScene = m_apTop[nCntPriority];

		if (m_nNumPriority[nCntPriority] <= 0)
		{
			m_apTop[nCntPriority] = NULL;
			m_apCur[nCntPriority] = NULL;
		}

		while (pScene != NULL)
		{
			// Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				// �t���O�������Ă���I�u�W�F�N�g�������Ă���
				pScene->DeleteAll();
				pScene = NULL;
			}

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}

	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdeteAll(void)
{
	CScene *pScene = NULL;

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�t�F�[�h���Ă��Ȃ��Ƃ��Ƀ|�[�Y�ł���
	/*for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (CCommand::GetCommand("PAUSE", nCnt) && CFade::GetFade() == CFade::FADE_NONE && CManager::GetMode() == CManager::MODE_GAME && m_bPause == true)
		{
			m_bPause = false;
		}
	}*/


	if (CCommand::GetCommand("DEBUG2D") == true)
	{
		m_bDebug2Ddraw = m_bDebug2Ddraw ? false : true;
	}

	if (m_bPause == false)
	{
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{// �D�揇�ʂ̐����J��Ԃ�
		 // �擪���擾����
			pScene = m_apTop[nCntPriority];

			while (pScene != NULL)
			{// ��ɂȂ�܂ŃA�b�v�f�[�g����

			 // Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
				CScene *pSceneNext = pScene->m_pNext;
				// �X�V
				if (pScene->GetObjType() != OBJTYPE_PAUSE)
				{
					if (pScene->m_bDeath == false)
					{
						pScene->Update();
					}
				}
				// ���̃V�[���ɐi�߂�
				pScene = pSceneNext;
			}
		}

		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{// �D�揇�ʂ̐����J��Ԃ�
			pScene = m_apTop[nCntPriority];

			while (pScene != NULL)
			{
				// Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
				CScene *pSceneNext = pScene->m_pNext;

				if (pScene->GetObjType() != OBJTYPE_PAUSE)
				{
					if (pScene->m_bDeath == true)
					{
						// �t���O�������Ă���I�u�W�F�N�g�������Ă���
						pScene->DeleteAll();
						pScene = NULL;
					}
				}
				// ���̃V�[���ɐi�߂�
				pScene = pSceneNext;
			}
		}
	}
	else
	{
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{// �D�揇�ʂ̐����J��Ԃ�
		 // �擪���擾����
			pScene = m_apTop[nCntPriority];

			while (pScene != NULL)
			{// ��ɂȂ�܂ŃA�b�v�f�[�g����

			 // Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
				CScene *pSceneNext = pScene->m_pNext;
				if (pScene->GetObjType() == OBJTYPE_PAUSE)
				{
					// �X�V
					pScene->Update();
				}
				// ���̃V�[���ɐi�߂�
				pScene = pSceneNext;
			}
		}

		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{// �D�揇�ʂ̐����J��Ԃ�
			pScene = m_apTop[nCntPriority];

			while (pScene != NULL)
			{
				// Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
				CScene *pSceneNext = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					// �t���O�������Ă���I�u�W�F�N�g�������Ă���
					pScene->DeleteAll();
					pScene = NULL;
				}

				// ���̃V�[���ɐi�߂�
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(int nCamera)
{
	CPlayer *pPlayer = NULL;
	CPoint *pPioint = NULL;

	pPlayer = CManager::GetPlayer(nCamera - 1);//�v���C���[�̎擾
	//pPioint = CManager::GetPoint(nCamera - 1);	// �|�C���g�擾

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
	 // �擪�̏ꏊ���擾
		CScene *pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// ��ɂȂ�܂ŕ`�悷��
		 // Draw�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;
			if (pScene->GetObjType() == OBJTYPE_PLAYER && nCamera != 5&& CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CPlayer *pPlayerScene = ((CPlayer*)pScene);
				if (pPlayerScene->GetID() == nCamera - 1)
				{	// ������`��
					int ntest = pPlayerScene->GetID();
					pScene->Draw();

					CPlayer *pPlayerOld = CManager::GetPlayer(pPlayerScene->GetID()); // �|�C���g��ID�擾
					CScene3D *pScene3D = ((CScene3D*)pPlayerOld->GetBulletUI());
					if (pScene3D != NULL) { pScene3D->Draw(); }

					CSceneBillBoard *pSceneBill = ((CSceneBillBoard*)pPlayerOld->GetMissileUI());
					if (pSceneBill != NULL) { pSceneBill->Draw(); }
				}
				else
				{	// ���v���C���[�`��
					if (pPlayer->GetVision(pPlayerScene->GetID()) == true)
					{
						int ntest = pPlayerScene->GetID();
						pScene->Draw();

						CPlayer *pPlayerOld = CManager::GetPlayer(pPlayerScene->GetID()); // �|�C���g��ID�擾
						if (pPlayerOld->GetMissileTargetID() == nCamera - 1)
						{
							CSceneBillBoard *pSceneBill = ((CSceneBillBoard*)pPlayerOld->GetMissileUI());
							if (pSceneBill != NULL) { pSceneBill->Draw(); }
						}

					}
				}
			}
			else if (pScene->GetObjType() == OBJTYPE_POINT && nCamera != 5 && CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CPoint *pPlayerScene = ((CPoint*)pScene);

				if (pPlayerScene->GetID() == nCamera - 1)
				{	// ������`��
					int ntest = pPlayerScene->GetID();
					pPlayerScene->Draw();

					pPioint = CManager::GetPoint(pPlayerScene->GetID()); // �|�C���g��ID�擾

					if (pPioint->GetID() == nCamera - 1)
					{	// ������`��
						CSceneBillBoard *pBill = ((CSceneBillBoard*)pPioint->GetCrwon());
						if (pBill != NULL) { pBill->Draw(); }
					}
				}
				else
				{	// ���v���C���[�`��
					if (pPlayer->GetVision(pPlayerScene->GetID()) == true)
					{
						int ntest = pPlayerScene->GetID();
						pPlayerScene->Draw();

						pPioint = CManager::GetPoint(pPlayerScene->GetID());
						CSceneBillBoard *pBill = ((CSceneBillBoard*)pPioint->GetCrwon());
						if (pBill != NULL) { pBill->Draw(); }
					}
				}
			}
			else if (pScene->GetObjType() == OBJTYPE_SCENEX&& CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CSceneX *pSceneX = ((CSceneX*)pScene);
				if (pSceneX->GetModelType() == CLoad::MODEL_BUSH)
				{	//���ނ�̂ݔ���
					//�ǂ̃v���C���[�J��������n��
					pSceneX->SetCameraNum(nCamera - 1);
					// ���f���`��
					pScene->Draw();
				}
				else
				{	//���ނ�ȊO��`��
					pScene->Draw();
				}
			}
			else if (pScene->GetObjType() == OBJTYPE_WORD && nCamera != 5 && CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CWord *pWord = ((CWord*)pScene);

				CSceneBillBoard *pBill = ((CSceneBillBoard*)pWord->GetPopBill());

				if (pBill != NULL && pBill->GetColFlag() == true)
				{	// 3�����ڒT��������ꍇ
					pBill->SetBillboard(pBill->GetPos(), 200.0f, 17.0f);
					if (pWord->GetID(nCamera - 1) >= 0 && pWord->GetID(nCamera - 1) <= 3)
					{	// 1P�`4P�̏ꍇ
						pBill->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					}
					else
					{	// �������g�̔ԍ��ȊO
						pBill->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						pBill->SetBillboard(pBill->GetPos(), 80.0f, 17.0f);
					}
				}
				if (pBill != NULL && pBill->GetColFlag() == false)
				{	// 3�����ڒT���������ꍇ
					pBill->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					pBill->SetBillboard(pBill->GetPos(), 80.0f, 17.0f);
				}
				pWord->Draw();

			}
			else if (pScene->GetObjType() == OBJTYPE_AVOIDUI&& CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{
				CAvoidUi *pAvoidUI = ((CAvoidUi*)pScene);
				//�ǂ̃v���C���[�J��������n��
				pAvoidUI->SetCameraNum(nCamera - 1);
				//���f���`��
				pScene->Draw();
			}
			else if (pScene->GetObjType() == OBJTYPE_PAUSE)
			{//�|�[�Y�p�J�����̎��̓|�[�Y�̂ݕ`�悷��
				if (m_bPause == true)
				{
					pScene->Draw();
				}
			}
			else if ((pScene->GetObjType() == OBJTYPE_SCENE2D || pScene->GetObjType() == OBJTYPE_BILLBOARD
					|| pScene->GetObjType() == OBJTYPE_TIME || pScene->GetObjType() == OBJTYPE_POINT)
						&& CCameraManager::GetCameraName() != "PAUSE_CAMERA")
			{//
				if (m_bDebug2Ddraw == false)
				{
					pScene->Draw();
				}
			}
			else if(CCameraManager::GetCameraName() != "PAUSE_CAMERA" && pScene->GetObjType() != OBJTYPE_CROWN &&
				pScene->GetObjType() != OBJTYPE_BULLETUI && pScene->GetObjType() != OBJTYPE_MISSILEUI)
			{
				// �`��
				pScene->Draw();
			}

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̉������
//=============================================================================
void CScene::Release(void)
{
	// ���S�t���O�𗧂Ă�
	m_bDeath = true;
}

//=============================================================================
// �t���O���������I�u�W�F�N�g�̉������
//=============================================================================
void CScene::DeleteAll(void)
{
	int nPriority;
	nPriority = m_nPriority;

	// ������I�u�W�F�N�g�̑O�����邩�ǂ���
	if (m_pPrev == NULL)
	{// �O�����Ȃ���
	 // �擪�����ɂ��炷
		m_apTop[nPriority] = m_pNext;
	}
	else
	{// �O�����鎞
	 // �O�̃I�u�W�F�N�g�ɂ��鎩���̏������̃I�u�W�F�N�g�ɓn��
		m_pPrev->m_pNext = m_pNext;
	}

	// ������I�u�W�F�N�g�̎������邩�ǂ���
	if (m_pNext == NULL)
	{// �������Ȃ���
	 // ���݁i�Ō���j�̃I�u�W�F�N�g��O�̃I�u�W�F�N�g�ɓn��
		m_apCur[nPriority] = m_pPrev;
	}
	else
	{// �������鎞
	 // ���ɂ���I�u�W�F�N�g�ɂ��鎩���̏���O�̃I�u�W�F�N�g�ɓn��
		m_pNext->m_pPrev = m_pPrev;
	}

	// ����������
	delete this;

	m_nNumPriority[nPriority]--;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ̐ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// �D�揇�ʂ̎擾
//=============================================================================
int CScene::GetPriority(void)
{
	return m_nPriority;
}

//=============================================================================
// �擪�̃I�u�W�F�N�g���擾
//=============================================================================
CScene *CScene::GetTop(int nPriority)
{
	return m_apTop[nPriority];
}

//=============================================================================
// ���̃I�u�W�F�N�g�̃|�C���^���擾
//=============================================================================
CScene *CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// ���S�t���O���擾
//=============================================================================
bool CScene::GetDeath(void)
{
	return m_bDeath;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ̎擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}
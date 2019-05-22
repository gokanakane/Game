//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "Pause.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScene *CScene::m_apScene[MAX_MYPRIORITY][MAX_POLYGON] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
	{
		if (m_apScene[nPriority][nCnt] == NULL)
		{//�󂾂�����N���G�C�g����Ă�����̂�������
			m_apScene[nPriority][nCnt] = this;
			m_nNumAll++;
			m_nId = nCnt;
			m_nPriority = nPriority;
			break;
		}
	}

	m_Objtype = OBJTYPE_NONE;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}
//=============================================================================
// ���ׂẴ|���S���̊J������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_MYPRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{//���������c���Ă���
					/* �I������ */
				m_apScene[nCntPriority][nCnt]->Uninit();

				/* �������̊J�� */
				delete m_apScene[nCntPriority][nCnt];
				m_apScene[nCntPriority][nCnt] = NULL;
			}
		}
	}

	m_nNumAll = 0;
}
//=============================================================================
// ���ׂẴ|���S���̊J������
//=============================================================================
void CScene::ReleaseAllFade(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_MYPRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{//���������c���Ă���
				CScene::OBJTYPE objtype;
				objtype = m_apScene[nCntPriority][nCnt]->GetObjtype();		//�I�u�W�F�N�g�̃^�C�v�������m�F�ł���

				if (objtype != OBJTYPE_FADE)
				{
					/* �I������ */
					m_apScene[nCntPriority][nCnt]->Uninit();

					/* �������̊J�� */
					delete m_apScene[nCntPriority][nCnt];
					m_apScene[nCntPriority][nCnt] = NULL;
				}
			}
		}
	}

	m_nNumAll = 0;
}
//=============================================================================
// ���ׂẴ|���S���̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_MYPRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{//���������c���Ă���
				CManager::MODE mode = CManager::GetMode();
				if (mode == CManager::MODE_GAME)
				{
					bool bPause = CPause::GetPause();
					if (bPause == false)
					{
						/* �X�V���� */
						m_apScene[nCntPriority][nCnt]->Update();
					}
				}
				else
				{
					/* �X�V���� */
					m_apScene[nCntPriority][nCnt]->Update();
				}
			}
		}
	}
}
//=============================================================================
// ���ׂẴ|���S���̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_MYPRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
		{
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{//���������c���Ă���
			 /* �`�揈�� */
				m_apScene[nCntPriority][nCnt]->Draw();
			}
		}
	}
}
//=============================================================================
// �I�u�W�F�N�g�̔j��
//=============================================================================
void  CScene::Release(void)
{
	/* delete����ƃV�[���̒��g���Ȃ��Ȃ�B
	m_nId,m_mPriority�������邽�߂ǂ����Q�Ƃ��邩�킩��Ȃ��Ȃ�̂ŁA��x���[�J���ϐ��Ɉڂ��Ă��K�v������B*/
	int nId, nPriority;
	nId = m_nId;
	nPriority = m_nPriority;

	if (m_apScene[nPriority][nId] != NULL)//m_apScene[this->m_nId]�Ƃ�������
	{//�󂶂�Ȃ����������
#if 0
		/* ���ꂶ��_�� */
		delete m_apScene[m_nId];		//���
		m_apScene[m_nId];
		m_nNumAll--;					//�ő吔�����炷
#endif
		delete m_apScene[nPriority][nId];
		m_apScene[nPriority][nId] = NULL;
		m_nNumAll--;					//�ő吔�����炷
	}
}
//=============================================================================
// �I�u�W�F�N�g�^�C�v�̐ݒ�
//=============================================================================
void CScene::SetObjtype(const OBJTYPE type)
{
	m_Objtype = type;
}
//=============================================================================
// �V�[���̎擾
//=============================================================================
CScene *CScene::GetScene(int nPriority, int nIdx)
{
	return m_apScene[nPriority][nIdx];
}
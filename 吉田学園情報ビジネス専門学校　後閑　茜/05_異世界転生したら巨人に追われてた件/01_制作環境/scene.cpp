//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"		// �V�[��
#include "manager.h"	// �}�l�[�W���[
#include "renderer.h"	// �����_���[
#include "input.h"		// ����
#include "font.h"		// �t�H���g
#include "pause.h"		// �|�[�Y

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CScene		*CScene::m_pTop[PRIORITY_MAX] = {};			// �擪�̃I�u�W�F�N�g�ւ̃|�C���^			
CScene		*CScene::m_pCur[PRIORITY_MAX] = {};			// ���݂̃I�u�W�F�N�g�ւ̃|�C���^

int			CScene::m_nNumAll = 0;						// ����
int			CScene::m_nNumPri[PRIORITY_MAX] = {};		// ����
int			CScene::m_nStartUp = 0;						// �X�V�͈�k

//=============================================================================
// �R���X�g���N�^									(public)	*** CScene ***
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objType)
{
	m_pPrev = m_pCur[nPriority];						// �O�̃I�u�W�F�N�g�ݒ�
	m_pNext = NULL;										// ���̃I�u�W�F�N�g�ݒ�

	m_pCur[nPriority] = this;							// ���݂̃I�u�W�F�N�g�ݒ�

	if (m_pPrev != NULL)
	{// �O�̃I�u�W�F�N�g��NULL�ȊO�̏ꍇ
		m_pPrev->m_pNext = m_pCur[nPriority];			// �O�̎��̃I�u�W�F�N�g�ݒ�
	}

	m_nPriority = nPriority;							// ���ʐݒ�
	m_objType = objType;								// ���
	m_bDeath = false;									// ���S�t���O
	m_nNumAll++;										// �����J�E���g
	m_nNumPri[nPriority]++;								// �����J�E���g

	if (m_pTop[nPriority] == NULL)
	{// �擪�̃I�u�W�F�N�g��NULL�ȊO�̏ꍇ
		m_pTop[nPriority] = m_pCur[nPriority];			// �擪�̃I�u�W�F�N�g�ݒ�
	}
	else if (m_pTop[nPriority] == m_pCur[nPriority]->m_pPrev)
	{// �擪�̃I�u�W�F�N�g�ƑO�̃I�u�W�F�N�g�������ꍇ
		m_pTop[nPriority]->m_pNext = m_pCur[nPriority];	// �擪�̎��̃I�u�W�F�N�g�ݒ�
	}

	char *pObjName = ConObjtype(objType);
	int nLenght = strlen(pObjName);
	char cObjName[32];
	for (int nCount = 0; nCount < nLenght; nCount++)
	{
		cObjName[nCount] = pObjName[nCount];
	}
	cObjName[nLenght] = '\0';

	CFont *pFont = CRenderer::GetFont(CFont::FONTNUM_LOG);

	if (pFont != NULL)
	{
		pFont->SetMessage(CFont::SETTYPE_LOG, "�� Create : [%s(%d)]\n", cObjName, CScene::PRIORITY_4);
	}
}

//=============================================================================
// �f�X�g���N�^										(public)	*** CScene ***
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �S�t�F�[�h�ȊO�J������										(public)	*** CScene ***
//=============================================================================
void CScene::ReleaseMode(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_FADE; nCntPriority++)
	{// �J�E���g
		while (m_pTop[nCntPriority] != NULL)
		{// �擪�̃I�u�W�F�N�g��NULL�ɂȂ�܂�
			m_pTop[nCntPriority]->Uninit();			// �擪�̃I�u�W�F�N�g�I��
			m_pTop[nCntPriority]->Release();		// �J������
		}
		m_nNumPri[nCntPriority] = 0;				// �v���C�I���e�B����������
	}

	m_nNumAll = 0;									// ����������
}

//=============================================================================
// �S�J������										(public)	*** CScene ***
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{// �J�E���g
		while (m_pTop[nCntPriority] != NULL)
		{// �擪�̃I�u�W�F�N�g��NULL�ɂȂ�܂�
			m_pTop[nCntPriority]->Uninit();			// �擪�̃I�u�W�F�N�g�I��
			m_pTop[nCntPriority]->Release();		// �J������
		}
		m_nNumPri[nCntPriority] = 0;				// �v���C�I���e�B����������
	}

	m_nNumAll = 0;									// ����������
}

//=============================================================================
// �S�X�V����										(public)	*** CScene ***
//=============================================================================
void CScene::UpadteAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		bool bPause = CPause::GetPause();
		CScene *pScene = m_pTop[nCntPriority];		// �X�V�̃I�u�W�F�N�g�i�擪���L���j
		CScene *pNext = NULL;						// ���̃I�u�W�F�N�g�L��

		if (bPause == false && nCntPriority != 7 || bPause == true && nCntPriority == 7)
		{
			while (pScene != NULL)
			{// �X�V�̃I�u�W�F�N�g��NULL�ȊO�̏ꍇ
				pNext = pScene->m_pNext;				// ���̃I�u�W�F�N�g�ݒ�
				if (pScene->m_bDeath == false)
				{// �j�����Ȃ�
					pScene->Update();					// �X�V����
				}
				if (pScene->m_bDeath == true)
				{// �j������
					pScene->Release();					// �J������
				}
				pScene = pNext;							// �X�V�̃I�u�W�F�N�g�Ɏ��̃I�u�W�F�N�g�ݒ�
			}
		}
	}
}

//=============================================================================
// �S�`�揈��										(public)	*** CScene ***
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{// �J�E���g
		CScene *pScene = m_pTop[nCntPriority];		// �`��̃I�u�W�F�N�g�i�擪���L���j
		CScene *pNext = NULL;						// ���̃I�u�W�F�N�g�L��

		while (pScene != NULL)
		{// �`��̃I�u�W�F�N�g��NULL�ȊO�̏ꍇ
			pNext = pScene->m_pNext;				// ���̃I�u�W�F�N�g�ݒ�
			if (pScene->m_bDeath == false)
			{// �j�����Ȃ�
				pScene->Draw();						// �`�揈��
			}
			if (pScene->m_bDeath == true)
			{// �j������
				pScene->Release();					// �J������
			}
			pScene = pNext;							// �`��̃I�u�W�F�N�g�Ɏ��̃I�u�W�F�N�g�ݒ�
		}
	}
}

//=============================================================================
// �J������											(protected)	*** CScene ***
//=============================================================================
void CScene::Release(void)
{
	if (this != NULL)
	{// ������NULL�ȊO�̏ꍇ
		int nPriority = m_nPriority;
		OBJTYPE objType = m_objType;

		if (m_pPrev != NULL)	// m_pTop�ȊO
		{// �O�̃I�u�W�F�N�g��NULL�ȊO�̏ꍇ
			if (m_pTop[nPriority] == m_pPrev)
			{// �擪�̃I�u�W�F�N�g���O�̃I�u�W�F�N�g�Ɠ����ꍇ
				m_pTop[nPriority]->m_pNext = m_pNext;		// �擪�̎��̃I�u�W�F�N�g�ݒ�
			}

			m_pPrev->m_pNext = m_pNext;						// �O�̎��̃I�u�W�F�N�g�ݒ�
		}

		if (m_pNext != NULL)	// m_pCur�ȊO
		{// ���̃I�u�W�F�N�g��NULL�ȊO�̏ꍇ
			if (m_pCur[nPriority] == m_pNext)
			{// ���݂̃I�u�W�F�N�g���O�̃I�u�W�F�N�g�Ɠ����ꍇ
				m_pCur[nPriority]->m_pPrev = m_pPrev;		// ���݂̑O�̃I�u�W�F�N�g�ݒ�
			}

			m_pNext->m_pPrev = m_pPrev;						// ���̑O�̃I�u�W�F�N�g�ݒ�
		}

		if (m_pTop[nPriority] == this)
		{// �擪�̃I�u�W�F�N�g�������Ɠ����ꍇ
			m_pTop[nPriority] = m_pNext;					// �擪�̃I�u�W�F�N�g�����ɍX�V
		}
		if (m_pCur[nPriority] == this)
		{// ���݂̃I�u�W�F�N�g�������Ɠ����ꍇ
			m_pCur[nPriority] = m_pPrev;					// ���݂̃I�u�W�F�N�g��O�ɍX�V
		}

		m_pPrev = NULL;										// �O�̃I�u�W�F�N�g
		m_pNext = NULL;										// ���̃I�u�W�F�N�g

		char *pObjName = ConObjtype(objType);
		int nLenght = strlen(pObjName);
		char cObjName[32];
		for (int nCount = 0; nCount < nLenght; nCount++)
		{
			cObjName[nCount] = pObjName[nCount];
		}
		cObjName[nLenght] = '\0';

		CFont *pFont = CRenderer::GetFont(CFont::FONTNUM_LOG);

		if (pFont != NULL)
		{
			pFont->SetMessage(CFont::SETTYPE_LOG, "�~ Delete : [%s(%d)]\n", cObjName, nPriority);
		}

		delete this;										// �j��
		m_nNumPri[nPriority]--;								// �v���C�I���e�B���������炷
		m_nNumAll--;										// ���������炷
	}
}

//=============================================================================
// �I�u�W�F�N�g�^�C�v�����ϊ�����						(public)	*** CScene ***
//=============================================================================
char *CScene::ConObjtype(CScene::OBJTYPE objType)
{
	char cName[32];

	switch (objType)
	{
	case OBJTYPE_MESHFIELD:
		wsprintf(cName, "Meshfield");
		break;
	case OBJTYPE_MESHWALL:
		wsprintf(cName, "Meshwall");
		break;
	case OBJTYPE_MESHCYLINDER:
		wsprintf(cName, "Meshcylinder");
		break;
	case OBJTYPE_BG:
		wsprintf(cName, "Bg");
		break;
	case OBJTYPE_ENEMY:
		wsprintf(cName, "Enemy");
		break;
	case OBJTYPE_PLAYER:
		wsprintf(cName, "Player");
		break;
	case OBJTYPE_BULLET:
		wsprintf(cName, "Bullet");
		break;
	case OBJTYPE_EFFECT:
		wsprintf(cName, "Effect");
		break;
	case OBJTYPE_NUMBER:
		wsprintf(cName, "Number");
		break;
	case OBJTYPE_SCORE:
		wsprintf(cName, "Score");
		break;
	case OBJTYPE_RANKING:
		wsprintf(cName, "Ranking");
		break;
	case OBJTYPE_MENU:
		wsprintf(cName, "Menu");
		break;
	case OBJTYPE_PAUSE:
		wsprintf(cName, "Pause");
		break;
	case OBJTYPE_TITLE:
		wsprintf(cName, "Title");
		break;
	case OBJTYPE_FADE:
		wsprintf(cName, "Fade");
		break;
	case OBJTYPE_CAMERA:
		wsprintf(cName, "Camera");
		break;
	default:
		wsprintf(cName, "Unknow");
		break;
	}

	return &cName[0];
}
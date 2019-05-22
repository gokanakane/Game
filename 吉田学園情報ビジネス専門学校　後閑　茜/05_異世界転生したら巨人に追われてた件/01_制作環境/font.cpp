//=============================================================================
//
// �t�H���g���� [font.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "font.h"			// �t�H���g
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "input.h"			// ����

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
CFont *CFont::m_apFont[FONTNUM_MAX] = {};		// �V�[��

#ifdef _DEBUG
bool CFont::m_bDispAll = true;					// �\��
#else
bool CFont::m_bDispAll = false;					// �\��
#endif

char CFont::m_MessageData[CScene::OBJTYPE_MAX][MAX_MESSAGE] = {};

//=============================================================================
// �R���X�g���N�^									(public)	*** CFont ***
//=============================================================================
CFont::CFont()
{
	for (int nCntFont = 0; nCntFont < FONTNUM_MAX; nCntFont++)
	{// �V�[���J�E���g
		if (m_apFont[nCntFont] == NULL)
		{// NULL�̏ꍇ
			m_apFont[nCntFont] = this;				// ��������
			m_nID = nCntFont;
			m_bDisp = false;

			if (nCntFont == FONTNUM_COMMAND ||
				nCntFont == FONTNUM_DEBUG) { m_bDisp = true; }

#ifdef _DEBUG
			if (nCntFont == FONTNUM_TEST) { m_bDisp = true; }
#endif
			break;
		}
	}
}

//=============================================================================
// �f�X�g���N�^										(public)	*** CFont ***
//=============================================================================
CFont::~CFont()
{

}

//=============================================================================
// �S�J������										(public)	*** CScene ***
//=============================================================================
void CFont::ReleaseAll(void)
{
	for (int nCntFont = 0; nCntFont < FONTNUM_MAX; nCntFont++)
	{// �V�[���J�E���g
		if (m_apFont[nCntFont] != NULL)
		{// NULL�ȊO�̏ꍇ
		 // �|���S���X�V����
			m_apFont[nCntFont]->Uninit();

			delete m_apFont[nCntFont];
			m_apFont[nCntFont] = NULL;
		}
	}
}

//=============================================================================
// �S�`�揈��										(public)	*** CScene ***
//=============================================================================
void CFont::DrawAll(void)
{
	static int nCntPress = 0;

	if (CManager::GetInputKeyboard()->GetPress(DIK_F1) == true)
	{
		nCntPress++;
		if (nCntPress == 60)
		{
			m_bDispAll = m_bDispAll ? false : true;
		}
	}
	else
	{
		nCntPress = 0;
	}

	if (m_bDispAll == true)
	{
		for (int nCntFont = 0; nCntFont < FONTNUM_MAX; nCntFont++)
		{// �V�[���J�E���g
			if (m_apFont[nCntFont] != NULL)
			{// NULL�ȊO�̏ꍇ
			 // �|���S���X�V����
				m_apFont[nCntFont]->Draw();
			}
		}
	}
}

//=============================================================================
// �����ݒ菈��											(public)	*** CFont ***
//=============================================================================
void CFont::SetMessageData(CScene::OBJTYPE objType, SETTYPE nSetType, char *aMessage, ...)
{
	char cMessage[MAX_MESSAGE], cMessageCat[MAX_MESSAGE + (MAX_MESSAGE / 2)];
	cMessage[0] = '\0';	cMessageCat[0] = '\0';

	va_list arg;
	va_start(arg, aMessage);
	vsprintf(cMessage, aMessage, arg);
	va_end(arg);

	// ���������
	if (nSetType == 0)
	{
		wsprintf(&m_MessageData[objType][0], "%s", &cMessage[0]);
	}
	else if (nSetType == 1)
	{
		wsprintf(&cMessageCat[0], "%s", &m_MessageData[objType][0]);

		strcat(&cMessageCat[0], &cMessage[0]);
		cMessageCat[MAX_MESSAGE - 1] = '\0';

		wsprintf(&m_MessageData[objType][0], "%s", &cMessageCat[0]);
	}
	else if (nSetType == 2)
	{
		wsprintf(&cMessageCat[0], "%s", &cMessage[0]);

		strcat(&cMessageCat[0], &m_MessageData[objType][0]);
		cMessageCat[MAX_MESSAGE - 1] = '\0';

		wsprintf(&m_MessageData[objType][0], "%s", &cMessageCat[0]);
	}
}

//=============================================================================
// �N���G�C�g										(public)	*** CFont ***
//=============================================================================
CFont *CFont::Create(int nHeight, int nWidth, int nWeight, RECT rect, UINT uFormat, D3DXCOLOR col)
{
	CFont *pFont = NULL;			// �|�C���^

	if (pFont == NULL)
	{// NULL�̏ꍇ
		pFont = new CFont;			// �������m��
	}

	if (pFont != NULL)
	{// NULL�ȊO�̏ꍇ
		pFont->Init(nHeight, nWidth, nWeight, rect, uFormat, col);		// ����������
	}

	return pFont;
}

//=============================================================================
// ����������										(public)	*** CFont ***
//=============================================================================
HRESULT CFont::Init(int nHeight, int nWidth, int nWeight, RECT rect, UINT uFormat, D3DXCOLOR col)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateFont(pDevice, nHeight, nWidth, nWeight, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas", &m_pFont);

	m_rect = rect;
	m_uFormat = uFormat;
	m_col = col;

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CFont ***
//=============================================================================
void CFont::Uninit(void)
{
	if (m_pFont != NULL)
	{// NULL�ȊO�̏ꍇ
		m_pFont->Release();			// ���
		m_pFont = NULL;				// NULL��
	}
}

//=============================================================================
// �X�V����											(public)	*** CFont ***
//=============================================================================
void CFont::Update(void)
{

}

//=============================================================================
// �`�揈��											(public)	*** CFont ***
//=============================================================================
void CFont::Draw(void)
{
	if (m_pFont != NULL)
	{
		if (m_bDisp == true)
		{
			// �e�L�X�g�`��
			m_pFont->DrawText(NULL, m_Message, -1, &m_rect, m_uFormat, m_col);
		}
	}
}

//=============================================================================
// �����ݒ菈��											(public)	*** CFont ***
//=============================================================================
void CFont::SetMessage(SETTYPE nSetType, char *aMessage, ...)
{
	char cMessage[MAX_MESSAGE], cMessageCat[MAX_MESSAGE + (MAX_MESSAGE / 2)];
	cMessage[0] = '\0';	cMessageCat[0] = '\0';

	va_list arg;
	va_start(arg, aMessage);
	vsprintf(cMessage, aMessage, arg);
	va_end(arg);

	// ���������
	if (nSetType == 0)
	{
		wsprintf(&m_Message[0], "%s", &cMessage[0]);
	}
	else if (nSetType == 1)
	{
		wsprintf(&cMessageCat[0], "%s", &m_Message[0]);

		strcat(&cMessageCat[0], &cMessage[0]);
		cMessageCat[MAX_MESSAGE - 1] = '\0';

		wsprintf(&m_Message[0], "%s", &cMessageCat[0]);
	}
	else if (nSetType == 2)
	{
		wsprintf(&cMessageCat[0], "%s", &cMessage[0]);

		strcat(&cMessageCat[0], &m_Message[0]);
		cMessageCat[MAX_MESSAGE - 1] = '\0';

		wsprintf(&m_Message[0], "%s", &cMessageCat[0]);
	}
}

//=============================================================================
// �J������											(protected)	*** CScene ***
//=============================================================================
void CFont::Release(void)
{
	if (m_apFont[m_nID] != NULL)
	{// NUll�ȊO�̏ꍇ
		int nID = m_nID;					// ID��ۑ��i�f�[�^�̕s��h�~�j

		delete m_apFont[nID];		// �������J��
		m_apFont[nID] = NULL;		// NULL��
	}
}
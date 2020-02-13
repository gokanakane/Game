//---------------------------------------------------------------------
// �N���W�b�g���� [credit.cpp]
// Author : Yokomichi Shun
//---------------------------------------------------------------------
#include "credit.h"
#include "scene2D.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BACK_BG_POS	 (D3DXVECTOR3(1190.0f, 660.0f, 0.0f))	// �߂�̈ʒu
#define BACK_BG_SIZE (D3DXVECTOR2(100.0f, 80.0f))			// �߂�̃T�C�Y
#define COL_A		 (0.01f)								// �F�̌��Z�l
#define PURPOSE_COL_A	(0.3f)								// �w�肵���l�ȉ��̏ꍇ
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------

//--------------------------------------------
//���[�h�Z���N�g�N���X �R���X�g���N�^
//--------------------------------------------
CCredit::CCredit(int nPriority) : CScene(7)
{
	m_pCredit = NULL;
	m_pBack = NULL;
	m_nCntFlash = 0;
}

//--------------------------------------------
//���[�h�Z���N�g�N���X �f�X�g���N�^
//--------------------------------------------
CCredit::~CCredit(){}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CCredit *CCredit::Create()
{
	//���[�h�Z���N�g�̃|�C���^
	CCredit *pCredit;
	pCredit = new CCredit;

	//���[�h�Z���N�g�̏�����
	pCredit->Init();
	//���[�h�Z���N�g�̏���Ԃ�
	return pCredit;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCredit::Init(void)
{
	SetInit();	// �N���W�b�g�̈ʒu�ݒ�

	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_MODESELECT);
	return S_OK;
}

//=============================================================================
// ���[�h�Z���N�g�N���X �I������
//=============================================================================
void CCredit::Uninit(void)
{
	if (m_pCredit != NULL) { m_pCredit->Uninit(); m_pCredit = NULL; }
	if (m_pBack != NULL) { m_pBack->Uninit(); m_pBack = NULL; }

	//������j��
	Release();
}

//=============================================================================
// ���[�h�Z���N�g�N���X �X�V����
//=============================================================================
void CCredit::Update(void)
{
	Flash();	// �_�ŏ���

	if (CManager::GetXInput(0)->GetTrigger(CInputXPad::XPAD_RIGHT_SHOULDER) || CManager::GetInputKeyboard()->GetTrigger(DIK_BACKSPACE)
		|| CManager::GetInputKeyboard()->GetTrigger(DIK_ESCAPE) || CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		Uninit();
		CManager::SetMode(CManager::MODE_SELECT);
	}
}

//=============================================================================
// ���[�h�Z���N�g�N���X �`�揈��
//=============================================================================
void CCredit::Draw(void){}

//=============================================================================
// ���[�h�Z���N�g�N���X �ʒu�ݒ�
//=============================================================================
void CCredit::SetInit(void)
{
	if (m_pCredit == NULL)
	{	//�N���W�b�g
		m_pCredit = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , 0.0f), "CREADIT_BG", 5);
		m_pCredit->SetWidthHeight(SCREEN_WIDTH-450, SCREEN_HEIGHT-205);
	}

	if (m_pBack == NULL)
	{	// �߂�{�^��
		D3DXVECTOR3 pos = BACK_BG_POS;
		m_pBack = CScene2D::Create(pos, "BACK_PRESS", 6);
		m_pBack->SetWidthHeight(BACK_BG_SIZE.x, BACK_BG_SIZE.y);
		m_pBack->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================================================
// ���[�h�Z���N�g�N���X �F�̓_��
//=============================================================================
void CCredit::Flash(void)
{
	if (m_pBack != NULL)
	{
		D3DXCOLOR col = m_pBack->GetCol();
		col.a -= COL_A;
		if (col.a < PURPOSE_COL_A)
		{	// �w�肵���F�̒l�ȉ��̏ꍇ
			col.a = 1.0f;
		}

		m_pBack->SetCol(col);
	}
}
//=============================================================================
//
// �^�C�g���t���[������ [titleframe.cpp]
// Author : Shun Yokomichi
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "titleframe.h"		// �^�C�g���t���[��
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "sound.h"			// �T�E���h
#include "input.h"			// ����
#include "font.h"			// �t�H���g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NAME000	"data\\TEXTURE\\title\\UI_Frame001.png"	// �e�N�X�`��
#define	TEXTURE_NAME001	"data\\TEXTURE\\title\\UI_Frame000.png"	// �e�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CTitleFrame::m_pTexture[MAX_FRAME] = {};			// �e�N�X�`�����ւ̃|�C���^

																		//=============================================================================
																		// �R���X�g���N�^									(public)	*** CTitleLogo ***
																		//=============================================================================
CTitleFrame::CTitleFrame() : CScene2D(CScene::PRIORITY_UI, CScene::OBJTYPE_TITLE)
{

}

//=============================================================================
// �f�X�g���N�^									(public)	*** CTitleLogo ***
//=============================================================================
CTitleFrame::~CTitleFrame()
{

}

//=============================================================================
// ���[�h����									(public)	*** CTitleLogo ***
//=============================================================================
HRESULT CTitleFrame::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_pTexture[0] == NULL)
	{// NULL�̏ꍇ
	 // �e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME000, &m_pTexture[0]);
		D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME001, &m_pTexture[1]);
	}

	return S_OK;
}

//=============================================================================
// �A�����[�h����									(public)	*** CTitleLogo ***
//=============================================================================
void CTitleFrame::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_FRAME; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{// NULL�̏ꍇ
		 // �e�N�X�`���̐���
			m_pTexture[nCntTex]->Release();		// ���
			m_pTexture[nCntTex] = NULL;			// NULL��
		}
	}
}

//=============================================================================
// �m�ۏ���										(public)	*** CTitleLogo ***
//=============================================================================
CTitleFrame *CTitleFrame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float rot, int nTex)
{
	CTitleFrame *pTitleFrame = NULL;				// �|�C���^

	if (pTitleFrame == NULL)
	{// NULL�̏ꍇ
		pTitleFrame = new CTitleFrame;			// �������m��
	}

	if (pTitleFrame != NULL)
	{// NULL�ȊO�̏ꍇ
		pTitleFrame->Init(pos, size, rot);			// ����������
		pTitleFrame->BindTexture(m_pTexture[nTex]);	// �e�N�X�`���ݒ�
	}

	return pTitleFrame;
}

//=============================================================================
// ����������										(public)	*** CTitleLogo ***
//=============================================================================
HRESULT CTitleFrame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float rot)
{
	CScene2D::SetInitAll(pos, size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));			// �����l�ݒ�
	CScene2D::Setrot(rot);					// �����̐ݒ�
	CScene2D::Init();						// ����������

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CTitleLogo ***
//=============================================================================
void CTitleFrame::Uninit(void)
{
	CScene2D::Uninit();						// �I������
}

//=============================================================================
// �X�V����											(public)	*** CTitleLogo ***
//=============================================================================
void CTitleFrame::Update(void)
{
	m_msize = CScene2D::Getsize();
	m_msize.x += 7.0f;
	m_msize.y += 3.5f;
	CScene2D::Setsize(D3DXVECTOR3(m_msize.x, m_msize.y, m_msize.z));
	CScene2D::Update();						// �X�V����
	if (m_msize.x >= 1800.0f || m_msize.y >= 1200.0f)
	{	// ������x�̃T�C�Y�ɍs������I��
		CTitleFrame::Uninit();
	}
}

//=============================================================================
// �`�揈��											(public)	*** CTitleLogo ***
//=============================================================================
void CTitleFrame::Draw(void)
{
	CScene2D::Draw();						// �`�揈��
}
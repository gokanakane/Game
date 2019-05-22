//=============================================================================
//
// �^�C�g�����S���� [titlelogo.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "titlelogo.h"		// �^�C�g�����S
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "sound.h"			// �T�E���h
#include "input.h"			// ����
#include "font.h"			// �t�H���g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NAME000	"data\\TEXTURE\\title\\TitleLogo3.png"	// �e�N�X�`��
#define	TEXTURE_NAME001	"data\\TEXTURE\\title\\credit.png"		// �e�N�X�`��
#define CHANGE_TEMI		(600)									// ��ʂ��ς��܂ł̎���
#define SIZE_X			(500.0f)								// �T�C�Y�̏��(X��)
#define SIZE_Y			(200.0f)								// �T�C�Y�̏��(Y��)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CTitleLogo::m_pTexture[MAX_LOGO] = {};			// �e�N�X�`�����ւ̃|�C���^
int					CTitleLogo::m_Pattern = 0;
int					CTitleLogo::m_nData = 0;
//=============================================================================
// �R���X�g���N�^									(public)	*** CTitleLogo ***
//=============================================================================
CTitleLogo::CTitleLogo() : CScene2D(CScene::PRIORITY_UI, CScene::OBJTYPE_TITLE)
{

}

//=============================================================================
// �f�X�g���N�^									(public)	*** CTitleLogo ***
//=============================================================================
CTitleLogo::~CTitleLogo()
{

}

//=============================================================================
// ���[�h����									(public)	*** CTitleLogo ***
//=============================================================================
HRESULT CTitleLogo::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntTex = 0; nCntTex < MAX_LOGO; nCntTex++)
	{
		if (m_pTexture[nCntTex] == NULL)
		{// NULL�̏ꍇ
		 // �e�N�X�`���̐���
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME000, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME001, &m_pTexture[1]);
		}
	}

	return S_OK;
}

//=============================================================================
// �A�����[�h����									(public)	*** CTitleLogo ***
//=============================================================================
void CTitleLogo::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_LOGO; nCntTex++)
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
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, int nTex)
{
	CTitleLogo *pTitleLogo = NULL;				// �|�C���^

	if (pTitleLogo == NULL)
	{// NULL�̏ꍇ
		pTitleLogo = new CTitleLogo;			// �������m��
	}

	if (pTitleLogo != NULL)
	{// NULL�ȊO�̏ꍇ
		pTitleLogo->Init(pos, size, type);			// ����������
		pTitleLogo->BindTexture(m_pTexture[nTex]);	// �e�N�X�`���ݒ�
	}

	return pTitleLogo;
}

//=============================================================================
// ����������										(public)	*** CTitleLogo ***
//=============================================================================
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CScene2D::SetInitAll(pos, size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));			// �����l�ݒ�
	m_size = size;							// �T�C�Y�̑��
	CScene2D::Init();						// ����������
	m_Pattern = 0;
	m_nTime = 0;
	m_fColA = 0.0f;
	m_type = type;
	m_nData = 0;

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CTitleLogo ***
//=============================================================================
void CTitleLogo::Uninit(void)
{
	CScene2D::Uninit();						// �I������
}

//=============================================================================
// �X�V����											(public)	*** CTitleLogo ***
//=============================================================================
void CTitleLogo::Update(void)
{
	switch (m_type)
	{
	case TYPE_LOGO:
		// ���S�̏ꍇ
		if (SIZE_X >= m_size.x && SIZE_Y >= m_size.y && m_Pattern == 0)
		{	// ������x�T�C�Y�ɂȂ�܂�
			m_size.x += 4.0f;
			m_size.y += 1.6f;
			m_fColA = 1.0f;
		}
		else if (m_Pattern == 0)
		{	// �t���O��0�Ȃ�
			m_Pattern = 1;
		}

		m_nTime++;			// ���Ԃ̑���

		if (m_nTime >= CHANGE_TEMI)
		{	// �w�肵�����Ԉȏ�Ȃ�
			m_fColA -= 0.02f;		// �����x��������
			if (m_fColA <= 0.0f)
			{	// �����x��0.0f�ȉ��Ȃ�(�����Ȃ�)
				m_Pattern = 3;
				Uninit();
				return;
			}
		}
		break;

	case TYPE_CREDIT:
		m_nTime++;			// ���Ԃ̑���

		if (m_nTime >= CHANGE_TEMI)
		{	// �w�肵�����Ԉȏ�Ȃ�
			m_fColA -= 0.02f;		// �����x��������
			if (m_fColA <= 0.0f)
			{	// �����x��0.0f�ȉ��Ȃ�(�����Ȃ�)
				m_Pattern = 1;
				m_nData = 1;
				Uninit();
				return;
			}
		}
		else
		{
			m_fColA += 0.02f;		// �����x��������
			if (m_fColA >= 1.0f)
			{	// �����x��0.0f�ȉ��Ȃ�(�����Ȃ�)
				m_fColA = 1.0f;
			}
		}
		break;
	}

	CScene2D::Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColA));	// �F�̍X�V
	CScene2D::Setsize(m_size);				// �T�C�Y�̍X�V
	CScene2D::Update();						// �X�V����
}

//=============================================================================
// �`�揈��											(public)	*** CTitleLogo ***
//=============================================================================
void CTitleLogo::Draw(void)
{
	CScene2D::Draw();						// �`�揈��
}
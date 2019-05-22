//=============================================================================
//
// �����L���O���S���� [rankinglogo.cpp]
// Author : Shun Yokomichi
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "rankinglogo.h"	// �����L���O���S
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "sound.h"			// �T�E���h
#include "input.h"			// ����
#include "font.h"			// �t�H���g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NAME000	"data\\TEXTURE\\ranking\\RankingLogo000.png"	// �e�N�X�`��
#define	TEXTURE_NAME001	"data\\TEXTURE\\ranking\\Ranking001.png"	// �e�N�X�`��
#define	TEXTURE_NAME002	"data\\TEXTURE\\ranking\\Ranking002.png"	// �e�N�X�`��
#define	TEXTURE_NAME003	"data\\TEXTURE\\ranking\\Ranking003.png"	// �e�N�X�`��
#define	TEXTURE_NAME004	"data\\TEXTURE\\ranking\\Ranking004.png"	// �e�N�X�`��
#define	TEXTURE_NAME005	"data\\TEXTURE\\ranking\\Ranking005.png"	// �e�N�X�`��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CRnkingLogo::m_pTexture[MAX_RANK_LOGO] = {};			// �e�N�X�`�����ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^									(public)	*** CTitleLogo ***
//=============================================================================
CRnkingLogo::CRnkingLogo() : CScene2D(CScene::PRIORITY_UI, CScene::OBJTYPE_TITLE)
{

}

//=============================================================================
// �f�X�g���N�^									(public)	*** CTitleLogo ***
//=============================================================================
CRnkingLogo::~CRnkingLogo()
{

}

//=============================================================================
// ���[�h����									(public)	*** CTitleLogo ***
//=============================================================================
HRESULT CRnkingLogo::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntLogo = 0; nCntLogo < MAX_RANK_LOGO; nCntLogo++)
	{
		if (m_pTexture[nCntLogo] == NULL)
		{// NULL�̏ꍇ
			// �e�N�X�`���̐���
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME000, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME001, &m_pTexture[1]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME002, &m_pTexture[2]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME003, &m_pTexture[3]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME004, &m_pTexture[4]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME005, &m_pTexture[5]);
		}
	}

	return S_OK;
}

//=============================================================================
// �A�����[�h����									(public)	*** CTitleLogo ***
//=============================================================================
void CRnkingLogo::Unload(void)
{
	for (int nCntLogo = 0; nCntLogo < MAX_RANK_LOGO; nCntLogo++)
	{
		if (m_pTexture[nCntLogo] != NULL)
		{// NULL�̏ꍇ
		 // �e�N�X�`���̐���
			m_pTexture[nCntLogo]->Release();		// ���
			m_pTexture[nCntLogo] = NULL;			// NULL��
		}
	}
}

//=============================================================================
// �m�ۏ���										(public)	*** CTitleLogo ***
//=============================================================================
CRnkingLogo *CRnkingLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTexNum)
{
	CRnkingLogo *pRnkingLogo = NULL;				// �|�C���^

	if (pRnkingLogo == NULL)
	{// NULL�̏ꍇ
		pRnkingLogo = new CRnkingLogo;			// �������m��
	}

	if (pRnkingLogo != NULL)
	{// NULL�ȊO�̏ꍇ
		pRnkingLogo->Init(pos, size);			// ����������
		pRnkingLogo->BindTexture(m_pTexture[nTexNum]);	// �e�N�X�`���ݒ�
	}

	return pRnkingLogo;
}

//=============================================================================
// ����������										(public)	*** CTitleLogo ***
//=============================================================================
HRESULT CRnkingLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::SetInitAll(pos, size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));			// �����l�ݒ�
	m_size = size;							// �T�C�Y�̑��
	CScene2D::Init();						// ����������
	
	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CTitleLogo ***
//=============================================================================
void CRnkingLogo::Uninit(void)
{
	CScene2D::Uninit();						// �I������
}

//=============================================================================
// �X�V����											(public)	*** CTitleLogo ***
//=============================================================================
void CRnkingLogo::Update(void)
{
	CScene2D::Update();						// �X�V����
}

//=============================================================================
// �`�揈��											(public)	*** CTitleLogo ***
//=============================================================================
void CRnkingLogo::Draw(void)
{
	CScene2D::Draw();						// �`�揈��
}
//**************************************************************
//
//				�w�i�̏���[bg.h]
//				Auther : Shun Yokomichi
//
//**************************************************************
#include "scene3d.h"
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "game.h"
#include "player.h"

//**************************************************************
//				�}�N����`
//**************************************************************
#define BG_TEXTURENAME000	"data/TEXTURE/game/BG001.jpg"			//�ǂݍ��ރe�N�X�`��000

//**************************************************************
//				�ÓI�����o�ϐ�
//**************************************************************
LPDIRECT3DTEXTURE9 CBg::m_pTexture = NULL;

//**************************************************************
//				�w�i�̐���
//**************************************************************
CBg *CBg::Create()
{
	CBg *pBg = NULL;	// �|�C���^�̐���

	// �V�[���̐���
	if (pBg == NULL)
	{
		pBg = new CBg;
		if (pBg != NULL)
		{
			pBg->Init();
		}
	}

	return pBg;
}

//**************************************************************
//				�ǂݍ��ރe�N�X�`��
//**************************************************************
HRESULT CBg::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	CManager::MODE pMode = CManager::GetMode();				// ���[�h�̎擾

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME000, &m_pTexture);
	
	return S_OK;
}

//**************************************************************
//				�J������e�N�X�`��
//**************************************************************
void CBg::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	
}

//**************************************************************
//		�R���X�g���N�^
//**************************************************************
CBg::CBg() : CScene(PRIORITY_BG, OBJTYPE_BG)
{
	// �f�t�H���g�l
	m_mvoetex_x = 0.0f;
}

//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CBg::~CBg()
{

}

//**************************************************************
//		����������
//**************************************************************
HRESULT CBg::Init(void)
{
	CManager::MODE pMode = CManager::GetMode();

	m_pScene = new CScene3D(PRIORITY_BG, OBJTYPE_BG);
	if (m_pScene != NULL)
	{
		m_pScene->SetInitAll(D3DXVECTOR3(0.0f, 300.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 300.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), CScene3D::SCENE3DTYPE_BILLBOARD);		// �����l�ݒ�
		m_pScene->Init();
		m_pScene->BindTexture(m_pTexture);
	}

	return S_OK;
}

//**************************************************************
//		�I������
//**************************************************************
void CBg::Uninit(void)
{
	if (m_pScene != NULL)
	{	// NULL����Ȃ��ꍇ
		m_pScene->Uninit();
		m_pScene = NULL;
	}
	

	CScene::SetDeath();		// ���S�t���O
}

//**************************************************************
//		�X�V����
//**************************************************************
void CBg::Update(void)
{
	CManager::MODE pMode = CManager::GetMode();	

	if (pMode == CManager::MODE_TITLE)
	{
		m_mvoetex_x += 0.0008f;

		m_pScene->Setpos(D3DXVECTOR3(CManager::GetCamera()->GetPosVDest().x, m_pScene->Getpos().y, m_pScene->Getpos().z));
		m_pScene->SetTex(1, 0, D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(m_mvoetex_x, 0.0f));
	}
	else if (pMode == CManager::MODE_GAME)
	{
		if (CManager::GetCamera()->GetPosVDest().x - 2.0f <= CGame::GetPlayer()->Getpos().x)
		{
				m_mvoetex_x += 0.0004f;
		}
	
		m_pScene->Setpos(D3DXVECTOR3(CManager::GetCamera()->GetPosVDest().x, m_pScene->Getpos().y, m_pScene->Getpos().z));
		m_pScene->SetTex(1, 0, D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(m_mvoetex_x, 0.0f));
	}
}

//**************************************************************
//		�`�揈��
//**************************************************************
void CBg::Draw(void)
{
	m_pScene->Draw();
}
//**************************************************************
//
//				���C�t�̏���[life.cpp]
//				Auther : Shun Yokomichi
//
//**************************************************************
#include "life.h"			// ���C�t
#include "manager.h"		// �}�l�[�W���[
#include "game.h"			// �Q�[��
#include "player.h"			//�v���C���[
#include "renderer.h"		// �����_���[
#include "input.h"			// ����
#include "fade.h"			// �t�F�[�h
#include "sound.h"			//�T�E���h

//**************************************************************
//				�}�N����`
//**************************************************************
#define LIFE_TEXTURENAME000		"data/TEXTURE/game/LifeCore.png"	//�ǂݍ��ރe�N�X�`��000
#define LIFE_SIZE_X				(15.0f)								// X�̑傫��(����)
#define LIFE_SIZE_Y				(15.0f)								// Y�̑傫��(�c��)
#define POS_X					(145.0f)							// �ʒu���W(X��)
#define POS_Y					(70.0f)								// �ʒu���W(Y��)
#define POS_X_INTERVAL			(36.0f)								// �����Ԋu

//**************************************************************
//				�ÓI�����o�ϐ�
//**************************************************************
LPDIRECT3DTEXTURE9	CLife::m_pTexture = NULL;
bool				CLife::m_bUse[MAX_LIFE] = {true, true, true };
int					CLife::m_nLife = MAX_LIFE;

//**************************************************************
//				���C�t�̐���
//**************************************************************
CLife *CLife::Create()
{
	CLife *pLife = NULL;

	// �V�[���̐���
	if (pLife == NULL)
	{
		pLife = new CLife;
		if (pLife != NULL)
		{
			pLife->Init();
		}
	}

	return pLife;
}

//**************************************************************
//				�ǂݍ��ރe�N�X�`��
//**************************************************************
HRESULT CLife::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, LIFE_TEXTURENAME000, &m_pTexture);

	return S_OK;
}

//**************************************************************
//				�J������e�N�X�`��
//**************************************************************
void CLife::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//**************************************************************
//		�R���X�g���N�^
//**************************************************************
CLife::CLife() : CScene(PRIORITY_UI, OBJTYPE_NONE)
{
	// �f�t�H���g�l
	m_nLife = MAX_LIFE -1;
}

//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CLife::~CLife()
{

}

//**************************************************************
//		����������
//**************************************************************
HRESULT CLife::Init(void)
{

		for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
		{
			m_apScene[nCntLife] = new CScene2D(PRIORITY_UI, OBJTYPE_NONE);

			if (m_apScene[nCntLife] != NULL)
			{	// NULL�`�F�b�N
				m_apScene[nCntLife]->SetInitAll(D3DXVECTOR3(POS_X + (nCntLife * POS_X_INTERVAL), POS_Y, 0.0f), D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
				m_apScene[nCntLife]->Init();
				m_apScene[nCntLife]->BindTexture(m_pTexture);
			}
		}

	// �ϐ��̏�����
	m_nLife = MAX_LIFE - 1;
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		m_bUse[nCntLife] = true;
	}

	return S_OK;
}

//**************************************************************
//		�I������
//**************************************************************
void CLife::Uninit(void)
{
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (m_apScene[nCntLife] != NULL)
		{	// NULL�`�F�b�N
			m_apScene[nCntLife]->Uninit();
			m_apScene[nCntLife] = NULL;
		}
	}

	CScene::SetDeath();		// ���S�t���O
}

//**************************************************************
//		�X�V����
//**************************************************************
void CLife::Update(void)
{
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (m_bUse[nCntLife] == false)
		{
			m_apScene[nCntLife]->Setcol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
		else
		{
			m_apScene[nCntLife]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}


	if (CFade::GetFade() == CFade::FADE_NONE && m_nLife < 0)
	{// �t�F�[�h���Ă��Ȃ����(���U���g��ʂ�)
		if (CPlayer::GetFalling() == true)
		{
			CFade::Create(CManager::MODE_RESULT, CFade::FADE_OUT);
			CGame::SetGame(CGame::MODE_GAMEOVER001);				// ����ED

		}
		else
		{
			CFade::Create(CManager::MODE_RESULT, CFade::FADE_OUT);
			CGame::SetGame(CGame::MODE_GAMEOVER000);				// ���C�t���O�̃Q�[���I�[�o�[
		}
	}
}

//**************************************************************
//		�`�揈��
//**************************************************************
void CLife::Draw(void)
{

}

//**************************************************************
//		�_���[�W����
//**************************************************************
void CLife::HitDamage()
{
	// �T�E���h
	CSound *pSound = CManager::GetSound();

	if (m_bUse[m_nLife] == true)
	{
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE018);
		m_bUse[m_nLife] = false;
		m_nLife--;
		return;
	}
}

//**************************************************************
//		�񕜏���
//**************************************************************
void CLife::Recovery()
{
	if (m_nLife < 2)
	{
		m_nLife++;

		if (m_bUse[m_nLife] == false)
		{
			m_bUse[m_nLife] = true;
			return;
		}
	}
}
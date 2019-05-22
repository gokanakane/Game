//**************************************************************
//
//				�`���[�g���A���̏���[tutorial.cpp]
//				Auther : Shun Yokomichi
//
//**************************************************************
#include "scene2d.h"		// �V�[��2D
#include "tutorial.h"		// �`���[�g���A��
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "fade.h"			// �t�F�[�h
#include "input.h"			// ����
#include "press.h"			// �v���X�{�^��
#include "sound.h"			// �T�E���h

//**************************************************************
//				�}�N����`
//**************************************************************
#define TEXTURE	"data/TEXTURE/tutorial/Tutorial.png"	//�ǂݍ��ރe�N�X�`��000

//**************************************************************
//				�ÓI�����o�ϐ�
//**************************************************************
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;
CPress			   *CTutorial::m_apPress[PRESS_KEY] = {};

//**************************************************************
//				�ǂݍ��ރe�N�X�`��
//**************************************************************
HRESULT CTutorial::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	if (m_pTexture == NULL)
	{
		D3DXCreateTextureFromFile(pDevice, TEXTURE, &m_pTexture);
	}

	return S_OK;
}

//**************************************************************
//				�J������e�N�X�`��
//**************************************************************
void CTutorial::Unload(void)
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
CTutorial::CTutorial()
{
	// �f�t�H���g�l
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}
}

//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CTutorial::~CTutorial()
{

}

//**************************************************************
//		����������
//**************************************************************
HRESULT CTutorial::Init(void)
{
	CManager::MODE pMode = CManager::GetMode();

	//Load();
	CPress::Load();

	m_pScene = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_BG);	// ���I�m��

	if (m_pScene != NULL)
	{	// NULL����Ȃ��Ȃ�
		m_pScene->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.25, 1.0f));		// �����l�ݒ�
		m_pScene->Init();
		m_pScene->BindTexture(m_pTexture);
	}

	for (int nCntPress = 0; nCntPress < PRESS_KEY; nCntPress++)
	{
		if (m_apPress[nCntPress] == NULL)
		{
			m_apPress[nCntPress] = new CPress;	// ���I�m��
		}

		if (m_apPress[nCntPress] != NULL)
		{
			float rot = 0.0f;		// rot�̕ϐ�
			if (nCntPress == 0)
			{	// 0�̏ꍇ
				rot = -D3DX_PI * 0.5f;		// �����ݒ�
				m_apPress[nCntPress]->Init(D3DXVECTOR3(50.0f + (nCntPress * (1150.0f)), SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, rot);
				m_apPress[nCntPress]->SetType(CPress::TYPE_MANUAL);	// �^�C�v�̐ݒ�
			}
			if (nCntPress == 1)
			{	// �P�̏ꍇ
				rot = D3DX_PI * 0.5f;		// �����̐ݒ�
				m_apPress[nCntPress]->Init(D3DXVECTOR3(50.0f + (nCntPress * (1170.0f)), SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, rot);
			}
			else if (nCntPress == 2)
			{
				m_apPress[nCntPress]->Init(D3DXVECTOR3(70.0f + ((nCntPress - nCntPress) * (1170.0f)), 600.0f, 0.0f),
					D3DXVECTOR3(80.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, rot);
				m_apPress[nCntPress]->SetType(CPress::TYPE_NONE);	// �^�C�v�̐ݒ�
			}
			else if (nCntPress == 3)
			{
				m_apPress[nCntPress]->Init(D3DXVECTOR3(30.0f + ((nCntPress - 2) * (1170.0f)), 600.0f, 0.0f),
					D3DXVECTOR3(80.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, rot);
				m_apPress[nCntPress]->SetType(CPress::TYPE_NONE);	// �^�C�v�̐ݒ�
			}
			else if (nCntPress == 4)
			{
				m_apPress[nCntPress]->Init(D3DXVECTOR3(100.0f + ((nCntPress - nCntPress) * (1170.0f)), 680.0f, 0.0f),
					D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, D3DX_PI);
				m_apPress[nCntPress]->SetType(CPress::TYPE_NONE);	// �^�C�v�̐ݒ�
			}
			else if (nCntPress == 5)
			{
				m_apPress[nCntPress]->Init(D3DXVECTOR3(20.0f + ((nCntPress - 4) * (1170.0f)), 680.0f, 0.0f),
					D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 0.0f);
				m_apPress[nCntPress]->SetType(CPress::TYPE_NONE);	// �^�C�v�̐ݒ�
			}
		}
	}

	// ������
	m_nPress = 0;
	m_fTexX = 0.0f;
	m_bPress = false;
	m_bmove = false;

	return S_OK;
}

//**************************************************************
//		�I������
//**************************************************************
void CTutorial::Uninit(void)
{
	CPress::Unload();
	if (m_pScene != NULL)
	{	// NULL����Ȃ��ꍇ
		m_pScene->Uninit();
		m_pScene = NULL;
	}

	for (int nCntPress = 0; nCntPress < PRESS_KEY; nCntPress++)
	{
		if (m_apPress[nCntPress] != NULL)
		{	// NULL����Ȃ��ꍇ
			m_apPress[nCntPress]->Uninit();
			m_apPress[nCntPress] = NULL;
		}
	}

	CScene::ReleaseMode();
}

//**************************************************************
//		�X�V����
//**************************************************************
void CTutorial::Update(void)
{
	int nCreate = 0;	// �����x�������邩�ǂ���
	CSound *pSound = CManager::GetSound();

	if (CFade::GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���Ă��Ȃ����
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) && m_nPress >= 3
			|| CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true && m_nPress >= 3)
		{// �L�[�{�[�h�iENTER�j����͂����� && �񐔂�3��Ȃ�
			CFade::Create(CManager::MODE_GAME, CFade::FADE_OUT);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
		}
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_D) && m_bPress == false
		|| CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_RIGHT, 0) == true && m_bPress == false
		|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true && m_bPress == false)
	{	// ENTER && false�Ȃ�
		if (m_nPress < 3)
		{
			m_nPress++;			// �񐔂̑���
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE002);
		}
		nCreate++;
		m_bPress = true;	// �����true��
		m_bmove = false;	// �����false��
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_A) && m_bPress == false
		|| CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_LEFT, 0) == true && m_bPress == false
		|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true && m_bPress == false)
	{
		if (m_nPress > 0)
		{
			m_nPress--;			// �񐔂̑���
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE002);
		}
		nCreate++;
		m_bPress = true;	// �����true��
		m_bmove = true;		// �����false��
	}

	if (m_nPress == 0 && nCreate == 1)
	{	// �ŏ��̉�ʂ̏ꍇ
		m_apPress[1]->SetType(CPress::TYPE_OPAQUE);
		m_apPress[0]->SetType(CPress::TYPE_MANUAL);
	}
	else if (m_nPress == 1 && nCreate == 1 || m_nPress == 2 && nCreate == 1)
	{	// �Q�Ԗڂ̉�ʂ̏ꍇ
		m_apPress[0]->SetType(CPress::TYPE_OPAQUE);
		m_apPress[3]->SetTex(3);
		m_apPress[5]->SetTex(4);
		m_apPress[1]->SetType(CPress::TYPE_OPAQUE);
	}
	else if (m_nPress == 3 && nCreate == 1)
	{	// �Ō�̉�ʂ̏ꍇ
		m_apPress[0]->SetType(CPress::TYPE_OPAQUE);
		m_apPress[3]->SetTex(7);
		m_apPress[5]->SetTex(8);
		m_apPress[1]->SetType(CPress::TYPE_MANUAL);
	}

	// texture��UV�ړ�
	if (m_fTexX < (0.25f * m_nPress) && m_nPress <= 3 && m_bmove == false)
	{	// UV�ړ��͈́@&& �񐔂�2��ȉ� && �i�ނȂ�
		m_fTexX += 0.01f;		// UV�����炷
	}
	else if (m_fTexX >(0.25f * m_nPress) && m_nPress <= 3 && m_bmove == true)
	{	// UV�ړ��͈́@&& �񐔂�2��ȉ� && ���ǂ�Ȃ�
		m_fTexX -= 0.01f;		// UV�����炷
	}
	else if (m_nPress <= 3)
	{	// 2��ȉ��Ȃ�
		m_bPress = false;				// �����false��
		m_fTexX = (0.25f * m_nPress);	// UV����
	}

	if (m_pScene != NULL)
	{
		m_pScene->SetTex(0, 4, D3DXVECTOR2(m_fTexX, 1.0f));
		m_pScene->Update();
	}

}

//**************************************************************
//		�`�揈��
//**************************************************************
void CTutorial::Draw(void)
{
	if (m_pScene != NULL)
	{
		m_pScene->Draw();
	}

	for (int nCntPress = 0; nCntPress < PRESS_KEY; nCntPress++)
	{
		if (m_apPress[nCntPress] != NULL)
		{
			m_apPress[nCntPress]->Draw();
		}
	}
}
//*****************************************************************************
//
//				�|�[�Y�̏���[pause.cpp]
//				Auther : Shun Yokomichi
//
//*****************************************************************************

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"		// ����
#include "manager.h"	// �}�l�[�W���[
#include "renderer.h"	// �����_���[
#include "scene2D.h"	// �V�[��2D
#include "pause.h"		// �|�[�Y
#include "fade.h"		// �t�F�[�h
#include "pausebg.h"	// �|�[�Y�w�i
#include "press.h"		// �v���X�{�^��
#include "sound.h"		// �T�E���h

//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define TEXTURE_NAME000	"data/Texture/pause/continue.png"	// �ǂݍ��ރe�N�X�`��000
#define TEXTURE_NAME001	"data/Texture/pause/retry.png"		// �ǂݍ��ރe�N�X�`��001
#define TEXTURE_NAME002	"data/Texture/pause/Quit.png"		// �ǂݍ��ރe�N�X�`��002
#define COL_A			(0.009f)							// �����x�̕ω���
#define COL_A_MAX		(0.65f)								// �����x�̌��x��
#define POS_X_INTERVAL	(150.0f)							// X���W�̊Ԋu
#define PRESS_BUTTON_X	(50.0f)								// �{�^���̃T�C�Y(X��)
#define PRESS_BUTTON_Y	(50.0f)								// �{�^���̃T�C�Y(Y��)
#define PRESS_INTERVAL	(200.0f)							// ���j���[�Ƃ̋���

//*****************************************************************************
//				�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPause::m_pTexture[POLYGON_PAUSE] = {};
bool CPause::m_bPause = false;

//*****************************************************************************
//				��������
//*****************************************************************************
CPause *CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 UV)
{
	CPause *pPause = NULL;

	// �V�[���̐���
	if (pPause == NULL)
	{
		pPause = new CPause;

		if (pPause != NULL)
		{
			pPause->Init(pos, size, col, UV);
		}
	}
	return pPause;
}
//*****************************************************************************
//				���[�h
//*****************************************************************************
HRESULT CPause::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCntTex = 0; nCntTex < POLYGON_PAUSE; nCntTex++)
	{
		if (m_pTexture[nCntTex] == NULL)
		{	// NULL�Ȃ�
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME000, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME001, &m_pTexture[1]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME002, &m_pTexture[2]);
		}
	}
	return S_OK;
}
//*****************************************************************************
//				�A�����[�h
//*****************************************************************************
void CPause::Unload(void)
{
	for (int nCntTex = 0; nCntTex < POLYGON_PAUSE; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}
//*****************************************************************************
//				�R���X�g���N�^
//*****************************************************************************
CPause::CPause()
{
	for (int nCntPause = 0; nCntPause < POLYGON_PAUSE; nCntPause++)
	{
		m_apScene2D[nCntPause] = NULL;
	}
	m_pPauseBg = NULL;

	for (int nCntPause = 0; nCntPause < POLYGON_PAUSE; nCntPause++)
	{
		m_pPress[nCntPause] = NULL;
	}
}
//*****************************************************************************
//				�f�X�g���N�^
//*****************************************************************************
CPause::~CPause()
{
}

//*****************************************************************************
//				����������
//*****************************************************************************
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 UV)
{
	Load();		// �ǂݍ���
	CPress::Load();

	if (m_pPauseBg == NULL)
	{	// NULL�Ȃ�
		m_pPauseBg = new CPauseBg;
	}
	if (m_pPauseBg != NULL)
	{	// NULL����Ȃ��Ȃ�
		m_pPauseBg->Init();
	}

	for (int nCntPause = 0; nCntPause < POLYGON_PAUSE; nCntPause++)
	{
		m_apScene2D[nCntPause] = new CScene2D(CScene::PRIORITY_PAUSE, CScene::OBJTYPE_MENU);
		if (m_apScene2D[nCntPause] != NULL)
		{	// NULL����Ȃ��Ȃ�
			m_apScene2D[nCntPause]->SetInitAll(D3DXVECTOR3(pos.x, pos.y + (nCntPause * POS_X_INTERVAL), pos.x), size, col, UV);
			m_apScene2D[nCntPause]->Init();
			m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);
		}
	}

	for (int nCntPause = 0; nCntPause < POLYGON_PRESS; nCntPause++)
	{
		if (m_pPress[nCntPause] == NULL)
		{	// NULL�Ȃ�
			m_pPress[nCntPause] = new CPress;
		}
		if (m_pPress[nCntPause] != NULL)
		{	// NULL����Ȃ��Ȃ�
			if (nCntPause == 0)
			{
				m_pPress[nCntPause]->Init(D3DXVECTOR3(pos.x - PRESS_INTERVAL, pos.y, pos.z), D3DXVECTOR3(PRESS_BUTTON_X, PRESS_BUTTON_Y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, D3DX_PI * -0.5f);
			}
			if (nCntPause == 1)
			{
				m_pPress[nCntPause]->Init(D3DXVECTOR3(580.0f, 60.0f, pos.z), D3DXVECTOR3(PRESS_BUTTON_X - 20.0f, PRESS_BUTTON_Y - 20.0f , 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, D3DX_PI * -0.5f);
			}
			if (nCntPause == 2)
			{
				m_pPress[nCntPause]->Init(D3DXVECTOR3(580.0f, 580.0f, pos.z), D3DXVECTOR3(PRESS_BUTTON_X - 20.0f, PRESS_BUTTON_Y - 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, D3DX_PI * 0.5f);
			}
			if (nCntPause == 3)
			{
				m_pPress[nCntPause]->Init(D3DXVECTOR3(660.0f, 60.0f, pos.z), D3DXVECTOR3(PRESS_BUTTON_X - 20.0f, PRESS_BUTTON_Y - 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, D3DX_PI);
			}
			if (nCntPause == 4)
			{
				m_pPress[nCntPause]->Init(D3DXVECTOR3(660.0f, 580.0f, pos.z), D3DXVECTOR3(PRESS_BUTTON_X - 20.0f, PRESS_BUTTON_Y - 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, D3DX_PI);
			}

			m_pPress[nCntPause]->SetType(CPress::TYPE_NONE);
		}
	}

	//�@������
	m_nNum = 0;
	m_fColA = 1.0f;
	m_bPause = false;

	return S_OK;
}

//*****************************************************************************
//				�I������
//*****************************************************************************
void CPause::Uninit()
{
	Unload();	// texture�̔j��
	CPause::Unload();	// texture�̔j��

	for (int nCntPoylgon = 0; nCntPoylgon < POLYGON_PAUSE; nCntPoylgon++)
	{
		if (m_apScene2D[nCntPoylgon] != NULL)
		{	//CScene2D�̏I��
			m_apScene2D[nCntPoylgon]->Uninit();
			m_apScene2D[nCntPoylgon] = NULL;
		}
	}

	if (m_pPauseBg != NULL)
	{	// CPressBg�̏I����
		m_pPauseBg->Uninit();
		m_pPauseBg = NULL;
	}

	for (int nCntPoylgon = 0; nCntPoylgon < POLYGON_PRESS; nCntPoylgon++)
	{
		if (m_pPress[nCntPoylgon] != NULL)
		{	// CPress�̏I����
			m_pPress[nCntPoylgon]->Uninit();
			m_pPress[nCntPoylgon] = NULL;
		}
	}
}

//*****************************************************************************
//				�X�V����
//*****************************************************************************
void CPause::Update()
{
	CSound *pSound = CManager::GetSound();

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) || CManager::GetInputKeyboard()->GetTrigger(DIK_UP)
		|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
	{	// W ���́@���L�[���������ꍇ
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE002);
		m_nNum = (m_nNum + 2) % POLYGON_PAUSE;
		m_fColA = 1.0f;
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) || CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN)
		|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
	{	// S ���́@���L�[���������ꍇ
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE002);
		m_nNum = (m_nNum + 1) % POLYGON_PAUSE;
		m_fColA = 1.0f;
	}

	D3DXVECTOR3 pos = m_apScene2D[0]->Getpos();		// ���j���[�̈�Ԗڂ̍��W����

	m_fColA -= COL_A;	// �����x�̕ω�

	if (m_fColA < COL_A_MAX)
	{	// ������x�̒l�ɒB�����ꍇ
		m_fColA = 1.0f;
	}

	for (int nCntPoylgon = 0; nCntPoylgon < POLYGON_PAUSE; nCntPoylgon++)
	{
		if (m_apScene2D[nCntPoylgon] != NULL)
		{
			if (m_nNum == nCntPoylgon)
			{	// �ԍ��Ɠ��������̏ꍇ
				m_apScene2D[nCntPoylgon]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColA));
			}
			else
			{	// ����ȊO�̏ꍇ
				m_apScene2D[nCntPoylgon]->Setcol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
	{
		if (m_nNum == 0)
		{	// �|�[�Y����
			SetPause(false);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE003);
		}
		else if (m_nNum == 1)
		{	// �Q�[����ʂ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CFade::Create(CManager::MODE_GAME, CFade::FADE_OUT);
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
				SetPause(false);
			}
		}
		else if (m_nNum == 2)
		{	//�@�^�C�g����ʂ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT);
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
				SetPause(false);
			}
		}
	}
	if (m_pPress[0] != NULL)
	{

		m_pPress[0]->Setpos(D3DXVECTOR3(pos.x - PRESS_INTERVAL, pos.y + (m_nNum * POS_X_INTERVAL), pos.z));	// �ʒu�X�V
		m_pPress[0]->Setrot(D3DX_PI * 0.5f);		// �����̐ݒ�
		m_pPress[0]->Update();						// �X�V

	}

}

//*****************************************************************************
//				�`�揈��
//*****************************************************************************
void CPause::Draw()
{
	for (int nCntPause = 0; nCntPause < POLYGON_PAUSE; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Draw();
		}
	}
}

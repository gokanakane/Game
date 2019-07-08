//=============================================================================
//
// �L�����I�����[�h���� [CharacterSelect.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "fade.h"
#include "CharactorSelect.h"
#include "Input.h"
#include "bg.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�/�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CCharactorSelect::m_pTexture[MAX_TEXTURE_CHARACTORSELECT] = {};
CBg *CCharactorSelect::m_pBG = NULL;
CScene2D *CCharactorSelect::m_apScene2D[MAX_CHARACTORPOLYGON] = {};
CManager::StageSelectState CCharactorSelect::m_SelectStage = CManager::STAGESELECT_NONE;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharactorSelect::CCharactorSelect()
{
	nCntFade = 0;
	m_nSelectNum = 0;
	m_SelectState = CManager::CHARACTORSELECT_NONE;
	m_SelectCol = CHARACTORSELECTCOL_NONE;
	m_SelectStage = CManager::GetStageSelect();
	m_nCntAnim = 0;
	m_nPattarnAnim = 0;
	CSound::PlaySound(CSound::SOUND_LABEL_CHARACTORSELECT);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharactorSelect::~CCharactorSelect()
{
	CSound::StopSound(CSound::SOUND_LABEL_CHARACTORSELECT);
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CCharactorSelect::Init(void)
{
	CBg::Load();
	CCharactorSelect::Load();

	if (m_pBG == NULL)
	{
		m_pBG->Create();
	}

	for (int nCnt = 0; nCnt < MAX_CHARACTORPOLYGON; nCnt++)
	{
		if (nCnt == 0)
		{//�X�e�[�^�X
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, 310.0f, 0.0f), 400.0f, 200.0f);
			m_apScene2D[nCnt]->SetAnimY(1, 6,0);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_CHARACTORSELECT);
		}
		else if (nCnt == 1)
		{//�l�[���v���[�g
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(350.0f, 110.0f, 0.0f), 130.0f, 80.0f);
			m_apScene2D[nCnt]->SetAnimY(1,6, 0);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_CHARACTORSELECT);
		}
		else if(nCnt == 2)
		{//�T�u�^�C�g��
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(300.0f, 40.0f, 0.0f), 300.0f, 40.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_CHARACTORSELECT);
		}
		else if (nCnt >= 3 && nCnt <= 8)
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(300.0f + (130.0f*(nCnt - 3)), 580.0f, 0.0f), 100.0f, 100.0f);
			m_apScene2D[nCnt]->SetCharaAnim(1, 0.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_CHARACTORSELECT);
		}
		else
		{
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[9]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(300.0f + (130.0f*(nCnt - 6)), 580.0f, 0.0f), 50.0f, 80.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_CHARACTORSELECT);
		}
	}
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CCharactorSelect::Uninit(void)
{
	CBg::UnLoad();
	CCharactorSelect::UnLoad();

	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}
	//m_apScene2D��j���i�|���S�����j�����ꂽ������Ui���͔̂j������Ă��Ȃ��j
	for (int nCnt = 0; nCnt < MAX_CHARACTORPOLYGON; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
		}
	}

	CScene::ReleaseAllFade();
}
//=============================================================================
// �X�V����
//=============================================================================
void CCharactorSelect::Update(void)
{
	/* �L�[�{�[�h�̎擾 */
	CInputKeyBoard *pInput = NULL;
	CFade::FADEMODE g_fade = CFade::GetFade();
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}

	//�ړ�
	if (pInput->GetKeyboardTrigger(DIK_D) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
			m_nSelectNum = (m_nSelectNum + 1) % 6;

			if (m_nSelectNum == 0)
			{
				m_nSelectNum = 5;
			}
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
	}
	if (pInput->GetKeyboardTrigger(DIK_A) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_CURSOR);
			m_nSelectNum = (m_nSelectNum + 5) % 6;

			if (m_nSelectNum == 5)
			{
				m_nSelectNum = 0;
			}
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
	}

	if (pInput->GetKeyboardTrigger(DIK_L) == true)
	{
		if (g_fade != CFade::FADE_OUT)
		{
			//���[�h�ݒ�
			CFade::SetFade(CManager::MODE_STAGESELECT);
		}
	}
	//�I�����
	if (m_nSelectNum == 0)
	{//�h���O�[��
		m_SelectCol = CHARACTORSTATECOL_DORAGON;
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter����
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_SelectState = CManager::CHARACTORSTATE_DORAGON;
			}
		}
	}
	else if (m_nSelectNum == 1)
	{//�J�[�l���A��
		m_SelectCol = CHARACTORSTATECOL_KARNERIAN;
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter����
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_SelectState = CManager::CHARACTORSTATE_KARNERIAN;
			}
		}
	}
	else if (m_nSelectNum == 2)
	{//�r�r�A��
		m_SelectCol = CHARACTORSTATECOL_VIVIAN;
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter����
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_SelectState = CManager::CHARACTORSTATE_VIVIAN;
			}
		}
	}
	else if (m_nSelectNum == 3)
	{//�A���C�X�^
		m_SelectCol = CHARACTORSTATECOL_AREISTA;
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter����
			if (m_SelectStage != CManager::STAGESELECT_STAGE4)
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					CSound::PlaySound(CSound::SOUND_LABEL_SE_NOSELECT);
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
			else
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
					m_SelectState = CManager::CHARACTORSTATE_AREISTA;
				}
			}
		}
	}
	else if (m_nSelectNum == 4)
	{//�@��
		m_SelectCol = CHARACTORSTATECOL_RENGE;
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter����
			if (m_SelectStage != CManager::STAGESELECT_STAGE4)
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					CSound::PlaySound(CSound::SOUND_LABEL_SE_NOSELECT);
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
			else
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
					m_SelectState = CManager::CHARACTORSTATE_RENGE;
				}
			}
		}
	}
	else if (m_nSelectNum == 5)
	{//�����B�J���g
		m_SelectCol = CHARACTORSTATECOL_LILIY;
		if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
		{//Enter����
			if (m_SelectStage != CManager::STAGESELECT_STAGE4)
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					CSound::PlaySound(CSound::SOUND_LABEL_SE_NOSELECT);
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
			else
			{
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
					m_SelectState = CManager::CHARACTORSTATE_LILIY;
				}
			}
		}
	}

	if (m_SelectStage == CManager::STAGESELECT_STAGE4)
	{
		m_apScene2D[9]->SetAlpha(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_apScene2D[10]->SetAlpha(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_apScene2D[11]->SetAlpha(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}

	switch (m_SelectState)
	{//�I�����
	case CManager::CHARACTORSELECT_NONE:
		break;

	case CManager::CHARACTORSTATE_DORAGON:	//�h���O�[��
		nCntFade++;
		if (nCntFade > 30)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				CManager::SetCharactorSelect(CManager::CHARACTORSTATE_DORAGON);
				//���[�h�ݒ�
				CFade::SetFade(CManager::MODE_TUTORIAL);
			}
		}
		break;

	case CManager::CHARACTORSTATE_KARNERIAN:	//�J�[�l���A��
		nCntFade++;
		if (nCntFade > 30)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				CManager::SetCharactorSelect(CManager::CHARACTORSTATE_KARNERIAN);

				//���[�h�ݒ�
				CFade::SetFade(CManager::MODE_TUTORIAL);
			}
		}
		break;

	case CManager::CHARACTORSTATE_VIVIAN:		//�r�r�A��
		nCntFade++;
		if (nCntFade > 30)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				CManager::SetCharactorSelect(CManager::CHARACTORSTATE_VIVIAN);

				//���[�h�ݒ�
				CFade::SetFade(CManager::MODE_TUTORIAL);
			}
		}
		break;

	case CManager::CHARACTORSTATE_AREISTA:	//�A���C�X�^
		nCntFade++;
		if (nCntFade > 30)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				CManager::SetCharactorSelect(CManager::CHARACTORSTATE_AREISTA);

				//���[�h�ݒ�
				CFade::SetFade(CManager::MODE_TUTORIAL);
			}
		}
		break;

	case CManager::CHARACTORSTATE_RENGE:		//�@��
		nCntFade++;
		if (nCntFade > 30)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				CManager::SetCharactorSelect(CManager::CHARACTORSTATE_RENGE);

				//���[�h�ݒ�
				CFade::SetFade(CManager::MODE_TUTORIAL);
			}
		}
		break;

	case CManager::CHARACTORSTATE_LILIY:		//�����B�J���g
		nCntFade++;
		if (nCntFade > 30)
		{
			if (g_fade != CFade::FADE_OUT)
			{
				CManager::SetCharactorSelect(CManager::CHARACTORSTATE_LILIY);

				//���[�h�ݒ�
				CFade::SetFade(CManager::MODE_TUTORIAL);
			}
		}
		break;
	}

	switch (m_SelectCol)
	{//�F�ƃA�j���[�V����
	case CHARACTORSELECTCOL_NONE:
		break;

	case CHARACTORSTATECOL_DORAGON:		//�h���O�[��
		/* �X�e�[�^�X�n */
		m_apScene2D[0]->SetAnimY(1, 6, 0);
		m_apScene2D[1]->SetAnimY(1, 6, 0);

		/* �A�j���[�V���� */
		CharactorAnimation(3);

		/* ���I���̃L�����̐F */
		m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[4]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[5]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[6]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[7]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[8]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		break;

	case CHARACTORSTATECOL_KARNERIAN:	//�J�[�l���A��
		/* �X�e�[�^�X�n */
		m_apScene2D[0]->SetAnimY(1, 6, 1);
		m_apScene2D[1]->SetAnimY(1, 6, 1);

		/* �A�j���[�V���� */
		CharactorAnimation(4);

		/* ���I���̃L�����̐F */
		m_apScene2D[3]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[5]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[6]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[7]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[8]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		break;

	case CHARACTORSTATECOL_VIVIAN:		//�r�r�A��
		/* �X�e�[�^�X�n */
		m_apScene2D[0]->SetAnimY(1, 6, 2);
		m_apScene2D[1]->SetAnimY(1, 6, 2);

		/* �A�j���[�V���� */
		CharactorAnimation(5);

		/* ���I���̃L�����̐F */
		m_apScene2D[3]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[4]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[6]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[7]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[8]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		break;

	case CHARACTORSTATECOL_AREISTA:		//�A���C�X�^
		/* �X�e�[�^�X�n */
		m_apScene2D[0]->SetAnimY(1, 6, 3);
		m_apScene2D[1]->SetAnimY(1, 6, 3);

		/* �A�j���[�V���� */
		CharactorAnimation(6);

		/* ���I���̃L�����̐F */
		m_apScene2D[3]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[4]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[5]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[7]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[8]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		break;

	case CHARACTORSTATECOL_RENGE:		//�@��
		/* �X�e�[�^�X�n */
		m_apScene2D[0]->SetAnimY(1, 6, 4);
		m_apScene2D[1]->SetAnimY(1, 6, 4);

		/* �A�j���[�V���� */
		CharactorAnimation(7);

		/* ���I���̃L�����̐F */
		m_apScene2D[3]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[4]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[5]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[6]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[7]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apScene2D[8]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		break;

	case CHARACTORSTATECOL_LILIY:		//�����B�J���g
		/* �X�e�[�^�X�n */
		m_apScene2D[0]->SetAnimY(1, 6, 5);
		m_apScene2D[1]->SetAnimY(1, 6, 5);

		/* �A�j���[�V���� */
		CharactorAnimation(8);

		/* ���I���̃L�����̐F */
		m_apScene2D[3]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[4]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[5]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[6]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[7]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_apScene2D[8]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}

	CDirectXInput::ResetInputJoyState(CDirectXInput::GetInputJoyState());
}
//=============================================================================
// �`�揈��
//=============================================================================
void CCharactorSelect::Draw(void)
{

}
//=============================================================================
// �A�j���[�V����
//=============================================================================
void CCharactorSelect::CharactorAnimation(int nNum)
{
	m_nCntAnim++;
	if (m_nCntAnim % 8 == 0)
	{
		m_nPattarnAnim++;
		m_apScene2D[nNum]->SetCharaAnim(m_nPattarnAnim, 0.0f);
		if (m_nPattarnAnim >= 4)
		{
			m_nPattarnAnim = 0;
		}
	}
}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CCharactorSelect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	if (m_SelectStage == CManager::STAGESELECT_STAGE4)
	{
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTORSTATUS_PC6, &m_pTexture[0]);
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTORNAME_PC6, &m_pTexture[1]);
	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTORSTATUS_PC3, &m_pTexture[0]);
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTORNAME_PC3, &m_pTexture[1]);
	}
	D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTORSELECT_SUBTITLE, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYERICON_DRAGON, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYERICON_KARNERIAN, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYERICON_VIVIAN, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYERICON_AREISTA, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYERICON_RENGE, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PLAYERICON_LILIY, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTORMASK, &m_pTexture[9]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CCharactorSelect::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEXTURE_CHARACTORSELECT; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
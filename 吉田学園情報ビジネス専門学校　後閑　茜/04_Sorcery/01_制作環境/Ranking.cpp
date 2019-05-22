//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "Input.h"
#include "fade.h"
#include "ranking.h"
#include "bg.h"
#include "scoreBase.h"
#include "number.h"
#include "effectBase.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�/�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CRanking::m_pTexture[MAX_TEXTURE_RANKING] = {};
CBg *CRanking::m_pBG = NULL;
CScene2D *CRanking::m_apScene2D[MAX_POLYGON_RANKING] = {};
CScore *CRanking::m_pScore = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	CSound::PlaySound(CSound::SOUND_LABEL_RANKING);
	m_State = PRESSSTATE_NONE;
	m_col = DEFALT_COL_WHITE;
	m_fChangeAlpha = 0.05f;
	m_nCntFade = 0;
	m_nChangeMode = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{
	CSound::StopSound(CSound::SOUND_LABEL_RANKING);
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	CBg::Load();
	CRanking::Load();
	CNumber::Load();
	CEffect::Load();

	if (m_pBG == NULL)
	{
		m_pBG = new CBg;
		m_pBG->Create();
	}
	for (int nCnt = 0; nCnt < MAX_POLYGON_RANKING; nCnt++)
	{
		if (nCnt == 0)
		{//����
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(700.0f, 80.0f, 0.0f), 350.0f, 60.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_RANKING);
		}
		else if(nCnt == 1)
		{//����
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(300.0f, 400.0f, 0.0f), 100.0f, 250.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_RANKING);
		}
		else
		{//�L�����A�C�R��
			m_apScene2D[nCnt] = new CScene2D;
			m_apScene2D[nCnt]->Init();
			m_apScene2D[nCnt]->BindTexture(m_pTexture[2]);
			m_apScene2D[nCnt]->SetScene2D(D3DXVECTOR3(460.0f, 200.0f + (100.0f*(nCnt - 2)), 0.0f), 50.0f, 50.0f);
			m_apScene2D[nCnt]->SetObjtype(CScene::OBJTYPE_RANKING);
			m_apScene2D[nCnt]->SetAnimY(1, 6, 0);
		}
	}
	if(m_pScore == NULL)
	{
		m_pScore = CScore::Create(CScore::SCORETYPE_RANKING);
	}
	m_nChangeMode = 0;
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
	CBg::UnLoad();
	CRanking::UnLoad();
	CNumber::UnLoad();
	CEffect::UnLoad();
	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}
	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		m_pScore = NULL;
	}
	CScene::ReleaseAllFade();
}
//=============================================================================
// �X�V����
//=============================================================================
void CRanking::Update(void)
{
	/* �L�[�{�[�h�̎擾 */
	CInputKeyBoard *pInput = NULL;
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	CFade::FADEMODE g_fade = CFade::GetFade();
	m_fChangeAlpha++;

	if (pInput == NULL)
	{
		pInput = CManager::GetInput();
	}
	if (rand() % 20 == 0)
	{
		float nPos = float(rand() % SCREEN_WIDTH);

		CEffect::Create(D3DXVECTOR3(nPos, 0.0f, 0.0f), CEffect::EFFECTTYPE_FALL,DEFALT_COL_WHITE);
	}

	if (pInput->GetKeyboardPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{//Enter����
		if (g_fade != CFade::FADE_OUT)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			//���[�h�ݒ�
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}

	if (m_fChangeAlpha >= 600)
	{
		if (g_fade != CFade::FADE_OUT)
		{
			//���[�h�ݒ�
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}

	for (int nCnt = 2; nCnt < MAX_POLYGON_RANKING; nCnt++)
	{
		m_apScene2D[nCnt]->SetAnimY(1, 6, CManager::m_RankingCharactor[nCnt - 2] - 1);
	}

	CDirectXInput::ResetInputJoyState(CDirectXInput::GetInputJoyState());
}
//=============================================================================
// �`�揈��
//=============================================================================
void CRanking::Draw(void)
{

}
//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CRanking::Load(void)
{
	CManager::MODE mode = CManager::GetMode();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_SUBTITLE, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_RANK, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_CHARAICON, &m_pTexture[2]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̃A�����[�h
//=============================================================================
void CRanking::UnLoad(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEXTURE_RANKING; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
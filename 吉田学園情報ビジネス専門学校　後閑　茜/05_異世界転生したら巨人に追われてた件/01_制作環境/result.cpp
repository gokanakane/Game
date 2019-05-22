//**************************************************************
//
//				���U���g�̏���[result.cpp]
//				Auther : Shun Yokomichi
//
//**************************************************************
#include "scene2d.h"		// �V�[��2D
#include "result.h"			// ���U���g
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "fade.h"			// �t�F�[�h
#include "input.h"			// ����
#include "sound.h"			// �T�E���h
#include "scene.h"			// �V�[��
#include "press.h"			// �{�^��
//**************************************************************
//				�}�N����`
//**************************************************************
#define DEFAULT_COLOR_OPACITY_WHITE		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						//�s�����̔�
#define DEFAULT_COLOR_OPACITY_BLACK		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))						//�s�����̍�
#define DEFAULT_COLOR_HALFCLEAN_WHITE	(D3DXCOLOR(1.0f,1.0f,1.0f,0.5f))						//�������̔�
#define DEFAULT_COLOR_HALFCLEAN_BLACK	(D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))						//�������̍�
#define DEFAULT_COLOR_CLEAN_WHITE		(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))						//�����̔�
#define DEFAULT_COLOR_CLEAN_BLACK		(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))						//�����̍�
#define MENU_TEX						"data/TEXTURE/Pause/Menu.png"							// ���j���[
#define RESULT_FALLING_LOGO				"data/TEXTURE/result/Result1_Falling/Logo.png"			// ���S

//===============================
// ����ED
//===============================
#define RESULT_FALLING_BROCK			"data/TEXTURE/result/Result1_Falling/00_BG.png"			// ����ED�F��
#define RESULT_FALLING_PLAYER			"data/TEXTURE/result/Result1_Falling/Player.png"		// ����ED�F�v���C���[
#define RESULT_FALLING_SPEECH			"data/TEXTURE/result/Result1_Falling/00_speech.png"		// ����ED�F�䎌
#define RESULT_FALLING_LIGHT			"data/TEXTURE/result/Result1_Falling/01_Light.png"		// ����ED�F���C�g
#define RESULT_FALLING_SOUL				"data/TEXTURE/result/Result1_Falling/01_Soul.png"		// ����ED�F��
#define FALLING_POS_X_KEY				(275.0f)												// �L�[�{�[�h�̈ʒu
#define FALLING_POS_X_DIFFERENCE		(100.0f)												// �v���X�{�^���̈ʒu�̍���
#define FALLING_POS_X_JOIPAD			(FALLING_POS_X_KEY + FALLING_POS_X_DIFFERENCE)			// �R���g���[���[�̃{�^���ʒu
#define FALLING_POS_Y_DIFFERENCE		(140.0f)												// posY�̍���
#define	FALLING_POS_Y_NUM_DIF			(650.0f)												// �I���������̈ʒu����
//===============================
// �ߊlED
//===============================
#define RESULT_PREY_SKY					"data/TEXTURE/result/Result2_prey/Sky.png"				// �ߊlED�F��
#define RESULT_PREY_WOOD				"data/TEXTURE/result/Result2_prey/Wood.png"				// �ߊlED�F��
#define RESULT_PREY_CLOUD				"data/TEXTURE/result/Result2_prey/Cloud.png"			// �ߊlED�F�_
#define RESULT_PREY_GROUND				"data/TEXTURE/fieldmesh.png"							// �ߊlED�F�n��
#define RESULT_PREY_PLAYER				"data/TEXTURE/result/Result2_prey/Player.png"			// ����ED�F�v���C���[
#define RESULT_PREY_OPTION				"data/TEXTURE/result/Result2_prey/option.png"			// ����ED�F����
#define PREY_POS_X_KEY					(465.0f)												// �L�[�{�[�h�̈ʒu
#define PREY_POS_X_DIFFERENCE			(100.0f)												// �v���X�{�^���̈ʒu�̍���
#define PREY_POS_X_JOIPAD				(PREY_POS_X_KEY + PREY_POS_X_DIFFERENCE)				// �R���g���[���[�̃{�^���ʒu
#define PREY_POS_Y_DIFFERENCE			(250.0f)												// posY�̍���
#define	PREY_POS_Y_NUM_DIF				(500.0f)												// �I���������̈ʒu����
//===============================
// ����ED
//===============================
#define RESULT_ESCAPE_PLAYER			"data/TEXTURE/result/Result3_escape/Player.png"			// ����ED�F�v���C���[
#define RESULT_ESCAPE_ENEMY				"data/TEXTURE/result/Result3_escape/Enemy.png"			// ����ED�F���l
#define RESULT_ESCAPE_BG				"data/TEXTURE/result/Result3_escape/Bg.png"				// ����ED�F�w�i
#define RESULT_ESCAPE_SKY				"data/TEXTURE/result/Result3_escape/Sky.png"				// ����ED�F�w�i

//**************************************************************
//				�ÓI�����o�ϐ�
//**************************************************************
CResult *CResult::m_pResult = NULL;
int CResult::m_nCntfade = 0;
LPDIRECT3DTEXTURE9 CFallingEnd::m_pTexture[MAX_FALLINGMODE_TEXTURE] = {};
LPDIRECT3DTEXTURE9 CPreyEnd::m_pTexture[MAX_PREYMODE_TEXTURE] = {};
LPDIRECT3DTEXTURE9 CEscapeEnd::m_pTexture[MAX_ESCAPEMODE_TEXTURE] = {};

//**************************************************************
//		�R���X�g���N�^
//**************************************************************
CResult::CResult()
{
	// �f�t�H���g�l
	m_nCntfade = 0;
}

//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CResult::~CResult()
{

}
//**************************************************************
//				�ǂݍ��ރe�N�X�`��
//**************************************************************
HRESULT CResult::Load(void)
{
	return S_OK;
}

//**************************************************************
//				�J������e�N�X�`��
//**************************************************************
void CResult::Unload(void)
{

}

CResult *CResult::Create(CGame::MODEGAME gameMode)
{
	switch (gameMode)
	{
	case CGame::MODE_GAMECLEAR:		// �N���A���
		if (m_pResult == NULL)
		{
			m_pResult = new CEscapeEnd;
		}
		break;

	case CGame::MODE_GAMEOVER000:	// ���l�ɕ߂܂������
		if (m_pResult == NULL)
		{
			m_pResult = new CPreyEnd;
		}
		break;

	case CGame::MODE_GAMEOVER001:	//�̗͂�0�ɂȂ������
		if (m_pResult == NULL)
		{
			m_pResult = new CFallingEnd;
		}
		break;
	}


	return m_pResult;
}

//**************************************************************
//		����������
//**************************************************************
HRESULT CResult::Init(void)
{
	return S_OK;
}

//**************************************************************
//		�I������
//**************************************************************
void CResult::Uninit(void)
{
	if (m_pResult != NULL)
	{
		m_pResult = NULL;
	}

	CScene::ReleaseMode();	// ���[�h�I��
}

//**************************************************************
//		�X�V����
//**************************************************************
void CResult::Update(void)
{

}

//**************************************************************
//		�`�揈��
//**************************************************************
void CResult::Draw(void)
{

}
//**************************************************************
//		�t�F�[�h�̃J�E���g�_�E��
//**************************************************************
void CResult::CntDownFadeTime(void)
{
	m_nCntfade++;

	if (m_nCntfade >= MAX_FADERESTRICTION)
	{//8�`10�b�o�����烉���L���O�֑J��
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			CFade::Create(CManager::MODE_RANKING, CFade::FADE_OUT);
		}
	}
}

//=============================================================================
// ��CFallingEnd :(����ED)
//=============================================================================
//**************************************************************
//		�R���X�g���N�^
//**************************************************************
CFallingEnd::CFallingEnd()
{
	m_FallingMode = FALLINGMODE_MOVENOSTART;
	m_MenuState = MENUSTATE_NONE;
	m_MenuCol = MENUSTATECOLOR_NONE;

	for (int nCnt = 0; nCnt < MAX_FALLINGMODE_POLYGON; nCnt++)
	{
		m_pScene[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_PRESS_BUTTON; nCnt++)
	{
		m_apPress[nCnt] = NULL;
	}

	m_Scalvalue = 0.0f;
	m_fChengeMove = -0.01f;
	m_fCntMove = 0.0f;
	m_bSkipProduction = false;
	m_nSelectNum = 0;
}
//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CFallingEnd::~CFallingEnd()
{

}
//**************************************************************
//				�ǂݍ��ރe�N�X�`��
//**************************************************************
HRESULT CFallingEnd::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, MENU_TEX, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_BROCK, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_PLAYER, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_SPEECH, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_LIGHT, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_SOUL, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_LOGO, &m_pTexture[6]);

	return S_OK;
}

//**************************************************************
//				�J������e�N�X�`��
//**************************************************************
void CFallingEnd::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_FALLINGMODE_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//**************************************************************
//		����������
//**************************************************************
HRESULT CFallingEnd::Init()
{
	CPress::Load();
	for (int nCnt = 0; nCnt < MAX_FALLINGMODE_POLYGON; nCnt++)
	{
		if (m_pScene[nCnt] == NULL)
		{
			if (nCnt == SCENETYPE_MASK)
			{//���w�i
				m_pScene[nCnt] = new CScene2D(CScene::CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), DEFAULT_COLOR_OPACITY_BLACK, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
			}
			else if (nCnt == SCENETYPE_BLOCK)
			{//��
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), DEFAULT_COLOR_OPACITY_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_PLAYER)
			{//�v���C���[
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_1, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(800.0f, 800.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(0.5f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_SPEECH)
			{//�f����
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_2, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(500.0f, 250.0f, 0.0f),
					D3DXVECTOR3(50.0f, 100.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->Setrot(0.8f);
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_LIGHT)
			{//�Ɩ�
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, 320.0f, 0.0f),
					D3DXVECTOR3(350.0f, 320.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_SOUL)
			{//��
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_2, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f),
					D3DXVECTOR3(50.0f, 100.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(0.5f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_LOGO)
			{//���S
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_3, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f),
					D3DXVECTOR3(500.0f, 80.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 0.5f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_MENU_RETRY)
			{//���j���[(���g���C�j
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_4, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(300.0f, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(150.0f, 100.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 1.0f / 3));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->SetTex(1, 1, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->BindTexture(m_pTexture[0]);
			}
			else if (nCnt == SCENETYPE_MENU_QUIT)
			{//���j���[�i�N�C�b�g�j
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_4, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(950.0f, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(150.0f, 100.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 1.0f / 3));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->SetTex(1, 2, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->BindTexture(m_pTexture[0]);
			}

		}
	}

	for (int nCnt = 0; nCnt < MAX_PRESS_BUTTON; nCnt++)
	{
		if (m_apPress[nCnt] == NULL)
		{
			m_apPress[nCnt] = new CPress;

			if (nCnt == 0)
			{	// �L�[�{�[�h�p�̃{�^��
				m_apPress[nCnt]->Init(D3DXVECTOR3(FALLING_POS_X_KEY, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(70.0f, 50.0f, 0.0f),
					D3DXCOLOR(DEFAULT_COLOR_CLEAN_WHITE), 9, 0.0f);
				m_apPress[nCnt]->SetType(CPress::TYPE_MANUAL);
			}
			else
			{	// �R���g���[���[�p�̃{�^��
				m_apPress[nCnt]->Init(D3DXVECTOR3(FALLING_POS_X_JOIPAD, SCREEN_HEIGHT / 2 + FALLING_POS_Y_DIFFERENCE, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f),
					D3DXCOLOR(DEFAULT_COLOR_CLEAN_WHITE), 8, 0.0f);
				m_apPress[nCnt]->SetType(CPress::TYPE_MANUAL);
			}
		}
	}

	return S_OK;
}
//**************************************************************
//		�I������
//**************************************************************
void CFallingEnd::Uninit(void)
{
	CPress::Unload();

	for (int nCnt = 0; nCnt < MAX_FALLINGMODE_POLYGON; nCnt++)
	{
		if (m_pScene[nCnt] != NULL)
		{	// NULL����Ȃ��ꍇ
			m_pScene[nCnt]->Uninit();
			m_pScene[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_PRESS_BUTTON; nCnt++)
	{
		if (m_apPress[nCnt] != NULL)
		{	// NULL����Ȃ��ꍇ
			m_apPress[nCnt]->Uninit();
			m_apPress[nCnt] = NULL;
		}
	}

	CResult::Uninit();
}
//**************************************************************
//		�X�V����
//**************************************************************
void CFallingEnd::Update(void)
{
	CSound *pSound = CManager::GetSound();

	switch (m_FallingMode)
	{
	case FALLINGMODE_NONE:			//�����Ȃ����
		MoveScene(SCENETYPE_SOUL);
		CntDownFadeTime();
		break;

	case FALLINGMODE_MOVENOSTART:	//�A�j���[�V�������J�n���
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			if (m_pScene[SCENETYPE_PLAYER] != NULL)
			{
				m_pScene[SCENETYPE_PLAYER]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
			}
			if (m_pScene[SCENETYPE_SPEECH] != NULL)
			{
				m_pScene[SCENETYPE_SPEECH]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
			}
			m_FallingMode = FALLINGMODE_PLAYERFALL;
		}
		break;

	case FALLINGMODE_PLAYERFALL:	//�v���C���[�������Ă������
		if (m_pScene[SCENETYPE_PLAYER] != NULL)
		{/* �v���C���[�̓����Ɗ�̓����x�̏��� */

			D3DXVECTOR3 PlayerSize = m_pScene[SCENETYPE_PLAYER]->Getsize();	// �v���C���[�̌��݂̃T�C�Y���擾

			if (PlayerSize.x <= 1.0f&&PlayerSize.y <= 1.0f)
			{//�T�C�Y���������Ȃ肫���������t�F�[�h�A�E�g���Ď��̉�ʂ֍s������������
				m_pScene[SCENETYPE_PLAYER]->Setcol(DEFAULT_COLOR_CLEAN_WHITE);			//�v���C���[��s�����ɂ���
				if (m_pScene[SCENETYPE_SPEECH] != NULL)
				{/* �f�����̏��� */
					m_pScene[SCENETYPE_SPEECH]->Setcol(DEFAULT_COLOR_CLEAN_WHITE);
				}
				if (m_pScene[SCENETYPE_BLOCK] != NULL)
				{
					float fFadeColor = 0.08f;
					D3DXCOLOR col = m_pScene[SCENETYPE_BLOCK]->Getcol();
					if (col.a <= 0.0f)
					{//��̓����x��0�ȉ��ɂȂ�A�f�����̓����x��0�ɂȂ����玟�̃v���C���[������ł��ʂ�
						m_FallingMode = FALLINGMODE_DEATH;
					}
					else
					{//��̓����x��0�ȏゾ������0�ɂ��Ă���
						col.a -= fFadeColor;
						m_pScene[SCENETYPE_BLOCK]->Setcol(col);
					}
				}
			}
			else
			{//�������Ȃ��ĂȂ������珬�������Ă���
				if (PlayerSize.x == 800.0f && PlayerSize.y == 800.0f)
				{
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE039);
				}

				if (m_pScene[SCENETYPE_SPEECH] != NULL)
				{/* �f�����̏��� */

					D3DXCOLOR SpeechCol = m_pScene[SCENETYPE_SPEECH]->Getcol();
					D3DXVECTOR3 SpeechPos = m_pScene[SCENETYPE_SPEECH]->Getpos();
					SpeechPos.x -= 0.5f;
					SpeechPos.y -= 0.5f;

					SpeechCol.a -= 0.01f;
					m_pScene[SCENETYPE_SPEECH]->Setcol(SpeechCol);
					m_pScene[SCENETYPE_SPEECH]->Setpos(SpeechPos);
				}

				/* �v���C���[�̏k������ */
				m_Scalvalue += 0.3f;
				float fPlayerFadeColor = 0.005f;
				D3DXCOLOR col = m_pScene[SCENETYPE_PLAYER]->Getcol();

				D3DXVECTOR3 Scal = D3DXVECTOR3(PlayerSize.x - m_Scalvalue, PlayerSize.y - m_Scalvalue, 0.0f);

				col.a -= fPlayerFadeColor;
				m_pScene[SCENETYPE_PLAYER]->Setsize(D3DXVECTOR3(Scal.x, Scal.y, 0.0f));
				m_pScene[SCENETYPE_PLAYER]->Setcol(col);
			}
		}
		break;

	case FALLINGMODE_DEATH:			//�v���C���[�����񂾏��
		if (m_pScene[SCENETYPE_PLAYER] != NULL)
		{/* �v���C���[�̏��� */
			m_pScene[SCENETYPE_PLAYER]->Setsize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));	//�T�C�Y�����Ɏg���T�C�Y�ɂ���
			m_pScene[SCENETYPE_PLAYER]->SetTex(1, 1, D3DXVECTOR2(0.5f, 1.0f));		//�|�ꂽ�v���C���[�̃R�}�ɕύX
			m_pScene[SCENETYPE_PLAYER]->Setpos(D3DXVECTOR3(630.0f, 450.0f, 0.0f));	//�|�ꂽ�v���C���[�̈ʒu�ɕύX

			D3DXCOLOR col = m_pScene[SCENETYPE_PLAYER]->Getcol();
			float fLightFadeColor = 0.01f;
			col.a += fLightFadeColor;
			if (col.a >= 1.0f)
			{//
				m_pScene[SCENETYPE_PLAYER]->Setcol(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
				m_FallingMode = FALLINGMODE_LIGHTON;
			}
			else
			{
				m_pScene[SCENETYPE_PLAYER]->Setcol(D3DXCOLOR(0.3f, 0.3f, 0.3f, col.a));
			}
		}
		break;
	case FALLINGMODE_LIGHTON:
		if (m_pScene[SCENETYPE_LIGHT] != NULL)
		{//���C�g�̓����x���グ��
			m_pScene[SCENETYPE_LIGHT]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);

			if (m_pScene[SCENETYPE_PLAYER] != NULL)
			{//�v���C���[�̐F��߂�
				m_pScene[SCENETYPE_PLAYER]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
				if (m_pScene[SCENETYPE_SOUL] != NULL)
				{
					m_pScene[SCENETYPE_SOUL]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
					if (m_pScene[SCENETYPE_LOGO] != NULL)
					{
						m_pScene[SCENETYPE_LOGO]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
						m_FallingMode = FALLINGMODE_NONE;

						//BGM�F�Q�[���I�[�o�[
						pSound->PlaySoundA(CSound::SOUND_LABEL_BGM004);

						//SE �F�`�[��
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE019);

						m_MenuState = MENUSTATE_RETRY;
					}
				}
			}
		}
		break;
	}

	/* ���j���[�̏��� */
	if (m_MenuState != MENUSTATE_NONE)
	{//NONE����Ȃ��Ƃ���������\�ɂ���
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_A) == true || CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true)
		{
			m_nSelectNum = (m_nSelectNum + 1) % 2;
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE002);
		}

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_D) == true || CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
		{
			m_nSelectNum = (m_nSelectNum + 1) % 2;
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE002);
		}

		for (int nCnt = 0; nCnt < MAX_PRESS_BUTTON; nCnt++)
		{
			if (m_apPress[nCnt] != NULL)
			{
				m_apPress[nCnt]->Setpos(D3DXVECTOR3((FALLING_POS_X_KEY + (nCnt * FALLING_POS_X_DIFFERENCE)) + (m_nSelectNum * FALLING_POS_Y_NUM_DIF), SCREEN_HEIGHT / 2 + FALLING_POS_Y_DIFFERENCE, 0.0f));
				m_apPress[nCnt]->SetType(CPress::TYPE_NONE);
			}
		}

		/* ���j���[���I�΂�Ă��鎞�̏��� */
		if (m_nSelectNum == 0)
		{//���g���C
			m_MenuState = MENUSTATE_RETRY;
		}
		else if (m_nSelectNum == 1)
		{//�N�C�b�g
			m_MenuState = MENUSTATE_QUIT;
		}
	}
	switch (m_MenuState)
	{//�I�΂�Ă郂�[�h�ʂ̏���
	case MENUSTATE_NONE:
		break;

	case MENUSTATE_RETRY:
		m_MenuCol = MENUSTATECOLOR_RETRY;
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
				CFade::Create(CManager::MODE_GAME, CFade::FADE_OUT);
				m_MenuState = MENUSTATE_NONE;
				pSound->StopSound(CSound::SOUND_LABEL_BGM004);
			}
		}
		break;

	case MENUSTATE_QUIT:
		m_MenuCol = MENUSTATECOLOR_QUIT;
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT);
				m_MenuState = MENUSTATE_NONE;
				pSound->StopSound(CSound::SOUND_LABEL_BGM004);
			}
		}
		break;
	}
	switch (m_MenuCol)
	{//�I�΂�Ă郂�[�h�̐F�ƈʒu
	case MENUSTATECOLOR_NONE:
		break;

	case MENUSTATECOLOR_RETRY:
		if (m_pScene[SCENETYPE_MENU_RETRY] != NULL)
		{
			m_pScene[SCENETYPE_MENU_RETRY]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
		}
		if (m_pScene[SCENETYPE_MENU_QUIT] != NULL)
		{
			m_pScene[SCENETYPE_MENU_QUIT]->Setcol(DEFAULT_COLOR_HALFCLEAN_WHITE);
		}
		break;

	case MENUSTATECOLOR_QUIT:
		if (m_pScene[SCENETYPE_MENU_RETRY] != NULL)
		{
			m_pScene[SCENETYPE_MENU_RETRY]->Setcol(DEFAULT_COLOR_HALFCLEAN_WHITE);
		}
		if (m_pScene[SCENETYPE_MENU_QUIT] != NULL)
		{
			m_pScene[SCENETYPE_MENU_QUIT]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
		}
		break;
	}

	/* ���o�X�L�b�v�̏��� */
	if (m_bSkipProduction == false)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				SkipProduction();
				m_bSkipProduction = true;
			}
		}
	}
}
//**************************************************************
//		�`�揈��
//**************************************************************
void CFallingEnd::Draw(void)
{

}
//**************************************************************
//		�㉺�ړ�����
//**************************************************************
void CFallingEnd::MoveScene(SceneType type)
{
	if (m_pScene[type] != NULL)
	{/* ���̏��� */
		D3DXVECTOR3 pos = m_pScene[type]->Getpos();

		if (m_fCntMove >= 1 || m_fCntMove <= -1)
		{
			m_fChengeMove *= -1.0f;//�܂�Ԃ�
		}
		m_fCntMove += m_fChengeMove;
		pos.y += m_fCntMove;

		m_pScene[type]->Setpos(pos);
	}
}
//**************************************************************
//		���o��΂������̏���
//**************************************************************
void CFallingEnd::SkipProduction(void)
{
	CSound *pSound = CManager::GetSound();

	if (m_pScene[SCENETYPE_BLOCK] != NULL)
	{//��̓����x��0�ɂ���
		m_pScene[SCENETYPE_BLOCK]->Setcol(DEFAULT_COLOR_CLEAN_WHITE);
	}
	if (m_pScene[SCENETYPE_PLAYER] != NULL)
	{//�v���C���[�̏���ύX
		m_pScene[SCENETYPE_PLAYER]->Setsize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
		m_pScene[SCENETYPE_PLAYER]->SetTex(1, 1, D3DXVECTOR2(0.5f, 1.0f));
		m_pScene[SCENETYPE_PLAYER]->Setpos(D3DXVECTOR3(630.0f, 450.0f, 0.0f));
		m_pScene[SCENETYPE_PLAYER]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	if (m_pScene[SCENETYPE_SPEECH] != NULL)
	{/* �f�����̏��� */
		m_pScene[SCENETYPE_SPEECH]->Setcol(DEFAULT_COLOR_CLEAN_WHITE);
	}
	if (m_pScene[SCENETYPE_LIGHT] != NULL)
	{//���C�g�̓����x���グ��
		m_pScene[SCENETYPE_LIGHT]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	if (m_pScene[SCENETYPE_SOUL] != NULL)
	{//�����o��
		m_pScene[SCENETYPE_SOUL]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	if (m_pScene[SCENETYPE_LOGO] != NULL)
	{//���S���o��
		m_pScene[SCENETYPE_LOGO]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	//BGM�F�Q�[���I�[�o�[
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM004);
	//SE �F�`�[��
	pSound->PlaySoundA(CSound::SOUND_LABEL_SE019);

	m_FallingMode = FALLINGMODE_NONE;
	m_MenuState = MENUSTATE_RETRY;
}

//=============================================================================
// ��CPreyEnd :(����ED)
//=============================================================================
//**************************************************************
//		�R���X�g���N�^
//**************************************************************
CPreyEnd::CPreyEnd()
{
	m_PreyEndMode = PREYMODE_MOVENOSTART;
	m_MenuState = MENUSTATE_NONE;
	m_MenuCol = MENUSTATECOLOR_NONE;

	for (int nCnt = 0; nCnt < MAX_PREYMODE_POLYGON; nCnt++)
	{
		m_pScene[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_PRESS_BUTTON; nCnt++)
	{
		m_apPress[nCnt] = NULL;
	}

	m_fCntPlayerMove = 0.0f;
	m_fChangePlayerMove = 0.05f;
	nCntframe = 0;
	m_fChengeMove = 0.01f;
	m_fCntMove = 0.0f;
	m_bSkipProduction = false;
	m_nSelectNum = 0;
	m_fCntWoodMove = 0.0f;
	m_fChangeWoodMove = 0.3f;
	m_fOptionCol = 0.3f;
	m_fCloudScroll = 0.0f;
}
//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CPreyEnd::~CPreyEnd()
{

}
//**************************************************************
//				�ǂݍ��ރe�N�X�`��
//**************************************************************
HRESULT CPreyEnd::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, MENU_TEX, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_PREY_SKY, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_PREY_WOOD, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, RESULT_PREY_CLOUD, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, RESULT_PREY_GROUND, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, RESULT_PREY_PLAYER, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, RESULT_PREY_OPTION, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_SOUL, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_LOGO, &m_pTexture[8]);

	return S_OK;
}

//**************************************************************
//				�J������e�N�X�`��
//**************************************************************
void CPreyEnd::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_PREYMODE_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//**************************************************************
//		����������
//**************************************************************
HRESULT CPreyEnd::Init()
{
	CPress::Load();
	for (int nCnt = 0; nCnt < MAX_PREYMODE_POLYGON; nCnt++)
	{
		if (m_pScene[nCnt] == NULL)
		{
			if (nCnt == SCENETYPE_SKY)
			{//��
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), DEFAULT_COLOR_OPACITY_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt + 1]);
			}
			else if (nCnt == SCENETYPE_WOOD)
			{//�X
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), D3DXVECTOR2(2.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->SetTex(1, 1, D3DXVECTOR2(2.0f, 1.0f));
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt + 1]);
			}
			else if (nCnt == SCENETYPE_CLOUD)
			{//�_
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, 320.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, 320.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt + 1]);
			}
			else if (nCnt == SCENETYPE_GROUND)
			{//�n��
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, 660.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, 60.0f, 0.0f), DEFAULT_COLOR_OPACITY_WHITE, D3DXVECTOR2(10.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt + 1]);
			}
			else if (nCnt == SCENETYPE_PLAYER)
			{//�v���C���[
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_1, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2 + 5.0f, SCREEN_HEIGHT / 2 + 5.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(0.5f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt + 1]);
			}
			else if (nCnt == SCENETYPE_OPTION)
			{//�����L��
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_2, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(1200.0f, 200.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt + 1]);
			}
			else if (nCnt == SCENETYPE_SOUL)
			{//��
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_2, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(1100.0f, 100.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(0.5f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->SetTex(1, 1, D3DXVECTOR2(0.5f, 1.0f));
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt + 1]);
			}
			else if (nCnt == SCENETYPE_LOGO)
			{//���S
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_3, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(500.0f, 100.0f, 0.0f),
					D3DXVECTOR3(480.0f, 80.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 0.5f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt + 1]);
			}
			else if (nCnt == SCENETYPE_MENU_RETRY)
			{//���j���[(���g���C�j
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_4, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(500.0f, 500.0f, 0.0f),
					D3DXVECTOR3(150.0f, 100.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 1.0f / 3));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->SetTex(1, 1, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->BindTexture(m_pTexture[0]);
			}
			else if (nCnt == SCENETYPE_MENU_QUIT)
			{//���j���[�i�N�C�b�g�j
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_4, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(1000.0f, 500.0f, 0.0f),
					D3DXVECTOR3(150.0f, 100.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 1.0f / 3));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->SetTex(1, 2, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->BindTexture(m_pTexture[0]);
			}
		}
	}

	for (int nCnt = 0; nCnt < MAX_PRESS_BUTTON; nCnt++)
	{
		if (m_apPress[nCnt] == NULL)
		{
			m_apPress[nCnt] = new CPress;

			if (nCnt == 0)
			{	// �L�[�{�[�h�p�̃{�^��
				m_apPress[nCnt]->Init(D3DXVECTOR3(PREY_POS_X_KEY, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(70.0f, 50.0f, 0.0f),
					D3DXCOLOR(DEFAULT_COLOR_CLEAN_WHITE), 9, 0.0f);
				m_apPress[nCnt]->SetType(CPress::TYPE_MANUAL);
			}
			else
			{	// �R���g���[���[�p�̃{�^��
				m_apPress[nCnt]->Init(D3DXVECTOR3(PREY_POS_X_KEY, SCREEN_HEIGHT / 2 + PREY_POS_Y_DIFFERENCE, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f),
					D3DXCOLOR(DEFAULT_COLOR_CLEAN_WHITE), 8, 0.0f);
				m_apPress[nCnt]->SetType(CPress::TYPE_MANUAL);
			}
		}
	}

	return S_OK;
}
//**************************************************************
//		�I������
//**************************************************************
void CPreyEnd::Uninit(void)
{
	CPress::Unload();
	for (int nCnt = 0; nCnt < MAX_PREYMODE_POLYGON; nCnt++)
	{
		if (m_pScene[nCnt] != NULL)
		{	// NULL����Ȃ��ꍇ
			m_pScene[nCnt]->Uninit();
			m_pScene[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_PRESS_BUTTON; nCnt++)
	{
		if (m_apPress[nCnt] != NULL)
		{	// NULL����Ȃ��ꍇ
			m_apPress[nCnt]->Uninit();
			m_apPress[nCnt] = NULL;
		}
	}

	CResult::Uninit();
}
//**************************************************************
//		�X�V����
//**************************************************************
void CPreyEnd::Update(void)
{
	CSound *pSound = CManager::GetSound();
	switch (m_PreyEndMode)
	{
	case PREYMODE_NONE:			//�����Ȃ����
		m_fCloudScroll -= 0.001f;
		MoveScene(SCENETYPE_SOUL);
		ScrollCloud(m_fCloudScroll);
		CntDownFadeTime();
		break;

	case PREYMODE_MOVENOSTART:	//�A�j���[�V�������J�n���
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			if (m_pScene[SCENETYPE_PLAYER] != NULL)
			{
				m_pScene[SCENETYPE_PLAYER]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
			}
			m_PreyEndMode = PREYMODE_PLAYERPREY;
		}
		break;

	case PREYMODE_PLAYERPREY:	//�v���C���[�����܂������
		if (nCntframe == 0)
		{
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE038);
		}

		nCntframe++;
		if (m_pScene[SCENETYPE_OPTION] != NULL)
		{//�����L��Null�`�F�b�N
			D3DXCOLOR col = m_pScene[SCENETYPE_OPTION]->Getcol();

			col.a += m_fOptionCol;

			m_pScene[SCENETYPE_OPTION]->Setcol(col);
			if (col.a >= 1.0f || col.a <= 0.0f)
			{
				m_fOptionCol *= -1.0f;
			}
		}
		if (nCntframe >= 30)
		{//0.5�b���܂��Ă���Ƃ���������Ă��瓮����
			if (m_pScene[SCENETYPE_OPTION] != NULL)
			{//�����L���͓����ɂ���
				m_pScene[SCENETYPE_OPTION]->Setcol(DEFAULT_COLOR_CLEAN_WHITE);
			}
			if (m_pScene[SCENETYPE_WOOD] != NULL)
			{//�XNull�`�F�b�N
				if (m_pScene[SCENETYPE_PLAYER] != NULL)
				{//�v���C���[Null�`�F�b�N
					if (m_pScene[SCENETYPE_GROUND] != NULL)
					{//�n��Null�`�F�b�N

						D3DXVECTOR3 Playerpos = m_pScene[SCENETYPE_PLAYER]->Getpos();
						D3DXVECTOR3 WoodPos = m_pScene[SCENETYPE_WOOD]->Getpos();
						D3DXVECTOR3 GraundPos = m_pScene[SCENETYPE_GROUND]->Getpos();

						/* �v���C���[�̏��� */
						//��ɂ�����
						m_fCntPlayerMove += m_fChangePlayerMove;
						Playerpos.y += m_fCntPlayerMove;

						if (m_fCntPlayerMove >= 0.5f)
						{//�������ɉ���������
							m_fChangePlayerMove = -1.0f;
						}

						m_pScene[SCENETYPE_PLAYER]->Setpos(Playerpos);

						/* �X�̏��� */
						// ���ɗ��Ƃ�
						m_fCntWoodMove += m_fChangeWoodMove;
						WoodPos.y -= m_fCntPlayerMove;

						m_pScene[SCENETYPE_WOOD]->Setpos(WoodPos);

						/* �n�ʂ̏��� */

						GraundPos.y -= m_fCntPlayerMove;

						if (GraundPos.y >= SCREEN_HEIGHT + m_pScene[SCENETYPE_GROUND]->Getsize().y)
						{//��ʊO�ɍs������
							m_pScene[SCENETYPE_GROUND]->Setpos(D3DXVECTOR3(GraundPos.x, SCREEN_HEIGHT + m_pScene[SCENETYPE_GROUND]->Getsize().y, 0.0f));
							m_pScene[SCENETYPE_GROUND]->Setcol(DEFAULT_COLOR_CLEAN_WHITE);
						}
						m_pScene[SCENETYPE_GROUND]->Setpos(GraundPos);

						if (Playerpos.y <= 0.0f - SCREEN_HEIGHT / 2 && WoodPos.y >= SCREEN_HEIGHT + 200.0f)
						{//�v���C���[����ʊO�ɏo����
							m_pScene[SCENETYPE_PLAYER]->Setcol(DEFAULT_COLOR_CLEAN_WHITE); //���ɔ����ē������
							m_pScene[SCENETYPE_PLAYER]->SetTex(1, 1, D3DXVECTOR2(0.5f, 1.0f));
							nCntframe = 0;
							m_PreyEndMode = PREYMODE_DEATH;
						}
					}
				}
			}
		}
		break;

	case PREYMODE_DEATH:		//�v���C���[�����񂾏��
		nCntframe++;
		ScrollCloud(m_fCloudScroll);

		if (m_pScene[SCENETYPE_CLOUD] != NULL)
		{//�_Null�`�F�b�N
			D3DXCOLOR Cloudcol = m_pScene[SCENETYPE_CLOUD]->Getcol();
			float fCloudcol = 0.1f;

			Cloudcol.a += fCloudcol;
			m_pScene[SCENETYPE_CLOUD]->Setcol(Cloudcol);
			if (Cloudcol.a >= 1.0f)
			{
				m_pScene[SCENETYPE_CLOUD]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
			}
		}
		if (nCntframe >= 40)
		{//0.6�b���������
			if (m_pScene[SCENETYPE_PLAYER] != NULL)
			{
				/* �v���C���[�̏��� */
				D3DXCOLOR col = m_pScene[SCENETYPE_PLAYER]->Getcol();
				float fFadePLCol = 0.01f;

				m_pScene[SCENETYPE_PLAYER]->Setpos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

				col.a += fFadePLCol;
				m_pScene[SCENETYPE_PLAYER]->Setcol(col);
				if (col.a >= 1.0f)
				{//�����x���オ��؂���
					if (m_pScene[SCENETYPE_SOUL] != NULL)
					{
						m_pScene[SCENETYPE_SOUL]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
					}
				}
				if (m_pScene[SCENETYPE_LOGO] != NULL)
				{
					D3DXCOLOR Logocol = m_pScene[SCENETYPE_LOGO]->Getcol();
					float fFadeLogoCol = 0.01f;

					Logocol.a += fFadeLogoCol;
					m_pScene[SCENETYPE_LOGO]->Setcol(Logocol);

					if (Logocol.a >= 1.0f)
					{//�����x���オ��؂�
						if (m_pScene[SCENETYPE_MENU_RETRY])
						{
							m_pScene[SCENETYPE_MENU_RETRY]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
						}
						if (m_pScene[SCENETYPE_MENU_QUIT])
						{
							m_pScene[SCENETYPE_MENU_QUIT]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
						}

						//BGM�F�Q�[���I�[�o�[
						pSound->PlaySoundA(CSound::SOUND_LABEL_BGM004);

						//SE �F�`�[��
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE019);

						m_PreyEndMode = PREYMODE_NONE;
						m_MenuState = MENUSTATE_RETRY;
					}
				}
			}
		}
		break;
	}

	/* ���j���[�̏��� */
	if (m_MenuState != MENUSTATE_NONE)
	{//NONE����Ȃ��Ƃ���������\�ɂ���
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_A) == true || CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true)
		{
			m_nSelectNum = (m_nSelectNum + 1) % 2;
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE002);
		}

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_D) == true || CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
		{
			m_nSelectNum = (m_nSelectNum + 1) % 2;
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE002);
		}

		for (int nCnt = 0; nCnt < MAX_PRESS_BUTTON; nCnt++)
		{
			if (m_apPress[nCnt] != NULL)
			{
				m_apPress[nCnt]->Setpos(D3DXVECTOR3((PREY_POS_X_KEY + (nCnt * PREY_POS_X_DIFFERENCE)) + (m_nSelectNum * PREY_POS_Y_NUM_DIF), SCREEN_HEIGHT / 2 + PREY_POS_Y_DIFFERENCE, 0.0f));
				m_apPress[nCnt]->SetType(CPress::TYPE_NONE);
			}
		}

		/* ���j���[���I�΂�Ă��鎞�̏��� */
		if (m_nSelectNum == 0)
		{//���g���C
			m_MenuState = MENUSTATE_RETRY;
		}
		else if (m_nSelectNum == 1)
		{//�N�C�b�g
			m_MenuState = MENUSTATE_QUIT;
		}
	}
	switch (m_MenuState)
	{//�I�΂�Ă郂�[�h�ʂ̏���
	case MENUSTATE_NONE:
		break;

	case MENUSTATE_RETRY:
		m_MenuCol = MENUSTATECOLOR_RETRY;
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
				CFade::Create(CManager::MODE_GAME, CFade::FADE_OUT);
				m_MenuState = MENUSTATE_NONE;
				pSound->StopSound(CSound::SOUND_LABEL_BGM004);
			}
		}
		break;

	case MENUSTATE_QUIT:
		m_MenuCol = MENUSTATECOLOR_QUIT;
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT);
				m_MenuState = MENUSTATE_NONE;
				pSound->StopSound(CSound::SOUND_LABEL_BGM004);
			}
		}
		break;
	}
	switch (m_MenuCol)
	{//�I�΂�Ă郂�[�h�̐F�ƈʒu
	case MENUSTATECOLOR_NONE:
		break;

	case MENUSTATECOLOR_RETRY:
		if (m_pScene[SCENETYPE_MENU_RETRY] != NULL)
		{
			m_pScene[SCENETYPE_MENU_RETRY]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
		}
		if (m_pScene[SCENETYPE_MENU_QUIT] != NULL)
		{
			m_pScene[SCENETYPE_MENU_QUIT]->Setcol(DEFAULT_COLOR_HALFCLEAN_WHITE);
		}
		break;

	case MENUSTATECOLOR_QUIT:
		if (m_pScene[SCENETYPE_MENU_RETRY] != NULL)
		{
			m_pScene[SCENETYPE_MENU_RETRY]->Setcol(DEFAULT_COLOR_HALFCLEAN_WHITE);
		}
		if (m_pScene[SCENETYPE_MENU_QUIT] != NULL)
		{
			m_pScene[SCENETYPE_MENU_QUIT]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
		}
		break;
	}

	/* ���o�X�L�b�v�̏��� */
	if (m_bSkipProduction == false)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				SkipProduction();
				m_bSkipProduction = true;
			}
		}
	}
}
//**************************************************************
//		�`�揈��
//**************************************************************
void CPreyEnd::Draw(void)
{

}
//**************************************************************
//		�㉺�ړ�����
//**************************************************************
void CPreyEnd::MoveScene(SceneType type)
{
	if (m_pScene[type] != NULL)
	{/* ���̏��� */
		D3DXVECTOR3 pos = m_pScene[type]->Getpos();

		if (m_fCntMove >= 0.5f || m_fCntMove <= -0.5f)
		{
			m_fChengeMove *= -1.0f;//�܂�Ԃ�
		}
		m_fCntMove += m_fChengeMove;
		pos.x += m_fCntMove;

		m_pScene[type]->Setpos(pos);
	}
}
//**************************************************************
//		���o��΂������̏���
//**************************************************************
void CPreyEnd::SkipProduction(void)
{
	CSound *pSound = CManager::GetSound();

	if (m_pScene[SCENETYPE_CLOUD] != NULL)
	{//�_
		m_pScene[SCENETYPE_CLOUD]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	if (m_pScene[SCENETYPE_WOOD] != NULL)
	{//�X
		m_pScene[SCENETYPE_WOOD]->Setpos(D3DXVECTOR3(m_pScene[SCENETYPE_WOOD]->Getpos().x, SCREEN_HEIGHT + 200.0f, 0.0f));
	}
	if (m_pScene[SCENETYPE_GROUND] != NULL)
	{//�n��
		m_pScene[SCENETYPE_GROUND]->Setcol(DEFAULT_COLOR_CLEAN_WHITE);
	}
	if (m_pScene[SCENETYPE_PLAYER] != NULL)
	{//�v���C���[
		m_pScene[SCENETYPE_PLAYER]->Setpos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_pScene[SCENETYPE_PLAYER]->SetTex(1, 1, D3DXVECTOR2(0.5f, 1.0f));
		m_pScene[SCENETYPE_PLAYER]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	if (m_pScene[SCENETYPE_SOUL] != NULL)
	{//��
		m_pScene[SCENETYPE_SOUL]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	if (m_pScene[SCENETYPE_OPTION] != NULL)
	{//�����L��
		m_pScene[SCENETYPE_OPTION]->Setcol(DEFAULT_COLOR_CLEAN_WHITE);
	}
	if (m_pScene[SCENETYPE_LOGO] != NULL)
	{//���S
		m_pScene[SCENETYPE_LOGO]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	if (m_pScene[SCENETYPE_MENU_RETRY])
	{//���g���C
		m_pScene[SCENETYPE_MENU_RETRY]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}
	if (m_pScene[SCENETYPE_MENU_QUIT])
	{//�N�C�b�g
		m_pScene[SCENETYPE_MENU_QUIT]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
	}

	//BGM�F�Q�[���I�[�o�[
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM004);
	//SE �F�`�[��
	pSound->PlaySoundA(CSound::SOUND_LABEL_SE019);

	m_PreyEndMode = PREYMODE_NONE;
	m_MenuState = MENUSTATE_RETRY;
}
//**************************************************************
//		�_�̃X�N���[��
//**************************************************************
void CPreyEnd::ScrollCloud(float Scroll)
{
	if (m_pScene[SCENETYPE_CLOUD] != NULL)
	{//�_Null�`�F�b�N
		m_pScene[SCENETYPE_CLOUD]->SetTex(1, 1, D3DXVECTOR2(Scroll, 1.0f));
	}
}
//=============================================================================
// ��CEscapeEnd :(����ED)
//=============================================================================
//**************************************************************
//		�R���X�g���N�^
//**************************************************************
CEscapeEnd::CEscapeEnd()
{
	for (int nCnt = 0; nCnt < MAX_ESCAPEMODE_POLYGON; nCnt++)
	{
		m_pScene[nCnt] = NULL;
	}
	m_fScrollCloud = 0.0f;
	m_fCntMove = 0.0f;
	m_fChengeMove = 0.001f;
}
//**************************************************************
//		�f�X�g���N�^
//**************************************************************
CEscapeEnd::~CEscapeEnd()
{

}
//**************************************************************
//				�ǂݍ��ރe�N�X�`��
//**************************************************************
HRESULT CEscapeEnd::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, RESULT_ESCAPE_SKY, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_ESCAPE_BG, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_PREY_CLOUD, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, RESULT_ESCAPE_ENEMY, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, RESULT_ESCAPE_PLAYER, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, RESULT_FALLING_LOGO, &m_pTexture[5]);

	return S_OK;
}

//**************************************************************
//				�J������e�N�X�`��
//**************************************************************
void CEscapeEnd::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ESCAPEMODE_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//**************************************************************
//		����������
//**************************************************************
HRESULT CEscapeEnd::Init()
{
	CSound *pSound = CManager::GetSound();
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM003);

	for (int nCnt = 0; nCnt < MAX_ESCAPEMODE_POLYGON; nCnt++)
	{
		if (m_pScene[nCnt] == NULL)
		{
			if (nCnt == SCENETYPE_SKY)
			{//��
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), DEFAULT_COLOR_OPACITY_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_BG)
			{//�w�i
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_2, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), DEFAULT_COLOR_OPACITY_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_CLOUD)
			{//�_
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_BG, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(500.0f, 200.0f, 0.0f),
					D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), DEFAULT_COLOR_OPACITY_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->Setrot(0.2f);
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_ENEMY)
			{//�G
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_1, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(180.0f, 380.0f, 0.0f),
					D3DXVECTOR3(150.0f, 150.0f, 0.0f), DEFAULT_COLOR_OPACITY_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_PLAYER)
			{//�v���C���[
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_3, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(980.0f, 405.0f, 0.0f),
					D3DXVECTOR3(250.0f, 400.0f, 0.0f), DEFAULT_COLOR_OPACITY_WHITE, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->Setrot(-0.2f);
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}
			else if (nCnt == SCENETYPE_LOGO)
			{//���S
				m_pScene[nCnt] = new CScene2D(CScene::PRIORITY_4, CScene::OBJTYPE_RESULT);
				m_pScene[nCnt]->SetInitAll(D3DXVECTOR3(320.0f, 80.0f, 0.0f),
					D3DXVECTOR3(300.0f, 80.0f, 0.0f), DEFAULT_COLOR_CLEAN_WHITE, D3DXVECTOR2(1.0f, 0.5f));
				m_pScene[nCnt]->Init();
				m_pScene[nCnt]->SetTex(1, 1, D3DXVECTOR2(1.0f, 1.0f));
				m_pScene[nCnt]->BindTexture(m_pTexture[nCnt]);
			}

		}
	}

	return S_OK;
}
//**************************************************************
//		�I������
//**************************************************************
void CEscapeEnd::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	for (int nCnt = 0; nCnt < MAX_ESCAPEMODE_POLYGON; nCnt++)
	{
		if (m_pScene[nCnt] != NULL)
		{	// NULL����Ȃ��ꍇ
			m_pScene[nCnt]->Uninit();
			m_pScene[nCnt] = NULL;
		}
	}

	CResult::Uninit();
}
//**************************************************************
//		�X�V����
//**************************************************************
void CEscapeEnd::Update(void)
{
	CSound *pSound = CManager::GetSound();

	/* �_�̏��� */
	m_fScrollCloud += 0.001f;
	ScrollCloud(m_fScrollCloud);
	CntDownFadeTime();

	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		if (m_pScene[SCENETYPE_LOGO] != NULL)
		{
			/* ���S�̏��� */
			D3DXCOLOR col = m_pScene[SCENETYPE_LOGO]->Getcol();
			float FadeCol = 0.1f;

			col.a += FadeCol;

			m_pScene[SCENETYPE_LOGO]->Setcol(col);

			if (col.a >= 1.0f)
			{
				m_pScene[SCENETYPE_LOGO]->Setcol(DEFAULT_COLOR_OPACITY_WHITE);
			}
		}
	}
	if (m_pScene[SCENETYPE_PLAYER] != NULL)
	{
		/* �v���C���[�̏��� */
		float rot = m_pScene[SCENETYPE_PLAYER]->Getrot();

		if (m_fCntMove >= 0.015f || m_fCntMove <= -0.015f)
		{
			m_fChengeMove *= -1.0f;//�܂�Ԃ�
		}

		m_fCntMove += m_fChengeMove;
		rot += m_fCntMove;

		m_pScene[SCENETYPE_PLAYER]->Setrot(rot);
	}
	if (m_pScene[SCENETYPE_ENEMY] != NULL)
	{
		/* �G�̏��� */
		D3DXVECTOR3 size = m_pScene[SCENETYPE_ENEMY]->Getsize();
		D3DXVECTOR3 pos = m_pScene[SCENETYPE_ENEMY]->Getpos();
		float Shrink = 0.2f;

		D3DXVECTOR3 Scal = D3DXVECTOR3(size.x - Shrink, size.y - Shrink, 0.0f);
		D3DXVECTOR3 NextPos = D3DXVECTOR3(pos.x - Shrink, pos.y + Shrink + Shrink, 0.0f);

		m_pScene[SCENETYPE_ENEMY]->Setsize(Scal);
		m_pScene[SCENETYPE_ENEMY]->Setpos(NextPos);
		if (Scal.x <= 0.0f&&Scal.y <= 0.0f)
		{//�������Ȃ肫����
			m_pScene[SCENETYPE_ENEMY]->Setsize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (CFade::GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���Ă��Ȃ����
		if (CManager::GetInputKeyboard()->GetALL(1) || CManager::GetInputXPad()->GetALL(1, 0) == true)
		{// �L�[�{�[�h�iENTER�j����͂�����
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE001);
			CFade::Create(CManager::MODE_RANKING, CFade::FADE_OUT);
		}
	}
}
//**************************************************************
//		�`�揈��
//**************************************************************
void CEscapeEnd::Draw(void)
{

}
//**************************************************************
//		�_�̃X�N���[��
//**************************************************************
void CEscapeEnd::ScrollCloud(float Scroll)
{
	if (m_pScene[SCENETYPE_CLOUD] != NULL)
	{//�_Null�`�F�b�N
		m_pScene[SCENETYPE_CLOUD]->SetTex(1, 1, D3DXVECTOR2(Scroll, 1.0f));
	}
}

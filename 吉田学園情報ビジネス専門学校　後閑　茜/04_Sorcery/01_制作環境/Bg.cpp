//=============================================================================
//
// îwåièàóù [bg.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "bg.h"

//=============================================================================
// ê√ìIÉÅÉìÉoïœêî
//=============================================================================
//bool g_bBool = false;
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_TEXTURE] = {};

//=============================================================================
// ÉRÉìÉXÉgÉâÉNÉ^
//=============================================================================
CBg::CBg():CScene(1)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}
	m_nCntBG = 0;
}
//=============================================================================
// ÉfÉXÉgÉâÉNÉ^
//=============================================================================
CBg::~CBg() {}
//=============================================================================
// îwåiÇÃê∂ê¨
//=============================================================================
CBg *CBg::Create(void)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		pBg = new CBg;
		pBg->Init();
	}

	//ÉIÉuÉWÉFÉNÉgÇÃéÌóﬁÇÃê›íË
	pBg->SetObjtype(CScene::OBJTYPE_BG);

	return pBg;
}
//=============================================================================
// îwåiÇÃèâä˙âªèàóù
//=============================================================================
HRESULT CBg::Init(void)
{
	CManager::MODE mode = CManager::GetMode();

	switch (mode)
	{
	case CManager::MODE_TITLE:
		//îwåi1ñáñ⁄
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;

	case CManager::MODE_STAGESELECT:
		//îwåi1ñáñ⁄
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;

	case CManager::MODE_CHARACTORSELECT:
		//îwåi1ñáñ⁄
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;


	case CManager::MODE_TUTORIAL:
		//îwåi1ñáñ⁄
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		
		m_apScene2D[1] = new CScene2D(1);
		m_apScene2D[1]->Init();
		m_apScene2D[1]->BindTexture(m_pTexture[1]);
		m_apScene2D[1]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), SCREEN_WIDTH / 2, 300);
		break;

	case CManager::MODE_GAME:
		//îwåi1ñáñ⁄
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		//îwåi2ñáñ⁄
		m_apScene2D[1] = new CScene2D(1);
		m_apScene2D[1]->Init();
		m_apScene2D[1]->BindTexture(m_pTexture[1]);
		m_apScene2D[1]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		break;
		
	case CManager::MODE_CLEAR:
		//îwåi1ñáñ⁄
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;

	case CManager::MODE_OVER:
		//îwåi1ñáñ⁄
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;

	case CManager::MODE_RANKING:
		m_apScene2D[0] = new CScene2D(1);
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetScene2D(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		break;
	}

	return S_OK;
}

//=============================================================================
// îwåiÇÃèIóπèàóù
//=============================================================================
void CBg::Uninit(void)
{
	//m_apScene2DÇîjä¸ÅiÉ|ÉäÉSÉìÇ™îjä¸Ç≥ÇÍÇΩÇæÇØÇ≈bgé©ëÃÇÕîjä¸Ç≥ÇÍÇƒÇ¢Ç»Ç¢Åj
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
		}
	}

	//bgÇîjä¸
	Release();
}
//=============================================================================
// îwåiÇÃçXêVèàóù
//=============================================================================
void CBg::Update(void)
{
	m_nCntBG++;
	CManager::MODE mode = CManager::GetMode();

	switch (mode)
	{
	case CManager::MODE_TITLE:
		break;

	case CManager::MODE_STAGESELECT:
		break;

	case CManager::MODE_CHARACTORSELECT:
		break;

	case CManager::MODE_TUTORIAL:
		m_apScene2D[0]->SetScroll(m_nCntBG, 0.001f);
		m_apScene2D[1]->SetScroll(m_nCntBG, 0.0015f);
		break;

	case CManager::MODE_GAME:
		m_apScene2D[0]->SetScroll(m_nCntBG, 0.001f);
		m_apScene2D[1]->SetScroll(m_nCntBG, 0.002f);
		break;

	case CManager::MODE_CLEAR:
		break;

	case CManager::MODE_OVER:
		break;

	case CManager::MODE_RANKING:
		break;
	}
}
//=============================================================================
// îwåiÇÃï`âÊèàóù
//=============================================================================
void CBg::Draw(void)
{

}
//=============================================================================
// ÉeÉNÉXÉ`ÉÉÇÃÉçÅ[Éh
//=============================================================================
HRESULT CBg::Load(void)
{
	CManager::MODE mode = CManager::GetMode();
	CManager::StageSelectState select = CManager::GetStageSelect();
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	switch (mode)
	{
	case CManager::MODE_TITLE:
		// ÉeÉNÉXÉ`ÉÉÇÃê∂ê¨
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE, &m_pTexture[0]);
		break;

	case CManager::MODE_STAGESELECT:
		// ÉeÉNÉXÉ`ÉÉÇÃê∂ê¨
		D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGESELECT, &m_pTexture[0]);
		break;

	case CManager::MODE_CHARACTORSELECT:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CHARACTERSELECT, &m_pTexture[0]);
		break;

	case CManager::MODE_TUTORIAL:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTORIAL, &m_pTexture[0]);
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTORIAL_SCROLL, &m_pTexture[1]);
		break;

	case CManager::MODE_GAME:
		switch (select)
		{
		case CManager::STAGESELECT_STAGE1:
			D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGE1, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_RAIN, &m_pTexture[1]);
			break;

		case CManager::STAGESELECT_STAGE2:
			D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGE2, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_SMOKE, &m_pTexture[1]);
			break;

		case CManager::STAGESELECT_STAGE3:
			D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGE3, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_SMOKE, &m_pTexture[1]);
			break;

		case CManager::STAGESELECT_STAGE4:
			D3DXCreateTextureFromFile(pDevice, TEXTURE_STAGE4, &m_pTexture[0]);
			D3DXCreateTextureFromFile(pDevice, TEXTURE_SMOKE, &m_pTexture[1]);
			break;
		}
		break;

	case CManager::MODE_CLEAR:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT, &m_pTexture[0]);
		break;

	case CManager::MODE_OVER:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT, &m_pTexture[0]);
		break;

	case CManager::MODE_RANKING:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING, &m_pTexture[0]);
		break;
	}

	return S_OK;
}
//=============================================================================
// ÉeÉNÉXÉ`ÉÉÇÃÉAÉìÉçÅ[Éh
//=============================================================================
void CBg::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		// ÉeÉNÉXÉ`ÉÉÇÃîjä¸
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �ڍ� ������
//
//=============================================================================
#include "renderer.h"
#include "main.h"
#include "scene.h"
#include "debugProc.h"
#include "fade.h"
#include "camera.h"
#include "CameraManager.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WINDOW_CLEAR_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=============================================================================
// �����_�����O�N���X�̃R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	// �l���N���A
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	//#ifdef _DEBUG
	//	m_pFont = NULL;
	//#endif
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
																//d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g���@
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// depth��24bit�X�e���V����8bit
	d3dpp.Windowed = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

																// �f�o�C�X�̐���
																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
#ifdef _DEBUG
	// �f�o�b�N�\���̍X�V
	CDebugProc::Print("cn", "FPS:", GetFPS());
#endif

	// �S�ẴV�[�����X�V
	CScene::UpdeteAll();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		WINDOW_CLEAR_COLOR, 1.0f, 0);

	CFade *pFade = CManager::GetFade();
	CCameraManager* pCameraManager = CManager::GetCameraManager();
	D3DVIEWPORT9 viewportDef;
	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		m_pD3DDevice->GetViewport(&viewportDef);
		//�J����
		if (pCameraManager != NULL)
		{
			switch (CManager::GetMode())
			{
			case CManager::MODE_STAGESELECT:
				if (pCameraManager->SetCamera("STAGESELECT_CAMERA"))
				{
					CScene::DrawAll(0);
				}
				break;
			case CManager::MODE_GAME:
				if (pCameraManager->SetCamera("1P_CAMERA"))
				{
					CScene::DrawAll(1);
				}
				if (pCameraManager->SetCamera("2P_CAMERA"))
				{
					CScene::DrawAll(2);
				}
				if (pCameraManager->SetCamera("3P_CAMERA"))
				{
					CScene::DrawAll(3);
				}
				if (pCameraManager->SetCamera("4P_CAMERA"))
				{
					CScene::DrawAll(4);
				}
				if (pCameraManager->SetCamera("TOPVIEW_CAMERA"))
				{
					CScene::DrawAll(5);
				}

				if (pCameraManager->SetCamera("PAUSE_CAMERA") && CScene::GetbPause() == true)
				{
					CScene::DrawAll(5);
				}

				break;
			case CManager::MODE_TUTORIAL:
				if (pCameraManager->SetCamera("1P_CAMERA"))
				{
					CScene::DrawAll(1);
				}
				if (pCameraManager->SetCamera("2P_CAMERA"))
				{
					CScene::DrawAll(2);
				}
				if (pCameraManager->SetCamera("3P_CAMERA"))
				{
					CScene::DrawAll(3);
				}
				if (pCameraManager->SetCamera("4P_CAMERA"))
				{
					CScene::DrawAll(4);
				}
				if (pCameraManager->SetCamera("TOPVIEW_CAMERA"))
				{
					CScene::DrawAll(5);
				}
				break;
			case CManager::MODE_RESULT:
				if (pCameraManager->SetCamera("RESULT_CAMERA"))
				{
					CScene::DrawAll(5);
				}
				break;
			default:
				if (pCameraManager->SetCamera("DEFAULT_CAMERA"))
				{
					CScene::DrawAll(5);
				}
				break;
			}
		}
		m_pD3DDevice->SetViewport(&viewportDef);

		if (pFade != NULL)
		{
			// �`�揈��
			pFade->Draw();
		}

#ifdef _DEBUG
		// FPS�\��
		CDebugProc::Draw();
#endif
		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �`��ݒ�����Ƃɖ߂�
//=============================================================================
HRESULT CRenderer::ResetRenderState(void)
{
	//�J�����O�ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�A���t�@�u�����h��L����
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//�ʏ퍇���ɂ���
	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���C�e�B���O��L����
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	return S_OK;
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
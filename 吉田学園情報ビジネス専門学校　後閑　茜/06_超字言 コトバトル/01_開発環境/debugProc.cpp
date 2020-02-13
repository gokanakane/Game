//=============================================================================
//
// �f�o�b�N�\������ [debugProc.cpp]
// Author : �ڍ� ������
//
//=============================================================================
#include "debugProc.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;

std::string CDebugProc::m_strDebug;		//�錾���ɂ��łɏ���������Ă���̂ł����ŉ�������K�v�͂Ȃ�

//=============================================================================
// �f�o�b�N�\���N���X�̃R���X�g���N�^
//=============================================================================
CDebugProc::CDebugProc()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// �f�o�b�N�\���̏���������
//=============================================================================
void CDebugProc::Init(void)
{
#ifdef _DEBUG
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 23, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

}

//=============================================================================
// �f�o�b�N�\���̏I������
//=============================================================================
void CDebugProc::Uninit(void)
{
#ifdef _DEBUG
	//������̍폜(������)
	m_strDebug.clear();
	m_strDebug.shrink_to_fit();

	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif
}

//=============================================================================
// �f�o�b�N�\���̕\������
//=============================================================================
void CDebugProc::Print(char *fmt, ...)
{
#ifdef _DEBUG

	// �C�ӌ̈������P�̕ϐ��ɕϊ�
	va_list ap;

	// �ϒ��������P�̕ϐ��ɂ܂Ƃ߂�
	va_start(ap, fmt);

	while (*fmt)
	{
		switch (*fmt)
		{
		case 'c':	// char�^
			m_strDebug += va_arg(ap, char*);//���X�g�̒���char*(string)�^�����o���āAm_strDebug�ɓ����
			break;

		case 'n':	// int�^
			m_strDebug += std::to_string(va_arg(ap, int));//�����o����������string�^�ɕϊ����ē����
			m_strDebug += " ";	//���l�̊Ԃ�1�}�X�J����
			break;

		case 'f':	// float�^(4���Ŋۂ߂�)
			m_strDebug += std::_Floating_to_string("%.4f", va_arg(ap, double));//�����o����������string�^�ɕϊ����ē����
			m_strDebug += " ";	//���l�̊Ԃ�1�}�X�J����
			break;
		}

		fmt++;	// �t�H�[�}�b�g�̕������P�����i�߂�
	}

	m_strDebug += "\n";	//���s

	va_end(ap);	//�I������
#endif
}

//=============================================================================
// �f�o�b�N�\���̍폜����
//=============================================================================
void CDebugProc::ReleseStr(void)
{
#ifdef _DEBUG
	//������̍폜(������)
	m_strDebug.clear();
#endif
}

//=============================================================================
// �f�o�b�N�\���̕\������
//=============================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//�F�w��
	D3DXCOLOR col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_strDebug.c_str(), -1, &rect, DT_LEFT, col);

#endif

}
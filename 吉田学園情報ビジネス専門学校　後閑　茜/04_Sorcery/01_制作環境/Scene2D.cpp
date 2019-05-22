//=============================================================================
//
// ���C������ [scene2D.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "Pause.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
//bool g_bBool = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_TexNum = 0;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fAngle = 0.0f;
	m_fLenge = 0.0f;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D() {}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	//�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();	/* ����܂�悭�Ȃ� */
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	
	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);


	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̑傫���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�|���S���̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�I�u�W�F�N�g�i�������g�j�̔j��
	Release();
}
//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void) {}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	CScene::OBJTYPE type = CScene::GetObjtype();
	
	if (type == CScene::OBJTYPE_PAUSE)
	{
		bool bPause = CPause::GetPause();

		if (bPause == true)
		{
			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
		}
	}
	else
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}
//=============================================================================
// 2D�|���S���̐���
//=============================================================================
CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene = NULL;
	if (pScene == NULL)
	{
		pScene = new CScene2D;
		pScene->Init();
	}

	return pScene;
}
//=============================================================================
// 2D�|���S���̈ړ��̐ݒ�
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	m_pos = pos;

	// ���_����ݒ�
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̑傫���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_fWidth), (m_pos.y + m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y + m_fHeight), 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 2D�|���S���̈ړ��̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// 2D�|���S���̐ݒ�
//=============================================================================
void CScene2D::SetScene2D(D3DXVECTOR3 pos, float sizeW, float sizeH)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	m_pos = pos;
	m_fWidth = sizeW;
	m_fHeight = sizeH;

	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̑傫���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_fWidth), (m_pos.y + m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y + m_fHeight), 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 2D�|���S���̐ݒ�i���𒆐S���W�ɂ���j
//=============================================================================
void CScene2D::SetScene2DLeftCenter(D3DXVECTOR3 pos, float sizeW, float sizeH)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	m_pos = pos;
	m_fWidth = sizeW;
	m_fHeight = sizeH;

	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̑傫���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, (m_pos.y - m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y - m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, (m_pos.y + m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_fWidth), (m_pos.y + m_fHeight), 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}
//=============================================================================
// �e�N�X�`���X�N���[���̏���
//=============================================================================
void CScene2D::SetScroll(int nCnt, float fSpeed)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̑傫���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nCnt*(fSpeed + 1)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + (nCnt*(fSpeed + 1)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nCnt*(fSpeed + 1)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (nCnt*(fSpeed + 1)), 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �����x�̐ݒ�
//=============================================================================
void CScene2D::SetAlpha(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̍X�V
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, col.a);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, col.a);//�O�ڂ̒��_�̐F�w��i�E���j

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̍X�V
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);//�O�ڂ̒��_�̐F�w��i�E���j

	 //���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �e�N�X�`���A�j���[�V����(X��؂�)
//=============================================================================
void CScene2D::SetAnimX(int MaxPattarnX,int MaxPattarnY, int nPattarn)
{//(X��؂�ł̍ő�p�^�[����,Y��؂�ł̍ő�p�^�[����,�p�^�[��)

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̍X�V
	pVtx[0].tex = D3DXVECTOR2((nPattarn % MaxPattarnX) * (1.0f / MaxPattarnX), (1.0f / MaxPattarnY));
	pVtx[1].tex = D3DXVECTOR2((nPattarn % MaxPattarnX) * (1.0f / MaxPattarnX) + (1.0f / MaxPattarnX), (1.0f / MaxPattarnY));
	pVtx[2].tex = D3DXVECTOR2((nPattarn % MaxPattarnX) * (1.0f / MaxPattarnX), (1.0f / MaxPattarnY) + (1.0f / MaxPattarnY));
	pVtx[3].tex = D3DXVECTOR2((nPattarn % MaxPattarnX) * (1.0f / MaxPattarnX) + (1.0f / MaxPattarnX), (1.0f / MaxPattarnY) + (1.0f / MaxPattarnY));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �e�N�X�`���A�j���[�V����(Y��؂�)
//=============================================================================
void CScene2D::SetAnimY(int MaxPattarnX, int MaxPattarnY,int nPattarn)
{//(X��؂�ł̍ő�p�^�[����,Y��؂�ł̍ő�p�^�[����,�p�^�[��)

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̍X�V
	pVtx[0].tex = D3DXVECTOR2((1.0f / MaxPattarnX),(nPattarn % MaxPattarnY) * (1.0f / MaxPattarnY));
	pVtx[1].tex = D3DXVECTOR2((1.0f / MaxPattarnX) + (1.0f / MaxPattarnX),(nPattarn % MaxPattarnY) * (1.0f / MaxPattarnY));
	pVtx[2].tex = D3DXVECTOR2((1.0f / MaxPattarnX),(nPattarn % MaxPattarnY) * (1.0f / MaxPattarnY) + (1.0f / MaxPattarnY));
	pVtx[3].tex = D3DXVECTOR2((1.0f / MaxPattarnX) + (1.0f / MaxPattarnX),(nPattarn % MaxPattarnY) * (1.0f / MaxPattarnY) + (1.0f / MaxPattarnY));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �e�N�X�`���A�j���[�V����(�L�����p)
//=============================================================================
void CScene2D::SetCharaAnim(int nPattarn,float TexsliceY)
{//(X��؂�ł̍ő�p�^�[����,Y��؂�ł̍ő�p�^�[����,�p�^�[��)

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̍X�V
	pVtx[0].tex = D3DXVECTOR2((nPattarn % 4) * (1.0f / 4), TexsliceY);
	pVtx[1].tex = D3DXVECTOR2((nPattarn % 4) * (1.0f / 4) + (1.0f / 4), TexsliceY);
	pVtx[2].tex = D3DXVECTOR2((nPattarn % 4) * (1.0f / 4), TexsliceY + (1.0f / 4));
	pVtx[3].tex = D3DXVECTOR2((nPattarn % 4) * (1.0f / 4) + (1.0f / 4), TexsliceY + (1.0f / 4));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �|���S���T�C�Y
//=============================================================================
void CScene2D::SetSize(float sizeW, float sizeH)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^


	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̑傫���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - sizeW), (m_pos.y - sizeH), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + sizeW), (m_pos.y - sizeH), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - sizeW), (m_pos.y + sizeH), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + sizeW), (m_pos.y + sizeH), 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �|���S���̉�]
//=============================================================================
void CScene2D::SetRotation(float sizeW, float sizeH,float Angle)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	m_fAngle += Angle;									//�p�x��ݒ�
	m_fLenge = sqrtf(sizeW * sizeW + sizeH * sizeH);	//�Ίp���̌v�Z


	/* �p�x�C��	�����a���{���Ĉ�������� */
	if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI*2.0f;
	}
	if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI*2.0f;
	}

	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̑傫���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3((m_pos.x + sinf(m_fAngle+D3DX_PI) * m_fLenge), (m_pos.y + cosf(m_fAngle+D3DX_PI) * m_fLenge), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + sinf(m_fAngle+D3DX_PI*0.5f) * m_fLenge), (m_pos.y + cosf(m_fAngle+D3DX_PI*0.5f) * m_fLenge), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((m_pos.x + sinf(m_fAngle+D3DX_PI*-0.5f) * m_fLenge), (m_pos.y + cosf(m_fAngle+D3DX_PI*-0.5f) * m_fLenge), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + sinf(m_fAngle) * m_fLenge), (m_pos.y + cosf(m_fAngle) * m_fLenge), 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
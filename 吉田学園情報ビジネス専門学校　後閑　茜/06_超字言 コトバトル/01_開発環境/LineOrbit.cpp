//=============================================================================
//
// �O�Տ��� [LineOrbit.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "LineOrbit.h"
#include "manager.h"

#include "debugProc.h"
//=============================================================================
//
// �O�ՃN���X (CLineOrbit)
// Author : Kodama Yuto
//
//=============================================================================

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CLineOrbit::CLineOrbit(int pri, OBJTYPE type) : CScene(pri,type)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pTexture = NULL;

	m_nVtxNum = 0;
	m_nIdxNum = 0;
	m_nPolygonNum = 0;

	m_apMesh = NULL;
}

CLineOrbit::~CLineOrbit()
{

}

//=============================================================================
// ��������
//=============================================================================
CLineOrbit* CLineOrbit::Create(void)
{
	CLineOrbit* pOrbit = NULL;

	pOrbit = new CLineOrbit(6,OBJTYPE_ORBIT);

	if (pOrbit != NULL)
	{
		pOrbit->Init();
	}

	return pOrbit;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void  CLineOrbit::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fScale, D3DXMATRIX* parent, LPCSTR Tag,
	D3DXCOLOR col, unsigned int nMeshNum, unsigned int nPointCreateTime)
{
	m_nCount = 0;
	m_pos = pos;
	m_offset = pos;
	m_rot = rot;
	m_fScale = fScale;
	m_Parent = parent;
	m_color = col;

	m_nMeshNum = nMeshNum;
	if (m_nMeshNum == 0) { m_nMeshNum = 1; }

	m_nPointCreateTime = nPointCreateTime;
	if (m_nPointCreateTime == 0) { m_nPointCreateTime = 1; }

	m_nVtxNum = (nMeshNum * 2) + 2;
	m_nIdxNum = m_nVtxNum;
	m_nPolygonNum = m_nVtxNum / 2;

	//���_�����������I����
	m_apMesh = new D3DXVECTOR3[m_nVtxNum];
	if (m_apMesh != NULL)
	{
		for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
		{
			m_apMesh[nCntVtx] = pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		m_apMesh[0] = pos + D3DXVECTOR3(0.0f,fScale,0.0f);
		m_apMesh[1] = pos + D3DXVECTOR3(0.0f, -fScale, 0.0f);

	}

	//���_�o�b�t�@
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// �f�o�C�X�̎擾
		pDevice = pRenderer->GetDevice();
	}



	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtxNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
	{
		pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntVtx].col = m_color;
		pVtx[nCntVtx].tex = D3DXVECTOR2((nCntVtx / 2.0f) * 1.0f,(nCntVtx % 2) * 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


	//�C���f�b�N�X�o�b�t�@
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIdxNum,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16�r�b�g�̃f�[�^���m��
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);
	WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^

				// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIdx = 0; nCntIdx < m_nIdxNum; nCntIdx++)
	{
		pIdx[nCntIdx] = nCntIdx;	//���̂܂܂Ȃ�
	}
	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	//�e�N�X�`��
	m_pTexture = CTexture::GetTexture("LINE");
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLineOrbit::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLineOrbit::Uninit(void)
{
	//
	if (m_apMesh != NULL)
	{
		delete[] m_apMesh;
		m_apMesh = NULL;
	}

	//���_�o�b�t�@
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�C���f�b�N�X�o�b�t�@
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	m_pTexture = NULL;

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLineOrbit::Update(void)
{
	m_nCount++;

	//CDebugProc::ReleseStr();
	//�ʒu�̍X�V
	m_pos = m_offset;
	if (m_Parent != NULL)
	{
		m_pos = D3DXVECTOR3(m_Parent->_41, m_Parent->_42, m_Parent->_43);
	}

	//���b�V���̍X�V
	if (m_apMesh != NULL)
	{
		if (m_nCount % m_nPointCreateTime == 0)
		{
			//����
			for (int nCntMesh = m_nVtxNum - 1; nCntMesh >= 1; nCntMesh--)
			{
				m_apMesh[nCntMesh] = m_apMesh[nCntMesh - 1];
			}
			for (int nCntMesh = m_nVtxNum - 1; nCntMesh >= 1; nCntMesh--)
			{
				m_apMesh[nCntMesh] = m_apMesh[nCntMesh - 1];
			}

			m_apMesh[0] = m_pos + D3DXVECTOR3(0.0f, m_fScale, 0.0f);
			m_apMesh[1] = m_pos + D3DXVECTOR3(0.0f, -m_fScale, 0.0f);
		}
	}

	//���_�̍X�V
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
	{
		pVtx[nCntVtx].pos = m_apMesh[nCntVtx];
		//CDebugProc::Print("cfcfcf","pos : X = ",m_apMesh[nCntVtx].x,
		//						   "pos : Y = ", m_apMesh[nCntVtx].y,
		//						   "pos : Z = ", m_apMesh[nCntVtx].z);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void CLineOrbit::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// �f�o�C�X�̎擾
		pDevice = pRenderer->GetDevice();
	}

	//���[���h�}�g���b�N�X�̐���(�ʒu�͒��_�o�b�t�@�Ŕ��f���Ă���̂ŋ�̒l������)
	CUtilityMath::CalWorldMatrix(&m_mtxWorld,D3DXVECTOR3(0.0f,0.0f,0.0f),m_rot);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���ʃJ�����O���s��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �|���S���̕`��(���h���̂��߂ɕ�����`�悷��)
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtxNum, 0, m_nPolygonNum);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtxNum, 0, m_nPolygonNum);

	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtxNum, 0, m_nPolygonNum);

	// �ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


}

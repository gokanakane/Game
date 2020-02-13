//=============================================================================
//
// �����b�V���N���X [meshSphere.cpp]
// Author : Kodama Yuto
//	���Ӂ@�����p�Ȃ̂ŒP�̂ł͎g��Ȃ����ƁI�I
//
//=============================================================================
#include "meshSphere.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CMeshSphere::CMeshSphere(int pri, OBJTYPE type) : CScene(pri,type)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pTexture = NULL;
}
CMeshSphere::~CMeshSphere()
{

}

//=============================================================================
// ��������
//=============================================================================
CMeshSphere* CMeshSphere::Create(void)
{
	CMeshSphere* pSphere = NULL;

	pSphere = new CMeshSphere(1, OBJTYPE_MESH_SPHERE);

	if (pSphere != NULL)
	{
		pSphere->Init();
	}

	return pSphere;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CMeshSphere::Set(D3DXVECTOR3 pos, LPCSTR Tag, int nMeshWidth, int nMeshHeight, D3DXVECTOR3 Size, D3DXCOLOR Col,D3DXVECTOR3 rot)
{
	//�f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�l�̐ݒ�
	m_pos = pos;
	m_rot = rot;
	m_Size = Size;
	m_Color = Col;

	m_nMeshWidth = nMeshWidth;
	m_nMeshHeight = nMeshHeight;

	//// ���_��
	//m_nVtxNum = (m_nMeshWidth + 1) * (m_nMeshHeight + 1);
	m_nVtxNum = m_nMeshWidth * (m_nMeshHeight + 1);

	//// �C���f�b�N�X��
	//m_nIdxNum = (m_nMeshWidth + 1) * (m_nMeshHeight + 1)
	//	+ (2 * (m_nMeshHeight - 1))
	//	+ (m_nMeshWidth + 1) * (m_nMeshHeight - 1);
	m_nIdxNum = 2 * m_nMeshHeight * (m_nMeshWidth + 1);

	//// �|���S����
	m_nPolygonNum =(m_nMeshWidth * m_nMeshHeight * 2) + (4 * (m_nMeshHeight - 1));

	//m_nPolygonNum = m_nIdxNum - 2;
	//���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�̐ݒ�
	CreateVertex(pDevice);
	CreateIndex(pDevice);

	//�e�N�X�`���̐ݒ�
	m_pTexture = CTexture::GetTexture(Tag);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshSphere::Init(void)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pTexture = NULL;

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_nMeshWidth = 2;
	m_nMeshHeight = 2;
	m_nVtxNum = 2;

	m_AnimTexUV = D3DXVECTOR2(0.0f,0.0f);
	m_nCntTexAnim = 2;
	m_nCount = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshSphere::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}


	// �I�u�W�F�N�g�̉��
	Release();

}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshSphere::Update(void)
{
	m_nCount++;

	if (m_nCount % m_nCntTexAnim == 0)
	{
		// ���_���̐ݒ�
		VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
							// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
		{
				pVtx[nCntVtx].tex += m_AnimTexUV;
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshSphere::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_pos,m_rot,NULL,m_Size);

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

	//pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
		m_nVtxNum, 0, m_nPolygonNum);

	//pDevice->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0,
	//	m_nVtxNum, 0, m_nPolygonNum);

}

//=============================================================================
// ���_�o�b�t�@��������
//=============================================================================
void CMeshSphere::CreateVertex(LPDIRECT3DDEVICE9 pDev)
{
	//���ɍ���Ă����炢������폜
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// ���_�o�b�t�@�𐶐�
	pDev->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtxNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtxY = 0; nCntVtxY <= m_nMeshHeight; nCntVtxY++)
	{
		for (int nCntVtxX = 0; nCntVtxX < m_nMeshWidth; nCntVtxX++)
		{
			int nNum = (m_nMeshWidth * nCntVtxY) + nCntVtxX;

			float fTheta = D3DXToRadian((180.0f * nCntVtxY) / m_nMeshHeight);
			float fPhi = D3DXToRadian((360.0f * nCntVtxX) / m_nMeshWidth);

			pVtx[nNum].pos = D3DXVECTOR3(sinf(fTheta) * sinf(fPhi),
				cosf(fTheta),
				sinf(fTheta) * cosf(fPhi));

			pVtx[nNum].tex =
				D3DXVECTOR2((nCntVtxX * (1.0f / (float)m_nMeshWidth)),
				(nCntVtxY * (1.0f / (float)m_nMeshHeight)));

			D3DXVECTOR3 nor;
			D3DXVec3Normalize(&nor, &pVtx[nNum].pos);

			pVtx[nNum].nor = nor;
			pVtx[nNum].col = m_Color;

		}
	}


	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �C���f�b�N�X�o�b�t�@��������
//=============================================================================
void CMeshSphere::CreateIndex(LPDIRECT3DDEVICE9 pDev)
{
	//���ɍ���Ă����炢������폜
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	pDev->CreateIndexBuffer(sizeof(WORD) * m_nIdxNum,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16�r�b�g�̃f�[�^���m��
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nIdxCounter = 0;

				// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY <= m_nMeshHeight; nCntIdxY++) {
		for (int nCntIdxX = 0; nCntIdxX < m_nMeshWidth; nCntIdxX++) {
			if (nCntIdxX == m_nMeshWidth) {
				pIdx[nIdxCounter++] = nCntIdxY * m_nMeshWidth;
				pIdx[nIdxCounter++] = (nCntIdxY + 1) * m_nMeshWidth;
			}
			else {
				pIdx[nIdxCounter++] = (nCntIdxY * m_nMeshWidth) + nCntIdxX;
				pIdx[nIdxCounter++] = pIdx[nIdxCounter - 1] + m_nMeshWidth;
			}
		}
	}


	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

}

//=============================================================================
// ���_�F�ݒ菈��
//=============================================================================
void CMeshSphere::SetColor(D3DXCOLOR col)
{
	if (m_pVtxBuff != NULL)
	{
		m_Color = col;

		// ���_���̐ݒ�
		VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
							// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
		{
			pVtx[nCntVtx].col = m_Color;
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

	}
}
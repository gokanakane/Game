//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshField.cpp]
// Author :
//
//=============================================================================
#include "meshField.h"
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================

//=============================================================================
// ���b�V���t�B�[���h�̃R���X�g���N�^
//=============================================================================
CMeshField::CMeshField(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bRand = false;
	m_nSplitX = 0;
	m_nSplitZ = 0;
	m_fDepth = 0;
	m_fWidth = 0;

	for (int nCntNor = 0; nCntNor < NUM_POLYGON; nCntNor++)
	{
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, int nSplitX, int nSplitZ, float fWidth)
{
	CMeshField *pMeshField = NULL;

	if (pMeshField == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pMeshField = new CMeshField;

		if (pMeshField != NULL)
		{
			pMeshField->m_pos = pos;
			pMeshField->m_nSplitX = nSplitX;
			pMeshField->m_nSplitZ = nSplitZ;
			pMeshField->m_fWidth = fWidth;
			pMeshField->Init();
		}
	}

	return pMeshField;
}
//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CMeshField::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�����Ă���������
	m_pTexture = pTexture;
}

void CMeshField::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshField::Init(void)
{
	// �l�̏�����
	m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bRand = false;

	//�����ɔz�u
	float TestX = MESH_CENTER;
	float TestZ = -MESH_CENTER;
	//TestX = MESH_CENTER;

	//MESH_CENTER
	//m_pos.x = (m_nSplitX / 2) * -MESHFIELD_SIZE + (MESHFIELD_SIZE / 2);
	//m_pos.z = (m_nSplitZ / 2) * MESHFIELD_SIZE - (MESHFIELD_SIZE / 2);

	//for (int nCntZ = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	//{
	//	for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
	//	{
			//g_aHeight[nCntZ][nCntX] = 0.0f;
	//	}
	//}

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// �f�o�C�X�̎擾
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);
	m_pTexture = CTexture::GetTexture("FIELD001");

	// ���_���̍쐬
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;

	// ���_��
	m_nNumVerTex = (m_nSplitX + 1) * (m_nSplitZ + 1);

	// �C���f�b�N�X��
	m_nNumIndex = (m_nSplitX + 1) * (m_nSplitZ + 1)
		+ (2 * (m_nSplitZ - 1))
		+ (m_nSplitX + 1) * (m_nSplitZ - 1);

	// �|���S����
	m_nNumPolygon = m_nNumIndex - 2;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVerTex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16�r�b�g�̃f�[�^���m��
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < m_nSplitZ + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < m_nSplitX + 1; nCntVtxX++)
		{
			// ���_���W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3(TestX + (-m_fWidth + (nCntVtxX * m_fWidth)), 0.0f, TestZ + (m_fWidth - (nCntVtxZ * m_fWidth)));
			// �@���̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].tex =
				D3DXVECTOR2(0.0f + (nCntVtxX /** (10.0f / m_nSplitX)*/), 0.0f + (nCntVtxZ /** (10.0f / m_nSplitZ)*/));
		}
		nVtxCounter += m_nSplitX;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

#if(1)
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;

	int nData = 0;
	int nData2 = 0;
	int nData3 = 0;

	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 vec0, vec1, vec2;
			D3DXVECTOR3 nor;

			// ����̃|���S���̂Q�̃x�N�g������@�����Z�o
			pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;
			pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1)].pos;
			pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1) + 1].pos;
			pPos3 = &pVtx[(nCntX + nCntZ + nCntPolygon) + 1].pos;

			vec0 = *pPos1 - *pPos0;
			vec1 = *pPos2 - *pPos0;
			vec2 = *pPos3 - *pPos0;

			// �O�ς��g���Ċe�|���S���̖@�������߂�
			D3DXVec3Cross(&nor, &vec1, &vec0);
			// ���K������
			D3DXVec3Normalize(&nor, &nor);
			// �@����ۑ�
			m_aNor[(nCntZ * m_nSplitZ) + (nCntX * m_nSplitX) + nCntPolygon] = nor;

			// �O�ς��g���Ċe�|���S���̖@�������߂�
			D3DXVec3Cross(&nor, &vec2, &vec1);
			// ���K������
			D3DXVec3Normalize(&nor, &nor);
			// �@����ۑ�
			m_aNor[(nCntZ * m_nSplitZ) + (nCntX * m_nSplitX) + nCntPolygon + 1] = nor;
		}

		nCntPolygon += m_nSplitX;
	}

	for (int nCntPolygonZ = 0; nCntPolygonZ < m_nSplitZ + 1; nCntPolygonZ++)
	{
		for (int nCntPolygonX = 0; nCntPolygonX < m_nSplitX + 1; nCntPolygonX++)
		{
			if (nCntPolygonZ == 0)
			{// ��[
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntPolygonX == m_nSplitX)
				{// �E�[
					pVtx[m_nSplitX].nor = m_aNor[m_nSplitX + (m_nSplitX - 1)];
				}
				else
				{// ��[�̐^��
					pVtx[nCntPolygonX].nor =
						(m_aNor[(nCntPolygonX * 2) - 1] + m_aNor[((nCntPolygonX * 2) - 1) + 1] + m_aNor[((nCntPolygonX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntPolygonZ == m_nSplitZ)
			{// ���[
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[m_nSplitZ * (m_nSplitX + 1)].nor = m_aNor[2 * (m_nSplitX * (m_nSplitZ - 1))];
				}
				else if (nCntPolygonX == m_nSplitX)
				{// �E�[
					pVtx[(m_nSplitX * m_nSplitZ) + (m_nSplitX + m_nSplitZ)].nor =
						(m_aNor[(m_nSplitX * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))] +
							m_aNor[((2 * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))) + 1]) / 2;
				}
				else
				{// ���[�̐^��
					pVtx[(m_nSplitZ * (m_nSplitX + 1)) + nCntPolygonX].nor =
						(m_aNor[(m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2] +
							m_aNor[((m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2) + 1] +
							m_aNor[((m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2) + 2]) / 3;
				}
			}
			else
			{// �^��
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[(m_nSplitX + 1) * nCntPolygonZ].nor =
						(m_aNor[(nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)] +
							m_aNor[(nCntPolygonZ * (2 * m_nSplitX))] +
							m_aNor[(nCntPolygonZ * (2 * m_nSplitX) + 1)]) / 3;
				}
				else if (nCntPolygonX == m_nSplitX)
				{// �E�[
					pVtx[((nCntPolygonZ + 1) * m_nSplitX) + nCntPolygonZ].nor =
						(m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1)))]
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1))) + 1]
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1))) + ((m_nSplitX * 2) + 1)]) / 3;
				}
				else
				{
					pVtx[(m_nSplitX + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (m_nSplitX + 1)) - (m_nSplitX + 1))].nor =
						(m_aNor[((nCntPolygonX - 1) * 2) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 1) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 2) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)))] +
							m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX))) + ((nCntPolygonX * 2) - 2)] +
							m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)) + 1) + ((nCntPolygonX * 2) - 2)] +
							m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)) + 2) + ((nCntPolygonX * 2) - 2)]) / 6;
				}
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

#endif

	WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < m_nSplitZ; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < m_nSplitX + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + m_nSplitX + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < m_nSplitZ - 1 && nCntIdxX == m_nSplitX)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (m_nSplitX + 1) + 1;
				pIdx += 2;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	//LoadHeight();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	//// �e�N�X�`���̔j��
	//if (m_pTexture != NULL)
	//{
	//  m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
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
void CMeshField::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

#if(1)

	if (m_pVtxBuff == NULL) { return; }
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;
	int nCntNorPolygon = 0;

	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 vec0, vec1, vec2;
			D3DXVECTOR3 nor;

			// ����̃|���S���̂Q�̃x�N�g������@�����Z�o
			pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;
			pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1)].pos;
			pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1) + 1].pos;
			pPos3 = &pVtx[(nCntX + nCntZ + nCntPolygon) + 1].pos;

			vec0 = *pPos1 - *pPos0;
			vec1 = *pPos2 - *pPos0;
			vec2 = *pPos3 - *pPos0;

			// �O�ς��g���Ċe�|���S���̖@�������߂�
			D3DXVec3Cross(&nor, &vec1, &vec0);
			// ���K������
			D3DXVec3Normalize(&nor, &nor);
			// �@����ۑ�
			m_aNor[(nCntZ * 2) + (nCntX * 2) + nCntNorPolygon] = nor;

			// �O�ς��g���Ċe�|���S���̖@�������߂�
			D3DXVec3Cross(&nor, &vec2, &vec1);
			// ���K������
			D3DXVec3Normalize(&nor, &nor);
			// �@����ۑ�
			m_aNor[(nCntZ * 2) + (nCntX * 2) + nCntNorPolygon + 1] = nor;
		}

		nCntPolygon += m_nSplitX;
		nCntNorPolygon += (m_nSplitX * 2) - 2;
	}

	int nData0 = 0;
	int nData1 = 0;

	for (int nCntPolygonZ = 0; nCntPolygonZ < m_nSplitZ + 1; nCntPolygonZ++)
	{
		for (int nCntPolygonX = 0; nCntPolygonX < m_nSplitX + 1; nCntPolygonX++)
		{
			if (nCntPolygonZ == 0)
			{// ��[
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntPolygonX == m_nSplitX)
				{// �E�[
					pVtx[m_nSplitX].nor = m_aNor[m_nSplitX + (m_nSplitX - 1)];
				}
				else
				{// ��[�̐^��
					pVtx[nCntPolygonX].nor =
						(m_aNor[(nCntPolygonX * 2) - 1] + m_aNor[((nCntPolygonX * 2) - 1) + 1] + m_aNor[((nCntPolygonX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntPolygonZ == m_nSplitZ)
			{// ���[
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[m_nSplitZ * (m_nSplitX + 1)].nor = m_aNor[2 * (m_nSplitX * (m_nSplitZ - 1))];
				}
				else if (nCntPolygonX == m_nSplitX)
				{// �E�[
					pVtx[(m_nSplitX * m_nSplitZ) + (m_nSplitX + m_nSplitZ)].nor =
						(m_aNor[(2 * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))] +
							m_aNor[((2 * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))) + 1]) / 2;
				}
				else
				{// ���[�̐^��
					pVtx[(m_nSplitZ * (m_nSplitX + 1)) + nCntPolygonX].nor =
						(m_aNor[(m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2] +
							m_aNor[((m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2) + 1] +
							m_aNor[((m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2) + 2]) / 3;
				}
			}
			else
			{// �^��
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[(m_nSplitX + 1) * nCntPolygonZ].nor =
						(m_aNor[(nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)] +
						m_aNor[(nCntPolygonZ * (2 * m_nSplitX))] +
						m_aNor[(nCntPolygonZ * (2 * m_nSplitX) + 1)]) / 3;
				}
				else if (nCntPolygonX == m_nSplitX)
				{// �E�[
					pVtx[((nCntPolygonZ + 1) * m_nSplitX) + nCntPolygonZ].nor =
						(m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1)))]
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1))) + 1]
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1))) + ((m_nSplitX * 2) + 1)]) / 3;
				}
				else
				{
					pVtx[(m_nSplitX + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (m_nSplitX + 1)) - (m_nSplitX + 1))].nor =
						(m_aNor[((nCntPolygonX - 1) * 2) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX))] +
						 m_aNor[((((nCntPolygonX - 1) * 2) + 1) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)))] +
						 m_aNor[((((nCntPolygonX - 1) * 2) + 2) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)))] +
						 m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX))) + ((nCntPolygonX * 2) - 1)] +
						 m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)) + 1) + ((nCntPolygonX * 2) - 1)] +
						 m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)) + 2) + ((nCntPolygonX * 2) - 1)]) / 6;

					nData0 = (m_nSplitX + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (m_nSplitX + 1)) - (m_nSplitX + 1));
					/*nData1 = ((2 * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))) + 1;*/
				}
			}
		}
	}

	int nVtxCounter = 0;

	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{// 0�L�[�������ꂽ��
		SaveHeight();
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

#endif

#ifdef _DEBUG
	CDebugProc::Print("c", "�t�B�[���h");

#endif


}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
{

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// �f�o�C�X�̎擾
		pDevice = pRenderer->GetDevice();
	}

	//�}�g���b�N�X�̌v�Z
	CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_pos,m_rot);

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
	if (CManager::GetMode() != CManager::MODE_TUTORIAL)
	{// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVerTex, 0, m_nNumPolygon);
	}
}

//=============================================================================
// �������擾
//============================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	bool bX = false;
	bool bZ = false;
	bool *abX = new bool[m_nSplitX];
	bool *abZ = new bool[m_nSplitZ];
	bool bRand = false;

	for (int nCount = 0; nCount < m_nSplitX; nCount++)
	{
		abX[nCount] = false;
	}

	for (int nCount = 0; nCount < m_nSplitZ; nCount++)
	{
		abZ[nCount] = false;
	}

	// ���������ǂ̃|���S���ɏ���Ă��邩
	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX -1; nCntX++)
		{
			float  test = MESH_CENTER - m_fWidth + (nCntX * m_fWidth);
			float  test1 = MESH_CENTER + m_fWidth + (nCntX * m_fWidth);
			float  test2 = MESH_CENTER - m_fWidth + (nCntZ * m_fWidth);
			float  test3 = MESH_CENTER  + (nCntZ * m_fWidth);

			if (pos.x >= test && pos.x < test1)
			{
				bX = true;
				abX[nCntX] = true;
			}

			if (pos.z >= test2 && pos.z < test3)
			{
				bZ = true;
				abZ[nCntZ] = true;
			}
		}
	}

	int nCount = 0;

	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			if (abX[nCntX] == true && abZ[nCntZ] == true)
			{
				//CDebugProc::Print("nc", nCntX + nCntZ + nCount, ": ��");
				bRand = true;
			}
			else
			{
				//CDebugProc::Print("nc", nCntX + nCntZ + nCount, ": �O");

				bRand = false;
			}
		}
		nCount+= 2;
	}


	int nCntPolygon = 0;
	int nCntNorPolygon = 0;

	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			if (abX[nCntX] == true && abZ[nCntZ] == true)
			{
				D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
				D3DXVECTOR3 vec0, vec1, vec2, vec3;
				D3DXVECTOR3 nor0, nor1;
				float fData = 0.0f;

				// ����̃|���S���̂Q�̃x�N�g������@�����Z�o
				pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;							// ����
				pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1)].pos;		// ����
				pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1) + 1].pos;	// �E��
				pPos3 = &pVtx[(nCntX + nCntZ + nCntPolygon) + 1].pos;					// �E��

				vec0 = *pPos1 - *pPos0;	// ���̕ӂ̃x�N�g��
				vec1 = *pPos2 - *pPos0;	// ���ォ��E���̃x�N�g��
				vec2 = *pPos3 - *pPos0;	// ��̕ӂ̃x�N�g��
				vec3 = pos - *pPos0;

				// �O�ς��g���Ċe�|���S���̖@�������߂�
				D3DXVec3Cross(&nor0, &vec1, &vec0);
				// ���K������
				D3DXVec3Normalize(&nor0, &nor0);

				// �O�ς��g���Ċe�|���S���̖@�������߂�
				D3DXVec3Cross(&nor1, &vec2, &vec1);
				// ���K������
				D3DXVec3Normalize(&nor1, &nor1);

				fData = ((vec1.z * vec3.x) - (vec1.x * vec3.z));

				if (fData > 0)
				{
					pos.y = (((nor0.x * (pos.x - pPos0->x) + nor0.z * (pos.z - pPos0->z)) / -nor0.y) + pPos0->y);
				}
				else
				{
					pos.y = (((nor1.x * (pos.x - pPos2->x) + nor1.z * (pos.z - pPos2->z)) / -nor1.y) + pPos2->y);
				}

				break;
			}
		}

		nCntPolygon += m_nSplitX;
		nCntNorPolygon += (m_nSplitX * 2) - 2;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	delete[] abX;
	delete[] abZ;

	return pos.y;
}

//=============================================================================
// ������ݒ�
//============================================================================
void CMeshField::SetHeight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
		{
			// pos����Ώۂ̒��_�܂ł̋���
			float fLength = sqrtf
				// x�̋���
				((pos.x - pVtx->pos.x) * (pos.x - pVtx->pos.x) +
				// z�̋���
				(pos.z - pVtx->pos.z) * (pos.z - pVtx->pos.z));

			if (fLength < fRange)
			{// �Ώۂ̒��_���͈͓�
				// �͈͓��ł̋����̔䗦�ɉ���������
				float fHeight = cosf((fLength / fRange) * (D3DX_PI * 0.5f)) * fValue;

				pVtx->pos.y += fHeight;
			}

			// ��������
			//g_aHeight[nCntZ][nCntX] = pVtx->pos.y;

			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �n�ʂ̍�����Ԃ�(�u�[����Ԃ�)
//=============================================================================
bool CMeshField::GetHeightbool(D3DXVECTOR3 &pos)
{
#if 0
	//�ϐ��錾
	D3DXVECTOR3 vec0;
	D3DXVECTOR3 vec1;
	D3DXVECTOR3 nor;
	D3DXVECTOR3 VtxPos[3];
	D3DXVECTOR3 VtxNor[6];
	int			nNumber;
	float		fHeight;

	//�v���C���[�ƃ��b�V���t�B�[���h�̈ʒu�̍������o��
	D3DXVECTOR3 posMtx = pos - m_pos;

	int test1, test2;
	test1 = m_nSplitX;
	test2 = m_nSplitZ;
	//���݃v���C���[�����u���b�N�ڂɂ��邩���m�F���鎮
	int			nMeshX = (int)((posMtx.x) / (MESHFIELD_SIZE / m_nSplitX));
	int			nMeshZ = (int)((posMtx.z) / (MESHFIELD_SIZE / m_nSplitZ) * -1);

	if (nMeshX >= m_nSplitX || nMeshX < 0)
	{
		return false;
	}
	if (nMeshZ >= m_nSplitZ || nMeshZ < 0)
	{
		return false;
	}

	//���݂̏�������Ă���u���b�N�̒��_�̏o����
	int			nMeshLU = nMeshX + nMeshZ * (m_nSplitX + 1);					//��@0�Ԗڂ̒��_
	int			nMeshRU = (nMeshX + 1) + nMeshZ * (m_nSplitX + 1);			//��@1�Ԗڂ̒��_
	int			nMeshLD = nMeshX + (nMeshZ + 1) * (m_nSplitX + 1);			//��@3�Ԗڂ̒��_
	int			nMeshRD = (nMeshX + 1) + (nMeshZ + 1) * (m_nSplitX + 1);		//��@4�Ԗڂ̒��_

																				//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (posMtx.x < 0 || posMtx.x > pVtx[m_nSplitX].pos.x)
	{
		return false;
	}
	if (posMtx.z > 0 || posMtx.z > pVtx[m_nSplitX].pos.z)
	{
		return false;
	}

	CDebugProc::Print("cn", "���݂̃u���b�N�@���� %d�@�u���b�N��\n", nMeshX);
	//	CDebugProc::Print("cncfcfcfc", "pos[", nCntNor, "] : (", pVtx[nCntNor].pos.x, ", ", pVtx[nCntNor].pos.y, ", ", pVtx[nCntNor].pos.z, ")");
	CDebugProc::Print("cn", "���݂̃u���b�N�@�c�� %d�@�u���b�N��\n", nMeshZ);

	//�x�N�g���v�Z�� �ړI - ����
	vec0 = pVtx[nMeshLU].pos - pVtx[nMeshRD].pos;
	//�x�N�g���v�Z�� �����̈ʒu�@- ����
	vec1 = posMtx - pVtx[nMeshRD].pos;

	if ((vec0.x * vec1.z) - (vec0.z * vec1.x) <= 0)
	{//�O�p�`���E�ɂ���ꍇ
		CDebugProc::Print("c", "MeshField���E�͈� : TURE\n");
		vec0 = (posMtx - pVtx[nMeshLU].pos);

		//�e���_�̕ۊ�
		VtxPos[0] = pVtx[nMeshRU].pos;
		VtxPos[1] = pVtx[nMeshRD].pos;
		VtxPos[2] = pVtx[nMeshLU].pos;

		nNumber = 3;
	}
	else if ((vec0.x * vec1.z) - (vec0.z * vec1.x) >= 0)
	{//�O�p�`��荶�ɂ���ꍇ
		CDebugProc::Print("c", "MeshField�����͈� : TURE\n");
		vec0 = (posMtx - pVtx[nMeshRD].pos);

		//�e���_�̕ۊ�
		VtxPos[0] = pVtx[nMeshLD].pos;
		VtxPos[1] = pVtx[nMeshLU].pos;
		VtxPos[2] = pVtx[nMeshRD].pos;

		nNumber = 0;
	}

	//�����@���������O�ɕۑ�����
	fHeight = VtxPos[0].y;

	//3���_��0�̒l���Ђ��Ă����Ė@���ƃv���C���[�̃x�N�g���𒼌������邽��
	VtxPos[2].y -= VtxPos[0].y;
	VtxPos[1].y -= VtxPos[0].y;
	VtxPos[0].y -= VtxPos[0].y;

	//�@���̌v�Z
	vec0 = VtxPos[1] - VtxPos[0];
	vec1 = VtxPos[2] - VtxPos[0];

	//�O�ς̌v�Z
	D3DXVec3Cross(&nor, &vec0, &vec1);
	//���K��
	D3DXVec3Normalize(&nor, &nor);
	//�v���C���[�ւ̃x�N�g��
	vec0 = posMtx - VtxPos[0];
	//���ό���
	((vec0.x * pVtx[nNumber].nor.x) + (vec0.y * pVtx[nNumber].nor.y) + (vec0.z * pVtx[nNumber].nor.z));
	//���όv�Z��
	vec0.y = (-(vec0.x * nor.x) - (vec0.z * nor.z)) / nor.y;
	//�v���C���[��y�ɓ����
	posMtx.y = vec0.y + fHeight + m_pos.y;
	//���_�o�b�t�@�̃A�����b�N����
	m_pVtxBuff->Unlock();

	if (pos.y < posMtx.y)
	{// �v���C���[��n�ʂɏ悹��
		pos.y = posMtx.y;
		return true;
	}
#endif
	return false;

}


//=============================================================================
// �������Z�[�u
//=============================================================================
void CMeshField::SaveHeight(void)
{
	FILE *pFile = NULL;

	// �t�@�C���ɏ�������
	pFile = fopen(TOUL_FILENAME, "wb");

	if (pFile != NULL)
	{
		//fwrite(&g_aHeight[0][0], sizeof(float), m_nSplitZ * m_nSplitX, pFile);	// �f�[�^�̃A�h���X,�f�[�^�̃T�C�Y,�f�[�^�̌�,�t�@�C���|�C���^

		fclose(pFile);
	}
	else
	{
		MessageBox(0, "NULL�ł���", "�x��", MB_OK);
	}

}

//=============================================================================
// ���������[�h
//=============================================================================
void CMeshField::LoadHeight(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	FILE *pFile = NULL;

	pFile = fopen(TOUL_FILENAME, "rb");

	if (pFile != NULL)
	{
		//fread(&g_aHeight[0][0], sizeof(float), m_nSplitZ * m_nSplitX, pFile);	// �f�[�^�̃A�h���X,�f�[�^�̃T�C�Y,�f�[�^�̌�,�t�@�C���|�C���^

		fclose(pFile);
	}
	else
	{
		MessageBox(0, "NULL�ł���", "�x��", MB_OK);
	}

	for (int nCntZ = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
		{// pos����
			//pVtx->pos.y = g_aHeight[nCntZ][nCntX];

			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
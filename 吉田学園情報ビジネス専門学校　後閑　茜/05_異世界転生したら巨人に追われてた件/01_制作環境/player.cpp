//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Eisuke Sakagawa
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "player.h"			// �v���C���[
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "sound.h"			// �T�E���h
#include "game.h"			// �Q�[��
#include "input.h"			// ����
#include "model.h"			// ���f��
#include "motion.h"			// ���[�V����
#include "camera.h"			// �J����
#include "meshField.h"		// ���b�V���t�B�[���h
#include "meshriver.h"		// ���b�V�����o�[
#include "block.h"			// �u���b�N
#include "item.h"			// �A�C�e��
#include "life.h"			// �̗�
#include "effect.h"			// �G�t�F�N�g
#include "enemy.h"			// �G
#include "wall.h"			// ��
#include "start.h"			// �X�^�[�g
#include "fade.h"			//�t�F�C�h
#include "shadow.h"			// �e

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ANIM_NAME			"data\\TEXT\\playermodeldata.txt"	// ���[�V�����f�[�^
#define GRAVITY				(0.7f)								// �d��
#define MOVE_DOWNSPEED_NOR	(0.25f)								// �ʏ팸���X�s�[�h
#define MOVE_DOWNSPEED_ICE	(0.13f)								// ���錸���X�s�[�h
#define MOVE_UPSPEED		(1.0f)								// �A�C�e���ɂ���đ����Ȃ�X�s�[�h�̒l
#define MOVE_UPCOUNTER		(90)								// �A�C�e���ɂ���đ����Ȃ鎞��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int						CPlayer::m_MaxModel = 0;			// ���f����
int						CPlayer::m_MaxAnim = 0;				// �A�j���[�V������

bool					CPlayer::m_bFalling = false;

LPDIRECT3DTEXTURE9		**CPlayer::m_pTexture = NULL;		// �e�N�X�`�����ւ̃|�C���^
LPD3DXMESH				*CPlayer::m_pMesh = NULL;			// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER			*CPlayer::m_pBuffMat = NULL;		// �}�e���A�����ւ̃|�C���^
DWORD					*CPlayer::m_nNumMat = NULL;			// �}�e���A�����̐�

CPlayer::MODEL_INFO		*CPlayer::m_ModelInfo = NULL;		// ���f���C���t�H
CMotion::ANIM_INFO		*CPlayer::m_AnimInfo = NULL;		// �A�j���C���t�H

//=============================================================================
// �R���X�g���N�^									(public)	*** CPlayer ***
//=============================================================================
CPlayer::CPlayer() : CScene(CScene::PRIORITY_3, CScene::OBJTYPE_PLAYER)
{
	m_bStart = true;
	m_nCntStart = 0;
	m_bEnd = false;
	m_bClear = false;
	m_AnimEditCounter = 0;									// �A�j���[�V�����ҏW�J�E���^
	m_state = STATE_NONE;									// ���
	m_nCntEffect = 0;										// �G�t�F�N�g�J�E���^
	m_SoundCounter = 0;										// �T�E���h�J�E���^
	m_nCntState = 0;										// ��ԃJ�E���^
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����MAX
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����MIN
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu�O��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ړ���
	m_frotDest = 0.0f;										// �ڕW����
	m_bJump = false;										// �W�����v
	m_bMove = false;											// �ړ��ł��邩
	m_bSlip = false;										// �����Ă��邩
	m_fSliprot = 0.0f;										// �����Ă������
	m_fDownSpeed = MOVE_DOWNSPEED_NOR;									// ����
	m_nWallJump = 5;										// �ǃL�b�N�J�E���g
	m_bWallJump = false;									// �ǃL�b�N���Ă邩
	m_bWallJumpmove = 0.0f;									// �ǃL�b�N�ړ���
	m_bmoveUp = false;										// �X�s�[�h�A�b�v
	m_nMoveCounter = 0;										// �ړ��J�E���^
	m_bFalling = false;										// ����ED�J�ڗp

	m_shadowHeight = 0.0f;
}

//=============================================================================
// �f�X�g���N�^										(public)	*** CPlayer ***
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ���[�h����							(public)	*** CBullet ***
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		// �f�o�C�X�擾

	FILE *pFile = NULL;

	pFile = fopen(ANIM_NAME, "r");

	if (pFile != NULL)
	{
		int nCntModel = 0;
		int nCntMotion = 0;
		int nCntKey = 0;

		char *pStrCut;		// ������̐擪�ւ̃|�C���^
		char aLine[256];	// ������ǂݎ��p�i�P�s���j
		char aStr[256];		// �����񔲂��o���p

		pStrCut = ReadFile(pFile, &aLine[0]);
		strcpy(aStr, pStrCut);

		if (memcmp(aStr, "SCRIPT", strlen("SCRIPT")) == 0)
		{
			do
			{
				pStrCut = ReadFile(pFile, &aLine[0]);
				strcpy(aStr, pStrCut);

				if (memcmp(aStr, "NUM_MODEL", strlen("NUM_MODEL")) == 0)
				{
					pStrCut += strlen("NUM_MODEL");
					strcpy(aStr, PopString(pStrCut));
					m_MaxModel = atoi(aStr);

					if (m_ModelInfo == NULL)
					{
						m_ModelInfo = new MODEL_INFO[m_MaxModel];
					}
				}
				else if (memcmp(aStr, "MODEL_FILENAME", strlen("MODEL_FILENAME")) == 0)
				{
					pStrCut += strlen("MODEL_FILENAME");
					strcpy(aStr, PopString(pStrCut));
					strcpy(m_ModelInfo[nCntModel].cFileName, aStr);

					nCntModel++;
				}
				else if (memcmp(aStr, "CHARACTERSET", strlen("CHARACTERSET")) == 0)
				{
					nCntModel = 0;

					do
					{
						pStrCut = ReadFile(pFile, &aLine[0]);
						strcpy(aStr, pStrCut);

						if (memcmp(aStr, "PARTSSET", strlen("PARTSSET")) == 0)
						{
							do
							{
								pStrCut = ReadFile(pFile, &aLine[0]);
								strcpy(aStr, pStrCut);

								if (memcmp(aStr, "INDEX", strlen("INDEX")) == 0)
								{
									pStrCut += strlen("INDEX");
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].nIndex = atoi(aStr);
								}
								else if (memcmp(aStr, "PARENT", strlen("PARENT")) == 0)
								{
									pStrCut += strlen("PARENT");
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].nIndex = atoi(aStr);
								}
								else if (memcmp(aStr, "POS", strlen("POS")) == 0)
								{
									pStrCut += strlen("POS");
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].pos.x = (float)atof(aStr);
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].pos.y = (float)atof(aStr);
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].pos.z = (float)atof(aStr);
								}
								else if (memcmp(aStr, "ROT", strlen("ROT")) == 0)
								{
									pStrCut += strlen("ROT");
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].rot.x = (float)atof(aStr);
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].rot.y = (float)atof(aStr);
									strcpy(aStr, PopString(pStrCut));
									m_ModelInfo[nCntModel].rot.z = (float)atof(aStr);
								}
							} while (memcmp(aStr, "END_PARTSSET", strlen("END_PARTSSET")) != 0);
							nCntModel++;
						}
					} while (memcmp(aStr, "END_CHARACTERSET", strlen("END_CHARACTERSET")) != 0);
				}

				if (memcmp(aStr, "NUM_MOTION", strlen("NUM_MOTION")) == 0)
				{
					pStrCut += strlen("NUM_MOTION");
					strcpy(aStr, PopString(pStrCut));
					m_MaxAnim = atoi(aStr);

					if (m_AnimInfo == NULL)
					{
						m_AnimInfo = new CMotion::ANIM_INFO[m_MaxAnim];

						for (int nCount = 0; nCount < m_MaxAnim; nCount++)
						{
							m_AnimInfo[nCount].aKeyInfo = NULL;
						}
					}
				}
				else if (memcmp(aStr, "MOTIONSET", strlen("MOTIONSET")) == 0)
				{
					nCntKey = 0;

					do
					{
						pStrCut = ReadFile(pFile, &aLine[0]);
						strcpy(aStr, pStrCut);

						if (memcmp(aStr, "LOOP", strlen("LOOP")) == 0)
						{
							pStrCut += strlen("LOOP");
							strcpy(aStr, PopString(pStrCut));
							m_AnimInfo[nCntMotion].bLoop = atoi(aStr);
						}
						else if (memcmp(aStr, "NUM_KEY", strlen("NUM_KEY")) == 0)
						{
							pStrCut += strlen("NUM_KEY");
							strcpy(aStr, PopString(pStrCut));
							m_AnimInfo[nCntMotion].nKeyMax = atoi(aStr);

							if (m_AnimInfo[nCntMotion].aKeyInfo == NULL)
							{
								m_AnimInfo[nCntMotion].aKeyInfo = new CMotion::KEY_INFO[m_AnimInfo[nCntMotion].nKeyMax];

								for (int nCount = 0; nCount < m_AnimInfo[nCntMotion].nKeyMax; nCount++)
								{
									m_AnimInfo[nCntMotion].aKeyInfo[nCount].aKey = NULL;
								}
							}
						}
						else if (memcmp(aStr, "BLEND_FRAME", strlen("BLEND_FRAME")) == 0)
						{
							pStrCut += strlen("BLEND_FRAME");
							strcpy(aStr, PopString(pStrCut));
							m_AnimInfo[nCntMotion].nBrendFrame = atoi(aStr);
						}
						else if (memcmp(aStr, "KEYSET", strlen("KEYSET")) == 0)
						{
							nCntModel = 0;

							if (nCntKey < m_AnimInfo[nCntMotion].nKeyMax)
							{
								if (m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey == NULL)
								{
									m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey = new CMotion::KEY[m_MaxModel];
								}
							}

							do
							{
								pStrCut = ReadFile(pFile, &aLine[0]);
								strcpy(aStr, pStrCut);

								if (memcmp(aStr, "FRAME", strlen("FRAME")) == 0)
								{
									pStrCut += strlen("FRAME");
									strcpy(aStr, PopString(pStrCut));
									m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = atoi(aStr);
								}
								else if (memcmp(aStr, "KEY", strlen("KEY")) == 0)
								{
									do
									{
										pStrCut = ReadFile(pFile, &aLine[0]);
										strcpy(aStr, pStrCut);

										if (memcmp(aStr, "POS", strlen("POS")) == 0)
										{
											pStrCut += strlen("POS");
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.x = (float)atof(aStr);
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.y = (float)atof(aStr);
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.z = (float)atof(aStr);
										}
										else if (memcmp(aStr, "ROT", strlen("ROT")) == 0)
										{
											pStrCut += strlen("ROT");
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.x = (float)atof(aStr);
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.y = (float)atof(aStr);
											strcpy(aStr, PopString(pStrCut));
											m_AnimInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.z = (float)atof(aStr);
										}
									} while (memcmp(aStr, "END_KEY", strlen("END_KEY")) != 0);
									nCntModel++;
								}
							} while (memcmp(aStr, "END_KEYSET", strlen("END_KEYSET")) != 0);
							nCntKey++;
						}
					} while (memcmp(aStr, "END_MOTIONSET", strlen("END_MOTIONSET")) != 0);
					nCntMotion++;
				}
			} while (memcmp(aStr, "END_SCRIPT", strlen("END_SCRIPT")) != 0);
		}
	}

	if (m_pTexture == NULL) m_pTexture = new LPDIRECT3DTEXTURE9*[m_MaxModel];
	if (m_pMesh == NULL)	m_pMesh = new LPD3DXMESH[m_MaxModel];
	if (m_pBuffMat == NULL) m_pBuffMat = new LPD3DXBUFFER[m_MaxModel];
	if (m_nNumMat == NULL)	m_nNumMat = new DWORD[m_MaxModel];

	char cName[256];

	for (int nCntParnet = 0; nCntParnet < m_MaxModel; nCntParnet++)
	{
		wsprintf(cName, m_ModelInfo[nCntParnet].cFileName);

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(cName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[nCntParnet], NULL, &m_nNumMat[nCntParnet], &m_pMesh[nCntParnet]);

		D3DXMATERIAL *pmat;							// �}�e���A���f�[�^�ւ̃|�C���^
		D3DMATERIAL9 *matDef;						// ���݂̃}�e���A���ۑ��p
		pmat = (D3DXMATERIAL*)m_pBuffMat[nCntParnet]->GetBufferPointer();
		matDef = new D3DMATERIAL9[m_nNumMat[nCntParnet]];
		m_pTexture[nCntParnet] = new LPDIRECT3DTEXTURE9[m_nNumMat[nCntParnet]];

		for (DWORD tex = 0; tex < m_nNumMat[nCntParnet]; tex++)
		{// �J�E���g
			matDef[tex] = pmat[tex].MatD3D;
			matDef[tex].Ambient = matDef[tex].Diffuse;
			m_pTexture[nCntParnet][tex] = NULL;
			if (pmat[tex].pTextureFilename != NULL &&
				lstrlen(pmat[tex].pTextureFilename) > 0)
			{// �e�N�X�`�����g�p���Ă���
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					pmat[tex].pTextureFilename,
					&m_pTexture[nCntParnet][tex])))
				{
					//MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				}
			}
		}

		delete[] matDef;
		matDef = NULL;
	}

	return S_OK;
}

//=============================================================================
// �A�����[�h����								(public)	*** CBullet ***
//=============================================================================
void CPlayer::Unload(void)
{
	for (int nCntParnet = 0; nCntParnet < m_MaxModel; nCntParnet++)
	{
		// �e�N�X�`���̔j��
		for (DWORD tex = 0; tex < m_nNumMat[nCntParnet]; tex++)
		{// �J�E���g
			if (m_pTexture[nCntParnet][tex] != NULL)
			{// NULL�ȊO�̏ꍇ
				m_pTexture[nCntParnet][tex]->Release();		// ���
				m_pTexture[nCntParnet][tex] = NULL;			// NULL��
			}
		}

		delete[] m_pTexture[nCntParnet];
		m_pTexture[nCntParnet] = NULL;

		// �}�e���A���̊J��
		if (m_pBuffMat[nCntParnet] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pBuffMat[nCntParnet]->Release();				// ���
			m_pBuffMat[nCntParnet] = NULL;					// NULL��
		}

		// �}�e���A���̊J��
		if (m_pMesh[nCntParnet] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pMesh[nCntParnet]->Release();					// ���
			m_pMesh[nCntParnet] = NULL;						// NULL��
		}

		m_nNumMat[nCntParnet] = 0;				// ������
	}

	if (m_pTexture != NULL) { delete[] m_pTexture; m_pTexture = NULL; }
	if (m_pMesh != NULL) { delete[] m_pMesh; m_pMesh = NULL; }
	if (m_pBuffMat != NULL) { delete[] m_pBuffMat; m_pBuffMat = NULL; }
	if (m_nNumMat != NULL) { delete[] m_nNumMat; m_nNumMat = NULL; }

	if (m_ModelInfo != NULL)
	{
		delete[] m_ModelInfo;
		m_ModelInfo = NULL;
	}

	if (m_AnimInfo != NULL)
	{
		for (int nCntAnim = 0; nCntAnim < m_MaxAnim; nCntAnim++)
		{
			for (int nCntKey = 0; nCntKey < m_AnimInfo[nCntAnim].nKeyMax; nCntKey++)
			{
				delete[] m_AnimInfo[nCntAnim].aKeyInfo[nCntKey].aKey;
				m_AnimInfo[nCntAnim].aKeyInfo[nCntKey].aKey = NULL;
			}
			delete[] m_AnimInfo[nCntAnim].aKeyInfo;
			m_AnimInfo[nCntAnim].aKeyInfo = NULL;
		}

		delete[] m_AnimInfo;
		m_AnimInfo = NULL;
	}
}

//=============================================================================
// �m�ۏ���											(public)	*** CPlayer ***
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;			// �|�C���^

	if (pPlayer == NULL)
	{// NULL�̏ꍇ
		pPlayer = new CPlayer;			// �������m��
	}

	if (pPlayer != NULL)
	{// NULL�ȊO�̏ꍇ
		pPlayer->m_pModel = new CModel[m_MaxModel];		// �������m��

		for (int nCntModel = 0; nCntModel < m_MaxModel; nCntModel++)
		{// ���f���J�E���^
		 // ���f���ݒ�
			pPlayer->m_pModel[nCntModel].SetInitAll(m_pTexture[nCntModel], m_pMesh[nCntModel], m_pBuffMat[nCntModel], m_nNumMat[nCntModel], m_ModelInfo[nCntModel].pos, m_ModelInfo[nCntModel].rot);
			pPlayer->m_pModel[nCntModel].Init();

			if (0 <= m_ModelInfo[nCntModel].nIndex)
			{// �e�ȊO
				pPlayer->m_pModel[nCntModel].SetParent(&pPlayer->m_pModel[m_ModelInfo[nCntModel].nIndex]);
			}
		}

		// �l�ݒ�
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->m_frotDest = rot.y;
		pPlayer->Init();					// ����������
	}

	return pPlayer;			// �l��Ԃ�
}

//=============================================================================
// ����������										(public)	*** CPlayer ***
//=============================================================================
HRESULT CPlayer::Init()
{
	if (m_pMotion == NULL)
	{// NULL�̏ꍇ
		m_pMotion = new CMotion;			// �������m��
	}

	// ����ݒ�
	m_vtxMax = D3DXVECTOR3(16.0f, 50.0f, 16.0f);
	m_vtxMin = D3DXVECTOR3(-16.0f, 0.0f, -16.0f);

	m_pMotion->SetAnimNum(0);		// �ҋ@���[�V����

	return S_OK;
}

//=============================================================================
// �I������											(public)	*** CPlayer ***
//=============================================================================
void CPlayer::Uninit(void)
{
	if (m_pModel != NULL)
	{
		for (int nCntModel = 0; nCntModel < m_MaxModel; nCntModel++)
		{
			m_pModel[nCntModel].Uninit();
		}

		delete[] m_pModel;
		m_pModel = NULL;
	}

	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	CGame::SetPlayer();

	CScene::SetDeath();						// �I������
}

//=============================================================================
// �X�V����											(public)	*** CPlayer ***
//=============================================================================
void CPlayer::Update(void)
{
	CFont *pFont = CRenderer::GetFont(CFont::FONTNUM_TEST);

	// �J�����ݒ�
	D3DXVECTOR3 posVDest = CManager::GetCamera()->GetPosVDest();	// ���_�擾
	D3DXVECTOR3 posRDest = CManager::GetCamera()->GetPosRDest();	// �����_�擾

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F

	// �T�E���h
	CSound *pSound = CManager::GetSound();

	switch (m_state)
	{// ���
	case STATE_NONE:			// �ʏ�
		break;
	case STATE_DAMAGE:			// �_���[�W
		m_nCntState++;			// ��ԃJ�E���g

		// �_��
		if (m_nCntState / 9 % 2)
		{// ��
			col = D3DXCOLOR(1.0f, 0.3f, 0.1f, 1.0f);
		}
		else
		{// ��
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}

		if (m_nCntState == 90)
		{// ���̃J�E���g�ɒB������ʏ��
			m_nCntState = 0;
			m_state = STATE_NONE;
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		for (int nCntModel = 0; nCntModel < m_MaxModel; nCntModel++)
		{// ���f��
			m_pModel[nCntModel].Setcol(col);
		}

		break;
	case STATE_DEATH:			// ����
		break;
	}

	bool bMeshField = false;			// ���b�V���t�B�[���h�L��
	bool bMeshRiver = false;			// ���b�V�����o�[�L��
	CMeshField *pMeshField = NULL;
	CMeshRiver *pMeshRiver = NULL;

	for (int nCount = 0; nCount < CGame::m_MeshFieldMax; nCount++)
	{// �t�B�[���h�J�E���^
		pMeshField = CGame::GetMeshField(nCount);

		if (pMeshField != NULL)
		{// NULL�ȊO�̏ꍇ
			if (pMeshField->ColInMesh(m_pos + m_vtxMax))
			{// ������ɂ��邩
				bMeshField = true;			// ���b�V���L��
				break;
			}
			else if (pMeshField->ColInMesh(m_pos))
			{// ������ɂ��邩
				bMeshField = true;			// ���b�V���L��
				break;
			}
			else if (pMeshField->ColInMesh(m_pos + m_vtxMin))
			{// ������ɂ��邩
				bMeshField = true;			// ���b�V���L��
				break;
			}
		}
	}

	for (int nCount = 0; nCount < CGame::m_MeshRiverMax; nCount++)
	{// �t�B�[���h�J�E���^
		pMeshRiver = CGame::GetMeshRiver(nCount);

		if (pMeshRiver != NULL)
		{// NULL�ȊO�̏ꍇ
			if (pMeshRiver->ColInMesh(m_pos + m_vtxMax))
			{// ������ɂ��邩
				bMeshRiver = true;			// ���b�V���L��
				break;
			}
			else if (pMeshRiver->ColInMesh(m_pos))
			{// ������ɂ��邩
				bMeshRiver = true;			// ���b�V���L��
				break;
			}
			else if (pMeshRiver->ColInMesh(m_pos + m_vtxMin))
			{// ������ɂ��邩
				bMeshRiver = true;			// ���b�V���L��
				break;
			}
		}
	}

	m_posOld = m_pos;		// �ʒu�ۑ�

	float fHeight = -500.0f;
	float fUpDown = 0.0f;
	float frotDest = 0.0f;			// �ڕW����
	float fNor = 0.0f;

	if (bMeshField == true)
	{
		fHeight = pMeshField->GetHeight(m_pos);			// �����擾
		//fUpDown = CGame::GetMeshField(nMeshNum)->GetUpDown(m_pos, m_rot);		// �����擾

		//fNor = CGame::GetMeshField(nMeshNum)->GetBlockNor(m_pos);				// �u���b�N�@��

		/*
		// ���鏈��
		if (fNor < 0.8f && fNor != 0.0f)
		{// �͈̓`�F�b�N
			if (m_bSlip == false)
			{// �����ĂȂ�������
				m_fSliprot = m_frotDest;	// �����ݒ�
			}
			m_bSlip = true;		// �����Ă���
		}
		else
		{// �͈͊O
			m_bSlip = false;	// �����Ă��Ȃ�
			m_fSliprot = 0.0f;	// ����������
		}

		if (m_bSlip == true)
		{// �����Ă���
			frotDest = CGame::GetMeshField(nMeshNum)->GetUpDown(m_pos, D3DXVECTOR3(m_rot.x, m_fSliprot, m_rot.z));		// �X�ΐݒ�

																														// �����ύX
			if (frotDest < fUpDown)
			{
				m_fSliprot -= 0.08f;
			}
			else
			{
				m_fSliprot += 0.08f;
			}

			// ����
			m_move.x += sinf(m_fSliprot) * (1.2f + (1.5f * frotDest));
			m_move.z += cosf(m_fSliprot) * (1.2f + (1.5f * frotDest));
		}*/
	}

	m_shadowHeight = fHeight;

	if (m_pos.x >= 13508)
	{//	�Q�[���I���̃t���O���Ă�
		m_bEnd = true;
		m_bMove = false;
	}
	if (m_bEnd == true)
	{//	�t���O����������
		if (m_pos.x >= 13508)
		{
			if (m_pos.x <= 14300)
			{
				m_frotDest = -D3DX_PI * 0.5f;
				m_move.x += sinf(-m_frotDest) * ((1.3f - m_bWallJumpmove) + (1.3f * fUpDown));
				m_move.z += cosf(-m_frotDest) * ((1.3f - m_bWallJumpmove) + (1.3f * fUpDown));
				m_pMotion->SetAnimNum(1);		// �������[�V����
			}
			if (m_pos.x >= 13600)
			{//	����ȏ�̍��W�ɍs������
				m_bClear = true;			//�Q�[��clear

				if (m_bClear == true)
				{//	�Q�[���N���A��������
					if (CFade::GetFade() == CFade::FADE_NONE)
					{// �t�F�[�h���Ă��Ȃ����
					 //	�Q�[���N���A�ɉ�ʑJ��
						CGame::SetGame(CGame::MODE_GAMECLEAR);
						CFade::Create(CManager::MODE_RESULT, CFade::FADE_OUT);

					}
				}

			}
		}
	}
	else if (m_bStart == true)
	{
		if (m_pos.x < 0.0f)
		{
			m_frotDest = -D3DX_PI * 0.5f;
			m_move.x += sinf(-m_frotDest) * ((1.3f - m_bWallJumpmove) + (1.3f * fUpDown));
			m_move.z += cosf(-m_frotDest) * ((1.3f - m_bWallJumpmove) + (1.3f * fUpDown));

			if (m_pMotion->GetAnimNum() != 1)
			{// �W�����v���Ă��Ȃ�
				m_pMotion->SetAnimNum(1);		// �������[�V����
			}
		}
		else
		{
			if (m_nCntStart == 0)
			{
				if (m_pMotion->GetAnimNum() != 0)
				{// �W�����v���Ă��Ȃ�
					m_pMotion->SetAnimNum(0);		// ��~���[�V����
				}
			}

			m_nCntStart++;

			if (m_nCntStart == 30)
			{
				CEffect::Create(m_pos + D3DXVECTOR3(0.0f, 40.0f, 0.0f), 8, 11);//�@�e�N�X�`���@�e�L�X�g
			}
			else if (m_nCntStart == 65)
			{
				CStart::Create(D3DXVECTOR3(posVDest.x, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
			}
			else if (m_nCntStart == 180)
			{
				m_bStart = false;
				m_nCntStart = 0;
				m_bMove = true;
			}
		}
	}
	else
	{
		if (m_bmoveUp == true)	//			[�X�s�[�hUP]
		{//	�A�C�e���ɂ���ăX�s�[�hUP���Ă�����
			m_nMoveCounter++;
			if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true || CManager::GetInputKeyboard()->GetPress(DIK_D) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
			{//	�A�C�e�����擾�������̏��
				m_move.x += sinf(-m_frotDest) * (MOVE_UPSPEED + (MOVE_UPSPEED * fUpDown));
			}
			if (m_nMoveCounter > MOVE_UPCOUNTER)
			{//	���Ԍo�߂ɂ���ăA�C�e���̌��ʂ�����
				m_bmoveUp = false;	//	������ʏ�ɖ߂�
				m_nMoveCounter = 0;	//	�J�E���^�[������������
			}
		}

		// �ړ�����
		if (m_bMove == true)
		{// �ړ��ł���
			if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true)
			{// �iA�j����������
			 // �����ύX�A�ړ��ʐݒ�
				m_frotDest = D3DX_PI * 0.5f;
				m_move.x += sinf(-m_frotDest) * ((1.3f - m_bWallJumpmove) + (1.3f * fUpDown));
				m_move.z += cosf(-m_frotDest) * ((1.3f - m_bWallJumpmove) + (1.3f * fUpDown));

				if (m_bJump == false && m_pMotion->GetAnimNum() != 6)
				{// �W�����v���Ă��Ȃ�
					m_pMotion->SetAnimNum(1);		// �������[�V����
				}
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
			{// �iD�j����������
			 // �����ݒ�A�ړ�����
				m_frotDest = -D3DX_PI * 0.5f;
				m_move.x += sinf(-m_frotDest) * ((1.3f - m_bWallJumpmove) + (1.3f * fUpDown));
				m_move.z += cosf(-m_frotDest) * ((1.3f - m_bWallJumpmove) + (1.3f * fUpDown));

				if (m_bJump == false && m_pMotion->GetAnimNum() != 6)
				{// �W�����v���Ă��Ȃ�
					m_pMotion->SetAnimNum(1);		// �������[�V����
				}
			}
			else
			{// �ړ����Ă��Ȃ�
				if (m_pMotion->GetAnimNum() != 4)
				{// ���ʃ��[�V�����ȊO
					m_pMotion->SetStop(false);		// ���[�V����������
				}

				m_bWallJump = false;				// �ǃL�b�N���Ă��Ȃ�

				if (m_bJump == false && m_pMotion->GetAnimNum() != 3 && m_pMotion->GetAnimNum() != 6 && (m_pMotion->GetAnimNum() != 8 || m_pMotion->GetAnimKeyNum() == 1))
				{// �W�����v���Ă��Ȃ��A���n���[�V�����ȊO�A�i���胂�[�V�����ȊO�A�L�[���P�Ȃ�j
					m_pMotion->SetAnimNum(0);		// �ҋ@���[�V����
				}
			}

			if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{// �i�X�y�[�X�j����������
				if (m_bWallJump == true)
				{// �ǃL�b�N���Ă���
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE017);
					if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true)
					{// �iA�j����������
					 // �����ݒ�A�ړ��ʂ��������A�ړ�����
						m_frotDest = -D3DX_PI * 0.5f;
						m_move.x = 0.0f;
						m_move.x += sinf(-m_frotDest) * 20.0f;
						m_move.z += cosf(-m_frotDest) * 20.0f;
						m_pMotion->SetStop(false);					// ���[�V������~
					}
					else if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
					{// �iD�j����������
					 // �����ݒ�A�ړ��ʂ��������A�ړ�����
						m_frotDest = D3DX_PI * 0.5f;
						m_move.x = 0.0f;
						m_move.x += sinf(-m_frotDest) * 20.0f;
						m_move.z += cosf(-m_frotDest) * 20.0f;
						m_pMotion->SetStop(false);					// ���[�V������~ddad
					}

					m_bWallJump = false;		// �ǃL�b�N���Ȃ�
					m_bWallJumpmove = 1.3f;		// �ǃL�b�N�ړ���
					m_move.y = 12.0f;			// �㏸
					m_fDownSpeed = MOVE_DOWNSPEED_NOR;		// ����������
					m_bJump = true;				// �W�����v���Ă���
					m_pMotion->SetAnimNum(2);	// �W�����v���[�V����
				}

				if (m_bJump == false)
				{// �W�����v�ȊO
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE016);
					m_bWallJump = false;		// �ǃL�b�N���Ȃ�
					m_move.y = 10.0f;			// �㏸
					m_fDownSpeed = MOVE_DOWNSPEED_NOR;		// ����������
					m_bJump = true;				// �W�����v���Ă���

					if (m_pMotion->GetAnimNum() != 6)
						m_pMotion->SetAnimNum(2);	// �W�����v���[�V����
				}
			}
		}
	}

	if ((m_move.x > 0.5f || m_move.x < -0.5f) && m_pos.y <= 5.0f)
	{
		m_nCntEffect++;
		m_SoundCounter++;
		if ((m_nCntEffect % 6) == 0)
		{//	��
			CEffect::Create(m_pos, 4, 4);//�@�e�N�X�`���@�e�L�X�g
			CEffect::Create(m_pos, 2, 3);//�@�e�N�X�`���@�e�L�X�g
		}
		if ((m_SoundCounter % 30) == 0)
		{	// �_�b�V����
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE009);
		}
	}
	if (m_move.y > 5.0f)
	{
		CEffect::Create(m_pos, 3, 5);//�@�e�N�X�`���@�e�L�X�g
	}

	if (bMeshRiver == true)
	{
		if (pMeshRiver != NULL)
		{
			if (m_pos.y < pMeshRiver->Getpos().y)
			{
				m_move.x *= 0.7f;

				if (m_move.y < -12.0f)
				{
					m_move.y *= 0.8f;
					CEffect::Create(m_pos, 7, 0);//�@�e�N�X�`���@�e�L�X�g
				}
				if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true || CManager::GetInputKeyboard()->GetPress(DIK_D) == true
					|| CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
				{
					CEffect::Create(m_pos, 7, 0);//�@�e�N�X�`���@�e�L�X�g
				}
			}
		}
	}

	m_pos += m_move;	// �ړ��ʉ��Z

	// �u���b�N�`�F�b�N
	bool bBlock = false;	// ��������
	bool bClimb = false;	// �o���Ă���
	bool bWallJump = false;	// �o���Ă���

	// �V�[��
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_3);	// ���݁@
	CScene *pSceneNext = NULL;								// ��

	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
		pSceneNext = pScene->GetSceneNext();				// ����ۑ�
		if (pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
		{// �I�u�W�F�N�g�^�C�v���u���b�N��������
			CBlock *pBlock = (CBlock*)pScene;				// �u���b�N�ɃL���X�g
															//bool bLand[4] = { pBlock->Collision(&m_pos, &m_posOld, &m_move, &m_fDownSpeed, m_vtxMax, m_vtxMin) };		// ����`�F�b�N
			pBlock->Collision(&m_pos, &m_posOld, &m_move, &m_fDownSpeed, m_vtxMax, m_vtxMin);		// ����`�F�b�N
			bool *bLand = pBlock->GetHit();

			if (bLand[0] == true)
			{// �㔻��
				pFont->SetMessage(CFont::SETTYPE_ADD, "*0\n");
				m_bJump = false;		// �W�����v���Ȃ�
				bBlock = true;			// ��������

				m_shadowHeight = pBlock->Getpos().y + pBlock->Getsize(0).y;

				if (m_move.y < -16.0f && m_state == STATE_NONE)
				{// �ړ��ʂɉ����ă_���[�W���󂯂�A�ʏ��Ԃ�������
					m_state = STATE_DAMAGE;		// �_���[�W���
					CLife::HitDamage();			// �̗͂����炷
				}

				if (pBlock->GetType() == CBlock::COLTYPE_ICE)
				{// ����u���b�N
					m_fDownSpeed = MOVE_DOWNSPEED_ICE;
				}
				else
				{
					m_fDownSpeed = MOVE_DOWNSPEED_NOR;

					if (pBlock->GetType() == CBlock::COLTYPE_SKY)
					{// �󒆃u���b�N
						if (CManager::GetInputKeyboard()->GetPress(DIK_S) || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true)
						{// �iB�j����������
							m_pos.y -= 1.0f;
							m_posOld.y = m_pos.y;
						}
					}
				}
			}
			else if (bLand[1] == true)
			{// ������
				pFont->SetMessage(CFont::SETTYPE_ADD, "*1\n");
				bBlock = true;			// ��������
			}
			else if (bLand[2] == true)
			{// ������
				pFont->SetMessage(CFont::SETTYPE_ADD, "*2\n");
				bBlock = true;			// ��������

				if (pBlock->GetType() == CBlock::COLTYPE_PUSH)
				{// �����u���b�N
					m_pMotion->SetAnimNum(7);	// �������[�V����
					if ((m_SoundCounter % 30) == 0)
					{	// �������鉹
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE025);
					}

				}
				else if (pBlock->GetType() == CBlock::COLTYPE_BREAK)
				{// �j��u���b�N
					if (CManager::GetInputKeyboard()->GetPress(DIK_B))
					{// �iB�j����������
						m_pMotion->SetAnimNum(8);		// �j�󃂁[�V����
						pBlock->Uninit();				// �u���b�N�j��
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE032);	// �j��
					}
				}
				else if (pBlock->GetType() == CBlock::COLTYPE_FALL)
				{// �|���u���b�N
					if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
					{// �u���b�N�����ɉ����Ă�����
						if (D3DX_PI * 0.3f < pBlock->Getrot().z)		// �͈͂��w�肵�ĉ�]
							pBlock->Setrot(pBlock->Getrot() + D3DXVECTOR3(0.0f, 0.0f, -0.038f));
						if (pBlock->Getrot().z != 0.0f)					// �|�ꂽ�牟�����[�V����
							m_pMotion->SetAnimNum(7);
						if ((m_SoundCounter % 30) == 0)
						{	// �������鉹
							pSound->PlaySoundA(CSound::SOUND_LABEL_SE025);
						}
					}
				}
				else if (pBlock->GetType() == CBlock::COLTYPE_CLIMB)
				{// �o���u���b�N
					m_move.y = 0.0f;				// �ړ��ʁiY�j��������
					m_bJump = false;				// �W�����v���Ă��Ȃ�
					bClimb = true;					// �o���Ă���
					m_pMotion->SetStop(true);		// ���[�V������~

					if (m_pMotion->GetAnimNum() != 6)
					{// �o�胂�[�V�����ȊO
						m_pMotion->SetAnimNumrot(6, 0);		// �o�胂�[�V����
						m_AnimEditCounter = 0;				// ���[�V�����ҏW�J�E���^������
					}

					if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE))
					{// �i�X�y�[�X)����������
						m_pMotion->SetAnimNumrot(6, (m_pMotion->GetAnimKeyNum() + 1) % m_AnimInfo[m_pMotion->GetAnimNum()].nKeyMax);
					}

					if (CManager::GetInputKeyboard()->GetPress(DIK_W) || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true)
					{// �iW)����������
					 // �㏸�A���[�V�����L�[��i�߂�
						m_pos.y += 2.0f;
						m_AnimEditCounter++;
						if (m_AnimEditCounter % 5 == 0)
							m_pMotion->SetAnimNumrot(6, (m_pMotion->GetAnimKeyNum() + 1) % m_AnimInfo[m_pMotion->GetAnimNum()].nKeyMax);
						// �c�^�̉�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE026);
					}
					else if (CManager::GetInputKeyboard()->GetPress(DIK_S) || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true)
					{// �iS)����������
					 // ���~�A���[�V�����L�[��i�߂�
						m_pos.y -= 2.0f;
						m_AnimEditCounter++;
						if (m_AnimEditCounter % 5 == 0)
							m_pMotion->SetAnimNumrot(6, (m_pMotion->GetAnimKeyNum() + 1) % m_AnimInfo[m_pMotion->GetAnimNum()].nKeyMax);
						// �c�^�̉�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE026);
					}
					else
					{
						m_AnimEditCounter = 0;
					}
				}
				else if (pBlock->GetType() == CBlock::COLTYPE_WALLJUMP)
				{// �ǃL�b�N�u���b�N
					bWallJump = true;

					if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
					{// �u���b�N�����ɉ����Ă�����
						if (m_pMotion->GetAnimNum() != 6)
						{// �o�胂�[�V�����ȊO
							m_pMotion->SetAnimNumrot(6, 0);		// �o�胂�[�V����
							m_AnimEditCounter = 0;				// ���[�V�����ҏW�J�E���^������
							m_pMotion->SetStop(true);			// ���[�V������~
						}

						m_move.y = 0.0f;			// �ړ��ʁiY�j��������
						m_pos.y -= 0.2f;			// �ǂ�����
						m_bWallJump = true;			// �ǃL�b�N����
					}
				}
			}
			else if (bLand[3] == true)
			{
				pFont->SetMessage(CFont::SETTYPE_ADD, "*3\n");
				bBlock = true;			// ��������

				if (pBlock->GetType() == CBlock::COLTYPE_PUSH)
				{// �����u���b�N
					m_pMotion->SetAnimNum(7);	// �������[�V����
					if ((m_SoundCounter % 30) == 0)
					{	// �������鉹
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE025);
					}
				}
				else if (pBlock->GetType() == CBlock::COLTYPE_BREAK)
				{// �j��u���b�N
					if (CManager::GetInputKeyboard()->GetPress(DIK_B))
					{// �iB�j����������
						m_pMotion->SetAnimNum(8);		// �j�󃂁[�V����
						pBlock->Uninit();				// �u���b�N�j��
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE032);	// �j��
					}
				}
				else if (pBlock->GetType() == CBlock::COLTYPE_CLIMB)
				{// �o���u���b�N
					m_move.y = 0.0f;				// �ړ��ʁiY�j��������
					m_bJump = false;				// �W�����v���Ă��Ȃ�
					bClimb = true;					// �o���Ă���
					m_pMotion->SetStop(true);		// ���[�V������~

					if (m_pMotion->GetAnimNum() != 6)
					{// �o�胂�[�V�����ȊO
						m_pMotion->SetAnimNumrot(6, 0);		// �o�胂�[�V����
						m_AnimEditCounter = 0;				// ���[�V�����ҏW�J�E���^������
					}

					if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE))
					{// �i�X�y�[�X)����������
						m_pMotion->SetAnimNumrot(6, (m_pMotion->GetAnimKeyNum() + 1) % m_AnimInfo[m_pMotion->GetAnimNum()].nKeyMax);
					}

					if (CManager::GetInputKeyboard()->GetPress(DIK_W) || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true)
					{// �iW)����������
					 // �㏸�A���[�V�����L�[��i�߂�
						m_pos.y += 2.0f;
						m_AnimEditCounter++;
						if (m_AnimEditCounter % 8 == 0)
							m_pMotion->SetAnimNumrot(6, (m_pMotion->GetAnimKeyNum() + 1) % m_AnimInfo[m_pMotion->GetAnimNum()].nKeyMax);
						// �c�^�̉�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE026);
					}
					else if (CManager::GetInputKeyboard()->GetPress(DIK_S) || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true)
					{// �iS)����������
					 // ���~�A���[�V�����L�[��i�߂�
						m_pos.y -= 2.0f;
						m_AnimEditCounter++;
						if (m_AnimEditCounter % 8 == 0)
							m_pMotion->SetAnimNumrot(6, (m_pMotion->GetAnimKeyNum() + 1) % m_AnimInfo[m_pMotion->GetAnimNum()].nKeyMax);
						// �c�^�̉�
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE026);
					}
					else
					{
						m_AnimEditCounter = 0;
					}
				}
				else if (pBlock->GetType() == CBlock::COLTYPE_WALLJUMP)
				{// �ǃL�b�N�u���b�N
					bWallJump = true;

					if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true || CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true)
					{// �u���b�N�����ɉ����Ă�����
						if (m_pMotion->GetAnimNum() != 6)
						{// �o�胂�[�V�����ȊO
							m_pMotion->SetAnimNumrot(6, 0);		// �o�胂�[�V����
							m_AnimEditCounter = 0;				// ���[�V�����ҏW�J�E���^������
							m_pMotion->SetStop(true);			// ���[�V������~
						}

						m_move.y = 0.0f;			// �ړ��ʁiY�j��������
						m_pos.y -= 0.2f;			// �ǂ�����
						m_bWallJump = true;			// �ǃL�b�N����
					}
				}
			}
		}
		pScene = pSceneNext;		// ����ݒ�
	}

	// �V�[��
	pScene = CScene::GetScene(CScene::PRIORITY_4);		// ����
	pSceneNext = NULL;									// ��
	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_ITEM)
		{//	�I�u�W�F�N�g���A�C�e����������
			CItem *pItem = (CItem*)pScene;
			if (pItem->CollisionItem(&m_pos, &m_move, D3DXVECTOR3(30.0f, 30.0f, 30.0f), D3DXVECTOR3(-30.0f, -30.0f, -30.0f)) == true)
			{//	�A�C�e���ɓ���������
				m_bmoveUp = true;		//	�����𑁂�����
			}
		}
		pScene = pSceneNext;		// ����ݒ�
	}

	// �V�[��
	pScene = CScene::GetScene(CScene::PRIORITY_1);		// ����
	pSceneNext = NULL;									// ��
	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_WALL)
		{//	�I�u�W�F�N�g���ǂ�������
			CWall *pWall = (CWall*)pScene;
			pWall->Collision(&m_pos, &m_posOld, &m_move, D3DXVECTOR3(30.0f, 30.0f, 30.0f), D3DXVECTOR3(-30.0f, -30.0f, -30.0f));
		}
		pScene = pSceneNext;		// ����ݒ�
	}

	bool bHitEnemy = false;
	CEnemy *pEnemy = CGame::GetEnemy();

	if (pEnemy != NULL)
	{//	�I�u�W�F�N�g���A�C�e����������
		if (pEnemy->CollisionEnemy(&m_pos, &m_move, D3DXVECTOR3(30.0f, 30.0f, 30.0f), D3DXVECTOR3(-30.0f, -30.0f, -30.0f)) == true)
		{//	�G�ɓ���������
			bHitEnemy = true;
		}
	}

	if (bHitEnemy == true)
	{
		CLife::HitDamage();
		CLife::HitDamage();
		CLife::HitDamage();
		m_pMotion->SetAnimNum(4);
		m_bMove = false;
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE020);
	}

	if (bBlock == false)
	{// �u���b�N�ɓ������Ă��Ȃ�
		if (m_pMotion->GetAnimNum() != 4)
		{// ���ʃ��[�V�����ȊO
			m_pMotion->SetStop(false);		// ���[�V������~
		}

		if (m_pMotion->GetAnimNum() == 6)
		{// �o�胂�[�V����
			m_pMotion->SetStop(false);		// ���[�V������~
			m_pMotion->SetAnimNum(0, 0, 1);		// �ҋ@���[�V����
		}

		m_nWallJump--;		// �ǃL�b�N�J�E���^���炷
		if (m_nWallJump == 0)
		{// �O�ɂȂ�����
			m_bJump = true;	// �W�����v���Ă���
		}
	}
	else
	{// �������Ă���
		m_nWallJump = 5;	// �ǃL�b�N�J�E���^�ݒ�
	}

	if (bBlock == true && m_bJump == false && m_bWallJump == false && bClimb == false && bWallJump == true && m_pMotion->GetAnimNum() == 6)
	{// �o�胂�[�V����
		m_pMotion->SetStop(false);		// ���[�V������~
		m_pMotion->SetAnimNum(0);		// �ҋ@���[�V����
	}

	if (m_bWallJumpmove != 0.0f)
	{// �ǃL�b�N�ړ��ʂ�����
		if (0.0f < m_bWallJumpmove)
		{// �ړ��ʂ�����
			m_bWallJumpmove -= 0.13f;		// ���炵�Ă���
		}
		else
		{// �O�ȉ��ɂȂ�����
			m_bWallJumpmove = 0.0f;			// ������
		}
	}

	if (m_pos.y < fHeight && bMeshField == true)
	{// ���b�V���̍��������A���b�V���L��
		if (m_move.y < -16.0f && m_state == STATE_NONE)
		{// �ړ��ʂɉ����ă_���[�W���󂯂�A�ʏ��Ԃ�������
			m_state = STATE_DAMAGE;		// �_���[�W���
			CLife::HitDamage();			// �̗͂����炷
		}

		m_pos.y = fHeight;				// �����ݒ�
		m_move.y = 0.0f;				// �ړ��ʁiY�j��������
		m_fDownSpeed = MOVE_DOWNSPEED_NOR;			// ����������
		m_nWallJump = 5;				// �ǃL�b�N�J�E���^������
		m_bWallJumpmove = 0.0f;			// �ǃL�b�N�ړ��ʏ�����

		m_bJump = false;				// �W�����v���Ă��Ȃ�

		if (m_pMotion->GetAnimNum() == 6)
		{// �o�胂�[�V����
			m_pMotion->SetStop(false);		// ���[�V������~
			m_pMotion->SetAnimNum(0);		// �ҋ@���[�V����
		}
	}

	if (m_move.y < 0.0f && m_bJump == true)
	{// ���~���Ă���A�W�����v���Ă���
		m_pMotion->SetAnimNum(3);		// ���n���[�V����
	}

	// �J�����ɑ΂��Ĉړ��͈͂��w��
	if (m_pos.x < posVDest.x - 350.0f)
	{// �����E
		m_pos.x = posVDest.x - 350.0f;		// �ʒu�ݒ�
		m_move.x = 0.0f;					// �ړ��ʁiX)��������
	}
	else if (posVDest.x < m_pos.x)
	{// �E���E
		if (0.0f < m_move.x)
		{// �E�Ɉړ����Ă���
		 // �J�����𓮂���
			posVDest.x += m_move.x;			// ���_
			posRDest.x += m_move.x;			// �����_
		}
	}

	if (m_bEnd == false)
	{
		// �J�������f
		CManager::GetCamera()->SetPosVDest(posVDest);
		CManager::GetCamera()->SetPosRDest(posRDest);
	}

	if (0.65f < m_bWallJumpmove)
	{// �ǃL�b�N�ړ��ʃ`�F�b�N
		m_rot.y += ((m_frotDest - m_rot.y) / 5.0f) * ((0.65f - (m_bWallJumpmove / 2.0f)) / 0.65f);		// �����𒲐�
	}
	else
	{// �͈͊O
		m_rot.y += ((m_frotDest - m_rot.y) / 5.0f);														// �����𒲐�
	}

	// ��������
	m_move.x -= (m_move.x - 0.0f) * m_fDownSpeed;
	m_move.y -= GRAVITY;
	m_move.z -= (m_move.z - 0.0f) * m_fDownSpeed;

	if (bClimb == true)m_move.y = 0.0f;			// �o���Ă�����ړ��ʁiY)��������


	if (m_bStart == false || (m_bStart == true && m_nCntStart < 60))
	{
		m_pMotion->Update(m_MaxModel, &m_AnimInfo[0], &m_pModel[0], m_ModelInfo[0].pos);		// ���[�V�����X�V
	}

	CFont::SetMessageData(CScene::OBJTYPE_PLAYER, CFont::SETTYPE_ADD, "Player : �ʒu�@[%.2f, %.2f, %.2f]\n", m_pos.x, m_pos.y, m_pos.z);
	CFont::SetMessageData(CScene::OBJTYPE_PLAYER, CFont::SETTYPE_ADD, "Player : �����@[%.2f, %.2f, %.2f]\n", m_rot.x, m_rot.y, m_rot.z);
	CFont::SetMessageData(CScene::OBJTYPE_PLAYER, CFont::SETTYPE_ADD, "Player : UpDown�@[%.2f]\n", fUpDown);
	CFont::SetMessageData(CScene::OBJTYPE_PLAYER, CFont::SETTYPE_ADD, "Player : fNor�@[%.2f]\n", fNor);
	CFont::SetMessageData(CScene::OBJTYPE_PLAYER, CFont::SETTYPE_ADD, "Player : m_bmoveUp�@[%d]\n", m_bmoveUp);
	CFont::SetMessageData(CScene::OBJTYPE_PLAYER, CFont::SETTYPE_ADD, "\n");

	if (m_bEnd == false)
	{
		if (m_bStart == false)
		{
			if (m_bFalling == false)
			{
				if (m_pos.y < -150.0f)
				{// �����ݒ�
					m_pos.y = -150.0f;							// �ʒu�ݒ�
					m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �v���C���[��~
					m_bMove = false;							// �ړ��ł��Ȃ�
					m_bFalling = true;							// ����ED�ɓ��邽�߂̃t���O
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE039);
				}
			}

			if (m_bMove == false)
			{// �ړ��ł��Ȃ�
				CLife::HitDamage();							// �_���[�W�󂯂�
			}

			if (CLife::GetLife() <= 0)
			{// �̗͂��O
				m_bMove = false;							// �ړ��ł��Ȃ�
				m_pMotion->SetStop(false);					// ���[�V�����J�n
				m_pMotion->SetAnimNum(4);					// ���ʃ��[�V����
			}

			if (m_pMotion->GetAnimNum() == 4 && m_pMotion->GetAnimKeyNum() == 2)
			{// �L�[���Q�ɂȂ�����
				m_pMotion->SetStop(true);					// ���[�V������~
			}
		}
	}
}

//=============================================================================
// �`�揈��											(public)	*** CPlayer ***
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		// �f�o�C�X�擾
	D3DXMATRIX mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

											// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntModel = 0; nCntModel < m_MaxModel; nCntModel++)
	{
		if (m_pModel != NULL)
		{
			m_pModel[nCntModel].Draw();
			CShadow::SetShadow(m_pModel[nCntModel].GetmtxWorld(), m_pMesh[nCntModel], m_nNumMat[nCntModel], D3DXVECTOR3(m_pos.x, m_shadowHeight, m_pos.z));
		}
	}
}
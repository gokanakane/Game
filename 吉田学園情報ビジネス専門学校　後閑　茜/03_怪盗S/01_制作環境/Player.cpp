//=============================================================================
//
// �v���C���[���� [Player.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "Player.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "Stage.h"
#include "Obj.h"
#include "DisPlay.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Enemy.h"
#include "fade.h"
#include "Wall.h"
#include "score.h"
#include "sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//�e�N�X�`���ւ̃|�C���^
Player g_Player;								//���f���̏��
bool g_bPlaying;						//�Q�[�������ǂ����itrue��������X�V�𑱂���j
//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//���_��
	DWORD sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;						//���_�o�b�t�@�̃|�C���^
	g_Player.vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_Player.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	for (int nCnt = 0; nCnt < MAX_PLAYERMODEL; nCnt++)
	{
		g_Player.aModel[nCnt].NumMat = 0;
	}
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(PLAYER_1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMat,
		NULL,
		&g_Player.aModel[0].NumMat,
		&g_Player.aModel[0].pMesh);

	D3DXLoadMeshFromX(PLAYER_2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMat,
		NULL,
		&g_Player.aModel[1].NumMat,
		&g_Player.aModel[1].pMesh);

	D3DXLoadMeshFromX(PLAYER_3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[2].pBuffMat,
		NULL,
		&g_Player.aModel[2].NumMat,
		&g_Player.aModel[2].pMesh);

	D3DXLoadMeshFromX(PLAYER_4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[3].pBuffMat,
		NULL,
		&g_Player.aModel[3].NumMat,
		&g_Player.aModel[3].pMesh);

	D3DXLoadMeshFromX(PLAYER_5,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[4].pBuffMat,
		NULL,
		&g_Player.aModel[4].NumMat,
		&g_Player.aModel[4].pMesh);

	D3DXLoadMeshFromX(PLAYER_6,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[5].pBuffMat,
		NULL,
		&g_Player.aModel[5].NumMat,
		&g_Player.aModel[5].pMesh);

	D3DXLoadMeshFromX(PLAYER_7,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[6].pBuffMat,
		NULL,
		&g_Player.aModel[6].NumMat,
		&g_Player.aModel[6].pMesh);

	D3DXLoadMeshFromX(PLAYER_8,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[7].pBuffMat,
		NULL,
		&g_Player.aModel[7].NumMat,
		&g_Player.aModel[7].pMesh);

	D3DXLoadMeshFromX(PLAYER_9,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[8].pBuffMat,
		NULL,
		&g_Player.aModel[8].NumMat,
		&g_Player.aModel[8].pMesh);

	D3DXLoadMeshFromX(PLAYER_10,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[9].pBuffMat,
		NULL,
		&g_Player.aModel[9].NumMat,
		&g_Player.aModel[9].pMesh);

	D3DXLoadMeshFromX(PLAYER_11,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[10].pBuffMat,
		NULL,
		&g_Player.aModel[10].NumMat,
		&g_Player.aModel[10].pMesh);

	D3DXLoadMeshFromX(PLAYER_12,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[11].pBuffMat,
		NULL,
		&g_Player.aModel[11].NumMat,
		&g_Player.aModel[11].pMesh);

	D3DXLoadMeshFromX(PLAYER_13,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[12].pBuffMat,
		NULL,
		&g_Player.aModel[12].NumMat,
		&g_Player.aModel[12].pMesh);

	D3DXLoadMeshFromX(PLAYER_14,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[13].pBuffMat,
		NULL,
		&g_Player.aModel[13].NumMat,
		&g_Player.aModel[13].pMesh);

	D3DXLoadMeshFromX(PLAYER_15,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[14].pBuffMat,
		NULL,
		&g_Player.aModel[14].NumMat,
		&g_Player.aModel[14].pMesh);

	for (int nCnt2 = 0; nCnt2 < MAX_PLAYERMODEL; nCnt2++)
	{
	//���_���̎擾
	nNumVtx = g_Player.aModel[nCnt2].pMesh->GetNumVertices();
	sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCnt2].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_Player.aModel[nCnt2].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
		{//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (g_Player.vtxMin.x > vtx.x)
			{//X�̍ŏ��l�̏�������
				g_Player.vtxMin.x = vtx.x;
			}
			if (g_Player.vtxMin.z > vtx.z)
			{//Z�̍ŏ��l�̏�������
				g_Player.vtxMin.z = vtx.z;
			}
			if (g_Player.vtxMax.x < vtx.x)
			{//X�̍ŏ��l�̏�������
				g_Player.vtxMax.x = vtx.x;
			}
			if (g_Player.vtxMax.z < vtx.z)
			{//Z�̍ŏ��l�̏�������
				g_Player.vtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@�̃A�����b�N
		g_Player.aModel[nCnt2].pMesh->UnlockVertexBuffer();
	}

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTUER, &g_pTexturePlayer);

	//�㔼�g
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].nIdxModel = -1;	//�e�F����

										//�����g
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].nIdxModel = 0;	//�e�F�㔼�g

										//��
	g_Player.aModel[2].pos = D3DXVECTOR3(0.0f, 2.8f, 0.0f);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[2].nIdxModel = 0;	//�e�F�㔼�g

										//��̘r�E
	g_Player.aModel[3].pos = D3DXVECTOR3(-1.5f, 2.0f, -0.2f);
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[3].nIdxModel = 0;	//�e�F�㔼�g

										//�r�E
	g_Player.aModel[4].pos = D3DXVECTOR3(-3.7f, 1.8f, -0.2f);
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[4].nIdxModel = 3;	//�e�F��̘r

										//�E��
	g_Player.aModel[5].pos = D3DXVECTOR3(-5.0f, 1.7f, -0.25f);
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[5].nIdxModel = 4;	//�e�F�㔼�g

										//��̘r��
	g_Player.aModel[6].pos = D3DXVECTOR3(1.5f, 2.0f, -0.2f);
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[6].nIdxModel = 0;	//�e�F�㔼�g

										//�r��
	g_Player.aModel[7].pos = D3DXVECTOR3(3.7f, 1.8f, -0.2f);
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[7].nIdxModel = 6;	//�e�F��̘r

										//����
	g_Player.aModel[8].pos = D3DXVECTOR3(5.4f, 1.6f, -0.25f);
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[8].nIdxModel = 7;	//�e�F�r

										//�E������
	g_Player.aModel[9].pos = D3DXVECTOR3(-0.8f, -1.5f, -1.0f);
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[9].nIdxModel = 1;	//�e�F�����g

										//�E����
	g_Player.aModel[10].pos = D3DXVECTOR3(-1.25f, -3.8f, -0.75f);
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[10].nIdxModel = 9;	//�e�F������

										//�E��
	g_Player.aModel[11].pos = D3DXVECTOR3(-1.5f, -6.1f, -0.7f);
	g_Player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[11].nIdxModel = 10;	//�e�F����

										//��������
	g_Player.aModel[12].pos = D3DXVECTOR3(0.8f, -1.6f, 0.0f);
	g_Player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[12].nIdxModel = 1;	//�e�F�����g

										//������
	g_Player.aModel[13].pos = D3DXVECTOR3(1.2f, -3.8f, -0.6f);
	g_Player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[13].nIdxModel = 12;	//�e�F������

										//����
	g_Player.aModel[14].pos = D3DXVECTOR3(1.5f, -6.1f, -0.7f);
	g_Player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[14].nIdxModel = 13;	//�e�F����


	// �ʒu�E�����E�F�̏����ݒ�
	g_Player.pos = D3DXVECTOR3(570.0f, 8.0f, -570.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	g_Player.nIdxShadow = SetShadow(g_Player.pos, g_Player.rot);
	g_bPlaying = true;
}
//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYERMODEL; nCnt++)
	{
		// ���b�V���̊J��
		if (g_Player.aModel[nCnt].pMesh != NULL)
		{
			g_Player.aModel[nCnt].pMesh->Release();
			g_Player.aModel[nCnt].pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_Player.aModel[nCnt].pBuffMat != NULL)
		{
			g_Player.aModel[nCnt].pBuffMat->Release();
			g_Player.aModel[nCnt].pBuffMat = NULL;
		}
	}
	//�e�N�X�`���̏�����
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	Camera*pCamera = GetCamera();
	Obj*pObj = GetObj();
	FADE g_Fade = GetFade();
	g_Player.posOld = g_Player.pos;
	if (g_bPlaying == true)
	{
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_Player.rot.y = 0.0f + pCamera->rot.y;
			g_Player.move.x += sinf(D3DX_PI + pCamera->rot.y)*PLAYER_MOVR;
			g_Player.move.z += cosf(D3DX_PI + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.x += sinf(D3DX_PI + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.z += cosf(D3DX_PI + pCamera->rot.y)*PLAYER_MOVR;

		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_Player.rot.y = D3DX_PI + pCamera->rot.y;
			g_Player.move.x += sinf(0.0f + pCamera->rot.y)*PLAYER_MOVR;
			g_Player.move.z += cosf(0.0f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.x += sinf(0.0f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.z += cosf(0.0f + pCamera->rot.y)*PLAYER_MOVR;

		}
		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.rot.y = D3DX_PI * -0.5f + pCamera->rot.y;

			g_Player.move.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y)*PLAYER_MOVR;
			g_Player.move.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y)*PLAYER_MOVR;

			//g_Player.pos.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y)*PLAYER_MOVR;

		}
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.rot.y = D3DX_PI * 0.5f + pCamera->rot.y;

			g_Player.move.x += sinf(D3DX_PI * -0.5f + pCamera->rot.y)*PLAYER_MOVR;
			g_Player.move.z += cosf(D3DX_PI * -0.5f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.x += sinf(D3DX_PI * -0.5f + pCamera->rot.y)*PLAYER_MOVR;
			//g_Player.pos.z += cosf(D3DX_PI * -0.5f + pCamera->rot.y)*PLAYER_MOVR;

		}

		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{//������
			g_Player.rot.y -= 0.5f;
		}
		if (GetKeyboardPress(DIK_RSHIFT) == true)
		{//������
			g_Player.rot.y += 0.5f;
		}
		//�ʒu�X�V
		g_Player.pos += g_Player.move;

		//����
		g_Player.move.x += (0.0f - g_Player.move.x)*0.6f;
		g_Player.move.y += (0.0f - g_Player.move.y)*0.6f;
		g_Player.move.z += (0.0f - g_Player.move.z)*0.6f;


		//�X�e�[�W�̂����蔻��
		CollisionStagePL();

		//���̕ǂƂ̂����蔻��
		CollisionWall_WIDTH_PL(&g_Player.pos, &g_Player.posOld);
		CollisionWall_HEIDTH_PL(&g_Player.pos, &g_Player.posOld);

		//���f���Ƃ̂����蔻��
		if (CollisionObj(&g_Player.pos, &g_Player.posOld, g_Player.vtxMin, g_Player.vtxMax) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				AddScore(2000);
				SetGameState(GAMESTATE_CLEAR);
			}
		}

		//�G�Ƃ̂����蔻��
		if (CollisionEnemy(g_Player.pos, g_Player.vtxMin, g_Player.vtxMax) == true)
		{
			if (g_Fade != FADE_OUT)
			{
				SetGameState(GAMESTATE_OVER);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
		}

		CollisionDisPlay(&g_Player.pos, &g_Player.posOld, g_Player.vtxMin, g_Player.vtxMax);
		//�e�̐ݒu
		SetPositionShadow(g_Player.nIdxShadow, g_Player.pos);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;

	//z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//�v���C���[�̕`��------------------------------------
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);


	for (int nCnt = 0; nCnt < MAX_PLAYERMODEL; nCnt++)
	{
		//�e���f���̃C���f�b�N�X��"-1"
		if (g_Player.aModel[nCnt].nIdxModel == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aModel[0].mtxWorld;
		}

		//���f���̕`��------------------------------------
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCnt].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCnt].rot.y, g_Player.aModel[nCnt].rot.x, g_Player.aModel[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCnt].pos.x, g_Player.aModel[nCnt].pos.y, g_Player.aModel[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxTrans);

		//�e�̃��f���Ɗ֘A�t��
		D3DXMatrixMultiply(&g_Player.aModel[nCnt].mtxWorld, &g_Player.aModel[nCnt].mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCnt].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat <= (int)g_Player.aModel[nCnt].NumMat; nCntMat++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePlayer);

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// ���f��(�p�[�c)�̕`��
			g_Player.aModel[nCnt].pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}


	////���f��[1]�̕`��------------------------------------
	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_Player.aModel[1].mtxWorld);

	//// ��]�𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[1].rot.y, g_Player.aModel[1].rot.x, g_Player.aModel[1].rot.z);
	//D3DXMatrixMultiply(&g_Player.aModel[1].mtxWorld, &g_Player.aModel[1].mtxWorld, &mtxRot);

	//// �ړ��𔽉f
	//D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[1].pos.x, g_Player.aModel[1].pos.y, g_Player.aModel[1].pos.z);
	//D3DXMatrixMultiply(&g_Player.aModel[1].mtxWorld, &g_Player.aModel[1].mtxWorld, &mtxTrans);

	////�e�̃��f���Ɗ֘A�t��
	//D3DXMatrixMultiply(&g_Player.aModel[1].mtxWorld, &g_Player.aModel[1].mtxWorld, &g_Player.aModel[0].mtxWorld);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[1].mtxWorld);

	//// ���݂̃}�e���A�����擾
	//pDevice->GetMaterial(&matDef);

	//// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//pMat = (D3DXMATERIAL*)g_Player.aModel[1].pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat <= (int)g_Player.aModel[1].NumMat; nCntMat++)
	//{
	//	// �e�N�X�`���̐ݒ�
	//	pDevice->SetTexture(0, g_pTexturePlayer);

	//	// �}�e���A���̐ݒ�
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

	//	// ���f��(�p�[�c)�̕`��
	//	g_Player.aModel[1].pMesh->DrawSubset(nCntMat);
	//}

	//// �}�e���A�����f�t�H���g�ɖ߂�
	//pDevice->SetMaterial(&matDef);

	//z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

}
//=============================================================================
// ���f���̎擾
//=============================================================================
Player*GetPlayer(void)
{
	return &g_Player;
}
//=============================================================================
// �X�e�[�W1�̕ӂ蔻��
//=============================================================================
void CollisionStagePL(void)
{
	float VecLine[4];		//�����蔻��̌v�Z����
	D3DXVECTOR3 aPos[4];

	aPos[0] = D3DXVECTOR3(-40.0f, 0.0f, 40.0f);
	aPos[1] = D3DXVECTOR3(590.0f, 0.0f, 40.0f);
	aPos[2] = D3DXVECTOR3(590.0f, 0.0f, -590.0f);
	aPos[3] = D3DXVECTOR3(-40.0f, 0.0f, -590.0f);
	
	//��ǂ����蔻��--------------------------------------------------------------
	//�x�N�g���v�Z
	g_Player.VecA = aPos[0] - aPos[1];
	g_Player.VecC = g_Player.pos - aPos[0];

	//�����蔻��v�Z
	VecLine[0] = (g_Player.VecA.z*g_Player.VecC.x) - (g_Player.VecA.x*g_Player.VecC.z);

	if (VecLine[0] >= 0)
	{//���������獶��
		g_Player.pos.z = aPos[0].z + g_Player.vtxMin.z + 5.0f;
	}
	//���ǂ����蔻��--------------------------------------------------------------
	//�x�N�g���v�Z
	g_Player.VecA = aPos[2] - aPos[3];
	g_Player.VecC = g_Player.pos - aPos[2];

	//�����蔻��v�Z
	VecLine[1] = (g_Player.VecA.z*g_Player.VecC.x) - (g_Player.VecA.x*g_Player.VecC.z);

	if (VecLine[1] >= 0)
	{//���������獶��
		g_Player.pos.z = aPos[2].z + g_Player.vtxMax.z - 5.0f;
	}

	//�E�ǂ����蔻��--------------------------------------------------------------
	//�x�N�g���v�Z
	g_Player.VecA = aPos[1] - aPos[2];
	g_Player.VecC = g_Player.pos - aPos[1];

	//�����蔻��v�Z
	VecLine[2] = (g_Player.VecA.z*g_Player.VecC.x) - (g_Player.VecA.x*g_Player.VecC.z);

	if (VecLine[2] >= 0)
	{//���������獶��
		g_Player.pos.x = aPos[2].x + g_Player.vtxMax.x - 5.0f;
	}

	//���ǂ����蔻��--------------------------------------------------------------
	//�x�N�g���v�Z
	g_Player.VecA = aPos[3] - aPos[0];
	g_Player.VecC = g_Player.pos - aPos[3];

	//�����蔻��v�Z
	VecLine[3] = (g_Player.VecA.z*g_Player.VecC.x) - (g_Player.VecA.x*g_Player.VecC.z);

	if (VecLine[3] >= 0)
	{//���������獶��
		g_Player.pos.x = aPos[3].x + g_Player.vtxMin.x + 5.0f;
	}

}


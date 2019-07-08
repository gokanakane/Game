//=============================================================================
//
// �����L���O�X�R�A���� [score.cpp]
// Author : Gokan Akane
//
//=============================================================================
#include "RankingScore.h"
#include "score.h"
#include "time.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RANKINGSCORE "data\\TEXTURE\\UI\\number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_RANKINGSCORE (8)							    //�X�R�A�̌���
#define MAX_RANKINGSCORE_HEIGTH (5)							//�X�R�A�̒i��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRankingScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int	g_nHighScore[MAX_RANKINGSCORE_HEIGTH];					// �X�R�A
int	g_nScore2;
int g_nRankingScore;										// �\�[�g�p���u���X�R�A
int g_aRankingScoreData[MAX_RANKINGSCORE_HEIGTH][MAX_RANKINGSCORE];// �P���ɐ������i�[����ϐ�
bool bRank = true;

//=============================================================================
// ����������
//=============================================================================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nRankingScore = 0;
	g_nScore2 = 0;

	for (int nRank = 0; nRank < MAX_RANKINGSCORE_HEIGTH; nRank++)
	{//����
		for (int nCnt = 0; nCnt < MAX_RANKINGSCORE; nCnt++)
		{//��
			g_aRankingScoreData[nRank][nCnt] = 0;
		}
	}

	if (bRank == true)
	{
		g_nHighScore[0] = 40000;
		g_nHighScore[1] = 35000;
		g_nHighScore[2] = 30000;
		g_nHighScore[3] = 20000;
		g_nHighScore[4] = 10000;

		bRank = false;
	}

	g_nScore2 = 0;
	g_nRankingScore = 0;

	//�X�R�A�̎擾
	SetHighScore(GetScore());

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						 // �f�o�C�X�ւ̃|�C���^
							TEXTURE_RANKINGSCORE,			// �t�@�C���̖��O
							&g_pTextureRankingScore);		// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexRankingScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRankingScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankingScore(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nRank = 0; nRank < MAX_RANKINGSCORE_HEIGTH; nRank++)
	{//����
		for (int nCnt = 0; nCnt < MAX_RANKINGSCORE; nCnt++)
		{//��
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aRankingScoreData[nRank][nCnt] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aRankingScoreData[nRank][nCnt] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aRankingScoreData[nRank][nCnt] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aRankingScoreData[nRank][nCnt] * 0.1f), 1.0f);

			//�Y���̈ʒu�܂Ői�߂�
			pVtx += 4;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRankingScore->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCnt;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffRankingScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingScore);

	for (nCnt = 0; nCnt < MAX_RANKINGSCORE * MAX_RANKINGSCORE_HEIGTH; nCnt++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCnt * 4,
			2);

	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRankingScore(LPDIRECT3DDEVICE9 pDevice)
{
	int nCnt;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKINGSCORE * MAX_RANKINGSCORE_HEIGTH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt1 = 0; nCnt1 < MAX_RANKINGSCORE_HEIGTH; nCnt1++)
	{//�i
		for (nCnt = 0; nCnt < MAX_RANKINGSCORE; nCnt++)
		{//��
			// ���_����ݒ�	
			pVtx[0].pos = D3DXVECTOR3(420.0f + (60 * nCnt), 180.0f + (110.0f * nCnt1), 0.0f);//��ڂ̒��_�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(480.0f + (60 * nCnt), 180.0f + (110.0f * nCnt1), 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[2].pos = D3DXVECTOR3(420.0f + (60 * nCnt), 280.0f + (110.0f * nCnt1), 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[3].pos = D3DXVECTOR3(480.0f + (60 * nCnt), 280.0f + (110.0f * nCnt1), 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�F
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j


			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			//�Y���̈ʒu�܂Ői�߂�
			pVtx += 4;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRankingScore->Unlock();

}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void SetHighScore(int nScore)
{
	int nCntNum;			//�X�R�A�̌����̃J�E���^�[
	int nNum = 100000000;
	int nNum2 = 10000000;
	int nScore1 = 0;
	int pTime = GetTime();

	nScore1 = nScore*(pTime / 60);

	for (int nRank = 0; nRank < MAX_RANKINGSCORE_HEIGTH; nRank++)
	{//����
		if (g_nHighScore[nRank] < nScore1)
		{
			g_nRankingScore = g_nHighScore[nRank];
			g_nHighScore[nRank] = nScore1;

			for (int nRankCnt = nRank + 1; nRankCnt < MAX_RANKINGSCORE_HEIGTH; nRankCnt++)
			{
				g_nScore2 = g_nHighScore[nRankCnt];
				g_nHighScore[nRankCnt] = g_nRankingScore;
				g_nRankingScore = g_nScore2;
			}
			break;
		}
	}

	for (int nRank = 0; nRank < MAX_RANKINGSCORE_HEIGTH; nRank++)
	{//����
		for (nCntNum = 0; nCntNum < MAX_RANKINGSCORE; nCntNum++)
		{
			g_aRankingScoreData[nRank][nCntNum] = (g_nHighScore[nRank] % nNum) / nNum2;	//�i�[���鐔�����v�Z

			//�������P�����炷
			nNum = nNum / 10;
			nNum2 = nNum2 / 10;

			if (nCntNum == MAX_RANKINGSCORE - 1)
			{//����������
				nNum = 100000000;
				nNum2 = 10000000;
			}
		}
	}
	//�X�R�A�̏�����
	InitScore();
}
//=============================================================================
//
// �����̊Ǘ����� [word_manager.h]
// Author : ���� �x
//
//=============================================================================
#ifndef _WORE_MANAGER_H_
#define _WORE_MANAGER_H_

#include "main.h"
#include "charactor.h"
#include "player.h"
//===================================================================
// �}�N����`
//===================================================================
#define MAX_WORD	(3)			// ������
#define NOT_NUM		(990)		// �S�~����������
#define EMPTINESS_NUM	(1000)	// ��̐���
//===================================================================
// �N���X�̒�`
//===================================================================
class CWordManager
{
public:
	typedef struct
	{
		int nNum;
		char *cWord;
		bool bClearFlag;

	}TYPE_WORD;

	// ��{�֐�
	void Init(void);
	void Uninit(void);
	void Update(void);

	CWordManager();
	~CWordManager();

	void Reset(void);	// ���Z�b�g
	void WordReset(void);	// �������Z�b�g

	// �ݒ�̊֐�
	void SetWord(int nType);
	void BulletCreate(int nID, D3DXVECTOR3 BulletMuzzle, D3DXVECTOR3 BulletRot, CPlayer::PLAYER_TYPE type, C3DCharactor* pChara = NULL);	//BulletMuzzle = �e���o��ʒu	BulletRot = �e���o��p�x
	void SetID(int nID) { m_nPlayerID = nID; }
	static void SetWordLoad(int nNumModel, D3DXVECTOR3 AnswerNum, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int type, int Model, int nPoint);	// �t�@�C�����烊�\�[�X�̓ǂݍ���
	static void SetWordAnswerNum(int nAnswerNum);
	int SearchWord(void);							// �����̑g�ݍ��킹���������ǂ���


	// �擾�p�̊֐�
	int GetCntNum(void) { return m_nCntNum; }
	int GetWordNum(int nNum) { return m_aWord[nNum].nNum; }
	int GetAnswer(void) { return m_nCreateType;	}		// �����Ă��镶���ō��郂�f���̔ԍ����擾
	int GetStockNum(void) { return m_nCntStock; }		// �X�g�b�N���̎擾
	bool GetBulletFlag(void) { return m_bPress; }		// �e�����Ă�悤�ɂȂ����
	float *GetAnswerData(void) { return m_fAnswerData; }	// 2�����̎��ɑg�ݍ��킹�邱�Ƃ��o���镶���f�[�^�̎擾
	static D3DXVECTOR3 *GetAnswerNum(void) { return m_AnswerNum; }
	static int GetAnswerDataNum(void) { return m_nAnswerDataNum; }
	bool GetGatherFlag(void) { return m_bGatherFlag; }
	int GetStock(int nStockNum) { return m_nStock[nStockNum]; }		// �X�g�b�N���̎擾

	// �f�o�b�N�p
	void CreateOblDebug(void);
	void WordDebug(int nCntNum);

private:
	void SearchAssist(int nCntData);
	void UninitAssist(void);

	TYPE_WORD m_aWord[MAX_WORD];
	static int m_nAnswerDataNum;
	static D3DXVECTOR3 *m_AnswerNum;
	static D3DXVECTOR3 *m_Scale;
	static D3DXVECTOR3 *m_rot;
	static int *m_type;
	static int *m_nAnswerTypeModel;
	static int *m_nPoint;

	int m_nCreateType;
	int m_nCntNum;
	int m_nCntaAnswer;
	int m_nPlayerID;
	int m_nCntStock;
	int m_nStock[MAX_WORD];				// �������f���̃X�g�b�N
	float *m_fAnswerData;
	bool m_bPress;
	bool m_bSearch;					// �T�[�`�̃t���O
	bool m_bAnswer[MAX_WORD];
	bool m_bFlag;
	bool m_bAnswerCheck;
	bool m_bGatherFlag;		// �W�߂�t���O
	/* �f�o�b�N�p*/
	void DebugWordCreate(void);
	int nDebugNUm;
	int nDebugCnt;
};

#endif

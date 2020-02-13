//=============================================================================
//
// �����̃r���{�[�h�̏��� [word.h]
// Author :  Shun Yokomici
//
//=============================================================================
#ifndef _WORD_H_
#define _WORD_H_

#include "sceneBillboard.h"
#include "game.h"

//*********************************************************************
// �}�N����`
//*********************************************************************
#define MAX_SIZE		(D3DXVECTOR2(25.0f, 15.0f))	// �T�C�Y�̍ő�l
#define MAX_SIZE_3or4	(D3DXVECTOR2(28.0f, 16.0f))	// �T�C�Y�̍ő�l

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CWord : public CSceneBillBoard //�h���N���X
{
public:
	CWord();
	~CWord();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWord *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWidth, float fHeight, LPCSTR Tag, int nWord, int LostType, int nNum = 0);

	// �֐�
	D3DXVECTOR3 Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle, float fDistance);
	void Circle(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle);				// �~�����
	void Distance(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNumPlayer);							// ���������𑪂�
	int ComparisonDistance(int nNumPlayer);		// �����̔�r
	void SetSearchCol(int nID);			// 3�����ڌ��̐F�ݒ�
	void UninitSearchCol(int nID);		// 3�����ڌ�₪�������ꍇ

	// �擾 �������� �ݒ�̊֐�
	int GetWordNum(void) { return m_nWordNum; }	// �����ԍ����擾
	int GetNum(void) { return m_nNum; }			// �������g�̔ԍ����擾
	int GetID(int nID) { return m_nPlayerID[nID]; }
	bool GetUninitFlag(void) { return m_bFlagUninit; }

	CSceneBillBoard *GetPopBill(void) { return m_pBillBoard[0]; }

	static int GetAllNum(void) { return m_nAllNum; }
private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void SizeScale(D3DXVECTOR3 *size, float fMove, D3DXVECTOR2 MaxSize);		// �g��k��
	void FlashingCol(void);						// �_�ł��鎞�̊֐�

	static int m_nAllNum;

	D3DXVECTOR3 m_move;		// �T�C�Y

	D3DXVECTOR3 m_size;		// �T�C�Y
	D3DXVECTOR3 m_sizeOld;	// �T�C�Y(�ߋ�)
	D3DXVECTOR2 m_SelectNumSize;
	D3DXCOLOR m_col;		// �F
	bool m_bFlagUninit;		// �I�����邽�߂̃t���O
	bool m_bMoveFlag;		// �㉺�ړ��̃t���O
	bool m_bScaleFlag;		// �g��k������t���O
	bool m_bFlag;			// �l���ł��邩�ł��Ȃ���
	bool m_bPopFlag;		// �o�����̃t���O
	bool m_bFlashingFlag;	// �_�Ńt���O
	bool m_bRestFlag;		// ���Z�b�g�t���O
	int m_nWordNum;			// �����̔ԍ�
	int m_nCntFlashing;		// �_�ł��ď��ł̎���
	float m_fDistance[MAX_PLAYER];	// �v���C���[�Ƃ̋���
	float m_fMoveY;			// �ړ�����
	float m_colA;			// �����x

	int		   m_nNum;
	int		   m_nCntUninit;	// �I������܂ł̃J�E���g

	CSceneBillBoard *m_pBillBoard[2];
	int		m_nAnim;
	int		m_nPatten;

	// 3�����ڂ̌�⎞
	bool m_bSearchFlag;		// �T�����̃t���O
	int m_nCntSearch;
	int m_nPlayerID[MAX_PLAYER];

	int	m_nLostType;		// �����邩�����Ȃ����̎��
	int m_nLostCut;			// ������܂ł̃J�E���g

};

#endif
//=============================================================================
//
// �����ۊ�UI�̏��� [tube.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _TUBE_H_
#define _TUBE_H_

#include "scene2D.h"
#include "word_manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CTube : public CScene2D
{
public:
	CTube(int nPriority = 3, OBJTYPE objType = OBJTYPE_UI);											// �R���X�g���N�^
	~CTube();										// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos);				// 2D�I�u�W�F�N�g����������
	virtual void Uninit(void);							// 2D�I�u�W�F�N�g�I������
	virtual void Update(void);							// 2D�I�u�W�F�N�g�X�V����
	virtual void Draw(void);							// 2D�I�u�W�F�N�g�`�揈��

	static CTube *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,LPCSTR Tag, int nPriority = 3);				// �I�u�W�F�N�g�̐���

	//�ݒ�̊֐�
	void SetWordNum(int nWordNum, int nNum, int nStock);
	void SetPoint(int nPoint, int nNum, bool bPoint);
	void SetAnswer(int nAnswer, int nStock);
	void SetStockNum(int nStock) { m_nStockNum = nStock; }
	void AllDelete(int nNum);
	void UninitChack(bool bFlag);	// �I�����Ă��邩�ǂ����̊m�F
	void SetID(int nID) { m_nID = nID; }	// �ԍ��ݒ�

	bool GetFlag(void) { return m_bCreateFlag; }
private:
	void Collect(void);		//�������W�߂�Tex�𐶐�
	void Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNum);
	void Toward(void);		// �������Ă�������
	void WordCreate2D(void);	// �����̕\��
	void SizeChange(D3DXVECTOR2 size);
	void WordUninit();		// �����擾��A������܂ł̃J�E���g

	D3DXVECTOR3 m_AnswerPos;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_sizeAnswer;
	CScene2D *m_apWord[MAX_WORD];
	CScene2D *m_pAnswerModel[MAX_WORD];
	CScene2D *m_pShootingStar[MAX_WORD];
	int			m_anAnswerNum[MAX_WORD];
	int		    m_nAnswer;
	int			m_nID;
	int			m_nCntUninit;	// �����擾�������܂ł̎���

	bool	 m_bModelTexFlag;
	bool	 m_bCreateFlag;
	bool	 m_bTowardFlag;	// �ړI�̏ꏊ�Ɍ���������
	bool	 m_bSizeFlag;	// �T�C�Y�ω��̃t���O
	bool	 m_bUninitFlag;	// �I���t���O
	int m_nAnswerModelNum;	// �����̔ԍ�
	int m_nStockNum;

};

#endif
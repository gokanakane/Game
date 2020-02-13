//=============================================================================
//
// �������ԏ��� [time.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _POINT_H_
#define _POINT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;
class CBillNumber;
class CScene2D;
class CSceneBillBoard;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_POINT_NUM			(2)		// �^�C�}�[�̌���

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPoint : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPR_PLAYER,	// �v���C���[
		TYPE_CPU,		// �G
		TYPE_MAX
	}TYPE_CHARACTER;

	CPoint(int nPriority = 4, OBJTYPE objType = OBJTYPE_POINT);
	~CPoint();

	static CPoint *Create(int nID, int nNumPlayer, TYPE_CHARACTER type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TexPoint(int nTexData);

	//============================
	// �ݒ�@�擾�@�̊֐�
	//============================
	int GetPoint(void) { return m_nTotalPoint; }
	bool GetVision(int nNumPlayer) { return m_bDrawVision[nNumPlayer]; }
	int GetID(void) { return m_nID; }
	CSceneBillBoard *GetCrwon(void) { return m_pCrown; }

	void SetVision(int nNumPlayer, bool bFlag);

	//============================
	// ���Z�@���Z�@�̊֐�
	//============================
	void AddPoint(int nPoint);				// ���Z����
	void SubtractionPoint(int nPoint);		// ���Z����
	void RankLogoTex(int nWinNum);			// ���ʂ�TEX�ύX


private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData);
	void UIPosition(int nID);			// UI�̈ʒu�܂Ƃ�
	void PointPostion();				// �|�C���g�̈ʒu�܂Ƃ�
	void SizeChange(void);				// �������̃T�C�Y�ύX
	void RankPos(void);					// ���ʂ̈ʒu�܂Ƃ�
	void ChangeRank(void);				// ���ʓ���ւ�菈��
	void ConfirmDirecting(D3DXVECTOR2 size);		// �m�艉�o

	CBillNumber *m_apNumber[MAX_POINT_NUM];	// �i���o�[�ւ̃|�C���^
	int m_nTotalPoint;							// �g�[�^���̃|�C���g
	int						m_nPointNum;		// �|�C���g�̕\��������
	int						m_nNumPlayer;		// �l���ۊ�
	int						m_nID;				// �����̔ԍ�
	int						m_nCount;			// �񌅖ڂɍs�����̃J�E���g
	int						m_nWinNum;			// �����_�ł̏�����
	int						m_nCntbConfirm;		// �m��̎��ԃJ�E���g
	int						m_nCountNum;			// �J�E���g
	float					m_fPosOld;
	bool					m_bStart;
	bool					m_bSizeChange;		// �|�C���g�������̃T�C�Y�ύX
	bool					m_bColChange;		// �F�̐ؑ�
	bool					m_bChangeFlag;		// �ؑփt���O
	bool					m_bFlag;
	bool					m_bRankChangeFlag;	// ���ʓ���ւ����̃t���O
	bool					m_bFlag001;
	bool					m_bConfirmFlag;		// ���ʊm��t���O
	bool					m_bDrawVision[MAX_PLAYER];		// �`��t���O
	D3DXVECTOR3				m_pos;				// �ʒu
	D3DXVECTOR3				m_RnakSize;			// ���ʂ̃T�C�Y
	CScene2D				*m_pIcon;			// �v���C���[�A�C�R��
	CScene2D				*m_pRank;			// ���ʂ̃��S
	CSceneBillBoard			*m_pCrown;			// ����
	TYPE_CHARACTER			m_type;				// ���
	CSceneBillBoard			*m_pDouble;			// 2�{�̕\��

	D3DXVECTOR2				m_TexMin, m_TexMax;	// �e�N�X�`�����W�ۑ�
};
#endif

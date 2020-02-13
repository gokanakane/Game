//=============================================================================
//
// �������ԏ��� [tutotime.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _TUTOTIME_H_
#define _TUTOTIME_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;
class CBillNumber;
class CSceneBillBoard;
class CPlayer;
class CScene2D;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTOTIME_MAX		(2)		// �^�C�}�[�̌���
#define PLAYER_MAX			(4)		// �v���C���[�ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTutoTime : public CScene
{
public:
	CTutoTime(int nPriority = 6, OBJTYPE objType = OBJTYPE_TUTOTIME);
	~CTutoTime();

	static CTutoTime *Create(int nNumPlayer);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TexTime(int nTexData, int nTimeOne);

	//============================
	// �ݒ�@�擾�@�̊֐�
	//============================
	static int GetTime(void) { return m_nTime; };
	static void AddTime(int nTime);
	static bool GetTimeFlag(void) { return m_bCountFlag; };
	static void SetTimeFlag(bool bFlag) { m_bCountFlag = bFlag; };
	static int GetSatgeNum(void) { return m_nStageNum; }		// �X�e�[�W�`�Ԃ̎擾
private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData, int nOperation);
	void ChangeStage(void);				// �X�e�[�W���؂�ւ�邱�Ƃ�m�点�鉉�o
	void DefaultCol(void);				// �����Ȃǂ�default�̐F�ɖ߂�
	void CountDown(void);				// �J�E���g�_�E��


	CNumber *m_apNumber[TUTOTIME_MAX][PLAYER_MAX];			// �i���o�[�ւ̃|�C���^
	static int				m_nTime;			// ����
	static int				m_nTimeCount;		// ���Ԃ̃J�E���^
	static int				m_nTimeOld;
	static int				m_nTimeOne;
	static int				m_nStageNum;
	int						m_nTimeNum;			// ���Ԃ̕\��������
	int						m_nWaitTime;		// �Q�[���I�����̑҂�����
	int						m_nNumPlayer;		// �l���ۊ�
	bool					m_bStart;
	D3DXVECTOR3				m_pos;				// �ʒu
	CScene2D				*m_pScene2D[PLAYER_MAX];		// 2D�|���S���ւ̃|�C���^

	static bool m_bCountFlag;			//���Ԃ��J�E���g���邩
};
#endif

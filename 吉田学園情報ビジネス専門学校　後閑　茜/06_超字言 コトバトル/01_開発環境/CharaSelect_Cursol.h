//=============================================================================
//
// �L�����Z���N�g�̃J�[�\������ [CharaSelect_Cursol.h]
// Author : �ڍ�������/��Ո�
//
//=============================================================================
#ifndef _CHARASELECT_CURSOL_H_
#define _CHARASELECT_CURSOL_H_

#include "scene2D.h"
#include "CharaSelect.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CPlayer;
class CFade;
class CManager;
class CCharaSelect;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCharaSelCursol : public CScene2D
{
public:
	CCharaSelCursol();
	~CCharaSelCursol();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCharaSelCursol *Create(int nId);

	CCharaSelect::SELECT_STATE GetSelectState() { return m_SelectState; }
	CPlayer::PLAYER_TYPE GetPlayerType() { return m_CharaType; }
	CPlayer::PLAYER_TYPE GetPlayerTypeOld() { return m_CharaTypeOld; }
	bool GetSelMove(void) { return m_bPCSelMove; }
	CScene2D *GetpBadge(void) { return this->m_apBadge2D; }
	CScene2D *GetpCursor(void) { return this->m_apCursor2D; }

private:
	void Initpointer(void);																						//�|�C���^�̏�����
	void InitCharaSelectPoly(void);																				//�|�C���^�̏�����
	void PressGauge(CFade *pFade, CManager *pManager, int operation);											//�߂�{�^�������Ă鎞�̃Q�[�W
	void SetCommand(void);																						//�R�}���h�ݒ�
	void Move(CFade *pFade, CManager *pManager, int nControllNum);												//�ړ�/�I������
	D3DXVECTOR3 MoveRestriction(D3DXVECTOR3 pos);																//�ړ�����
	void Set(int nId);

	CScene2D *m_apCursor2D;								//�J�[�\��
	CScene2D *m_apBadge2D;								//�o�b�W
	CScene2D *m_apGauge2D;								//�߂鎞�̃Q�[�W
	CPlayerSelect::SELECTPLAYER *m_PlayerNum;			//�v���C���[�̐l��
	float m_fGaugeSizeX;								//�߂�Q�[�W�̒�����ۊ�
	float m_fMaxGaugeX;									//�Q�[�W�̍ő�̒���
	int m_nCntGauge;									//�Q�[�W���������Ԃ��Ǘ�
	int m_nId = 0;										//ID
	CPlayer::PLAYER_TYPE m_CharaType;					//�I�΂ꂽ�L�����̎��
	CPlayer::PLAYER_TYPE m_CharaTypeOld;				//�O��I�΂ꂽ�L�����̎��
	CCharaSelect::SELECT_STATE m_SelectState;			//���o�̏��
	CCharaSelect::SELECT_STATE m_SelectStateold;		//�O��̉��o��Ԃ��L�^
	D3DXVECTOR3 m_move;									//�ړ���
	D3DXVECTOR3 m_pos;									//�ړ���
	bool m_bPCSelMove;									//�I�΂�Ă��Ȃ����݈̂ړ��ł���
	bool m_bPlayer;										//�v���C���[���ǂ�������
};
#endif
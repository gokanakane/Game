//=============================================================================
//
//				�X�R�A�̏���[score.h]
//				Auther : Shun Yokomichi
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene.h"		// �V�[��
#include "number.h"		// ����

//*****************************************************************************
//				�}�N����`
//*****************************************************************************
#define MAX_SCORE		(6)		// �����̍ő吔

//*****************************************************************************
//				�N���X��`(�X�R�A)
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore();
	~CScore();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetScore(void);		// �X�R�A�̎擾

	// �ÓI�����o�֐�
	static CScore *Create();			// ����
	static void SetScore(int nScore);	// �X�R�A�̐ݒ�
	static void AddScore(int nValue);	// �X�R�A�̉��Z

private:
	// �ÓI�����o�ϐ�
	static CNumber2D *m_apNumber[MAX_SCORE];		// �X�R�A�̍ő包��
	static int m_nScore;
};
#endif

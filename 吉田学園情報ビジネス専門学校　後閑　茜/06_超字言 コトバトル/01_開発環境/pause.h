//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
//#define
//=============================================================================
// �N���X��`
//=============================================================================
class CPause : public CScene
{
public:
	CPause();
	CPause(int nPriority = 7);
	~CPause();

	static CPause* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CScene2D* m_pBG;			//�|�[�Y�̔w�i�p
	CScene2D* m_pPause;		   //�|�[�Y�̕����\���p�̃|���S��
	CScene2D* m_apSelectMenu[4];//�|�[�Y���j���[�p�̃|���S��
	D3DXVECTOR3 m_aMenuDefaultPos[4];
	int m_nSelect;		//�Z���N�g���j���[���p�̕ϐ�
};
#endif // !_PAUSE_H_

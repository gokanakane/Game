//=============================================================================
//
// �^�C�g������ [select.h]
// Author : �ڍ� ������
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "scene.h"


//�O���錾

//�N���X�i�V�[��2D�̔h���N���X�j
class CSelect
{
public:
	CSelect();
	~CSelect();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSelect *Create(void);

	//�����o�ϐ�
private:
	int m_nTimer;		//�I���^�C�}�[���Z

#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif
};
#endif
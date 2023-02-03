//=============================================================================
//
// �x�[�X�V�[������ [base.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _BASE_H_
#define _BASE_H_

#include "renderer.h"

//-----------------------------------------------------------------------------
// �x�[�X�N���X(��{�N���X)
//-----------------------------------------------------------------------------
class CBase
{
public:
	enum EBase
	{// �V�[���̎��
		BASE_NONE = 0,
		BASE_TITLE,
		BASE_GAME,
		BASE_RESULT,
		BASE_MAX
	};

	CBase();
	virtual ~CBase();

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

	void SetType(EBase type) { m_type = type; }
	EBase GetType() { return m_type; }

private:
	// �V�[���̎��
	EBase m_type;
};

#endif

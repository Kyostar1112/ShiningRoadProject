#pragma once

#include "PartsBase.h"

//�A�Z���u���V�[���̃��f������.
class clsASSEMBLE_MODEL
{
public:
	clsASSEMBLE_MODEL();
	~clsASSEMBLE_MODEL();

	void Create();

private:

	//�p�[�c�̐����̃|�C���^.
	clsPARTS_BASE**	m_wppParts;
	UCHAR			m_ucPartsMax;

};


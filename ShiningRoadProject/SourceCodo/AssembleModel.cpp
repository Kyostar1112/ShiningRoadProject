#include "AssembleModel.h"


clsASSEMBLE_MODEL::clsASSEMBLE_MODEL() :
	m_pPartsFactory( nullptr ),
	m_wppParts( nullptr )
{
	m_ucPartsMax = static_cast<UCHAR>( enPARTS::MAX );
}

clsASSEMBLE_MODEL::~clsASSEMBLE_MODEL()
{
	if( m_wppParts != nullptr ){
		for( UCHAR i=0; i<m_ucPartsMax; i++ ){
			m_wppParts[i] = nullptr;
		}
		delete[] m_wppParts;
		m_wppParts = nullptr;
	}
	m_ucPartsMax = 0;
	SAFE_DELETE( m_pPartsFactory );
}


void clsASSEMBLE_MODEL::Create()
{
	m_pPartsFactory = new clsFACTORY_PARTS;
	m_wppParts = new clsPARTS_BASE*[m_ucPartsMax];
}


#include "FactoryScene.h"



clsFACTORY::clsFACTORY( clsPOINTER_GROUP* const ptrGroup )
{

}

clsFACTORY::~clsFACTORY()
{
}


//�O����g���K��.
clsSCENE_BASE* clsFACTORY::Create( 
	const enSCENE enScene )
{
	clsSCENE_BASE* pScene = CreateProduct( enScene );
	return pScene;
}





//�V�[���̃t�@�N�g��.

clsSCENE_FACTORY::clsSCENE_FACTORY( clsPOINTER_GROUP* const ptrGroup ) : clsFACTORY( ptrGroup ) ,
	m_wpPtrGroup( ptrGroup )
{

}
clsSCENE_FACTORY::~clsSCENE_FACTORY()
{
	m_wpPtrGroup = nullptr;
}


//���g.
clsSCENE_BASE* clsSCENE_FACTORY::CreateProduct( 
	const enSCENE enScene )
{
	//�w�肳�ꂽ�V�[��������ēf���o��.
	switch( enScene )
	{
	case enSCENE::TITLE:
		return new clsSCENE_TITLE( m_wpPtrGroup );
		break;
	case enSCENE::ASSEMBLE:
		return new clsSCENE_ASSEMBLE( m_wpPtrGroup );
		break;
	case enSCENE::MISSION:
		return new clsSCENE_MISSION( m_wpPtrGroup );
		break;
	case enSCENE::ENDING:
		return new clsSCENE_ENDING( m_wpPtrGroup );
		break;
	case enSCENE::GAMEOVER:
		return new clsSCENE_GAME_OVER( m_wpPtrGroup );
		break;
	default:
		assert( !"�s���ȃV�[�����w�肳��܂���" );
		break;
	}
	return nullptr;
}
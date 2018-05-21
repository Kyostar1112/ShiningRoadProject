#ifndef MY_MACRO_H_	//�C���N���[�h�K�[�h.
#define MY_MACRO_H_


#include <assert.h>

//============================================================
//	�}�N��.
//============================================================

//�G���[���b�Z�[�W.
#define ERR_MSG(str,title)	{MessageBox(NULL,str,title,MB_OK);}

//���.
#define SAFE_RELEASE(x)		{ if(x) {(x)->Release();(x)=nullptr; } }
#define SAFE_DELETE(p)		{ if(p) { delete (p);   (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p){ if(p) { delete[] (p); (p)=nullptr; } }

//�L�[�{�[�h����.
//�����Ă����.
#define GETKEY_STAY(x) if (GetAsyncKeyState(x) & 0x8000)
//�������Ƃ�����.
#define GETKEY_DOWN(x) if (GetAsyncKeyState(x) & 0x0001)


//----- Tahara 2018 04/18 11:38 -----.
////�ϐ����𕶎����.
//#define TO_STRING(VariableName) # VariableName



//null�ɃA�T�[�g���o��.
#define ASSERT_IF_NULL(p){ \
	if( p == nullptr ){ \
		assert( p ||! "��null�ł���" "( ||! �͋C�ɂ��Ȃ��ł�������)");\
	}\
}
//	{ assert( !( p == nullptr ) ); }//null�̎��Ɉ���������.

//null����Ȃ��ꍇ�ɃA�T�[�g���o��.
#define ASSERT_IF_NOT_NULL(p){ \
	if( p != nullptr ){ \
		assert( p ||! "��null����Ȃ��ł���" "( ||! �͋C�ɂ��Ȃ��ł�������)");\
	}\
}
//	{ assert( !( p != nullptr ) ); }//null����Ȃ����Ɉ���������.



//null�`�F�b�N.
#define RETURN_IF_NULL(p) \
	{ ASSERT_IF_NULL( p ); return; }//null�Ȃ�A�T�[�g�o���ă��^�[��.

//null����Ȃ����`�F�b�N.
#define RETURN_IF_NOT_NULL(p) \
	{ ASSERT_IF_NOT_NULL( p ); return; }//null����Ȃ��Ȃ�A�T�[�g�o���ă��^�[��.
//----- end -----.



#endif//#ifndef MY_MACRO_H_
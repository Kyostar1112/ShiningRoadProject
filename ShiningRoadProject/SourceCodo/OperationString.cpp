#include "OperationString.h"

using namespace std;

clsOPERATION_STRING::clsOPERATION_STRING()
{
}

clsOPERATION_STRING::~clsOPERATION_STRING()
{
}



//数字と連結.
//連結 : consolidated.
string clsOPERATION_STRING::ConsolidatedNumber( const string& s, const int num ) const
{
	return ConsolidatedNumberProduct( s, num );
};

string clsOPERATION_STRING::ConsolidatedNumber( const string& s, const unsigned int num ) const
{
	return ConsolidatedNumberProduct( s, num );
};

string clsOPERATION_STRING::ConsolidatedNumber( const string& s, const short num ) const
{
	return ConsolidatedNumberProduct( s, num );
};

string clsOPERATION_STRING::ConsolidatedNumber( const string& s, const unsigned short num ) const
{
	return ConsolidatedNumberProduct( s, num );
};

string clsOPERATION_STRING::ConsolidatedNumber( const string& s, const char num ) const
{
	return ConsolidatedNumberProduct( s, num );
};

string clsOPERATION_STRING::ConsolidatedNumber( const string& s, const unsigned char num ) const
{
	return ConsolidatedNumberProduct( s, num );
};


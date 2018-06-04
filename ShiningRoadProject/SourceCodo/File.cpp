#include "File.h"

using namespace std;

const unsigned int uiRESERVE_SIZE_ROW = 64;//�x�N�^�[�̏����ő�T�C�Y( �s ).
const unsigned int uiRESERVE_SIZE_COL = 16;//�x�N�^�[�̏����ő�T�C�Y( �s�̃J���}��؂�̐� ).

const char cDELIMITER = ',';//��؂蕶��.
	
const string sERROR = "THIS_IS_ERROR";//�G���[�p������.

//�������p�f�[�^�쐬( �v�b�V���o�b�N�p ).
const vector<string> vsINIT_LINE;


clsFILE::clsFILE() :
	m_bUsing( false )
{
}

clsFILE::~clsFILE()
{
	Close();
}


void clsFILE::Open( string sFileName )
{
	assert( !m_bUsing );//�g�p����open�����.

	m_sFileName = sFileName;

	//�������m��.
	m_vvsData.reserve( uiRESERVE_SIZE_ROW );
//	for( unsigned int i=0; i<m_vvsData.size(); i++ ){
//		m_vvsData[i].reserve( uiRESERVE_SIZE_COL );
//	}


	//�t�@�C�����J��.
	ifstream ifs( m_sFileName );
	{
		//open�`�F�b�N.
		if( !ifs ){
			cout << "�Ђ炯�Ȃ�������" << endl;
			cin.get();
			return;
		}

		string sBuff;
		unsigned int uiIndexRow = 0;
		//��s�Ât�@�C�����ׂĂ�ǂݍ���.
		while( true )
		{
			//�t�@�C���̏I�[�܂ŗ�����I��.
			if( ifs.eof() ){
				break;
			}
			m_vvsData.push_back( vsINIT_LINE );
			m_vvsData[uiIndexRow].reserve( uiRESERVE_SIZE_COL );//�������m��.

			getline( ifs, sBuff );
			m_vvsData[uiIndexRow].push_back( "" );
			m_vvsData[uiIndexRow][0] = sBuff;
			m_vvsData[uiIndexRow] = Split( m_vvsData[uiIndexRow][0], cDELIMITER );

			m_vvsData[uiIndexRow].shrink_to_fit();

			uiIndexRow ++;
		}
	}

	m_vvsData.shrink_to_fit();

	m_bUsing = true;
}


void clsFILE::Close()
{
	for( unsigned int i=0; i<m_vvsData.size(); i++ ){
		m_vvsData[i].clear();
		m_vvsData[i].shrink_to_fit();
	}
	m_vvsData.clear();
	m_vvsData.shrink_to_fit();

	m_bUsing = false;
}



string clsFILE::GetDataString( const int iRow, const int iCol )
{
	if( !m_bUsing ){
		assert( m_bUsing );//�g�p������Ȃ���΃A�T�[�g.
		return sERROR;
	}
	//�͈͓�?.
	if( iRow >= static_cast<int>( m_vvsData.size() ) )			return sERROR;
	for( unsigned int i=0; i<m_vvsData.size(); i++ ){
		if( iCol >= static_cast<int>( m_vvsData[i].size() ) )	return sERROR;
	}
	//�}�C�i�X�͂͂���( ���G���[�l�ł͂Ȃ� ).
	if( iRow < 0 && iRow != MyFile::ERR_LINE )	return sERROR;
	if( iCol < 0 && iCol != MyFile::ERR_LINE )	return sERROR;


	//�S����Ԃ�.
	if( iRow == MyFile::ERR_LINE ){
		string sData;
		//�S���A��.
		for( unsigned int i=0; i<m_vvsData.size(); i++ ){
			for( unsigned int j=0; j<m_vvsData[i].size(); j++ ){
				sData += m_vvsData[i][j];
			}
		}
		return sData;
	}

	//�w��s��Ԃ�.
	if( iCol == MyFile::ERR_LINE ){
		string sData;
		//��s�A��.
		for( unsigned int i=0; i<m_vvsData[iRow].size(); i++ ){
			sData += m_vvsData[iRow][i];
		}
		return sData;
	}

	//�w�蕔����Ԃ�.
	return m_vvsData[iRow][iCol];
}

int clsFILE::GetDataInt(
	const int iRow, 
	const int iCol )
{
	string sBuff = GetDataString( iRow, iCol );//������擾.	

	if( sBuff == sERROR ){
		return 0;	
	}

	int iNum = stoi( sBuff );			//������𐔎��ɂ���.
	return iNum;
}

float clsFILE::GetDataFloat(
	const int iRow, 
	const int iCol )
{
	string sBuff = GetDataString( iRow, iCol );//������擾.	

	if( sBuff == sERROR ){
		return 0;	
	}

	float fNum = stof( sBuff );			//������𐔎��ɂ���.
	return fNum;
}

double clsFILE::GetDataDouble(
	const int iRow, 
	const int iCol )
{
	string sBuff = GetDataString( iRow, iCol );//������擾.	

	if( sBuff == sERROR ){
		return 0;	
	}

	double dNum = stod( sBuff );			//������𐔎��ɂ���.
	return dNum;
}


//�����񕪊��ǂݍ���( �������͋�؂蕶�� ).
vector< string > clsFILE::Split( const std::string &sStr, char cSep )
{
	vector< string > vsOut;
	stringstream ss( sStr );
	string sBuff;

	vsOut.reserve( uiRESERVE_SIZE_COL );

	while( std::getline( ss, sBuff, cSep ) ){
		vsOut.push_back( sBuff );
	}
//	vsOut.pop_back();

	vsOut.shrink_to_fit();

	return vsOut;
}


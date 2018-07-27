#include "MusicFile.h"

wistream& operator>>(wistream& is, MusicFile& mf)
{
	return is >> mf.strFileName >> mf.strFileSite;
}
MusicFile::MusicFile(const wstring& strFileSite, const wstring& strFileName) :strFileSite(strFileSite), strFileName(strFileName), SID(0)
{

}
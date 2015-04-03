#ifndef _baseerror_H
#define _baseerror_H

#include <string.h>

class CBaseError
{
public:
	CBaseError()
	{
		bzero(m_errbuf,sizeof(m_errbuf));
	}

	const char * getErr() const  { return m_errbuf;  }

	int setError(const char * fmt,...);

protected:
	char m_errbuf[1024];
};



























#endif


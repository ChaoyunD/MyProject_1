#include "RespondFactory.h"

RespondFactory::RespondFactory()
{
	m_flag = false;
}

RespondFactory::RespondFactory(RespondMsg * msg)
{
	m_flag = true;
	m_respond = msg;
}

RespondFactory::~RespondFactory()
{
	if (m_respond != NULL)
	{
		delete m_respond;
	}
}

Codec * RespondFactory::createCodec()
{
	if (m_flag == true)
	{
		return new RespondCodec(m_respond);
	}
	else
	{
		return new RespondCodec();
	}
}

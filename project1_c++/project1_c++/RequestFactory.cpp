#include "RequestFactory.h"

RequestFactory::RequestFactory()
{
	m_flag = false;
}

RequestFactory::RequestFactory(RequestMsg * msg)
{
	m_flag = true;
	m_request = msg;
}

RequestFactory::~RequestFactory()
{
	if (m_request != NULL)
	{
		delete m_request;
	}
}

Codec * RequestFactory::createCodec()
{
	if (m_flag)
	{
		return new RequestCodec(m_request);
	}
	else
	{
		return new RequestCodec();
	}
}

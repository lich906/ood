#pragma once

#include <iostream>
#include <sstream>

class CaptureStdoutOutput
{
public:
	CaptureStdoutOutput()
		: m_stdoutBuff(std::cout.rdbuf())
	{
		std::cout.rdbuf(m_oss.rdbuf());
	}

	std::string operator()()
	{
		auto content = m_oss.str();
		m_oss.str("");
		return content;
	}

	~CaptureStdoutOutput()
	{
		std::cout.rdbuf(m_stdoutBuff);
	}

private:
	std::streambuf* m_stdoutBuff;
	std::ostringstream m_oss;
};

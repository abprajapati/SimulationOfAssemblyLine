
#include "Utilities.h"
using namespace std;

namespace sdds 
{
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const 
	{
		return m_widthField;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

    void Utilities::setDelimiter(char newDelimiter) 
	{
		m_delimiter = newDelimiter;
	}
    
	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
	{
		string recordToken{};

		if (str[next_pos] != m_delimiter)
		{
			size_t next_delimeter_pos = str.find(m_delimiter, next_pos + 1);
			recordToken = str.substr(next_pos, next_delimeter_pos - next_pos);
			next_pos = recordToken.size() + next_pos + 1;
			if ((next_pos - 1) != str.length())
			{
				more = true;
			}
			else
			{
				more = false;
			}
			if (m_widthField < recordToken.size())
			{
				setFieldWidth(recordToken.size());
			}

		}
		else 
		{
			more = false;
			throw string("output error!");

		}

		return recordToken;
	}
}
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>

namespace sdds 
{
	class Utilities 
	{
		size_t m_widthField = 1;
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		static char getDelimiter();
		static void setDelimiter(char newDelimiter);
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	};
}

#endif // !SDDS_UTILITIES_H


#include "Station.h"
#include <iomanip>

using namespace std;

namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const string& info)
	{
		id_generator++;
		stationId = id_generator;

		size_t nextPosition = 0;
		bool record = false;
		string temp = info;

		nameOfItem = m_utilities.extractToken(temp, nextPosition, record);
		serialNum = stoi(m_utilities.extractToken(temp, nextPosition, record));
		numOfItemsInStock = stoi(m_utilities.extractToken(temp, nextPosition, record));

		if (Station::m_widthField < m_utilities.getFieldWidth())
		{
			Station::m_widthField = m_utilities.getFieldWidth();
		}
		stationDescrip = m_utilities.extractToken(temp, nextPosition, record);
	}

	const std::string& Station::getItemName() const
	{
		return nameOfItem;
	};


	void Station::updateQuantity()
	{
		if ( numOfItemsInStock - 1 >= 0)
		{
			numOfItemsInStock = numOfItemsInStock - 1;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		if (full == false)
		{
			os << right << "[";
			os.fill('0');
			os.width(3);
			os << stationId << "]" << " Item: ";
			os.width(m_widthField);
			os << left;
			os.fill(' ');
			os << nameOfItem << " [";
			os.width(6);
			os << right;
			os.fill('0');
			os << serialNum << "]" << endl;
		}
		else
		{
			os << right;
			os << "[";
			os.fill('0');
			os.width(3);
			os << stationId;
			os << "]" << " Item: ";
			os.width(m_widthField);
			os << left;
			os.fill(' ');
			os << nameOfItem << " [";
			os.width(6);
			os << right;
			os.fill('0');
			os << serialNum << "]" << " Quantity: ";
			os.width(m_widthField);
			os << left;
			os.fill(' ');
			os << numOfItemsInStock << " Description: " << stationDescrip << endl;
		}
	}

	size_t Station::getQuantity() const
	{
		return numOfItemsInStock;
	}

	size_t Station::getNextSerialNumber()
	{
		return serialNum++;
	}

}
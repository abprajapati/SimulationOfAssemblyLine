
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
#include "Utilities.h"

namespace sdds
{
	class Station 
	{
		int stationId = 0;
		std::string stationDescrip;
		std::string nameOfItem;
		unsigned int numOfItemsInStock;
		unsigned int serialNum;
		static size_t m_widthField;
		static size_t id_generator;
		Utilities m_utilities;
	public:
		Station(const std::string&);
		const std::string& getItemName() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
		size_t getQuantity() const;
		size_t getNextSerialNumber();	
	};
}
#endif // !SDDS_STATION_H

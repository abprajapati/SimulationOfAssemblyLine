#include "CustomerOrder.h"
#include <algorithm>
#include <iomanip>

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() 
	{
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	};

	CustomerOrder::CustomerOrder(const CustomerOrder&)
	{
		throw "Exception Occured!";
	};

	CustomerOrder::CustomerOrder(const std::string& string) 
	{
		size_t recordNext = 0;
		bool record = true;
		Utilities utility;

		try {
			m_name = utility.extractToken(string, recordNext, record);
			m_product = utility.extractToken(string, recordNext, record);
			m_cntItem = std::count(string.begin(), string.end(), utility.getDelimiter()) - 1;
			m_lstItem = new Item * [m_cntItem];
			size_t i = 0;
			while (i < m_cntItem)
			{
				m_lstItem[i] = new Item(utility.extractToken(string, recordNext, record));
				i++;
			};
			m_widthField = std::max(utility.getFieldWidth(), m_widthField);
		}
		catch (std::string& massage) 
		{
			std::cout << massage;
		}

	};

	CustomerOrder::CustomerOrder(CustomerOrder&& object)noexcept 
	{
		m_lstItem = new Item * [object.m_cntItem + 1];
		*this = std::move(object);
	};

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& object)noexcept
	{
		if (this != &object)
		{
			if (m_name != "")
			{
				for (size_t i = 0; i < m_cntItem; i++)
				{
					delete m_lstItem[i];
				}
			}
			delete[] m_lstItem;
			this->m_name = object.m_name;
			this->m_product = object.m_product;
			m_lstItem = new Item * [object.m_cntItem + 1];
			for (size_t i = 0; i < object.m_cntItem; i++)
			{
				this->m_lstItem[i] = object.m_lstItem[i];
			}
			this->m_widthField = object.m_widthField;
			this->m_cntItem = object.m_cntItem;
			object.m_cntItem = 0;
			for (size_t i = 0; i < object.m_cntItem; i++)
			{
				object.m_lstItem[i] = nullptr;
			}
			object.m_name = "";
			object.m_product = "";
		}
		return *this;
	};
	
	CustomerOrder::~CustomerOrder() 
	{
		if (m_lstItem != nullptr) 
		{
			size_t i = 0;
			while ( i < m_cntItem)
			{
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
				i++;
			};
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	};

	bool CustomerOrder::isFilled() const 
	{
		bool record = true;
		size_t i = 0; 
		while (i < m_cntItem)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				record = false;
			}
			i++;
		}
		return record;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		size_t i = 0;
		while (i < m_cntItem)
		{
			if (station.getItemName() == m_lstItem[i]->m_itemName && station.getQuantity() > 0)
			{
				station.updateQuantity();
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				os << "    Filled " << m_name;
				os << ", " << m_product;
				os << " [" << m_lstItem[i]->m_itemName;
				os << ']' << std::endl;
			}
			else if (station.getItemName() == m_lstItem[i]->m_itemName)
			{
				os << "    Unable to fill " << m_name;
				os << ", " << m_product;
				os << " [" << m_lstItem[i]->m_itemName;
				os << ']' << std::endl;
			}
			i++;
		};
	};

	bool CustomerOrder::isItemFilled(const std::string& itemName) const 
	{
		bool record = true;
		size_t i = 0; 
		while (i < m_cntItem)
		{
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
			{
					record = false;
			}
			i++;
		};
		return record;
	}

	void CustomerOrder::display(std::ostream& os) const 
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) 
		{

			os << "[" << std::setw(6) << std::right << std::setfill('0');
			os << m_lstItem[i]->m_serialNumber;
			os << "] ";
			os << std::setw(m_widthField) << std::left << std::setfill(' ');
			os << m_lstItem[i]->m_itemName;
			if (m_lstItem[i]->m_isFilled) 
			{
				os << " - FILLED" << std::endl;
			}
			else
			{
				os << " - TO BE FILLED" << std::endl;
			}
		}
	};
}
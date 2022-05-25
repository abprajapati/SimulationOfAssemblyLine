
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include "Station.h"
#include "Utilities.h"
namespace sdds {

	class CustomerOrder {
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};
		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem;
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string&);
		CustomerOrder(const CustomerOrder&);
		CustomerOrder(CustomerOrder&&)noexcept;
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder& operator=(CustomerOrder&&)noexcept;
		~CustomerOrder();
		bool isFilled() const;
		void fillItem(Station& station, std::ostream& os);
		bool isItemFilled(const std::string& itemName) const;
		void display(std::ostream& os) const;
	};
}


#endif // !SDDS_CUSTOMERORDER_H

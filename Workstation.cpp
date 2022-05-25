
#include "Workstation.h"
namespace sdds 
{
	std::deque<CustomerOrder> pending{};
	std::deque<CustomerOrder> completed{};
	std::deque<CustomerOrder> incomplete{};


	Workstation::Workstation(const std::string& str) : Station(str) { m_pNextStation = nullptr; };

	void Workstation::fill(std::ostream& os) 
	{
		if (!m_orders.empty()) 
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() 
	{
		bool record = false;

		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0)
		    {
		        if (m_pNextStation != nullptr)
		        {
			   *m_pNextStation += std::move(m_orders.front());
			    m_orders.pop_front();
			    record = true;
		        }
		        else if (!m_orders.front().isFilled())
		        {
			    incomplete.push_back(std::move(m_orders.front()));
		        m_orders.pop_front();
			    record = true;
		        }
		        else if (m_orders.front().isFilled())
		        {
			    completed.push_back(std::move(m_orders.front()));
			    m_orders.pop_front();
			    record = true;
		        }
		    }
		}
		return record;
	};

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	};

	void Workstation::setNextStation(Workstation* station) 
	{
		if (m_pNextStation == station)
		{
			m_pNextStation = nullptr;
		}
		else
		{
			m_pNextStation = station;
		}
	};

	void Workstation::display(std::ostream& os) const 
	{
		os << getItemName();
		os << " --> ";
		if (m_pNextStation == nullptr) 
		{
			os << "End of Line";
		}
		else 
		{
			os << m_pNextStation->getItemName(); 
		}
		os << std::endl;
	};

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) 
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	};
}

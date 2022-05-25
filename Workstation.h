
#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds 
{
	extern std::deque<CustomerOrder>pending;
	extern std::deque<CustomerOrder>completed;
	extern std::deque<CustomerOrder>incomplete;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};
	public:
		Workstation(const std::string&);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		Workstation* getNextStation() const;
		void setNextStation(Workstation* station);
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
		Workstation(Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&) = delete;
		Workstation& operator=(Workstation&&) = delete;
	};
}

#endif 

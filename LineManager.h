
#ifndef LINEMANAGER_H_
#define LINEMANAGER_H_

#include <vector>
#include "Workstation.h"

namespace sdds {
	class LineManager {
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder;
		Workstation* m_firstStation;
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		bool run(std::ostream& os);
		void linkStations();
		void display(std::ostream& os) const;
		};
}

#endif
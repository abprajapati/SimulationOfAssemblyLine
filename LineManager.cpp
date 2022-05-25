
#include "LineManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

namespace sdds {

	void LineManager::linkStations()
	{
		std::vector<Workstation*> tempStation{};
		Workstation* v_cStation;
		v_cStation = m_firstStation;

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws1) 
			{
			if (v_cStation)
			{
				tempStation.push_back(v_cStation);
				v_cStation = v_cStation->getNextStation();
			}
			});
		activeLine = tempStation;
	}

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) 
	{
		try
		{
			bool info = false;
			std::string mString, fRec, sRec;
			std::fstream fs(file);
			Utilities m_util;
			m_firstStation = nullptr;
			m_cntCustomerOrder = pending.size();

			while (getline(fs, mString))
			{
				size_t pos = 0;
				fRec = m_util.extractToken(mString, pos, info);

				if (!info)
				{
					sRec = "";
				}
				else
				{
					sRec = m_util.extractToken(mString, pos, info);
				}

				std::for_each(stations.begin(), stations.end(), [&](Workstation* ws1)
					{
						if (ws1->getItemName() == fRec)
						{
							std::for_each(stations.begin(), stations.end(), [&](Workstation* ws2)
								{
									if (ws2->getItemName() == sRec) ws1->setNextStation(ws2);
								});
							activeLine.push_back(ws1);
						}
					});
			}
			m_firstStation = activeLine.front();
		}
		catch (...)
		{
			std::cerr << "An Error Occurred!!";
		}
	}

	bool LineManager::run(std::ostream& os) 
	{
		static size_t valid = 1;
		bool record = false;
		size_t bOrder = completed.size() + incomplete.size();
		os << "Line Manager Iteration: " << valid << std::endl;
		if (!pending.empty()) 
		{
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) {
			w->fill(os);
			});
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) {
			w->attemptToMoveOrder();
			});
		size_t aOrder = completed.size() + incomplete.size();
		m_cntCustomerOrder -= (aOrder - bOrder);
		if (m_cntCustomerOrder <= 0)
		{
			record = true;
		}
		valid++;

		return record;
	}

	void LineManager::display(std::ostream& os) const 
	{
		std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* ws) {
			ws->display(os); });
	}
}

#pragma once
#include <string>
#include <map>
#include <list>
namespace DK{
	class dkCmdline {
	private:
		using curCLTy = std::list<std::string>;
		using curCLPoint = curCLTy::iterator;
		using curTable = std::map<std::string, curCLPoint>;
		
		void storeIntoTable(const std::string& key, curCLPoint& valuePoint);
		void parseEQExp(curCLPoint& pointer);

	public:

		void erase();
		void changeTable();
		void parse(int argc, const char* argv[]) {
			
		}
		
	};
}
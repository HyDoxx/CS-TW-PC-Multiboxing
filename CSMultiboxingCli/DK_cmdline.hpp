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

		std::list<std::string> helpPrint;
		curTable table;
		curCLTy cmdline;

		static const char* nullDir =
#ifdef WIN32
		"NUL";
#elif defined __linux
		"/dev/null";
#elif defined __unix
		"/dev/null";
#endif
		
		static FILE* NUL;
		void storeIntoTable(const std::string& key, curCLPoint& valuePoint) {
			static std::string temp;
			if(key[0] == '-' && key[1] == '-') {
				temp = key.data() + 2;
			}
			else if(key[0] == '-') {
				temp = key.data() + 1;
			}
			if(!temp.length()) {
				return;
			}
			if(table.find(temp) != table.end() && table.at(temp) == cmdline.end()) {
				table[temp] = valuePoint;
			}
		}
		
		void parseEQExp(curCLPoint& pointer) {
			std::string& curLine = *pointer;
			std::string temp{curLine, curLine.find_first_of('=') + 1};
			curLine.erase(curLine.find_first_of('='));
			auto newIt = cmdline.insert(pointer, temp);
			temp.clear();
			storeIntoTable(curLine, newIt);
		}

	public:
		dkCmdline() {
			
		}
		void erase();
		void changeTable();
		
		void addItem(const std::string& shortName = "", const std::string& longName = "", const std::string& describe = ""){
			if((table.find(shortName) == table.end()) || (table.find(longName) == table.end())){
				static std::string tempLine;
				if(shortName.length()) {
					tempLine.operator+=("-");
					tempLine += shortName;
					tempLine += '\0';
					table[shortName] = cmdline.end();
				}
				if(longName.length()) {
					tempLine.operator+=("--");
					tempLine += longName;
					tempLine += '\0';
					table[longName] = cmdline.end();
				}
				if (describe.length()) {
					tempLine += describe;
					tempLine += '\0';
				}
				helpPrint.push_back(tempLine);
				tempLine.clear();
			}
			else {
				
			}
		}
		
		void noHelp();
		void printHelp() {

		}
		
		const std::string& getItemValue(const std::string& name);
		
		void parse(int argc, const char* argv[]) {
			char temp[256];
			int i = 1;
			while (i < argc) {
				if (std::strlen(argv[i]) > 255) {
					return;
				}
				auto it = cmdline.insert(cmdline.end(), argv[i]);
				if (*(argv[i]) == '-' && *(argv[i] + 1) == '-') {
					if (sscanf_s(argv[i], "%[=]", temp, 255)) {
						parseEQExp(it);
					}
					else {
						
					}
				}
				else if (*(argv[i]) == '-') {
					if (argv[i][2] == '=') {
						parseEQExp(it);
					}
					else {
						
					}
				}
				else {
					return;
				}
				
			}
		}
	};
}
#include <iostream>
#include <fstream>
#include <sstream>
#include "Arena.h"


const int NUM_FILES = 5; // the total number of files to be read from

const std::string fileArray[NUM_FILES] = { "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt" }; // the string aray containing the file names

// This will take a string temp and an arena object and will execute an instruction from the string
// no return, but writes the results of the instruction into the ofs filestream
void parse_instruction(std::string temp, std::ofstream &ofs, Arena* aptr);

// This function is a platform independent way of reading files of various line ending types.
// It's definiton is at the bottom of the file, don't worry if you don't understand it.
namespace ta {
    std::istream& getline(std::istream& is, std::string& line);
}

// to determine whether or not to use abilities during a battle
// will begin as false, but can be set true by a certain instruction at the begining of the file
bool useAbilities;

int main() {

	for (int i = 0; i < NUM_FILES; i++) {
		std::ifstream ifs; // create the stream to read in from the files
		std::ofstream ofs; // create the output stream to write to an output file
		std::string temp; // used to store the current instruction
		Arena* aptr = new Arena();

		ifs.open(fileArray[i]); // open the file to read from
		ofs.open("out_" + fileArray[i]); // open the file to write to

		if (!ifs.is_open()) { // if the file did not open, there was no such file
			std::cout << "File " << i + 1 << " could not open, please check your lab setup" << std::endl;
		} else {
            std::cout << "Reading file" << i + 1 << ".txt..." << std::endl;
        }

		useAbilities = false;
		ta::getline(ifs, temp); // get the first instruction
		if (temp == "USE ABILITY") { // first line of file determines whether or not to use abilities during fights
			useAbilities = true;
            std::cout << "'useAbilities' flag set to true" << std::endl;
            std::cout << "Battles for file " << i << " will involve the 'useAbility()' and 'regenerate()' functions" << std::endl;
		}

		std::cout << "Beginning out_file" << i + 1 << ".txt write" << std::endl;
		while (ta::getline(ifs, temp)) { // while there are more instructions to get,
			parse_instruction(temp, ofs, aptr); // parse the instructions
		}
		std::cout << "File write complete" << std::endl << std::endl;
		delete aptr;
	}
	std::cout << "end" << std::endl; // indicate that the program has successfuly executed all instructions
	return 0;
}

void parse_instruction(std::string temp, std::ofstream &ofs, Arena* aptr) {
	std::string command, arg1, arg2;
	std::stringstream ss(temp);
	if (!(ss >> command)) { return; } // get command, but if string was empty, return
	if (command == "addFighter") { // comand to add a new fighter to the arena
		if (aptr->addFighter(ss.str().substr(10, std::string::npos))) { // use the rest of the stringstream as addFighter input
			ofs << temp << " Added" << std::endl;
		}
		else {
			ofs << temp << " Invalid" << std::endl;
		}
	}
	else if (command == "removeFighter") { // command to remove a fighter from the arena (given the fighters name)
		ss >> arg1; // get the name of the fighter to remove
		if (aptr->removeFighter(arg1)) {
			ofs << temp << " True" << std::endl;
		}
		else {
			ofs << temp << " False" << std::endl;
		}
	}
	else if (command == "getFighter") { // command to return a pointer to a fighter (given the name of the fighter)
		ss >> arg1; // get the name of the fighter to print
		FighterInterface* fptr = aptr->getFighter(arg1);
		if (fptr != NULL) {
			ofs << temp << std::endl << "  " << fptr->getName() << " " << fptr->getCurrentHP() << " " << fptr->getMaximumHP() << " " << fptr->getStrength() << " " << fptr->getSpeed() << " " << fptr->getMagic() << std::endl;
		}
		else {
			ofs << temp << " NULL" << std::endl;
		}
	}
	else if (command == "getSize") { // command to get the number of fighters in the arena
		ofs << temp << " " << aptr->getSize() << std::endl;
	}
	else if (command == "reset") {
		ss >> arg1; // get the name of the fighter to reset
		FighterInterface* fptr = aptr->getFighter(arg1);
		if (fptr != NULL) {
			fptr->reset();
			ofs << temp << " Success" << std::endl;
        }
		else {
			ofs << temp << " NULL" << std::endl;
		}
	}
	else if (command == "battle") { // command to print the results of a battle between two fighters
		ss >> arg1 >> arg2;
		FighterInterface *fptr1 = aptr->getFighter(arg1), *fptr2 = aptr->getFighter(arg2); // get the pointers to the two fighters who will be fighting
		if (fptr1 == NULL || fptr2 == NULL) { // if one of the fighters was not found, stop here
			ofs << temp << " Fighter not found" << std::endl;
			return;
		}
		// print the info about the fighters
		ofs << temp << std::endl;
		ofs << std::endl << "  " << fptr1->getName() << " " << fptr1->getCurrentHP() << " " << fptr1->getMaximumHP() << " " << fptr1->getStrength() << " " << fptr1->getSpeed() << " " << fptr1->getMagic();
		ofs << std::endl << "  " << fptr2->getName() << " " << fptr2->getCurrentHP() << " " << fptr2->getMaximumHP() << " " << fptr2->getStrength() << " " << fptr2->getSpeed() << " " << fptr2->getMagic() << std::endl;

		// while the fight has not ended (both fighters have positive HP)
		// fighters take turns attacking the opposing fighter
		// abilities and regenerate are used only if the useAbilities bool has been set
		// after each fighter deals damage, fighter info is printed out again
		while (fptr1->getCurrentHP() > 0 && fptr2->getCurrentHP() > 0) {
			int dmg;

			if (useAbilities) {
				fptr1->regenerate();
				fptr1->useAbility();
			}
			dmg = fptr1->getDamage();
			fptr2->takeDamage(dmg);

			if (fptr2->getCurrentHP() < 1) {
				ofs << std::endl << "  " << fptr1->getName() << " " << fptr1->getCurrentHP() << " " << fptr1->getMaximumHP() << " " << fptr1->getStrength() << " " << fptr1->getSpeed() << " " << fptr1->getMagic();
				ofs << std::endl << "  " << fptr2->getName() << " " << fptr2->getCurrentHP() << " " << fptr2->getMaximumHP() << " " << fptr2->getStrength() << " " << fptr2->getSpeed() << " " << fptr2->getMagic() << std::endl;
				return;
			}

			if (useAbilities) {
				fptr2->regenerate();
				fptr2->useAbility();
			}
			dmg = fptr2->getDamage();
			fptr1->takeDamage(dmg);

			ofs << std::endl << "  " << fptr1->getName() << " " << fptr1->getCurrentHP() << " " << fptr1->getMaximumHP() << " " << fptr1->getStrength() << " " << fptr1->getSpeed() << " " << fptr1->getMagic();
			ofs << std::endl << "  " << fptr2->getName() << " " << fptr2->getCurrentHP() << " " << fptr2->getMaximumHP() << " " << fptr2->getStrength() << " " << fptr2->getSpeed() << " " << fptr2->getMagic() << std::endl;

			if (fptr1->getCurrentHP() < 1) {
				return;
			}
		}
	}
	else { // invalid command, wrong input file format
        std::cout << "Command: \"" << command << "\"" << std::endl;
		std::cout << "Invalid command.  Do you have the correct input file?" << std::endl;
	}
}

// Version of getline which does not preserve end of line characters
namespace ta {
    std::istream& getline(std::istream& in, std::string& line) {
        line.clear();

        std::istream::sentry guard(in, true); // Use a sentry to maintain the state of the stream
        std::streambuf *buffer = in.rdbuf();  // Use the stream's internal buffer directly to read characters
        int c = 0;

        while (true) { // Continue to loop until a line break if found (or end of file)
            c = buffer->sbumpc(); // Read one character
            switch (c) {
                case '\n': // Unix style, return stream for further parsing
                    return in;
                case '\r': // Dos style, check for the following '\n' and advance buffer if needed
                    if (buffer->sgetc() == '\n') { buffer->sbumpc(); }
                    return in;
                case EOF:  // End of File, make sure that the stream gets flagged as empty
                    in.setstate(std::ios::eofbit);
                    return in;
                default:   // Non-linebreak character, go ahead and append the character to the line
                    line.append(1, (char)c);
            }
        }
    }
}

#ifndef SECTION_H
#define SECTION_H
#include <string>

class Section
{
public:
	Section();
	virtual std::string Type() = 0;
	virtual std::string To_string() = 0;

private:

};
#endif // !SECTION_H


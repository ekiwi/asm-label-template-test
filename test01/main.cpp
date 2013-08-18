#include <iostream>

extern "C" void defaultFunction(void) {
	std::cout << "defaultFunction called" << std::endl;
}

extern "C" void linktimeReplaceableFunction(void)	__attribute__ ((weak, alias("defaultFunction")));


int main() {
	linktimeReplaceableFunction();
}

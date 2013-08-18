#include <iostream>

// comment out to see working verson without using templates
#define USE_TEMPLATES

#if defined(USE_TEMPLATES)
// ----------------------------------------------------------------------------
// This should end up in a header file
template<void (*overwriteFunction)(void)>
class OverwriteTemplate
{
public:
	static void
	Function(void) __asm__("linktimeReplaceableFunction");
};

template<void (*overwriteFunction)(void)>
void
OverwriteTemplate<overwriteFunction>::Function(void)
{
	std::cout << "Function of OverwriteTemplate called" << std::endl;
	overwriteFunction();
}
// ----------------------------------------------------------------------------

void inline customOverwriteFunction()
{
	std::cout << "customOverwriteFunction called" << std::endl;
}

template class OverwriteTemplate<customOverwriteFunction>;

#else /* !defined(USE_TEMPLATES) */

void customOverwriteFunction() __asm__("linktimeReplaceableFunction");
void customOverwriteFunction()
{
	std::cout << "customOverwriteFunction without templates called" << std::endl;
}

#endif

# Test01

## Compile and Run

	make gcc				# compile using gcc/g++
	make clang				# compile using clang/clang++
	make symbols_overwrite	# show symbols generated for overwrite.cpp
	make symbols_main		# show symbols generated for main.cpp
	make symbols			# show symbols generated for both files
	make clean				# remove target and object files
	./test01				# execute test01

## main.cpp

In this file the function `linktimeReplaceableFunction` is declared
using the `extern "C"` keyword to avoid c++ style name mangling.
The `__attribute__ ((weak, alias("defaultFunction")))` tell the linker
to use the `defaultFunction` declared above in place of
`linktimeReplaceableFunction` if no other declaration of
`linktimeReplaceableFunction` is found.

In the main function, `linktimeReplaceableFunction` is called and the
program exits.


## overwrite.cpp

This file contains a preprocessor macro switch:
* If you remove the `#define USE_TEMPLATES` line: A `customOverwriteFunction`
  is declared and the compiler is told to use `linktimeReplaceableFunction`
  as a label for this function. Below the `customOverwriteFunction` is defined
  to output a string. This configuration works with both _gcc_ as well as
  _clang_. But this is not the purpose of this test.
* If you keep the `#define USE_TEMPLATES` line: A `OverwriteTemplate` template
  class is defined which accepts a function pointer as template parameter.
  This class gets one _static_ function called `Function` which the compiler
  is instructed to name `linktimeReplaceableFunction`.
  Below the `OverwriteTemplate<>::Function` is defined to output a string
  and call the function behind the function pointer handed to the template.
  Now a `customOverwriteFunction` which writes a string to _cout_ is declared
  and defined. Afterwards an instance of the `OverwriteTemplate` template
  class is explicitly instantiated.

## The outcome

Let's have a look at the output of `make symbols`:

_gcc_ seems to ignore the `__asm__` directive of the template function.
The `OverwriteTemplate<customOverwriteFunction>::Function` gets the default
symbol
`W _ZN17OverwriteTemplateIXadL_Z23customOverwriteFunctionvEEE8FunctionEv`.

_clang_ on the other hand labels the
`OverwriteTemplate<customOverwriteFunction>::Function` according to the
`__asm__` directive as `W linktimeReplaceableFunction`.
Unfortunately, since it is a template function it is labeld `W` for _weak_
and thus is not considered by the linker as an implementation of
`linktimeReplaceableFunction` from `main.cpp`.

Thus while _clang_ follows the `__asm__` directive, the goal of being able
to use a template to replace a function from a different object file at
link time was not attained.
However `test02` will explore a different way of reaching this goal using
_clang_'s apparent support for the `__asm__` directive in conjunction with
templates.

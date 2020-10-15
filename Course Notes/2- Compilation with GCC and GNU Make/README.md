# **In the name of Allah the Merciful**

# Week 2 - Compilation With GCC and GNU Make

## Week Objectives
> Implement a build system using GNU’s Make and GCC compiler toolsets <br>
> Examine the pre-processor's role in compilation <br>
> Integrate new libraries to a build system <br> 
> Write a makefile that can natively and cross compile an application <br>
> Generate preprocessor, assembly, object, dependency, executable, and map output files <br>

## Table of Contents
* [Introduction to Build Systems Using GNU Toolsets](#--)
* [Compiling and Invoking GCC](#--)
* [Preprocessor Directives](#--)
* [Creating Header and Implementation Files](#--)
* [Linkers](#--)
* [Make](#--)
* [Makefiles](#--)
* [Other Useful GNU Bin Tools](#--)

## Introduction to Build Systems Using GNU Toolsets
- To transform the code written in high level language to the executable form which is written in architecture specific machine code, we use various tools so that each one do its specific job.
- The tools that we use in this course are provided by *GNU's Compiler Collection (GCC)*, GNU bundles many useful compilation tools together, this is what we refer to as (toolchain)
- GCC was developed by a third party as free software. GCC suppports a wide array of architectures including ARM.
- This wide support is important for developers as it allows them to have some flexibility in their platform choice
- In this course, we will use the compiler toolchain on the Ubuntu Linux host machine, and we will investigate the steps of compilation.
![](Images/esDevPlatform.png)
![](Images/buildEnvironment.png)
![](Images/swTools.png)

- To install the code on the target platform, the high level language (mostly C) is translated into the architecture specific assembly language (which is the low level language), then the assembly is translated into the machine code which is the binary encoded assembly instructions.
- This machine code is what processors understand and use to perform their required jobs.
![](Images/buildingSW.png)

- The machine code is a binary represented encoded instructions, these instructions can be looked up in the processor's *instruction set architecture (ISA)*
- The compiler toolchain consists of:
  1. Preprocessor
  2. Compiler
  3. Assembler
  4. Linker
  5. Locator
  
![](Images/buildProcess.png)  

- Preprocessor takes the source and header files, transforms them to new files after evaluating the preprocessor directives and perform macros substitution, these files will be of extension *.i*. The preprocessor stage is nothing but text replacement.
- Then these files are fed into the compiler to translate the code from C language to Assembly language. The compiler output files are of extension *.s or .asm*
- After that, the assembly files are fed into the assembler to translate from assembly into object code which is not human readable. The assembler output files are of extension *.o*
- Now we have multiple object files, so we feed them to the linker in order to resolve all references (aka.: symbols) between object files, and combine all the *.o* files into a single executable file called *relocatable file*
- Finally, the relocatable file is fed into the locator which will map all the virtual addresses of code and data into the processor's physical memory space, and generates the final executable file which will be installed on the target.
- Once we compile a project, the executable will only work on the architecture we compiled for, so it can't run on other systems even on the host machine itself.
- The latter point leads us to compare between native compilation and cross compilation:
  > - Native compilation: it's when you compile your project for the same system you intend to run the executable on (e.g.: the programs that run on PC)
  > ![](Images/nativeCompilation.png)
  > - Cross compilation: is when you compile your project on a system that is intended to run on another system (this is our case in embedded systems). Here we need a hardware circuit to install the executable from the host machine to the target.
  > ![](Images/crossCompilation.png)
- We use cross compilation for embedded systems as the microcontroller doesn't have neither the operating system nor the resources for programs like GCC to be installed and perform the build process. Maybe some advanced machines such as the ARM cortex-A processors can have the resources to perform native compilation.
- We may not need an external HW circuit to install the executable on the target as the board may have an internal on-board programmer/debugger like the one in the following image:
 ![](Images/crossCompilation2.png)
 
 - Building large software projects can be tedious (boring) as managing a large number of files for compilation with all their respective compile options becomes very slow. That's why we need an automated way to manage this process.
 - GNU Make is a tool that controls the generation of executables and other non source files of the program, and helps us managing the whole process of building, specially for large projects.
 - Mastering how to use the build tools will prove immensly valuable in industry and in our own projects.
 
## Compiling and Invoking GCC
- In this lesson, we will use GCC to build the system through command line interface.
- Recall the GCC toolchain:
![](Images/toolchain.png)

- The preprocessor and compiler are invoked with the `gcc` command
- Assembler is invoked by the `as` command
- Linker and locator are invoked by the `ld` command
- However, we can perform the whole build process using the `gcc` command directly
- Many compiler toolchains can be installed on the host machine, we can list the installed toolchains using the command `ls -la /usr/bin/*gcc`
- The installed toolchains are named in a specific format:
  1. The architecture name
  2. The vendor name
  3. The OS name
  4. The Application Binary Interface (ABI)
- Consider the following example:
![](Images/gccToolCheck.png)

- The 2 ARM compilers listed in the image above are cross compilers for 2 different architecture targets, one of them is for an embedded system with a Linux OS installed and the other is for a bare-metal embedded target
- Note: bare-metal firmware means to write code directly to interface with hardware
- In the above image, we can also see a native compiler installed which is `gcc-4.8`
- We can see all the tools installed inside the cross-compiler toolchain (for example: arm-non-eabi toolchains) using the command `ls -la /usr/bin/arm-none-eabi*`
![](Images/compiler.png)
- Only one gcc compiler is activated although we may see many compilers are installed, to know which version of gcc is the activated version we type `gcc --version`
- The command `which gcc` tells you the location of installation of the activated gcc
- Regarding the assembler process, as we stated before, the assembler converts the assembly instruction into binary encoded operations, these binary encoded operations are referred to as *operation codes* or *op-codes*, some op-codes also have some associated information about the operands or the data they are operating on
![](Images/assemblyTranslation.png)

- The `gcc` command will always have the form: `gcc [OPTIONS] [FILES]`, the options that we provide are for giving specific instructions on how to compile the required files
- The following image contains some important options to know: (for the full options description please refer to the $$$$$)
![](Images/gccOptions.png)

- The command `gcc -std=c99 -Werror -o main.out main.c` will compile and link the file (main.c) using the C99 standardization, the `-o` option is to save the output executalbe into a file named (main.out), and the (-Werror) flag is used for a quality driven software so that it will cause compilation to fail if any warnings occur.
- We can use the `-Werror` flag to prevent developers from building software without resolving all of their warning messages first, as some unresolved warnings may introduce bugs.
- The `-v` flag may be used to tell the compiler to output more logging information
- Important note: when we invoke the GCC this way, then it will automatically search it's own libraries that are included in the source code to be compiled (for example: the stdio library which exists in the GCC included path)
- Jumping to the execution process, the main funtion is not actually the entry point into the application, there is an initialization code that is compiled and run before the main function and this code is the one responsible for invoking the main function. This code is also responsible for cleaning up the application and exiting after the main returns.
- As we have general flags for GCC whether it's native or cross compiler, we also have other architecture specific compiler flags for ARM cross compilers that are shown below:
![](Images/archFlags.png)

- **These architecture flags are important for informing the compiler and the linker about specific libraries to include as well as the target architecture and CPU to cross-compile for.**
- For example: consider this command to generate the embedded architecture specific assembly file `arm-none-eabi-gcc -std=c99 -mcpu=cortex-m0plus -mthumb -Wall -S main.c -o main.s` ... we can add the `-g` flag to add debug symbols for the assembly file.
- Also consider this to generate the main.out file: `arm-none-eabi-gcc main.c -o main.out --specs=nosys.specs -std=c99 -mcpu=cortex-m0plus -mthumb -Werror`
- If we try to execute the latter main.out file on our host machine it will fail as it's compiled for another system.

## Preprocessor Directives
- The preprocessor doesn't do any translation or any generation of architecture specific code, instead it helps us providing specific control of compilation within files.
- We can consider the preprocessor as a text replacement tool (or search and replace), so it provides us with macros that can help with code reuse and readability.
- The preprocessor provides special keywords called preprocessor directives. Directives start with the `#` sign. 
- Directives can be used to define `constants` as well as `macro functions` 
- Some important directives to discuss are shown in the list below:
  - `#define`, `#undef` 
  - `#ifndef`, `#ifdef`, `#endif`
  - `#include`
  - `#warning`, `#error` --> for stopping or printing warning messages in compilation.
  - `#pragma`--> this directive allows us to provide instructions to the compiler through the code itself rather than the command line.
  
- Command to stop the build process just after the preprocessing stage and generate a '.i' file: `gcc -E -o file.i file.c`
- When we look at the file.i we will find that the declarations, definitions of '#define' and files that are to be included have been added to the top of the file.
- `#define` use cases:
  > - We don't want to place random constants all over the code, it's a lot better, more readable and maintainable, and easier to modify if we #define all constants at the top of the file. The **macro variables** are defined with the statement: `#define <MACRO-NAME> <MACRO-VALUE>` .. the <MACRO-VALUE> may be a constant, a string, or even a C statement.
  ![](Images/constantExamples.png)
  ![](Images/macroSubstitution.png)
  
  > - We may want to make **macro functions**, suppose we have a specific maths formula that we use regularly in our code, so we decide that it will be better to replace the function which is doing this operation over and over with overheads like the context switching and so on with a **macro function** .. we do so using the statement `#define <MACRO-FUNCTION>(<PARAMETERS>) (<C_OPERATIONS>)` .. consider the following example:
   ![](Images/macroFunction.png)
   ![](Images/macroFunctionsExample.png)
  
  
  > - On the other side, if there is a bug in the macros, it will be harder to find and resolve as we usually don't examine the .i files. For example consider the following example:
   ![](Images/macroIssues.png)
  
  > The code was meant to output y_square to 4, but due to this bug it has multiplied 2\*3 and the result became 6. This is because we forgot the fact that preprocessor directives only make text replacements, we provided an input to the function as a valid operation to the compiler but it's not the same perspective as the preprocesor which has made text replacement twice and led us to undefined behavior.
  
  > - We can define a macro without any value, we use this way as a true/false condition of whether a certain feature is represented or not. We do so by the statement `#define <FEATURE-NAME>`. This use case can be used with the `#ifdef` & `#ifndef` to perform **compile time switches**
   ![](Images/defundef.png)
   
- Conditional directives use cases:
  - The conditional directives may be:
    - #ifdef
    - #ifndef
    - #if
    - #elif
    - #else
    - #endif --> crucial to end every block of the conditional directives
  - These directives can turn off large amounts of unneeded code, we can use them along side the `#define` & `#undef` to perform **compile time switches**, for example if we are writing a generic code for various microcontroller devices, then we can use these directives to include the header file of just the specific microcontroller device we need
  - These directives are useful for debugging
  - The if-else directives are just like the if-else in C programming, except that we don't provide the brackets `{....}`and instead we end the block with the `#endif`
   ![](Images/ifelse.png)
   ![](Images/ifelse2.png)
   
 - `#include` use cases:
   ![](Images/include.png)
   For example, in the following image the preprocessed file now contains the contents of both the .c & .h files:
   ![](Images/include2.png)

- `#pragma` use cases:
  - It's used to provide specific instructions for the compiler from the code itself, not the command line.
  - It's important when we want to provide a specific option for a specific piece of code that general compile options shouldn't do
  - It's compiler specific, meaning that some compilers can respond to the #pragma and some others may not recognize the instruction so the compiler igonre it.
  - In embedded systems, we avoid using some functions that are known to be costly resourceful (like the printf), so we use the `poison` option to enforce the developer not to use these functions or an error will occur.
   ![](Images/pragma.png)
   ![](Images/pragma2.png)

- We mentioned the term **compile time switch** before, let's discuss it in more details:
  - The compile time switches are conditional blocks of code that can change which block is executed based on a runtime parameter (the #define <--->)
  - We may add the macro name to be defined from the command line itself without modifying the code. We do so by adding the option `-D<MACRO-NAME>` and please note that the <MACRO-NAME> comes immediately after the -D ... this is equavalent to defining the macro in one of the source or header files
  ![](Images/compileTimeSwitch.png)
  
  - As we mentioned before, the compile time switch allows us to use the same code for different embedded platforms, in the following image we have the same application installed on different hardware platforms with similar software except for the UART_Lib, thanks to the compile time switches we can easily provide a very portable top layer of software with a very flexible firmware layer so that we compile the same code for two different hardware targets.
  ![](Images/CTS.png)
   
   
- The pros of preprocessor directives:
  - They make less overhead than the typical code
  - Make great improvement for writing maintainable, readable, and platform independent programs.
  
- The cons of preprocessor directives:
  - They don't perform type checking
  - They may increase bugs
  - They increase the code size

## Creating Header and Implementation Files
- Library: is a collection of sotware, either as a source code or a precompiled code format
- A standard library is a pre-written code that is pre-compiled and provided by the toolchain, we don't have access to the source code itself although we can include it in our own projects.
- The standard libraries provided in the compiler toolchain will likely be pretty optimized for the ISA we are using, meaning that they may not be optimized for our specific platform. Remember that we have very limited resources in embedded systems like memory and hardware blocks, that's why some organizations may at some point choose to rewrite some functions from these libraries in order not to include the whole standard library. 
![](Images/includingStandardLibs.png)
- We may design our own libraries to create reusable modules across different software projects
- Module: is a SW organization so that each module encapsulates certain functionalities.
- We want to design our projects in pieces or blocks to help split up the work and ease the validation process by writing software tests for each separate block or module (which is called *unit test*).
- Each module contains 2 files:
  1. The implementation or source file (.c) that contains functions definitions and other C codes. 
  2. The header file (.h) which contains functions declarations, macros and the derived datatype definitions like the *enums* and *structures*
- The .c file shouln't be directly accessible by SW projects, if we want certain data (e.g.: a certain variable) to be directly accessible we should declare them in the .h file. We can think of this as hiding the private implementation details of the C file, making the header file is the main access point and the documentation source of the module.
- Each header file should begin with the *include guard* in order to prevent more than one include of the same file in the project. This is important as if the compiler sees certain symbols are redefined it will invoke a compilation error
![](Images/includeGuard.png)
![](Images/includeGuard1.png)
![](Images/includeGuard2.png)
![](Images/includeGuard3.png)

- We can use an alternative include guard rather than the `#ifndef - #define` which is the `#pragma once` but as we mentioned before that the `#pragma` directives are non-standard and non-portable directives so it has its disadvantages.
![](Images/includeGuard4.png)
![](Images/includeGuard5.png)

- Now, we discuss some naming conventions that help maintaining and reading the code much easier:
  - When we define our own module (the .c and .h files), give each module a good name related to its functionality (e.g: keypad.c & keypad.h)
  - Give the associating include guard preprocessor directive a similar name as the module name but in which all letters are capital (e.g.: #ifndef __KEYPAD_H__)
  - Make the header file descriptive by providing a desription of the information it covers at the top of the file (like the module description, author information, copyrights, ...)
  - Also, functions prototypes need informative comments on how to use each function (as in the following image)
 ![](Images/documenting.png)
 
- Back to the pre-compiled libraries, we have 2 types of these libraries:
  - Static libraries: the libraries that are directly linked into the output executable at compile time (an example of this kind of pre-compiled libraries is the standard libraries that are provided with the toolchain)
    - Static libraries can be created using the *archiever* GNU tool (ar)
     ![](Images/staticLib.png)
  - Shared libraries: libraries that are linked dynamically with the executable at runtime, meaning that the executable file is placed in separate memory regions than the shared libraries (i.e.: The shared libraries do exist in the platform memory already, and are not installed with the executable)
    - The shared libraries are typically used by architectures running multiple programs using the same library like the advanced architectures that run an embedded operating system
    - Some embedded manufacturers provide a specific section of memory dedicated to store precompiled libraries on the hardware
    - If we install a shared library on our embedded system, then we should save it in a region of memory that will not be overwritten
    - We can create shared libraries with the `shared` option from GCC
     ![](Images/dynamicLib.png)
- Designing libraries effectively is an important software architecture paradigm. We should take time to think through code design before trying to write any implementation. Things like how our codes will interface with each other, the purpose of the modules,and the purpose of the functions. So we have to ask ourselves some questions regarding the project design:
  - Where do we actually create the architecture dependances? is it set in the code? or in the command line? .. the choice is up to the designer as there is no answer is better than the other.
  - An example of the latter point: Imagine we have a build system that supports two boards with two different micro controllers, an MSP and KL25Z.
  We have a main file that we want to be architecture independent. So, it includes an intermediate header file called platform.h.
  This platform file helps us selecting between the two different architectures we support based on a compile time switch.
  Each included file in the platform.h contains architecture dependent, low-level interface information for our intended target.
  Given the switch, the correct architecture gets included. This method requires us to create the same function name interface for both the architecture specific files, so that higher levels are compatible with the initialized function.
  There are other options to perform this architecture dependent compilation by putting compiled times switches directly in the codeinstead of intermediate files, or even using version control to help create different file trees.
![](Images/moduleDesign.png)

- The following image illustrates how we can perform compile time switches between different platforms
![](Images/CTS00.png)
![](Images/CTS01.png)


## Linkers
- The process of linking and locating are typically done in one stage and it's the last stage of the building process.
- Remember that the linker's job is to take the compiled object files (which are not executable yet) and combine them to a single executable file, and the locator maps the object file contents into specifc address locations, producing an executable program that can be installed into the embedded microprocessor.
- Normally, we have multiple files that go through the building process, some of them are the typical *.c and .h files*, some are *assembly files (.s)* and some are *library files (.a)*. The first and second types of those files go through their specific path to generate their corresponding *object file (.o)*, then all those object files as well as the .a files are fed to the linker to combine them together into a single object file which in turn is fed into the locator to map the file contents into the memory regions
![](Images/typicalBuildProcess.png)

- The **linker file** is the file responsible for telling the linker/locator how to map the executable file into the proper addresses. We pass the linker file through command line with the `-T` flag.

- The linker can be invoked directly by the `ld` or indirectly from the `gcc -o` command
- Linking process is not as simple as appending the contents of some object files into one file, as each object file contains different types of code, each type is stored in a specific memory region (e.g.: code memory and data memory) so each type is managed differently by the linker.
- The code we design is likely written with many modules, defining many functions and variables, these functions and variables are likely used across many other files. For example, consider a module called "memory", this module has a defined function called "memzero", this function is called in the main.c file. The compiler and assembler don't know that this "memzero" function is declared and defined in the "memory" module so that the "memzero" in main.c is just a *symbol* in the compiler's perspective.
![](Images/symbolsCompiler.png)

- The symbols defined in one file and used in another file need to be mapped so that the location of the symbol's address is known and assigned properly to all uses of that symbol, the linker does this mapping but without assigning the proper addresses
![](Images/afterLinking.png)

- The locator is the tool responsible for assigning the proper addresses of the symbols
![](Images/afterLocating.png)

- Errors occur when we don't properly declare or include a symbol definition that is called somewhere in the project files, in this case the linker will search through all of the object files trying to find that symbol to map it as we discussed before and ofcourse it won't be found as this symbol isn't created, then it will try to search through the included library paths to find that symbol, if it is not found then the linker will throw an error and exit. (consider the example shown in the image below)
![](Images/linkerError.png)

- Pre-compiled static libraries will directly be linked to the executable at the linking process (we need to provide the `-l` or `-L`flag to include these libraries).
![](Images/static&Linking.png)

- However, dynamically linked symbols will contain paths to dynamic libraries that are already installed on the target. This causes issues if there was an incompatibility of the library that is installed on the target and the library headers we are including.
![](Images/dynamic&Linking.png)

- If we are writing code for an embedded OS platform, then there are likely libraries already installed on the target, so there is no reason to statically compile and upload them again and waste memory space.
- It's worthy to know that standard libraries can be statically or dynamically linked.
- You will likely use static and dynamic linking at one point in your career so it's good to know about them.

- We should also wonder about the question of *What happens before `main` is called and how do we exit or return from the `main` function?" 
  - The answer is that there is a startup routine that runs before the main function, the main is actually invoked in this **startup code**
  - The startup code is usually defined in some C standard libraries and is automatically included in the build process (by the linker) as a static library. (when we directly invoke the linker instead of letting GCC do it's mission from the beginning, then the linker won't link the startup code, and the application won't find the entry for main and other startup instructions, throwing a compilation error). So if we invoke the linker directly, we will have to manually give it these libraries in order to finish the job properly.
  - We can also tell GCC to stop making automatic include to the startup code, we do so if we want to write our own custom startup code (we can do this by providing the `-nostdlib` flag in command line)
  - We can use the *verbose* flag `-v-` to see more details of the compilation and linking processes
- After all linking is done and a final object file has been created with all symbols resolved, the output is called a *relocatable file* and is fed into the *locator* in order to assign the addresses as discussed at the beginning of this lesson.
- The locator takes the relocatable file (which contains many sub-segments of code blocks which need to be mapped into the architecture's specific memory regions by assigning a specific address to each symbol (recall the following 2 images again:)
![](Images/afterLinking.png)
![](Images/afterLocating.png)

- Each architecture is very different from others, so the locator needs a special file to provide instructions about how to assign architecture specific addresses to the generic object file. This special file is called *linker file* or *linker script*
- Linker file provides the locator with information on where are the physical memory regions of the processor that will interface with the defined code regions. Linker file is architecture dependant
- Linker file specifies details such as:
  - segment name
  - region name
  - memory sizes
    - We need to assign the exact start address of the data and code memory (origin), and also the memory length of each segment (length)
  - access permission
    - Each memory region specifies access permission such as read (R), write (W), and execute (X) for memory blocks
  A brief example is shown in the following image (will discuss it in more details in Week 3)
![](Images/linkerscriptDetails.png)
![](Images/linkerscriptExample.png)
![](Images/linkerscriptExample1.png)

- It's obvious that the total size of memory segments provided in the linker file must be greater than or equal the total compiled code and data sections. To help prevent this, the linker script may contain small checks to verify that the memory regions are not overallocated. The following image shows a code example to verify that the heap and stack are not overflowing into one another in data memory, if they do then the linker throws an error and exits.
![](Images/LinkerscriptTest.png)

- The following example shows how the latter basic linker file will help the locator assign each item to its proper memory location.
![](Images/memoryMap.png)
![](Images/memoryMap1.png)
![](Images/memoryMap2.png)

- We will discuss memory section in more details in week 3.
- If we want to see how exactly the memory allocation is done, we can provide the `-map` flag with the linker in order to produce a memory map file containing information about how all memory regions and segments are used and allocated, it also provides us with specific addresses for the allocations
- The following image contains some important flags regarding the linking and locating process:
![](Images/linkerFlags.png)
![](Images/linkerFlags1.png)

- After the linking and locating process is successfully done, an output executable will be generated and ready to get installed on the target, the format of this executable file varies depending on the installer and the architecture. Some of those formats are:
![](Images/executableFileFormats.png)

## Make

- Building manually can be a very tedious process as we invoke multiple commands in which we activate multiple flags, specially when we have large projects with numerous files. For example: the linux kernel project contains over 40000 software files: +23000 .c files, +18000 .h files, and +1400 .s files; hugely increasing the chance for human error and time waste.
![](/Images/buildManually.png)

- If we look at how the IDE performs the build process, we will find huge commands (+100 characters) and maybe (+10 flags) for each file type whether it's .c or .s or .o or ...
![](/Images/largeCommands.png)

- To conclude, we need a tool to automate the build process in order to save efforts and time. This automation tool is called *make* 
- Build management, build generation, and build automation are all terms that can be used interchangibly to express the functionality of *make*
- *Make* is a **free** tool that we get from the GNU toolchain, it is utilized from the command line in the exact same way as gcc, but Make is different from gcc as it is independent of the compiler or the architecture we are using (i.e.: we won't type `arm-none-eabi-` command, instead we directly type `make` command) so we can develop our own tool that supports many compilers and architectures.
[](/Images/makeAutomates.png)
[](/Images/makeDefinition.png)

- We can use GNU make to do more than just compile; we can use it to generate software dependancies, statistical information, ...
- We can think of Make as an abstraction interface to the building process:
[](/Images/abstractionInterface.png)
[](/Images/abstractionInterface2.png)


- The makefile provides special directions and procedures in order to create the executable file from a multitude of input files, its extension is *.mk*
[](/Images/makefiles.png)

- Makefile consists of *targets* or *rules*, each target can follow a particular recipe depending on how you define your targets.
- While executing, we specify the command `make` then specify the target name we wish to execute (which we defined in the makefile)
- If no target is specified, then *make* by default implements the first defined target in the makefile.
- Some most common targets:
  - Direct object file creation
  - all: complete build for all project files
  - clean: removes all generated and object files, it helps creating a fresh build as it cleans the project from previously compiled outputs.
  [](/Images/makefileTargets.png)

- With *make*, we can still use GCC tool chain or use another vendor provider toolchain, we can also configure the makefile to support multiple versions of a compiler or even multiple compilers in the same file.
- We can also output the object files, dependancy files and map files from *make* if we want:
[](/Images/superMake.png)

- Normally, IDEs provide multiple makefiles that are autogenerated in each project by default during the project configuration process, that's how the IDE can build the whole project with just one click from the user. We can check the makefiles that the IDE includes from the *project explorer* 
- In other words, depending on the project configurations that we perform at the beginning of each new "create project", the IDE will dynamically autogenerate the corresponding makefile(s) with all the specific flags and linker files regarding the architecture. This is very good for providing a very simple interface for developers wanting to start fast, but it's bad for maintainability and portability, that's why most software teams build their own make system and version control that are maintainable and portable by them which can be used for a variety of architectures
[](/Images/IDEautoGeneration.png)

- Consider the following simple example:
  - We have a directory listing 2 source files, 3 headers, and 2 makefiles (Makefile & sources.mk) as listed in the following image
  - One makefile is used as our main makefile and the other is used to track (save) what our target source files are.
  [](/Images/makeExample1.png)
  - If we open the makefile we will find that it supports a small set of targets, we will discuss them later.
  - If we run `make all`, it will do the magic to perform a complete build to create an executable output file.
  - As we can see in the following figure, all individual compile commands with each file's specific flags are executed by only the `make all` command, and then a final link command is executed
  [](/Images/makeExample2.png)
  - If we list the contents of the current working directory once again we will see the output files are added:
  [](/Images/makeExample3.png)
  - After that, if we run the `make clean` command, it will remove all the generated output files (i.e.: clean the build directory from the non-source files). It performs the basic *remove* command for these files.
  [](/Images/makeExample4.png)
  [](/Images/makeExample5.png)
  - We must be careful when we implement the *clean* target as we don't want to accidentally remove source files or other important files 
  - We can also run `make` to build a specific individual file like the generation of the *main.o* file
  [](/Images/makeExample6.png)
- Then we will talk about how to create the makefile itself.

## Makefiles
- In some cases, we may need to use shell scripting or other scripting languages to run a series of commands to generate the needed executables.
- Or we will be writing a makefile that stores all of the necessary configurations, flags, and commands in order to generate our build and other non-source files.
- we can version control the makefile as we may update the build process over time to meet the changes that occur in the source files. However, we should not store the output files and dependancy files in the repository as we have all we need to generate them (the source files and the makefile) so no need for storing them and waste memory space.
- We can name the makefile whatever name we want, although it's mostly common that makefiles are named as one of the following: makefile, Makefile, sources.mk, includes.mk, ...
- As we mentioned in the previous lesson, each makefile has **build targets** or **build rules** that can be called alongside the `make` command to perform some specific operation .. example of build targets/rules: all, clean, main.out, main.o, ...
- These targets/rules and output files typically require other files such as dependancies (like object files or header files) to build the final output executable
- Each target containts special syntax:
  1. The target name is provided and followed by a colon (e.g.: the target name may be the name of the output file we wish to generate)
  2. The prerequisite list (dependency list) is provided after the colon and the list is separated by spaces (e.g.: prerequisites are the files that must exist before the current target can be executed). This list can be written manually or auto-generated by make.
  3. The recipe, which is the set of commands that will be executed in order to produce this target file (e.g.: the commands that we will run if we build manually from the command line)
- To simplify, consider the following example to build a file named "my_file.o" which have dependancies: my_file.c & my_file.h:
[](/Images/makefilesRules.png)
- After invoking the `make my_file.o` command, make will search through a given or a default makefile looking for a matching target name, it then checks if the prerequisites exist and generates them if they don't exist, then it executes the recipe.
- Makefiles have their own syntax, just as other software languages:
  - *Make* doesn't execute the full makefile nor does it execute every line from top to bottom. However, it has very similar characterisitcs to the C programming language
  - Makefiles can have comments, they start with the `#` .. write as many comments as you want and document what the makefiles does at the top of the file
  - We can include other makefiles with the `include` command
  - If the line gets too long, we can use the `\` to make the makefile more readable 
  - We can also create variables to make the makefile more readable and protable by reusing the variable name alongside the code instead of retyping all of its contents (they allow us to remove a lot of duplicated code)
  - We can define as many rules as we like
  - Each command in the recipe **must** start with a tab
  - Rules (targets) can be used by other rules, they may depend on each other.
  - Some advanced syntax will be discussed later.
  [](/Images/makefileSyntax.png)

- Now, we discuss more details about *variables*
  - We can access the variable by writing `$` directly before the variable name which is typed in parenthes (e.g.: $(VariableName)).
  - There are different types of variables, each type has its way to get data assigned to them:
    - Recursuvely expanded variables (=)
      - Data is assigned and substitued into a statement whenever the variable is referenced
    - Simply expanded variables (:=)
      - Data is assigned only once during the time of definition
      - It's useful for gathering some information about the current system we are compiling on (as it's not likely to be changed)
  - We can use variables to represent the flags we need to provide (e.g.: we can create a variable for the compiler flags called CFLAGS to hold the regularly occurring compile flags that we use, so we can now provide the variable instead of listing that long line each time)
  - We can also make it more dynamic and automated by using variables that contain other variables.
  - The next figure illustrates all the previous points about variables:
  [](/Images/makefileVariables.png)
  
  - We can also create variables that point to the source files and include paths, this helps us alot when we create *dynamic targets* instead of *static targets*. We can make a "INCLUDES" variable to list all header files, "SRCS" variable to list all of the project source files, "OBJECTS" variable to list all of the object files for easy referencing.
  [](/Images/makefileVariables1.png)

  - Now we can begin to make targets more flexible, readable and portable. As we can implement a particular target providing every single prerequisite, command and flag (which is too static), we can also use the variables to implement a generic target that can be used in many scenarios.
  [](/Images/makefileVariables2.png)
  
  - For more automation, makefiles have special variables called *automatic variables* that can be used to further reduce the amount of re-typing for a particular rule. Automatic variables are only useful within the recipe as they have a scope.
  - We have 2 automatic variables:
    1. `$<` this represents the prerequisite names
    2. `$@` this represents the target (rule) name
  [](/Images/makefileVariables3.png)

- If we examine the previous points we will find 2 issues limiting the automation process:
  1. We have to create 2 separate lists for the source files and the object files
  2.  We have to independently track the prerequisites of each target, this forces us to create individual targets and caused the makefile to contain many repeated rule definitions, a definition for each file name!
- Make has 2 features to solve the previous 2 issues:
  1. Make provides us the ability to auto-generate prerequisites!
  2. Make allows us to create an implicit rule by using a *pattern match* to associate the C files to object files; we do this with the `%` operator. (i.e.: the pattern match feature is used to match file names)
    - Consider the following example in the image below, the statement `%.o: %.c` tells *make* that if the user calls any target that matches the pattern with a file that ends with a ".o", it will have a prerequisite of a ".c" file before the recipe runs. For example: if we call in the command line `make main.o` and we don't have a rule named main.o in the makefile, instead we have that pattern match, then Make will know how to generate it:
    [](/Images/patternMatching.png)
  - Furthermore, we can also create a variable to track all of these object files automatically!
    1. Create the *SRCS* variable that lists all the source files in the project
    2. Use the *SRCS* to generate a list of the project object files and put in the *OBJS* variable
    - We do so by the statement: `OBJS:= $(SRCS:.c=.o)` ... This statement tells Make to define a simply expanded variable called *OBJS* that is going to go through every word in the *SRCS* list, and replace any *.c* ending with a *.o* ending, and assign the new list to the *OBJS*.
    [](/Images/patternMatching1.png)
- Now, we can highly automate the process of generating targets.
- Not every target we need are actual file names, target may be named "all" or "clean" or whatever name we want

- We can automate the *all* target as well; but first we need to introduce a new feature of *Make* called a *directive*
  - It's somehow similar to the preprocessor directives in C, it gives extra information to *Make* on what to do.
  - `.PHONY` directive indicates that this is a non-file target so that *Make* doesn't confuse this with an actual file.
[](/Images/PHONY.png)

- We may want our makefile to support multiple architectures as well as multiple build targets.
- *Make* also have functions! We can even do conditional executions in the makefile based on input parameters or system information (i.e.: we can perform something similar to the compile time switches we've done in C)!
  - Makefile functions can do a variety of things like: run linux commands or perform conditional operations
  - Some makefile functions are: shell, file, origin, conditional, ...
  - The `shell` function runs a specific linux command with options, then it assigns the data outputted from the command to the variable. Using the `shell` command, we can create dynamic makefiles that can query the system for its information like the *architecture directory*, *operating system*, ...
  - We can then combine the shell command output and use the conditional operator `ifeq` to see -for example- if we are currently executing on a Linux OS or not.
  [](/Images/Shell.png)

  - Conditional execution is not limited to shell function output. We can actually pass parameters into *Make* to help make decisions; For example: we can create a variable called "PLATFORM" to help us determining which compiler we are going to use for building, we can assign the needed platform from the command line and makefile will execute the defined conditonal execution to dedicate the proper compiler for that target, for example: if the target platform is the *MSP* then we need to change the target CPU to cortex M4, if the platform is the *Freedom board* then we need to change the target cpu to Cortex M0+
  [](/Images/overridingVariables.png)

  - We can extend the idea to change various compile time or linker time flags
  [](/Images/overridingVariables1.png)

- We mentioned before the *CPPFLAGS* and *CFLAGS* variables, these particular variable names are not randomly chosen as these variable names are special variables that are implicitly used by *Make*
[](/Images/specialVariables.png)

- There is some pros and cons using *GNU make*, but its popularity, simplicity, and its free cost make it a great application to use.
- Now we will discuss a demo of a simple *make* system with 2 makefiles and some source and header files:
- Currently, the PWD is clean with no generated files yet:
[](/Images/makeDemo.png)
- The makefiles presented in the directory are *Makefile* that defines all of the targets/rules and *sources.mk* that defines the source files needed to create a complete build
- This is the contents of the *sources.mk* separated by the line continuation `\` to make it more readable:
[](/Images/makeDemo1.png)
- And this is the main *Makefile*, it starts with some documentation on what targets/rules we have in the file, as well as variable overrides for some compiled time switches:
[](/Images/makeDemo2.png)
- The file starts by the inclusion of the *sources.mk* followed by the defined variables
[](/Images/makeDemo3.png)
- Then the target list is written, the .PHONY directives is used for the non-file targets, and the pattern match is used for the file targets
[](/Images/makeDemo4.png)
- We can test the implicit rule of the pattern match to see if it goes well:  
[](/Images/makeDemo5.png)


## Other Useful GNU Bin Tools
- Here we will discuss some other important tools that come with the GNU toolchain
- We already know about the preprocessor, compiler, assembler, linker, and make. There is also a collection of supportive applications just as the *GNU project debugger* and the *GNU bin utils* and more.
- The binary utils are extra programs to give more help with the building process by evaluating, manipulating, and even test our executable files
- The assembler and linker are 2 examples of the bin utils, and here are some more programs of the bin utils:
[](/Images/binutils.png)

- Here is a list of some more utilities:
[](/Images/gdb.png)

- The GNU project debugger (gdb) provides us with tools that help with debugging, it's an independent application (much like *Make* is)
- We also have the *size* utility which allows us to investigate the size of different memory sections assigned after compiling the object files.
[](/Images/sizeUtil.png)

- The NM utility is used to look at the declared symbols in an object file, investigate their sizes.
  - Symbols are special identifiers for code and data in software, there are also debug symbols that help when using the debugger
  - There are many types of symbols, the next figure introduces just 4 of them
[](/Images/NM.png)

- An example using the NM util; we have a source file called my_file.c that contains 5 very short functions. The NM can investigate the object form of this file after compiling and determine what types of symbols are defined, this file doesn't include another files so all of the symbols are of type `T` or code symbols
[](/Images/NM1.png)

- The next utility to discuss is the object copy (objcopy); it's used to copy or convert object files. We mentioned before that there are many object file formats that based on various manufacturers and vendors, so depending on the architecture and the loader, we may need to convert the object file from a format to another so that the system understands how to install or execute the object file
[](/Images/objcopy.png)

- The object dump (objdump) utility is used to take an object file and dump information about that object file, this tool can take the object file and convert it to the assoicated assembly code so that the developer can investigate subtle bugs that maybe happening at the assembly level, or even analyze runtime execution down to clock cycles
[](/Images/objdump.png)
[](/Images/objdump1.png)

- The readelf utility is helpful in understanding the elf files, other formats like the intel HEX record, motorola S record -with some perseverance- can be decoded and mapped into assembly because of its hex encoding, but elf files are not that way, that's why we use the `readelf` command in order to print some interesting information about the elf executable (as an alternative to decoding) such as size, architecture, and memory sections
[](/Images/readelf.png)

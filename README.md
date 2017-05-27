# simpleNewton -  general purpose parallel simulation framework

# Introduction

Welcome to the simpleNewton framework. It started off as a hobby C++ project in March 2017, after I got my masters' degree in Computational Engineering at FAU Erlangen-Nuernberg. The aim is clearly set - firstly scientific, and then fast! The latter calls for parallelization strategies. As a first step, the framework shall incorporate a physics simulation engine.

# Notes on tools required

The C++ compiler needs to comply with the C++11 standard. The project is made using CMake, a cross-platform build system. This 
is done for portability, package finding, configurability and ease of use. 

The project makes use of MPI and OpenMP parallelization strategies so an installation of MPICH or OpenMPI would be advantageous but strictly speaking not a requirement; the framework can be built in single-processing mode. The documentation has been made possible by Doxygen, a delightful piece of documentation software. For version control, the popular git is highly recommendable.

# Notes on error handling

Error handling takes different approaches in debug and release modes. 

In debug mode, sturdy assertions are used to abruptly stop the program if an error occurs. 

However, in release mode, exceptions are thrown to keep with the RAII principle. Catching exceptions higher up in the call stack is naturally desirable. More on this in the future.

# Notes on parallelization strategies

Three dimensional domains shall be split into blocks, each block will be assigned one MPI process only. If MPI is not available/included in the CMake configuration, the domain will be represented by one block only and the MPI module will not 
be compiled. 

Each process shall be capable of multithreading - this will also be a compiler flag which can be selected in the CMake interface. OpenMP 4.0 makes multiple, new ideas and concepts realisable - explicit SIMD directives and GPGPU possibilities along with good old SMT parallelization.

Apart from this, the possibility to use the C++11 STL's multithreading library is also to be taken into consideration.

# Layout

The project has six modules so far: asserts, concurrency, containers, core, logger and types.

The asserts module provides run-time - debug and release mode requirements with an exit strategy described by the process 
singleton (which is part of the core module), and also compile-time - debug and release mode type constraints which is 
fairly elaborate and flexible.

The concurrency module shall have sub modules of mpi, openmp and multithreading of which only mpi has been worked upon. 
Many supporting classes and units such as special containers reside in other folders and are also conditionally compiled 
based on the CMake configuration.

The containers module has primary dynamic container and automatic container classes from which every possible container which 
may be required by the framework can be derived.
	At the root of the dynamic container class is the RAIIWrapper class, which functions as a resource manager similar to the 
STL's std::unique_ptr. Dynamic resource allocation is intended for large fields and containers. 
  The automatic container class is used as the base class for all small-sized containers such as mathematical containers - 
Vector2, Vector3, Matrix2, Matrix3 et cetera, the advantage being compiler optimizations which are made possible by fixing 
the container size at compile time.
	
The core module shall incorporate vital functionality. Here resides the ProcSingleton, the only singleton class in the framework. 
This class manages process-essential functions and has a lifetime equal to that of the program's.  A high precision timer which 
selects only a steady clock is also available here. Special exception classes are also provided here.

The logger is unconventional and provides interesting functionality. Instead of the traditional detail levels this logger 
provides distinct, useful logger levels: error and exception reporting, warning reporting, watching of variables and watching 
of low- and high-level events. All levels and their corresponding file writing can be toggled in the CMake configuration. 
The file writing and console output are thread-safe and a file is created for every process.

Event watching is done with Event Watching Regions (EWR) which are declared by macros. There exist distinct EWRs for both 
low and high-level  events. Low-level events could be resource allocations and deallocations, thread forking and 
synchronizations and MPI operations, among others. High-level events are purely user-defined and can be anything the user 
desires. With the help of event watching, the debugger can focus on small (or large) sections of the program and study every 
action in detail.
	
The types module incorporates a comprehensive typetraits implementation (made possible with some template metaprogramming), a 
functor class and a typelist class for the framework.

# Statement

Thank you for reading this introduction. The software described above is open-source under GNU GPL 3.0 and can be downloaded 
from github. PLEASE DO WRITE ME YOUR SUGGESTIONS AND COMMENTS by email. These will be greatly appreciated!

Nitin Malapally (anxiousprogrammer)


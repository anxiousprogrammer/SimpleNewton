#ifndef SN_EXCEPTION_HPP
#define SN_EXCEPTION_HPP

#include <string>
#include <cstdlib>

#include <stdexcept>
#include <ios>

#include <Types.hpp>

//==========================================================================================================================================
//
//  This file is part of simpleNewton. simpleNewton is free software: you can 
//  redistribute it and/or modify it under the terms of the GNU General Public
//  License as published by the Free Software Foundation, either version 3 of 
//  the License, or (at your option) any later version.
//  
//  simpleNewton is distributed in the hope that it will be useful, but WITHOUT 
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
//  for more details.
//  
//  You should have received a copy of the GNU General Public License along
//  with simpleNewton (see LICENSE.txt). If not, see <http://www.gnu.org/licenses/>.
//
///   Contains all the exception classes for the modules of the simpleNewton framework. These can be classified under logical errors 
///   (invalid arguments, pre-condition errors, domain errors, size errors and out of range errors) and run-time errors (range, overflow, 
///   underflow, input/output, functor, allocation, allocation size errors and MPI errors), and are derived from their respective standard 
///   library representatives.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

//===CLASS==================================================================================================================================

/** This class extends the information of the std::exception classes by providing module, line and file information wherever possible. */
//==========================================================================================================================================

class ExceptionInfo {

public:
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Deleted trivial constructor. */
   ExceptionInfo() = delete;
   
   /** Direct initialization constructor sets up the std::exception unit as well as additional error information. */
   ExceptionInfo( uint_t , const std::string & );
   
   /** Deteled copy constructor. */
   ExceptionInfo( const ExceptionInfo & ) = delete;
   
   /** Deteled move constructor. */
   ExceptionInfo( ExceptionInfo && ) = default;
   
   /** @} */
   
   /** \name Access
   *   @{
   */
   /** A function to get information about the line at which the error was thrown. */
   inline uint_t getLine() const                        { return line_; }
   
   /** A function to get information about in which module the error was thrown. */
   inline const std::string & getFunction() const       { return func_; }
   
   /** @} */

private:
   
   uint_t line_;        ///< Line information.
   std::string func_;   ///< Function information.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Logic exceptions - when the programmer causes the error (bug)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** This class is intended for use when an argument turns out to be invalid based on any type of constraint. */
class InvalidArgument : public std::invalid_argument, ExceptionInfo {

public:
   
   InvalidArgument( const std::string & ,
                    uint_t = {},
                    const std::string & = {} );
};



/** This class is intended for use when a function's pre-condition is not met. */
class PreconditionError : public std::logic_error, ExceptionInfo {

public:
   
   PreconditionError( const std::string & ,
                      uint_t = {},
                      const std::string & = {} );
};



/** This class is intended for use when a mathematical function is provided an argument outside of its domain. */
class DomainError : public std::domain_error, ExceptionInfo {

public:
   
   DomainError( const std::string & ,
                uint_t = {},
                const std::string & = {} );
};



/** This class is intended for use when a mathematical function is provided an argument outside of its domain. */
class MaxSizeError : public std::length_error, ExceptionInfo {

public:
   
   MaxSizeError( const std::string & ,
                 uint_t = {},
                 const std::string & = {} );
};



/** This class is intended for use when a container index is out of range i.e., is greater than the container size. */
class OORError : public std::out_of_range, ExceptionInfo {

public:
   
   OORError( const std::string & ,
             uint_t = {},
             const std::string & = {} );
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Run-time exceptions or real errors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** This class is intended for use when e.g. a floating point value goes out of range and cannot be stored in its destination. */
class RangeError : public std::range_error, ExceptionInfo {

public:
   
   RangeError( const std::string & ,
               uint_t = {},
               const std::string & = {} );
};



/** This class is intended for use when an overflow occurs i.e., an integer value is higher than an instance of its type can contain. */
class OverflowError : public std::overflow_error, ExceptionInfo {

public:
   
   OverflowError( const std::string & ,
                  uint_t = {},
                  const std::string & = {} );
};



/** This class is intended for use when an underflow occurs i.e., an integer value is lower than an instance of its type can contain. */
class UnderflowError : public std::underflow_error, ExceptionInfo {

public:
   
   UnderflowError( const std::string & ,
                   uint_t = {},
                   const std::string & = {} );
};



/** This class is intended for use when an error occures in the input/output system. It is recommended that only badbits throw such 
*   exceptions. */
class IOError : public std::ios_base::failure, ExceptionInfo {

public:
   
   IOError( const std::string & ,
            uint_t = {},
            const std::string & = {} );
};



/** This class is intended for use when a funtion wrapper (functor) points to a false or non-existent target. */
class FunctorError : public std::bad_function_call, ExceptionInfo {

public:
   
   FunctorError( uint_t = {},
                 const std::string & = {} );
};



/** This class is intended for use when a resource could not be allocated using the new operator. */
class AllocError : public std::bad_alloc, ExceptionInfo {

public:
   
   AllocError( uint_t = {},
               const std::string & = {} );
};



/** This class is intended for use when a resource could not be allocated using the new operator because of size problems. */
class AllocSizeError : public std::bad_array_new_length, ExceptionInfo {

public:
   
   AllocSizeError( uint_t = {},
                   const std::string & = {} );
};



/** This class is intended for use when an MPI operation fails. */
class MPIError : public std::runtime_error, ExceptionInfo {

public:
   
   MPIError( const std::string & ,
             uint_t = {},
             const std::string & = {} );
};

}   // namespace simpleNewton

#include "ExceptionMacros.hpp"
#endif

#include "Exceptions.hpp"

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
///   Contains implementations of the exceptions classes of the simpleNewton framework.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================


/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

ExceptionInfo::ExceptionInfo( uint_t line,                    /**< The line information. */
                              const std::string & func        /**< The function name. */ ) : line_(line), func_(func)   {}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Logical exceptions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
InvalidArgument::InvalidArgument( const std::string & what_arg, /**< The message returned by what() */
                                  uint_t line,                  /**< The line information. */
                                  const std::string & func      /**< The function name. */ ) : std::invalid_argument( what_arg ), 
                                                                                               ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
PreconditionError::PreconditionError( const std::string & what_arg, /**< The message returned by what() */
                                      uint_t line,                  /**< The line information. */
                                      const std::string & func      /**< The function name. */ ) : std::logic_error( what_arg ), 
                                                                                                   ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
MathError::MathError( const std::string & what_arg, /**< The message returned by what() */
                      uint_t line,                  /**< The line information. */
                      const std::string & func      /**< The function name. */ ) : std::domain_error( what_arg ), 
                                                                                   ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
OORError::OORError( const std::string & what_arg, /**< The message returned by what() */
                    uint_t line,                  /**< The line information. */
                    const std::string & func      /**< The function name. */ ) : std::out_of_range( what_arg ), 
                                                                                 ExceptionInfo( line, func ) {}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Run-time exceptions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
RangeError::RangeError( const std::string & what_arg, /**< The message returned by what() */
                        uint_t line,                  /**< The line information. */
                        const std::string & func      /**< The function name. */ ) : std::range_error( what_arg ), 
                                                                                     ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
OverflowError::OverflowError( const std::string & what_arg, /**< The message returned by what() */
                              uint_t line,                  /**< The line information. */
                              const std::string & func      /**< The function name. */ ) : std::overflow_error( what_arg ), 
                                                                                           ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
UnderflowError::UnderflowError( const std::string & what_arg, /**< The message returned by what() */
                                uint_t line,                  /**< The line information. */
                                const std::string & func      /**< The function name. */ ) : std::underflow_error( what_arg ), 
                                                                                             ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
IOError::IOError( const std::string & what_arg, /**< The message returned by what() */
                  uint_t line,                  /**< The line information. */
                  const std::string & func      /**< The function name. */ ) : std::ios_base::failure( what_arg ), 
                                                                               ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
FunctorError::FunctorError( uint_t line,                  /**< The line information. */
                            const std::string & func      /**< The function name. */ ) : std::bad_function_call(), 
                                                                                         ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
AllocError::AllocError( uint_t line,                  /**< The line information. */
                        const std::string & func      /**< The function name. */ ) : std::bad_alloc(), 
                                                                                     ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
AllocSizeError::AllocSizeError( uint_t line,                  /**< The line information. */
                                const std::string & func      /**< The function name. */ ) : std::bad_array_new_length(), 
                                                                                             ExceptionInfo( line, func ) {}

/** Direct initialization constructor sets up the exception and distributes the information to its corresponding base classes. */
MPIError::MPIError( const std::string & what_arg, /**< The message returned by what() */
                    uint_t line,                  /**< The line information. */
                    const std::string & func      /**< The function name. */ ) : std::runtime_error( what_arg ), 
                                                                                 ExceptionInfo( line, func ) {}

}   // namespace simpleNewton

#ifndef SN_EXCEPTIONMACROS_HPP
#define SN_EXCEPTIONMACROS_HPP

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
///   Contains macros for ease of use and convenience for throwing exceptions from Exceptions.hpp.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifndef __SN_EXCEPTIONS_FUNC_LINE_INFO__
   
   #define SN_THROW_INVALID_ARGUMENT( WHAT )      do { throw simpleNewton::InvalidArgument( WHAT ); } while(false)
   #define SN_THROW_PRECONDITION_ERROR( WHAT )    do { throw simpleNewton::PreconditionError( WHAT ); } while(false)
   #define SN_THROW_POSTCONDITION_ERROR( WHAT )   do { throw simpleNewton::PostconditionError( WHAT ); } while(false)
   #define SN_THROW_MATH_ERROR( WHAT )            do { throw simpleNewton::MathError( WHAT ); } while(false)
   #define SN_THROW_OOR_ERROR( WHAT )             do { throw simpleNewton::OORError( WHAT ); } while(false)
   #define SN_THROW_RANGE_ERROR( WHAT )           do { throw simpleNewton::RangeError( WHAT ); } while(false)
   #define SN_THROW_OVERFLOW_ERROR( WHAT )        do { throw simpleNewton::OverflowError( WHAT ); } while(false)
   #define SN_THROW_UNDERFLOW_ERROR( WHAT )       do { throw simpleNewton::UnderflowError( WHAT ); } while(false)
   #define SN_THROW_IO_ERROR( WHAT )              do { throw simpleNewton::IOError( WHAT ); } while(false)
   #define SN_THROW_FUNCTOR_ERROR()               do { throw simpleNewton::FunctorError(); } while(false)
   #define SN_THROW_ALLOC_ERROR()                 do { throw simpleNewton::AllocError(); } while(false)
   #define SN_THROW_ALLOC_SIZE_ERROR()            do { throw simpleNewton::AllocSizeError(); } while(false)
   #define SN_THROW_SYSTEM_ERROR( EC, WHAT )      do { throw simpleNewton::SystemError( EC, WHAT ); } while(false)
   #define SN_THROW_MPI_ERROR( WHAT )             do { throw simpleNewton::MPIError( WHAT ); } while(false)
   #define SN_THROW_UNKNOWN_ERROR( WHAT )         do { throw simpleNewton::UnknownError( WHAT ); } while(false)

#else
   
   /** This macro throws an exception of type InvalidArgument. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_INVALID_ARGUMENT( WHAT )      do { throw simpleNewton::InvalidArgument( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type PreconditionError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_PRECONDITION_ERROR( WHAT )    do { throw simpleNewton::PreconditionError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type PostconditionError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_POSTCONDITION_ERROR( WHAT )   do { throw simpleNewton::PostconditionError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type DomainError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_MATH_ERROR( WHAT )            do { throw simpleNewton::MathError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type OORError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_OOR_ERROR( WHAT )             do { throw simpleNewton::OORError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type RangeError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_RANGE_ERROR( WHAT )           do { throw simpleNewton::RangeError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type OverflowError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_OVERFLOW_ERROR( WHAT )        do { throw simpleNewton::OverflowError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type UnderflowError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_UNDERFLOW_ERROR( WHAT )       do { throw simpleNewton::UnderflowError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type IOError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_IO_ERROR( WHAT )              do { throw simpleNewton::IOError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type FunctorError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_FUNCTOR_ERROR()               do { throw simpleNewton::FunctorError( __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type AllocError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_ALLOC_ERROR()                 do { throw simpleNewton::AllocError( __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type AllocSizeError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_ALLOC_SIZE_ERROR()            do { throw simpleNewton::AllocSizeError( __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type SystemError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_SYSTEM_ERROR( EC, WHAT )      do { throw simpleNewton::SystemError( EC, WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type MPIError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_MPI_ERROR( WHAT )             do { throw simpleNewton::MPIError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type UnknownError. It includes function and line info if __SN_EXCEPTIONS_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_UNKNOWN_ERROR( WHAT )         do { throw simpleNewton::UnknownError( WHAT, __LINE__, __func__ ); } while(false)
   
#endif   // Line and func info flag
#endif   // Header Guard

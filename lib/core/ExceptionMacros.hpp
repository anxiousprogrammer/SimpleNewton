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
///   Contains exception macros which make it easier and more convenient to throw exceptions.
///   \file
///   \addtogroup core Core
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifdef __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__
   
   /** This macro throws an exception of type InvalidArgument. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_INVALID_ARGUMENT( WHAT )     do { throw InvalidArgument( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type PreconditionError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_PRECONDITION_ERROR( WHAT )   do { throw PreconditionError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type DomainError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_DOMAIN_ERROR( WHAT )         do { throw DomainError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type MaxSizeError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_MAX_SIZE_ERROR( WHAT )           do { throw SizeError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type OORError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_OOR_ERROR( WHAT )            do { throw OORError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type RangeError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_RANGE_ERROR( WHAT )          do { throw RangeError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type OverflowError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_OVERFLOW_ERROR( WHAT )       do { throw OverflowError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type UnderflowError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_UNDERFLOW_ERROR( WHAT )      do { throw UnderflowError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type IOError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_IO_ERROR( WHAT )             do { throw IOError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type FunctorError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_FUNCTOR_ERROR( WHAT )        do { throw FunctorError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type AllocError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_ALLOC_ERROR( WHAT )          do { throw AllocError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type AllocSizeError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_ALLOC_SIZE_ERROR( WHAT )     do { throw AllocSizeError( WHAT, __LINE__, __func__ ); } while(false)
   
   /** This macro throws an exception of type MPIError. It includes function and line info if __SN_EXCEPTIONS_WITH_FUNC_LINE_INFO__ 
   *   has been defined by the make system. */
   #define SN_THROW_MPI_ERROR( WHAT )            do { throw MPIError( WHAT, __LINE__, __func__ ); } while(false)

#else
   
   #define SN_THROW_INVALID_ARGUMENT( WHAT )     do { throw InvalidArgument( WHAT ); } while(false)
   #define SN_THROW_PRECONDITION_ERROR( WHAT )   do { throw PreconditionError( WHAT ); } while(false)
   #define SN_THROW_DOMAIN_ERROR( WHAT )         do { throw DomainError( WHAT ); } while(false)
   #define SN_THROW_SIZE_ERROR( WHAT )           do { throw SizeError( WHAT ); } while(false)
   #define SN_THROW_OOR_ERROR( WHAT )            do { throw OORError( WHAT ); } while(false)
   #define SN_THROW_RANGE_ERROR( WHAT )          do { throw RangeError( WHAT ); } while(false)
   #define SN_THROW_OVERFLOW_ERROR( WHAT )       do { throw OverflowError( WHAT ); } while(false)
   #define SN_THROW_UNDERFLOW_ERROR( WHAT )      do { throw UnderflowError( WHAT ); } while(false)
   #define SN_THROW_IO_ERROR( WHAT )             do { throw IOError( WHAT ); } while(false)
   #define SN_THROW_FUNCTOR_ERROR( WHAT )        do { throw FunctorError( WHAT ); } while(false)
   #define SN_THROW_ALLOC_ERROR( WHAT )          do { throw AllocError( WHAT ); } while(false)
   #define SN_THROW_ALLOC_SIZE_ERROR( WHAT )     do { throw AllocSizeError( WHAT ); } while(false)
   #define SN_THROW_MPI_ERROR( WHAT )            do { throw MPIError( WHAT ); } while(false)
   
#endif   // Line and func info flag
#endif   // Header Guard

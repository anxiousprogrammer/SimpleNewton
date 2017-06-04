#ifndef SN_THREADPOOL_HPP
#define SN_THREADPOOL_HPP

#include <Types.hpp>
#include <BasicBases.hpp>

#include <algorithm>
#include <vector>

#include <logger/Logger.hpp>

#ifdef __SN_USE_STL_MULTITHREADING__
   #include <thread>
#endif

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
///   Contains the class ThreadPool, which is the STL multithreading manager for the framework.
///   \file
///   \addtogroup concurrency Concurrency
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

/** A typedef which identifies a handle to a std::thread. */
using ThreadHandle_t = std::thread * ;

//=== CLASS ================================================================================================================================

/** This class is responsible for spinning threads, assigning them tasks and managing their lifecycles. */
//==========================================================================================================================================

class ThreadPool : private NonCopyable {

public:
   
   /** \name Constructors and destructor
   *   @{
   */
   /** Default trivial constructor */
   ThreadPool() = default;
   /** Explicitly defined destructor joins threads. */
   ~ThreadPool();
   
   /** @} */
   
   /** \name Primary functionality
   *   @{
   */
   /** A function which spins up STL threads and assigns them tasks.
   *
   *   \tparam RET_TYPE    The return type of the target function. This will be deduced by the compiler.
   *   \tparam PARAM       The parameters of the target function. This will be deduced by the compiler.
   *   \tparam DATA        The types of the data, which is either to be shared or be made private. This will be deduced by the compiler.
   *   \param  task        A functor with the task for the thread.
   *   \param  data_args   The data which is either to be shared or be made private.
   *   \return             A handle to the newly created thread.
   */
   #ifdef __SN_USE_STL_MULTITHREADING__
   template< class RET_TYPE, class... PARAM, class... DATA >
   ThreadHandle_t spinThread( RET_TYPE(*task)( PARAM... ), DATA &&... data_args ) {

      tp_.push_back( std::thread( task, data_args... ) );
      SN_LOG_REPORT_L1_EVENT( LogEventType::ThreadFork, "" );
      
      return &tp_.back();
   }
   #else
   template< class RET_TYPE, class... PARAM, class... DATA >
   ThreadHandle_t spinThread( RET_TYPE(*)( PARAM... ), DATA &&... ) { return nullptr; }
   #endif   // STL threading guard

private:
   
   #ifdef __SN_USE_STL_MULTITHREADING__
   /* std::thread manager */
   std::vector< std::thread > tp_ = {};
   #endif   // STL threading guard
};

}   // namespace simpleNewton

#endif   // Header guard


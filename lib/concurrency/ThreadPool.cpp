
#include "ThreadPool.hpp"

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
///   Contains the implementation of header, ThreadPool.
///   \file
///   \addtogroup concurrency Concurrency
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

/** The space in which all global entities of the framework are accessible */
namespace simpleNewton {

ThreadPool::~ThreadPool() {
   
   #ifdef __SN_USE_STL_MULTITHREADING__
   // Bring all threads back together
   std::for_each( tp_.begin(), tp_.end(), []( std::thread & iter ){ iter.join(); SN_LOG_REPORT_L1_EVENT( LogEventType::ThreadJoin, "" ); } );
   #endif   // STL threading guard
}

}   // namespace simpleNewton

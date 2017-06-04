#ifndef SN_OPENMP_HPP
#define SN_OPENMP_HPP

#ifdef __SN_USE_OPENMP__
   #include <omp.h>
#endif

#include <logger/Logger.hpp>

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
///   Includes OpenMP if the configuration allows it.
///   \file
///   \defgroup openmp OpenMP
///   \author Nitin Malapally (anxiousprogrammer) <nitin.malapally@gmail.com>
//
//==========================================================================================================================================

#ifdef __SN_USE_OPENMP__
   
   // The following are necessary global functions which have no definitions. They exist to keep the compiler from despairing
   // over specific components of OpenMP directives.
   //void shared( ... );
   //void firstprivate( ... );
   //void lastprivate( ... );
   
   /* Necessary constructs */
   #define __SN_PRAGMA__(X)                       _Pragma( #X )
   
   
   
   #define SN_OPENMP_FORK_REGION( ... )           SN_LOG_REPORT_L1_EVENT( LogEventType::OMPFork, "" ); \
                                                  __SN_PRAGMA__( omp parallel __VA_ARGS__ ) \
                                                  {
   #define SN_OPENMP_SYNC()                       } \
                                                  SN_LOG_REPORT_L1_EVENT( LogEventType::OMPJoin, "" );
   #define OMP_THREADS( N )                       num_threads( N )



   /* Data-sharing constructs */
   #define OMP_DEFAULT( TYPE )         default( TYPE )
   #define OMP_SHARED( ... )           shared( __VA_ARGS__ )
   #define OMP_PRIVATE( ... )          private( __VA_ARGS__ )
   #define OMP_FIRST_PRIVATE( ... )    firstprivate( __VA_ARGS__ )
   #define OMP_LAST_PRIVATE( ... )     lastprivate( __VA_ARGS__ )



   /* Work-sharing constructs */
   #define OMP_FOR_LOOP( ... )         __SN_PRAGMA__( omp for __VA_ARGS__ )

   #define OMP_STATIC_CS( P )          schedule( static, P )
   #define OMP_DYNAMIC_CS( P )         schedule( dynamic, P )
   #define OMP_GUIDED_CS( P )          schedule( guided, P )
   #define OMP_AUTO                    schedule( auto )
   #define OMP_COLLAPSE( N )           collapse( N )
   #define OMP_REDUCTION( ... )        reduction( __VA_ARGS__ )
   #define OMP_NOWAIT                  nowait
   #define OMP_ORDERED                 ordered
   
   #define OMP_SINGLE()                __SN_PRAGMA__( omp single )
   
   #define OMP_SECTIONS_REGION()       __SN_PRAGMA__( omp sections )
   
   #define OMP_SECTION()               __SN_PRAGMA__( omp section )



   /* Synchronization constructs */   
   #define OMP_BARRIER                 __SN_PRAGMA__( omp barrier )
   #define OMP_ATOMIC_REGION()         __SN_PRAGMA__( omp critical )
   #define OMP_CRITICAL_REGION()       OMP_ATOMIC_REGION()
   #define OMP_MASTER_REGION()         __SN_PRAGMA__( omp master )
   
#endif

#endif   // Header include guard 

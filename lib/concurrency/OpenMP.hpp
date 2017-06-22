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

#ifndef __SN_USE_OPENMP__
   
   #ifndef DOXYGEN_SHOULD_SKIP_THIS // <--- Internal macros
   #define __SN_PRAGMA__(X)
   #endif   // DOXYSKIP   <--- Now begins the interface


   /** This macro initiates an OpenMP parallel region. The daemon wakes up supporting threads. All OpenMP constructs are to be used within 
   *   parallel regions only.
   */
   #define SN_OPENMP_FORK( ... )
   
   /** This macro performs a synchronization operation i.e., joins all secondary threads to the primary. This signifies the end of a 
   *   parallel region.
   */
   #define SN_OPENMP_SYNC()
   
   /** This macro definition can be passed as an argument to the forking macro and instructs the daemon to launch the following parallel 
   *   region with a provided number of threads.
   *
   *   \param N   The number of threads required to be used in the following parallel region.
   */
   #define OMP_THREADS( N )
   
   /** This macro defines the data-sharing construct for the following parallel region. The ellipsis captures the arguments.
   */
   #define OMP_DEFAULT( TYPE )

   /** This macro takes arguments as shared data for the following parallel region. Warning -  the incorrect use of this construct can 
   *   lead to very poor performances and incorrect results. The ellipsis captures the arguments.
   */
   #define OMP_SHARED( ... )
   
   /** This macro takes arguments as private data for the following parallel region. Furthermore, the private instances will be 
   *   initialised with their default values. The ellipsis captures the arguments.
   */
   #define OMP_PRIVATE( ... )
   
   /** This macro takes arguments as private data for the following parallel region but copies their values from the master thread
   *   instances into the respective slave thread instances. The ellipsis captures the arguments.
   */
   #define OMP_FIRST_PRIVATE( ... )
   
   /** This macro takes arguments as private data for the following parallel region but copies the values of the slowest/last finishing 
   *   thread instances into the master thread instances. The ellipsis captures the arguments.
   */
   #define OMP_LAST_PRIVATE( ... )



   /** This macro declares the work-sharing for-loop construct. The directly following for-loop will be parallelised such that each thread 
   *   will be assigned certain iterations. The parameters captured by the ellipsis decide the attributes of the for-loop. The scheduling 
   *   largely decides the speedup obtained, and the options available are - static, dynamic, guided and automatic scheduling modes.
   */
   #define OMP_FOR_LOOP( ... )

   /** This macro can be passed as an argument to a parallel for-loop to select static scheduling. The iterations are allocated to 
   *   the threads only once, at the beginning.
   */
   #define OMP_STATIC
   
   /** This definition can be passed as an argument to a parallel for-loop to select dynamic scheduling. The iterations are handed out to 
   *   the threads as and when they complete the previously allocated tasks/iterations. This mode allows better parallelization for 
   *   iterations with heterogeneous computational intensities. When this is not the case, using this can come with significant overheads.
   */
   #define OMP_DYNAMIC
   
   /** This definition can be passed as an argument to a parallel for-loop to select guided scheduling. The iterations are handed out to 
   *   the threads as and when they complete the previously allocated tasks/iterations. The only difference from the dynamic mode is 
   *   that the chunk size starts off relatively large and is subsequently reduced upon each task completion to better balance the load.
   */
   #define OMP_GUIDED
   
   /** Same as OMP_STATIC, but the user must specify a chunk size as argument to the scheduler.
   *
   *   \param C_SZ   The chunk size decides the interval of the distribution. The default value is TOTAL_LOOP_COUNT/NUMBER_OF_THREADS.
   */
   #define OMP_STATIC_CS( C_SZ )
   
   /** Same as OMP_DYNAMIC, but the user must specify a chunk size as argument to the scheduler.
   *
   *   \param C_SZ   The chunk size decides the interval of the distribution. The default value is 1.
   */
   #define OMP_DYNAMIC_CS( C_SZ )
   
   /** Same as OMP_GUIDED, but the user must specify a starting chunk size as argument to the scheduler.
   *
   *   \param C_SZ   The chunk size decides the interval of the distribution at the start. The default starting value is TOTAL_LOOP_COUNT/
   *                 NUMBER_OF_THREADS.
   */
   #define OMP_GUIDED_CS( C_SZ )
   
   /** This definition can be passed as an argument to a parallel for-loop to select automatic task distribution. The task scheduling 
   *   strategy is then decided by the compiler at compile-time.
   */
   #define OMP_AUTO
   
   /** This attribute definition is passed as an argument to a parallel loop and is used to collapse the following nested for-loops for a 
   *   larger task pool with finer grained task distribution. 
   *
   *   \param N   The number of inner for-loops to be collapsed.
   */
   #define OMP_COLLAPSE( N )
   
   /** This attribute definition is passed as an argument to a parallel loop and provides a set of operations which can be performed on 
   *   certain variables (which are created as private copies for each thread) at the very end of the parallel loop. The resulting value 
   *   will be copied into the master thread's instance.
   */
   #define OMP_REDUCTION( ... )
   
   /** This definition is passed as an argument to a parallel for-loop to indicate that threads need not wait for synchronization at the 
   *   end of the loop. This can be used when for example a for-loop is directly followed by another within a parallel region.
   */
   #define OMP_NOWAIT
   
   /** This definition is passed as an argument to a parallel for-loop to indicate that the iterations have to be executed in the same 
   *   order as they would be by the corresponding serial loop. It is highly recommended that this be used alongside with static scheduling 
   *   with chunk-size 1 i.e., interleaved threads, to maximise the concurrency in spite of the ordering.
   */
   #define OMP_ORDERED
   
   
   
   /** This macro declares an SIMD for-loop. The following iterations will be executed concurrently in the SIMD lanes available to the
   *   thread. The ellipsis captures the various attributes of the directive.
   */
   #define SN_OPENMP_SIMD_LOOP( ... )
   
   /** This macro declares a parallelized loop which also uses SIMD. The following iterations are executed by threads which utilize the 
   *   available SIMD lanes. The ellipsis captures the various attributes of the directive.
   */
   #define SN_OPENMP_FOR_SIMD_LOOP( ... )
   
   /** This macro declares that the following function be made compatible for a SIMD loop. This enables the creation of a SIMD version of
   *   the function. The ellipsis captures the various attributes of the directive.
   */
   #define SN_OPENMP_DECLARE_SIMD( ... )
   
   /** This attribute definition can be passed as an argument to a SIMD loop macro. It decides the maximum logical distance 
   *   in the iteration space between any two iterations to be executed concurrently. This can be used to control dependencies.
   *
   *   \param L   The logical distance which is always greater than that between any two iterations in the iteration space.
   */
   #define OMP_SAFELEN( L )
   
   /** This attribute definition identifies the maximum number of arguments to be executed concurrently and can be passed as argument to a 
   *   OMP_DECLARE_SIMD macro.
   */
   #define OMP_SIMDLEN( L )
   
   /** This attribute declares that the listed parameters will have invariant values for all concurrent invocations of the function in the
   *   execution of a single SIMD loop and can be passed as argument to a OMP_DECLARE_SIMD macro.
   */
   #define OMP_UNIFORM( ... )
   
   /** This attribute definition can be passed as an argument to a SIMD loop macro. The values of the master thread instances are copied 
   *   into the respective instances of the other threads. Furthermore, the value of these variables is equal to the iteration value 
   *   multiplied by a specified scalar. The ellipsis captures the arguments of the attribute.
   */
   #define OMP_LINEAR( ... )
   
   /** This attribute hints to the compiler that the elements listed by it are aligned to the specified size in bytes. It is to be used 
   *   only if the alignment is guaranteed, satisfying which it makes the code shorter and perform faster.
   */
   #define OMP_ALIGNED( ... )
   
   /** This attribute informs the compiler that the function will always be called from inside a conditional statement in a SIMD loop. It 
   *   can be passed as an argument to the OMP_DECLARE_SIMD macro.
   */
   #define OMP_INBRANCH
   
   /** This attribute informs the compiler that the function will never be called from inside a conditional statement in a SIMD loop. It 
   *   can be passed as an argument to the OMP_DECLARE_SIMD macro.
   */
   #define OMP_NOT_INBRANCH
   
   
   
   /** This macro represents a work-sharing construct in which any one thread shall execute the following block. */
   #define OMP_SINGLE()
   
   /** This macro declares the following block as a sections region. Each section contained in this region will be assigned one thread 
   *   only. Whether threads which complete their section are allowed to begin executing another is implementation-defined.
   */
   #define OMP_SECTIONS_REGION()
   
   /** This macro declares the following block to be a section within a sections region. */
   #define OMP_SECTION()



   /** This macro represents a synchronization construct which only allows threads past it after every thread has called it. */   
   #define OMP_BARRIER
   
   /** This macro declares the following block to be critical i.e., necessarily serial. It can be used to protect shared resources from the
   *   potential problems of the dreaded race-condition.
   */
   #define OMP_CRITICAL_REGION()
   
   /** This macro allows the execution of the following block by only the master thread. */
   #define OMP_MASTER_REGION()



#else



   
   #ifndef DOXYGEN_SHOULD_SKIP_THIS
   
   /* Necessary constructs */
   #define __SN_PRAGMA__(X)                       _Pragma( #X )
   
   
   
   #define SN_OPENMP_FORK( ... )                  SN_LOG_REPORT_L1_EVENT( LogEventType::OMPFork, "" ); \
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

   #define OMP_STATIC                  schedule( static )
   #define OMP_DYNAMIC                 schedule( dynamic )
   #define OMP_GUIDED                  schedule( guided )
   #define OMP_STATIC_CS( P )          schedule( static, P )
   #define OMP_DYNAMIC_CS( P )         schedule( dynamic, P )
   #define OMP_GUIDED_CS( P )          schedule( guided, P )
   #define OMP_AUTO                    schedule( auto )
   #define OMP_COLLAPSE( N )           collapse( N )
   #define OMP_REDUCTION( ... )        reduction( __VA_ARGS__ )
   #define OMP_NOWAIT                  nowait
   #define OMP_ORDERED                 ordered
   
   #define SN_OPENMP_SIMD_LOOP( ... )        __SN_PRAGMA__( omp simd )
   #define SN_OPENMP_FOR_SIMD_LOOP( ... )    __SN_PRAGMA__( omp for simd )
   #define SN_OPENMP_DECLARE_SIMD( ... )     __SN_PRAGMA__( omp declare simd )
   
   #define OMP_SAFELEN( L )            safelen( L )
   #define OMP_SIMDLEN( L )            simdlen( L )
   #define OMP_UNIFORM( ... )          uniform( __VA_ARGS__ )
   #define OMP_LINEAR( ... )           linear( __VA_ARGS__ )
   #define OMP_ALIGNED( ... )          aligned( __VA_ARGS__ )
   #define OMP_INBRANCH                inbranch
   #define OMP_NOT_INBRANCH            notinbranch
   
   #define OMP_SINGLE()                __SN_PRAGMA__( omp single )
   
   #define OMP_SECTIONS_REGION()       __SN_PRAGMA__( omp sections )
   
   #define OMP_SECTION()               __SN_PRAGMA__( omp section )



   /* Synchronization constructs */   
   #define OMP_BARRIER                 __SN_PRAGMA__( omp barrier )
   #define OMP_ATOMIC_REGION()         __SN_PRAGMA__( omp critical )
   #define OMP_CRITICAL_REGION()       OMP_ATOMIC_REGION()
   #define OMP_MASTER_REGION()         __SN_PRAGMA__( omp master )
   
   #endif   // DOXYSKIP

#endif

#endif   // Header include guard 

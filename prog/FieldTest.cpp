#include <iostream>
#include <vector>

#include <core/ProcSingleton.hpp>
#include <logger/Logger.hpp>

#include <containers/Field.hpp>

#include <concurrency/OpenMP.hpp>
#include <concurrency/ThreadPool.hpp>

using namespace simpleNewton;

void FieldFunc( small_t testSize = 30000 ) {
   
   Field< real_t > cont;
   
   const small_t csize = testSize;
   
   for( small_t i=0; i<csize; ++i ) {
      cont.pushBack( 10.0 );
   }
}

void VectorFunc( small_t testSize = 30000 ) {
   
   std::vector< real_t > cont;
   
   const small_t csize = testSize;
   
   for( small_t i=0; i<csize; ++i ) {
      cont.push_back( 10.0 );
   }
}

void Test() {
   
   SN_LOG_MESSAGE( "Vector vs Field test begun!" );
   
   const small_t testSize = 100;
    
   real_t t1 = ProcSingleton::getDurationFromStart();
   for( small_t i=0; i<testSize; ++i )
      VectorFunc();
   real_t t2 = ProcSingleton::getDurationFromStart();
   
   SN_LOG_PRINT_PRECISE_TIME( "Vector push_back time ", (t2 - t1)/real_cast( testSize ) );
   
   t1 = ProcSingleton::getDurationFromStart();
   for( small_t i=0; i<testSize; ++i )
      FieldFunc();
   t2 = ProcSingleton::getDurationFromStart();
   
   SN_LOG_PRINT_PRECISE_TIME( "Fieldfunc pushBack time ", (t2 - t1)/real_cast( testSize ) );
}



int main( int argc, char ** argv ) {
   
   ProcSingleton::init( argc, argv );
   SN_LOG_SWITCH_ON_CONSOLE_OUTPUT();
   
   Test();
   
   Field< real_t, 10 > f1;
   for( small_t i=0; i<15; ++i ) {
      
      f1.pushBack( real_cast(i) );
   }
   
   std::cout << std::endl;
   for( small_t i=0; i<15; ++i ) {
      std::cout << f1[i] << " " << std::ends;
   }
   std::cout << std::endl;
   
   return 0;
}

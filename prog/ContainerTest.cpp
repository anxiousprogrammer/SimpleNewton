#include <iostream>

#include <core/ProcSingleton.hpp>
#include <logger/Logger.hpp>
#include <containers/SmallMV.hpp>
#include <containers/mpi/OpenMPIBuffer.hpp>

using namespace simpleNewton;

int main( int argc, char ** argv ) {
   
   ProcSingleton::init( argc, argv );
   
   SN_LOG_MESSAGE( "Hi! Testing the logger." );
   
   Vector2<double> v1( 1.0, 2.0 ),      v2( 3.0, 4.0 );
   Vector3<double> v3( 1.0, 2.0, 3.0 ), v4( 4.0, 5.0, 6.0 );
   Matrix2<double> m1( 1.0, 2.0, 
                       3.0, 4.0 );
   Matrix3<double> m2( 1.0, 2.0, 3.0,
                       4.0, 5.0, 6.0,
                       7.0, 8.0, 9.0 );
   Vector2<double> v2_add = v1 + v2 + v1 + v2;
   Vector3<double> v3_add = v3 + v4 + v3 + v4;
   Matrix2<double> m2_add = m1 + m1 + m1 + m1;
   Matrix3<double> m3_add = m2 + m2 + m2 + m2;
   double dot_p_2 = v1.t()*v2, dot_p_3 = v3.t()*v4;
   
   SN_LOG_WATCH_VARIABLES( "Results of addition test: ", v2_add, v3_add, m2_add, m3_add );
   SN_LOG_WATCH_VARIABLES( "Results of dot product test: ", dot_p_2, dot_p_3 );
   
   return 0;
}

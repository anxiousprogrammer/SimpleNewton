#include <iostream>
#include <TypeTraits.hpp>
#include <Typelist.hpp>


int main() {
   
   using namespace simpleNewton;
   
   // Test calc. length and concatenate 'functions' of typelist implementation.
   using TL = SN_CT_TYPELIST< int, unsigned int, long, unsigned long, long long, unsigned long long >;
   using newL = TL::concatenateList< SN_CT_TYPELIST<float, double> >;
   using answer = SN_CT_TYPELIST< int, unsigned int, long, unsigned long, long long, unsigned long long, float, double >;
   SN_CT_ASSERT_SAME_TYPENAME( newL, answer );
   std::cout << TL::concatenateList< SN_CT_TYPELIST<float, double> >::getSize << std::endl;
   
   std::cout << TL::removeFromList< float >::getSize << std::endl;
   
   return 0;
}

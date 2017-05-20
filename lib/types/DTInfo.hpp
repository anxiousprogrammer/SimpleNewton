#ifndef DTInfo_HPP
#define DTInfo_HPP

#ifdef __SN_USE_MPI__
   #include <mpi.h>
#endif

/**||**************************************************************************************************************************************
*
*   Description: MPI datatype specifics - internal implementation to reduce the boilerplate effect
*
|**************************************************************************************************************************************///+

namespace simpleNewton {
namespace types {

// Take care of type first
template< typename TYPE > struct DTInfo;


/* bool */
template<> struct DTInfo< bool > { 
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_INT;
   static constexpr char mpi_name[] = "MPI_INT";
   #endif
   
   static constexpr char name[] = "bool";
};



/* char */
template<> struct DTInfo< char > { 
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_CHAR;
   static constexpr char mpi_name[] = "MPI_CHAR";
   #endif
   
   static constexpr char name[] = "char";
};
                                           
template<> struct DTInfo< unsigned char > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED_CHAR;
   static constexpr char mpi_name[] = "MPI_UNSIGNED_CHAR";
   #endif
   
   static constexpr char name[] = "unsigned char";
};

/* short */
template<> struct DTInfo< short > { 
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_SHORT;
   static constexpr char mpi_name[] = "MPI_SHORT";
   #endif
   
   static constexpr char name[] = "short";
};
                                            
template<> struct DTInfo< unsigned short > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED_SHORT;
   static constexpr char mpi_name[] = "MPI_UNSIGNED_SHORT";
   #endif
   
   static constexpr char name[] = "unsigned short";
};

/* int */
template<> struct DTInfo< int > {

   #ifdef __SN_USE_MPI__    
   static constexpr MPI_Datatype mpi_type = MPI_INT;
   static constexpr char mpi_name[] = "MPI_INT";
   #endif
   
   static constexpr char name[] = "int";
};

template<> struct DTInfo< unsigned int > {

   #ifdef __SN_USE_MPI__   
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED;
   static constexpr char mpi_name[] = "MPI_UNSIGNED";
   #endif
   
   static constexpr char name[] = "unsigned int";
};

/* long */
template<> struct DTInfo< long > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_LONG;
      static constexpr char mpi_name[] = "MPI_LONG";
   #endif
   
   static constexpr char name[] = "long";
};

template<> struct DTInfo< unsigned long > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED_LONG;
   static constexpr char mpi_name[] = "MPI_UNSIGNED_LONG";
   #endif
   
   static constexpr char name[] = "unsigned long";
};

/* long long */
template<> struct DTInfo< long long > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_LONG_LONG;
   static constexpr char mpi_name[] = "MPI_LONG_LONG";
   #endif
   
   static constexpr char name[] = "long long";
};
                                                
template<> struct DTInfo< unsigned long long > {

   #ifdef __SN_USE_MPI__   
   static constexpr MPI_Datatype mpi_type = MPI_UNSIGNED_LONG_LONG;
   static constexpr char mpi_name[] = "MPI_UNSIGNED_LONG_LONG";
   #endif
   
   static constexpr char name[] = "unsigned long long";
};

/* floating point */
template<> struct DTInfo< float >  {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_FLOAT;
   static constexpr char mpi_name[] = "MPI_FLOAT";
   #endif
   
   static constexpr char name[] = "float";
};

template<> struct DTInfo< double > {
   
   #ifdef __SN_USE_MPI__
   static constexpr MPI_Datatype mpi_type = MPI_DOUBLE;
   static constexpr char mpi_name[] = "MPI_DOUBLE";
   #endif
   
   static constexpr char name[] = "double";
};

}   // namespace types
}   // namespace simpleNewton

#endif



#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

namespace simpleNewton {

/**||***************************************************************************************************************************************
*
*   Description: General purpose Functor class for the framework.
*
|***************************************************************************************************************************************///+

template< class RET_TYPE, class... PARAM >
class Functor {
public:
   /* type declaration is free to be accessed by the interface */
   using type = RET_TYPE (*)( PARAM... );
   /* explicit constructor */
   explicit Functor( type _F ) : func_ptr( _F ) {}
   /* Rule of three - copy constructor, copy assignment operator and destructor */
   Functor( const Functor< RET_TYPE, PARAM... > & _ref ) = default;
   Functor< RET_TYPE, PARAM... > & operator=( const Functor< RET_TYPE, PARAM... > & _ref ) = default;
   ~Functor() { reset(); }
   /* Class is exception safe */
   
   /* Main operator */
   inline RET_TYPE operator()( PARAM... args ) { return func_ptr( args... ); }
   
   /* Functionality */
   inline void reset() { func_ptr = nullptr; }

private:
   type func_ptr;
};

}   // namespace simpleNewton

#endif

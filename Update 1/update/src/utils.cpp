

#include "utils.h"
#include "vex.h"

typedef char *string;

template <typename T>
void utils::println(T const & args)
{
  Brain.Screen.print(args);
  Brain.Screen.newLine(); 
}

template<class T, size_t N>
constexpr size_t sizeofArray(T (&)[N]) { return N; }


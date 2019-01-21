#ifndef almost_equal_6FB10D8D_A53B_4C9F_B2DF_C0DD029808EA
#define almost_equal_6FB10D8D_A53B_4C9F_B2DF_C0DD029808EA

#include <vector>

template<typename T> bool almost_equal_vectors(std::vector<T> x, std::vector<T> y, unsigned int ulp);
template<typename T> bool almost_equal(T x, T y, unsigned int ulp);

#endif

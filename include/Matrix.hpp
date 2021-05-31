#ifndef CONTROLBOX_MATRIX_H
#define CONTROLBOX_MATRIX_H

#include <vector>
#include <numeric>
#include <fstream>


namespace ControlBox
{
    using Size = std::size_t;
    constexpr double PI = 3.141592653589793;
    
	struct RowMajor { Size r_ld; constexpr RowMajor(Size r_ld_)noexcept :r_ld(r_ld_) {}; };
	struct ColMajor { Size c_ld; constexpr ColMajor(Size c_ld_)noexcept :c_ld(c_ld_) {}; };
	struct Stride { Size r_ld, c_ld; Stride()noexcept = default; constexpr Stride(Size r_ld_, Size c_ld_)noexcept :r_ld(r_ld_), c_ld(c_ld_) {}; };

	auto inline constexpr T(Size ld)noexcept->ColMajor { return ColMajor(ld); }
	auto inline constexpr at(Size i, Size ld)noexcept->Size { return i * ld; }
	auto inline constexpr at(Size i, Size j, Size ld)noexcept->Size { return i * ld + j; }
	auto inline constexpr next_r(Size at, Size ld)noexcept->Size { return at + ld; }
	auto inline constexpr last_r(Size at, Size ld)noexcept->Size { return at - ld; }
	auto inline constexpr next_c(Size at, Size ld)noexcept->Size { return at + 1; }
	auto inline constexpr last_c(Size at, Size ld)noexcept->Size { return at - 1; }
	auto inline constexpr next_d(Size at, Size ld)noexcept->Size { return at + 1 + ld; }
	auto inline constexpr last_d(Size at, Size ld)noexcept->Size { return at - 1 - ld; }

	auto inline constexpr T(RowMajor r)noexcept->ColMajor { return ColMajor(r.r_ld); }
	auto inline constexpr at(Size i, RowMajor row_major)noexcept->Size { return i * row_major.r_ld; }
	auto inline constexpr at(Size i, Size j, RowMajor row_major)noexcept->Size { return i * row_major.r_ld + j; }
	auto inline constexpr next_r(Size at, RowMajor row_major)noexcept->Size { return at + row_major.r_ld; }
	auto inline constexpr last_r(Size at, RowMajor row_major)noexcept->Size { return at - row_major.r_ld; }
	auto inline constexpr next_c(Size at, RowMajor row_major)noexcept->Size { return at + 1; }
	auto inline constexpr last_c(Size at, RowMajor row_major)noexcept->Size { return at - 1; }
	auto inline constexpr next_d(Size at, RowMajor row_major)noexcept->Size { return at + 1 + row_major.r_ld; }
	auto inline constexpr last_d(Size at, RowMajor row_major)noexcept->Size { return at - 1 - row_major.r_ld; }

	auto inline constexpr T(ColMajor c)noexcept->RowMajor { return RowMajor(c.c_ld); }
	auto inline constexpr at(Size i, ColMajor col_major)noexcept->Size { return i; }
	auto inline constexpr at(Size i, Size j, ColMajor col_major)noexcept->Size { return i + j * col_major.c_ld; }
	auto inline constexpr next_r(Size at, ColMajor col_major)noexcept->Size { return at + 1; }
	auto inline constexpr last_r(Size at, ColMajor col_major)noexcept->Size { return at - 1; }
	auto inline constexpr next_c(Size at, ColMajor col_major)noexcept->Size { return at + col_major.c_ld; }
	auto inline constexpr last_c(Size at, ColMajor col_major)noexcept->Size { return at - col_major.c_ld; }
	auto inline constexpr next_d(Size at, ColMajor col_major)noexcept->Size { return at + 1 + col_major.c_ld; }
	auto inline constexpr last_d(Size at, ColMajor col_major)noexcept->Size { return at - 1 - col_major.c_ld; }

	auto inline constexpr T(Stride s)noexcept->Stride { return Stride(s.c_ld, s.r_ld); }
	auto inline constexpr at(Size i, Stride stride)noexcept->Size { return i * stride.r_ld; }
	auto inline constexpr at(Size i, Size j, Stride stride)noexcept->Size { return i * stride.r_ld + j * stride.c_ld; }
	auto inline constexpr next_r(Size at, Stride stride)noexcept->Size { return at + stride.r_ld; }
	auto inline constexpr last_r(Size at, Stride stride)noexcept->Size { return at - stride.r_ld; }
	auto inline constexpr next_c(Size at, Stride stride)noexcept->Size { return at + stride.c_ld; }
	auto inline constexpr last_c(Size at, Stride stride)noexcept->Size { return at - stride.c_ld; }
	auto inline constexpr next_d(Size at, Stride stride)noexcept->Size { return at + stride.c_ld + stride.r_ld; }
	auto inline constexpr last_d(Size at, Stride stride)noexcept->Size { return at - stride.c_ld - stride.r_ld; }

	template <typename AType>
	auto inline eye(Size m, double *A, AType a_t) noexcept->void
	{
		for (Size i(-1), ai0{ 0 }, aii{ 0 }; ++i < m; ai0 = next_r(ai0, a_t), aii = next_d(aii, a_t))
		{
			for (Size j(-1), aij{ ai0 }; ++j < m; aij = next_c(aij, a_t))
				A[aij] = 0.0;
			A[aii] = 1.0;
		}
	}
	auto inline eye(Size m, double *A) noexcept->void { return eye(m, A, m); }
    
    template <typename AddType, typename Btype, typename Ctype>
    auto inline add(Size m, Size n, const double *A,AddType a_t, const double* B, Btype b_t, double* c, Ctype c_t)->void
    {
        for(Size i(-1), ai0{0}, bi0{0}, ci0{0}; ++i; ai0 = next_r(ai0,a_t), bi0 = next_r(bi0,b_t), ci0 = next_r(ci0,c_t))
        {
            for(Size j(-1), aij{ai0}, bij{bi0}, cij{ci0}; ++j <n; aij = next_c(aij, a_t), bij = next_c(bij, b_t), cij = next_c(cij, c_t))
            {
                c[cij] = A[aij] + B[bij];
            }
        }
    }
    auto inline add(Size m, Size n, const double* A, const double* B, double* c)->void{add(m,n,A,m,B,m,c,m);}

    template<typename Atype, typename Btype, typename Ctype>
    auto inline sub(Size m, Size n, const double* A, Atype a_t, const double* B, Btype b_t, double* c, Ctype c_t)->void
    {
        for(Size i(-1), ai0{0}, bi0{0}, ci0{0}; ++i; ai0 = next_r(ai0,a_t), bi0 = next_r(bi0,b_t), ci0 = next_r(ci0,c_t))
        {
            for(Size j(-1), aij{ai0}, bij{bi0}, cij{ci0}; ++j <n; aij = next_c(aij, a_t), bij = next_c(bij, b_t), cij = next_c(cij, c_t))
            {
                c[cij] = A[aij] + B[bij];
            }
        }
    }
    auto inline sub(Size m, Size n, const double* A, const double* B, double* c)->void{ sub(m,n,A,m,B,m,c,m);}

    template<typename Atype, typename Btype, typename Ctype>
    auto inline mult(Size m, Size n, Size o, const double* A, Atype a_t, const double* B, Btype b_t, double* c, Ctype c_t)
    {
        for(Size i(-1), ai0{0}; ++i < m; ai0 = next_r(ai0, a_t) )
        {
            for(Size j(-1), b0j{0}; ++j< o; b0j = next_c(b0j, b_t))
            {   
                Size cij{at(i,j,c_t)};
                for(Size k(-1), aik{ai0}, bkj{b0j}; ++k < n; aik = next_c(aik, a_t), bkj = next_r(bkj, b_t) )
                {
                    c[cij] += (A[aik] * B[bkj]);
                }
            }
        }
    }
    auto inline mult(Size m, Size n, Size o, const double* A, const double* B, double* c)->void{mult(m,n,o,A,m,B,n,c,m);}
    

}

#endif
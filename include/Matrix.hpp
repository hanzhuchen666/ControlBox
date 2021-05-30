#ifndef CONTROL_MATRIX_H
#define CONTROL_MATRIX_H

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


    
}
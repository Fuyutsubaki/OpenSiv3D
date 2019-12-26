# pragma once
#include "Platform.hpp"
#if SIV3D_PLATFORM(WEB)
# include <emscripten.h>
# include <wasm_simd128.h>
# include <Siv3D/Types.hpp>

union __m128 {
     float     m128_f32[4];
     s3d::uint64    m128_u64[2];
     s3d::int8      m128_i8[16];
     s3d::int16     m128_i16[8];
     s3d::int32     m128_i32[4];
     s3d::int64     m128_i64[2];
     s3d::uint8     m128_u8[16];
     s3d::uint16    m128_u16[8];
     s3d::uint32    m128_u32[4];
 };
union __m128i {
    s3d::int8      m128i_i8[16];
    s3d::int16     m128i_i16[8];
    s3d::int32     m128i_i32[4];
    s3d::int64     m128i_i64[2];
    s3d::uint8     m128i_u8[16];
    s3d::uint16    m128i_u16[8];
    s3d::uint32    m128i_u32[4];
    s3d::uint64    m128i_u64[2];
};

inline constexpr __m128 _mm_set_ss(float w )
{
    return { w, 0.0f, 0.0f, 0.0f };
}
inline constexpr __m128 _mm_set1_ps(float w )
{
    return { w, w, w, w };
}
inline constexpr __m128 _mm_set_ps(float z, float y, float x, float w )
{
    return { w, z, y, x };
}
inline constexpr __m128 _mm_setr_ps (float z, float y, float x, float w )
{
    return { x, y, z, w };
}
inline constexpr __m128 _mm_setzero_ps(void)
{
    return { 0.0f, 0.0f, 0.0f, 0.0f };
}
inline constexpr  __m128i _mm_set_epi32(int _I3, int _I2, int _I1, int _I0)
{
    return {.m128i_i32 =  {_I3, _I2, _I1, _I0}};
}

inline constexpr __m128  _mm_castsi128_ps(__m128i a) {
    return {.m128_i64 = {a.m128i_i64[0], a.m128i_i64[1]}};
}

inline constexpr __m128 _mm_set_ps1(float _A) {
    return _mm_set1_ps(_A);
}

inline constexpr __m128i _mm_set1_epi32(int i) {
    return {.m128i_i32 =  {i,i,i,i}};
}

inline constexpr __m128 _mm_shuffle_ps(__m128 _A, __m128 _B, unsigned int _Imm8) {
    int z = _Imm8 & 0b11000000;
    int y = _Imm8 & 0b00110000;
    int x = _Imm8 & 0b00001100;
    int w = _Imm8 & 0b00000011;
    return {.m128_i32 =  {
        _B.m128_i32[z],
        _B.m128_i32[y],
        _A.m128_i32[x],
        _A.m128_i32[w]}};
}
#define _MM_SHUFFLE(fp3,fp2,fp1,fp0) (((fp3) << 6) | ((fp2) << 4) | \
                                     ((fp1) << 2) | ((fp0)))

inline constexpr float _mm_cvtss_f32(__m128 _A) {
    return _A.m128_f32[0];
}

inline constexpr __m128i _mm_castps_si128(__m128 _A) {
    return {.m128i_i64 = {_A.m128_i64[0], _A.m128_i64[1]}};
}

inline constexpr __m128i _mm_and_si128(__m128i a, __m128i b){
    return {.m128i_i64 = {a.m128i_i64[0] & b.m128i_i64[0], a.m128i_i64[1] & b.m128i_i64[1]}};
}
inline constexpr __m128i _mm_or_si128(__m128i a, __m128i b){
    return {.m128i_i64 = {a.m128i_i64[0] | b.m128i_i64[0], a.m128i_i64[1] | b.m128i_i64[1]}};
}
inline constexpr __m128i _mm_xor_si128(__m128i a, __m128i b){
    return {.m128i_i64 = {a.m128i_i64[0] ^ b.m128i_i64[0], a.m128i_i64[1] ^ b.m128i_i64[1]}};
}
inline constexpr __m128i _mm_slli_epi32(__m128i a, int count){
    return {.m128i_u32 = {a.m128i_u32[0]<<count,a.m128i_u32[1]<<count,a.m128i_u32[2]<<count,a.m128i_u32[3]<<count}};
}
inline constexpr __m128i _mm_srli_epi32(__m128i a, int count){
    return {.m128i_u32 = {a.m128i_u32[0]>>count,a.m128i_u32[1]>>count,a.m128i_u32[2]>>count,a.m128i_u32[3]>>count}};
}
inline constexpr __m128i _mm_slli_si128(__m128i a, int imm){
    // todo: 適当な実装
    return {.m128i_u64 = {(a.m128i_u64[0]<<imm) | (a.m128i_u64[1]>>(64-imm)), a.m128i_u64[1]<<imm }};
}
inline constexpr __m128i _mm_srli_si128(__m128i a, int imm){
    // todo: 適当な実装
    return {.m128i_u64 = {a.m128i_u64[0]>>imm, (a.m128i_u64[0]<<(64-imm)) | (a.m128i_u64[1]>>imm) }};
}
inline constexpr int _mm_cvtsi128_si32(__m128i _A) {
    return _A.m128i_i32[0];
}

inline constexpr __m128 _mm_move_ss( __m128 a, __m128 b){
    return { b.m128_f32[0], a.m128_f32[1], a.m128_f32[2], a.m128_f32[3] };
}

inline constexpr  __m128 _mm_load_ss(float const*_A) {
    return { *_A, 0,0,0 };
}

inline constexpr void _mm_store_ss(float *_V, __m128 _A) {
    *_V = _A.m128_f32[0];
}

// ToDo
inline constexpr __m128 _mm_andnot_ps(__m128 a, __m128 b) {
    return b;
}

inline constexpr __m128 _mm_and_ps(__m128 _A, __m128 _B);
inline constexpr __m128 _mm_andnot_ps(__m128 _A, __m128 _B);
inline constexpr __m128 _mm_or_ps(__m128 _A, __m128 _B);
inline constexpr __m128 _mm_xor_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_movelh_ps(__m128, __m128);

inline constexpr  __m128 _mm_unpacklo_ps(__m128 _A, __m128 _B);

inline constexpr  int _mm_movemask_ps(__m128 _A);

inline constexpr  __m128 _mm_add_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_add_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_sub_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_sub_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_mul_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_mul_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_div_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_div_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_sqrt_ss(__m128 _A);
inline constexpr  __m128 _mm_sqrt_ps(__m128 _A);
inline constexpr  __m128 _mm_rcp_ss(__m128 _A);
inline constexpr  __m128 _mm_rcp_ps(__m128 _A);
inline constexpr  __m128 _mm_rsqrt_ss(__m128 _A);
inline constexpr  __m128 _mm_rsqrt_ps(__m128 _A);
inline constexpr  __m128 _mm_min_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_min_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_max_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_max_ps(__m128 _A, __m128 _B);


/*
 * FP, comparison
 */

inline constexpr  __m128 _mm_cmpeq_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpeq_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmplt_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmplt_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmple_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmple_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpgt_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpgt_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpge_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpge_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpneq_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpneq_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpnlt_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpnlt_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpnle_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpnle_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpngt_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpngt_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpnge_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpnge_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpord_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpord_ps(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpunord_ss(__m128 _A, __m128 _B);
inline constexpr  __m128 _mm_cmpunord_ps(__m128 _A, __m128 _B);
inline constexpr  int _mm_comieq_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_comilt_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_comile_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_comigt_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_comige_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_comineq_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_ucomieq_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_ucomilt_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_ucomile_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_ucomigt_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_ucomige_ss(__m128 _A, __m128 _B);
inline constexpr  int _mm_ucomineq_ss(__m128 _A, __m128 _B);
inline constexpr  void _mm_stream_ps(float *, __m128);
inline constexpr  void _mm_sfence(void);

inline constexpr  __m128i _mm_shuffle_epi32(__m128i _A, int _Imm);
inline constexpr  __m128i _mm_slli_si128(__m128i _A, int _Imm);
inline constexpr   void _mm_storeu_ps(float *_V, __m128 _A);
__m128 _mm_loadu_ps(float const*_A);
__m128 _mm_unpackhi_ps(__m128 _A, __m128 _B);
__m128 _mm_movehl_ps(__m128, __m128);
__m128i _mm_cvtsi32_si128(int _A);
#else
# include <emmintrin.h>
# include <xmmintrin.h>
#endif

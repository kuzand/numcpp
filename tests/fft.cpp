#include "catch.hpp"
#include <numcpp/core.h>
#include <numcpp/base.h>
#include <numcpp/expressions.h>
#include <numcpp/fft.h>

using namespace numcpp;

TEST_CASE( "numcpp/fft/dct", "DCT test" )
{

  {
    size_t N = 8;
    Array<double> x = range(0,N);

    auto y = dct(x);
    auto z = idct(y);

    REQUIRE( norm(x - z) < 1e-6 );
  }

  {
    size_t N = 8;
    Array<float> x = range(0,N);

    auto y = dct(x);
    auto z = idct(y);

    REQUIRE( norm(x - z) < 1e-6 );
  }

}

TEST_CASE( "numcpp/fft/fft", "FFT test" )
{

  {
    size_t N = 8;
    Array<double> x = range(0,N);

    auto y = fft(x);
    auto z = ifft(y);

    REQUIRE( norm(x - z) < 1e-6 );
  }

  {
    size_t N = 8;
    Array<float> x = range(0,N);

    auto y = fft(x);
    auto z = ifft(y);

    REQUIRE( norm(x - z) < 1e-6 );
  }

}

TEST_CASE( "numcpp/fft/rfft", "RFFT test" )
{

  {
    size_t N = 8;
    Array<double> x = range(0,N);

    auto y = rfft(x);
    auto z = irfft(y);

    REQUIRE( norm(x - z) < 1e-6 );
  }

  {
    size_t N = 8;
    Array<float> x = range(0,N);

    auto y = rfft(x);
    auto z = irfft(y);

    REQUIRE( norm(x - z) < 1e-6 );
  }

}

TEST_CASE( "numcpp/fft/nfft", "NFFT test" )
{
  size_t m = 4;
  double sigma = 2.0;

  SECTION( "1D", "1D Tests")
  {
    size_t N = 16;
    size_t M = N;

    Array<double> x = linspace(-0.5, 0.5, M);
    Array<cdouble> fHat = range(0, M);

    auto f = ndftAdjoint(fHat, x, {N});
    auto fApprox = nfftAdjoint(fHat, x, {N}, m, sigma);

    REQUIRE( nrmsd(f, fApprox) < 1e-6 );

    auto g = ndft(f, x);
    auto gApprox = nfft(f, x, m, sigma);

    REQUIRE( nrmsd(g, gApprox) < 1e-6 );
  }

  SECTION( "2D", "2D Tests")
  {
    size_t N = 16;
    size_t M = N*N;

    Array<double> x(M,2); x = linspace(-0.5,0.49,2*M);
    Array<cdouble> fHat = range(0, M);

    auto f = ndftAdjoint(fHat, x, {N,N});
    auto fApprox = nfftAdjoint(fHat, x, {N,N}, m, sigma);

    REQUIRE( nrmsd(f, fApprox) < 1e-6 );

    auto g = ndft(f, x);
    auto gApprox = nfft(f, x, m, sigma);

    REQUIRE( nrmsd(g, gApprox) < 1e-6 );
  }

  SECTION( "3D", "3D Tests")
  {
    size_t N = 8;
    size_t M = N*N*N;

    Array<double> x(M, 3); x = linspace(-0.5,0.5,3*M);
    Array<cdouble> fHat = range(0, M);

    auto f = ndftAdjoint(fHat, x, {N,N,N});
    auto fApprox = nfftAdjoint(fHat, x, {N,N,N}, m, sigma);

    REQUIRE( nrmsd(f, fApprox) < 1e-6 );

    auto g = ndft(f, x);
    auto gApprox = nfft(f, x, m, sigma);

    REQUIRE( nrmsd(g, gApprox) < 1e-6 );
  }
}

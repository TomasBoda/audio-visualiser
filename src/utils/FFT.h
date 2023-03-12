#include <complex>
#include <vector>
#include <cmath>

#ifndef FFT_MUSIC_VISUALISER_FFT_H
#define FFT_MUSIC_VISUALISER_FFT_H

void FFT(std::vector<std::complex<double>> & x) {
    const size_t N = x.size();

    if (N <= 1) {
        return;
    }

    std::vector<std::complex<double>> even(N / 2), odd(N / 2);

    for (size_t i = 0; i < N / 2; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2*i + 1];
    }

    FFT(even);
    FFT(odd);

    for (size_t k = 0; k < N / 2; k++) {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N/2] = even[k] - t;
    }
}

#endif

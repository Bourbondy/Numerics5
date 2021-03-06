// This is head file "myStatisticFunctions.hpp"
// developed by Ziyu Liu,Yu Dong
// Date: 24/05/2020
#include <algorithm>
#include <cmath>
using namespace std;
// function declarations
template <typename T> double mean(const T *dataPtr, const unsigned int &len);
template <typename T> double median(const T *dataPtr, const unsigned int &len);
// variance type: 1) sample variance; 2) population variance
template <typename T>
double var(const T *dataPtr, const unsigned int &len,
           const unsigned int type = 1);
// standard deviation type: 1) sample; 2) population
template <typename T>
double stdDeviation(const T *dataPtr, const unsigned int &len,
                    const unsigned int type = 1);
// p%-quantile
template <typename T>
double quantile(const T *dataPtr, unsigned int len, const unsigned int p = 25);

// function definitions
template <typename T> double mean(const T *dataPtr, const unsigned int &len) {
  double m = 0;
  for (unsigned int i = 0; i < len; i++)
    m += dataPtr[i];
  return (m / len);
}

template <typename T>
double var(const T *dataPtr, const unsigned int &len, const unsigned int type) {
  double m = mean(dataPtr, len);
  double sum;
  for (unsigned int i = 0; i < len; i++)
    sum += pow(dataPtr[i] - m, 2);

  if (type == 1)
    sum = sum / (len - 1);
  else
    sum = sum / len;
  return sum;
}

template <typename T>
double stdDeviation(const T *dataPtr, const unsigned int &len,
                    const unsigned int type) {
  double p = var(dataPtr, len, type);
  return sqrt(p);
}

template <typename T>
double quantile(const T *dataPtr, unsigned int len, const unsigned int p) {
  // step1 sort
  T *copy = nullptr;
  copy = new T[len];
  for (unsigned int i = 0; i < len; i++)
    copy[i] = dataPtr[i];
  sort(copy, copy + len);
  // get p%-quantile
  double m = 0;
  unsigned int k = 0;
  k = floor(len * p / 100.0);
  // judge if len*p% is an integer
  if ((len * p / 100.0 - k) < 0.000000000000001) // integer
    m = (copy[k - 1] + copy[k]) / 2;
  else // not integer
    m = copy[k];
  // delete copy
  delete[] copy;
  copy = nullptr;
  return m;
}

template <typename T> double median(const T *dataPtr, const unsigned int &len) {
  return quantile(dataPtr, len, 50);
}

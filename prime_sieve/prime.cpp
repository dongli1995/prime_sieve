#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
using namespace std;

const int L1D_CACHE_SIZE = 32768;

void prime_sieve(int64_t limit, int64_t N)
{
  int sqrt = (int) std::sqrt((double) limit);
  int64_t count = (limit < 2) ? 0 : 1;
  int64_t s = 2;
  int64_t n = 3;
  int segment_size = L1D_CACHE_SIZE;

  std::vector<char> sieve(segment_size);

  std::vector<char> is_prime(sqrt + 1, 1);
  for (int i = 2; i * i <= sqrt; i++)
    if (is_prime[i])
      for (int j = i * i; j <= sqrt; j += i)
        is_prime[j] = 0;

  std::vector<int> primes;
  std::vector<int> next;

  for (int64_t low = 0; low <= limit; low += segment_size)
  {
    std::fill(sieve.begin(), sieve.end(), 1);

    int64_t high = std::min(low + segment_size - 1, limit);

    for (; s * s <= high; s++)
    {
      if (is_prime[s])
      {
        primes.push_back((int) s);
          next.push_back((int)(s * s - low));
      }
    }

    for (std::size_t i = 1; i < primes.size(); i++)
    {
      int j = next[i];
      for (int k = primes[i] * 2; j < segment_size; j += k)
        sieve[j] = 0;
      next[i] = j - segment_size;
    }

	for (; n <= high; n += 2)
	{
		if (sieve[n - low]) // n is a prime
			count++;
		if (count == N)
		{
			std::cout << n << std::endl;
			return;
		}
	}

  }

}


int main()
{
  int64_t limit = 10000000000;
  int64_t N;
  std::cin >> N;

  prime_sieve(limit, N);
  return 0;
}

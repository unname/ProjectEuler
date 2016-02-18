#include "euler_functions.h"

#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "windows.h"

void get_dividend_by_divisor(size_t k1, size_t k2, size_t *pOut, size_t *ulOut, size_t x, ...)
{
    size_t *pIn;
    *ulOut = 0;

    for (size_t i = k1; i <= k2; i++)
    {
        //Начинаем с первого делителя
        pIn = &x;

        while (*pIn)
        {
            if (i % *pIn)
            {
                pIn++;
            }
            else
            {
                if (pOut)
                {
                    *pOut = i;
                    pOut++;
                }

                (*ulOut)++;
                break;
            }
        }
    }
}

void get_divisor_by_dividend(size_t n, size_t *pOut, size_t *ulOut)
{
    *ulOut = 0;

    if (n == 1)
    {
        if (pOut)
            *pOut = 1;

        *ulOut = 1;

		return;
    }

    if ((n == 2) || (n == 3))
    {
        if (pOut)
        {
            *pOut = 1;
            pOut++;
            *pOut = n;
        }

        *ulOut = 2;

		return;
    }

    for (size_t i = 1; i <= sqrt((double)n); ++i)
    {
        if (n%i == 0)
        {
            if (pOut)
            {
                *pOut = i;
                pOut++;

				if (i != n / i)
				{
					*pOut = n / i;
					pOut++;
				}
            }

            if (i != n / i)
                (*ulOut) += 2;
            else
                (*ulOut)++;
        }
    }
}

void get_divisor_by_dividend_prime(size_t n, size_t *pOut[2], size_t *ulOut)
{
    *ulOut = 0;

    //Если число простое, то раскладывать его не требуется
    if (test_prime(n) || n == 1 || n == 0)
    {
        if (pOut)
        {
            *(pOut[0]) = n;
            *(pOut[0] + 1) = 1;
        }

        *ulOut = 1;

        return;
    }

    //Для составных чисел ищем делители и их степень
    for (size_t i = 2; i <= sqrt((double)n); ++i)
    {
        if (n%i == 0)
        {
            if (test_prime(i))
            {
                if (pOut)
                {
                    size_t k = n;
                    size_t exp_size = 0;

                    while (k && (k%i == 0))
                    {
                        exp_size++;
                        k /= i;
                    }

                    *(pOut[*ulOut]) = i;
                    *(pOut[*ulOut] + 1) = exp_size;
                }

                (*ulOut)++;
            }

            if (n / i != i)
            {
                if (test_prime(n / i))
                {
                    if (pOut)
                    {
                        size_t k = n;
                        size_t exp_size = 0;

                        while (k && (k%i == 0))
                        {
                            exp_size++;
                            k /= i;
                        }

                        *(pOut[*ulOut]) = n / i;
                        *(pOut[*ulOut] + 1) = exp_size;
                    }

                    (*ulOut)++;
                }
            }
        }
    }
}

void get_fibonacci(size_t n1, size_t n2, size_t k, size_t *pOut, size_t *ulOut, bool start)
{
    // Осторожно с большими значениями 
    // рекурсия может привести к переполнению стэка 

    if (start)
    {
        if (pOut)
        {
            pOut[0] = n1;
            pOut[1] = n2;

            pOut += 2;
        }

        *ulOut  = 2;
    }

    size_t current_value = n1 + n2;
    
    if (current_value >= k)
        return;

    if (pOut)
    {
        *pOut = current_value;
        pOut++;
    }

    (*ulOut)++;

    get_fibonacci(n2, current_value, k, pOut, ulOut);
}

void expansion_ds(size_t n, size_t *d, size_t *s)
{
    *d = 0;
    *s = 0;

    if (n % 2 == 0)
    {
        return;
    }

    n = n - 1;

    while (n)
    {
        if (n % 2 == 0)
            (*s)++;
        else
        {
            *d = n;
            break;
        }

        n /= 2;
    }
}

bool test_sprp(size_t n, size_t a)
{
    // n is a strong probable-prime base a (an a-SPRP) if either a^d = 1 (mod n) or
    // (a^(d*2^r) = -1 (mod n) for some non-negative r less than s. 

    size_t d, s, r;

    expansion_ds(n, &d, &s);

    if (d && s)
    {
        if (pow_mod(a, d, n) == 1)
            return true;

        for (r = 0; r <= s - 1; ++r)
        {
            if (pow_mod(a, d * pow(2,(double)r), n) == n - 1)
                return true;
        }
    }

    return false;
}

bool test_divisors(size_t n, size_t k)
{
    //простые делители от 1 до 10.000
    size_t prime_divisors[] =
    {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
        127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
        179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
        233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
        283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
        353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
        419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
        467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
        547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
        607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
        661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
        739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
        811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
        877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
        947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013,
        1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
        1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151,
        1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
        1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291,
        1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
        1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451,
        1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
        1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583,
        1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657,
        1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733,
        1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811,
        1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889,
        1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987,
        1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053,
        2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129,
        2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213,
        2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287,
        2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357,
        2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423,
        2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531,
        2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617,
        2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687,
        2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741,
        2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819,
        2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903,
        2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999,
        3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079,
        3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181,
        3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257,
        3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331,
        3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413,
        3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511,
        3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571,
        3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643,
        3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727,
        3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821,
        3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907,
        3911, 3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989,
        4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057,
        4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139,
        4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231,
        4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297,
        4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409,
        4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493,
        4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583,
        4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651, 4657,
        4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751,
        4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831,
        4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937,
        4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999, 5003,
        5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087,
        5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171, 5179,
        5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261, 5273, 5279,
        5281, 5297, 5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387,
        5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443,
        5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507, 5519, 5521,
        5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591, 5623, 5639,
        5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683, 5689, 5693,
        5701, 5711, 5717, 5737, 5741, 5743, 5749, 5779, 5783, 5791,
        5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849, 5851, 5857,
        5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923, 5927, 5939,
        5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043, 6047, 6053,
        6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133,
        6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211, 6217, 6221,
        6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287, 6299, 6301,
        6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359, 6361, 6367,
        6373, 6379, 6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473,
        6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563, 6569, 6571,
        6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659, 6661, 6673,
        6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733, 6737, 6761,
        6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833,
        6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907, 6911, 6917,
        6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983, 6991, 6997,
        7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069, 7079, 7103,
        7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207,
        7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253, 7283, 7297,
        7307, 7309, 7321, 7331, 7333, 7349, 7351, 7369, 7393, 7411,
        7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487, 7489, 7499,
        7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561,
        7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621, 7639, 7643,
        7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703, 7717, 7723,
        7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817, 7823, 7829,
        7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919,
        7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009, 8011, 8017,
        8039, 8053, 8059, 8069, 8081, 8087, 8089, 8093, 8101, 8111,
        8117, 8123, 8147, 8161, 8167, 8171, 8179, 8191, 8209, 8219,
        8221, 8231, 8233, 8237, 8243, 8263, 8269, 8273, 8287, 8291,
        8293, 8297, 8311, 8317, 8329, 8353, 8363, 8369, 8377, 8387,
        8389, 8419, 8423, 8429, 8431, 8443, 8447, 8461, 8467, 8501,
        8513, 8521, 8527, 8537, 8539, 8543, 8563, 8573, 8581, 8597,
        8599, 8609, 8623, 8627, 8629, 8641, 8647, 8663, 8669, 8677,
        8681, 8689, 8693, 8699, 8707, 8713, 8719, 8731, 8737, 8741,
        8747, 8753, 8761, 8779, 8783, 8803, 8807, 8819, 8821, 8831,
        8837, 8839, 8849, 8861, 8863, 8867, 8887, 8893, 8923, 8929,
        8933, 8941, 8951, 8963, 8969, 8971, 8999, 9001, 9007, 9011,
        9013, 9029, 9041, 9043, 9049, 9059, 9067, 9091, 9103, 9109,
        9127, 9133, 9137, 9151, 9157, 9161, 9173, 9181, 9187, 9199,
        9203, 9209, 9221, 9227, 9239, 9241, 9257, 9277, 9281, 9283,
        9293, 9311, 9319, 9323, 9337, 9341, 9343, 9349, 9371, 9377,
        9391, 9397, 9403, 9413, 9419, 9421, 9431, 9433, 9437, 9439,
        9461, 9463, 9467, 9473, 9479, 9491, 9497, 9511, 9521, 9533,
        9539, 9547, 9551, 9587, 9601, 9613, 9619, 9623, 9629, 9631,
        9643, 9649, 9661, 9677, 9679, 9689, 9697, 9719, 9721, 9733,
        9739, 9743, 9749, 9767, 9769, 9781, 9787, 9791, 9803, 9811,
        9817, 9829, 9833, 9839, 9851, 9857, 9859, 9871, 9883, 9887,
        9901, 9907, 9923, 9929, 9931, 9941, 9949, 9967, 9973,
    };

    double last_k = sqrt((double)n);

    for (size_t i = 0; i < min(k, sizeof(prime_divisors)); ++i)
    {
        if (prime_divisors[i] > last_k)
            break;

        if (n % prime_divisors[i] == 0)
            return false;
    }

    return true;
}

size_t pow_mod(size_t n, size_t e, size_t m)
{
    size_t digit  = 0;
    size_t result = 1;

    while(e)
    {
        if (e % 2)
        {
            size_t k = n;

            for (size_t i = 0; i < digit; ++i)
            {
                k = (k*k) % m;
            }

            result *= k;
            result %= m;
        }

        e = e / 2;
        digit++;
    }

    return result;
}

bool test_prime(size_t n)
{
    if (n == 2)
        return true;
    if (n == 3)
        return true;

    //k = 54 - все делители меньше 257
    if (!test_divisors(n, 54))
        return false;

    //2 и 3-SPRP
    if (!test_sprp(n, 2))
        return false;
    if (!test_sprp(n, 3))
        return false;

    if (n < 1373653)
        return true;

    //5-SPRP
    if (!test_sprp(n, 5))
        return false;

    if (n < 25326001)
        return true;

    //7-SPRP
    if (n == 3215031751)
        return false;

    if (!test_sprp(n, 7))
        return false;

    if (n < 25000000000)
        return true;

    //11-SPRP
    if (!test_sprp(n, 11))
        return false;

    if (n < 2152302898747)
        return true;


    //13-SPRP
    if (!test_sprp(n, 13))
        return false;

    if (n < 3474749660383)
        return true;

    //17-SPRP
    if (!test_sprp(n, 17))
        return false;

    if (n < 341550071728321)
        return true;

    return false;
}

bool test_palindrome(size_t n, size_t b)
{
    if (!b)
        return false;

    size_t capacity = 0;
    size_t n1 = n;
    bool result = true;

    while (n1)
    {
        capacity++;
        n1 = n1 / b;
    }

    size_t* digits = (size_t *)malloc(sizeof(size_t)* capacity);
    
    for (size_t i = 0; i < capacity; ++i)
    {
        digits[i] = n % b;
        n = n / b;
    }

    for (size_t i = 0; i < capacity/2; ++i)
    {
        if (digits[i] != digits[capacity-1-i])
        {
            result = false;
            break;
        }
    }

    free(digits);
    return result;
}

bool test_palindrome(char* n, size_t size)
{
    if (!size)
        return false;

    bool result = true;

    for (size_t i = 0; i < size / 2; ++i)
    {
        if (n[i] != n[size - 1 - i])
        {
            result = false;
            break;
        }
    }

    return result;
}

bool test_power(size_t n, size_t* base, size_t* power)
{
    bool powered = true;

    size_t size = 0;

    get_divisor_by_dividend_prime(n, NULL, &size);
    
    if (!size)
    {
        if (power)
            *power = 0;
        if (base)
            *base = 0;

        return false;
    }

    size_t** exponents = (size_t**)malloc(sizeof(size_t*) * size);
    for (size_t i = 0; i < size; ++i)
        exponents[i] = (size_t*)malloc(sizeof(size_t) * 2);

    get_divisor_by_dividend_prime(n, exponents, &size);

    if (base)
        *base = 1;

    for (size_t i = 0; i < size; ++i)
    {
        if (exponents[0][1] != exponents[i][1])
        {
            powered = false;
            break;
        }

        if (base)
            *base *= exponents[i][0];
    }

    if (powered && exponents[0][1] == 1)
        powered = false;

    if (base)
        if (!powered)
            *base = 0;

    if (power)
        if (powered)
            *power = exponents[0][1];
        else
            *power = 0;

    for (size_t i = 0; i < size; ++i)
        free(exponents[i]);
    free(exponents);

    return powered;
}

void sum_string(char* n1, char*  n2, char* sum, size_t* length)
{
    size_t offset = 0;

    char* max_number;
    char* min_number;
    
    if (strlen(n1) >= strlen(n2))
    {
        max_number = n1;
        min_number = n2;
    }
    else
    {
        max_number = n2;
        min_number = n1;
    }

    char* result = (char*)malloc(sizeof(char) * (strlen(max_number) + 1 + 1));

    for (size_t i = 0; i < strlen(max_number); ++i)
    {
        if (i<strlen(min_number))
            result[i] = max_number[strlen(max_number) - i - 1] + min_number[strlen(min_number) - i - 1] -'0' + offset;
        else
            result[i] = max_number[strlen(max_number) - i - 1] + offset;
  
        if (result[i] - '0' > 9)
        {
            result[i] -= 10;
            offset = 1;
        }
        else
            offset = 0;
    }

    if (offset == 1)
    {   
        result[strlen(max_number)] = 1 + '0';
        *length = strlen(max_number) + 1 + 1;
    }
    else
        *length = strlen(max_number) + 1;
    
    if (sum)
    {
        for (size_t i = 0; i < *length; ++i)
            sum[i] = result[*length - i - 1 - 1];

        sum[*length - 1] = '\0';
    }

    free(result);
}

void sub_string(char* n1, char*  n2, char* sub, size_t* length)
{
    size_t offset = 0;

    char* max_number;
    char* min_number;

    if (strcmp(n1, n2) >= 0)
    {
        max_number = n1;
        min_number = n2;
    }
    else
    {
        max_number = n2;
        min_number = n1;
    }

    if ((strlen(n1) == 1 && n1[0] == '0') || (strlen(n2) == 1 && n2[0] == '0'))
    {
        *length = strlen(max_number) + 1;
        
        if (sub)
        {
            strcpy_s(sub, *length, max_number);
        }

        return;
    }

    char* result = (char*)malloc(sizeof(char) * (strlen(max_number) + 1));

    for (size_t i = 0; i < strlen(max_number); ++i)
    {
        if (i < strlen(min_number))
        {   
            if (max_number[strlen(max_number) - i - 1] - offset >= min_number[strlen(min_number) - i - 1])
            {
                result[i] = max_number[strlen(max_number) - i - 1] - min_number[strlen(min_number) - i - 1] - offset + '0';
                offset = 0;
            }
            else
            {
                result[i] = 10 - (min_number[strlen(min_number) - i - 1] - max_number[strlen(max_number) - i - 1]) - offset + '0';
                offset = 1;
            }
        }
        else
        {
            if (max_number[strlen(max_number) - i - 1])
            {
                result[i] = max_number[strlen(max_number) - i - 1] - offset;
                offset = 0;
            }
            else
            {
                if (offset)
                    result[i] = 10 - max_number[strlen(max_number) - i - 1];
            }
        }
    }

    *length = strlen(max_number);
    while (*length > 0 && result[*length - 1] == '0')
        (*length)--;

    if (*length)
        *length += 1;
    else
        *length += 2;

    if (sub)
    {
        for (size_t i = 0; i < *length - 1; ++i)
            sub[i] = result[*length - i - 1 - 1];

        sub[*length - 1] = '\0';
    }

    free(result);
}

void mult_string(char* n1, char* n2, char* mult, size_t* length)
{
    size_t n1_size = strlen(n1);
    size_t n2_size = strlen(n2);

    size_t interim_size = n1_size + n2_size;
    char* interim_result = (char*)malloc(sizeof(char) * (interim_size + 1));
   
    size_t size = n1_size + n2_size;
    char* result = (char*)malloc(sizeof(char) * (size + 1));

    memset(result, '0', size);
    result[size] = '\0';

    for (size_t i = 0; i < n1_size; ++i)
    {
        size_t current_number = n1[n1_size - i - 1] - '0';
        size_t offset = 0;

        memset(interim_result, '0', interim_size);
        interim_result[interim_size] = '\0';

        for (size_t j = 0; j < n2_size; ++j)
        {   
            size_t current_mult = current_number * (n2[n2_size - j - 1] - '0') + offset;

            offset = current_mult / 10;
            interim_result[interim_size - i - j - 1] = (current_mult%10) + '0';
        }

        if (offset)
        {
            interim_result[interim_size - n2_size - i - 1] = offset + '0';
        }

        sum_string(result, interim_result, result, &size);
    }

    *length = size;

    for (size_t i = 0; result[i] == '0'; ++i)
    {
        (*length)--;
    }

    if (mult)
    {
        for (size_t i = 0; i < *length; ++i)
            mult[*length - 1 - i] = result[size - 1 - i];

        mult[*length - 1] = '\0';
    }

    free(interim_result);
    free(result);
}

void pow_string(char* n1, size_t n2, char* exp, size_t* length)
{
    size_t size = strlen(n1) + 1;
    char* result = (char*)malloc(sizeof(char) * size);

    for (size_t i = 0; i < size; ++i)
    {
        result[i] = n1[i];
    }

    for (size_t i = 0; i < n2 - 1; ++i)
    {
        mult_string(result, n1, NULL, &size);
        result = (char*)realloc(result, sizeof(char) * size);
        mult_string(result, n1, result, &size);
    }

    *length = size;

    if (exp)
    {
        for (size_t i = 0; i < *length; ++i)
            exp[i] = result[i];
    }

    free(result);
}

void factorial_string(size_t n, char* fact, size_t* length)
{
	if (n == 0)
	{
		if (fact)
			fact = "1";
		*length = 1;

		return;
	}

	size_t size;
	char* result		 = (char*)malloc(sizeof(char) * (get_digitsize(n) + 1));
	char* current_number = (char*)malloc(sizeof(char) * (get_digitsize(n) + 1));

	sprintf_s(result, get_digitsize(n) + 1, "%Iu", n);

	for (size_t i = 2; i < n; ++i)
	{
		sprintf_s(current_number, get_digitsize(i) + 1, "%Iu", i);

		mult_string(result, current_number, NULL, &size);
		result = (char*)realloc(result, sizeof(char) * size);
		mult_string(result, current_number, result, &size);
	}

	*length = size;

	if (fact)
	{
		for (size_t i = 0; i < size; ++i)
			fact[i] = result[i];
	}

	free(result);
	free(current_number);
}

void get_сollatz(size_t n, size_t *pOut, size_t *ulOut)
{
    *ulOut = 1;

    if (pOut)
    {
        *pOut = n;
        pOut++;
    }

    while (n != 1)
    {
        if (n % 2)
            n = 3 * n + 1;
        else
            n = n / 2;

        (*ulOut)++;

        if (pOut)
        {
            *pOut = n;
            pOut++;
        }
    }
}

size_t factorial(size_t n, size_t k)
{
    if (n == 0)
        return 1;

    size_t res = 1;

    for (; k <= n; ++k)
    {
        res *= k;
    }

    return res;
}

void factorial(size_t n, size_t *pOut[2], size_t *ulOut, size_t k)
{
    *(ulOut) = 0;

    if (n == 0)
    {
        if (pOut)
        {
            *(pOut[*ulOut]) = 1;
            *(pOut[*ulOut] + 1) = 1;

            *(ulOut)++;
        }
    }

    //Динамический двумерный массив в котором будет аккумулироваться результат
    size_t** output_primes = NULL;
    size_t output_size = 0;
    size_t new_output_size = 0;

    for (; k <= n; ++k)
    {
        //Получаем разлажение на простые множетели для k-ого члена
        size_t size = 0;

        get_divisor_by_dividend_prime(k, NULL, &size);
        
        size_t** primes = (size_t**)malloc(sizeof(size_t*) * size);
        for (size_t i = 0; i < size; ++i)
            primes[i] = (size_t*)malloc(sizeof(size_t) * 2);

        get_divisor_by_dividend_prime(k, primes, &size);


        //Если разложили первый элемент, то копируем его разложение в массив с результатом
        if (!output_primes)
        {
            output_size = size;

            output_primes = (size_t**)malloc(sizeof(size_t*) * output_size);
            for (size_t i = 0; i < output_size; ++i)
                output_primes[i] = (size_t*)malloc(sizeof(size_t) * 2);

            for (size_t i = 0; i < output_size; ++i)
            {
                output_primes[i][0] = primes[i][0];
                output_primes[i][1] = primes[i][1];
            }
        }
        else
        {
            //Если в массиве с результатом уже есть найденный делитель, то увеличиваем его степень, иначе добавляем новый
           
            new_output_size = output_size;

            for (size_t p_cnt = 0; p_cnt < size; ++p_cnt)
            {
                for (size_t out_p_cnt = 0; out_p_cnt < output_size; ++out_p_cnt)
                {
                    //увеличиваем степень
                    if (output_primes[out_p_cnt][0] == primes[p_cnt][0])
                    {
                        output_primes[out_p_cnt][1] += primes[p_cnt][1];
                        break;
                    }
                    else
                    {
                        //добавляем новый элемент
                        if (out_p_cnt == output_size - 1)
                        {
                            new_output_size++;

                            output_primes = (size_t**)realloc(output_primes, sizeof(size_t*) * new_output_size);
                            output_primes[new_output_size-1] = (size_t*)malloc(sizeof(size_t) * 2);

                            output_primes[new_output_size-1][0] = primes[p_cnt][0];
                            output_primes[new_output_size-1][1] = primes[p_cnt][1];
                        }
                    }
                }
            }

            output_size = new_output_size;
        }

        //Освобождение памяти для массива с разложение текущего элемента
        for (size_t i = 0; i < size; ++i)
            free(primes[i]);
        free(primes);
    }

    //Если есть входной буфер, то копируем в него ответ
    if (pOut)
    {
        for (size_t i = 0; i < output_size; ++i)
        {
            *(pOut[i])      = output_primes[i][0];
            *(pOut[i] + 1)  = output_primes[i][1];
        }
    }

    *ulOut = output_size; 

    //Освобождение памяти для массива с результатом
    for (size_t i = 0; i < output_size; ++i)
        free(output_primes[i]);
    free(output_primes);
}

size_t binom_coeff(size_t n, size_t k)
{
    if (k > n)
        return 0;

    if (k == 0 || k == n)
        return 1;

    if (k == 1)
        return n;


    size_t** numerator   = NULL;
    size_t** denominator = NULL;

    size_t n_size = 0;
    size_t d_size = 0;

    //Вычисляем числитель
    factorial(n, NULL, &n_size, max(k, n - k) + 1);

    numerator = (size_t**)malloc(sizeof(size_t*) * n_size);
    for (size_t i = 0; i < n_size; ++i)
        numerator[i] = (size_t*)malloc(sizeof(size_t) * 2);

    factorial(n, numerator, &n_size, max(k, n - k) + 1);

    //Вычисляем знаменатель
    factorial(min(k, n - k), NULL, &d_size);

    denominator = (size_t**)malloc(sizeof(size_t*) * d_size);
    for (size_t i = 0; i < d_size; ++i)
        denominator[i] = (size_t*)malloc(sizeof(size_t) * 2);

    factorial(min(k, n - k), denominator, &d_size);

    //Вычисляем значение дроби
    size_t result = 1;

    for (size_t i = 0; i < n_size; ++i)
    {
        for (size_t j = 0; j < d_size; ++j)
        {
            if (numerator[i][0] == denominator[j][0])
            {
                result *= pow(numerator[i][0], (double)(numerator[i][1] - denominator[j][1]));
                break;
            }

            if (j == d_size - 1)
                result *= pow(numerator[i][0], (double)(numerator[i][1]));
        }
    }
    
    //Освобождение памяти
    for (size_t i = 0; i < n_size; ++i)
        free(numerator[i]);
    free(numerator);

    for (size_t i = 0; i < d_size; ++i)
        free(denominator[i]);
    free(denominator);

    return result;
}

bool test_leapyear(size_t yy)
{
	if (yy % 400 == 0)
		return true;
	else
		if (yy % 100 == 0)
			return false;
		else
			if (yy % 4 == 0)
				return true;
			else
				return false;
}

size_t get_weekday(size_t dd, size_t mm, size_t yy)
{
	size_t first_day = 1; // Первый день нашей эры (01.01.0001) был понедельником
	size_t data_day_offset  = 0;

	size_t months[12] =	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (!dd || !mm || !yy)
		return 0;

	if (mm > 12)
		return 0;

	if (dd > months[mm - 1])
		return 0;

	if (mm == 2 && !test_leapyear(yy) && dd > 28)
		return 0;


	data_day_offset += (yy - 1) * 365 + ((yy - 1) / 4 - ((yy - 1) / 100 - (yy - 1) / 400));

	for (size_t i = 0; i < mm - 1; ++i)
	{
		data_day_offset += months[i];

		if (i == 1 && !test_leapyear(yy))
			data_day_offset--;
	}

	data_day_offset += dd - 1;
	
	return (first_day - 1 + data_day_offset) % 7 + 1;
}

size_t get_digitsize(size_t n, size_t a)
{
	if (!n)
		return 1;

	size_t result = 0;

	while (n)
	{
		result++;
		n /= a;
	}

	return result;
}

void read_file(char* filename, void* pOut, size_t *size)
{
	FILE* f;

	fopen_s(&f, filename, "rb");
	if (f)
	{
		fseek(f, 0, SEEK_END);
		*size = ftell(f);
		fseek(f, 0, SEEK_SET);
		
		if (pOut)
		{
			fread(pOut, 1, *size, f);
			fclose(f);
		}
	}
	else
		printf("\nUnable to open file \"%s\".\n", filename);
}

void sort(char** strings, size_t size, bool numbers)
{
	if (size)
	{
		bool need_check = true;
		char* swap;

		while (need_check)
		{
			need_check = false;

			for (size_t i = 0; i < size - 1; ++i)
			{
                if (numbers == false)
                {
                    if (strcmp(strings[i], strings[i + 1]) > 0)
                    {
                        swap = strings[i];
                        strings[i] = strings[i + 1];
                        strings[i + 1] = swap;

                        need_check = true;
                    }
                }
                else
                {
                    if (strlen(strings[i]) > strlen(strings[i + 1]) ||
                        strlen(strings[i]) == strlen(strings[i + 1]) &&
                        strcmp(strings[i], strings[i + 1]) > 0)
                    {
                        swap = strings[i];
                        strings[i] = strings[i + 1];
                        strings[i + 1] = swap;

                        need_check = true;
                    }
                }
			}
		}
	}
}

void sort(size_t* numbers, size_t size, bool reverse)
{
	if (size)
	{
		bool need_check = true;
		size_t swap;

		while (need_check)
		{
			need_check = false;

			for (size_t i = 0; i < size - 1; ++i)
			{
                if (!reverse)
                {
                    if (numbers[i] > numbers[i + 1])
                    {
                        swap = numbers[i];
                        numbers[i] = numbers[i + 1];
                        numbers[i + 1] = swap;

                        need_check = true;
                    }
                }
                else
                {
                    if (numbers[i] < numbers[i + 1])
                    {
                        swap = numbers[i];
                        numbers[i] = numbers[i + 1];
                        numbers[i + 1] = swap;

                        need_check = true;
                    }
                }
			}
		}
	}
}

int test_perfect(size_t n)
{
	size_t size = 0;

	get_divisor_by_dividend(n, NULL, &size);
	size_t* divisors = (size_t*)malloc(sizeof(size_t) * size);
	get_divisor_by_dividend(n, divisors, &size);

	size_t sum = 0;

	for (size_t i = 0; i < size; ++i)
	{
		sum += divisors[i];
	}

	sum -= n;

	if (sum == n)
		return 0;
	if (sum < n)
		return -1;
	if (sum > n)
		return 1;

	free(divisors);
}

void expansion_factorial(size_t n, size_t* factorials, size_t* size)
{
	*size = 0;

	size_t n1 = n;

	while (n1)
	{
		(*size)++;
		n1 /= *size;
	}

	if (!n)
		*size = 1;

	if (factorials)
	{
		for (size_t i = *size - 1; i > 0; --i)
		{
			factorials[i] = n / factorial(i);

			n %= factorial(i);
		}

		factorials[0] = 0;
	}
}

size_t p(size_t n, size_t k[], size_t size)
{
    sort(k, size, true);

    size_t result = 0;

    while (true)
    {
        if (n < k[size - 1] || size == 1)
            break;
        
        result += p(n, k+1, size-1);

        if (n >= k[0])
            n -= k[0];
        else
            break;
    }
   
    if (n % k[0] == 0 || n == 0)
        result++;

    return result;
}

size_t gcd(size_t n, size_t m)
{
    if (!n || !m)
        return 1;

    size_t r1 = max(n, m) % min(n, m);

    if (r1 == 0)
        return min(n, m);

    size_t r2 = min(n, m) % r1;

    if (r2 == 0)
        return r1;

    while (r1 && r2)
    {
        if (r1 % r2 == 0)
            return r2;
        r1 %= r2;

        if (r2 % r1 == 0)
            return r1;
        r2 %= r1;
    }

    return 0;
}

bool test_pandigital(size_t a, size_t b)
{
    size_t c = 0;
    c = a * b;

    if (get_digitsize(a) + get_digitsize(b) + get_digitsize(c) != 9)
        return false;

    size_t result = 0;

    while (a || b || c)
    {
        if (a % 10)
            result |= 1 << (a % 10 - 1);
        if (b % 10)
            result |= 1 << (b % 10 - 1);
        if (c % 10)
            result |= 1 << (c % 10 - 1);

        a /= 10;
        b /= 10;
        c /= 10;
    }

    if (result == 0x1FF)
        return true;
    else
        return false;
}

bool test_pandigital(size_t n)
{
    if (get_digitsize(n) != 9)
        return false;

    size_t result = 0;

    while (n)
    {
        if (n % 10)
            result |= 1 << (n % 10 - 1);

        n /= 10;
    }

    if (result == 0x1FF)
        return true;
    else
        return false;
}

bool test_pandigital_n(size_t n)
{
    size_t expections[] = { 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF };
    size_t expection = expections[get_digitsize(n) - 1];

    size_t result = 0;

    while (n)
    {
        if (n % 10)
        {
            if (result & (1 << (n % 10 - 1)))
                return false;
            else
                result |= 1 << (n % 10 - 1);
        }
        else
            return false;

        n /= 10;
    }

    if (result == expection)
        return true;
    else
        return false;
}

size_t get_lex_permut(size_t* digits, size_t digits_size, size_t n, bool log)
{
    sort(digits, digits_size);

    size_t size = 0;
    expansion_factorial(n, NULL, &size);
    size_t* fact = (size_t*)malloc(sizeof(size_t) * size);
    expansion_factorial(n, fact, &size);

    if (log)
    {
        printf("\n%Iu = ", n);
        for (int i = size - 1; i >= 0; --i)
            if (fact[i])
                printf("%i!*%Iu + ", i, fact[i]);
        printf("\n");
    }

    size_t* used_digits = NULL;
    size_t used_size = 0;
    size_t result = 0;
    size_t* current_digit = 0;

    for (int i = digits_size - 1; i >= 0; --i)
    {
        if (i < size)
            current_digit = digits + fact[i];
        else
            current_digit = digits;

        for (size_t j = 0; j < used_size; ++j)
        {
            if (current_digit[0] >= used_digits[j])
                current_digit++;
        }

        result += current_digit[0] * pow(10, (double)i);

        used_size++;
        used_digits = (size_t*)realloc(used_digits, sizeof(size_t) * used_size);
        used_digits[used_size - 1] = current_digit[0];

        sort(used_digits, used_size);
    }

    free(used_digits);
    free(fact);

    return result;
}

bool test_permut(size_t n1, size_t n2)
{
    if (get_digitsize(n1) != get_digitsize(n2))
        return false;

    size_t digits1[10] = { 0 };
    size_t digits2[10] = { 0 };

    while (n1)
    {
        digits1[n1 % 10]++;
        digits2[n2 % 10]++;

        n1 /= 10;
        n2 /= 10;
    }
   
    for (size_t i = 0; i < 10; ++i)
    {
        if (digits1[i] != digits2[i])
            return false;
    }

    return true;
}
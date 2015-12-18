
// [Task_1] - �������� ������(� ��� �����������) ������� ��� ������� ���������� ���� �� ���� �� �������������� ���������
//
// k1 � k2      - �������� ������ �����
// pOut � ulOut - ������ �������� ����� � ��� �����������
// x, ...       - �������� ���������
void get_dividend_by_divisor(size_t k1, size_t k2, size_t *pOut, size_t *ulOut, size_t x, ...);

// [Task_12] - �������� ������(� ��� �����������) ��������� ��� ��������������� ��������
//
// n            - �������
// pOut � ulOut - ������ ��������� � ��� ����������� (��������� 1 � n)
void get_divisor_by_dividend(size_t n, size_t *pOut, size_t *ulOut);

// [Task_15] - �������� ��������� ������(� ��� �����������) ��� (������� ��������, �������) ��� ��������������� ��������
//
// n            - �������
// pOut � ulOut - ������ ������� ��������� �� ��������� � ��� ����������� (�� ��������� 1 � n)
void get_divisor_by_dividend_prime(size_t n, size_t *pOut[2], size_t *ulOut);

// [Task_2] - �������� ������(� ��� �����������) �����, ������� ������������ ����� ������������������ '���������'
//
// n1 � n2      - �������� �������� ������������������
// k            - ������� ������ ������
// pOut � ulOut - ������ �������� ����� � ��� �����������
// start        - ������� ����������� ������ ��� (������������� ����������)
void get_fibonacci(size_t n1, size_t n2, size_t k, size_t *pOut, size_t *ulOut, bool start=false);


// [Task_3] - ���������� � ������� �� ������
//
// n      - �������� �����
// e      - �������� �������
// m      - �������� ������
// return - ������� ������� (���������)
size_t pow_mod(size_t n, size_t e, size_t m);

// [Task_3] - ������� ������������� ����� � ������� n = 2^s*d+1
//
// n - �������� �����
// d - ��������� ���������
// s - ��������� �������
void expansion_ds(size_t n, size_t *d, size_t *s);

// [Task_3] - ��������� ����� n �� SPRP (������� �������� ������� �����) �� ��������� a
//
// n           - �������� �����
// a           - ��������� ����������
// return true - ����� �������� a-SPRP 
bool test_sprp(size_t n, size_t a);

// [Task_3] - ��������� ����� n �� ���������� ������� (���������) ���������
//
// n           - �������� �����
// k           - ���������� ��������� ��� ��������
// return true - � ����� �� ������� ��������� �� ������
bool test_divisors(size_t n, size_t k);

// [Task_3] - ��������� ����� n �� ��������
//
// n           - �������� �����
// return true - ����� �������
bool test_prime(size_t n);

// [Task_4] - ��������� ����� n �� ��������������
//
// n           - �������� �����
// b           - ������� ���������
// return true - ����� ���������
bool test_palindrome(size_t n, size_t b);

// [Task_13] - �������� ��������� �����
//
// n1 � n2 - �������� �����
// sum     - ��������� ��������
// length  - ������ ������ ���������� (� ������ terminate null)
void sum_string(char* n1, char* n2, char* sum, size_t* length);

// [Task_16] - ��������� ��������� �����
//
// n1 � n2 - �������� �����
// sum     - ��������� ���������
// length  - ������ ������ ���������� (� ������ terminate null)
void mult_string(char* n1, char* n2, char* mult, size_t* length);

// [Task_16] - ���������� � ������� ��������� �����
//
// n1      - ��������� ���������
// n2      - �������� ������� 
// exp     - ��������� ����������
// length  - ������ ������ ���������� (� ������ terminate null)
void pow_string(char* n1, size_t n2, char* exp, size_t* length);

// [Task_14] - �������� ������(� ��� �����������) ����� �������������� ������������������ '��������' �� �������� ����������
//
// n            - ��������� ��������
// pOut � ulOut - ������ ����� � ��� �����������
void get_�ollatz(size_t n, size_t *pOut, size_t *ulOut);

// [Task_15] - ���������� ����������
//
// n                 - �������� ��������
// k                 - �������� � ������� ������ ������� ���������
// pOut[2] � ulOut   - ��������� �������������� � ���� ������� ������� ���������
//                     �� ��������� � ��� ����������� (�� ��������� 1 � n)
// return            - �������� ���������� n
size_t factorial(size_t n, size_t k = 2);
void factorial(size_t n, size_t *pOut[2], size_t *ulOut, size_t k = 2);

// [Task_15] - �������� �������� ������������� ������������ 
//             ��� ��������������� ����� n � k
//
// n - ������ ����� �������
// k - ���������� ��������� � �������
// return - ���������� ��������� �� n �� k
size_t binom_coeff(size_t n, size_t k);

// [Task_19] - ��������� ��� �� ������������
//
// yy	  - ��� 
// return - true, ���� ����������
bool test_leapyear(size_t yy);


// [Task_19] - �������� ����� ��� ������ ��� ��������� ����
//
// dd	  - ���� ����
// mm	  - ����� ����
// yy	  - ��� ����
// return - ����� ���� ������
size_t get_weekday(size_t dd, size_t mm, size_t yy);
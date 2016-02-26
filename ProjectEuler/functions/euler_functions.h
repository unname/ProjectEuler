
// [Task_1] - получить массив(и его размерность) делимых для которых существует хотя бы один из представленных делителей
//
// k1 и k2      - диапазон поиска чисел
// pOut и ulOut - массив найденых чисел и его размерность
// x, ...       - перечень делителей
void get_dividend_by_divisor(size_t k1, size_t k2, size_t *pOut, size_t *ulOut, size_t x, ...);

// [Task_12] - получить массив(и его размерность) делителей для представленного делимого
//
// n            - делимое
// pOut и ulOut - массив делителей и его размерность (учитывает 1 и n)
void get_divisor_by_dividend(size_t n, size_t *pOut, size_t *ulOut);

// [Task_15] - получить двумерный массив(и его размерность) пар (простой делитель, степень) для представленного делимого
//
// n            - делимое
// pOut и ulOut - массив простых делителей со степенями и его размерность (не учитывает 1 и n)
void get_divisor_by_dividend_prime(size_t n, size_t *pOut[2], size_t *ulOut);

// [Task_2] - получить массив(и его размерность) чисел, которые представляют собой последовательность 'Фибоначчи'
//
// n1 и n2      - элементы задающие последовательность
// k            - верхний предел поиска
// pOut и ulOut - массив найденых чисел и его размерность
// start        - true - функция запускается первый раз (инициализация параметров)
void get_fibonacci(size_t n1, size_t n2, size_t k, size_t *pOut, size_t *ulOut, bool start=false);


// [Task_3] - возведение в степень по модулю
//
// n      - исходное число
// e      - исходная степень
// m      - исходный модуль
// return - остаток деления (результат)
size_t pow_mod(size_t n, size_t e, size_t m);

// [Task_3] - находит представление числа в формате n = 2^s * d + 1
//
// n - исходное число
// d - найденный множитель
// s - найденная степень
void expansion_ds(size_t n, size_t *d, size_t *s);

// [Task_3] - проверяет число n на SPRP (сильное вероятно простое число) по основанию a
//
// n           - исходное число
// a           - основание вычислений
// return true - число является a-SPRP 
bool test_sprp(size_t n, size_t a);

// [Task_3] - проверяет число n на отстутсвие простых (маленьких) делителей
//
// n           - исходное число
// k           - количество делителей для проверки
// return true - у числа не найдено делителей из набора
bool test_divisors(size_t n, size_t k);

// [Task_3] - проверяет число n на простату
//
// n           - исходное число
// return true - число простое
bool test_prime(size_t n);

// [Task_4] - проверяет число n на полиндромность
//
// n           - исходное число
// b           - система счисления
// return true - число полиндром
bool test_palindrome(size_t n, size_t b);
bool test_palindrome(char* n, size_t size);

// [Task_29] - проверяет является ли число n степенью другого числа
//
// n           - исходное число
// return true - число является степенью другого
bool test_power(size_t n, size_t* base = nullptr, size_t* power = nullptr);

// [Task_13] - сложение строковых чисел
//
// n1 и n2 - исходные числа
// sum     - результат сложения
// length  - размер строки результата (с учётом terminate null)
void sum_string(char* n1, char* n2, char* sum, size_t* length);

// [Task_13] - вычитание строковых чисел
//
// n1 и n2 - исходные числа
// sub     - результат вычитания
// length  - размер строки результата (с учётом terminate null)
void sub_string(char* n1, char* n2, char* sub, size_t* length);

// [Task_16] - умножение строковых чисел
//
// n1 и n2 - исходные числа
// sum     - результат умножения
// length  - размер строки результата (с учётом terminate null)
void mult_string(char* n1, char* n2, char* mult, size_t* length);

// [Task_16] - возведение в степень строковых чисел
//
// n1      - строковое основание
// n2      - числовая степень 
// exp     - результат возведения
// length  - размер строки результата (с учётом terminate null)
void pow_string(char* n1, size_t n2, char* exp, size_t* length);

// [Task_20] - вычисление факториала в строковом виде
//
// n       - исходное значение
// fact    - значение факториала
// length  - размер строки результата (с учётом terminate null)
void factorial_string(size_t n, char* fact, size_t* length);

// [Task_14] - получить массив(и его размерность) чисел представляющих последовательность 'Коллатца' по заданому начальному
//
// n            - начальное значение
// pOut и ulOut - массив чисел и его размерность
void get_сollatz(size_t n, size_t *pOut, size_t *ulOut);

// [Task_15] - вычисление факториала
//
// n                 - исходное значение
// k                 - значение с которой начать считать факториал
// pOut[2] и ulOut   - Факториал представленный в виде массива простых делителей
//                     со степенями и его размерность (не учитывает 1 и n)
// return            - значение факториала n
size_t factorial(size_t n, size_t k = 2);
void factorial(size_t n, size_t *pOut[2], size_t *ulOut, size_t k = 2);

// [Task_15] - получить значение биномиального коэффициента 
//             для неотичательцных целых n и k
//
// n - размер общей выборки
// k - количество элементов в выборке
// return - количество сочетаний из n по k
size_t binom_coeff(size_t n, size_t k);

// [Task_19] - проверить год на високосность
//
// yy	  - год 
// return - true, если високосный
bool test_leapyear(size_t yy);


// [Task_19] - получить номер дня недели для указанной даты
//
// dd	  - день даты
// mm	  - месяц даты
// yy	  - год даты
// return - номер длня недели
size_t get_weekday(size_t dd, size_t mm, size_t yy);

// [Task_20] - получить количество цифр в числе;
//
// n      - исходное число
// a      - основание числа
// return - количество цифр в числе
size_t get_digitsize(size_t n, size_t a = 10);

// [Task_22] - чтение файла
//
// filename - имя файла
// pOut		- буфер с данными файла
// size		- размер буфера с данными
void read_file(char* filename, void* pOut, size_t *size);

// [Task_22] - сортировка массива строк
//
// strings - буфер с данными для сортировки
// size    - размер буфера
// num     - true, для сортировки строковых чисел
void sort(char** strings, size_t size, bool numbers = false);

// [Task_23] - сортировка массива чисел
//
// numbers - буфер с данными для сортировки
// size    - размер буфера
void sort(size_t* numbers, size_t size, bool reverse = false);

// [Task_23] - проверка, является ли число идеальным (perfect number)
//
// n	  - число для проверки
// return - = 0, если число идеальное 
//		    < 0, если число дефицитное (deficient number)
//		    > 0, если число избыточное (abundant number)
int test_perfect(size_t n);

// [Task_24] - разложить число на сумму факториалов
//
// n	      - число для разложения
// factorials - массив содержит множители факториалов, а номером факториала является индекс
//			  - например разложение 17 = {0,1,2,2} == 0!*0 + 1!*1 + 2!*2 + 3!*2
// size       - размер массива
void expansion_factorial(size_t n, size_t* factorials, size_t* size);

// [Task_31] - рекуретная формула для подсёчта количества неупорядоченных разбиений числа на слогаемые
//
// n      - исходное число для разбиения
// k[]    - массив с элементами разбиения
// size   - размерность массива
// return - количество неупорядоченных разбиений
size_t p(size_t n, size_t k[], size_t size);

// [Task_33] - поиск наибольшего общего делителя
//
// n      - первое число
// m      - второе число
// return - НОД
size_t gcd(size_t n, size_t m);

// [Task_32] - проверка числа на pandigital
//
// n           - проверяемое число
// a и b       - множетели для проверки (a * b = c) - pandigital triplet
// return true - если число/произведение является pandigital
bool test_pandigital(size_t n);
bool test_pandigital(size_t n, size_t b);

// [Task_41] - проверка числа на n-digit pandigital
//
// n           - проверяемое число
// return true - если число/произведение является n-digit pandigital
bool test_pandigital_n(size_t n);

// [Task_24] - получаем лексикографическую перестановку по заданному массиву и номеру перестановки
//
// digits - массив чисел задающий элементы перестановки
// digits - размер массива чисел
// n      - номер перестановки (отсчёт перестановок начинается с 0)
// log    - true: вывод дополнительные данных
// return - лексикографическая перестановка с порядковым номером 'n'
size_t get_lex_permut(size_t* digits, size_t digits_size, size_t n, bool log = false);

// [Task_62] - проверяем являются ли представленные числа взаимными перестановками
//
// n, ... - перечень проверяемых чисел 
// return - true если все представленые числа являются взаимными перестановками
bool test_permut(size_t n1, size_t n2);

//[Task64] - получаем набор коэфицентов цепной дроби для квадратного корня представленного числа
// 
// number        - число, корень которого раскладывается в цепную дробь
// fraction      - набор коэфициентов цепной дроби (представляется в виде: √n = [a0;(a1,..,ak)] )
// fraction_size - размер набора
void get_continued_fraction(size_t number, size_t* fraction, size_t* fraction_size);

// [Task_66, function based on 57, 64, 65 tasks] - разложение квадратного корня представленного числа в приближённую дробь (цепные дроби)
//
// number        - число, для корня которого строится приближение
// approx_degree - степень приближения (точность дроби)
// numerator     - числитель дроби 
// num_size      - размер числителя (с terminated null)
// denominator   - знаминатель дроби
// den_size      - размер знаминателя (с terminated null)
void get_convergent(size_t number, size_t convergent_degree, char* numerator, size_t* num_size, char* denominator, size_t* den_size);
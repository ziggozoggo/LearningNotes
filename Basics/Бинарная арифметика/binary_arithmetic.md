# Бинарная арифметика (примеры на C)

Материалы по использованию бинарных операций:
- [Как работать с битами (rus)](https://www.youtube.com/watch?v=qewavPO6jcA) 
- [Арифметические действия в двоичной системе (rus)](https://www.youtube.com/watch?v=x92pfbuxhqY)
- [Реализация сложения без использования знака плюс (eng)](https://www.youtube.com/watch?v=qq64FrA2UXQ)

## Оглавление
- [Бинарная арифметика (примеры на C)](#бинарная-арифметика-примеры-на-c)
  - [Оглавление](#оглавление)
  - [Базовые понятия](#базовые-понятия)
  - [Работа с битами](#работа-с-битами)
  - [Арифметические операции](#арифметические-операции)

## Базовые понятия

**1. Двоичная система**

Представление двоичного 8-ми битного числа:

![basic_binary_scheme][basic_binary_scheme]

[basic_binary_scheme]: ./img/01.01_binary_representation.PNG "basic binary scheme"

В общем случае десятичное число представляет собой сумму произведений:

```
bit_status x (2 ^ position)
```

Где:
* bit_status - значение бита; 1 или 0
* position - позиция бита (0 - младший бит, старший в данном случае - 7)

Для приведённой выше схемы результат перевода в десятичную систему будет следующим:

```
(1 x 2 ^ 0) + (0 x 2 ^ 1) + (1 x 2 ^ 2) + ... (0 x 2 ^ 7) =
= 1 x 1 + 0 x 2 + 1 x 4 + 0 = 1 + 0 + 4 = 5
```

Проверка (python):

```
int("101", 2)
```

Обратное преобразование (python):

```
bin(5)
```

**2. Бинарные операции**

X|Y|X & Y|X \| Y|X ^ Y|~X 
|:-:|:-:|:-:|:-:|:-:|:-:|
|0|0|0|0|0|1|
|0|1|0|1|1|1|
|1|0|0|1|1|0|
|1|1|1|1|0|0|

Левый сдвиг << - умножение числа на 2 ^ N, где N - величина сдвига.

Правый сдвиг >> - деление числа на 2 ^ N, где N - величина сдвига.


## Работа с битами

**1. Получить значение бита по заданной позиции**

```
x & (1U << bit_position);
```

Суть:
- Создать маску как "единицу сдвинуть влево до заданной позиции"
- Применить операцию И: если бит 1 -> результатом будет 1;

**2. Перевести бит в 1 в заданной позиции**

```
x |= (1U << bit_position)
```

Суть:
- Создать маску как "единицу сдвинуть влево до заданной позиции"
- Применить операцию ИЛИ; если бит был 0, он станет 1; 

**3. Перевести бит в 0 в заданной позиции**

```
x &= ~(1U << bit_position)
```

Суть:
- Создать маску как "единицу сдвинуть влево до заданной позиции"; инвертировать маску
- Применить операцию И; если бит был 1, он станет 0; 

**4. Инвертировать бит в заданной позиции**

```
x ^= (1U << bit_position);
```

Суть:
- Создать маску как "единицу сдвинуть влево до заданной позиции"; 
- Применить операцию XOR; если бит был 1, он станет 0 и наоборот;

**5. Проверка числа на чётность**

Младший бит четного числа всегда равен 0; таким образом задача сводится к п.1 - получению значения бита в 0-й позиции.


## Арифметические операции 

Все примеры ниже рассматриваются на примере unsigned int 32bits

**1. Сумма**

```
u_int32_t s21_summ_bits(u_int32_t a, u_int32_t b) {
    bool carry_bit = 0;
    u_int32_t res = 0;

    for (int i = 0; i < 32; ++i) {
        bool a_bit = s21_get_bit(a, i);
        bool b_bit = s21_get_bit(b, i);
        bool tmp_res = (a_bit ^ carry_bit) ^ b_bit;

        if (tmp_res) {
            s21_set_bit_on(&res, i);
        } 
        
        carry_bit = (a_bit & b_bit) | ((a_bit | b_bit) & carry_bit);
    }
    return res;
}
```

Решение отталкивается от свойств операции XOR:
```
0 + 0 = 0 ^ 0 = 0
1 + 0 = 1 ^ 0 = 1
1 + 1 = 1 ^ 1 = 0 (перенос 1 на следующий разряд)
0 + 1 = 0 ^ 1 = 1
```

Для переноса разряда используется временная переменная carry_bit, которую мы дополнительно складываем при каждой итерации.

carri_bit = 1 если:
* (a)1 + (b)1 + (carry_bit)(0) -> 10
* (a)1 + (b)0 + (carry_bit)(1) -> 10
* (a)0 + (b)1 + (carry_bit)(1) -> 10

**2. Вычитание**

Отличается от суммы вычислением carry_bit

```
u_int32_t s21_sub_bits(u_int32_t a, u_int32_t b) {
    bool carry_bit = 0;
    u_int32_t res = 0;

    for (int i = 0; i < 32; ++i) {
        bool a_bit = s21_get_bit(a, i);
        bool b_bit = s21_get_bit(b, i);
        bool tmp_res = (a_bit ^ carry_bit) ^ b_bit;

        if (tmp_res) {
            s21_set_bit_on(&res, i);
        } 
        
        carry_bit = (!a_bit & b_bit) | ((!a_bit | b_bit) & carry_bit);
    }
    return res;
}
```

**3. Умножение**

Решение задачи побитового умножения сводится к разложению одного из множителей (лучше - меньшего) на сумму степени двоек. 

```
int binary_mult(int a, int b) {
  int res = 0;
  int l_mult = a;
  int r_mult = b;

  // l_mult x r_mult

  for (int i = 31; i >= 0; --i) {
    if (s21_get_bit(r_mult, i)) {
      res += l_mult << i;
    }
  }

  return res;
}
```

**4. Деление**

Реализует целочисленно деление в столбик с остатком

```
void s21_div(u_int32_t a, u_int32_t b, u_int32_t *res, u_int32_t *rem) {
  
  *res = 0;
  *rem = 0;

  // Получить количество бит делимого
  u_int32_t a_bits_count = 0;
  for (int i = 31; i >= 0; --i) {
    if (s21_get_bit(a, i)) {
      a_bits_count = i + 1; // i <- позиция старшего бита; для получения количества добавляем единицу
      break;
    }
  }

  // Выполнить деление
  for (int i = a_bits_count; i > 0; --i) {
    *rem <<= 1;
    u_int32_t mask = ((a >> (i - 1)) & 1);
    *rem |= mask;

    if (*rem >= b) {
      // Отнять из остатка b
      *rem = s21_sub_bits(*rem, b);
      // Записать результат
      u_int32_t mask = (1 << (i - 1));
      *res |= mask;
    }
  }
}
```



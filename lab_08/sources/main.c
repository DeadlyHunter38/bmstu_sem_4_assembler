/*написать программу, которая вызывает две подпрограммы на ассемблере
первая принимает один параметр - указатель на строку, определяет длину строки
и выполнена в виде ассемблерной вставки
вторая копирует строку с адреса, заданного этим указателем, по адресу,
заданному другим указателем, и реализована в отдельном asm-файле.
Функция должна принимать три параметра: два указателя и длину строки.
Про расположение указателей в памяти и расстояние между ними
заранее ничего не известно (первая строка может начинаться раньше второй
или наоборот; строки могут перекрываться).
Подпрограммы должны соотвествать соглашению о вызовах языка Си и
использовать команды обработки строк с префиксом повторения
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN "50"
#define END_LINE "\n\t"

int asm_len_string(char *string);
extern void copy(char *, char *, int);
char *create_string(char *str);

int main(void)
{
    setbuf(stdout, NULL);
    char string_1[] = "string";
    char string_2[] = "assembler";
    int len_string_1 = 0, len_string_2 = 0;

    len_string_1 = asm_len_string(string_1);
    char *string_result_1 = create_string(string_1);

    len_string_2 = asm_len_string(string_2);
    char *string_result_2 = create_string(string_2);
    
    copy(string_result_1, string_1, len_string_1 + 1);
    copy(string_result_2, string_2, len_string_2 + 1);

    printf("input_string = %s\n", string_1);
    printf("len_string = %d\n", len_string_1);
    printf("string_result = %s\n", string_result_1);

    printf("input_string = %s\n", string_2);
    printf("len_string = %d\n", len_string_2);
    printf("string_result = %s\n", string_result_2);
    
    return 0;
}

int asm_len_string(char *string)
{
    long len = 0;
    __asm__(".intel_syntax noprefix\n\t" //замена синтаксиса AT&T на синтаксис Intel
            //noprefix - позволяет писать код близком к диалекту nasm виде,
            //не используя при записи имен регистров префикс %
            //у GAS два синтаксиса (AT&T, Intel)
            //команда lea выполняет вычисление адреса второго операнда (вход) и занесение в первый
            //все регистры, начинающиеся с "r" - 64-битные
            "lea rdi, [%1]\n\t"
            "mov rcx, " MAX_LEN
            //нам нужно двигаться по строке вперед
            //нам нужно использовать команду scasb для просмотра строки
            //в поиске символа окончания строки $ (в Си - '\0')
            //эта команда смотрит на флаг DF, если он равен нулю, то
            //двигаемся по строке вперед (к di прибавляем 1)
            //если df == 1, то di--;
            "#CLD\n\t" //установить флаг DF в значение 0, чтобы осуществить движение сначала строки
            "mov al, 0\n\t" //поместить терминирующий нуль как признак окончания строки
            //scasb сравнивает каждый байт с al
            "repne scasb\n\t" //выполнить повторение операций над строками, пока
                            //cx не будет равен нулю
            "mov rax, " MAX_LEN END_LINE
            "sub rax, rcx\n\t"
            "dec rax\n\t" //не учитываем терминирующий символ
            "mov %0, eax\n\t" //записываем найденной значение в len  


            : "=r"(len) //выходные параметры
            : "r"(string) //входные параметры
            : "eax");//разрушаемые регистры
                    
    return len;
}

char *create_string(char *str)
{
	return malloc(strlen(str) + 1, sizeof(char));
}
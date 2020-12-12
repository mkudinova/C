//Комментарий про использование указателя на функцию к задаче list_2 из "Односвязные и двусвязные списки" c http://judge.mipt.ru/

/*
Задание:
написать void list_foreach(struct Node * list, void (*func)(Data d, void * param), void * param); // Используется для вызова функции func для всех элементов списка


Давайте рассмотрим подробнее:
void list_foreach(struct Node * list, void (*func)(Data d, void * param), void * param);
есть функция list_foreach, она не возвращает никаких значений, ее аргументы:
1) struct Node * list - указатель на первый элемент в списке;
2) void (*func)(Data d, void * param) - указатель на функцию func, причем с полным указанием типов возвращаемых значений и аргументов.
Т.е., тут написаны требования к функции func:
	- не возвращает значение,
	- имеет 2 аргумента:
		- первый аргумент типа Data
		- второй имеет тип void * - то есть это указатель на что-то, но мы не конкретизируем на что
Но в любом случае, в качестве 2го аргумента передается только указатель на саму функцию, а не ее аргументы или что-то еще.
Обратите внимание на то, что в примере вызова list_foreach на месте 2го аргумента стоит просто имя функции (и это немного похоже на то, как Вы передаете функцию сравнения 2х элементов в qsort).
3) void * param - параметр для func.

Т.е., list_foreach проходит по всем элементам списка и для каждого вызывает функцию func по указателю (который в list_foreach передают 2м аргументом) и с аргументами Data d (который берется из рассматриваемого элемента) и void * param (который был до этого передан в list_foreach в качестве 3го аргумента)

Теперь пример вызова:
list_foreach(list, print_it, stderr);
где
void print_it(Data d, void * param)
{
	FILE * fd = param;
	fprintf(fd, "%d ", d);
}
В list_foreach передали:
list - указатель на начало списка,
print_it - имя функции func (которую надо вызывать),
и stderr - аргумент для этой функции func

И описана сама функция print_it, которая просто печатает d в поток вывода, указанный ее 2м аргументом. В данном случае в качестве 2го аргумента получит stderr (но это мог бы быть и stdout или какой-то открытый файл).

Осталось только рассмотреть, как вызвать функцию по указателю:
внутри list_foreach будет примерно такой код:
// пройти по всем элементам списка и для каждого вызвать
	func(p_current->data, param); // если p_current - указатель на текущий элемент списка
*/

// Вот пример, как это все смотрится вместе (но тут list_foreach работает только для 1го элемента списка, а не для каждого)

#include <stdio.h>
typedef int Data;
struct Node {
	struct Node * next;
	struct Node * prev;
	Data data;
}; // заданное описание структур

void list_foreach(struct Node * list, void (*func)(Data d, void * param), void * param){
    
    struct Node * p_current = list; // рассматривает только 1й элемент
    func(p_current->data, param); // вызывает функцию func для этого элемента
    // передает в func param - тот самый который является 3м аргументом функции list_foreach
    
    return;
}

void print_it(Data d, void * param)
{
	FILE * fd = param; // понимает куда печатать
	fprintf(fd, "%d ", d); // печатает туда
}

int main()
{
    struct Node first_elem;
    struct Node * list;
    list=&first_elem;
    list->data=7;
    list->next=NULL;
    list->prev=NULL;
    // к этому моменту создали один элемент, заполнили его, положили его адрес в list
    
    list_foreach(list, print_it, stdout); // вызов функции list_foreach, которая позовет print_it() и передаст ей stdout в качестве одного из параметров
    
    return 0;
}

/*
Подробнее - Керниган и Ричи (5.12. УКАЗАТЕЛИ НА ФУНКЦИИ 121 - но номера параграфа и страниц могут отличаться в зависимости от издания).
*/

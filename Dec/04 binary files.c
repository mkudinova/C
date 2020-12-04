// copy content of a file

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){ 

	// открыть файлы, имена которых переданы как аргументы командной строки
	FILE * fpr = fopen(argv[1], "rb"); // открыть файл, имя которого передано в argv[1], на чтение как бинарный
	if (fpr == NULL){ // обработка ошибок
		printf("Error - in open");
		return 0;
	}
	FILE * fpw = fopen(argv[2], "wb"); // открыть на запись
	if (fpw == NULL){ // обработка ошибок
		printf("Error - in open");
		fclose (fpr); // закрыть предыдущий файл
		return 0;
	}

	// подсчитать размер содержимого первого файла
	// example of fseek()
	// перевести "курсор" в конец файла 
	int res = fseek(fpr, 0L, SEEK_END); // 1й аргумент - идентификатор файла, 2й - сдвинуть на 0 байт (0L означает рассматривать это 0 как long), 3й - сдвигать от конца файла (бывают SEEK_SET - от начала файла, SEEK_CUR - от текщего положения, or SEEK_END - от конца файла)
	if (res==-1)  // обработка ошибок
		printf("Error - in fseek");

	// example of ftell()
	long length = ftell(fpr); // узнать текущую позицию в файле
	if (res==-1)  // обработка ошибок
		printf("Error - in ftell");

	// теперь в length лежит размер Файла в байтах
	printf("%ld\n", length);
	
	// example of rewind()
	rewind(fpr); // переместить "курсор" в начало файла
	// эквивалентно вызову fseek(fpr, 0L, SEEK_SET);

	// example of fread()
	// считать содержимое первого файла в память
	char * read_buffer = (char *)malloc(sizeof(char) * length); // выделить память, достаточно, чтобы попало все содержимое файла // (char *) - приведение типа, так как по умолчанию malloc возвращает void *
	size_t retr = fread(read_buffer, sizeof(char), length, fpr); // 1й аргумент - указатель на выделенную память, 2й - размер каждого из считываемых элементов, 3й - количество считываемых элементов, 4й - идентификатор файла
	if (retr != length) // обработка ошибок // проверка, что прочитали столько элементов, сколько хотели
		printf("Error - in read");
	
	// распечатать содержимое первого файла
	for (int i=0; i<length; i++){
		printf("%c", read_buffer[i]);
	}
	
	// example of fwrite()
	// записать содержимое первого файла во второй
	size_t retw = fwrite(read_buffer, sizeof(char), length, fpw); // 1й аргумент - указатель на выделенную память, 2й - размер каждого из записываемых элементов, 3й - количество записываемых элементов, 4й - идентификатор файла
	if (retw != length) // обработка ошибок // проверка, что записали столько элементов, сколько хотели
		printf("Error - in write");

	// free all allocated memory
	free(read_buffer);

	// close both files
	fclose (fpr);
	fclose (fpw);
	return 0;
}

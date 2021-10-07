clean:
	rm a.out
	rm original
	rm text1 
	rm text2

EN:
	gcc text_sorter.c text.c qsort.c scmp_en.c -g -fsanitize=address -fsanitize=leak -D EN

RU:
	gcc text_sorter.c text.c qsort.c scmp_ru.c -g -fsanitize=address -fsanitize=leak -D RU

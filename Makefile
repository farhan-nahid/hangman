all:
	gcc main.c -o hangman -lm
	
windows:
	gcc main.windows.c -o hangman 

clean:
	rm hangman
	
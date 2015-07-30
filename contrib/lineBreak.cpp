#include"lineBreak.h"

String lineBreak(String &str1, String &str2, int numberOfCharacters){
	int strSize = str1.getSize();
	char ch;
	if (strSize > numberOfCharacters){
		str2.clear();
		str2 = str1;
		ch = str1[numberOfCharacters];
		str1.erase(numberOfCharacters, strSize - numberOfCharacters);
		if ((str1[numberOfCharacters-1] != ' ')&&(ch !=' ')){ str1.insert(numberOfCharacters,"-"); }
		str2.erase(0, numberOfCharacters);
		
	}
	return str1;
}
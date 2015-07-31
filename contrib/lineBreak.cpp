#include"lineBreak.h"

String lineBreak(String &str1, int numberOfCharacters){
	int strSize = str1.getSize();
	char ch;
	if (strSize > numberOfCharacters){
		String str2="";
		str2 = str1;
		ch = str1[numberOfCharacters];
		str1.erase(numberOfCharacters, strSize - numberOfCharacters);
		if ((str1[numberOfCharacters-1] != ' ')&&(ch !=' ')){ str1.insert(numberOfCharacters,"-"); }
		str2.erase(0, numberOfCharacters);
		str1.insert(str1.getSize(), "\n");
		if (!str2.isEmpty()){
			str1.insert(str1.getSize(), lineBreak(str2, numberOfCharacters));
		}

		
	}
	return str1;
}
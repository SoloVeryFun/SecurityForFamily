#include "Decrypt.h"

String Decrypt::decrypting(String key, String encrycode){
  const int chunkSize = 4;
  String *decryptarray;
  int *keyarray;
  int *encrycodearray;
  int arrayIndex = 0;
  String code = "";

  
  Serial.println(key);
  Serial.println(encrycode);

  //Պատրաստում ենք JSON ինֆորմացիոն բազան
  //Подготавливаем базу данных JSON
  //Preparing the JSON database
  StaticJsonDocument<200> doc;
  doc["ia%@"] = 1;
  doc["g%15"] = 2;
  doc["d$!3"] = 3;
  doc["f&@7"] = 4;
  doc["h*#9"] = 5;
  doc["j^%a"] = 6;
  doc["k)@8"] = 7;
  doc["l+%-"] = 8;
  doc["z-@3"] = 9;
  doc["x=@e"] = 10;
  doc["5b&%"] = 1;
  doc["h#18"] = 2;
  doc["e*!2"] = 3;
  doc["@60o"] = 4;
  doc["i^%0"] = 5;
  doc["s-@4"] = 6;
  doc["m=@5"] = 7;
  doc["n$!1"] = 8;
  doc["y&@9"] = 9;
  doc["w*#7"] = 10;
  doc["c$!@"] = 1;
  doc["k)@4"] = 2;
  doc["f+%-"] = 3;
  doc["u-@1"] = 4;
  doc["o=@6"] = 5;
  doc["p&%3"] = 6;
  doc["q*#5"] = 7;
  doc["r^%8"] = 8;
  doc["v)@2"] = 9;
  doc["t$!0"] = 10;
  doc["d+%-"] = 1;
  doc["l=@3"] = 2;
  doc["g^%9"] = 3;
  doc["v)@5"] = 4;
  doc["p-@0"] = 5;
  doc["e*#6"] = 6;
  doc["f&%2"] = 7;
  doc["g$!7"] = 8;
  doc["x)@4"] = 9;
  doc["c=@1"] = 10;
  doc["e*#1"] = 1;
  doc["m^%4"] = 2;
  doc["h)@7"] = 3;
  doc["w@*2"] = 4;
  doc["q-@8"] = 5;
  doc["r$!5"] = 6;
  doc["s)@0"] = 7;
  doc["t+%-"] = 8;
  doc["z&%3"] = 9;
  doc["b*#9"] = 10;
  doc["f&%6"] = 1;
  doc["n$!0"] = 2;
  doc["i)@3"] = 3;
  doc["x=@9"] = 4;
  doc["r^%7"] = 5;
  doc["t-@5"] = 6;
  doc["u*#4"] = 7;
  doc["v)@1"] = 8;
  doc["a$!@"] = 9;
  doc["d&%2"] = 10;

  //Պատրաստում ենք զանգվածներ
  //Подготавливаем массивы
  //Preparing arrays
  int arraysLength = key.length() / chunkSize + 1; 
  decryptarray = new String[arraysLength]; 
  encrycodearray = new int[arraysLength];
  keyarray = new int[arraysLength];

  //Մշակում ենք բանալին, հետագա գաղտնագրման համար
  //Подготавливаем код для дальнейшей расшифровки
  //Preparing the code for further decryption
  for (int i = 0; i < key.length(); i += chunkSize) {
    decryptarray[arrayIndex++] = key.substring(i, i + chunkSize);
  }

  //Ապագաղտնագրում ենք բանալին
  //Расшифруем ключ
  //Decrypt the key
  for (int i = 0; i < arraysLength-1; i++) {
    int value = doc[decryptarray[i]];
    keyarray[i] = doc[decryptarray[i]];
  }
  
    
  // Ապագաղտնգարում ենք կոդը
  //Расшифруем код
  //Decrypt the code
  int indexCounter = 0;
  String numberStr = "";

  for (int i = 0; i < encrycode.length(); i++){
    char segment = encrycode.charAt(i);

    if(segment != '/'){
      numberStr += segment;
    } 
    else{
      encrycodearray[indexCounter++] = numberStr.toInt();
      numberStr = ""; 
    }
  }

  //Ստանում ենք կոդը
  //Получаем код
  //Get the code
  for (int i = 0; i < arraysLength-1; i++) {
    int eca = encrycodearray[i];
    int da = keyarray[i];
    int number = 0;

    number = eca / da;
    number -= da;

    code += String(number);
  }

  return code;
}



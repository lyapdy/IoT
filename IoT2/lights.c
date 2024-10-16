void setup() {
  // задействуем ножки микроконтроллера:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // логика нажатия кнопки пешеходом
  if (digitalRead(5) == LOW) { // если кнопка не нажата
    digitalWrite(3, HIGH);
    digitalWrite(13, HIGH);
  }
  else { // если кнопка нажата
    for (int i=0; i<3; i++){ // мигаем два раза зеленым цветом для машин
      digitalWrite(13, HIGH);
      delay(300);  
      digitalWrite(13, LOW);
      delay(300);
    };
    digitalWrite(3, HIGH);// красный для пешехода все еще горит
    digitalWrite(12, HIGH);// желтый для машин горит
    delay(900);
    digitalWrite(12, LOW); // желтый для машин потух
    digitalWrite(3, LOW); // красный для пешехода потух
    digitalWrite(11, HIGH); // красный для машин зажегся
    digitalWrite(4, HIGH); // зеленый для пешехода зажегся
    delay(1200); // зеленый для пешехода горит некоторое время
    digitalWrite(12, HIGH); // желтый свет для машин загорается
    for (int i=0; i<3; i++){ // мигаем зеленым для пешехода
      digitalWrite(4, HIGH);
      delay(300);  
      digitalWrite(4, LOW);
      delay(300);  
    }
    digitalWrite(11, LOW); // потухает красный для машин
    digitalWrite(12, LOW); // потухает желтый для машин
    
  }
}

void setup() {
  // ����������� ����� ����������������:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // ������ ������� ������ ���������
  if (digitalRead(5) == LOW) { // ���� ������ �� ������
    digitalWrite(3, HIGH);
    digitalWrite(13, HIGH);
  }
  else { // ���� ������ ������
    for (int i=0; i<3; i++){ // ������ ��� ���� ������� ������ ��� �����
      digitalWrite(13, HIGH);
      delay(300);  
      digitalWrite(13, LOW);
      delay(300);
    };
    digitalWrite(3, HIGH);// ������� ��� �������� ��� ��� �����
    digitalWrite(12, HIGH);// ������ ��� ����� �����
    delay(900);
    digitalWrite(12, LOW); // ������ ��� ����� �����
    digitalWrite(3, LOW); // ������� ��� �������� �����
    digitalWrite(11, HIGH); // ������� ��� ����� �������
    digitalWrite(4, HIGH); // ������� ��� �������� �������
    delay(1200); // ������� ��� �������� ����� ��������� �����
    digitalWrite(12, HIGH); // ������ ���� ��� ����� ����������
    for (int i=0; i<3; i++){ // ������ ������� ��� ��������
      digitalWrite(4, HIGH);
      delay(300);  
      digitalWrite(4, LOW);
      delay(300);  
    }
    digitalWrite(11, LOW); // �������� ������� ��� �����
    digitalWrite(12, LOW); // �������� ������ ��� �����
    
  }
}

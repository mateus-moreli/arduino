#include <Keypad.h>
#include <LiquidCrystal.h> //controla o LCD

LiquidCrystal lcd (13, 12, 11, 10, 9, 8); //fala em qual pinos o lcd ta conectado
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//inicializando as váriaveis que serão utilizadas

long first = 0; //primeiro valor
long second = 0; //segundo valor
double total = 0; //resultado
int position = 0;//posição
char customKey; //qual tecla foi pressionada

//define as teclas 
char keys[ROWS][COLS] = {
    {'1', '2', '3', '/'},
    {'4', '5', '6', '*'},
    {'7', '8', '9', '-'},
    {'C', '0', '=', '+'}
};

//especifica em quais pins cada coisa ta conectada
byte rowPins[ROWS] = {7, 6,5, 4};
byte colPins[COLS] = {3, 2, 1, 0};

//setup

void setup(){
    lcd.begin(16,2);
    lcd.setCursor(5, 0);
    lcd.print("Calculadora");
    lcd.clear();
}

long secondNumber(){
    while (1){
        customKey = customKeypad.getKey();
        if (customKey >= '0' && customKey <= '9'){
            second = second * 10 + (customKey - '0');
            lcd.setCursor(position, 0);
            lcd.print(second);
        }
        if (customKey == 'C'){
            total = 0;
            first = 0;
            second = 0;
            position = 0;
            lcd.clear();
            break;
        }
    }
}

//função principal
void loop(){
    customKey = customKeypad.getKey();
    switch (customKey){
        case '0' ... '9': //recebe o primeiro valor 
                        //enquanto o usuário não apertar uma tecla de operação
            lcd.setCursor(0,0);
            first = first * 10 + (customKey - '0'); //multiplicar por dez pra converter pra próxima casa decimal e subtrair por '0' para converter de ASCII para int
            lcd.print(first);
            position++; //vai pra proxima posiçao
            break;

        case '+':
            if total != 0{
                first = total; 
            } //first = total != 0 ? total : first; (msm coisa mas em uma linha só)
            lcd.setCursor(position, 0);
            lcd.print("+");
            position++;
            second = secondNumber() //pega o segundo numero

            total = first + second;
            lcd.setCursor(1,1);
            lcd.print(total);
            first = 0, second = 0; //reseta os valores
            position = 0
            break;

        case '-':
            first = total != 0 ? total : first;
            lcd.setCursor(position, 0);
            lcd.print('-');
            position++;
            second = secondNumber();
            total = first - second;
            lcd.setCursor(1,1);
            lcd.print(total);
            first = 0, second = 0;
            position = 0;
            break;

        case '*':
            first = total != 0 ? total:first;
            lcd.setCursor(position, 0);
            lcd.print('*');
            position++;
            second = secondNumber();
            total = first * second;
            lcd.setCursor(1,1);
            lcd.print(total);
            first = 0, second = 0;
            position = 0; 
            break;

        case '/':
            first = total != 0 ? total:first;
            lcd.setCursor(position,0);
            lcd.print('/');
            position++;
            seconf = secondNumber;
            total = first / number;
            lcd.setCursor(1,1);
            lcd.print(total);
            first = 0, second = 0;
            position = 0;
            break;

        case 'C':
            total = 0;
            first = 0;
            second = 0;
            position = 0;
            lcd.clear()
            break;
    }
}

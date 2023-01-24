#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double countBalance (double balance, retire_info a) {
    balance = balance * (1 + a.rate_of_return) + a.contribution;
    return balance;
}

void retirement (int startAge, double initial, retire_info working, retire_info retired) {
    double balance = initial;
    for (int i = 0; i < working.months + 1; i++) {
        int age = (startAge + i) / 12;
        int month = (startAge + i) % 12;
        printf("Age %3d month %2d you have $%.2f\n", age, month, balance);//perhaps not printed out in format
        if (i == working.months) {
            break; //no adding to 816th month, stay where you are
        }
        balance = countBalance(balance, working);
    }
    for (int j = 1; j < retired.months ; j++) {
        int age = (startAge + working.months + j) / 12;
        int month = (startAge + working.months + j) % 12;
        balance = countBalance(balance, retired);
        printf("Age %3d month %2d you have $%.2f\n", age, month, balance);
    }
}

int main(void) {
    int startAge = 327;
    double initial = 21345;
    retire_info working = {
    489, 1000.0, 0.045 / 12
  };
    retire_info retired = {
    384, -4000.0, 0.01 / 12
  };  
    retirement (startAge, initial, working, retired);
    return 0;
}

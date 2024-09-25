/*
Author: Luke Walker
        lwalker24@huskers.unl.edu

Date: 2024/9/22

This program will take in command line arguments to create an amortization table
for a 401(k) plan

*/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<ctype.h>

int main (int argc, char **argv) {

    double startingBalance;
    double monthContribute;
    double avgAnnualRateReturn;
    double avgAnnualRateInflate;
    int numYearsRetire;


    startingBalance = atof(argv[1]);
    monthContribute = atof(argv[2]);
    avgAnnualRateReturn = atof(argv[3]);
    avgAnnualRateInflate = atof(argv[4]);
    numYearsRetire = atoi(argv[5]);

    int totalMonths = 12 * numYearsRetire;
    double inflateAdjRate = ((1 + avgAnnualRateReturn) / (1 + avgAnnualRateInflate)) - 1;
    double monthlyInterestRate = inflateAdjRate / 12;
    double compoundTotal = startingBalance * monthlyInterestRate;
    double balance = startingBalance + (compoundTotal) + monthContribute;
    double sumCompoundTotal = 0;


    if (argc != 6) {
        printf("ERROR: Invalid number of command line arguments!\n");
        exit (1);
    }

    if (monthContribute * 12 > 18500) {
        printf("ERROR: monthly contributions exceed $18,500 annual limit\n");
        exit(1);
    }


    //Number of Months until Retirement
    printf("Months          Interest            Balance\n");
    sumCompoundTotal = compoundTotal;
    for(int i = 1; i <= totalMonths; i++) {
        printf("%d", i);
        printf("                $%.2f",compoundTotal);
        printf("           $%.2f",balance);
        printf("\n");
        compoundTotal = round(100 * (balance * monthlyInterestRate)) / 100;
        if (i != totalMonths) {
            balance = round(100 * (balance + monthContribute + (compoundTotal))) / 100;
            sumCompoundTotal += compoundTotal;
        }


    }
    printf("Total Interest Earned: $%.2f\n", sumCompoundTotal);
    printf("Total Nest Egg: $%.2f\n", balance );


    return 0;
}

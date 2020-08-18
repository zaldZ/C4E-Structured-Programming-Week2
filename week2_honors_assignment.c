#include <stdio.h>
#include <stdlib.h>

typedef enum suit{clubs, hearts, spades, diamonds} suit;
typedef enum pips{ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king} pips;
typedef struct card{suit s; pips p;} card;

int main(void){
    //////////////////////////
    //  Variables declaration.
    card pickedCards[7];
    int repeatedPips[7];    //  Array that contains one of each repeated pips on hand.
    int repeatedTimes[7];   //  Array that contains the number of times the pip was repeated.
    int pairCounter, threeOfAKindCounter, fourOfAKindCounter;   //  Auxiliaries counters of available hands.
    int totalOnePair=0, totalTwoPairs=0, totalThreeOfAKind=0, totalFourOfAKind=0, totalNoPair=0, totalFullHouse=0;  //  Total counters of available hands.
    int seedNumber=0;   //  Random number generator initial seed. Reproducibility purposes.
    double numberOfIterations;
    int repetition, i, j, k;    //  Auxiliaries variables.

    printf("Number of iterations: ");
    scanf("%lf", &numberOfIterations);   
    if(numberOfIterations < 1){ return(printf("[Invalid number]: Number of iterations must be an integer bigger than 0.")); }

    for(repetition=0; repetition < numberOfIterations; repetition++){              
        /////////////////
        //  Card picking.
        setHand(pickedCards, 7);
        while(!isValidHand(pickedCards, 7)){
            setHand(pickedCards, 7);
        }

        ////////////////////////////////////////////////////////
        //  Sorting picked cards by eliminating duplicated pips and by counting the duplicates.
        setArrayToValue(repeatedPips, 7, 0);
        setArrayToValue(repeatedTimes, 7, 1);
        repeatedPips[0] = pickedCards[0].p;   //  The first repeated card is the first picked card.  
        i=0; k=1;
        NEXT:
        while(++i < 7){        
            for(j=0; j<k; j++){
                if(pickedCards[i].p == repeatedPips[j]){ repeatedTimes[j]++; goto NEXT; }
            }
            repeatedPips[k++] = pickedCards[i].p;
        }

        //////////////////////////////////////////////
        //  Counting how many times a pattern was set.
        pairCounter = threeOfAKindCounter = fourOfAKindCounter = 0;
        for(i=0; i<7; i++){
            if(repeatedTimes[i] == 2){ pairCounter++; }
            if(repeatedTimes[i] == 3){ threeOfAKindCounter++; totalThreeOfAKind++; }
            if(repeatedTimes[i] == 4){ fourOfAKindCounter++; totalFourOfAKind++; }       
        }
        if(pairCounter > 0){
            if(pairCounter == 1){ totalOnePair++; }
            if(pairCounter == 2){ totalTwoPairs++; }
            if(threeOfAKindCounter > 0){ totalFullHouse++; }
        }
        else{
            if(pairCounter + threeOfAKindCounter + fourOfAKindCounter == 0){ totalNoPair++; }
        }      
               
    }

    /////////////////////
    //  Table of results.
    printf("\nHand\t\t\tNumber of Occurrences\tThis Algorithm's Probability\tMonte Carlo's Probability");
    printf("\nNo Pair\t\t\t%d\t\t\t%lf\t\t\t0.17411920", totalNoPair, totalNoPair/numberOfIterations);
    printf("\nOne Pair\t\t%d\t\t\t%lf\t\t\t0.43822546", totalOnePair, totalOnePair/numberOfIterations);
    printf("\nTwo Pairs\t\t%d\t\t\t%lf\t\t\t0.23495536", totalTwoPairs, totalTwoPairs/numberOfIterations);
    printf("\nThree of a Kind\t\t%d\t\t\t%lf\t\t\t0.04829870", totalThreeOfAKind, totalThreeOfAKind/numberOfIterations);
    printf("\nFour of a Kind\t\t%d\t\t\t%lf\t\t\t0.00168067", totalFourOfAKind, totalFourOfAKind/numberOfIterations);
    printf("\nFull House\t\t%d\t\t\t%lf\t\t\t0.02596102", totalFullHouse, totalFullHouse/numberOfIterations);
}

/////////////////
//  Functions  //
/////////////////

////////////////////////////////////////////////////
//  Fill the card array x with random card elements.
void setHand(card x[], int xSize){
    while(xSize-- > 0){
        x[xSize].s = (rand() % 4);    //  Random suit.
        x[xSize].p = (rand() % 13);   //  Random pips.
    }
}

//////////////////////////////////////////////////////////////////
//  Checks if card array x contains repeated cards.
//  e.g. if x contains two 'Ace of Spades', isValidHand returns 0.
int isValidHand(card x[], int xSize){
    int i, j;
    for(i=0; i<(xSize-1); i++){
        for(j=i+1; j<xSize; j++){
            if(x[i].s==x[j].s && x[i].p==x[j].p){ return(0); }
        }
    }
    return(1);
}

///////////////////////////////////////////////
//  Set all elements of array x to the value y.
void setArrayToValue(int x[], int xSize, int y){
    while(xSize-- > 0){
        x[xSize] = y;
    }
}
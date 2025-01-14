#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <Windows.h>
#include <math.h>

//Create variable zone -fah
char SuitCard[4] = {'\x05', '\x04', '\x03', '\x06'}; //Suit of card
int card[52];                                        //Set of card follow by 0-51
int CardOnHand[17][3];                               //Card on hand at player  card
int SumCardOnHand[17];                               //Amount of player's card
int CardOut = 0;                                     //How many card is out
int SumPlayer;                                       //How many player
int PlayerPoint[17];                                 //Score

//Create function zone
void NumOfCard(int Playernow, int cardnow); //Show card                     -fah
void Pointcheck(int Playernow);             //Check Point                   -fah
void ShowPoint(int Playernow);              //Show what you got             -fah
void ClearTerminal(int sec);                //Clear Terminal                -na
void Winer(int maxpoint);                   //Show winer                    -praew
void UnBoxDeck();                           //Unbox card deck               -ryu
void DrawCard();                            //Draw 2 card                   -na
void Playing();                             //Playing                       -fah
void Shuffle();                             //Shuffle card                  -ryu
void Welcome();                             //Welcome                       -ryu
int AskToPlayAgain();                       //Wanna play again              -praew
int Player();                               //Input sum of player           -na
int Result();                               //Out put max point of player   -praew

//main zone
int main()
{
    srand(time(NULL));
    system("cls");
    UnBoxDeck();
    Welcome();
    do
    {
        Shuffle();
        SumPlayer = Player();
        system("cls");
        DrawCard();
        Playing();
        Winer(Result());
    } while (AskToPlayAgain());
    printf("\nThx For Playing :)\n\n");
}

//edit function zone
void ClearTerminal(int sec)
{
    printf("\nDelete Text in\n\n");
    for (int count = sec; count > 0; count--)
    {
        printf("**%d**\n", count);
        sleep(1);
    }
    system("cls");
}

void NumOfCard(int Playernow, int cardnow)
{
    char NumCard[3];
    if (CardOnHand[Playernow][cardnow] % 13 + 1 < 10)
        NumCard[0] = '0' + (CardOnHand[Playernow][cardnow] % 13 + 1), NumCard[1] = '\0';
    else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 10)
        strcpy(NumCard, "10");
    else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 11)
        strcpy(NumCard, "J");
    else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 12)
        strcpy(NumCard, "Q");
    else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 13)
        strcpy(NumCard, "K");

    printf("%s %c \n", NumCard, SuitCard[(CardOnHand[Playernow][cardnow]) / 13]); //41/13=3
}

void Pointcheck(int Playernow)
{
    int point = 0, straight = 0;
    for (int cardnow = 0; cardnow < 2; cardnow++)
    { //1-2card
        if (!(CardOnHand[Playernow][cardnow] % 13 + 1 > 10))
        {
            point += CardOnHand[Playernow][cardnow] % 13 + 1;
        }
    }
    point %= 10;
    if (SumCardOnHand[Playernow] == 3)
    {
        for (int firstcard = 0; firstcard < 3; firstcard++)
        { //Check straight
            for (int secondcard = 0; secondcard < 3; secondcard++)
            {
                for (int thirdcard = 0; thirdcard < 3; thirdcard++)
                {
                    if (firstcard == secondcard || firstcard == thirdcard || secondcard == thirdcard)
                    {
                        continue;
                    }
                    if (CardOnHand[Playernow][firstcard] % 13 == CardOnHand[Playernow][secondcard] % 13 + 1 && CardOnHand[Playernow][secondcard] % 13 + 1 == CardOnHand[Playernow][thirdcard] % 13 + 2)
                    {
                        straight = 1;
                    }
                }
            }
        }
    }
    if (point == 9 && SumCardOnHand[Playernow] == 2)
    { //check POK 9
        PlayerPoint[Playernow] = 4000;
    }
    else if (point == 8 && SumCardOnHand[Playernow] == 2)
    { //check POK 8
        PlayerPoint[Playernow] = 3000;
    }
    else if (CardOnHand[Playernow][0] % 13 + 1 == CardOnHand[Playernow][1] % 13 + 1 && CardOnHand[Playernow][1] % 13 + 1 == CardOnHand[Playernow][2] % 13 + 1 && SumCardOnHand[Playernow] == 3)
    { //check TONG
        PlayerPoint[Playernow] = (2000 + (CardOnHand[Playernow][0] % 13 + 1));
    }
    else if (straight)
    { //Straight ?
        if (CardOnHand[Playernow][0] / 13 == CardOnHand[Playernow][1] / 13 && CardOnHand[Playernow][1] / 13 == CardOnHand[Playernow][2] / 13)
        { //Check StraightFlush
            PlayerPoint[Playernow] = (1000 + (CardOnHand[Playernow][0] % 13 + 1) + ((CardOnHand[Playernow][0]) / 13 + 1) * 100);
        }
        else
        { //NonFlush
            PlayerPoint[Playernow] = (1000 + (CardOnHand[Playernow][0] % 13 + 1));
        }
    }
    else if (CardOnHand[Playernow][0] % 13 + 1 > 10 && CardOnHand[Playernow][1] % 13 + 1 > 10 && CardOnHand[Playernow][2] % 13 + 1 > 10)
    { //check royal
        PlayerPoint[Playernow] = 500;
    }
    else
    { //Just point
        for (int cardnow = 0; cardnow < SumCardOnHand[Playernow]; cardnow++)
        {
            if (CardOnHand[Playernow][cardnow] % 13 + 1 < 10)
            {
                PlayerPoint[Playernow] += CardOnHand[Playernow][cardnow] % 13 + 1;
            }
        }
        PlayerPoint[Playernow] %= 10;
    }
}

void ShowPoint(int Playernow)
{
    PlayerPoint[Playernow] = 0;
    Pointcheck(Playernow);
    if (PlayerPoint[Playernow] == 4000)
        printf("Now you have POK 9\n");
    else if (PlayerPoint[Playernow] == 3000)
        printf("Now you have POK 8\n");
    else if (PlayerPoint[Playernow] > 2000)
        printf("Now you have triple card\n");
    else if (PlayerPoint[Playernow] >= 1100)
        printf("Now you have StraightFlush\n");
    else if (PlayerPoint[Playernow] > 1000)
        printf("Now you have Straight\n");
    else if (PlayerPoint[Playernow] == 500)
        printf("Now you have Yellow\n");
    else
        printf("Now you have %d point\n", PlayerPoint[Playernow]);
}

void Playing()
{
    char WordIn[3];
    for (int Playernow = 0; Playernow < SumPlayer; Playernow++)
    {
        //wait for see card
        printf("\n\tPlayer %d \n", Playernow + 1);
        printf("\nWrite \'Y\' when you wanna see your cards :");
        do
        {
            scanf(" %s", WordIn);
            if (strcmp(WordIn, "Y"))
                printf("Wrong input. Please try again :");
        } while (strcmp(WordIn, "Y"));
        printf("\n");
        for (int cardnow = 0; cardnow < 2; cardnow++)
            NumOfCard(Playernow, cardnow);

        //wait for write (Y/N)
        ShowPoint(Playernow);
        if (PlayerPoint[Playernow] != 4000 && PlayerPoint[Playernow] != 3000)
        {
            printf("\nDo you wanna draw one more card (Y/N) :");
            do
            {
                scanf(" %s", WordIn);
                if (strcmp(WordIn, "Y") && strcmp(WordIn, "N"))
                    printf("Wrong input. Please try again (Y/N) :");
            } while (strcmp(WordIn, "Y") && strcmp(WordIn, "N"));
            //if Y draw one more card
            if (!(strcmp(WordIn, "Y")))
            {
                CardOnHand[Playernow][2] = card[CardOut++];
                SumCardOnHand[Playernow]++;
                printf("You got : ");
                NumOfCard(Playernow, 2);
            }
            ShowPoint(Playernow);
        }
        //wait for SumPlayer finished
        printf("\nWrite \'Y\' when you got finished :");
        do
        {
            scanf(" %s", WordIn);
            if (strcmp(WordIn, "Y"))
                printf("Wrong input. Please try again :");
        } while (strcmp(WordIn, "Y"));
        ClearTerminal(3);
    }
}

void DrawCard()
{
    for (int cardnow = 0; cardnow < 2; cardnow++)
    {
        for (int Playernow = 0; Playernow < SumPlayer; Playernow++)
        {
            CardOnHand[Playernow][cardnow] = card[CardOut++];
            SumCardOnHand[Playernow]++;
        }
    }
}

int AskToPlayAgain()
{
    char WordIn[3];
    printf("\nDo you want to play again (Y/N) :");
    do
    { // "Y" = "Y"
        scanf(" %s", WordIn);
        if (!(strcmp(WordIn, "Y")))
            return 1;
        else if (!(strcmp(WordIn, "N")))
            return 0;
        else
            printf("\n\nWrong input. Please try again (Y/N) :");
    } while (strcmp(WordIn, "Y") && strcmp(WordIn, "N"));
    ClearTerminal(3);
}

void UnBoxDeck()
{
    //just set card 0 to 51
    for (int cardnow = 0; cardnow < 52; cardnow++)
        card[cardnow] = cardnow;
}

void Shuffle()
{
    int randvariable, keepvariable;
    CardOut = 0;
    for (int cardnow = 0; cardnow < 52; cardnow++)
    {
        randvariable = rand() % 52;
        keepvariable = card[cardnow];
        card[cardnow] = card[randvariable];
        card[randvariable] = keepvariable;
    }
    //just set up variable
    for (int Playernow = 0; Playernow < 17; Playernow++)
    {
        for (int cardnow = 0; cardnow < 3; cardnow++)
        {
            CardOnHand[Playernow][cardnow] = 0;
        }
        PlayerPoint[Playernow] = 0;
        SumCardOnHand[Playernow] = 0;
    }
    //If you want to test some case do it here
/*
    card[0] = 1;
    card[2] = 2;
    card[4] = 0;
*/
}

void Welcome()
{
    printf("\tWelcome to PokDeng from TNI15 \x03\n\n");
}

int Player()
{
    char numberplayer[10];
    int playernow, checkplayer = 0;
    printf("How many player Do you want to play ? (^_^) : ");
again:
    checkplayer = 0;
    scanf("%s", numberplayer);
    for (playernow = 0; playernow < strlen(numberplayer); ++playernow)
    {
        if (!(numberplayer[playernow] >= '0' && numberplayer[playernow] <= '9'))
        {
            ++checkplayer;
        }
    }
    if (!checkplayer)
    {
        for (playernow = 0; playernow < strlen(numberplayer); ++playernow)
        {
            checkplayer += (numberplayer[playernow] - 48) * pow(10, (strlen(numberplayer) - playernow - 1));
        }
        if (checkplayer > 17)
        {
            printf("\nToo many players , Card not Enought!! (-_^) \n\n");
            printf("Please try again : ");
            goto again;
        }
        else if (checkplayer < 2)
        {
            printf("\nNot Enought players (T_T) \n\n");
            printf("Please try again : ");
            goto again;
        }
    }
    else
    {
        printf("\nPlease Enter The Positive Number!!! (>_<) \n\n");
        printf("Please try again : ");
        goto again;
    }
    return checkplayer;
}

int Result()
{
    int maxpoint = 0;
    for (int Playernow = 0; Playernow < SumPlayer; Playernow++)
        if (PlayerPoint[Playernow] > maxpoint)
            maxpoint = PlayerPoint[Playernow];
    return maxpoint;
}

void Winer(int maxpoint)
{
    char NumCard[3];
    for (int Playernow = 0; Playernow < SumPlayer; Playernow++)
    {
        if (maxpoint == PlayerPoint[Playernow])
        {
            printf("\tPlayer %d Win\n", Playernow + 1);
            for (int cardnow = 0; cardnow < SumCardOnHand[Playernow]; cardnow++)
            {
                if (CardOnHand[Playernow][cardnow] % 13 + 1 < 10)
                    NumCard[0] = '0' + (CardOnHand[Playernow][cardnow] % 13 + 1), NumCard[1] = '\0';
                else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 10)
                    strcpy(NumCard, "10");
                else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 11)
                    strcpy(NumCard, "J");
                else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 12)
                    strcpy(NumCard, "Q");
                else if (CardOnHand[Playernow][cardnow] % 13 + 1 == 13)
                    strcpy(NumCard, "K");
                printf("%s %c \n", NumCard, SuitCard[(CardOnHand[Playernow][cardnow]) / 13]);
            }
        }
    }
}
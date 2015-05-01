#include <stdio.h>
#include <stdlib.h>

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)

 int getPin (int x)
{

    const int  g_registers = 3;         // Number of shift registers in use
    int g_registerArray [g_registers];

    unsigned int allActive = 1;
    int RegisterPin = x;
    allActive= ((0x3FF)^(allActive<<(RegisterPin)));    // 3FF = 11 1111 1111

    /*  g_registerArray [2] =  (allActive&(0x3F0000))>>16 ; // 03F0000   = 11 1111 1111 0000 0000 0000 0000 // generates MSB
      g_registerArray [1] =   (allActive&(0xFF00))>>8;  //FF00 = 1111 1111 0000 0000     //generates mid
      g_registerArray [0] =   (allActive&(0xFF));   // FF = 1111 1111
*/
     // printf("OUTPUT of get pin allActive:  "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
    //                      BYTETOBINARY(allActive>>16), BYTETOBINARY(allActive>>8), BYTETOBINARY(allActive));
    return allActive;
}

int getLed(int r , int c)
{
    int rawR = (0x3FF&(getPin(r)));
    int rawC = (0x3FFC00&(getPin(c)));


   // printf("OUTPUT of rawR:       "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
    //                      BYTETOBINARY(rawR>>16), BYTETOBINARY(rawR>>8), BYTETOBINARY(rawR));

    printf("OUTPUT of rawC:       "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
                          BYTETOBINARY(rawC>>16), BYTETOBINARY(rawC>>8), BYTETOBINARY(rawC));

    return (  rawR | rawC  );   //3FF = 11 1111 1111   3FFC00 = 11 1111 1111 1100 0000 0000
}

int main()
{
    for(int dexter =11; dexter<22; dexter++){
    int row =0 ,column= dexter;
    //////////////////////////////////print x///////////////////////////////////////
 /*printf("enter the row: ");
 scanf("%d",&row);
 printf("enter the column: ");
 scanf("%d",&column);*/
 int x1 = getPin(row);
 int x2 = getPin(column);
 int x3 = getLed(row,column);

 //printf("OUTPUT of row:        "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
 //           BYTETOBINARY(x1>>16), BYTETOBINARY(x1>>8), BYTETOBINARY(x1));

  printf("OUTPUT of %d column:  "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n", dexter,
            BYTETOBINARY(x2>>16), BYTETOBINARY(x2>>8), BYTETOBINARY(x2));
 printf("OUTPUT of led:        "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
            BYTETOBINARY(x3>>16), BYTETOBINARY(x3>>8), BYTETOBINARY(x3));

    int y2 =  (x3&(0x3F0000))>>16 ; // 03F0000   = 11 1111 0000 0000 0000 0000 // generates MSB
     int y1 =   (x3&(0xFF00))>>8;  //FF00 = 1111 1111 0000 0000     //generates mid
      int y0 =   x3&(0xFF);   // FF = 1111 1111

      printf("OUTPUT of y2:         "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
            BYTETOBINARY(y2>>16), BYTETOBINARY(y2>>8), BYTETOBINARY(y2));

    ("OUTPUT of y1:         "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
           BYTETOBINARY(y1>>16), BYTETOBINARY(y1>>8), BYTETOBINARY(y1));

    ("OUTPUT of y0:         "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN" "BYTETOBINARYPATTERN"\n",
         BYTETOBINARY(y0>>16), BYTETOBINARY(y0>>8), BYTETOBINARY(y0));

 }
}

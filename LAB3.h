#include <stdio.h>

#define Set_Bit(Reg,Bit)    (Reg |=1<<Bit)
#define Clear_Bit(Reg,Bit)  (Reg &=~(1<<Bit))
#define Get_Bit(Reg,Bit)    ((Reg & 1<<Bit)>>Bit)
#define Toggle_Bit(Reg,Bit) (Reg^=1<<Bit)
const int  g_pinCommLatch = 9;      // This pin gets sets low when I want the 595s to listen
const int  g_pinClock     = 10;     // This pin is used by ShiftOut to toggle to say there's another bit to shift
const int  g_pinData    = 8;        // This pin is used to pass the next bit
const int  g_registers = 3;         // Number of shift registers in use
signed long int       g_registerArray [g_registers]; // Array of numbers to pass to shift registers


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void setup()
  {
    pinMode (g_pinCommLatch, OUTPUT);
    pinMode (g_pinClock, OUTPUT);
    pinMode (g_pinData, OUTPUT);
    Serial.begin (9600);
    
  }  
             
/////////////////////////////////////////////////////creating SPI /////////////////////////////////////////////////////////////////////////////////////

void sendSerialData ( int registerCount,  // How many shift registers? 
   signed long int *pValueArray)   // Array of bytes with LSByte in array [0]
{
  // Signal to the 595s to listen for data
  digitalWrite (g_pinCommLatch, LOW);
  
  for (int reg = registerCount; reg > 0; reg--)
  {
    int value = pValueArray [reg - 1];
    
    for (int bitMask = 128; bitMask > 0; bitMask >>= 1)   //output are 128 ,64 ,32,16,8,4,2,1
    {
      digitalWrite (g_pinClock, LOW);
    
      digitalWrite (g_pinData, value & bitMask ? HIGH : LOW);
        
      digitalWrite (g_pinClock, HIGH);
    }
  }
  
  digitalWrite (g_pinCommLatch, HIGH);    // Signal to the 595s that I'm done sending
}  // sendSerialData
///////////////////////////////////////////////////////////Activating Pin///////////////////////////////////////////////////////////////////////////////
signed long int getPin (int x)
{
    signed long int allActive = 1;
    signed long int RegisterPin = x;
    allActive= ((0x3FF)^(allActive<<(RegisterPin)));    // 3FF = 11 1111 1111   
    return allActive;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 signed long int getLed(int r , int c)
{
   signed long  int rawR = (0x3FF&(getPin(r)));      //3FF = 11 1111 1111 
    signed long int rawC = (0x3FFC00&(getPin(c)));  // 3FFC00 = 11 1111 1111 1100 0000 0000


    return ( rawC | rawR   );   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void loop()
  {
    for(int i=0;i<10;i++) {
    for(int j=10;j<22;j++){
     signed long int dummy =getLed(i,j);
    Serial.println(dummy, BIN);
 ////////////////////////////////////////////////creating data packets//////////////////////////////////////////////////////////////////////////////////////////           
      g_registerArray [2] =  ((dummy&(0x3F0000))>>16)&0x3F ; // 03F0000   = 11 1111 0000 0000 0000 0000 // generates MSB
      g_registerArray [1] =   (dummy&(0xFF00))>>8;  //FF00 = 1111 1111 0000 0000     //generates mid
      g_registerArray [0] =   dummy&(0xFF);   // FF = 1111 1111
 //////////////////////////////////////////////////sending data packets////////////////////////////////////////////////////////////////////////////////////////     
    sendSerialData (g_registers, g_registerArray);
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
    // delay(50);
    }  
}
} // loop

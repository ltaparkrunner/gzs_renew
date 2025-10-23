extern "C" {
#include<stdio.h>
#include<stdlib.h>
#include "sio.h"
#include "i7k.h"
#include "i87000_lnx.h"

#define RBUF_SIZE 80
static char szCmd8K[80], szRec8K[80];
static char cmd[80];

extern char HexToAscii(WORD hex);
extern char AsciiToHex(char cASCII);

/************************************************************/
/*  AnalogInAll_87K											*/
/*															*/	
/*  Command:  "#AA" + [CHK(2)] + CR(1) 						*/ 
/*  Response: ">+00.000+01.001+02.002+03.003-04.004			*/
/*				-05.005-06.006-07.007" + [CHK(2)] + CR(1)	*/
/*															*/
/*  Module: I-87013,I8017H,I-87017,I-87018					*/
/*          ADAM-5013/17/18									*/
/*															*/
/*  [Apr,15,2002] by Kevin									*/
/************************************************************/
WORD /*CALLBACK*/ AnalogInAll_87K_2(DWORD dwBuf[], float fBuf[],
        char szSend[], char szReceive[])
{

	char   wPort,wFlag,cTemp[80],wMode;
	WORD   wRet,wAddr,wRetVal,i,j,wCheckSum,wTimeOut,wT,k;
//	WORD   wTotalChannel;
	int   wTotalByte;
//	int	   iRet;
	DWORD  dwID;
	char *endptr;
	

	//---------------------- input -------------------------------------
	wPort=(char)dwBuf[0];			// RS-232 port number: 1/2/3/4/..../255
	wAddr=(WORD)dwBuf[1];			// module address: 0x00 to 0xFF
	dwID=dwBuf[2];					// module ID: 0x87013/87017/87018
	wCheckSum=(WORD)dwBuf[3];       // checksum: 0=disable, 1=enable
	wTimeOut=(WORD)dwBuf[4];        // TimeOut constant: normal=100
	wFlag=(char)dwBuf[6];			// flag: 0=no save, 1=save send/receive string
	wMode=(char)dwBuf[7];			// 0: Engineer 1:% FSR 2:Hex
	printf("wPort: %d, wAddr: %x, dwID: %x,  wCheckSum: %x, wTimeOut: %x, wFlag: %x, wMode: %x\n", 
		wPort, wAddr, dwID, wCheckSum, wTimeOut, wFlag, wMode);
	switch (dwID)
	{
		case 0x87013:
/*			wTotalChannel=4;
			if(wCheckSum)
				wTotalByte=31;
			else 
				wTotalByte=29;*/
			break;    
		case 0x87017:
		case 0x87018:
		case 0x87015:
		case 0x87019:
/*			wTotalChannel=8;
			if(wCheckSum)
				wTotalByte=59;
			else 
				wTotalByte=57;*/
			break; 
		default: return(ModuleIdError);
	}

	// #define RCVBUF_SIZE 64
	 char rbuf[RBUF_SIZE] = {0};
	__tod_t texp;
//	sprintf(szCmd8K,"#%02X",wAddr);
//	sprintf(cmd,"#%02X\r",wAddr);
	sprintf(cmd,"#%02X",wAddr);
	printf("CMD: %s \n", cmd);
//	wRetVal=Send_Receive_Cmd(wPort, szCmd8K, szRec8K, wTimeOut, wCheckSum,&wT);
	sio_set_noncan(wPort);
	sio_set_timer(wPort, 0, 1);		/* set timeout for 0.4 sec */

	int r = i7k_send_readt_cs(wPort, cmd, rbuf, RBUF_SIZE, &texp);
	wRetVal = r;
//	int wRetVal2=i7k_send_readt_cs(int fd, const char *cmd, char *rbuf, int rmax, __tod_t * texp);

	if(wFlag)
	{
		strcpy(szSend,szCmd8K);
		strcpy(szReceive,szRec8K);
	}
	printf("7k_send_readt without CR k result: %d \n", wRetVal);
	printf("Receive_Binary results: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n", 
        rbuf[0],  rbuf[1], rbuf[2], rbuf[3],
        rbuf[4],  rbuf[5], rbuf[6], rbuf[7],
        rbuf[8],  rbuf[9], rbuf[10], rbuf[11],
        rbuf[12],  rbuf[13], rbuf[14], rbuf[15]);

	sprintf(cmd, "#%02X\r", 0);
	static char buf2[80] = {0};
	char * rez = _i7k_gum_chksum((void*)buf2, cmd);

	printf("buf is: %x %x %x %x %x %x %x \n", 
	buf2[0],  buf2[1], buf2[2], buf2[3],
	buf2[4],  buf2[5], buf2[6]);
	r = i7k_send_readt(wPort, buf2, rbuf, RBUF_SIZE, &texp);
	printf("Receive_Binary results 2: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n", 
        rbuf[0],  rbuf[1], rbuf[2], rbuf[3],
        rbuf[4],  rbuf[5], rbuf[6], rbuf[7],
        rbuf[8],  rbuf[9], rbuf[10], rbuf[11],
        rbuf[12],  rbuf[13], rbuf[14], rbuf[15]);

	sleep(1);
	r = i7k_send_readt_cs(wPort, cmd, rbuf, RBUF_SIZE, &texp);
	printf("Receive_Binary results 3: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n", 
        rbuf[0],  rbuf[1], rbuf[2], rbuf[3],
        rbuf[4],  rbuf[5], rbuf[6], rbuf[7],
        rbuf[8],  rbuf[9], rbuf[10], rbuf[11],
        rbuf[12],  rbuf[13], rbuf[14], rbuf[15]);	
//	if (wRetVal != NoError) return wRetVal;


/*	// Only check the first byte and total bytes.
	if((szRec8K[0]!='>') && (strlen(szRec8K)!=wTotalByte)) 
		return ResultStrCheckError;
	
	for(i=0;i<wTotalChannel;i++)
	{
		//"+03.567" one float value uses 7 bytes.
		for(j=0;j<7;j++)		
			cTemp[j]=szRec8K[1+i*7+j];	
		cTemp[7]=0;
		fBuf[i]=(float)atof(cTemp);
	}
  return(NoError);*/

  switch (dwID)
  {
     
     case 0x87013 :
	 case 0x87017 :
	 case 0x87018 :
	 case 0x87016 :
	 case 0x87015 :
	 case 0x87019 :

		i=1; //szCmd8K[0] is '>'
		k=0;
		j=0;
		if (!wCheckSum) 
	 		wTotalByte=strlen(szRec8K);
		else
			wTotalByte=strlen(szRec8K)-2;
		printf("The length of szRec8K is: %d", wTotalByte);
		sleep(1);
		wRet=NoError;
		switch(wMode)
		{
			case 0: //Engineer
			case 1: //Fsr
			case 3:
			while(i<=wTotalByte) //57 (without '\0')
			{
				if(szRec8K[i]=='+' || szRec8K[i]=='-' || i==wTotalByte)
				{
					if(i!=1 || i==wTotalByte)
					{
						cTemp[j]='\0';
						if( !memcmp(cTemp,"-0000",5) && strlen(cTemp)==5)
						{
							strcpy(cTemp,"-9999");
							wRet=UnderInputRange;
						}
						else if( !memcmp(cTemp,"+9999",5) )
							wRet=ExceedInputRange;
						else if( !memcmp(cTemp,"+999.99",6) )
							wRet=ExceedInputRange;
						fBuf[k]=(float)atof(cTemp);
						if(i==wTotalByte)
							break;
						k++;
						j=0;
					}				  
					cTemp[j++]=szRec8K[i];
				}
				else			
					cTemp[j++]=szRec8K[i];			
				i++;
			}
			break;
			case 2: //Hex
			k=8; //Start from wBuf[8]
			while(i<=wTotalByte) // (without '\0')
			{
				if(szRec8K[i]=='+' || szRec8K[i]=='-')
				{				
					for(j=0;j<5;j++)
						cTemp[j]=szRec8K[i++];
					if(!memcmp(cTemp,"-0000",5))
					{
						strcpy(cTemp,"8000"); //UnderRange or the cable broke
						wRet=UnderInputRange;
					}
					else if(!memcmp(cTemp,"+9999",5))
					{
						strcpy(cTemp,"7FFF"); //OverRange or the cable broke
						wRet=ExceedInputRange;
					}

				}
				else			
				{
					for(j=0;j<4;j++)
						cTemp[j]=szRec8K[i++];					
				}				
				cTemp[j]='\0';
				dwBuf[k++]=(DWORD)strtol(cTemp,&endptr,16); //16 means 0~9,A~F
//				fBuf[k]=(float)atof(cTemp);
				if(!memcmp(cTemp,"7FFF",4))										
					wRet=ExceedInputRange;				
				
					
			}
			break;
		}
		break;
  }
	return wRet;
}

WORD /*CALLBACK*/ AnalogOut_87K(DWORD dwBuf[], float fBuf[],
        char szSend[], char szReceive[])
{
  char    wPort,wFlag,c1,c2;
  WORD    wAddr,wRetVal,i,wCheckSum,wTimeOut,wT,wChannel;
  	__tod_t texp;
  float   fVal;
  WORD    wRecStrLen;
  char    OutCh[10];
  DWORD   dwID;


  //---------------------- input -------------------------------------
  wPort=(char)dwBuf[0];   // RS-232 port number: 1/2/3/4/..../255
  wAddr=(WORD)dwBuf[1];         // module address: 0x00 to 0xFF
  dwID=dwBuf[2];           // module ID: 0x87016/21/22/24
  wCheckSum=(WORD)dwBuf[3];     // checksum: 0=disable, 1=enable
  wTimeOut=(WORD)dwBuf[4];      // TimeOut constant: normal=100
  wChannel=(WORD)dwBuf[5];      // Not used if module ID is 7016/7021
                             // Channel No.(0 to 1) if module ID is 7022
                             // Channel No.(0 to 3) if module ID is 7024
  wFlag=(char)dwBuf[6];   // flag: 0=no save, 1=save send/receive string
  fVal=fBuf[0];          // analog output value
  //---------------------- output ------------------------------------
                          // void
  if( dwID==0x87016 )
  {
     sprintf(OutCh,"%+07.3f",fBuf[0]);

     szCmd8K[0]='$';
     c2=(char)(wAddr&0x0f);
     wAddr=wAddr/16;
     c1=(char)(wAddr&0x0f);
     szCmd8K[1]=HexToAscii(c1);
     szCmd8K[2]=HexToAscii(c2);
     szCmd8K[3]='7';

     szCmd8K[4]=OutCh[0];
     szCmd8K[5]=OutCh[1];
     szCmd8K[6]=OutCh[2];
     szCmd8K[7]=OutCh[3];
     szCmd8K[8]=OutCh[4];
     szCmd8K[9]=OutCh[5];
     szCmd8K[10]=OutCh[6];
     szCmd8K[11]=0;
  }
  else if(dwID==0x87021)
  {
   szCmd8K[0]='#';
   c2=(char)(wAddr&0x0f);
   wAddr=wAddr/16;
   c1=(char)(wAddr&0x0f);
   szCmd8K[1] = HexToAscii(c1);
   szCmd8K[2] = HexToAscii(c2);

   szCmd8K[5]='.';
   szCmd8K[9]=0;


   i=(WORD)(fVal/10.0);
   szCmd8K[3]=i+0x30; fVal-=i*10;

   i=(int)fVal;
   szCmd8K[4]=i+0x30; fVal-=i;

   fVal *= (float)10.0;
   i=(int)fVal;
   szCmd8K[6]=i+0x30; fVal-=(float)i;

   fVal *= (float)10.0;
   i=(int)fVal;
   szCmd8K[7]=i+0x30; fVal-=(float)i;

   fVal *= (float)10.0;
   i=(int)fVal;
   szCmd8K[8]=i+0x30;
  }
  else if( dwID==0x87022 )
  {
     if( wChannel>2 )
     {
         return(AdChannelError);
     }
     sprintf(OutCh,"%06.3f",fBuf[0]);

     szCmd8K[0]='#';
     c2=(char)(wAddr&0x0f);
     wAddr=wAddr/16;
     c1=(char)(wAddr&0x0f);
     szCmd8K[1] = HexToAscii(c1);
     szCmd8K[2] = HexToAscii(c2);
     szCmd8K[3]=(char)(wChannel+0x30);  // channel No.

     szCmd8K[4]=OutCh[0];
     szCmd8K[5]=OutCh[1];
     szCmd8K[6]=OutCh[2];
     szCmd8K[7]=OutCh[3];
     szCmd8K[8]=OutCh[4];
     szCmd8K[9]=OutCh[5];
     szCmd8K[10]=0;
   }
  else if( dwID==0x87024 )
  {
     if( wChannel>3 )
     {
         return(AdChannelError);
     }
     sprintf(OutCh,"%+07.3f",fBuf[0]);
         // sprintf(OutCh,"%+07.1f",fValue);


     szCmd8K[0]='#';
     c2=(char)(wAddr&0x0f);
     wAddr=wAddr/16;
     c1=(char)(wAddr&0x0f);
     szCmd8K[1] = HexToAscii(c1);
     szCmd8K[2] = HexToAscii(c2);
     szCmd8K[3]=(char)(wChannel+0x30);  // channel No.

     szCmd8K[4]=OutCh[0];
     szCmd8K[5]=OutCh[1];
     szCmd8K[6]=OutCh[2];
     szCmd8K[7]=OutCh[3];
     szCmd8K[8]=OutCh[4];
     szCmd8K[9]=OutCh[5];
     szCmd8K[10]=OutCh[6];
     szCmd8K[11]=0;
  }


  else if( dwID==0x87026 )
  {
     if( wChannel>2 )
     {
         return(AdChannelError);
     }
     sprintf(OutCh,"%06.3f",fBuf[0]);

     szCmd8K[0]='#';
     c2=(char)(wAddr&0x0f);
     wAddr=wAddr/16;
     c1=(char)(wAddr&0x0f);
     szCmd8K[1] = HexToAscii(c1);
     szCmd8K[2] = HexToAscii(c2);
     szCmd8K[3]=(char)(wChannel+0x30);  // channel No.

     szCmd8K[4]=OutCh[0];
     szCmd8K[5]=OutCh[1];
     szCmd8K[6]=OutCh[2];
     szCmd8K[7]=OutCh[3];
     szCmd8K[8]=OutCh[4];
     szCmd8K[9]=OutCh[5];
     szCmd8K[10]=0;
   }



  else
     return(ModuleIdError);


   if(wFlag==1)
   {
      strcpy(szSend,szCmd8K);
      szReceive[0]=0;
   }
//   wRetVal=Send_Receive_Cmd(wPort, szCmd8K, szRec8K, wTimeOut, wCheckSum,&wT);
   	sio_set_noncan(wPort);
	sio_set_timer(wPort, 0, 1);		/* set timeout for 0.1 sec */
   	printf("String to send: string length: %ld, \nString: %s \n", strlen(szCmd8K), szCmd8K);
	wRetVal = i7k_send_readt_cs(wPort, szCmd8K, szRec8K, RBUF_SIZE, &texp);
	printf("Received string length: %d, \nString: %s \n", wRetVal, szRec8K);

   if(wFlag==1)      strcpy(szReceive,szRec8K);

//   if(wRetVal != NoError) return wRetVal;
	if(wRetVal < 0) return wRetVal;
	else if(wRetVal == 0) return -1;

  if( dwID==0x87016 )
  {
     if(szRec8K[0] != '!')
     {
        return ResultStrCheckError;
     }
     if(wCheckSum==0) wRecStrLen=3; else wRecStrLen=5;
  }
  else    // 7021, 7024
  {
     if(szRec8K[0] != '>')
     {
        return ResultStrCheckError;
     }
     if(wCheckSum==0) wRecStrLen=1; else wRecStrLen=3;
  }

  if(strlen(szRec8K) != (wRecStrLen+1)) return ResultStrCheckError;

  return(NoError);
}

WORD /*CALLBACK*/ DigitalOut_87K(DWORD dwBuf[], float fBuf[],
        char szSend[], char szReceive[])
{
   char  wPort,wFlag,c1,c2,A,B,C,D;
   WORD  wAddr,wRetVal,wCheckSum,wTimeOut,wT;//,wAddr2
	__tod_t texp;
   WORD  wRecStrLen;
   DWORD dwID,dwData;
   int i;
   //char  szCmd2[80];

   //---------------------- input ---------------------------
   wPort=(char)dwBuf[0];   // RS-232 port number: 1/2/3/4/..../255
   wAddr=(WORD)dwBuf[1];         // module address: 0x00 to 0xFF
   dwID=dwBuf[2];           // module ID: 0x87054/55/56/57/60/63/64/65/66/68/41
   wCheckSum=(WORD)dwBuf[3];     // checksum: 0=disable, 1=enable
   wTimeOut=(WORD)dwBuf[4];      // TimeOut constant: normal=100
   dwData=dwBuf[5];         // 16-bit digital data to output
   wFlag=(char)dwBuf[6];   // flag: 0=no save, 1=save send/receive string
   //---------------------- output -----------------------
   // void

   //@AA(Data)[CHK](cr)
   szCmd8K[0]='@';
   c2=(char)(wAddr&0x0f);
   wAddr=wAddr/16;
   c1=(char)(wAddr&0x0f);
   szCmd8K[1] = HexToAscii(c1);
   szCmd8K[2] = HexToAscii(c2);

   switch (dwID)
   {
		case 0x87041: //32 channels
		           dwData&=0xFFFFFFFF;
				   for(i=0;i<8;i++)
				   {
						A=(char)(dwData >> i*4) & 0x0f;
						szCmd8K[10-i]=HexToAscii(A);
				   }
					szCmd8K[11]=0;
/*	               D=dwData&0x0f; dwData=dwData/16;
	               C=dwData&0x0f; dwData=dwData/16;
	               B=dwData&0x0f; dwData=dwData/16;
	               A=dwData&0x0f;
	               szCmd8K[3]=HexToAscii(A);
		           szCmd8K[4]=HexToAscii(B);
	               szCmd8K[5]=HexToAscii(C);
	               szCmd8K[6]=HexToAscii(D);
	               szCmd8K[7]=0;*/
			break;
       case 0x87054:  //return(54);
       case 0x87055:  //return(55);
       case 0x87064:  //return(64);
       case 0x87065:  ///return(65);
       case 0x87066:  //return(66);
       case 0x87069:
       case 0x87068:  //return(68);

				   dwData&=0x00FF;
				   B=(char)dwData&0x0f; dwData=dwData/16;
                   A=(char)dwData&0x0f;
		           szCmd8K[3]=HexToAscii(A);
		           szCmd8K[4]=HexToAscii(B);
                   szCmd8K[5] = 0;
				   break;

       case 0x87056: 	  //16 channels 
	   case 0x87057:	  //16 channels 
		           dwData&=0xFFFF;
	               D=(char)dwData&0x0f; dwData=dwData/16;
	               C=(char)dwData&0x0f; dwData=dwData/16;
	               B=(char)dwData&0x0f; dwData=dwData/16;
	               A=(char)dwData&0x0f;
	               szCmd8K[3]=HexToAscii(A);
		           szCmd8K[4]=HexToAscii(B);
	               szCmd8K[5]=HexToAscii(C);
	               szCmd8K[6]=HexToAscii(D);
	               szCmd8K[7]=0;
		           break;

       case 0x87060:  //6 channels
				   dwData&=0x003F;
				   B=(char)dwData&0x0f; dwData=dwData/16;
                   A=(char)dwData&0x0f;
		           szCmd8K[3]=HexToAscii(A);
		           szCmd8K[4]=HexToAscii(B);
                   szCmd8K[5] = 0;
		           break;
       case 0x87063: //4 channels          // 01/06/2003 by sean              
				   dwData&=0x000F;
				   B=(char)dwData&0x0f; 
//				   dwData=dwData/16;
//                 A=dwData&0x0f;
                   szCmd8K[3]=HexToAscii(B);
                   szCmd8K[4]=0;
/*		           szCmd8K[3]=HexToAscii(A);
		           szCmd8K[4]=HexToAscii(B);
                   szCmd8K[5] = 0;*/
		           break;        

       default: return(ModuleIdError);
   }



   if(wFlag==1)
   {
      strcpy(szSend,szCmd8K);
      szReceive[0]=0;
   }

//   wRetVal=Send_Receive_Cmd(wPort, szCmd8K, szRec8K, wTimeOut, wCheckSum,&wT);
   	sio_set_noncan(wPort);
	sio_set_timer(wPort, 0, 1);		/* set timeout for 0.1 sec */
   	printf("String to send: string length: %ld, \nString: %s \n", strlen(szCmd8K), szCmd8K);
	wRetVal = i7k_send_readt_cs(wPort, szCmd8K, szRec8K, RBUF_SIZE, &texp);
	printf("Received string length: %d, \nString: %s \n", wRetVal, szRec8K);
   if(wFlag==1)      strcpy(szReceive,szRec8K);

//   if(wRetVal != NoError) return wRetVal;
	if(wRetVal < 0) return wRetVal;
	else if(wRetVal == 0) return -1;

   if(szRec8K[0] != '>')   return ResultStrCheckError;

   if(wCheckSum==0) wRecStrLen=1; else wRecStrLen=3;
  
   if(strlen(szRec8K) != (wRecStrLen + 1)) return ResultStrCheckError;

   return(NoError);
}

/************************************************************/
/*  AnalogInAll_87K											*/
/*															*/	
/*  Command:  "#AA" + [CHK(2)] + CR(1) 						*/ 
/*  Response: ">+00.000+01.001+02.002+03.003-04.004			*/
/*				-05.005-06.006-07.007" + [CHK(2)] + CR(1)	*/
/*															*/
/*  Module: I-87013,I8017H,I-87017,I-87018					*/
/*          ADAM-5013/17/18									*/
/*															*/
/*  [Apr,15,2002] by Kevin									*/
/************************************************************/
WORD /*CALLBACK*/ AnalogInAll_87K(DWORD dwBuf[], float fBuf[],
        char szSend[], char szReceive[])
{

	char   wPort,wFlag,cTemp[80],wMode;
	WORD   wRet,wAddr,wRetVal,i,j,wCheckSum,wTimeOut,wT,k;
	__tod_t texp;
//	WORD   wTotalChannel;
//	WORD   wTotalByte;
	int   wTotalByte;
//	int	   iRet;
	DWORD  dwID;
	char *endptr;
	

	//---------------------- input -------------------------------------
	wPort=(char)dwBuf[0];			// RS-232 port number: 1/2/3/4/..../255
	wAddr=(WORD)dwBuf[1];			// module address: 0x00 to 0xFF
	dwID=dwBuf[2];					// module ID: 0x87013/87017/87018
	wCheckSum=(WORD)dwBuf[3];       // checksum: 0=disable, 1=enable
	wTimeOut=(WORD)dwBuf[4];        // TimeOut constant: normal=100
	wFlag=(char)dwBuf[6];			// flag: 0=no save, 1=save send/receive string
	wMode=(char)dwBuf[7];			// 0: Engineer 1:% FSR 2:Hex

	switch (dwID)
	{
		case 0x87013:
/*			wTotalChannel=4;
			if(wCheckSum)
				wTotalByte=31;
			else 
				wTotalByte=29;*/
			break;    
		case 0x87017:
		case 0x87018:
		case 0x87015:
		case 0x87019:
/*			wTotalChannel=8;
			if(wCheckSum)
				wTotalByte=59;
			else 
				wTotalByte=57;*/
			break; 
		default: return(ModuleIdError);
	}

    sprintf(szCmd8K,"#%02X", wAddr);

	sio_set_noncan(wPort);
	sio_set_timer(wPort, 0, 1);		/* set timeout for 0.1 sec */
	memset(szRec8K, 0, RBUF_SIZE);
    printf("wPort= %d, message: %s\n", wPort, szCmd8K);
	wRetVal = i7k_send_readt_cs(wPort, szCmd8K, szRec8K, RBUF_SIZE, &texp);
    printf("Received string length: %d, \nString: \n%s \n", wRetVal, szRec8K);

	if(wFlag)
	{
		strcpy(szSend,szCmd8K);
		strcpy(szReceive,szRec8K);
	}
//	if (wRetVal != NoError) return wRetVal;
	if(wRetVal < 0) return wRetVal;
	else if(wRetVal == 0) return -1;

/*	// Only check the first byte and total bytes.
	if((szRec8K[0]!='>') && (strlen(szRec8K)!=wTotalByte)) 
		return ResultStrCheckError;
	
	for(i=0;i<wTotalChannel;i++)
	{
		//"+03.567" one float value uses 7 bytes.
		for(j=0;j<7;j++)		
			cTemp[j]=szRec8K[1+i*7+j];	
		cTemp[7]=0;
		fBuf[i]=(float)atof(cTemp);
	}
  return(NoError);*/

  switch (dwID)
  {
     
     case 0x87013 :
	 case 0x87017 :
	 case 0x87018 :
	 case 0x87016 :
	 case 0x87015 :
	 case 0x87019 :

		i=1; //szCmd8K[0] is '>'
		k=0;
		j=0;
		if (!wCheckSum) 
	 		wTotalByte=strlen(szRec8K);
		else
			wTotalByte=strlen(szRec8K)-2;
		printf("The length of szRec8K is: %d\n", wTotalByte);
		sleep(1);
		wRet=NoError;
		switch(wMode)
		{
			case 0: //Engineer
			case 1: //Fsr
			case 3:
			while(i<=wTotalByte) //57 (without '\0')
			{
				if(szRec8K[i]=='+' || szRec8K[i]=='-' || i==wTotalByte)
				{
					if(i!=1 || i==wTotalByte)
					{
						cTemp[j]='\0';
						if( !memcmp(cTemp,"-0000",5) && strlen(cTemp)==5)
						{
							strcpy(cTemp,"-9999");
							wRet=UnderInputRange;
						}
						else if( !memcmp(cTemp,"+9999",5) )
							wRet=ExceedInputRange;
						else if( !memcmp(cTemp,"+999.99",6) )
							wRet=ExceedInputRange;
						fBuf[k]=(float)atof(cTemp);
						if(i==wTotalByte)
							break;
						k++;
						j=0;
					}				  
					cTemp[j++]=szRec8K[i];
				}
				else			
					cTemp[j++]=szRec8K[i];			
				i++;
			}
			break;
			case 2: //Hex
			k=8; //Start from wBuf[8]
			while(i<=wTotalByte) // (without '\0')
			{
				if(szRec8K[i]=='+' || szRec8K[i]=='-')
				{				
					for(j=0;j<5;j++)
						cTemp[j]=szRec8K[i++];
					if(!memcmp(cTemp,"-0000",5))
					{
						strcpy(cTemp,"8000"); //UnderRange or the cable broke
						wRet=UnderInputRange;
					}
					else if(!memcmp(cTemp,"+9999",5))
					{
						strcpy(cTemp,"7FFF"); //OverRange or the cable broke
						wRet=ExceedInputRange;
					}

				}
				else			
				{
					for(j=0;j<4;j++)
						cTemp[j]=szRec8K[i++];					
				}				
				cTemp[j]='\0';
				dwBuf[k++]=(DWORD)strtol(cTemp,&endptr,16); //16 means 0~9,A~F
//				fBuf[k]=(float)atof(cTemp);
				if(!memcmp(cTemp,"7FFF",4))										
					wRet=ExceedInputRange;				
				
					
			}
			break;
		}
		break;
  }
	return wRet;
}
}

	switch(cmd)
 	{
		case 1:     // Halt the card     //��ֹ���Ĳ���
//			status= PcdHalt();;			
			RevBuffer[0]=1;
			RevBuffer[1]=status;
			break;			
		case 2:     // Request,Anticoll,Select,return CardType(2 bytes)+CardSerialNo(4 bytes)
//			        // Ѱ��������ͻ��ѡ��    ���ؿ����ͣ�2 bytes��+ ��ϵ�к�(4 bytes)
         
			status= PcdRequest(PICC_REQALL,&RevBuffer[2]);
			if(status!=0)
			{
				status= PcdRequest(PICC_REQALL,&RevBuffer[2]);
				if(status!=0)				
				{
               led=1; 
//					RevBuffer[0]=1;	
					RevBuffer[1]=status;
					break;
				}
			}
             led=0; 
//			RevBuffer[0]=3;	
			RevBuffer[1]=status;
			break;
			
		case 3:                         // ����ͻ ������ϵ�к� MLastSelectedSnr
			status = PcdAnticoll(&RevBuffer[2]);
			if(status!=0)
			{
				RevBuffer[0]=1;	
				RevBuffer[1]=status;
				break;
			}
			memcpy(MLastSelectedSnr,&RevBuffer[2],4);
			RevBuffer[0]=5;
			RevBuffer[1]=status;
			break;	
		case 4:		                    // ѡ�� Select Card
			status=PcdSelect(MLastSelectedSnr);
			if(status!=MI_OK)
			{
				RevBuffer[0]=1;	
				RevBuffer[1]=status;
				break;
			}
			RevBuffer[0]=3;
			RevBuffer[1]=status;			
			break;
		case 5:	    // Key loading into the MF RC500's EEPROM
            status = PcdAuthState(RevBuffer[1], RevBuffer[3], DefaultKey, MLastSelectedSnr);// У�鿨����
			RevBuffer[0]=1;
			RevBuffer[1]=status;			
			break;							
		case 6: 
			RevBuffer[0]=1;
			RevBuffer[1]=status;			
			break;				
		case 7:     
    		RevBuffer[0]=1;
			RevBuffer[1]=status;			
			break;
		case 8:     // Read the mifare card
		            // ����
			status=PcdRead(RevBuffer[1],&RevBuffer[2]);
			if(status==0)
			{RevBuffer[0]=17;}
			else
			{RevBuffer[0]=1;}
			RevBuffer[1]=status;			
			break;
		case 9:     // Write the mifare card
		            // д��  ��������
			status=PcdWrite(RevBuffer[1],&RevBuffer[2]);
			RevBuffer[0]=1;
			RevBuffer[1]=status;			
			break;
		case 10:
            PcdValue(RevBuffer[1],RevBuffer[2],&RevBuffer[3]);
			RevBuffer[0]=1;	
			RevBuffer[1]=status;
			break;
		case 12:    // ��������
		    PcdBakValue(RevBuffer[1], RevBuffer[2]);
			RevBuffer[0]=1;	//contact
			RevBuffer[1]=0;
			break;		
	}

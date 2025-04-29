#include "sht30.h"
#include "iic.h"
#include "delay.h"
#include "stdio.h"

/*********************************************************************************************************
* �� �� �� : Sht30_Init
* ����˵�� : ��ʼ��SHT30�˿�
* ��    �� : ��
* �� �� ֵ : ��
* ��    ע : IIC_SCL��PB6��IIC_SDA��PB7
*********************************************************************************************************/ 
void Sht30_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};    
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;    //ͨ�����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;    //��©
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  //�ٶ�����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL; //���գ�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��

	//����״̬��Ĭ�ϸߵ�ƽ
	SDA_H;
	SCL_H;
}

//1.��ʼ��
//2.����������ַ��ʼͨ��
//3.��������
float te = 0;
float hu = 0;
void Sht30_ReadData(void)
{
	u16 buff[6] = {0};   //���մ洢����
	u16 Temperature, Humidity;  //����
	u8 cnt = 0;    //���ڼ�����������ʱ����
	
	repeat:
	IIC_Stop();    //����ֹͨ�Ź��̣����¿�ʼ
	--cnt;         //cnt���޷��ţ���0�����ݼ�����Ϊ255
	if(!cnt)
	{
		return;    
	}
	
	IIC_Start();    			//������ʼ�ź�
	IIC_WriteByte(0x44 << 1 | 0);	//����������ַ-д������-W

	if(IIC_Wait_ACK() == 0)   //Ӧ��-�ɹ�/ʧ��
	{
		IIC_WriteByte(0x2C);    //���������ʾ��ʼ��ȡ��ʪ������
		if(IIC_Wait_ACK() == 0)  //Ӧ��-�ɹ�/ʧ��
		{
			IIC_WriteByte(0x06);    //���������ʾ�߾���ģʽ��ȡ��ʪ������
			if(IIC_Wait_ACK() == 0)
			{
				IIC_Stop();      //ֹͣͨ��
				delay_ms(15);    //��ʱ�䴦������
				IIC_Start();     //���·�����ʼ�ź�
				IIC_WriteByte(0x44 << 1 | 1);	//����������ַ-��ȡ����-R
				if(IIC_Wait_ACK() == 0)    //����յ�ACK,��ȡ��ʪ������
				{
					buff[0] = IIC_ReadByte(0);
					buff[1] = IIC_ReadByte(0);
					buff[2] = IIC_ReadByte(0);
					buff[3] = IIC_ReadByte(0);
					buff[4] = IIC_ReadByte(0);
					buff[5] = IIC_ReadByte(0);
						
					//�������ֹͣͨ��
					IIC_Stop();
					
					//2/5�ֽ���У��
					Temperature = (buff[0] << 8 | buff[1]);    //�¶�ƴ��  0 + 1�ֽ�
					Humidity = (buff[3] << 8 | buff[4]);       //ʪ��ƴ��  3 + 4
					
					te = (175.0 * Temperature /65535.0-45);        //-45+175*T/2^16-1
					hu = (100 * Humidity /65535);
				}else goto repeat;
			}else goto repeat;
		}else goto repeat;
	}else goto repeat;

	
}








#ifndef __UPS_H
#define __UPS_H	 
#include "sys.h"

/******************************
��Ƭ��ͨ�����ڣ�������Ϊ2400��ʮ�����ƣ���ȡups����
1��UPS������ѯ���Q1<cr>
���Է���: Q1<cr> (ASCIIֵ��ʮ�����ƣ�51 31 0d)
UPS����: (MMM.M NNN.N PPP.P QQQ RR.R S.SS TT.T b7b6b5b4b3b2b1b0<cr>
MMM.M��223.5��	�����ѹ
NNN.N��223.5��	�����ѹ�쳣ת���������ʱ�������ѹֵ
PPP.P��223.0��	�����ѹ
QQQ��000��	    ������ʷֱ�
RR.R��49.9��	  �����ѹ��Ƶ��
SS.S��27.5��	  ��ص�ѹ
TTTT��25.0��	  �¶ȣ��󱸻������㣬Ԥ��������û�����壩

 7  	1: �е��쳣 ��ASCIIֵʮ������λ��31��
      0: �е����� ��ASCIIֵʮ������λ��30��
 6  	1 : ��ص�ѹ   
      0 : �������   
 5  	1 : �е�AVRģʽ���   
      0 : ���������        
 4  	1 : UPS ��������        
      0 : UPSû�й���         
 3  	Ĭ��1  
 2  	Ĭ��0                    
 1  	1 :������ش� 
      0 :������عر� 
 0  	Ĭ��0           

2����ذٷֱȲ�ѯ���Q2<cr>
���Է���: Q2<cr> (ASCIIֵ��ʮ�����ƣ�51 32 0d)
UPS����: (PPP<cr>

����ʮ��������ʾ��28 30 38 39 0d
��ʾ��ذٷֱ�Ϊ89%

******************************/

u8 InquireUPSData(void);
u8 UPSElectricity(void);

		 				    
#endif
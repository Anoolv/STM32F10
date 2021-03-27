#ifndef  __PIN_CFG_MASK__
#define  __PIN_CFG_MASK__

/*** CR�Ĵ���CNFλͨ�����ģʽ���� ***/
#define CNF_PP_G         0X0        
#define CNF_OD_G         0X4
/*** CR�Ĵ���CNFλ�������ģʽ���� ***/
#define CNF_PP_A         0X8
#define CNF_OD_A         0XC
/*** CR�Ĵ���MODEλͨ�ú͸������ģʽ���� ***/
#define MOD_LOW_O        0X2        //����ٶ�Ϊ2MHZ
#define MOD_MID_O        0X1        //����ٶ�Ϊ10MHZ
#define MOD_HIG_O        0X3        //����ٶ�Ϊ50MHZ
/*** CR�Ĵ���MODEλ����ģʽ���� ***/
#define MOD_IN           0X0 
/*** CR�Ĵ���CNFλ����ģʽ���� ***/
#define CNF_ANALOG_IN    0X0
#define CNF_FLOAT_IN     0X4
#define CNF_PDPU_IN      0X8
/*** CR�Ĵ���MODEλ����ģʽ���� ***/

/*** GPIO_CR�Ĵ�������pin���� ***/
#define PIN_MASK        0xF          //����pin�ŵ�����ֵ������ȡ������pin�� CR�Ĵ�����ֵ 

#define GPOP_PP_50MHZ   (CNF_PP_G | MOD_HIG_O)          //����pin��ͨ��-����-���ģʽ��50MHz���ʶ�Ӧ��CR�Ĵ���ֵ  
#define AFOP_PP_50MHZ   (CNF_PP_A | MOD_HIG_O)          //����pin�Ÿ���-����-���ģʽ��50MHz���ʶ�Ӧ��CR�Ĵ���ֵ  
#define IP_FT           (CNF_FLOAT_IN | MOD_IN)          //����pin�Ÿ���-����ģʽ����Ӧ��CR�Ĵ���ֵ  


#endif
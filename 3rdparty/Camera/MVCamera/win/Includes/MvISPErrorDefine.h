
#ifndef _MV_ISP_ERROR_DEFINE_H_
#define _MV_ISP_ERROR_DEFINE_H_
#include <cstdint>
typedef int64_t int64_t;

/************************************************************************
* ����ISP�㷨��Ĵ�����
************************************************************************/
// ͨ������
#define MV_ALG_OK                   0x00000000  //������ȷ
#define MV_ALG_ERR                  0x10000000  //��ȷ�����ʹ���

// �������
#define MV_ALG_E_ABILITY_ARG        0x10000001  //�������д�����Ч����

// �ڴ���
#define MV_ALG_E_MEM_NULL           0x10000002  //�ڴ��ַΪ��
#define MV_ALG_E_MEM_ALIGN          0x10000003  //�ڴ���벻����Ҫ��
#define MV_ALG_E_MEM_LACK           0x10000004  //�ڴ�ռ��С����
#define MV_ALG_E_MEM_SIZE_ALIGN     0x10000005  //�ڴ�ռ��С���������Ҫ��
#define MV_ALG_E_MEM_ADDR_ALIGN     0x10000006  //�ڴ��ַ���������Ҫ��

// ͼ����
#define MV_ALG_E_IMG_FORMAT         0x10000007  //ͼ���ʽ����ȷ���߲�֧��
#define MV_ALG_E_IMG_SIZE           0x10000008  //ͼ����߲���ȷ���߳�����Χ
#define MV_ALG_E_IMG_STEP           0x10000009  //ͼ�������step������ƥ��
#define MV_ALG_E_IMG_DATA_NULL      0x1000000A  //ͼ�����ݴ洢��ַΪ��

// ��������������
#define MV_ALG_E_CFG_TYPE           0x1000000B  //���û��߻�ȡ�������Ͳ���ȷ
#define MV_ALG_E_CFG_SIZE           0x1000000C  //���û��߻�ȡ���������롢����ṹ���С����ȷ
#define MV_ALG_E_PRC_TYPE           0x1000000D  //�������Ͳ���ȷ
#define MV_ALG_E_PRC_SIZE           0x1000000E  //����ʱ���롢���������С����ȷ
#define MV_ALG_E_FUNC_TYPE          0x1000000F  //�Ӵ������Ͳ���ȷ
#define MV_ALG_E_FUNC_SIZE          0x10000010  //�Ӵ���ʱ���롢���������С����ȷ

// ���в������
#define MV_ALG_E_PARAM_INDEX        0x10000011  //index��������ȷ
#define MV_ALG_E_PARAM_VALUE        0x10000012  //value��������ȷ���߳�����Χ
#define MV_ALG_E_PARAM_NUM          0x10000013  //param_num��������ȷ

// �ӿڵ��ü��
#define MV_ALG_E_NULL_PTR           0x10000014  //��������ָ��Ϊ��
#define MV_ALG_E_OVER_MAX_MEM       0x10000015  //�����޶�������ڴ�
#define MV_ALG_E_CALL_BACK          0x10000016  //�ص���������

// �㷨�������ؼ��
#define MV_ALG_E_ENCRYPT            0x10000017  //���ܴ���
#define MV_ALG_E_EXPIRE             0x10000018  //�㷨��ʹ�����޴���

// �ڲ�ģ�鷵�صĻ�����������
#define MV_ALG_E_BAD_ARG            0x10000019  //������Χ����ȷ
#define MV_ALG_E_DATA_SIZE          0x1000001A  //���ݴ�С����ȷ
#define MV_ALG_E_STEP               0x1000001B  //����step����ȷ

// cpuָ�֧�ִ�����
#define MV_ALG_E_CPUID              0x1000001C  //cpu��֧���Ż������е�ָ�

#define MV_ALG_WARNING              0x1000001D  //����

#define MV_ALG_E_TIME_OUT           0x1000001E  //�㷨�ⳬʱ
#define MV_ALG_E_LIB_VERSION        0x1000001F  //�㷨�汾�ų���
#define MV_ALG_E_MODEL_VERSION      0x10000020  //ģ�Ͱ汾�ų���
#define MV_ALG_E_GPU_MEM_ALLOC      0x10000021  //GPU�ڴ�������
#define MV_ALG_E_FILE_NON_EXIST     0x10000022  //�ļ�������
#define MV_ALG_E_NONE_STRING        0x10000023  //�ַ���Ϊ��
#define MV_ALG_E_IMAGE_CODEC        0x10000024  //ͼ�����������
#define MV_ALG_E_FILE_OPEN          0x10000025  //���ļ�����
#define MV_ALG_E_FILE_READ          0x10000026  //�ļ���ȡ����
#define MV_ALG_E_FILE_WRITE         0x10000027  //�ļ�д����
#define MV_ALG_E_FILE_READ_SIZE     0x10000028  //�ļ���ȡ��С����
#define MV_ALG_E_FILE_TYPE          0x10000029  //�ļ����ʹ���
#define MV_ALG_E_MODEL_TYPE         0x1000002A  //ģ�����ʹ���
#define MV_ALG_E_MALLOC_MEM         0x1000002B  //�����ڴ����
#define MV_ALG_E_BIND_CORE_FAILED   0x1000002C  //�̰߳��ʧ��

// �������д�����
#define MV_ALG_E_DENOISE_NE_IMG_FORMAT       0x10402001  //��������ͼ���ʽ����
#define MV_ALG_E_DENOISE_NE_FEATURE_TYPE     0x10402002  //�����������ʹ���
#define MV_ALG_E_DENOISE_NE_PROFILE_NUM      0x10402003  //�������Ը�������
#define MV_ALG_E_DENOISE_NE_GAIN_NUM         0x10402004  //�������������������
#define MV_ALG_E_DENOISE_NE_GAIN_VAL         0x10402005  //������������ֵ�������
#define MV_ALG_E_DENOISE_NE_BIN_NUM          0x10402006  //����������������
#define MV_ALG_E_DENOISE_NE_INIT_GAIN        0x10402007  //�������Ƴ�ʼ���������ô���
#define MV_ALG_E_DENOISE_NE_NOT_INIT         0x10402008  //��������δ��ʼ��
#define MV_ALG_E_DENOISE_COLOR_MODE          0x10402009  //��ɫ�ռ�ģʽ����
#define MV_ALG_E_DENOISE_ROI_NUM             0x1040200a  //ͼ��ROI��������
#define MV_ALG_E_DENOISE_ROI_ORI_PT          0x1040200b  //ͼ��ROIԭ�����
#define MV_ALG_E_DENOISE_ROI_SIZE            0x1040200c  //ͼ��ROI��С����
#define MV_ALG_E_DENOISE_GAIN_NOT_EXIST      0x1040200d  //�����������治����(��������Ѵ�����)
#define MV_ALG_E_DENOISE_GAIN_BEYOND_RANGE   0x1040200e  //�����������治�ڷ�Χ��
#define MV_ALG_E_DENOISE_NP_BUF_SIZE         0x1040200f  //��������������ڴ��С����

#endif //_MV_ISP_ERROR_DEFINE_H_

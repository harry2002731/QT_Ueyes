
#ifndef _MV_OBSOLETE_CAM_PARAMS_H_
#define _MV_OBSOLETE_CAM_PARAMS_H_

#include "PixelType.h"
#include <cstdint>
typedef int64_t int64_t;

/// \~chinese ���֡����Ϣ             \~english Output Frame Information
typedef struct _MV_FRAME_OUT_INFO_
{
    unsigned short      nWidth;             ///< [OUT]  \~chinese ͼ���            \~english Image Width
    unsigned short      nHeight;            ///< [OUT]  \~chinese ͼ���            \~english Image Height
    enum MvGvspPixelType    enPixelType;    ///< [OUT]  \~chinese ���ظ�ʽ          \~english Pixel Type

    unsigned int        nFrameNum;          ///< [OUT]  \~chinese ֡��              \~english Frame Number
    unsigned int        nDevTimeStampHigh;  ///< [OUT]  \~chinese ʱ�����32λ      \~english Timestamp high 32 bits
    unsigned int        nDevTimeStampLow;   ///< [OUT]  \~chinese ʱ�����32λ      \~english Timestamp low 32 bits
    unsigned int        nReserved0;         ///< [OUT]  \~chinese ������8�ֽڶ���   \~english Reserved, 8-byte aligned
    int64_t             nHostTimeStamp;     ///< [OUT]  \~chinese �������ɵ�ʱ���  \~english Host-generated timestamp

    unsigned int        nFrameLen;

    unsigned int        nLostPacket;  // ��֡������
    unsigned int        nReserved[2];
}MV_FRAME_OUT_INFO;

/// \~chinese ����ͼƬ����            \~english Save image type
typedef struct _MV_SAVE_IMAGE_PARAM_T_
{
    unsigned char*      pData;              ///< [IN]   \~chinese �������ݻ���      \~english Input Data Buffer
    unsigned int        nDataLen;           ///< [IN]   \~chinese �������ݴ�С      \~english Input Data Size
    enum MvGvspPixelType    enPixelType;    ///< [IN]   \~chinese �������ظ�ʽ      \~english Input Data Pixel Format
    unsigned short      nWidth;             ///< [IN]   \~chinese ͼ���            \~english Image Width
    unsigned short      nHeight;            ///< [IN]   \~chinese ͼ���            \~english Image Height

    unsigned char*      pImageBuffer;       ///< [OUT]  \~chinese ���ͼƬ����      \~english Output Image Buffer
    unsigned int        nImageLen;          ///< [OUT]  \~chinese ���ͼƬ��С      \~english Output Image Size
    unsigned int        nBufferSize;        ///< [IN]   \~chinese �ṩ�������������С  \~english Output buffer size provided
    enum MV_SAVE_IAMGE_TYPE enImageType;    ///< [IN]   \~chinese ���ͼƬ��ʽ      \~english Output Image Format

}MV_SAVE_IMAGE_PARAM;

typedef struct _MV_IMAGE_BASIC_INFO_
{
    unsigned short      nWidthValue;
    unsigned short      nWidthMin;
    unsigned int        nWidthMax;
    unsigned int        nWidthInc;

    unsigned int        nHeightValue;
    unsigned int        nHeightMin;
    unsigned int        nHeightMax;
    unsigned int        nHeightInc;

    float               fFrameRateValue;
    float               fFrameRateMin;
    float               fFrameRateMax;

    unsigned int        enPixelType;        ///< [OUT]  \~chinese ��ǰ�����ظ�ʽ    \~english Current pixel format
    unsigned int        nSupportedPixelFmtNum;  ///< [OUT]  \~chinese ֧�ֵ����ظ�ʽ����    \~english Support pixel format
    unsigned int        enPixelList[MV_MAX_XML_SYMBOLIC_NUM];
    unsigned int        nReserved[8];

}MV_IMAGE_BASIC_INFO;


/// \~chinese ������������    \~english Noise feature type
typedef enum _MV_CC_BAYER_NOISE_FEATURE_TYPE
{
    MV_CC_BAYER_NOISE_FEATURE_TYPE_INVALID = 0, ///<        \~chinese ��Чֵ                        \~english Invalid
    MV_CC_BAYER_NOISE_FEATURE_TYPE_PROFILE = 1, ///<        \~chinese ��������                      \~english Noise curve
    MV_CC_BAYER_NOISE_FEATURE_TYPE_LEVEL   = 2, ///<        \~chinese ����ˮƽ                      \~english Noise level
    MV_CC_BAYER_NOISE_FEATURE_TYPE_DEFAULT = 1, ///<        \~chinese Ĭ��ֵ                        \~english Default

}MV_CC_BAYER_NOISE_FEATURE_TYPE;

/// \~chinese Bayer��ʽ����������Ϣ    \~english Denoise profile info
typedef struct _MV_CC_BAYER_NOISE_PROFILE_INFO_T_
{
    unsigned int        nVersion;           ///<  \~chinese �汾                           \~english version
    MV_CC_BAYER_NOISE_FEATURE_TYPE enNoiseFeatureType;  ///<  \~chinese ������������       \~english noise feature type
    enum MvGvspPixelType    enPixelType;    ///<  \~chinese ͼ���ʽ                       \~english image format
    int                 nNoiseLevel;        ///<  \~chinese ƽ������ˮƽ                   \~english noise level
    unsigned int        nCurvePointNum;     ///<  \~chinese ���ߵ���                       \~english curve point number
    int*                nNoiseCurve;        ///<  \~chinese ��������                       \~english noise curve
    int*                nLumCurve;          ///<  \~chinese ��������                       \~english luminance curve

    unsigned int        nRes[8];            ///<       \~chinese Ԥ��                           \~english Reserved

}MV_CC_BAYER_NOISE_PROFILE_INFO;

/// \~chinese Bayer��ʽ�������Ʋ���    \~english Bayer noise estimate param
typedef struct _MV_CC_BAYER_NOISE_ESTIMATE_PARAM_T_
{
    unsigned int        nWidth;             ///< [IN]  \~chinese ͼ���(���ڵ���8)              \~english Width
    unsigned int        nHeight;            ///< [IN]  \~chinese ͼ���(���ڵ���8)              \~english Height
    enum MvGvspPixelType    enPixelType;    ///< [IN]  \~chinese ���ظ�ʽ                       \~english Pixel format

    unsigned char*      pSrcData;           ///< [IN]  \~chinese �������ݻ���                   \~english Input data buffer
    unsigned int        nSrcDataLen;        ///< [IN]  \~chinese �������ݴ�С                   \~english Input data size

    unsigned int        nNoiseThreshold;    ///< [IN]  \~chinese ������ֵ(0-4095)               \~english Noise Threshold

    unsigned char*      pCurveBuf;          ///< [IN]  \~chinese ���ڴ洢�������ߺ��������ߣ���Ҫ�ⲿ���䣬�����С��4096 * sizeof(int) * 2��     \~english Buffer used to store noise and brightness curves, size:4096 * sizeof(int) * 2)
    MV_CC_BAYER_NOISE_PROFILE_INFO stNoiseProfile; ///< [OUT]  \~chinese ����������Ϣ               \~english Denoise profile

    unsigned int        nThreadNum;         ///< [IN]  \~chinese �߳�������0��ʾ�㷨�����Ӳ������Ӧ��1��ʾ���̣߳�Ĭ�ϣ�������1��ʾ�߳���Ŀ      \~english Thread number, 0 means that the library is adaptive to the hardware, 1 means single thread(Default value), Greater than 1 indicates the number of threads

    unsigned int        nRes[8];            ///<       \~chinese Ԥ��                           \~english Reserved

}MV_CC_BAYER_NOISE_ESTIMATE_PARAM;

/// \~chinese Bayer��ʽ���������    \~english Bayer spatial Denoise param
typedef struct _MV_CC_BAYER_SPATIAL_DENOISE_PARAM_T_
{
    unsigned int        nWidth;             ///< [IN]  \~chinese ͼ���(���ڵ���8)              \~english Width
    unsigned int        nHeight;            ///< [IN]  \~chinese ͼ���(���ڵ���8)              \~english Height
    enum MvGvspPixelType    enPixelType;        ///< [IN]  \~chinese ���ظ�ʽ                       \~english Pixel format

    unsigned char*      pSrcData;           ///< [IN]  \~chinese �������ݻ���                   \~english Input data buffer
    unsigned int        nSrcDataLen;        ///< [IN]  \~chinese �������ݴ�С                   \~english Input data size

    unsigned char*      pDstBuf;            ///< [OUT] \~chinese �������������               \~english Output data buffer
    unsigned int        nDstBufSize;        ///< [IN]  \~chinese �ṩ�������������С           \~english Provided output buffer size
    unsigned int        nDstBufLen;         ///< [OUT] \~chinese ������������ݳ���           \~english Output data length

    MV_CC_BAYER_NOISE_PROFILE_INFO stNoiseProfile; ///< [IN]  \~chinese ����������Ϣ(��Դ����������)   \~english Denoise profile
    unsigned int        nDenoiseStrength;   ///< [IN]  \~chinese ����ǿ��(0-100)                \~english nDenoise Strength   
    unsigned int        nSharpenStrength;   ///< [IN]  \~chinese ��ǿ��(0-32)                 \~english Sharpen Strength
    unsigned int        nNoiseCorrect;      ///< [IN]  \~chinese ����У��ϵ��(0-1280)           \~english Noise Correct  

    unsigned int        nThreadNum;         ///< [IN]  \~chinese �߳�������0��ʾ�㷨�����Ӳ������Ӧ��1��ʾ���̣߳�Ĭ�ϣ�������1��ʾ�߳���Ŀ         \~english Thread number, 0 means that the library is adaptive to the hardware, 1 means single thread(Default value), Greater than 1 indicates the number of threads

    unsigned int        nRes[8];            ///<       \~chinese Ԥ��                           \~english Reserved

}MV_CC_BAYER_SPATIAL_DENOISE_PARAM;

/// \~chinese CLUT����                  \~english CLUT param
typedef struct _MV_CC_CLUT_PARAM_T_
{
    bool                bCLUTEnable;                                ///< [IN]  \~chinese �Ƿ�����CLUT           \~english CLUT enable
    unsigned int        nCLUTScale;                                 ///< [IN]  \~chinese ����ϵ��(2��������,���65536)  \~english Quantitative scale(Integer power of 2, <= 65536)
    unsigned int        nCLUTSize;                                  ///< [IN]  \~chinese CLUT��С,Ŀǰ��֧��17     \~english CLUT size, currently only supports 17
    unsigned char*      pCLUTBuf;                                   ///< [IN]  \~chinese ����CLUT��             \~english CLUT buffer
    unsigned int        nCLUTBufLen;                                ///< [IN]  \~chinese ����CLUT�����С(nCLUTSize*nCLUTSize*nCLUTSize*sizeof(int)*3)  \~english CLUT buffer length(nCLUTSize*nCLUTSize*nCLUTSize*sizeof(int)*3)

    unsigned int        nRes[8];                                    ///<       \~chinese Ԥ��                   \~english Reserved

}MV_CC_CLUT_PARAM;

/// \~chinese �񻯽ṹ��                \~english Sharpen structure
typedef struct _MV_CC_SHARPEN_PARAM_T_
{
    unsigned int            nWidth;                                 ///< [IN]  \~chinese ͼ�����(��С8)        \~english Image Width
    unsigned int            nHeight;                                ///< [IN]  \~chinese ͼ��߶�(��С8)        \~english Image Height
    unsigned char*          pSrcBuf;                                ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcBufLen;                             ///< [IN]  \~chinese �������ݴ�С           \~english Input data length
    enum MvGvspPixelType    enPixelType;                            ///< [IN]  \~chinese ���ظ�ʽ               \~english Pixel format

    unsigned char*          pDstBuf;                                ///< [OUT] \~chinese ������ݻ���           \~english Output data buffer
    unsigned int            nDstBufSize;                            ///< [IN]  \~chinese �ṩ�������������С   \~english Provided output buffer size
    unsigned int            nDstBufLen;                             ///< [OUT] \~chinese ������ݳ���           \~english Output data length

    unsigned int            nSharpenAmount;                         ///< [IN]  \~chinese ��ȵ���ǿ�ȣ�[0,500]  \~english Sharpen amount,[0,500]  //   [nSharpenAmount ���ϣ� ʹ�� nSharpenPosAmount & nSharpenNegAmount ��� ]
    unsigned int            nSharpenRadius;                         ///< [IN]  \~chinese ��ȵ��ڰ뾶(�뾶Խ�󣬺�ʱԽ��)��[1,21]   \~english Sharpen radius(The larger the radius, the longer it takes),[1,21]
    unsigned int            nSharpenThreshold;                      ///< [IN]  \~chinese ��ȵ�����ֵ��[0,255]  \~english Sharpen threshold,[0,255]


    unsigned int        nSharpenPosAmount;     // [IN]     ��ȵ�������ǿ�ȣ���Χ:[0, 500]  
    unsigned int        nSharpenNegAmount;     // [IN]     ��ȵ��ڸ���ǿ�ȣ���Χ:[0, 500]    

    unsigned int            nRes[6];                                ///<       \~chinese Ԥ��                   \~english Reserved

}MV_CC_SHARPEN_PARAM;

/// \~chinese ɫ��У���ṹ��            \~english Color correct structure
typedef struct _MV_CC_COLOR_CORRECT_PARAM_T_
{
    unsigned int            nWidth;                                 ///< [IN]  \~chinese ͼ�����               \~english Image Width
    unsigned int            nHeight;                                ///< [IN]  \~chinese ͼ��߶�               \~english Image Height
    unsigned char*          pSrcBuf;                                ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcBufLen;                             ///< [IN]  \~chinese �������ݴ�С           \~english Input data length
    enum MvGvspPixelType    enPixelType;                            ///< [IN]  \~chinese ���ظ�ʽ               \~english Pixel format

    unsigned char*          pDstBuf;                                ///< [OUT] \~chinese ������ݻ���           \~english Output data buffer
    unsigned int            nDstBufSize;                            ///< [IN]  \~chinese �ṩ�������������С   \~english Provided output buffer size
    unsigned int            nDstBufLen;                             ///< [OUT] \~chinese ������ݳ���           \~english Output data length

    unsigned int            nImageBit;                              ///< [IN]  \~chinese ��Чͼ��λ��(8,10,12,16)   \~english Image bit(8 or 10 or 12 or 16)
    MV_CC_GAMMA_PARAM       stGammaParam;                           ///< [IN]  \~chinese Gamma��Ϣ              \~english Gamma info
    MV_CC_CCM_PARAM_EX      stCCMParam;                             ///< [IN]  \~chinese CCM��Ϣ                \~english CCM info
    MV_CC_CLUT_PARAM        stCLUTParam;                            ///< [IN]  \~chinese CLUT��Ϣ               \~english CLUT info

    unsigned int            nRes[8];                                ///<       \~chinese Ԥ��                   \~english Reserved

}MV_CC_COLOR_CORRECT_PARAM;

/// \~chinese ����ROI�ṹ��             \~english Rect ROI structure
typedef struct _MV_CC_RECT_I_
{
    unsigned int nX;                                                ///< \~chinese �������Ͻ�X������            \~english X Position
    unsigned int nY;                                                ///< \~chinese �������Ͻ�Y������            \~english Y Position
    unsigned int nWidth;                                            ///< \~chinese ���ο���                     \~english Rect Width
    unsigned int nHeight;                                           ///< \~chinese ���θ߶�                     \~english Rect Height

}MV_CC_RECT_I;

/// \~chinese �������ƽṹ��            \~english Noise estimate structure
typedef struct _MV_CC_NOISE_ESTIMATE_PARAM_T_
{
    unsigned int            nWidth;                                 ///< [IN]  \~chinese ͼ�����(��С8)        \~english Image Width
    unsigned int            nHeight;                                ///< [IN]  \~chinese ͼ��߶�(��С8)        \~english Image Height
    enum MvGvspPixelType    enPixelType;                            ///< [IN]  \~chinese ���ظ�ʽ               \~english Pixel format
    unsigned char*          pSrcBuf;                                ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcBufLen;                             ///< [IN]  \~chinese �������ݴ�С           \~english Input data length

    MV_CC_RECT_I*           pstROIRect;                             ///< [IN]  \~chinese ͼ��ROI                \~english Image ROI
    unsigned int            nROINum;                                ///< [IN]  \~chinese ROI����                \~english ROI number

    ///< \~chinese Bayer���������Ʋ�����Mono8/RGB����Ч     \~english Bayer Noise estimate param,Mono8/RGB formats are invalid
    unsigned int            nNoiseThreshold;                        ///< [IN]  \~chinese ������ֵ[0,4095]       \~english Noise threshold[0,4095]
    ///< \~chinese ����ֵ:8bit,0xE0;10bit,0x380;12bit,0xE00     \~english Suggestive value:8bit,0xE0;10bit,0x380;12bit,0xE00

    unsigned char*          pNoiseProfile;                          ///< [OUT] \~chinese �����������           \~english Output Noise Profile
    unsigned int            nNoiseProfileSize;                      ///< [IN]  \~chinese �ṩ�������������С   \~english Provided output buffer size
    unsigned int            nNoiseProfileLen;                       ///< [OUT] \~chinese ����������Գ���       \~english Output Noise Profile length

    unsigned int            nRes[8];                                ///<       \~chinese Ԥ��                   \~english Reserved

}MV_CC_NOISE_ESTIMATE_PARAM;

/// \~chinese ������ṹ��            \~english Spatial denoise structure
typedef struct _MV_CC_SPATIAL_DENOISE_PARAM_T_
{
    unsigned int            nWidth;                                 ///< [IN]  \~chinese ͼ�����(��С8)        \~english Image Width
    unsigned int            nHeight;                                ///< [IN]  \~chinese ͼ��߶�(��С8)        \~english Image Height
    enum MvGvspPixelType    enPixelType;                            ///< [IN]  \~chinese ���ظ�ʽ               \~english Pixel format
    unsigned char*          pSrcBuf;                                ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcBufLen;                             ///< [IN]  \~chinese �������ݴ�С           \~english Input data length

    unsigned char*          pDstBuf;                                ///< [OUT] \~chinese �������������       \~english Output data buffer
    unsigned int            nDstBufSize;                            ///< [IN]  \~chinese �ṩ�������������С   \~english Provided output buffer size
    unsigned int            nDstBufLen;                             ///< [OUT] \~chinese ������������ݳ���   \~english Output data length

    unsigned char*          pNoiseProfile;                          ///< [IN]  \~chinese ������������           \~english Input Noise Profile
    unsigned int            nNoiseProfileLen;                       ///< [IN]  \~chinese �����������Գ���       \~english Input Noise Profile length

    ///< \~chinese Bayer������������Mono8/RGB����Ч     \~english Bayer Spatial denoise param,Mono8/RGB formats are invalid
    unsigned int            nBayerDenoiseStrength;                  ///< [IN]  \~chinese ����ǿ��[0,100]        \~english Denoise Strength[0,100]
    unsigned int            nBayerSharpenStrength;                  ///< [IN]  \~chinese ��ǿ��[0,32]         \~english Sharpen Strength[0,32]
    unsigned int            nBayerNoiseCorrect;                     ///< [IN]  \~chinese ����У��ϵ��[0,1280]   \~english Noise Correct[0,1280]

    ///< \~chinese Mono8/RGB������������Bayer����Ч     \~english Mono8/RGB Spatial denoise param,Bayer formats are invalid
    unsigned int            nNoiseCorrectLum;                       ///< [IN]  \~chinese ����У��ϵ��[1,2000]   \~english Noise Correct Lum[1,2000]
    unsigned int            nNoiseCorrectChrom;                     ///< [IN]  \~chinese ɫ��У��ϵ��[1,2000]   \~english Noise Correct Chrom[1,2000]
    unsigned int            nStrengthLum;                           ///< [IN]  \~chinese ���Ƚ���ǿ��[0,100]    \~english Strength Lum[0,100]
    unsigned int            nStrengthChrom;                         ///< [IN]  \~chinese ɫ������ǿ��[0,100]    \~english Strength Chrom[0,100]
    unsigned int            nStrengthSharpen;                       ///< [IN]  \~chinese ��ǿ��[1,1000]       \~english Strength Sharpen[1,1000]

    unsigned int            nRes[8];                                ///<       \~chinese Ԥ��                   \~english Reserved

}MV_CC_SPATIAL_DENOISE_PARAM;

/// \~chinese LSC�궨�ṹ��             \~english LSC calib structure
typedef struct _MV_CC_LSC_CALIB_PARAM_T_
{
    unsigned int            nWidth;                                 ///< [IN]  \~chinese ͼ�����[16,65535]     \~english Image Width
    unsigned int            nHeight;                                ///< [IN]  \~chinese ͼ��߶�[16-65535]     \~english Image Height
    enum MvGvspPixelType    enPixelType;                            ///< [IN]  \~chinese ���ظ�ʽ               \~english Pixel format
    unsigned char*          pSrcBuf;                                ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcBufLen;                             ///< [IN]  \~chinese �������ݳ���           \~english Input data length

    unsigned char*          pCalibBuf;                              ///< [OUT] \~chinese ����궨������         \~english Output calib buffer
    unsigned int            nCalibBufSize;                          ///< [IN]  \~chinese �ṩ�ı궨�������С(nWidth*nHeight*sizeof(unsigned short))    \~english Provided output buffer size
    unsigned int            nCalibBufLen;                           ///< [OUT] \~chinese ����궨�����泤��     \~english Output calib buffer length

    unsigned int            nSecNumW;                               ///< [IN]  \~chinese ���ȷֿ���             \~english Width Sec num
    unsigned int            nSecNumH;                               ///< [IN]  \~chinese �߶ȷֿ���             \~english Height Sec num
    unsigned int            nPadCoef;                               ///< [IN]  \~chinese ��Ե���ϵ��[1,5]      \~english Pad Coef[1,5]
    unsigned int            nCalibMethod;                           ///< [IN]  \~chinese �궨��ʽ(0-����Ϊ��׼;1-��������Ϊ��׼;2-Ŀ������Ϊ��׼) \~english Calib method
    unsigned int            nTargetGray;                            ///< [IN]  \~chinese Ŀ������(�궨��ʽΪ2ʱ��Ч)    \~english Target Gray
    ///< \~chinese 8λ,��Χ��[0,255]            \~english 8bit,range:[0,255]
    ///< \~chinese 10λ,��Χ��[0,1023]          \~english 10bit,range:[0,1023]
    ///< \~chinese 12λ,��Χ��[0,4095]          \~english 12bit,range:[0,4095]

    unsigned int            nRes[8];                                ///<       \~chinese Ԥ��                   \~english Reserved

}MV_CC_LSC_CALIB_PARAM;

/// \~chinese LSCУ���ṹ��             \~english LSC correct structure
typedef struct _MV_CC_LSC_CORRECT_PARAM_T_
{
    unsigned int            nWidth;                                 ///< [IN]  \~chinese ͼ�����[16,65535]     \~english Image Width
    unsigned int            nHeight;                                ///< [IN]  \~chinese ͼ��߶�[16,65535]     \~english Image Height
    enum MvGvspPixelType    enPixelType;                            ///< [IN]  \~chinese ���ظ�ʽ               \~english Pixel format
    unsigned char*          pSrcBuf;                                ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcBufLen;                             ///< [IN]  \~chinese �������ݳ���           \~english Input data length

    unsigned char*          pDstBuf;                                ///< [OUT] \~chinese ������ݻ���           \~english Output data buffer
    unsigned int            nDstBufSize;                            ///< [IN]  \~chinese �ṩ�������������С   \~english Provided output buffer size
    unsigned int            nDstBufLen;                             ///< [OUT] \~chinese ������ݳ���           \~english Output data length

    unsigned char*          pCalibBuf;                              ///< [IN]  \~chinese ����궨������         \~english Input calib buffer
    unsigned int            nCalibBufLen;                           ///< [IN]  \~chinese ����궨�����泤��     \~english Input calib buffer length

    unsigned int            nRes[8];                                ///<       \~chinese Ԥ��                   \~english Reserved

}MV_CC_LSC_CORRECT_PARAM;

/// \~chinese ĳ���ڵ��Ӧ���ӽڵ�������ֵ    \~english The maximum number of child nodes corresponding to a node
#define MV_MAX_XML_NODE_NUM_C       128

/// \~chinese �ڵ������ַ�����󳤶�            \~english The maximum length of node name string
#define MV_MAX_XML_NODE_STRLEN_C    64

/// \~chinese �ڵ�Stringֵ��󳤶�              \~english The maximum length of Node String
#define MV_MAX_XML_STRVALUE_STRLEN_C 64

/// \~chinese �ڵ������ֶ���󳤶�              \~english The maximum length of the node description field
#define MV_MAX_XML_DISC_STRLEN_C    512

/// \~chinese ���ĵ�Ԫ��                      \~english The maximum number of units
#define MV_MAX_XML_ENTRY_NUM        10

/// \~chinese ���ڵ��������                    \~english The maximum number of parent nodes
#define MV_MAX_XML_PARENTS_NUM      8

/// \~chinese ÿ���Ѿ�ʵ�ֵ�Ԫ�����Ƴ���        \~english The length of the name of each unit that has been implemented
#define MV_MAX_XML_SYMBOLIC_STRLEN_C 64

enum MV_XML_Visibility
{
    V_Beginner      = 0,    ///< Always visible
    V_Expert        = 1,    ///< Visible for experts or Gurus
    V_Guru          = 2,    ///< Visible for Gurus
    V_Invisible     = 3,    ///< Not Visible
    V_Undefined     = 99    ///< Object is not yet initialized
};

/// \~chinese �����ڵ�������� | en:Single Node Basic Attributes
typedef struct _MV_XML_NODE_FEATURE_
{
    enum MV_XML_InterfaceType   enType;                             ///< \~chinese �ڵ�����         \~english Node Type
    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Is visibility
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ�����,Ŀǰ�ݲ�֧��   \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice

    unsigned int        nReserved[4];
}MV_XML_NODE_FEATURE;

/// \~chinese �ڵ��б� | en:Node List
typedef struct _MV_XML_NODES_LIST_
{
    unsigned int        nNodeNum;       ///< \~chinese �ڵ����             \~english Node Number
    MV_XML_NODE_FEATURE stNodes[MV_MAX_XML_NODE_NUM_C];
}MV_XML_NODES_LIST;

typedef struct _MV_XML_FEATURE_Value_
{
    enum MV_XML_InterfaceType   enType;                             ///< \~chinese �ڵ�����         \~english Node Type
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ�����,Ŀǰ�ݲ�֧��   \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice
    unsigned int        nReserved[4];
}MV_XML_FEATURE_Value;

typedef struct _MV_XML_FEATURE_Base_
{
    enum MV_XML_AccessMode enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
}MV_XML_FEATURE_Base;

typedef struct _MV_XML_FEATURE_Integer_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    int64_t             nValue;                                     ///< \~chinese ��ǰֵ           \~english Current Value
    int64_t             nMinValue;                                  ///< \~chinese ��Сֵ           \~english Min Value
    int64_t             nMaxValue;                                  ///< \~chinese ���ֵ           \~english Max Value
    int64_t             nIncrement;                                 ///< \~chinese ����             \~english Increment

    unsigned int        nReserved[4];

}MV_XML_FEATURE_Integer;

typedef struct _MV_XML_FEATURE_Boolean_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    bool                bValue;                                     ///< \~chinese ��ǰֵ           \~english Current Value

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Boolean;

typedef struct _MV_XML_FEATURE_Command_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Command;

typedef struct _MV_XML_FEATURE_Float_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    double              dfValue;                                    ///< \~chinese ��ǰֵ           \~english Current Value
    double              dfMinValue;                                 ///< \~chinese ��Сֵ           \~english Min Value
    double              dfMaxValue;                                 ///< \~chinese ���ֵ           \~english Max Value
    double              dfIncrement;                                ///< \~chinese ����             \~english Increment

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Float;

typedef struct _MV_XML_FEATURE_String_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    char                strValue[MV_MAX_XML_STRVALUE_STRLEN_C];     ///< \~chinese ��ǰֵ           \~english Current Value

    unsigned int        nReserved[4];
}MV_XML_FEATURE_String;

typedef struct _MV_XML_FEATURE_Register_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    int64_t             nAddrValue;                                 ///< \~chinese ��ǰֵ           \~english Current Value

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Register;

typedef struct _MV_XML_FEATURE_Category_
{
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ����� Ŀǰ�ݲ�֧��    \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Category;

typedef struct _MV_XML_FEATURE_EnumEntry_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];
    int                 bIsImplemented;
    int                 nParentsNum;
    MV_XML_NODE_FEATURE stParentsList[MV_MAX_XML_PARENTS_NUM];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    int64_t             nValue;                                     ///< \~chinese ��ǰֵ           \~english Current Value
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    int                 nReserved[8];

}MV_XML_FEATURE_EnumEntry;

typedef struct _MV_XML_FEATURE_Enumeration_
{
    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ����� Ŀǰ�ݲ�֧��    \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice

    int                 nSymbolicNum;                               ///< \~chinese ymbolic��        \~english Symbolic Number
    char                strCurrentSymbolic[MV_MAX_XML_SYMBOLIC_STRLEN_C];///< \~chinese ��ǰSymbolic����    \~english Current Symbolic Index
    char                strSymbolic[MV_MAX_XML_SYMBOLIC_NUM][MV_MAX_XML_SYMBOLIC_STRLEN_C];
    enum MV_XML_AccessMode   enAccessMode;                          ////< \~chinese ����ģʽ        \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    int64_t             nValue;                                     ///< \~chinese ��ǰֵ           \~english Current Value

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Enumeration;

typedef struct _MV_XML_FEATURE_Port_
{
    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ�����,Ŀǰ�ݲ�֧��    \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice

    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Port;

typedef struct _MV_XML_CAMERA_FEATURE_
{
    enum MV_XML_InterfaceType    enType;
    union
    {
        MV_XML_FEATURE_Integer      stIntegerFeature;
        MV_XML_FEATURE_Float        stFloatFeature;
        MV_XML_FEATURE_Enumeration  stEnumerationFeature;
        MV_XML_FEATURE_String       stStringFeature;
    }SpecialFeature;

}MV_XML_CAMERA_FEATURE;



/// \~chinese ͼƬ�������              \~english Save Image Parameters
typedef struct _MV_SAVE_IMAGE_PARAM_T_EX_
{
    unsigned char*          pData;                                  ///< [IN]  \~chinese �������ݻ���           \~english Input Data Buffer
    unsigned int            nDataLen;                               ///< [IN]  \~chinese �������ݳ���           \~english Input Data length
    enum MvGvspPixelType    enPixelType;                            ///< [IN]  \~chinese �������ݵ����ظ�ʽ     \~english Input Data Pixel Format
    unsigned short          nWidth;                                 ///< [IN]  \~chinese ͼ���                 \~english Image Width
    unsigned short          nHeight;                                ///< [IN]  \~chinese ͼ���                 \~english Image Height

    unsigned char*          pImageBuffer;                           ///< [OUT] \~chinese ���ͼƬ����           \~english Output Image Buffer
    unsigned int            nImageLen;                              ///< [OUT] \~chinese ���ͼƬ����           \~english Output Image length
    unsigned int            nBufferSize;                            ///< [IN]  \~chinese �ṩ�������������С   \~english Output buffer size provided
    enum MV_SAVE_IAMGE_TYPE enImageType;                            ///< [IN]  \~chinese ���ͼƬ��ʽ           \~english Output Image Format
    unsigned int            nJpgQuality;                            ///< [IN]  \~chinese JPG��������(50-99]��������ʽ��Ч   \~english Encoding quality(50-99]��Other formats are invalid

    unsigned int            iMethodValue;                           ///< [IN]  \~chinese ��ֵ���� 0-���� 1-���⣨����ֵĬ��Ϊ���⣩ 2-���� 3-����+  \~english Bayer interpolation method  0-Fast 1-Equilibrium 2-Optimal 3-Optimal+

    unsigned int            nReserved[3];                           ///<       \~chinese Ԥ��                   \~english Reserved

}MV_SAVE_IMAGE_PARAM_EX;



/// \~chinese ͼƬ�������              \~english Save Image Parameters
typedef struct _MV_SAVE_IMG_TO_FILE_PARAM_
{
    enum MvGvspPixelType    enPixelType;                            ///< [IN]  \~chinese�������ݵ����ظ�ʽ      \~english The pixel format of the input data
    unsigned char*          pData;                                  ///< [IN]  \~chinese �������ݻ���           \~english Input Data Buffer
    unsigned int            nDataLen;                               ///< [IN]  \~chinese �������ݳ���           \~english Input Data length
    unsigned short          nWidth;                                 ///< [IN]  \~chinese ͼ���                 \~english Image Width
    unsigned short          nHeight;                                ///< [IN]  \~chinese ͼ���                 \~english Image Height
    enum MV_SAVE_IAMGE_TYPE enImageType;                            ///< [IN]  \~chinese ����ͼƬ��ʽ           \~english Input Image Format
    unsigned int            nQuality;                               ///< [IN]  \~chinese JPG��������(50-99]��������ʽ��Ч \~english JPG Encoding quality(50-99],Other formats are invalid
    char                    pImagePath[256];                        ///< [IN]  \~chinese �����ļ�·��           \~english Input file path

    int                     iMethodValue;                           ///< [IN]  \~chinese ��ֵ���� 0-���� 1-���⣨����ֵĬ��Ϊ���⣩ 2-���� 3-����+ \~english Bayer interpolation method  0-Fast 1-Equilibrium 2-Optimal 3-Optimal+

    unsigned int            nReserved[8];                           ///<       \~chinese Ԥ��                   \~english Reserved

}MV_SAVE_IMG_TO_FILE_PARAM;


// \~chinese ����ת���ṹ��            \~english Pixel convert structure
typedef struct _MV_CC_PIXEL_CONVERT_PARAM_
{
    unsigned short          nWidth;                                 ///< [IN]  \~chinese ͼ���                 \~english Width
    unsigned short          nHeight;                                ///< [IN]  \~chinese ͼ���                 \~english Height

    enum MvGvspPixelType    enSrcPixelType;                         ///< [IN]  \~chinese Դ���ظ�ʽ             \~english Source pixel format
    unsigned char*          pSrcData;                               ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcDataLen;                            ///< [IN]  \~chinese �������ݳ���           \~english Input data length

    enum MvGvspPixelType    enDstPixelType;                         ///< [IN]  \~chinese Ŀ�����ظ�ʽ           \~english Destination pixel format
    unsigned char*          pDstBuffer;                             ///< [OUT] \~chinese ������ݻ���           \~english Output data buffer
    unsigned int            nDstLen;                                ///< [OUT] \~chinese ������ݳ���           \~english Output data length
    unsigned int            nDstBufferSize;                         ///< [IN]  \~chinese �ṩ�������������С   \~english Provided output buffer size

    unsigned int            nRes[4];                                ///<       \~chinese Ԥ��                   \~english Reserved

}MV_CC_PIXEL_CONVERT_PARAM;




#endif /* _MV_OBSOLETE_CAM_PARAMS_H_ */

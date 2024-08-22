
#ifndef _MV_CAMERA_CTRL_H_
#define _MV_CAMERA_CTRL_H_
#include <cstdint>
typedef int64_t int64_t;

#include "MvErrorDefine.h"
#include "CameraParams.h"
#include "MvObsoleteInterfaces.h"



#ifndef MV_CAMCTRL_API

#if (defined (_WIN32) || defined(WIN64))
#if defined(MV_CAMCTRL_EXPORTS)
#define MV_CAMCTRL_API __declspec(dllexport)
#else
#define MV_CAMCTRL_API __declspec(dllimport)
#endif
#else
#ifndef __stdcall
#define __stdcall
#endif

#ifndef MV_CAMCTRL_API
#define  MV_CAMCTRL_API
#endif
#endif

#endif

#ifdef MV_CAMCTRL_API

#if (defined (_WIN32) || defined(WIN64))
	#if defined(MV_CAMCTRL_EXPORTS)
		#define MV_CAMCTRL_API __declspec(dllexport)
	#else
		#define MV_CAMCTRL_API __declspec(dllimport)
	#endif
	#else
		#ifndef __stdcall
			#define __stdcall
		#endif

		#if defined(MV_CAMCTRL_EXPORTS)
			#define  MV_CAMCTRL_API __attribute__((visibility("default")))
		#else
			#define  MV_CAMCTRL_API
		#endif
	#endif

#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifdef __cplusplus
extern "C" {
#endif 


/****************************** ch: ժҪ | en: Instructions**********************************************/

/** 
*   @~chinese
*     ��ͷ�ļ���Ҫ����9���֣�
*     1.����Ŀ��ƺ�ȡ���ӿ�
*     2.���/�ɼ��������������ýӿ�&��д�Ĵ����ӿ�
*     3.�������
*     4.ע���쳣�ص����¼��ӿ�
*     5.��GigE�豸֧�ֵĽӿ�
*     6.��CameraLink �豸֧�ֵĽӿ�
*     7.��U3V�豸֧�ֵĽӿ�
*     8.GenTL��ؽӿ�
*     9.ͼ�񱣴桢��ʽת������ؽӿ�

*   @~english
*     The document mainly consists of nine parts:
*     1.Camera control and streaming��
*     2.Camera/Frame grabber  attribute nodes set and obtained universal interface
*     3.Camera upgrade and read-write register memory interface
*     4.Enrol abnormal callbacks and event interface
*     5.Only support GigE device interface
*     6.Only support camlink device interface
*     7.Only support U3V device interface
*     8.Only support GenTL device interface
*     9.Related image save and format convert interface
**/



/**************************Part1 ch: ����Ŀ��ƺ�ȡ���ӿ� | en: Camera control and streaming******************************************/


/********************************************************************//**
 *  @~chinese
 *  @brief    ��ʼ��SDK
 *  @return   �ɹ�������MV_OK�����󣬷��ش�����

 *  @~english
 *  @brief  Initialize SDK  
 *  @return  Success, return MV_OK. Failure, return error code   
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_Initialize();

/********************************************************************//**
 *  @~chinese
 *  @brief    ����ʼ��SDK���ͷ���Դ
 *  @return   �ɹ�������MV_OK�����󣬷��ش�����

 *  @~english
 *  @brief   Terminate SDK  
 *  @return  Success, return MV_OK. Failure, return error code   
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_Finalize();

/*
 *  @~chinese
 *  @brief  ��ȡSDK�汾��
 *  @return ����4�ֽڰ汾��
            |��    |��    |����  |  ����|
             8bits  8bits  8bits  8bits
 *  @remarks ���緵��ֵΪ0x01000001����SDK�汾��ΪV1.0.0.1��
 
 *  @~english
 *  @brief  Get SDK Version
 *  @return Always return 4 Bytes of version number 
            |Main    |Sub    |Rev  |  Test|
             8bits  8bits  8bits  8bits
 *  @remarks For example, if the return value is 0x01000001, the SDK version is V1.0.0.1.
 ************************************************************************/
MV_CAMCTRL_API unsigned int __stdcall MV_CC_GetSDKVersion();

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ֧�ֵĴ����
 *  @return ֧�ֵĴ������ 
 *  @remarks �������豸�Ĵ���㣬���磨 MV_GIGE_DEVICE | MV_USB_DEVICE |MV_GENTL_XOF_DEVICE �ȣ����������ɼ���������

 *  @~english
 *  @brief  Get supported Transport Layer
 *  @return Supported Transport Layer number
 *  @remarks The return is the transport layer of the device, such as (MV_GIGE-DEVICE | MV_USBDEVICE | MV_GENTL-XOF-DEVICE, etc.), excluding the type of Frame grabber
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumerateTls();

/********************************************************************//**
 *  @~chinese
 *  @brief  ö���豸
 *  @param  nTLayerType                 [IN]            ö�ٴ����, ��������μ�CameraParams.h����, ��: #define MV_GIGE_DEVICE 0x00000001 GigE�豸
 *  @param  pstDevList                  [IN][OUT]       �豸�б�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �豸�б����ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź�����,���龡��������߳�ö�ٲ�����
 *  @remarks ����ö�ٴ���㣬���䴫��MV_GIGE_DEVICE��MV_1394_DEVICE��MV_USB_DEVICE��MV_CAMERALINK_DEVICE��MV_GIGE_DEVICE�ò���
             ��������GiGE��ص��豸��Ϣ����������GiGE��GenTL�µ�GiGE�豸����MV_USB_DEVICE�ò�����������USB�豸����������USB�豸��

 *  @~english
 *  @brief  Enumerate Device
 *  @param  nTLayerType                 [IN]            Enumerate TLs, Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_GIGE_DEVICE 0x00000001
 *  @param  pstDevList                  [IN][OUT]       Device List
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks The memory of the device list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied
             It is recommended to avoid multithreaded enumeration operations as much as possible.
 *  @remarks Transmission layer of enumeration, param only include MV_GIGE_DEVICE��MV_1394_DEVICE��MV_USB_DEVICE��MV_CAMERALINK_DEVICE;
             MV_GIGE_DEVICE can output virtual and GenTL GiGE devices, MV_USB_DEVICE can output all USB devices, include virtual usb devices.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumDevices(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ݳ�������ö���豸
 *  @param  nTLayerType                 [IN]            ö�ٴ����, ��������μ�CameraParams.h����, ��: #define MV_GIGE_DEVICE 0x00000001 GigE�豸
 *  @param  pstDevList                  [IN][OUT]       �豸�б�
 *  @param  strManufacturerName         [IN]            ��������
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����ö�ٴ���㣬���䴫��MV_GIGE_DEVICE��MV_1394_DEVICE��MV_USB_DEVICE��MV_CAMERALINK_DEVICE��MV_GIGE_DEVICE�ò���
            ��������GiGE��ص��豸��Ϣ����������GiGE��GenTL�µ�GiGE�豸����MV_USB_DEVICE�ò�����������USB�豸����������USB�豸��
 *  @remarks �豸�б����ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź�����,���龡��������߳�ö�ٲ�����

 *  @~english
 *  @brief  Enumerate device according to manufacture name
 *  @param  nTLayerType                 [IN]            Transmission layer of enumeration, , Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_GIGE_DEVICE 0x00000001
 *  @param  pstDevList                  [IN][OUT]       Device list
 *  @param  strManufacturerName         [IN]            Manufacture Name
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Transmission layer of enumeration, param only include MV_GIGE_DEVICE��MV_1394_DEVICE��MV_USB_DEVICE��MV_CAMERALINK_DEVICE;
             MV_GIGE_DEVICE can output virtual and GenTL GiGE devices, MV_USB_DEVICE can output all USB devices, include virtual usb devices.
 *  @remarks The memory of the device list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied.
             It is recommended to avoid multithreaded enumeration operations as much as possible.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumDevicesEx(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList, IN const char* strManufacturerName);


/********************************************************************//**
 *  @~chinese
 *  @brief  ö���豸��չ����ָ������ʽö�١����ݳ������ֹ��ˣ�
 *  @param  nTLayerType                 [IN]            ö�ٴ���㣨����ÿһ�ִ�������ͣ�����ϣ�, ��������μ�CameraParams.h����, ��: #define MV_GIGE_DEVICE 0x00000001 GigE�豸
 *  @param  pstDevList                  [IN][OUT]       �豸�б�
 *  @param  strManufacturerName         [IN]            �������֣��ɴ�NULL���������ˣ�
 *  @param  enSortMethod                [IN]            ����ʽ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �豸�б����ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź�����,���龡��������߳�ö�ٲ���
             strManufacturerName�ɴ���NULL��������NULL�򷵻��ź���������豸�б�,����ΪNULL��ֻ�����ź����ָ�������豸�б���

 *  @~english
 *  @brief  Enumerate device according to the specified ordering
 *  @param  nTLayerType                 [IN]            Transmission layer of enumeration(All layer protocol type can input), Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_GIGE_DEVICE 0x00000001
 *  @param  pstDevList                  [IN][OUT]       Device list
 *  @param  strManufacturerName         [IN]            Manufacture Name
 *  @param  enSortMethod                [IN]            Sorting Method
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks The memory of the device list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied.
             It is recommended to avoid multithreaded enumeration operations as much as possible.
             strManufacturerName can be passed in NULL,if NULL is passed in, it will return the sorted list of all devices.
             If it is not NULL,it will only return the sorted list of the specified manufacturer's devices.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumDevicesEx2(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList, IN const char* strManufacturerName, IN MV_SORT_METHOD enSortMethod);

/********************************************************************//**
 *  @~chinese
 *  @brief  �豸�Ƿ������
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��
 *  @param  nAccessMode                 [IN]            ����Ȩ��,��������μ�CameraParams.h����, ��:#define MV_ACCESS_Exclusive 1   ���ò���:���� MV_GIGE_DEVICE/MV_GENTL_GIGE_DEVICE ���͵��豸��Ч��
 *  @remarks GIGE���: ��ȡ�豸CCP�Ĵ�����ֵ���жϵ�ǰ״̬�Ƿ����ĳ�ַ���Ȩ��
             ����豸(MV_GENTL_GIGE_DEVICE/MV_GENTL_GIGE_DEVICE)��֧��MV_ACCESS_ExclusiveWithSwitch��MV_ACCESS_ControlWithSwitch��MV_ACCESS_ControlSwitchEnable������ģʽ���ӿڷ���false����Ŀǰ�豸��֧����3����ռģʽ�������������ĳ��̵��豸Ҳ���ݲ�֧����3��ģʽ����
             MV_GIGE_DEVICE/MV_GENTL_GIGE_DEVICE �����豸������nAccessMode�����ص�ǰ�Ƿ���Ա�����;
             �ýӿ�֧�� ���������U3V�����cxp, xof, cameralink�ɼ������, nAccessMode��Ч��������û�б����ӷ���true�� ����豸�����������ӣ��򷵻�false
             �ýӿڲ�֧��CameraLink�豸(����false)
 *  @~english
 *  @brief  Is the device accessible
 *  @param  pstDevInfo                  [IN]            Device Information Structure
 *  @param  nAccessMode                 [IN]            Access Right, Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_ACCESS_Exclusive 1  (This parameter is only valid for devices of type MV_GIGE-DEVICE/MV_GENTL_GIGE-DEVICE)
 *  @return Access, return true. Not access, return false
 *  @remarks Read device CCP register value and determine current access permission.
            If the device (MV_GENTL_GIGE_DEVICE/MV_GENTL_GIGE_DEVICE) does not support the MV_ACCESS_ExclusiveWithSwitch, MV_ACCESS_ControlWithSwitch, and MV_ACCESS_ControlSwitchEnableWithKey modes, the interface returns false. (At present, the device does not support these three preemptive modes, and the devices of mainstream international manufacturers do not currently support these three modes.)
            MV_GIGE_DEVICE/MV_GENTL_GIGE_DEVICE type device: returns whether it can be connected according to nAccessMode;
            This interface supports virtual cameras, U3V cameras, cxp, xof, cameralink capture card cameras, nAccessMode is invalid. If the camera is not connected, it returns true. If the device is connected by a third party, it returns false
            This interface does not support CameraLink devices (returns false)
 **************************************************************************/
MV_CAMCTRL_API bool __stdcall MV_CC_IsDeviceAccessible(IN MV_CC_DEVICE_INFO* pstDevInfo, IN unsigned int nAccessMode);

/********************************************************************//**
 *  @~chinese
 *  @brief   ö�ٲɼ���
 *  @param   nTLayerType        [IN]             �ɼ����ӿ����� eg: (MV_GIGE_INTERFACE | MV_CAMERALINK_INTERFACE | MV_CXP_INTERFACE| MV_XOF_INTERFACE��
 *  @param   pInterfaceInfoList [IN][OUT]       �ɼ����б�
 *  @return  �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief   enum Frame grabber
 *  @param   nTLayerType         [IN]             Frame grabber Type eg: (MV_GIGE_INTERFACE | MV_CAMERALINK_INTERFACE | MV_CXP_INTERFACE| MV_XOF_INTERFACE��
 *  @param   pInterfaceInfoList   [IN][OUT]       Frame grabbe List
 *  @return  Success, return MV_OK. Failure, return error code 
 *  @remarks This API do not support arm and Linux32 platform.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumInterfaces(IN unsigned int nTLayerType, IN OUT MV_INTERFACE_INFO_LIST* pInterfaceInfoList);

/********************************************************************//**
 *  @~chinese
 *  @brief   �����ɼ������
 *  @param   handle  [OUT] �ɼ������
 *  @param   pInterfaceInfo [IN] �ɼ�����Ϣ
 *  @return  �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief   create Frame grabber handle
 *  @param   handle              [OUT]      Frame grabber handle
 *  @param   pInterfaceInfo      [IN]       Frame grabber Info
 *  @return  Success, return MV_OK. Failure, return error code 
 *  @remarks This API do not support arm and Linux32 platform.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CreateInterface(IN OUT void ** handle, IN MV_INTERFACE_INFO* pInterfaceInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief   ͨ���ɼ���ID�����ɼ������
 *  @param   handle         [IN][OUT]       �ɼ������
 *  @param   pInterfaceID   [IN]            �ɼ���ID
 *  @return  �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief   create Frame grabber handle by ID 
 *  @param   handle             [IN][OUT]         Frame grabber handle
 *  @param   pInterfaceID       [IN]              Frame grabber ID
 *  @return  Success, return MV_OK. Failure, return error code 
 *  @remarks This API do not support arm and Linux32 platform.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CreateInterfaceByID(IN OUT void ** handle, IN const char* pInterfaceID);

/********************************************************************//**
 *  @~chinese
 *  @brief   �򿪲ɼ���
 *  @param   handle         [IN]        �ɼ������
 *  @param   pReserved      [IN]        Ԥ����ֱ����NULL
 *  @return  �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief   open Frame grabber
 *  @param   handle         [IN]       Frame grabber handle
 *  @param   pReserved      [IN]       Reserved��default NULL
 *  @return   Success, return MV_OK. Failure, return error code 
 *  @remarks This API do not support arm and Linux32 platform.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_OpenInterface(IN void* handle, IN char* pReserved);

/********************************************************************//**
 *  @~chinese
 *  @brief   �رղɼ���
 *  @param   handle  [IN]       �ɼ������
 *  @return  �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief   close Frame grabber
 *  @param   handle  [IN]          Frame grabber handle 
 *  @return   Success, return MV_OK. Failure, return error code 
 *  @remarks This API do not support arm and Linux32 platform.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CloseInterface(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief   ���ٲɼ������
 *  @param   handle  [IN]�ɼ������
 *  @return  �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks MV_CC_DestroyInterface �����������������Ч���� MV_CC_DestroyHandle ��ͬ; �ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief   Destroy Frame grabber handle
 *  @param   handle  [IN] Frame grabber handle 
 *  @return  Success, return MV_OK. Failure, return error code 
 *  @remarks If MV_CC_DestroyInterface passes in "Device handle", the effect is the same as the MV_CC_DestroyHandle. This API do not support arm and Linux32 platform.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DestroyInterface(IN void* handle);


/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸���
 *  @param  handle                      [IN][OUT]       �豸���
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����������豸��Ϣ���������ڲ��������Դ�ͳ�ʼ���ڲ�ģ��
             ͨ���ýӿڴ������������SDK�ӿڣ���Ĭ������SDK��־�ļ����������Ҫ������־�ļ������Խ���־�����ļ��е���־�ȼ��ĳ�off
 
 *  @~english
 *  @brief  Create Device Handle
 *  @param  handle                      [IN][OUT]       Device handle
 *  @param  pstDevInfo                  [IN]            Device Information Structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Create required resources within library and initialize internal module according to input device information. 
             By creating a handle through this interface and calling the SDK interface, SDK log files will be generated by default. If no log file needs to be generated, the log level in the log configuration file can be changed to off
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CreateHandle(IN OUT void ** handle, IN const MV_CC_DEVICE_INFO* pstDevInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸�������������־
 *  @param  handle                      [IN][OUT]       �豸���
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����������豸��Ϣ���������ڲ��������Դ�ͳ�ʼ���ڲ�ģ��
             ͨ���ýӿڴ������������SDK�ӿڣ�����Ĭ������SDK��־�ļ��������Ҫ������־�ļ�����ͨ��MV_CC_CreateHandle�����������־�ļ��Զ�����
 
 *  @~english
 *  @brief  Create Device Handle without log
 *  @param  handle                      [IN][OUT]       Device handle
 *  @param  pstDevInfo                  [IN]            Device Information Structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Create required resources within library and initialize internal module according to input device information.
             Create handle and call SDK interface through this interface, and SDK log file will not be created. To create logs,
             create handle through MV_CC_CreateHandle, and log files will be automatically generated.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CreateHandleWithoutLog(IN OUT void ** handle, IN const MV_CC_DEVICE_INFO* pstDevInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸���
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks MV_CC_DestroyHandle �������ɼ����������Ч���� MV_CC_DestroyInterface ��ͬ;
 
 *  @~english
 *  @brief  Destroy Device Handle
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks If MV_CC_DestroyHandle passes in "Frame grabber handle", the effect is the same as the MV_CC_DestroyInterface
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DestroyHandle(IN void * handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���豸
 *  @param  handle                      [IN]            �豸���
 *  @param  nAccessMode                 [IN]            ����Ȩ��, ��������μ�CameraParams.h����, ��:#define MV_ACCESS_Exclusive 1  ������ MV_GIGE_DEVICE/MV_GENTL_GIGE_DEVICE ���͵��豸��Ч��
 *  @param  nSwitchoverKey              [IN]            �л�����Ȩ��ʱ����Կ                                                        ������ MV_GIGE_DEVICE ���͵��豸��Ч��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �������õ��豸�������ҵ���Ӧ���豸�������豸, ���ýӿ�ʱ�ɲ�����nAccessMode��nSwitchoverKey����ʱĬ���豸����ģʽΪ��ռȨ�ޡ�
            MV_GIGE_DEVICE �����豸��Ŀǰ����̼��ݲ�֧��MV_ACCESS_ExclusiveWithSwitch��MV_ACCESS_ControlWithSwitch��MV_ACCESS_ControlSwitchEnable��MV_ACCESS_ControlSwitchEnableWithKey��������ռģʽ, SDK�ӿ�֧������
            MV_GENTL_GIGE_DEVICE �豸ֻ֧�� nAccessMode �� MV_ACCESS_Exclusive ��MV_ACCESS_Control ��MV_ACCESS_MonitorȨ��
            ����U3V�豸��CXP,Cameralink(MV_CAMERALINK_DEVICE��MV_GENTL_CAMERALINK_DEVICE), Xof�豸, ����GEV, ����U3V�豸��nAccessMode��nSwitchoverKey������������Ч�� Ĭ���Կ���Ȩ�޴��豸;
            �ýӿ�֧�������豸��ö��ֱ�Ӵ򿪣���֧��U�ں�GenTL�豸��ö�ٴ��豸

  *  @~english
  *  @brief  Open Device
  *  @param  handle                      [IN]            Device handle
  *  @param  nAccessMode                 [IN]            Access Right, Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_ACCESS_Exclusive 1 (Effective only for the device type of MV_GIGE_DEVICE/MV_GENTL_GIGE_DEVICE)
  *  @param  nSwitchoverKey              [IN]            Switch key of access right                                                                                        (Effective only for the device type of MV_GIGE_DEVICE)
  *  @return Success, return MV_OK. Failure, return error code
  *  @remarks Find specific device and connect according to set device parameters.When calling the interface, the input of nAccessMode and nSwitchoverKey is optional, 
             and the device access mode is exclusive. The device type of MV_GIGE_DEVICE, Currently the device firmware does not support the following preemption modes:
             MV_ACCESS_ExclusiveWithSwitch, MV_ACCESS_ControlWithSwitch, MV_ACCESS_ControlSwitchEnable, MV_ACCESS_ControlSwitchEnableWithKey; SDK Interface will return MV_OK.
             The device type of MV_GENTL_GIGE_DEVICE, only support nAccessMode as MV_ACCESS_Exclusive, MV_ACCESS_Control, MV_ACCESS_Monitor;
             For USB3Vision device, CXP device, Cameralink device(MV_CAMERALINK_DEVICE��MV_GENTL_CAMERALINK_DEVICE), Xof device, virtual GEV devoce, virtual U3V device, 
             nAccessMode, nSwitchoverKey are invalid. Open device with MV_ACCESS_Control in default.
             This Interface support open without enumeration by GEV device��USB device and GenTL device don't support .
 ************************************************************************/
#ifndef __cplusplus
MV_CAMCTRL_API int __stdcall MV_CC_OpenDevice(IN void* handle, IN unsigned int nAccessMode, IN unsigned short nSwitchoverKey);
#else
MV_CAMCTRL_API int __stdcall MV_CC_OpenDevice(IN void* handle, IN unsigned int nAccessMode = MV_ACCESS_Exclusive, IN unsigned short nSwitchoverKey = 0);
#endif

/********************************************************************//**
 *  @~chinese
 *  @brief  �ر��豸
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ͨ��MV_CC_OpenDevice�����豸�󣬿���ͨ���ýӿڶϿ��豸���ӣ��ͷ���Դ
 
 *  @~english
 *  @brief  Close Device
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After connecting to device through MV_CC_OpenDevice, use this interface to disconnect and release resources.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CloseDevice(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ж��豸�Ƿ�������״̬
 *  @param  handle                      [IN]            �豸���
 *  @return �豸��������״̬������true��û���ӻ�ʧȥ���ӣ�����false
 
 *  @~english
 *  @brief  Is The Device Connected
 *  @param  handle                      [IN]            Device handle
 *  @return Connected, return true. Not Connected or DIsconnected, return false
 ***********************************************************************/
MV_CAMCTRL_API bool __stdcall MV_CC_IsDeviceConnected(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��ͼ�����ݻص�
 *  @param  handle                      [IN]            �豸���
 *  @param  cbOutput                    [IN]            �ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ͨ���ýӿڿ�������ͼ�����ݻص���������MV_CC_CreateHandle֮�󼴿ɵ���, ͼ�����ݲɼ������ַ�ʽ�����ַ�ʽ���ܸ��ã�
             ��ʽһ������MV_CC_RegisterImageCallBackEx����ͼ�����ݻص�������Ȼ�����MV_CC_StartGrabbing��ʼ�ɼ����ɼ���ͼ�����������õĻص������з���
             ��ʽ��������MV_CC_StartGrabbing��ʼ�ɼ���Ȼ����Ӧ�ò�ѭ������MV_CC_GetOneFrameTimeout��ȡָ�����ظ�ʽ��֡���ݣ�
             ��ȡ֡����ʱ�ϲ�Ӧ�ó�����Ҫ����֡�ʿ��ƺõ��øýӿڵ�Ƶ�ʡ�
             �ýӿڲ�֧��MV_CAMERALINK_DEVICE ���͵��豸��
 
 *  @~english
 *  @brief  Register the image callback function
 *  @param  handle                      [IN]            Device handle
 *  @param  cbOutput                    [IN]            Callback function pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After MV_CC_CreateHandle, call this interface to set image data callback function.There are two available image data acquisition modes, and cannot be used together:
             Mode 1: Call MV_CC_RegisterImageCallBack to set image data callback function, and then callMV_CC_StartGrabbing to start acquiring. The acquired image data will return in the set callback function.
             Mode 2: Call MV_CC_StartGrabbing to start acquiring, and then call MV_CC_GetOneFrameTimeout repeatedly in application layer to get frame data of specified pixel format. When getting frame data,
             the frequency of calling this interface should be controlled by upper layer application according to frame rate.
             This interface does not support devices of type MV_CAMERALINK_DEVICE
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterImageCallBackEx(IN void* handle, 
                                                         IN void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser), IN void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��ͼ�����ݻص���RGB
 *  @param  handle                      [IN]            �豸���
 *  @param  cbOutput                    [IN]            �ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ͨ���ýӿڿ�������ͼ�����ݻص���������MV_CC_CreateHandle֮�󼴿ɵ��á�ͼ�����ݲɼ������ַ�ʽ�����ַ�ʽ���ܸ��ã�
             ��ʽһ������MV_CC_RegisterImageCallBackForRGB����RGB24��ʽͼ�����ݻص�������Ȼ�����MV_CC_StartGrabbing��ʼ�ɼ����ɼ���ͼ�����������õĻص������з��ء�
             ��ʽ��������MV_CC_StartGrabbing��ʼ�ɼ���Ȼ����Ӧ�ò�ѭ������MV_CC_GetImageForRGB��ȡRGB24��ʽ��֡����,
                      ��ȡ֡����ʱ�ϲ�Ӧ�ó�����Ҫ����֡�ʿ��ƺõ��øýӿڵ�Ƶ�ʡ�
             �ýӿڲ�֧��MV_CAMERALINK_DEVICE ���͵��豸��  
 
 *  @~english
 *  @brief  register image data callback, RGB
 *  @param  handle                      [IN]            Device handle
 *  @param  cbOutput                    [IN]            Callback function pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to set image data callback function, you should call this API MV_CC_CreateHandle.There are two image acquisition modes, the two modes cannot be reused:
             Mode 1: Call MV_CC_RegisterImageCallBackForRGB to set RGB24 format image data callback function, and then call MV_CC_StartGrabbing to start acquisition, the collected image data will be returned in the configured callback function.
             Mode 2: Call MV_CC_StartGrabbing to start acquisition, and the call MV_CC_GetImageForRGB repeatedly in application layer to get frame data with RGB24 format.
                     When getting frame data, the upper application program should control the frequency of calling this API according to frame rate.
             This interface does not support devices of type MV_CAMERALINK_DEVICE
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterImageCallBackForRGB(IN void* handle, 
                                                         IN void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser), IN void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��ͼ�����ݻص���BGR
 *  @param  handle                      [IN]            �豸���
 *  @param  cbOutput                    [IN]            �ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ͨ���ýӿڿ�������ͼ�����ݻص���������MV_CC_CreateHandle֮�󼴿ɵ��á�ͼ�����ݲɼ������ַ�ʽ�����ַ�ʽ���ܸ���:
             ��ʽһ������MV_CC_RegisterImageCallBackForBGR����BGR24ͼ�����ݻص�������Ȼ�����MV_CC_StartGrabbing��ʼ�ɼ����ɼ���ͼ�����������õĻص������з��ء�
             ��ʽ��������MV_CC_StartGrabbing��ʼ�ɼ���Ȼ����Ӧ�ò�ѭ������MV_CC_GetImageForBGR��ȡBGR24��ʽ��֡����,
                      ��ȡ֡����ʱ�ϲ�Ӧ�ó�����Ҫ����֡�ʿ��ƺõ��øýӿڵ�Ƶ�ʡ�
             �ýӿڲ�֧��MV_CAMERALINK_DEVICE ���͵��豸�� 
 
 *  @~english
 *  @brief  register image data callback, BGR
 *  @param  handle                      [IN]            Device handle
 *  @param  cbOutput                    [IN]            Callback function pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to set image data callback function, you should call this API MV_CC_CreateHandle.There are two image acquisition modes, the two modes cannot be reused:
             Mode 1: Call MV_CC_RegisterImageCallBackForBGR to set RGB24 format image data callback function, and then call MV_CC_StartGrabbing to start acquisition, the collected image data will be returned in the configured callback function.
             Mode 2: Call MV_CC_StartGrabbing to start acquisition, and the call MV_CC_GetImageForBGR repeatedly in application layer to get frame data with BGR24 format.
                     When getting frame data,the upper application program should control the frequency of calling this API according to frame rate.
            This interface does not support devices of type MV_CAMERALINK_DEVICE
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterImageCallBackForBGR(IN void* handle, 
                                                         IN void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser), IN void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʼȡ��
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڲ�֧��MV_CAMERALINK_DEVICE ���͵��豸��
 
 *  @~english
 *  @brief  Start Grabbing
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface does not support devices of type MV_CAMERALINK_DEVICE
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_StartGrabbing(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ֹͣȡ��
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڲ�֧��MV_CAMERALINK_DEVICE ���͵��豸��
 
 *  @~english
 *  @brief  Stop Grabbing
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface does not support devices of type MV_CAMERALINK_DEVICE
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_StopGrabbing(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡһ֡RGB���ݣ��˺���Ϊ��ѯʽ��ȡ��ÿ�ε��ò�ѯ�ڲ�
            �����������ݣ����������ȡ���ݣ������ݷ��ش�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pData                       [IN][OUT]       ͼ�����ݽ���ָ��
 *  @param  nDataSize                   [IN]            ���ջ����С
 *  @param  pstFrameInfo                [IN][OUT]       ͼ����Ϣ�ṹ��
 *  @param  nMsec                       [IN]            �ȴ���ʱʱ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ÿ�ε��øýӿڣ�����ѯ�ڲ������Ƿ������ݣ������������ת����RGB24��ʽ���أ����û�������򷵻ش����롣
             ��Ϊͼ��ת����RGB24��ʽ�к�ʱ�����Ե�����֡�ʹ���ʱ�ýӿڿ��ܻᵼ�¶�֡�����øýӿڻ�ȡͼ������֮֡ǰ��Ҫ�ȵ���MV_CC_StartGrabbing����ͼ��ɼ���
             �ýӿ�Ϊ����ʽ��ȡ֡���ݣ��ϲ�Ӧ�ó�����Ҫ����֡�ʣ����ƺõ��øýӿڵ�Ƶ�ʡ�
             �ýӿڲ�֧��MV_CAMERALINK_DEVICE�豸��
 
 *  @~english
 *  @brief  Get one frame of RGB data, this function is using query to get data
            query whether the internal cache has data, get data if there has, return error code if no data
 *  @param  handle                      [IN]            Device handle
 *  @param  pData                       [IN][OUT]       Image data receiving buffer
 *  @param  nDataSize                   [IN]            Buffer size
 *  @param  pstFrameInfo                [IN][OUT]       Image information structure
 *  @param  nMsec                       [IN]            Waiting timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Each time the API is called, the internal cache is checked for data. If there is data, it will be transformed as RGB24 format for return, if there is no data, return error code. 
             As time-consuming exists when transform the image to RGB24 format,this API may cause frame loss when the data frame rate is too high.
             Before calling this API to get image data frame, call MV_CC_StartGrabbing to start image acquisition.
             This API can get frame data actively, the upper layer program should control the frequency of calling this API according to the frame rate.
             This API is not supported by MV_CAMERALINK_DEVICE device.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetImageForRGB(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pstFrameInfo, IN int nMsec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡһ֡BGR���ݣ��˺���Ϊ��ѯʽ��ȡ��ÿ�ε��ò�ѯ�ڲ�
            �����������ݣ����������ȡ���ݣ������ݷ��ش�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pData                       [IN][OUT]       ͼ�����ݽ���ָ��
 *  @param  nDataSize                   [IN]            ���ջ����С
 *  @param  pstFrameInfo                [IN][OUT]       ͼ����Ϣ�ṹ��
 *  @param  nMsec                       [IN]            �ȴ���ʱʱ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ÿ�ε��øýӿڣ�����ѯ�ڲ������Ƿ������ݣ������������ת����BGR24��ʽ���أ����û�������򷵻ش����롣
             ��Ϊͼ��ת����BGR24��ʽ�к�ʱ�����Ե�����֡�ʹ���ʱ�ýӿڿ��ܻᵼ�¶�֡.���øýӿڻ�ȡͼ������֮֡ǰ��Ҫ�ȵ���MV_CC_StartGrabbing����ͼ��ɼ���
             �ýӿ�Ϊ����ʽ��ȡ֡���ݣ��ϲ�Ӧ�ó�����Ҫ����֡�ʣ����ƺõ��øýӿڵ�Ƶ�ʡ�
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Get one frame of BGR data, this function is using query to get data
            query whether the internal cache has data, get data if there has, return error code if no data
 *  @param  handle                      [IN]            Device handle
 *  @param  pData                       [IN][OUT]       Image data receiving buffer
 *  @param  nDataSize                   [IN]            Buffer size
 *  @param  pstFrameInfo                [IN][OUT]       Image information structure
 *  @param  nMsec                       [IN]            Waiting timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to set image data callback function, you should call this API MV_CC_CreateHandle.
             There are two image acquisition modes, the two modes cannot be reused: 
             Mode 1: Call MV_CC_RegisterImageCallBackForBGR to set RGB24 format image data callback function, and then call MV_CC_StartGrabbing to start acquisition, the collected image data will be returned in the configured callback function.
             Mode 2: Call MV_CC_StartGrabbing to start acquisition, and the call MV_CC_GetImageForBGR repeatedly in application layer to get frame data with BGR24 format.
             When getting frame data, the upper application program should control the frequency of calling this API according to frame rate.
             This API is not supported by CameraLink device.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetImageForBGR(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pstFrameInfo, IN int nMsec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ʹ���ڲ������ȡһ֡ͼƬ����MV_CC_Display����ͬʱʹ�ã�
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFrame                    [IN][OUT]       ͼ�����ݺ�ͼ����Ϣ
 *  @param  nMsec                       [IN]            �ȴ���ʱʱ�䣬����INFINITEʱ��ʾ���޵ȴ���ֱ���յ�һ֡���ݻ���ֹͣȡ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ���øýӿڻ�ȡͼ������֮֡ǰ��Ҫ�ȵ���MV_CC_StartGrabbing����ͼ��ɼ����ýӿ�Ϊ����ʽ��ȡ֡���ݣ��ϲ�Ӧ�ó�����Ҫ����֡�ʣ����ƺõ��øýӿڵ�Ƶ��,
             �ýӿ�֧�����ó�ʱʱ�䣬SDK�ڲ��ȴ�ֱ��������ʱ���أ���������ȡ��ƽ���ԣ��ʺ����ڶ�ƽ����Ҫ��ϸߵĳ��ϡ�
             �ýӿ���MV_CC_FreeImageBuffer����ʹ�ã���������ȡ�������ݺ���Ҫ��MV_CC_FreeImageBuffer�ӿڽ�pFrame�ڵ�����ָ��Ȩ�޽����ͷš�
             �ýӿ���MV_CC_GetOneFrameTimeout��ȣ����Ÿ��ߵ�Ч�ʡ�����ȡ������ķ�������sdk�ڲ��Զ�����ģ���MV_CC_GetOneFrameTimeout�ӿ�����Ҫ�ͻ����з��䡣
             �ýӿ��ڵ���MV_CC_Display���޷�ȡ����
             �ýӿڶ���U3V��GIGE�豸����֧�֡�
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Get a frame of an image using an internal cache
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFrame                    [IN][OUT]       Image data and image information
 *  @param  nMsec                       [IN]            Waiting timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to get image data frame, you should call MV_CC_StartGrabbing to start image acquisition.
             This API can get frame data actively, the upper layer program should control the frequency of calling this API according to the frame rate. This API support setting timeout, and SDK will wait to return until data appears. This function will increase the streaming stability, which can be used in the situation with high stability requirement. 
             This API and MV_CC_FreeImageBuffer should be called in pairs, after processing the acquired data, you should call MV_CC_FreeImageBuffer to release the data pointer permission of pFrame. 
             This interface is more efficient than MV_CC_GetOneFrameTimeout. The allocation of the stream cache is automatically allocated within the SDK.The MV_CC_GetOneFrameTimeout interface needs to be allocated by customers themselves. 
             This API cannot be called to stream after calling MV_CC_Display.
             This API is not supported by CameraLink device. 
             This API is supported by both USB3 vision camera and GigE camera. 
 *****************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetImageBuffer(IN void* handle, IN OUT MV_FRAME_OUT* pstFrame, IN unsigned int nMsec);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ͷ�ͼ�񻺴�(�˽ӿ������ͷŲ���ʹ�õ�ͼ�񻺴棬��MV_CC_GetImageBuffer����ʹ��)
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFrame                    [IN]            ͼ�����ݺ�ͼ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ���MV_CC_GetImageBuffer����ʹ�ã�ʹ��MV_CC_GetImageBuffer�ӿ�ȡ����ͼ������pFrame����Ҫ��MV_CC_FreeImageBuffer�ӿڽ���Ȩ���ͷ�
             �ýӿ�ȡ��Ч�ʸ���GetOneFrameTimeout�ӿ�
			 ��GetImageBuffer������FreeImageBufferʱ��������ͼ�����Ϊ��ǰ������SDK�Ļ���ڵ����(�û����Ե���SetImageNode�ӿڣ�����SDK�Ļ��������
             �ýӿڶ���U3V��GIGE�豸����֧��
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Free image buffer(this interface can free image buffer, used with MV_CC_GetImageBuffer)
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFrame                    [IN]            Image data and image information
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks MV_CC_FreeImageBuffer and MV_CC_GetImageBuffer API call in pairs, before calling MV_CC_GetImageBuffer to get image data pFrame, you should call MV_CC_FreeImageBuffer to release the permission.
             Compared with API MV_CC_GetOneFrameTimeout
             The API has higher efficiency of image acquisition. The max. number of nodes can be outputted is same as the "nNum" of  the current configuration of the SDK's cache (users can call the SetImageNode interface to adjust the SDK's cache count)
             The API is not supported by CameraLink device.
             The API is supported by both USB3 vision camera and GigE camera. 
 **********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FreeImageBuffer(IN void* handle, IN MV_FRAME_OUT* pstFrame);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ó�ʱ���ƻ�ȡһ֡ͼƬ��SDK�ڲ��ȴ�ֱ��������ʱ����
 *  @param  handle                      [IN]            �豸���
 *  @param  pData                       [IN][OUT]       ͼ�����ݽ���ָ��
 *  @param  nDataSize                   [IN]            ���ջ����С
 *  @param  pstFrameInfo                [IN][OUT]       ͼ����Ϣ�ṹ��
 *  @param  nMsec                       [IN]            �ȴ���ʱʱ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ���øýӿڻ�ȡͼ������֮֡ǰ��Ҫ�ȵ���MV_CC_StartGrabbing����ͼ��ɼ�
             �ýӿ�Ϊ����ʽ��ȡ֡���ݣ��ϲ�Ӧ�ó�����Ҫ����֡�ʣ����ƺõ��øýӿڵ�Ƶ��
             �ýӿ�֧�����ó�ʱʱ�䣬SDK�ڲ��ȴ�ֱ��������ʱ���أ���������ȡ��ƽ���ԣ��ʺ����ڶ�ƽ����Ҫ��ϸߵĳ���
             �ýӿڶ���U3V��GIGE�豸����֧��
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Timeout mechanism is used to get image, and the SDK waits inside until the data is returned
 *  @param  handle                      [IN]            Device handle
 *  @param  pData                       [IN][OUT]       Image data receiving buffer
 *  @param  nDataSize                   [IN]            Buffer size
 *  @param  pstFrameInfo                [IN][OUT]       Image information structure
 *  @param  nMsec                       [IN]            Waiting timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to get image data frame, call MV_CC_StartGrabbing to start image acquisition.
             This API can get frame data actively, the upper layer program should control the frequency of calling this API according to the frame rate.
             This API supports setting timeout, SDK will wait to return until data appears. This function will increase the streaming stability, which can be used in the situation with high stability requirement.
             Both the USB3Vision and GIGE camera can support this API.
             This API is not supported by CameraLink device.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetOneFrameTimeout(IN void* handle, IN OUT unsigned char* pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pstFrameInfo, IN unsigned int nMsec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ȡ�����ݻ���
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ������û��ڲ�ֹͣȡ����ʱ�򣬾�����������в���Ҫ��ͼ��
             �ýӿ�������ģʽ�д���ģʽ�󣬿��������ʷ���ݡ�
             �ýӿ�Ŀǰֻ�����SDK�ڲ���ͼ�񻺴棬�ɼ����ڵĻ��滹�޷������
 
 *  @~english
 *  @brief  if Image buffers has retrieved the data��Clear them
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface allows user to clear the unnecessary images from the buffer memory without stopping acquisition.
             This interface allows user to clear previous data after switching from continuous mode to trigger mode. 
             This interface can only clear the image cache inside the SDK, and the cache in the Frame grabber cannot be cleared.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_ClearImageBuffer(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ��ǰͼ�񻺴�������Чͼ�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pnValidImageNum             [IN][OUT]       ��ǰͼ�񻺴�������Чͼ�������ָ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ�ֻͳ��SDK�ڲ�����Чͼ��������������ɼ��������ڵ���Чͼ�����
 
 *  @~english
 *  @brief  Get the number of valid images in the current image buffer
 *  @param  handle                      [IN]            Device handle
 *  @param  pnValidImageNum             [IN][OUT]       The number of valid images in the current image buffer
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface only counts the number of valid images inside the SDK, not including the number of valid images in the capture card cache.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetValidImageNum(IN void* handle, IN OUT unsigned int *pnValidImageNum);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʾһ֡ͼ��
 *  @param  handle                      [IN]            �豸���
 *  @param  pstDisplayInfo              [IN]            ͼ����Ϣ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ���豸�����޹أ���ȾģʽΪD3Dʱ��֧�ֵ����ֱ���Ϊ16384 * 163840

 *  @~english
 *  @brief  Display one frame image
 *  @param  handle                      [IN]            Device handle
 *  @param  pstDisplayInfo              [IN]            Frame Info
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Not related to device type��When the render mode is D3D, the maximum resolution supported is 16384 * 163840
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DisplayOneFrame(IN void* handle, IN MV_DISPLAY_FRAME_INFO* pstDisplayInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʾһ֡ͼ��
 *  @param  handle                      [IN]            �豸���
 *  @param  hWnd                        [IN]            ���ھ��
 *  @param  pstDisplayInfo              [IN]            ͼ����Ϣ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ�֧��PixelType_Gvsp_RGB8_Packed��PixelType_Gvsp_BGR8_Packed��PixelType_Gvsp_Mono8�������ظ�ʽ����Ⱦ���ߴ�С��int����
 *           �������ظ�ʽ��Ⱦ��֧�ֿ�����short
 *           ��ȾģʽΪD3Dʱ��֧�ֵ����ֱ���Ϊ16384 * 163840
 
 *  @~english
 *  @brief  Display one frame image
 *  @param  handle                      [IN]            Device handle
 *  @param  hWnd                        [IN]            HWND
 *  @param  pstDisplayInfo              [IN]            Frame Info
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API support rendering in three pixel formats:PixelType_Gvsp_RGB8_Packed,PixelType_Gvsp_BGR8_Packed and PixelType_Gvsp_Mono8,width and height to int.
 *           The rest of the pixel format rendering only supports width and height to short.
 *           When the render mode is D3D, the maximum resolution supported is 16384 * 163840.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DisplayOneFrameEx(IN void* handle, IN void* hWnd, IN MV_DISPLAY_FRAME_INFO_EX* pstDisplayInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����SDK�ڲ�ͼ�񻺴�ڵ���������ڵ���1����ץͼǰ����
 *  @param  handle                      [IN]            �豸���
 *  @param  nNum                        [IN]            ����ڵ����
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ���øýӿڿ�������SDK�ڲ�ͼ�񻺴�ڵ�������ڵ���MV_CC_StartGrabbing��ʼץͼǰ���á�
             ��ͬ�����Ϊȡ����ʽ��ͬ��������MV_CC_SetImageNodeNum�ӿ�����£�Ĭ�ϲ�ͬ���Ĭ�ϻ���ڵ������ͬ������ ˫U�ڲ�����Ĭ��3���ڵ�
             SDKʵ�ʷ���Ľڵ���� = SDK�ڲ�Ԥ����ĸ��� + �û�����Ľڵ�(MV_CC_SetImageNodeNum);
             �ýӿڲ�֧��MV_CAMERALINK_DEVICE ���͵��豸��
             �ýӿڽ���SDK�ڲ����仺��ģʽ��Ч���ⲿ���仺��ģʽ��������MV_CC_RegisterBuffer����Ч;
 
 *  @~english
 *  @brief  Set the number of the internal image cache nodes in SDK, Greater than or equal to 1, to be called before the capture
 *  @param  handle                      [IN]            Device handle
 *  @param  nNum                        [IN]            Image Node Number
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Call this interface to set the number of SDK internal image buffer nodes. The interface should be called before calling MV_CC_StartGrabbing for capturing. 
			 Due to different stream retrieval methods, different cameras default to different cache nodes by default when not calling the MV_CC_SetImageNodeNum interface. For example, for dual U internal allocation, the default number of cache nodes is 3
             The actual number of nodes allocated by the SDK = the number of pre allocated nodes within the SDK + the number of nodes allocated by the user (MV_CC_SetImageNodeNum)
             This interface does not support devices of type MV_CAMERALINK_DEVICE
             This interface is only valid for the SDK's internal allocation cache mode, and the external allocation cache mode (i.e., calling MV_CC_RegisterBuffer) is invalid;
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetImageNodeNum(IN void* handle, IN unsigned int nNum);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ȡ�����ԣ��ýӿ�ֻ֧��windowsƽ̨��
 *  @param  handle                      [IN]            �豸���
 *  @param  enGrabStrategy              [IN]            ����ö��ֵ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڶ���������ȡ�����ԣ��û����Ը���ʵ���������ѡ�񡣾����������£�
             OneByOne:�Ӿɵ���һ֡һ֡�Ĵ���������б��л�ȡͼ�񣬴��豸��Ĭ��Ϊ�ò���
             LatestImagesOnly:������������б��л�ȡ���µ�һ֡ͼ��ͬʱ�����������б�
             LatestImages:����������б��л�ȡ���µ�OutputQueueSize֡ͼ������OutputQueueSize��ΧΪ1-ImageNodeNum������MV_CC_SetOutputQueueSize�ӿ����ã�ImageNodeNumĬ��Ϊ1��
                          ����MV_CC_SetImageNodeNum�ӿ����� OutputQueueSize���ó�1��ͬ��LatestImagesOnly���ԣ�OutputQueueSize���ó�ImageNodeNum��ͬ��OneByOne����
             UpcomingImage:�ڵ���ȡ���ӿ�ʱ������������б�������ͼ�񣬲��ȴ��豸�������ɵ�һ֡ͼ��
			 �ò���֧��MV_GIGE_DEVICE��MV_USB_DEVICE�豸��ע��MV_USB_DEVICE�豸��֧�� MV_GrabStrategy_UpcomingImage ģʽ��
			 ͬʱ�ò���Ҳ��֧��MV_CAMERALINK_DEVICE��MV_1394_DEVICE��GenTL���͵��豸��
 
 *  @~english
 *  @brief  Set Grab Strategy��This interface only supports windows platform��
 *  @param  handle                      [IN]            Device handle
 *  @param  enGrabStrategy              [IN]            The value of Grab Strategy
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is set by four image acquisition approaches, the user may choose one as needed. Specific details are as followed: 
             OneByOne:Obtain image from output cache list frame by frame in order, this function is default strategy when device is on.
             LatestImagesOnly:Obtain the latest image from output cache list only, meanwhile clear output cache list.
             LatestImages:Obtain the latest OutputQueueSize image from output cache list, the range of OutputQueueSize is 1-ImageNodeNum, 
                          the user may set the value of MV_CC_SetOutputQueueSizeinterface,the default value of ImageNodeNum is 1,
                          If the user usesMV_CC_SetImageNodeNuminterface to set up OutputQueueSize,when the value of OutputQueueSize is set to be 1, 
                          the function will be same as LatestImagesOnly; if the value of OutputQueueSize is set to be ImageNodeNum, the function will be same as OneByOne.
             UpcomingImage:Ignore all images in output cache list when calling image acuiqisiotn interface, wait the next upcoming image generated. 
			 This API support MV_GIGE_DEVICE,MV_USB_DEVICE device, notication:MV_USB_DEVICE device not support MV_GrabStrategy_UpcomingImage
			 This API not support MV_CAMERALINK_DEVICE,MV_1394_DEVICE,GenTL device.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetGrabStrategy(IN void* handle, IN MV_GRAB_STRATEGY enGrabStrategy);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����������������ýӿ�ֻ֧��windowsƽ̨��ֻ����MV_GrabStrategy_LatestImages�����²���Ч����Χ��1-ImageNodeNum��
 *  @param  handle                      [IN]            �豸���
 *  @param  nOutputQueueSize            [IN]            ����������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ�����LatestImagesȡ���������׵��ã���������LatestImages�����������������ͼ��ĸ�����������ȡ�������ж�̬��������������
 *            ��Ϊ˫U�������nOutputQueueSize��СӦ����Ϊ2
 
 *  @~english
 *  @brief  Set The Size of Output Queue(This interface only supports windows platform, Only work under the strategy of MV_GrabStrategy_LatestImages��rang��1-ImageNodeNum)
 *  @param  handle                      [IN]            Device handle
 *  @param  nOutputQueueSize            [IN]            The Size of Output Queue
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface must be used with LatestImages Grab strategy, it is used for setting the maximum allowance queue size of the image under the LatestImages strategy.
             The user may change the output queue size while grabbing images.
 *           The DoubleUsb Device nOutputQueueSize at least 2
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetOutputQueueSize(IN void* handle, IN unsigned int nOutputQueueSize);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸��Ϣ��ȡ��֮ǰ����
 *  @param  handle                      [IN]            �豸���
 *  @param  pstDevInfo                  [IN][OUT]       ���ظ��������й��豸��Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ֧���û��ڴ��豸���ȡ�豸��Ϣ����֧��GenTL�豸
             �����豸��GigE�豸������øýӿڴ����������գ���˲�������ȡ�������е��øýӿڡ�
 
 *  @~english
 *  @brief  Get device information
 *  @param  handle                      [IN]            Device handle
 *  @param  pstDevInfo                  [IN][OUT]       Structure pointer of device information
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks The API support users to access device information after opening the device��don't support GenTL Devices
             If the device is a GigE camera, there is a blocking risk in calling the interface, so it is not recommended to call the interface during the fetching process. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetDeviceInfo(IN void * handle, IN OUT MV_CC_DEVICE_INFO* pstDevInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�������͵���Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstInfo                     [IN][OUT]       ���ظ��������й��豸�������͵���Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ӿ�����������Ҫ��ȡ����Ϣ���ͣ�ָ��MV_ALL_MATCH_INFO�ṹ���е�nType���ͣ�����ȡ��Ӧ����Ϣ����MV_ALL_MATCH_INFO�ṹ����pInfo�ﷵ�أ�
             �ýӿڵĵ���ǰ������ȡ��������ȡ����Ϣ���ͣ���ȡGigE�豸��MV_MATCH_TYPE_NET_DETECT��Ϣ���ڿ���ץͼ֮����ã���ȡU3V�豸��MV_MATCH_TYPE_USB_DETECT��Ϣ���ڴ��豸֮�����
             ��Ϣ���� MV_MATCH_TYPE_NET_DETECT ��Ӧ�ṹ��MV_MATCH_INFO_NET_DETECT�� ֻ֧��MV_GIGE_DEVICE���/MV_GENTL_GIGE_DEVICE���
             ��Ϣ���� MV_MATCH_TYPE_USB_DETECT ��Ӧ�ṹ��MV_MATCH_INFO_USB_DETECT�� ֻ֧��MV_USB_DEVICE �������
             �ýӿڲ�֧��MV_CAMERALINK_DEVICE�豸��
 
 *  @~english
 *  @brief  Get various type of information
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInfo                     [IN][OUT]       Structure pointer of various type of information
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Input required information type (specify nType in structure MV_ALL_MATCH_INFO) in the interface and get corresponding information (return in pInfo of structure MV_ALL_MATCH_INFO)
             The calling precondition of this interface is determined by obtained information type. Call after enabling capture to get MV_MATCH_TYPE_NET_DETECT information of GigE device,
             and call after starting device to get MV_MATCH_TYPE_USB_DETECT information of USB3Vision device.
             The information type MV_MATCH_TYPE_NET_DETECT corresponds to the structure MV_MATCH_INFO_NET_DETECT, which only supports  cameras of  MV_GIGE_DEVICE and MV_GENTL_GIGE_DEVICE types
             The information type MV_MATCH_TYPE_USB_DETECT corresponds to the structure MV_MATCH_INFO_USB_DETECT, which only supports cameras of MV_USB_DEVICE type
             This API is not supported by MV_CAMERALINK_DEVICE device. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetAllMatchInfo(IN void* handle, IN OUT MV_ALL_MATCH_INFO* pstInfo);



/*******************Part2 ch: ���/�ɼ��������������ýӿ� | en: Camera /Frame grabber attribute nodes universal interface*******************/

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡInteger����ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ������Ϣ��Ϊ"Width"
 *  @param  pstIntValue                 [IN][OUT]       ���ظ��������й��豸���Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡint���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Get Integer value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value, for example, using "Width" to get width
 *  @param  pstIntValue                 [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks You can call this API to get the value of camera node with integer type after connecting the device. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetIntValueEx(IN void* handle,IN const char* strKey,IN OUT MVCC_INTVALUE_EX *pstIntValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Integer������ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ������Ϣ��Ϊ"Width"
 *  @param  nValue                      [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������int���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Set Integer value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value, for example, using "Width" to set width
 *  @param  nValue                      [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks You can call this API to get the value of camera node with integer type after connecting the device. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetIntValueEx(IN void* handle,IN const char* strKey,IN int64_t nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡEnum����ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
 *  @param  pstEnumValue                [IN][OUT]       ���ظ��������й��豸���Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡEnum���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Get Enum value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value, for example, using "PixelFormat" to get pixel format
 *  @param  pstEnumValue                [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified Enum nodes. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetEnumValue(IN void* handle,IN const char* strKey,IN OUT MVCC_ENUMVALUE *pstEnumValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Enum������ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
 *  @param  nValue                      [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������Enum���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Set Enum value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value, for example, using "PixelFormat" to set pixel format
 *  @param  nValue                      [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified Enum nodes. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetEnumValue(IN void* handle,IN const char* strKey,IN unsigned int nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡEnum�ͽڵ�ָ��ֵ�ķ���
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
 *  @param  pstEnumEntry                [IN][OUT]           ��Ҫ��ȡ���豸�����Է���
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡEnum���͵�ָ���ڵ��ֵ����Ӧ�ķ��š�
 
 *  @~english
 *  @brief  Get the symbolic of the specified value of the Enum type node
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value, for example, using "PixelFormat" to set pixel format
 *  @param  pstEnumEntry                [IN][OUT]           Symbolic to get
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Call this interface after connecting the device to obtain the symbol corresponding to the value of the specified node of Enum type.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetEnumEntrySymbolic(IN void* handle,IN const char* strKey,IN OUT MVCC_ENUMENTRY* pstEnumEntry);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Enum������ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
 *  @param  strValue                    [IN]            ��Ҫ���õ��豸�������ַ���
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������Enum���͵�ָ���ڵ��ֵ��
           
 *  @~english
 *  @brief  Set Enum value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value, for example, using "PixelFormat" to set pixel format
 *  @param  strValue                    [IN]            Feature String to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified Enum nodes. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetEnumValueByString(IN void* handle,IN const char* strKey,IN const char* strValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡFloat����ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  pstFloatValue               [IN][OUT]       ���ظ��������й��豸���Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡfloat���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Get Float value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value
 *  @param  pstFloatValue               [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified float node. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetFloatValue(IN void* handle,IN const char* strKey,IN OUT MVCC_FLOATVALUE *pstFloatValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����float������ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  fValue                      [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������float���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Set float value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value
 *  @param  fValue                      [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified float node. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetFloatValue(IN void* handle,IN const char* strKey,IN float fValue);
    
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡBoolean����ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  pbValue                     [IN][OUT]       ���ظ��������й��豸����ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡbool���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Get Boolean value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value
 *  @param  pbValue                     [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified bool nodes. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetBoolValue(IN void* handle,IN const char* strKey,IN OUT bool *pbValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Boolean������ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  bValue                      [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������bool���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Set Boolean value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value
 *  @param  bValue                      [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified bool nodes. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBoolValue(IN void* handle,IN const char* strKey,IN bool bValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡString����ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  pstStringValue              [IN][OUT]       ���ظ��������й��豸���Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡstring���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Get String value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value
 *  @param  pstStringValue              [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified string nodes. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetStringValue(IN void* handle,IN const char* strKey,IN OUT MVCC_STRINGVALUE *pstStringValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����String������ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  strValue                    [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������string���͵�ָ���ڵ��ֵ��
 
 *  @~english
 *  @brief  Set String value
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value
 *  @param  strValue                    [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified string nodes. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetStringValue(IN void* handle,IN const char* strKey,IN const char* strValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Command������ֵ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������ָ����Command���ͽڵ㡣
 
 *  @~english
 *  @brief  Send Command
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strKey                      [IN]            Key value
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified Command nodes. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetCommandValue(IN void* handle,IN const char* strKey);



/********************************************************************//**
 *  @~chinese
 *  @brief  ���ڴ�
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  pBuffer                     [IN][OUT]       ��Ϊ����ֵʹ�ã�����������ڴ�ֵ��GEV�豸�ڴ�ֵ�ǰ��մ��ģʽ�洢�ģ��ɼ����豸�Ͳɼ�����������մ�˴洢������Э���豸����С�˴洢��
 *  @param  nAddress                    [IN]            ����ȡ���ڴ��ַ���õ�ַ���Դ��豸��Camera.xml�ļ��л�ȡ������xxx_RegAddr��xml�ڵ�ֵ
 *  @param  nLength                     [IN]            ����ȡ���ڴ泤��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸����ȡĳ�μĴ��������ݡ�
 
 *  @~english
 *  @brief  Read Memory
 *  @param  handle                      [IN]            Device Handle/Frame grabber handle
 *  @param  pBuffer                     [IN][OUT]       Used as a return value, save the read-in memory value ( The memory value of GEV devices is stored in the big end mode, with the capture card device and the camera under the capture card stored in the big end mode, and other protocol devices stored in the small end mode)
 *  @param  nAddress                    [IN]            Memory address to be read, which can be obtained from the Camera.xml file of the device, the form xml node value of xxx_RegAddr
 *  @param  nLength                     [IN]            Length of the memory to be read
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Access device, read the data from certain register.
*************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_ReadMemory(IN void* handle , IN OUT void *pBuffer, IN int64_t nAddress, IN int64_t nLength);

/********************************************************************//**
 *  @~chinese
 *  @brief  д�ڴ�
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  pBuffer                     [IN]            ��д����ڴ�ֵ��ע��GEV�豸�ڴ�ֵҪ���մ��ģʽ�洢���ɼ����豸�Ͳɼ�����������մ�˴洢������Э���豸����С�˴洢��
 *  @param  nAddress                    [IN]            ��д����ڴ��ַ���õ�ַ���Դ��豸��Camera.xml�ļ��л�ȡ������xxx_RegAddr��xml�ڵ�ֵ
 *  @param  nLength                     [IN]            ��д����ڴ泤��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸����һ������д��ĳ�μĴ�����
 
 *  @~english
 *  @brief  Write Memory
 *  @param  handle                      [IN]            Device Handle/Frame grabber handle
 *  @param  pBuffer                     [IN]            Memory value to be written ( Note The memory value of GEV devices is stored in the big end mode, with the capture card device and the camera under the capture card stored in the big end mode, and other protocol devices stored in the small end mode)
 *  @param  nAddress                    [IN]            Memory address to be written, which can be obtained from the Camera.xml file of the device, the form xml node value of xxx_RegAddr
 *  @param  nLength                     [IN]            Length of the memory to be written
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Access device, write a piece of data into a certain segment of register.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_WriteMemory(IN void* handle, IN const void *pBuffer, IN int64_t nAddress, IN int64_t nLength);



/********************************************************************//**
 *  @~chinese
 *  @brief  ���GenICam�ڵ㻺��
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @~english
 *  @brief  Invalidate GenICam Nodes
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_InvalidateNodes(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸������XML
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  pData                       [IN][OUT]       XML���ݽ��ջ���
 *  @param  nDataSize                   [IN]            ���ջ����С
 *  @param  pnDataLen                   [IN][OUT]       ʵ�����ݴ�С
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ��pDataΪNULL��nDataSize��ʵ�ʵ�xml�ļ�Сʱ�����������ݣ���pnDataLen����xml�ļ���С
             ��pDataΪ��Ч�����ַ���һ����㹻��ʱ�������������ݱ����ڸû������棬����pnDataLen����xml�ļ�ʵ�ʴ�С��
 
 *  @~english
 *  @brief  Get camera feature tree XML
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  pData                       [IN][OUT]       XML data receiving buffer
 *  @param  nDataSize                   [IN]            Buffer size
 *  @param  pnDataLen                   [IN][OUT]       Actual data length
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks When pData is NULL or nDataSize than the actual XML file hours, do not copy the data, returned by pnDataLen XML file size.
             When pData is a valid cache address and the cache is large enough, copy the full data into the cache, and pnDataLen returns the actual size of the XML file.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_GetGenICamXML(IN void* handle, IN OUT unsigned char* pData, IN unsigned int nDataSize, IN OUT unsigned int* pnDataLen);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��õ�ǰ�ڵ�ķ���ģʽ
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strName                     [IN]            �ڵ�����
 *  @param  penAccessMode               [IN][OUT]       �ڵ�ķ���ģʽ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����

 *  @~english
 *  @brief  Get Access mode of cur node
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strName                     [IN]            Name of node
 *  @param  penAccessMode               [IN][OUT]       Access mode of the node
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_GetNodeAccessMode(IN void* handle, IN const char * strName, IN OUT MV_XML_AccessMode *penAccessMode);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��õ�ǰ�ڵ������
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strName                     [IN]            �ڵ�����
 *  @param  penInterfaceType            [IN][OUT]       �ڵ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڿ����ڵ������ܽӿ�֮ǰ����ǰ֪���ڵ����ͣ������û�ѡ����ʵ����ܽӿڽ��нڵ�ֵ�����úͻ�ȡ��

 *  @~english
 *  @brief  Get Interface Type of cur node
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strName                     [IN]            Name of node
 *  @param  penInterfaceType            [IN][OUT]       Interface Type of the node
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks The interface can know the node type in advance before calling the universal interface, so as to facilitate users to select the appropriate universal interface for setting and obtaining the node value.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_XML_GetNodeInterfaceType(IN void* handle, IN const char * strName, IN OUT MV_XML_InterfaceType *penInterfaceType);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸����
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strFileName                 [IN]            �����ļ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Save camera feature
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strFileName                 [IN]            File name
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FeatureSave(IN void* handle, IN const char* strFileName);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸����
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strFileName                 [IN]            �����ļ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Load camera feature
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strFileName                 [IN]            File name
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FeatureLoad(IN void* handle, IN const char* strFileName);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸���Բ����������Ϣ�б�
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  strFileName                 [IN]            �����ļ���
 *  @param  stNodeErrorList             [IN OUT]        ������Ϣ�б������û����ⲿ���벢���ڲ�������ݣ��ò���������null�����û������ĵ���ʱ�Ĵ�����Ϣ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ���ֽڵ㵼��ʧ��ʱ���ӿڷ���MV_OK��ͨ��������Ϣ�б���stNodeError��ȡ�����ڵ㼰ʧ��ԭ��

 *  @~english
 *  @brief  Load camera feature with error message list
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  strFileName                 [IN]            File name
 *  @param  pstNodeErrorList            [IN OUT]        Error message list, requested by the user externally and filled with data internally, \n
 *                                                      this parameter allows null to indicate that the user is not concerned about error information during import.
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks When some nodes fail to load, the interface returns MV_OK. \n
 *           The error node and the reason for the failure are obtained through stNodeError in the error message list.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FeatureLoadEx(IN void* handle, IN const char* strFileName, IN OUT MVCC_NODE_ERROR_LIST* pstNodeErrorList);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���豸��ȡ�ļ�
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  pstFileAccess               [IN]            �ļ���ȡ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Read the file from the camera
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  pstFileAccess               [IN]            File access structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FileAccessRead(IN void* handle, IN MV_CC_FILE_ACCESS * pstFileAccess);


/********************************************************************//**
 *  @~chinese
 *  @brief  ���豸��ȡ�ļ�,�ļ���Data����
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  pstFileAccess               [IN]            �ļ���ȡ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� �����ļ�����Ȩ�������ʧ�� 
 
 *  @~english
 *  @brief  Read the file data from the camera
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  pstFileAccess               [IN]            File access structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FileAccessReadEx(IN void* handle, IN OUT MV_CC_FILE_ACCESS_EX * pstFileAccessEx);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ļ�д���豸
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  pstFileAccess               [IN]            �ļ���ȡ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @~english
 *  @brief  Write the file to camera
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  pstFileAccess               [IN]            File access structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FileAccessWrite(IN void* handle, IN MV_CC_FILE_ACCESS * pstFileAccess);


/********************************************************************//**
 *  @~chinese
 *  @brief  ������(buffer)д���豸
 *  @param  handle                        [IN]            �豸���/�ɼ������
 *  @param  pstFileAccessEx               [IN][OUT]       �ļ���ȡ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ�ֱ��ʹ�û������ݣ����ж�д����������ֱ�Ӳ����ļ�������Ȩ�޵�����,��MV_CC_FileAccessWrite����չ�ӿ�
 
 *  @~english
 *  @brief  Write the data(buffer) to camera
 *  @param  handle                        [IN]            Device handle/Frame grabber handle
 *  @param  pstFileAccessEx               [IN][OUT]       File access structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface uses cached data for read and write,solve the problem of no permissions in direct operation files, it's an extended interface of MV_CC_FileAccessWrite.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FileAccessWriteEx(IN void* handle, IN OUT MV_CC_FILE_ACCESS_EX * pstFileAccessEx);


/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ļ���ȡ�Ľ���
 *  @param  handle                      [IN]            �豸���/�ɼ������
 *  @param  pstFileAccessProgress       [IN][OUT]       ��������
 *  @return �ɹ�������MV_OK�����󣬷��ش����� ����ǰ�ļ���ȡ��״̬��
 
 *  @~english
 *  @brief  Get File Access Progress 
 *  @param  handle                      [IN]            Device handle/Frame grabber handle
 *  @param  pstFileAccessProgress       [IN][OUT]       File access Progress
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetFileAccessProgress(IN void* handle, IN OUT MV_CC_FILE_ACCESS_PROGRESS * pstFileAccessProgress);


/*******************Part3 ch: ������� | en: Camera upgrade *******************/

/********************************************************************//**
 *  @~chinese
 *  @brief  �豸��������
 *  @param  handle                      [IN]            �豸���
 *  @param  strFilePathName             [IN]            �ļ���
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿڿ��Խ������̼��ļ����͸��豸����������
             �ýӿ���Ҫ�ȴ������̼��ļ��ɹ������豸��֮���ٷ��أ���Ӧʱ����ܽϳ���
 
 *  @~english
 *  @brief  Device Local Upgrade
 *  @param  handle                      [IN]            Device handle
 *  @param  strFilePathName             [IN]            File name
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Call this API to send the upgrade firmware to the device for upgrade.
             This API will wait for return until the upgrade firmware is sent to the device, this response may take a long time.
             For CameraLink device, it keeps sending upgrade firmware continuously. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_LocalUpgrade(IN void* handle, IN const void* strFilePathName);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ��������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnProcess                   [IN][OUT]       ���Ƚ��յ�ַ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 
 *  @~english
 *  @brief  Get Upgrade Progress
 *  @param  handle                      [IN]            Device handle
 *  @param  pnProcess                   [IN][OUT]       Progress receiving address
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetUpgradeProcess(IN void* handle, IN OUT unsigned int* pnProcess);


/*******************Part4  ch: ע���쳣�ص����¼��ӿ� | en: Enrol abnormal callbacks and event interface*******************/

/********************************************************************//**
 *  @~chinese
 *  @brief  ע���쳣��Ϣ�ص����ڴ��豸֮�����
 *  @param  handle                      [IN]            �豸���
 *  @param  cbException                 [IN]            �쳣�ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ���Ҫ��MV_CC_OpenDevice���豸֮����á�
             �豸�쳣�Ͽ����Ӻ�����ڻص������ȡ���쳣��Ϣ��GigE�豸����֮����Ҫ�ȵ���MV_CC_CloseDevice�ӿڹر��豸���ٵ���MV_CC_OpenDevice�ӿ����´��豸��
 
 *  @~english
 *  @brief  Register Exception Message CallBack, call after open device
 *  @param  handle                      [IN]            Device handle
 *  @param  cbException                 [IN]            Exception Message CallBack Function Pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Call this interface after the device is opened by MV_CC_OpenDevice. 
             When device is exceptionally disconnected, the exception message can be obtained from callback function. For Disconnected GigE device,
             first call MV_CC_CloseDevice to shut device, and then call MV_CC_OpenDevice to reopen the device. 
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterExceptionCallBack(IN void* handle, IN void(__stdcall* cbException)(unsigned int nMsgType, void* pUser), IN void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��ȫ���¼��ص����ڴ��豸֮�����
 *  @param  handle                      [IN]            �豸���
 *  @param  cbEvent                     [IN]            �¼��ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿ������¼��ص��������ڻص����������ȡ�ɼ����ع���¼���Ϣ
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Register event callback, which is called after the device is opened
 *  @param  handle                      [IN]            Device handle
 *  @param  cbEvent                     [IN]            Event CallBack Function Pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Call this API to set the event callback function to get the event information, e.g., acquisition, exposure, and so on
             This API is not supported by CameraLink device.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterAllEventCallBack(IN void* handle, IN void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), IN void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע�ᵥ���¼��ص����ڴ��豸֮�����
 *  @param  handle                      [IN]            �豸���
 *  @param  strEventName                [IN]            �¼�����
 *  @param  cbEvent                     [IN]            �¼��ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿ������¼��ص��������ڻص����������ȡ�ɼ����ع���¼���Ϣ��
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Register single event callback, which is called after the device is opened
 *  @param  handle                      [IN]            Device handle
 *  @param  strEventName                [IN]            Event name
 *  @param  cbEvent                     [IN]            Event CallBack Function Pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Call this API to set the event callback function to get the event information, e.g., acquisition, exposure, and so on.
             This API is not supported by CameraLink device .
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterEventCallBackEx(IN void* handle, IN const char* strEventName, IN void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), IN void* pUser);


/*******************Part5 ch: ��GigE�豸֧�ֵĽӿ� | en: Only support GigE interface*******************/

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ö�ٳ�ʱʱ�䣬��֧��GigEЭ�飬��Χ:[1, UINT_MAX)
 *  @param  nMilTimeout                 [IN]            ��ʱʱ�䣬ӦΪ�޷�������,Ĭ��100ms
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ڵ���MV_CC_EnumDevices��ö�ٽӿ�ǰʹ�øýӿڣ�������ö��GIGE�豸���������ʱʱ�䣨Ĭ��100ms��,���Լ������ʱʱ�䣬���ӿ�ö��GIGE�豸���ٶ�
 *  @remarks ��֧��GigEVision�豸��

 *  @~english
 *  @brief  Set enumerate device timeout,only support GigE,range:[1, UINT_MAX)
 *  @param  nMilTimeout                 [IN]            time out,input of unsigned int,default 100ms
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Before calling enum device interfaces,call MV_GIGE_SetEnumDevTimeout to set max timeout,can reduce the maximum timeout to speed up the enumeration of GigE devices.
 *  @remarks This API only support GigE Vision Device.
             
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetEnumDevTimeout(IN unsigned int nMilTimeout);

/********************************************************************//**
 *  @~chinese
 *  @brief  ǿ��IP
 *  @param  handle                      [IN]            �豸���
 *  @param  nIP                         [IN]            ���õ�IP
 *  @param  nSubNetMask                 [IN]            ��������
 *  @param  nDefaultGateWay             [IN]            Ĭ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ǿ�������豸�������������IP���������롢Ĭ�����أ���ǿ������֮����Ҫ���´����豸�����֧��GigEVision(MV_GIGE_DEVICE)�豸��GenTL(MV_GENTL_GIGE_DEVICE)�豸
             ����豸ΪDHCP��״̬�����øýӿ�ǿ�������豸�������֮���豸����������
 
 *  @~english
 *  @brief  Force IP
 *  @param  handle                      [IN]            Device handle
 *  @param  nIP                         [IN]            IP to set
 *  @param  nSubNetMask                 [IN]            Subnet mask
 *  @param  nDefaultGateWay             [IN]            Default gateway
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Force setting camera network parameter (including IP address, subnet mask, default gateway). After forced setting, device handle should be created again. 
             This API support GigEVision(MV_GIGE_DEVICE) and GenTL(MV_GENTL_GIGE_DEVICE) device.
             If device is in DHCP status, after calling this API to force setting camera network parameter, the device will restart.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_ForceIpEx(IN void* handle, IN unsigned int nIP, IN unsigned int nSubNetMask, IN unsigned int nDefaultGateWay);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����IP��ʽ
 *  @param  handle                      [IN]            �豸���
 *  @param  nType                       [IN]            IP���ͣ���MV_IP_CFG_x
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �������������豸��IP��ʽ����DHCP��LLA�ȣ���֧��GigEVision(MV_GIGE_DEVICE)��GenTl(MV_GENTL_GIGE_DEVICE)���豸��
 
 *  @~english
 *  @brief  IP configuration method
 *  @param  handle                      [IN]            Device handle
 *  @param  nType                       [IN]            IP type, refer to MV_IP_CFG_x
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Send command to set camera IP mode, such as DHCP and LLA, only supported by GigEVision(MV_GIGE_DEVICE) and GenTL(MV_GENTL_GIGE_DEVICE) Device.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetIpConfig(IN void* handle, IN unsigned int nType);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ý�ʹ��ĳ��ģʽ,type: MV_NET_TRANS_x��������ʱ��Ĭ������ʹ��driver
 *  @param  handle                      [IN]            �豸���
 *  @param  nType                       [IN]            ���紫��ģʽ����MV_NET_TRANS_x
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿڿ�������SDK�ڲ�����ʹ�õ�����ģʽ��Ĭ������ʹ������ģʽ����GigEVision�豸֧�֡�
 
 *  @~english
 *  @brief  Set to use only one mode,type: MV_NET_TRANS_x. When do not set, priority is to use driver by default
 *  @param  handle                      [IN]            Device handle
 *  @param  nType                       [IN]            Net transmission mode, refer to MV_NET_TRANS_x
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarksSet SDK internal priority network mode through this interface, drive mode by default, only supported by GigEVision camera.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetNetTransMode(IN void* handle, IN unsigned int nType);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ���紫����Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstInfo                     [IN][OUT]       ��Ϣ�ṹ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿڿ��Ի�ȡ���紫�������Ϣ�������ѽ������ݴ�С����֡�����ȣ���MV_CC_StartGrabbing�����ɼ�֮����á���GigEVision�豸֧�֡�
 
 *  @~english
 *  @brief  Get net transmission information
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInfo                     [IN][OUT]       Information Structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Get network transmission information through this API, including received data size, number of lost frames.
             Call this API after starting image acquiring through MV_CC_StartGrabbing. This API is supported only by GigEVision Camera.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetNetTransInfo(IN void* handle, IN OUT MV_NETTRANS_INFO* pstInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ö������Ļظ�������
 *  @param  nMode                       [IN]            �ظ������ͣ�Ĭ�Ϲ㲥����0-������1-�㲥
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�ֻ��GigE�����Ч��

 *  @~english
 *  @brief  Setting the ACK mode of devices Discovery.
 *  @param  nMode                       [IN]            ACK mode��Default-Broadcast��,0-Unicast,1-Broadcast.
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This interface is ONLY effective on GigE cameras.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetDiscoveryMode(IN unsigned int nMode);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����GVSPȡ����ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ��ʱʱ�䣬Ĭ��30ms����Χ:[10 - UINT_MAX)
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �����豸֮��ȡ����������ǰ�����øýӿڿ�������GVSPȡ����ʱʱ�䡣GVSPȡ����ʱ���ù��̿������ͼ���쳣�����ù����������ȡ��ʱ��䳤��
 
 *  @~english
 *  @brief  Set GVSP streaming timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            Timeout, default 30ms, range:[10 - UINT_MAX)
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, and just before start streaming, 
 *           call this interface to set GVSP streaming timeout value.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetGvspTimeout(IN void* handle, IN unsigned int nMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡGVSPȡ����ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  pnMillisec                  [IN][OUT]       ��ʱʱ��ָ�룬�Ժ���Ϊ��λ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��GVSPȡ����ʱʱ��
 
 *  @~english
 *  @brief  Get GVSP streaming timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  pnMillisec                  [IN][OUT]       Timeout, ms as unit
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to get the current GVSP streaming timeout.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetGvspTimeout(IN void* handle, IN OUT unsigned int* pnMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����GVCP���ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ��ʱʱ��(ms)��Ĭ��500ms����Χ��[0,10000]
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �����豸֮����øýӿڿ�������GVCP���ʱʱ�䡣
 
 *  @~english
 *  @brief  Set GVCP cammand timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            Timeout(ms), default 500ms, range: [0,10000]
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks The API can set GVCP command timeout(ms) after device is connected .
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetGvcpTimeout(IN void* handle, IN unsigned int nMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡGVCP���ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  pnMillisec                  [IN][OUT]       ��ʱʱ��ָ�룬�Ժ���Ϊ��λ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��GVCP��ʱʱ�䡣
 
 *  @~english
 *  @brief  Get GVCP cammand timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  pnMillisec                  [IN][OUT]       Timeout, ms as unit
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to get the current GVCP timeout.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetGvcpTimeout(IN void* handle, IN OUT unsigned int* pnMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����ش�GVCP�������
 *  @param  handle                      [IN]            �豸���
 *  @param  nRetryGvcpTimes             [IN]            �ش���������Χ��0-100
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�������GVCP�������쳣ʱ�������ش��Ĵ�������һ���̶��Ͽ��Ա����豸���ߣ���ΧΪ0-100��
 
 *  @~english
 *  @brief  Set the number of retry GVCP cammand
 *  @param  handle                      [IN]            Device handle
 *  @param  nRetryGvcpTimes             [IN]            The number of retries��rang��0-100
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to increase The Times of retransmission when GVCP packet transmission is abnormal,and to some extent,
             it can avoid dropping the camera, with a range of 0-100.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetRetryGvcpTimes(IN void* handle, IN unsigned int nRetryGvcpTimes);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ش�GVCP�������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnRetryGvcpTimes            [IN][OUT]       �ش�����ָ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��GVCP�ش�������Ĭ��3�Ρ�
 
 *  @~english
 *  @brief  Get the number of retry GVCP cammand
 *  @param  handle                      [IN]            Device handle
 *  @param  pnRetryGvcpTimes            [IN][OUT]       The number of retries
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to get the current number of GVCP retransmissions, which defaults to 3.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetRetryGvcpTimes(IN void* handle, IN OUT unsigned int* pnRetryGvcpTimes);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ��ѵ�packet size���ýӿ�Ŀǰֻ֧��GigE�豸
 *  @param  handle                      [IN]            �豸���
 *  @return ���packetsize
 *  @remarks ��ȡ��ѵ�packet size����ӦGigEVision�豸��SCPS��
             �ýӿ���Ҫ��MV_CC_OpenDevice֮��MV_CC_StartGrabbing֮ǰ���á�
             �ýӿڲ�֧��CameraLink�豸��U3V�豸��
			 �ýӿڲ�֧��GenTL�豸��Э�鲻֧�֣�,�����GenTL��ʽ���ӵ���������������������ʵ���������GevSCPSPacketSize����������1500��
 
 *  @~english
 *  @brief  Get the optimal Packet Size, Only support GigE Camera
 *  @param  handle                      [IN]            Device handle
 *  @return Optimal packetsize
 *  @remarks To get optimized packet size, for GigEVision device is SCPS
             and it is the size of a packet transported on the network. The interface should be called after MV_CC_OpenDevice and before MV_CC_StartGrabbing.
             This API is not supported by CameraLink device and U3V device. 
			 This interface does not support GenTL devices (protocol not supported). If a network camera is added in GenTL mode, it is recommended to configure GevSCPSPacketSize according to the actual network situation,or 1500.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetOptimalPacketSize(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����Ƿ���ط���֧�֣����ط�������
 *  @param  handle                      [IN]            �豸���
 *  @param  bEnable                     [IN]            �Ƿ�֧���ط���
 *  @param  nMaxResendPercent           [IN]            ����ط���
 *  @param  nResendTimeout              [IN]            �ط���ʱʱ�䣬��Χ��0-10000ms
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �����豸֮����øýӿڿ��������ط������ԣ���GigEVision�豸֧�֡�
 
 *  @~english
 *  @brief  Set whethe to enable resend, and set resend
 *  @param  handle                      [IN]            Device handle
 *  @param  bEnable                     [IN]            enable resend
 *  @param  nMaxResendPercent           [IN]            Max resend persent
 *  @param  nResendTimeout              [IN]            Resend timeout, rang��0-10000ms
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set resend packet properties, only supported by GigEVision camera.
 ************************************************************************/
#ifndef __cplusplus
MV_CAMCTRL_API int __stdcall MV_GIGE_SetResend(IN void* handle, IN unsigned int bEnable, IN unsigned int nMaxResendPercent, IN unsigned int nResendTimeout);
#else
MV_CAMCTRL_API int __stdcall MV_GIGE_SetResend(IN void* handle, IN unsigned int bEnable, IN unsigned int nMaxResendPercent = 10, IN unsigned int nResendTimeout = 50);
#endif

/********************************************************************//**
 *  @~chinese
 *  @brief  �����ش���������Դ���
 *  @param  handle                      [IN]            �豸���
 *  @param  nRetryTimes                 [IN]            �ش���������Դ�����Ĭ��20
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڱ����ڵ���MV_GIGE_SetResend�����ش�������֮����ã�����ʧ���ҷ���MV_E_CALLORDER
 
 *  @~english
 *  @brief  set the max resend retry times
 *  @param  handle                      [IN]            Device handle
 *  @param  nRetryTimes                 [IN]            The max times to retry resending lost packets��default 20
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface MUST be called after enabling resending lost packets by calling MV_GIGE_SetResend,
 *           otherwise would fail and return MV_E_CALLORDER.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall  MV_GIGE_SetResendMaxRetryTimes(IN void* handle, IN unsigned int nRetryTimes);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ش���������Դ���
 *  @param  handle                      [IN]            �豸���
 *  @param  pnRetryTimes                [IN][OUT]       �ش���������Դ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڱ����ڵ���MV_GIGE_SetResend�����ش�������֮����ã�����ʧ���ҷ���MV_E_CALLORDER
 
 *  @~english
 *  @brief  get the max resend retry times
 *  @param  handle                      [IN]            Device handle
 *  @param  pnRetryTimes                [IN][OUT]       The max times to retry resending lost packets
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface MUST be called after enabling resending lost packets by calling MV_GIGE_SetResend,
 *           otherwise would fail and return MV_E_CALLORDER. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall  MV_GIGE_GetResendMaxRetryTimes(IN void* handle, IN OUT unsigned int* pnRetryTimes);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͬһ�ش����������֮���ʱ����
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ͬһ�ش����������֮���ʱ������Ĭ��10ms
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڱ����ڵ���MV_GIGE_SetResend�����ش�������֮����ã�����ʧ���ҷ���MV_E_CALLORDER
 
 *  @~english
 *  @brief  set time interval between same resend requests
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            The time interval between same resend requests,default 10ms
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface MUST be called after enabling resending lost packets by calling MV_GIGE_SetResend,
 *           otherwise would fail and return MV_E_CALLORDER. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall  MV_GIGE_SetResendTimeInterval(IN void* handle, IN unsigned int nMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡͬһ�ش����������֮���ʱ����
 *  @param  handle                      [IN]            �豸���
 *  @param  pnMillisec                  [IN][OUT]       ͬһ�ش����������֮���ʱ����
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڱ����ڵ���MV_GIGE_SetResend�����ش�������֮����ã�����ʧ���ҷ���MV_E_CALLORDER
 
 *  @~english
 *  @brief  get time interval between same resend requests
 *  @param  handle                      [IN]            Device handle
 *  @param  pnMillisec                  [IN][OUT]       The time interval between same resend requests
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface MUST be called after enabling resending lost packets by calling MV_GIGE_SetResend,
 *           otherwise would fail and return MV_E_CALLORDER. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall  MV_GIGE_GetResendTimeInterval(IN void* handle, IN OUT unsigned int* pnMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ô���ģʽ������Ϊ����ģʽ���鲥ģʽ��
 *  @param  handle                      [IN]            �豸���
 *  @param  stTransmissionType          [IN]            ����ģʽ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ͨ���ýӿڿ������ô���ģʽΪ�������鲥��ģʽ����GigEVision�豸֧�֡�

 *  @~english
 *  @brief  Set transmission type,Unicast or Multicast
 *  @param  handle                      [IN]            Device handle
 *  @param  stTransmissionType          [IN]            Struct of transmission type
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Call this API to set the transmission mode as single cast mode and multicast mode. And this API is only valid for GigEVision camera. 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_SetTransmissionType(IN void* handle, IN MV_TRANSMISSION_TYPE * pstTransmissionType);

/********************************************************************//**
 *  @~chinese
 *  @brief   ������������
 *  @param   pstActionCmdInfo           [IN]            ����������Ϣ
 *  @param   pstActionCmdResults        [IN][OUT]       �����������Ϣ�б�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ��GigEVision�豸֧�֡�

 *  @~english
 *  @brief  Issue Action Command
 *  @param   pstActionCmdInfo           [IN]            Action Command
 *  @param   pstActionCmdResults        [IN][OUT]       Action Command Result List
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API is supported only by GigEVision camera.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_IssueActionCommand(IN MV_ACTION_CMD_INFO* pstActionCmdInfo, IN OUT MV_ACTION_CMD_RESULT_LIST* pstActionCmdResults);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�鲥״̬
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��
 *  @param  pbStatus                    [IN][OUT]       �鲥״̬,true:�鲥״̬��false:���鲥
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ������ж��豸��ǰ�Ƿ����鲥״̬������ͻ���ö��ʱ��Ҫ���豸�ж��鲥�����⡣
             ��֧�ֱ�׼GigE Vision ��MV_GIGE_DEVICE���豸��

 *  @~english
 *  @brief  Get Multicast Status
 *  @param  pstDevInfo                  [IN]            Device Information Structure
 *  @param  pbStatus                    [IN][OUT]       Status of Multicast
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to determine whether the camera is currently in multicast state, 
             and to solve the problem that the client needs to turn on the camera to determine multicast when enumerating.
			 This API only support GigE Vision ��MV_GIGE_DEVICE�� Device.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_GIGE_GetMulticastStatus(IN MV_CC_DEVICE_INFO* pstDevInfo, IN OUT bool* pbStatus);


/*******************Part6 ch: ��CameraLink �豸֧�ֵĽӿ� | en: Only support camlink device interface*******************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ������Ϣ�б�
 *  @param  pstSerialPortList           [IN][OUT]       ������Ϣ�б�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ����ڻ�ȡ���صĴ�����Ϣ���ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief  Get serial port information list
 *  @param  pstSerialPortList           [IN][OUT]       serial port information list
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to get local serial port information. This API do not support arm and Linux32 platform.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_GetSerialPortList(IN OUT MV_CAML_SERIAL_PORT_LIST* pstSerialPortList);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ȡָ��ö�ٴ���
 *  @param  pstSerialPortList           [IN][OUT]       ������Ϣ�б�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ���������ö��CameraLink �豸��ָ�����ڡ��ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief  Set the specified enumeration serial port
 *  @param  pstSerialPortList           [IN]       serial port information list
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to set the specified enumeration serial port. This API do not support arm and Linux32 platform.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_SetEnumSerialPorts(IN MV_CAML_SERIAL_PORT_LIST* pstSerialPortList);

/***********************************************************************************************************//**
 *  @~chinese
 *  @brief  �����豸������
 *  @param  handle                      [IN]            �豸���
 *  @param  nBaudrate                   [IN]            ���õĲ�����ֵ����ֵ�ο�CameraParams.h�к궨�壬��#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ�֧�����豸δ����ʱ����. ͨ��GenTLЭ������豸ʱ����Ҫ�������豸�����ܵ��øýӿ�
             ��Ӳ��/ϵͳ/�ⲿ���ŵ�����,���ø߲����ʿ��ܵ���ͨ���쳣���������ò��������С��115200
             �ýӿڲ�֧��arm��Linux32ƽ̨
 
 *  @~english
 *  @brief  Set device baudrate using one of the CL_BAUDRATE_XXXX value   
 *  @param  handle                      [IN]            Device handle
 *  @param  nBaudrate                   [IN]            baud rate to set. Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This API is supported only by CameraLink device.
             This API support calls when devices are not connected. But it is necessary to connect to the device first when accessing a CameraLink Device through the GenTL protocol.
             Due to hardware/system/external interference and other factors, configuring a high baud rate may cause abnormal communication. 
             It is recommended to configure a baud rate of less than 115200
             This API do not support arm and Linux32 platform.
************************************************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_SetDeviceBaudrate(IN void* handle, IN unsigned int nBaudrate);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnCurrentBaudrate           [IN][OUT]       ��������Ϣָ�룬��ֵ�ο�CameraParams.h�к궨�壬��#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ�֧�����豸δ����ʱ���á��ýӿڲ�֧��arm��Linux32ƽ̨
 
 *  @~english
 *  @brief  Returns the current device baudrate, using one of the CL_BAUDRATE_XXXX value
 *  @param  handle                      [IN]            Device handle
 *  @param  pnCurrentBaudrate           [IN][OUT]       Return pointer of baud rate to user. Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This API is supported only by CameraLink device.
             This API support calls when devices are not connected.
             This API do not support arm and Linux32 platform.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_GetDeviceBaudrate(IN void* handle,IN OUT unsigned int* pnCurrentBaudrate);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸������������֧�ֵĲ�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pnBaudrateAblity            [IN][OUT]       ֧�ֵĲ�������Ϣ��ָ�롣��֧�ֲ����ʵĻ���������������ֵ�ο�CameraParams.h�к궨�壬��MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ�֧�����豸δ����ʱ���á��ýӿڲ�֧��arm��Linux32ƽ̨
 
 *  @~english
 *  @brief  Returns supported baudrates of the combined device and host interface
 *  @param  handle                      [IN]            Device handle
 *  @param  pnBaudrateAblity            [IN][OUT]       Return pointer of the supported baudrates to user. 'OR' operation results of the supported baudrates. Refer to the 'CameraParams.h' for single value definitions, for example, MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This API is supported only by CameraLink device.
             This API support calls when devices are not connected.
             This API do not support arm and Linux32 platform.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_GetSupportBaudrates(IN void* handle,IN OUT unsigned int* pnBaudrateAblity);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ô��ڲ����ȴ�ʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ���ڲ����ĵȴ�ʱ��, ��λΪms
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿڲ�֧��arm��Linux32ƽ̨

 *  @~english
 *  @brief  Sets the timeout for operations on the serial port
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            Timeout in [ms] for operations on the serial port.
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This API do not support arm and Linux32 platform.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CAML_SetGenCPTimeOut(IN void* handle, IN unsigned int nMillisec);


/*******************Part7 ch: ��U3V�豸֧�ֵĽӿ� | en: Only support U3V device interface*******************/

/********************************************************************//**
 *  @~chinese
 *  @brief  ����U3V�Ĵ������С
 *  @param  handle                      [IN]            �豸���
 *  @param  nTransferSize               [IN]            ����İ���С, Byte��Ĭ��Ϊ1M��rang��>=0x400���������ֵ��[windows] rang <= 0x400000��[Linux] rang <= 0x200000
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ���Ӵ������С�����ʵ�����ȡ��ʱ��CPUռ���ʡ�����ͬ��PC�Ͳ�ͬUSB��չ�����ڲ�ͬ�ļ����ԣ�����ò������ù�����ܻ����ȡ����ͼ��ķ��ա�
 
 *  @~english
 *  @brief  Set transfer size of U3V device
 *  @param  handle                      [IN]            Device handle
 *  @param  nTransferSize               [IN]            Transfer size��Byte��default��1M��rang��>=0x400��Recommended maximum: [windows] rang <= 0x400000; [Linux] rang <= 0x200000
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Increasing the transmission packet size can reduce the CPU utilization at the time of fetching. However, different PCS and different USB extension CARDS have different compatibility, and if this parameter is set too large, there may be the risk of not getting the image.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_USB_SetTransferSize(IN void* handle, IN unsigned int nTransferSize);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡU3V�Ĵ������С
 *  @param  handle                      [IN]            �豸���
 *  @param  pnTransferSize              [IN][OUT]           ����İ���Сָ��, Byte
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��U3V�������С��Ĭ��1M��
 
 *  @~english
 *  @brief  Get transfer size of U3V device
 *  @param  handle                      [IN]            Device handle
 *  @param  pnTransferSize              [IN][OUT]           Transfer size��Byte
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This interface is used to get the current U3V transfer packet size, default 1M.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_USB_GetTransferSize(IN void* handle, IN OUT unsigned int* pnTransferSize);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����U3V�Ĵ���ͨ������
 *  @param  handle                      [IN]            �豸���
 *  @param  nTransferWays               [IN]            ����ͨ����������Χ��1-10
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �û����Ը���PC�����ܡ��豸��ͼ֡�ʡ�ͼ���С���ڴ�ʹ���ʵ����ضԸò������е��ڡ�����ͬ��PC�Ͳ�ͬ��USB��չ�����ڲ�ͬ�ļ����ԡ�
 
 *  @~english
 *  @brief  Set transfer ways of U3V device
 *  @param  handle                      [IN]            Device handle
 *  @param  nTransferWays               [IN]            Transfer ways��rang��1-10
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Users can adjust this parameter according to PC performance, camera image frame rate, image size, memory utilization and other factors. But different PCS and different USB expansion CARDS have different compatibility.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_USB_SetTransferWays(IN void* handle, IN unsigned int nTransferWays);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡU3V�Ĵ���ͨ������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnTransferWays              [IN][OUT]       ����ͨ������ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��U3V�첽ȡ���ڵ������U���������ͨ�����������ظ�ʽ��Ӧ�ĸ��ذ���С��أ�ͨ������첽ע�᳤�� / ���ظ�ʽ��Ӧ�ĸ��ذ���С ����ó���
 
 *  @~english
 *  @brief  Get transfer ways of U3V device
 *  @param  handle                      [IN]            Device handle
 *  @param  pnTransferWays              [IN][OUT]       Transfer ways
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This interface is used to get the current number of U3V asynchronous feed nodes.
	For U3V camera, The number of transmission channels is related to the size of the payload size corresponding to the pixel format, which is calculated by the maximum asynchronous registration length / the payload size corresponding to pixel format.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_USB_GetTransferWays(IN void* handle, IN OUT unsigned int* pnTransferWays);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע�����쳣��Ϣ�ص����ڴ��豸֮����ã�ֻ֧��U3V�������֧��GenTL�豸��
 *  @param  handle                      [IN]            �豸���
 *  @param  cbException                 [IN]            �쳣�ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 
 *  @~english
 *  @brief  Register exception stream callBack, call after open device (only support U3V Camera, don't support GenTL Device)
 *  @param  handle                      [IN]            Device handle
 *  @param  cbException                 [IN]            Exception callback function pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code 
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_USB_RegisterStreamExceptionCallBack(IN void* handle, IN void(__stdcall* cbException)(MV_CC_STREAM_EXCEPTION_TYPE enExceptionType, void* pUser), IN void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����U3V���¼�����ڵ����
 *  @param  handle                      [IN]            �豸���
 *  @param  nEventNodeNum               [IN]            �¼�����ڵ��������Χ��1-64
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ��������õ�ǰ��U3V�¼�����ڵ������Ĭ�������Ϊ5����
 
 *  @~english
 *  @brief  Set the number of U3V device event cache nodes
 *  @param  handle                      [IN]            Device handle
 *  @param  nEventNodeNum               [IN]            Event Node Number
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This interface is used to set the current number of U3V event nodes. default to 5 nodes.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_USB_SetEventNodeNum(IN void* handle, IN unsigned int nEventNodeNum);


/********************************************************************//**
 *  @~chinese
 *  @brief  ����U3V��ͬ����д��ʱʱ�䣬��ΧΪ:[1000, UINT_MAX)
 *  @param  handle                      [IN]            �豸���
 *  @param  nMills                      [IN]            ����ͬ����д��ʱʱ��,Ĭ��ʱ��Ϊ1000ms
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ��������ͬ����ȡʱ��ӿڣ����ݲ���������ò�������������1000ms�����

 *  @~english
 *  @brief  Set U3V Synchronisation timeout,range:[1000, UINT_MAX)
 *  @param  handle               [IN]            Device handle
 *  @param  nMills               [IN]            set synchronisation timeout(ms),default 1000ms
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Increasing the SetSyncTimeOut can compatible with some camera configuretion parameters very slow,more than 1000ms 
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_USB_SetSyncTimeOut(IN void* handle, IN unsigned int nMills);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡU3V���ͬ����д��ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  pnMills                     [IN][OUT]       ��ȡ�ĳ�ʱʱ��(ms)
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��U3Vͬ����д��ʱʱ���С��Ĭ��1000ms��
 
 *  @~english
 *  @brief  Get U3V Camera Synchronisation timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  pnMills                     [IN][OUT]       Get Synchronisation time(ms)
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This interface is used to get the current U3V timeout, default 1000ms.
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_USB_GetSyncTimeOut(IN void* handle, IN OUT unsigned int* pnMills);



/*******************Part8 ch: GenTL��ؽӿ� | en: GenTL related interface*******************/

/******************************************************************************//**
 *  @~chinese
 *  @brief  ͨ��GenTLö��Interfaces
 *  @param  pstIFList                   [IN][OUT]       Interfaces�б�
 *  @param  strGenTLPath                [IN]            GenTL��cti�ļ�·��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks Interfaces�б����ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź�����
             ���龡��������߳�ö�ٲ�����
             �ݲ�֧�ֹ�ҵ���SDKֱ�ӵ���MvProducerU3V.cti��MvProducerGEV.cti�� ֧�ֵ�������.cti
             
 *  @~english
 *  @brief  Enumerate Interfaces with GenTL
 *  @param  pstIFList                   [IN][OUT]       Interfaces List
 *  @param  strGenTLPath                [IN]            GenTL cti file path
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks The memory of the Interfaces list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied.\n
             It is recommended to avoid multithreaded enumeration operations as much as possible.
             Currently not supported for SDK to directly call MvProducerU3V. cti and MvProducerGEV. cti. supports calling other. cti
 *******************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumInterfacesByGenTL(IN OUT MV_GENTL_IF_INFO_LIST* pstIFList, IN const char * strGenTLPath);

/********************************************************************//**
 *  @~chinese
 *  @brief  ж��cti��
 *  @param  pGenTLPath                [IN]            ö�ٿ�ʱ���ص�cti�ļ�·��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ж��ǰ��Ҫ��֤ͨ����ctiö�ٳ��������ȫ���رգ����򱨴�ǰ����������
 
 *  @~english
 *  @brief  Unload cti library
 *  @param  pGenTLPath                [IN]            GenTL cti file path
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Make sure that all devices enumerated by this cti are already closed.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_UnloadGenTLLibrary(IN const char * pGenTLPath);

/*****************************************************************************************************//**
 *  @~chinese
 *  @brief  ͨ��GenTL Interfaceö���豸
 *  @param  pstIFInfo                   [IN]            Interface��Ϣ
 *  @param  pstDevList                  [IN][OUT]           �豸�б�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �豸�б����ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź�����
             ���龡��������߳�ö�ٲ�����
 
 *  @~english
 *  @brief  Enumerate Devices with GenTL interface
 *  @param  pstIFInfo                   [IN]            Interface information
 *  @param  pstDevList                  [IN][OUT]           Device List
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks The memory of the list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied.\n
             It is recommended to avoid multithreaded enumeration operations as much as possible.
 *****************************************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_EnumDevicesByGenTL(IN MV_GENTL_IF_INFO* pstIFInfo, IN OUT MV_GENTL_DEV_INFO_LIST* pstDevList);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͨ��GenTL�豸��Ϣ�����豸���
 *  @param  handle                      [IN][OUT]       �豸���
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��ָ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����������豸��Ϣ���������ڲ��������Դ�ͳ�ʼ���ڲ�ģ�顣
 
 *  @~english
 *  @brief  Create Device Handle with GenTL Device Info
 *  @param  handle                      [IN][OUT]       Device handle
 *  @param  pstDevInfo                  [IN]            Device Information
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Create required resources within library and initialize internal module according to input device information.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_CreateHandleByGenTL(IN OUT void ** handle, IN const MV_GENTL_DEV_INFO* pstDevInfo);



/*******************Part9 ch: ͼ�񱣴桢��ʽת������ؽӿ� | en: Related image save and format convert interface*******************/

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͼƬ��֧��Bmp��Jpeg.
 *  @param  handle                      [IN]            �豸���
 *  @param  pstSaveParam                [IN][OUT]       ����ͼƬ�����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ͨ���ýӿڿ��Խ����豸�ɼ�����ԭʼͼ������ת����JPEG����BMP�ȸ�ʽ�������ָ���ڴ��У�Ȼ���û����Խ�ת��֮�������ֱ�ӱ����ͼƬ�ļ���
             �ýӿڵ����޽ӿ�˳��Ҫ����ͼ��Դ���ݾͿ��Խ���ת���������ȵ���MV_CC_GetOneFrameTimeout����MV_CC_RegisterImageCallBackEx���ûص���������ȡһ֡ͼ�����ݣ�Ȼ����ͨ���ýӿ�ת����ʽ��
             �ýӿ�֧��ͼ�� �����ߡ��ܳ������ UINT_MAX, ����MV_CC_SaveImageEx2֧�� �����ߡ��ܳ������ USHRT_MAX
			 JPEG��ʽ���֧�ֿ���Ϊ65500
 
 *  @~english
 *  @brief  Save image, support Bmp and Jpeg.
 *  @param  handle                      [IN]            Device handle
 *  @param  pstSaveParam                [IN][OUT]       Save image parameters structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Once there is image data, you can call this API to convert the data.
             You can also call MV_CC_GetOneFrameTimeout or MV_CC_RegisterImageCallBackEx or MV_CC_GetImageBuffer to get one image frame and set the callback function, and then call this API to convert the format.
             Comparing with the API MV_CC_SaveImageEx2, this API support the parameter nWidth/nHeight/nDataLen to UINT_MAX. 
			 JPEG format supports a maximum width and height of 65500
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SaveImageEx3(IN void* handle, IN OUT MV_SAVE_IMAGE_PARAM_EX3* pstSaveParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͼ���ļ�
 *  @param  handle                      [IN]            �豸���
 *  @param  pstSaveFileParam            [IN][OUT]       ����ͼƬ�ļ������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�֧��BMP/JPEG/PNG/TIFF��
             �ýӿ�֧��ͼ�� �����ߡ��ܳ������ UINT_MAX, ����MV_CC_SaveImageToFile֧�� �����ߡ��ܳ������ USHRT_MAX
             �ýӿ���MV_CC_SaveImageToFile�ӿڵ���չ�ӿ�
			 JPEG��ʽ���֧�ֿ���Ϊ65500
 *  @~english
 *  @brief  Save the image file.
 *  @param  handle                      [IN]            Device handle
 *  @param  pstSaveFileParam            [IN][OUT]       Save the image file parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API support BMP/JPEG/PNG/TIFF.
             Comparing with the API MV_CC_SaveImageToFile, this API support the parameter nWidth/nHeight/nDataLen to UINT_MAX. 
			 JPEG format supports a maximum width and height of 65500
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SaveImageToFileEx(IN void* handle, IN OUT MV_SAVE_IMAGE_TO_FILE_PARAM_EX* pstSaveFileParam);


/********************************************************************//**
 *  @~chinese
 *  @brief  ����3D�������ݣ�֧��PLY��CSV��OBJ���ָ�ʽ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstPointDataParam           [IN][OUT]       ����������ݲ����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks 3D���ݸ�ʽ�����3D�ļ���ʽ��֧��PLY/CSV/OBJ��
             Ŀǰ֧��PixelType_Gvsp_Coord3D_ABC32��PixelType_Gvsp_Coord3D_ABC32f��PixelType_Gvsp_Coord3D_AB32��PixelType_Gvsp_Coord3D_AB32f��PixelType_Gvsp_Coord3D_AC32��PixelType_Gvsp_Coord3D_AC32f,
             �ݲ�֧������3D��ʽ��
 
 *  @~english
 *  @brief  Save 3D point data, support PLY��CSV and OBJ
 *  @param  handle                      [IN]            Device handle
 *  @param  pstPointDataParam           [IN][OUT]       Save 3D point data parameters structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Save the 3D data format to 3D file format��support PLY��CSV and OBJ,
             only support PixelType_Gvsp_Coord3D_ABC32��PixelType_Gvsp_Coord3D_ABC32f��PixelType_Gvsp_Coord3D_AB32��PixelType_Gvsp_Coord3D_AB32f��PixelType_Gvsp_Coord3D_AC32��PixelType_Gvsp_Coord3D_AC32f
             Other 3D format is not supported now.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SavePointCloudData(IN void* handle, IN OUT MV_SAVE_POINT_CLOUD_PARAM* pstPointDataParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͼ����ת
 *  @param  handle                      [IN]            �豸���
 *  @param  pstRotateParam              [IN][OUT]       ͼ����ת�����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�ֻ֧��MONO8/RGB24/BGR24��ʽ���ݵ�90/180/270����ת��
 
 *  @~english
 *  @brief  Rotate Image
 *  @param  handle                      [IN]            Device handle
 *  @param  pstRotateParam              [IN][OUT]       Rotate image parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API only support 90/180/270 rotation of data in the MONO8/RGB24/BGR24 format.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RotateImage(IN void* handle, IN OUT MV_CC_ROTATE_IMAGE_PARAM* pstRotateParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͼ��ת
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFlipParam                [IN][OUT]       ͼ��ת�����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�ֻ֧��MONO8/RGB24/BGR24��ʽ���ݵĴ�ֱ��ˮƽ��ת��
 
 *  @~english
 *  @brief  Flip Image
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFlipParam                [IN][OUT]       Flip image parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API only support vertical and horizontal reverse of data in the MONO8/RGB24/BGR24 format.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FlipImage(IN void* handle, IN OUT MV_CC_FLIP_IMAGE_PARAM* pstFlipParam);


/********************************************************************//**
 *  @~chinese
 *  @brief  ���ظ�ʽת��
 *  @param  handle                      [IN]            �豸���
 *  @param  pstCvtParam                 [IN][OUT]       ���ظ�ʽת�������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ͨ�����ӿڿ��Խ����豸�ɼ�����ԭʼͼ������ת�����û���������ظ�ʽ�������ָ���ڴ��С�
             �ýӿڵ����޽ӿ�˳��Ҫ����ͼ��Դ���ݾͿ��Խ���ת���������ȵ���MV_CC_GetOneFrameTimeout����MV_CC_RegisterImageCallBackEx���ûص�������
             ��ȡһ֡ͼ�����ݣ�Ȼ����ͨ���ýӿ�ת����ʽ������豸��ǰ�ɼ�ͼ����JPEGѹ���ĸ�ʽ����֧�ֵ��øýӿڽ���ת����
             �ýӿ�֧��ͼ�� �����ߡ��ܳ������ UINT_MAX, ����MV_CC_ConvertPixelType֧�� �����ߡ��ܳ������ USHRT_MAX
 
 *  @~english
 *  @brief  Pixel format conversion
 *  @param  handle                      [IN]            Device handle
 *  @param  pstCvtParam                 [IN][OUT]       Convert Pixel Type parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API is used to transform the collected original data to pixel format and save to specified memory. 
             There is no order requirement to call this API, the transformation will execute when there is image data. 
             First call MV_CC_GetOneFrameTimeout or MV_CC_RegisterImageCallBackEx to set callback function, and get a frame of image data,
             then call this API to transform the format.
             Comparing with the API MV_CC_ConvertPixelType, this API support the parameter nWidth/nHeight/nSrcDataLen to UINT_MAX. 

 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_ConvertPixelTypeEx(IN void* handle, IN OUT MV_CC_PIXEL_CONVERT_PARAM_EX* pstCvtParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ò�ֵ�㷨����
 *  @param  handle                      [IN]            �豸���
 *  @param  nBayerCvtQuality            [IN]            Bayer�Ĳ�ֵ����  0-���� 1-���⣨Ĭ��Ϊ���⣩ 2-���� 3-����+
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �����ڲ�ͼ��ת���ӿڵ�Bayer��ֵ�㷨���Ͳ�����MV_CC_ConvertPixelTypeEx��MV_CC_GetImageForRGB/BGR�ӿ��ڲ�ʹ�õĲ�ֵ�㷨�Ǹýӿ����趨�ġ�

 *  @~english
 *  @brief  Interpolation algorithm type setting
 *  @param  handle                      [IN]            Device handle
 *  @param  nBayerCvtQuality            [IN]            Bayer interpolation method  0-Fast 1-Equilibrium 2-Optimal
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Set the bell interpolation quality parameters of the internal image conversion interface, 
             and the interpolation algorithm used in the MV_CC_ConvertPixelTypeEx and MV_CC_GetImageForRGB/BGR interfaces is set by this interface.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBayerCvtQuality(IN void* handle, IN unsigned int nBayerCvtQuality);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ֵ�㷨ƽ��ʹ������
 *  @param  handle                      [IN]            �豸���
 *  @param  bFilterEnable               [IN]            ƽ��ʹ��(Ĭ�Ϲر�)
 *  @return �ɹ�������#MV_OK�����󣬷��ش����� 
 *  @remarks �����ڲ�ͼ��ת���ӿڵı�����ֵƽ��ʹ�ܲ�����MV_CC_ConvertPixelTypeEx��MV_CC_SaveImageEx3�ӿ��ڲ�ʹ�õĲ�ֵ�㷨�Ǹýӿ����趨�ġ�

 *  @~english
 *  @brief  Filter type of the bell interpolation quality algorithm setting
 *  @param  handle                      [IN]            Device handle
 *  @param  bFilterEnable               [IN]            Filter type enable
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Set the bell interpolation filter type parameters of the internal image conversion interface, 
             and the interpolation algorithm used in the MV_CC_ConvertPixelTypeEx and MV_CC_SaveImageEx3 interfaces is set by this interface.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBayerFilterEnable(IN void* handle, IN bool bFilterEnable);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��Gammaֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  fBayerGammaValue            [IN]            Gammaֵ:0.1 ~ 4.0
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ���ø�ֵ���ڵ���MV_CC_ConvertPixelTypeEx��MV_CC_SaveImageEx3��MV_CC_SaveImageToFileEx�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱ��Ч��

 *  @~english
 *  @brief  Set Gamma value
 *  @param  handle                      [IN]            Device handle
 *  @param  fBayerGammaValue            [IN]            Gamma value[0.1,4.0]
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After setting the value, it works when calling MV_CC_ConvertPixelTypeEx\MV_CC_SaveImageEx3\MV_CC_SaveImageToFileEx API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBayerGammaValue(IN void* handle, IN float fBayerGammaValue);

/********************************************************************//**
 *  @~chinese
 *  @brief   ����Mono8/Bayer8/10/12/16��ʽ��Gammaֵ
 *  @param   handle                           [IN] �豸���
 *  @param   MvGvspPixelType enSrcPixelType   [IN] ���ظ�ʽ,֧��PixelType_Gvsp_Mono8,Bayer8/10/12/16
 *  @param   fGammaValue                      [IN] Gammaֵ:0.1 ~ 4.0
 *  @return  �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����Mono8��gammaֵ���ڵ���MV_CC_ConvertPixelTypeEx�ӿڽ�Mono8ת��Mono8ʱgammaֵ��Ч��
 *  @remarks ����Bayer8/10/12/16��gammaֵ���ڵ���MV_CC_ConvertPixelTypeEx��MV_CC_SaveImageToFileEx��MV_CC_SaveImageEx3�ӿڽ�Bayer8/10/12/16תRGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱgammaֵ��Ч��
 *  @remarks �ýӿڼ���MV_CC_SetBayerGammaValue�ӿڣ�����֧��Mono8���ظ�ʽ
 
 *  @~english
 *  @brief  Set Gamma value
 *  @param  handle                           [IN]            Device handle
 *  @param  MvGvspPixelType enSrcPixelType   [IN]            PixelType,support PixelType_Gvsp_Mono8,Bayer8/10/12/16
 *  @param  fGammaValue                      [IN]            Gamma value:0.1~ 4.0
 *  @remarks After setting the gamma of Mono8 ��the gamma value takes effect when calling MV_CC_ConvertPixelTypeEx converts Mono8 to Mono8.
 *  @remarks After setting the gamma of Bayer8/10/12/16, the gamma value takes effect when calling MV_CC_ConvertPixelTypeEx\MV_CC_SaveImageToFileEx\MV_CC_SaveImageEx3 converts Bayer8/10/12/16 to RGB24/48,RGBA32/64,BGR24/48,BGRA32/64.
 *  @remarks This API compatible with MV_CC_SetBayerGammaValue, adds Mono8 PixelType.
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetGammaValue(IN void* handle, IN enum MvGvspPixelType enSrcPixelType, IN float fGammaValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��Gamma��Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstGammaParam               [IN]            Gamma��Ϣ   
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ���ø���Ϣ���ڵ���MV_CC_ConvertPixelTypeEx��MV_CC_SaveImageEx3��MV_CC_SaveImageToFileEx�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱGammaֵ��Ч��

 *  @~english
 *  @brief  Set Gamma param
 *  @param  handle                      [IN]            Device handle
 *  @param  pstGammaParam               [IN]            Gamma param
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After setting the param, it work in the calling MV_CC_ConvertPixelTypeEx\MV_CC_SaveImageEx3\MV_CC_SaveImageToFileEx API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBayerGammaParam(IN void* handle, IN MV_CC_GAMMA_PARAM* pstGammaParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��CCMʹ�ܺ;�������ϵ��Ĭ��1024
 *  @param  handle                      [IN]            �豸���
 *  @param  pstCCMParam                 [IN]            CCM����
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����CCM������CCM������ڵ���MV_CC_ConvertPixelTypeEx��MV_CC_SaveImageEx3�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱ��Ч�� 

 *  @~english
 *  @brief  Set CCM param,Scale default 1024
 *  @param  handle                      [IN]            Device handle
 *  @param  pstCCMParam                 [IN]            CCM parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After enable the color correction and set the color correction matrix, It work in the calling MV_CC_ConvertPixelTypeEx\MV_CC_SaveImageEx3 API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBayerCCMParam(IN void* handle, IN MV_CC_CCM_PARAM* pstCCMParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��CCMʹ�ܺ;���
 *  @param  handle                      [IN]            �豸���
 *  @param  pstCCMParam                 [IN]            CCM����
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����CCM������CCM������ڵ���MV_CC_ConvertPixelTypeEx��MV_CC_SaveImageEx3�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱ��Ч��

 *  @~english
 *  @brief  Set CCM param
 *  @param  handle                      [IN]            Device handle
 *  @param  pstCCMParam                 [IN]            CCM parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After enable the color correction and set the color correction matrix, It work in the calling MV_CC_ConvertPixelTypeEx\MV_CC_SaveImageEx3 API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_SetBayerCCMParamEx(IN void* handle, IN MV_CC_CCM_PARAM_EX* pstCCMParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͼ��Աȶȵ���
 *  @param  handle                      [IN]            �豸���
 *  @param  pstContrastParam            [IN][OUT]       �Աȶȵ��ڲ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks 

 *  @~english
 *  @brief  Adjust image contrast
 *  @param  handle                      [IN]            Device handle
 *  @param  pstContrastParam            [IN][OUT]       Contrast parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks 
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_ImageContrast(IN void* handle, IN OUT MV_CC_CONTRAST_PARAM* pstContrastParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  �������
 *  @param  handle                      [IN]            �豸���
 *  @param  pstDecodeParam              [IN][OUT]       �����������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ���������ȡ��������ѹ����������������ݣ�ͬʱ֧�ֽ�����ǰ���ʵʱͼ���ˮӡ��Ϣ���������������������ǵ�ǰ������߲���ʵʱȡ���ģ���ˮӡ���������쳣��;
			 ������ʧ�ܣ����������������1����ҪCPU֧�� SSE AVXָ���2������ǰ֡�쳣�������ȣ�,���ܵ��½����쳣��3�������ͼ�쳣�� ��ʹ������Ҳ���쳣

 *  @~english
 *  @brief  High Bandwidth Decode
 *  @param  handle                      [IN]            Device handle
 *  @param  pstDecodeParam              [IN][OUT]       High Bandwidth Decode parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Decode the lossless compressed data from the camera into raw data��At the same time, it supports parsing the watermark information of the real-time image of the current camera (if the input lossless code stream is not the current camera or is not real-time streaming, the watermark parsing may be abnormal);
			 If decoding fails, please check the following: (1) The CPU is required to support the SSE AVX instruction set. (2) If the current frame is abnormal (packet loss, etc.), it may cause decoding exceptions. (3) The camera plot is abnormal, even if there is no packet loss, it may cause exceptions
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_HB_Decode(IN void* handle, IN OUT MV_CC_HB_DECODE_PARAM* pstDecodeParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ͼ���ϻ��ƾ��ο�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pRectInfo                   [IN]            ���θ����ߵ���Ϣ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks  �ýӿڽ�֧��windowsƽ̨
 
 *  @~english
 *  @brief  Draw Rect Auxiliary Line
 *  @param  handle                      [IN]            Device handle
 *  @param  pRectInfo                   [IN]            Rect Auxiliary Line Info
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface only supports windows platform.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DrawRect(IN void* handle, IN MVCC_RECT_INFO* pRectInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ͼ���ϻ���Բ�θ�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pCircleInfo                 [IN]            Բ�θ����ߵ���Ϣ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks  �ýӿڽ�֧��windowsƽ̨
 
 *  @~english
 *  @brief  Draw Circle Auxiliary Line
 *  @param  handle                      [IN]            Device Handle
 *  @param  pCircleInfo                 [IN]            Circle Auxiliary Line Info
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface only supports windows platform.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DrawCircle(IN void* handle, IN MVCC_CIRCLE_INFO* pCircleInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ͼ���ϻ�������
 *  @param  handle                      [IN]            �豸���
 *  @param  pLinesInfo                  [IN]            ������������Ϣ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks  �ýӿڽ�֧��windowsƽ̨
 
 *  @~english
 *  @brief  Draw Line Auxiliary Line
 *  @param  handle                      [IN]            Device Handle
 *  @param  pLinesInfo                  [IN]            Linear Auxiliary Line Info
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks  This interface only supports windows platform.
 ***********************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_DrawLines(IN void* handle, IN MVCC_LINES_INFO* pLinesInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʼ¼��
 *  @param  handle                      [IN]            �豸���
 *  @param  pstRecordParam              [IN]            ¼������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
			�ýӿ����֧��Width*HeightΪ8000*8000��С������ᵼ�µ���MV_CC_InputOneFrame�ӿڴ���
 
 *  @~english
 *  @brief  Start Record
 *  @param  handle                      [IN]            Device handle
 *  @param  pstRecordParam              [IN]            Record param structure
 *  @return Success, return MV_OK. Failure, return error code
	The maximum supported width * height of this interface is 8000 * 8000, otherwise it will result in calling MV_ CC_ InputOneFrame interface error.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_StartRecord(IN void* handle, IN MV_CC_RECORD_PARAM* pstRecordParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����¼������
 *  @param  handle                      [IN]            �豸���
 *  @param  pstInputFrameInfo           [IN]            ¼�����ݽṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Input RAW data to Record
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInputFrameInfo           [IN]            Record data structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_InputOneFrame(IN void* handle, IN MV_CC_INPUT_FRAME_INFO * pstInputFrameInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ֹͣ¼��
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Stop Record
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_StopRecord(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  �򿪻�ȡ���������������GUI����
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK��ʧ�ܣ����ش����롣
 *  @remarks ͨ��MV_CC_OpenDevice�����豸�󣬿���ͨ���ýӿڻ�ȡ�������豸������
 *  @remarks ���ƣ���ͬһ�߳��ж����ͬʱ���øýӿڣ�ֻ�ܴ򿪵�ǰһ��GUI���棬��Ҫ�رյ�ǰ���GUI����󣬲ſɴ���һ�������GUI���棨�����汾�Ż���
			 �ýӿڽ�֧��windowsƽ̨

 *  @~english
 *  @brief  Open the GUI interface for getting or setting camera parameters
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK, Failure, return error code.
 *  @remarks After connecting to device through MV_CC_OpenDevice, use this interface to get or set device params.
 *  @remarks Limit: calling this interface multiple times in the same thread can only open one GUI interface. 
             You need to wait until the previous GUI interface is closed before opening the next GUI interface.(Subsequent version optimization)
			 This interface only supports windows platform.
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_OpenParamsGUI(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ع�ͼ��(���ڷ�ʱ�ع⹦��)
 *  @param  handle                      [IN]            �豸���
 *  @param  pstReconstructParam         [IN][OUT]       �ع�ͼ�����
 *  @return �ɹ�������MV_OK��ʧ�ܣ����ش����롣
 *  @remarks ͼ��ָ�֧���������ظ�ʽ��ͼ��ָ�Ӧ����������ġ�MultiLightControl���ڵ����ʹ�ã��ýڵ�����ö����ͬ���ع�ֵ����MultiLightControl=2,
             ����Ὣ������ͬ�ع�ֵ����Ӧ������ͼ�񽻵��ϲ�Ϊһ��ͼ��(ʵ�ʸ߶�Ϊ����ͼ��ĸ߶�)���͸��ϲ�Ӧ�ó���
             ���øýӿڲ������ʱ�ع�ֵnExposureNumΪ2���ɽ�������͵�һ��ͼ��ָ�Ϊ2��ͼ��������ͼ��ֱ��Ӧһ���ع�ֵ��
             ��ʹ����ͨ�����δ����������ġ�MultiLightControl���ڵ㣬��ͼ��ָ������壬ֻ�ǽ�ͼ���зָ�Ϊ2��3��4��ͼ��
             ÿ��ͼ��ĸ߶ȱ�Ϊԭͼ���1/2��1/3��1/4(��nExposureNum����)��

 *  @~english
 *  @brief  Reconstruct Image(For time-division exposure function)
 *  @param  handle                      [IN]            Device handle
 *  @param  pstReconstructParam         [IN][OUT]       Reconstruct image parameters
 *  @return Success, return MV_OK, Failure, return error code.
 *  @remarks Image segmentation supports any pixel format. Image segmentation should be used with the "MultiLightControl" node of the linear array camera. This node can set multiple different exposure values, such as MultiLightControl=2, 
             The camera will overlap and merge two images corresponding to two different exposure values into one image (the actual height is the height of the two images) and send it to the upper application. 
             Call the interface and pass in nExposureNum is two. One image sent by the camera can be divided into two images, each of which corresponds to an exposure value. 
             If an ordinary camera is used or the "MultiLightControl" node of the linear array camera is not turned on, the image segmentation is meaningless, but the image is divided into 2, 3, and 4 images by line. 
             The height of each image becomes 1/2, 1/3, 1/4 of the original image (determined by nExposureNum).
 ************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_ReconstructImage(IN void* handle, IN OUT MV_RECONSTRUCT_IMAGE_PARAM* pstReconstructParam);



/********************************************************************//**
*  @~chinese
*  @brief  ��������ڴ�
*  @param  nBufLen                      [IN]            �����ڴ�ĳ���
*  @param  nAlignment                   [IN]            �ڴ�����ֽ��� (�����Ǵ���0��������2����������)
*  @return �ɹ������������ڴ��ַ��ʧ�ܣ����� NULL
*  @remarks 

*  @~english
*  @brief  
*  @param  nBufLen                      [IN]        memory bytes     
*  @param  nAlignment                   [IN]        memory aligned bytes (Must be an integer power of 2 greater than 0)
*  @return Success, return memory address, Failure, return NULL.
*  @remarks 
************************************************************************/
MV_CAMCTRL_API void *  __stdcall MV_CC_AllocAlignedBuffer(IN uint64_t  nBufSize, IN unsigned int nAlignment);

/********************************************************************//**
*  @~chinese
*  @brief  �����ڴ��ͷ�
*  @param  pBuffer                      [IN]            �ڴ��ַ
*  @return �ɹ�������MV_OK��ʧ�ܣ����ش����롣
*  @remarks �����ڴ���ͷţ�����MV_CC_AllocAlignedBufferʹ��

*  @~english 
*  @brief   release aligned memory
*  @param  pBuffer                      [IN]        memory address
*  @return Success, return MV_OK, Failure, return error code.
*  @remarks
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_FreeAlignedBuffer(IN void* pBuffer);

/********************************************************************//**
*  @~chinese
*  @brief  ��ȡ�豸palyload��С��payload����ͼ�����ݺ�Chunk���ݣ����ڴ���䷽ʽ������SDK�ⲿע�Ỻ��ʱ��Ӧ�ò�����㹻�Ļ��漰��ȷ���ڴ���뷽ʽ
*  @param  handle                      [IN]            �豸���
*  @param  pnPayloadSize               [IN OUT]        ���س���
*  @param  pnAlignment                 [IN OUT]        �����ڴ������ֽ���
*  @return �ɹ�������MV_OK��ʧ�ܣ����ش����롣
*  @remarks

*  @~english
*  @brief  Obtain the device payload size (payload includes image data and Chunk data) and memory alignment method, 
    which is used by the application layer to allocate sufficient cache and correct memory alignment when registering external cache for SDK
*  @param  handle                      [IN]            Device Handle
*  @param  pnPayloadSize               [IN OUT]        Payload size
*  @param  pnAlignment                 [IN OUT]        Alignment bytes
*  @return Success, return MV_OK, Failure, return error code.
*  @remarks
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_GetPayloadSize(IN void* handle, IN OUT uint64_t* pnPayloadSize, IN OUT unsigned int* pnAlignment);

/********************************************************************//**
*  @~chinese
*  @brief  Ӧ�ó�����仺�棬��ע�ᵽSDK�ڲ�����SDKʹ��
*  @param  handle                      [IN]            �豸���
*  @param  pBuffer                     [IN]            �ڴ��ַ
*  @param  nBufSize                    [IN]            �ڴ泤��
*  @return �ɹ�������MV_OK��ʧ�ܣ����ش����롣
*  @remarks ����ʹ�� MV_CC_GetPayloadSize ��ȡ�����С����ʹ�� MV_CC_AllocAlignedBuffer ����ռ䣬֮�����MV_CC_RegisterBufferע��
            startǰ����,Ҫ�����3�����ϣ�������ע��3���ڴ浽SDK�У� ��U��/���������ʹ�ò���ע���ڴ�ڵ���Ϊ���棬����MV_CC_GetValidImageNum С��ʵ��ע���ⲿ�ڴ������
            ע��Ļ�����Ҫ��Ӧ�ò�֪ͨSDKȡ��ע�ᣨMV_CC_UnRegisterBuffer���󣬽����ͷţ�MV_CC_FreeAlignedBuffer��
            ʹ�øýӿں󣬽���֧��MV_CC_GetImageBuffer/MV_CC_FreeImageBuffer MV_CC_RegisterImageCallBackEx ��ȡͼ�񣬲�֧�������ӿڻ�ȡͼ��
            ʹ�øýӿں����֮ǰ������SDK�ڲ��ڵ㣨MV_CC_SetImageNodeNum����Ч
*  @~english
*  @brief  The application allocates memory and registers it within the SDK for use by the SDK
*  @param  handle                      [IN]            Device Handle
*  @param  pBuffer                     [IN]            external memory address
*  @param  nBufSize                    [IN]            external memory len 
*  @return Success, return MV_OK, Failure, return error code.
*  @remarks Registering memory can be done by using MV_CC_GetPayloadSize to obtain the memory size, and allocating the memory size using MV_CC_AllocAlignedBuffer
            Called before start, call at last 3 times, that is ,register at least 3 blocks of memory or more.(U-port/Ethernet port cameras will use some registered memory nodes as cache, so MV_CC_GetValidImageNum is less than the actual number of registered external memory.)
            The registered memory needs to be notified by the application layer to the SDK to cancel the registration (MV_CC_UnregisterBuffer) and then released (MV_CC_FreeAlignedBuffer)
            After using this interface, only MV_CC_GetImageBuffer��MV_CC_FreeImageBuffer/MV_CC_RegisterImageCallBackEx is supported for image retrieval, and other interfaces are not supported for image retrieval
            After using this interface, if the SDK internal node (MV_CC_SetImageNodeNum) was previously configured, it is invalid
************************************************************************/
MV_CAMCTRL_API int __stdcall MV_CC_RegisterBuffer(IN void* handle, IN void* pBuffer, IN uint64_t nBufSize);

/********************************************************************//**
*  @~chinese
*  @brief  �ⲿ�ڴ�ȡ��SDK�ڲ�ע��
*  @param  handle                      [IN]            �豸���
*  @param  pBuffer                     [IN]            �ⲿ�ڴ��ַ
*  @return �ɹ�������MV_OK��ʧ�ܣ����ش����롣
*  @remarks 

*  @~english
*  @brief   revoke external memory
*  @param  handle                      [IN]            Device Handle
*  @param  pBuffer                     [IN]            external memory address
*  @return Success, return MV_OK, Failure, return error code.
*  @remarks
************************************************************************/
MV_CAMCTRL_API int __stdcall  MV_CC_UnRegisterBuffer(IN void* handle, IN void* pBuffer);

#ifdef __cplusplus
}
#endif 

#endif //_MV_CAMERA_CTRL_H_

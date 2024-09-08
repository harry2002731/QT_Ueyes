
#ifndef _MV_ERROR_DEFINE_H_
#define _MV_ERROR_DEFINE_H_
#include <cstdint>
typedef int64_t int64_t;

#include "MvISPErrorDefine.h"

/********************************************************************/
///  \~chinese
///  \name ��ȷ�붨��
///  @{
///  \~english
///  \name Definition of correct code
///  @{
#define MV_OK                       0x00000000  ///< \~chinese �ɹ����޴���             \~english Successed, no error
/// @}

/********************************************************************/
///  \~chinese
///  \name ͨ�ô����붨��:��Χ0x80000000-0x800000FF
///  @{
///  \~english
///  \name Definition of General error code
///  @{
#define MV_E_HANDLE                 0x80000000  ///< \~chinese �������Ч�ľ��         \~english Error or invalid handle
#define MV_E_SUPPORT                0x80000001  ///< \~chinese ��֧�ֵĹ���             \~english Not supported function
#define MV_E_BUFOVER                0x80000002  ///< \~chinese ��������                 \~english Buffer overflow
#define MV_E_CALLORDER              0x80000003  ///< \~chinese ��������˳�����         \~english Function calling order error
#define MV_E_PARAMETER              0x80000004  ///< \~chinese ����Ĳ���               \~english Incorrect parameter
#define MV_E_RESOURCE               0x80000006  ///< \~chinese ��Դ����ʧ��             \~english Applying resource failed
#define MV_E_NODATA                 0x80000007  ///< \~chinese ������                   \~english No data
#define MV_E_PRECONDITION           0x80000008  ///< \~chinese ǰ���������󣬻����л����ѷ����仯   \~english Precondition error, or running environment changed
#define MV_E_VERSION                0x80000009  ///< \~chinese �汾��ƥ��               \~english Version mismatches
#define MV_E_NOENOUGH_BUF           0x8000000A  ///< \~chinese ������ڴ�ռ䲻��       \~english Insufficient memory
#define MV_E_ABNORMAL_IMAGE         0x8000000B  ///< \~chinese �쳣ͼ�񣬿����Ƕ�������ͼ������   \~english Abnormal image, maybe incomplete image because of lost packet
#define MV_E_LOAD_LIBRARY           0x8000000C  ///< \~chinese ��̬����DLLʧ��          \~english Load library failed
#define MV_E_NOOUTBUF               0x8000000D  ///< \~chinese û�п�����Ļ���         \~english No Avaliable Buffer
#define MV_E_ENCRYPT                0x8000000E  ///< \~chinese ���ܴ���                 \~english Encryption error
#define MV_E_OPENFILE               0x8000000F  ///< \~chinese ���ļ����ִ���         \~english open file error
#define MV_E_BUF_IN_USE             0x80000010  ///< \~chinese �����ַ��ʹ��           \~english Buffer already in use
#define MV_E_BUF_INVALID            0x80000011  ///< \~chinese ��Ч�Ļ����ַ           \~english Buffer address invalid
#define MV_E_NOALIGN_BUF            0x80000012  ///< \~chinese ��������쳣             \~english Buffer alignmenterror error
#define MV_E_NOENOUGH_BUF_NUM       0x80000013  ///< \~chinese �����������             \~english Insufficient cache count
#define MV_E_PORT_IN_USE            0x80000014  ///< \~chinese ���ڱ�ռ��               \~english Port is in use
#define MV_E_IMAGE_DECODEC          0x80000015  ///< \~chinese �������(SDKУ��ͼ���쳣)\~english Decoding error (SDK verification image exception)


#define MV_E_UNKNOW                 0x800000FF  ///< \~chinese δ֪�Ĵ���               \~english Unknown error
/// @}

/********************************************************************/
///  \~chinese
///  \name GenICamϵ�д���:��Χ0x80000100-0x800001FF
///  @{
///  \~english
///  \name GenICam Series Error Codes: Range from 0x80000100 to 0x800001FF
///  @{
#define MV_E_GC_GENERIC             0x80000100  ///< \~chinese ͨ�ô���                 \~english General error
#define MV_E_GC_ARGUMENT            0x80000101  ///< \~chinese �����Ƿ�                 \~english Illegal parameters
#define MV_E_GC_RANGE               0x80000102  ///< \~chinese ֵ������Χ               \~english The value is out of range
#define MV_E_GC_PROPERTY            0x80000103  ///< \~chinese ����                     \~english Property
#define MV_E_GC_RUNTIME             0x80000104  ///< \~chinese ���л���������           \~english Running environment error
#define MV_E_GC_LOGICAL             0x80000105  ///< \~chinese �߼�����                 \~english Logical error
#define MV_E_GC_ACCESS              0x80000106  ///< \~chinese �ڵ������������         \~english Node accessing condition error
#define MV_E_GC_TIMEOUT             0x80000107  ///< \~chinese ��ʱ                     \~english Timeout
#define MV_E_GC_DYNAMICCAST         0x80000108  ///< \~chinese ת���쳣                 \~english Transformation exception
#define MV_E_GC_UNKNOW              0x800001FF  ///< \~chinese GenICamδ֪����          \~english GenICam unknown error
/// @}

/********************************************************************/
///  \~chinese
///  \name GigE_STATUS��Ӧ�Ĵ�����:��Χ0x80000200-0x800002FF
///  @{
///  \~english
///  \name GigE_STATUS Error Codes: Range from 0x80000200 to 0x800002FF
///  @{
#define MV_E_NOT_IMPLEMENTED        0x80000200  ///< \~chinese ������豸֧��         \~english The command is not supported by device
#define MV_E_INVALID_ADDRESS        0x80000201  ///< \~chinese ���ʵ�Ŀ���ַ������     \~english The target address being accessed does not exist
#define MV_E_WRITE_PROTECT          0x80000202  ///< \~chinese Ŀ���ַ����д           \~english The target address is not writable
#define MV_E_ACCESS_DENIED          0x80000203  ///< \~chinese �豸�޷���Ȩ��           \~english No permission
#define MV_E_BUSY                   0x80000204  ///< \~chinese �豸æ��������Ͽ�       \~english Device is busy, or network disconnected
#define MV_E_PACKET                 0x80000205  ///< \~chinese ��������ݴ���           \~english Network data packet error
#define MV_E_NETER                  0x80000206  ///< \~chinese ������ش���             \~english Network error
#define MV_E_KEY_VERIFICATION       0x8000020F  ///< \~chinese ��ԿУ�����              \~english SwitchKey error
#define MV_E_IP_CONFLICT            0x80000221  ///< \~chinese �豸IP��ͻ               \~english Device IP conflict
/// @}

/********************************************************************/
///  \~chinese
///  \name USB_STATUS��Ӧ�Ĵ�����:��Χ0x80000300-0x800003FF
///  @{
///  \~english
///  \name USB_STATUS Error Codes: Range from 0x80000300 to 0x800003FF
///  @{
#define MV_E_USB_READ               0x80000300  ///< \~chinese ��usb����                \~english Reading USB error
#define MV_E_USB_WRITE              0x80000301  ///< \~chinese дusb����                \~english Writing USB error
#define MV_E_USB_DEVICE             0x80000302  ///< \~chinese �豸�쳣                 \~english Device exception
#define MV_E_USB_GENICAM            0x80000303  ///< \~chinese GenICam��ش���          \~english GenICam error
#define MV_E_USB_BANDWIDTH          0x80000304  ///< \~chinese ��������                 \~english Insufficient bandwidth
#define MV_E_USB_DRIVER             0x80000305  ///< \~chinese ������ƥ�����δװ����   \~english Driver mismatch or unmounted drive
#define MV_E_USB_UNKNOW             0x800003FF  ///< \~chinese USBδ֪�Ĵ���            \~english USB unknown error
/// @}

/********************************************************************/
///  \~chinese
///  \name ����ʱ��Ӧ�Ĵ�����:��Χ0x80000400-0x800004FF
///  @{
///  \~english
///  \name Upgrade Error Codes: Range from 0x80000400 to 0x800004FF
///  @{
#define MV_E_UPG_FILE_MISMATCH      0x80000400  ///< \~chinese �����̼���ƥ��           \~english Firmware mismatches
#define MV_E_UPG_LANGUSGE_MISMATCH  0x80000401  ///< \~chinese �����̼����Բ�ƥ��       \~english Firmware language mismatches
#define MV_E_UPG_CONFLICT           0x80000402  ///< \~chinese ������ͻ���豸�Ѿ����������ٴ��������������ش˴��� \~english Upgrading conflicted (repeated upgrading requests during device upgrade)
#define MV_E_UPG_INNER_ERR          0x80000403  ///< \~chinese ����ʱ�豸�ڲ����ִ���   \~english Camera internal error during upgrade
#define MV_E_UPG_UNKNOW             0x800004FF  ///< \~chinese ����ʱδ֪����           \~english Unknown error during upgrade
/// @}

#endif //_MV_ERROR_DEFINE_H_

#include "Hikvision_Lib.h"
#include <string>

#define IMAGE_NAME_LEN 64

using namespace QtHik;
using namespace std;
Hikvision_Lib::Hikvision_Lib()
{
    m_pBufForDriver = nullptr;
    m_pBufForSaveImage  = nullptr;
    m_pCMvCamera = nullptr;
    // m_hwndDisplay = nullptr;

    m_nBufSizeForDriver = 0;
    m_bOpenDevice =false;
    m_bStartGrabbing = false;
    m_nTriggerMode = 0;
    m_nBufSizeForSaveImage = 0;

}
Hikvision_Lib::~Hikvision_Lib()
{
    delete m_pBufForDriver;
    delete m_pBufForSaveImage;
    delete m_pCMvCamera;
}
int Hikvision_Lib::EnumDevices(vector< QString> &QUserNames)
{
    // ch:设备信息列表结构体变量，用来存储设备列表
    // ch:初始化设备信息列表
    memset(&this->m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    unsigned int nTLayerType = 0x00000001;
    int nRet = CMvCamera::EnumDevices(nTLayerType, &this->m_stDevList);
    if(nRet != MV_OK)
    {
        return -1;
    }
    for(size_t i = 0; i < this->m_stDevList.nDeviceNum; i++)
    {
        //设备信息
        MV_CC_DEVICE_INFO *pDeviceInfo = this->m_stDevList.pDeviceInfo[i];
        if(pDeviceInfo == nullptr)
        {
            continue;
        }
        unsigned char *pUserName = pDeviceInfo->SpecialInfo.stGigEInfo.chModelName;
        string pUserName2 = reinterpret_cast<char *>(pUserName);
        QUserNames.push_back( QString::fromStdString(pUserName2) );
    }
    if(this->m_stDevList.nDeviceNum == 0)
    {
        //throw "No device" ;
        return -1;
    }
    return MV_OK;
}

int Hikvision_Lib::OpenDevice(int &nIndex)
{
    if(m_bOpenDevice == true)
        return -1;

    if( (nIndex < 0) || (nIndex >= MV_MAX_DEVICE_NUM))
    {
        //throw "Please select device ";
        return -1;
    }
    if(this->m_stDevList.pDeviceInfo[nIndex] == nullptr)
    {
        //throw "Open Device Failed";
        return -1;
    }

    this->m_pCMvCamera = new CMvCamera;
    if(this->m_pCMvCamera == nullptr)
    {
        //throw "Initailized Failed";
        return -1;
    }
    int nRet = m_pCMvCamera->Open(this->m_stDevList.pDeviceInfo[nIndex]);
    if(nRet != MV_OK)
    {
        delete this->m_pCMvCamera;
        this->m_pCMvCamera = nullptr;
        return nRet;
    }
    m_bOpenDevice = true;
    return MV_OK;
}

int Hikvision_Lib::CloseDevice()
{
    if(m_pCMvCamera != nullptr)
    {
        m_pCMvCamera->Close();
        delete m_pCMvCamera;
        m_pCMvCamera = nullptr;
    }
    m_bOpenDevice = false;
    m_bStartGrabbing = false;
    /*
    if(m_pBufForDriver != nullptr)
    {
        free(m_pBufForDriver);
        //m_pBufForDriver = nullptr;
    }
    //m_nBufSizeForDriver = 0;
    if(m_pBufForSaveImage != nullptr)
    {
        free(m_pBufForSaveImage);
        //m_pBufForSaveImage = nullptr;

    }
    //m_nBufSizeForSaveImage = 0;
    */
    return MV_OK;
}

int Hikvision_Lib::SetTriggerMode(unsigned int trigger_mode)
{
    if(trigger_mode == 0)
        this->m_nTriggerMode = MV_TRIGGER_MODE_OFF;
    else {
        this->m_nTriggerMode = MV_TRIGGER_MODE_ON;
    }
    int nRet = m_pCMvCamera->SetEnumValue("TriggerMode", this->m_nTriggerMode);
    if(nRet != MV_OK)
        return nRet;
    return MV_OK;
}
int Hikvision_Lib::SetExposureTime(float nValue)
{
    m_pCMvCamera->SetEnumValue("ExposureAuto", 0);
    int nRet = m_pCMvCamera->SetFloatValue("ExposureTime", nValue);
    if(nRet != MV_OK)
        return nRet;
    return MV_OK;
}
float Hikvision_Lib::GetExposureTime()
{
    MVCC_FLOATVALUE stFloatValue;
    memset(&stFloatValue, 0, sizeof(MVCC_FLOATVALUE));

    int nRet = m_pCMvCamera->GetFloatValue("ExposureTime", &stFloatValue);
    if(nRet != MV_OK)
        return nRet;
    return stFloatValue.fCurValue;
}

float Hikvision_Lib::GetGainAuto()
{
    MVCC_FLOATVALUE stFloatValue;
    memset(&stFloatValue, 0, sizeof(MVCC_FLOATVALUE));

    int nRet = m_pCMvCamera->GetFloatValue("Gain", &stFloatValue);
    if(nRet != MV_OK)
        return nRet;
    return stFloatValue.fCurValue;
}

float Hikvision_Lib::GetAcquisitionFrameRate()
{
    MVCC_FLOATVALUE stFloatValue;
    memset(&stFloatValue, 0, sizeof(MVCC_FLOATVALUE));

    int nRet = m_pCMvCamera->GetFloatValue("ResultingFrameRate", &stFloatValue);
    if(nRet != MV_OK)
        return nRet;
    return stFloatValue.fCurValue;
}

int Hikvision_Lib::SetGainAuto( float nValue)
{
    m_pCMvCamera->SetEnumValue("GainAuto", 0);
    int nRet = m_pCMvCamera->SetFloatValue("Gain", nValue);
    if(nRet != MV_OK)
        return nRet;
    return MV_OK;
}
int Hikvision_Lib::SetAcquisitionFrameRate(float nValue)
{
    int nRet = m_pCMvCamera->SetFloatValue("AcquisitionFrameRate", nValue);
    if(nRet != MV_OK)
        return nRet;
    return MV_OK;
}


int Hikvision_Lib::StartGrabbing(WId MainWndID)
{
    //开始采集
    if(m_bOpenDevice == false || m_bStartGrabbing == true)
    {
        return -1;
    }
    int nRet = -1;
    if(m_pCMvCamera != nullptr)
    {
        nRet = m_pCMvCamera->StartGrabbing();
        //m_pCMvCamera->m_hDevHandle = MainWndID;
        this->m_hwndDisplay = MainWndID;
        if(nRet == MV_OK)
        {
            nRet = m_pCMvCamera->Display((void*)m_hwndDisplay);
        }
    }
    else {
        return -1;
    }
    if(nRet != MV_OK)
        return -1;
    if(nRet != MV_OK)
    {
        //QMessageBox::information(this,"hint","failed in get payloadsize");
        return -1;
    }
    m_bStartGrabbing = true;
    return nRet;
}

int Hikvision_Lib::StopGrabbing()
{
    if(m_bOpenDevice == false || m_bStartGrabbing == false)
    {
        return -1;
    }
    int nRet = -1;
    if(m_pCMvCamera != nullptr)
    {
        nRet = m_pCMvCamera->StopGrabbing();
    }
    else {
        return -1;
    }
    m_bStartGrabbing = false;
    return nRet;
}


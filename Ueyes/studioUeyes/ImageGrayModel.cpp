
#include "ImageGrayModel.h"
#include "qcoreevent.h"
#include "qmessagebox.h"
#include "qwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
//#include <QSvgRenderer>

ImageGrayModel::ImageGrayModel()
    : _imgShowLabel(new QLabel("")),
    _debugLabel(new QLabel(""))

{
    _debugLabel->setStyleSheet("background:transparent");
    QPixmap pix("C:\\Users\\HarryWen\\Downloads\\setting.svg");

    _debugLabel->setPixmap(pix.scaled(20,20,Qt::KeepAspectRatio));
    _imgShowLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _imgShowLabel->font();
    f.setBold(true);
    f.setItalic(true);

    _imgShowLabel->setFont(f);

//    _imgShowLabel->setMinimumSize(200, 200);
    _imgShowLabel->setMaximumSize(2000, 2000);

    _imgShowLabel->installEventFilter(this);
    _debugLabel->installEventFilter(this);
}
QImage cvMatToQImage(const cv::Mat& mat)
{
    switch (mat.type()) {
    case CV_8UC1:{
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);

        image.setColorCount(256);
        for(int i = 0; i < 256; i++){
            image.setColor(i, qRgb(i, i, i));
        }

        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++){
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }

        return image;
    }
    break;
    case CV_8UC3:{
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

        return image.rgbSwapped();
    }
    break;
    case CV_8UC4:{
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);

        return image.copy();
    }
    break;
    default:
        break;
    }

    return QImage();
}

cv::Mat QImageTocvMat(const QImage &image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_Grayscale8: //灰度图，每个像素点1个字节（8位）
    case QImage::Format_Indexed8: //Mat构造：行数，列数，存储结构，数据，step每行多少字节
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888: //RR,GG,BB字节顺序存储
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR); //opencv需要转为BGR的字节顺序
        break;
    }
    return mat;
}


unsigned int ImageGrayModel::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 1;
        break;

    case PortType::Out:
        result = 1;

    default:
        break;
    }

    return result;
}

bool ImageGrayModel::eventFilter(QObject *object, QEvent *event)
{
    int w,h;
    qreal dpr;

    if (object == _imgShowLabel) {
        if (event->type() == QEvent::MouseButtonPress or event->type() == QEvent::Resize)
        {
            dpr = _imgShowLabel->window()->windowHandle()->devicePixelRatio();
            w = _imgShowLabel->width()*dpr;
            h = _imgShowLabel->height()*dpr;
        }
        if (event->type() == QEvent::Resize) {
            if (!_pixmap.isNull())
            {
                _pixmap.setDevicePixelRatio(dpr);
                _imgShowLabel->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio,Qt::SmoothTransformation));
            }
        }
    }
    if (object == _debugLabel)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            this->createDebugWidget();
        }
    }
    return false;
}

void ImageGrayModel::createDebugWidget()
{
    auto w = new QWidget();
    QSlider *slider = new QSlider(Qt::Horizontal,w);
    slider->setRange(0, 255); // 设置滑动范围从0到100
    slider->setSliderPosition(thres);

    QHBoxLayout *layout = new QHBoxLayout(w);
    layout->addWidget(slider);
    w->setLayout(layout);
    _debugWin->setCentralWidget(w);
    _debugWin->show();
    connect(slider, &QSlider::valueChanged, this, &ImageGrayModel::onSliderValueChanged);
}

void ImageGrayModel::onSliderValueChanged(int value) {
    // 处理滑动条值变化的逻辑
    thres = value;
    setOutData();
    updateLabel();
}


NodeDataType ImageGrayModel::dataType(PortType const, PortIndex const) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> ImageGrayModel::outData(PortIndex)
{
    return std::make_shared<PixmapData>(_pixmap);
}

void ImageGrayModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const)
{
    QImage temp;
    _nodeData = nodeData;
    hasImage = false;
    inImage = QImage();
    if (_nodeData) {
        auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
        temp = d->pixmap().toImage();
        if (temp.width() != 0 && temp.height() != 0)
        {
            hasImage = true;
            inImage = temp;
        }

    }
    setOutData();
    updateLabel();
}

void ImageGrayModel::setOutData()
{
    if (hasImage)
    {
        QImage tarImage = binaryImage(inImage, thres, "cv::THRESH_BINARY");
        _pixmap = QPixmap::fromImage(tarImage);
        Q_EMIT dataUpdated(0);
    }
    else
    {
        _pixmap = QPixmap();
    }

}

void ImageGrayModel::updateLabel()
{
    if (hasImage)
    {
        int w = _imgShowLabel->width();
        int h = _imgShowLabel->height();
        _imgShowLabel->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));
    }
    else
    {
        _imgShowLabel->setPixmap(QPixmap());
    }
}


QImage ImageGrayModel::binaryImage(QImage &orin_img, int threshold , QString func)
{
    QImage tar_img = orin_img.convertToFormat(QImage::Format_ARGB32_Premultiplied);;
    cv::Mat orin_cv_img = QImageTocvMat(orin_img);
    cv::Mat tar_cv_img = cv::Mat(tar_img.height(), tar_img.width(), CV_8UC1, (void*)tar_img.constBits(), tar_img.bytesPerLine());

    cv::cvtColor(orin_cv_img, tar_cv_img, cv::COLOR_BGR2GRAY);
    cv::threshold(tar_cv_img, tar_cv_img, threshold, 255, cv::THRESH_BINARY);
    tar_img = cvMatToQImage(tar_cv_img);
    return tar_img;
}

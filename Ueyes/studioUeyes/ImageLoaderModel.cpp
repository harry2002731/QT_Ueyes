#include "ImageLoaderModel.hpp"
#include "qwindow.h"

#include <QtCore/QDir>
#include <QtCore/QEvent>

#include <QtWidgets/QFileDialog>

ImageLoaderModel::ImageLoaderModel()
    : _label(new QLabel("Double click to load image")),
    _button(new QPushButton())

{
    _button->setFixedSize(20,20);

    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);

    _label->setMinimumSize(200, 200);
    _label->setMaximumSize(2000, 2000);

    _label->installEventFilter(this);
}

unsigned int ImageLoaderModel::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 0;
        break;

    case PortType::Out:
        result = 1;

    default:
        break;
    }

    return result;
}

bool ImageLoaderModel::eventFilter(QObject *object, QEvent *event)
{
//    qreal dpr = _label->windowHandle()->devicePixelRatio();
    int w,h;
    qreal dpr;
    if (object == _label) {
        if (event->type() == QEvent::MouseButtonPress or event->type() == QEvent::Resize)
        {
            dpr = _label->window()->windowHandle()->devicePixelRatio();
            w = _label->width()*dpr;
            h = _label->height()*dpr;
        }
        if (event->type() == QEvent::MouseButtonPress) {
            QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                            tr("Open Image"),
                                                            QDir::homePath(),
                                                            tr("Image Files (*.png *.jpg *.bmp)"));

            _pixmap = QPixmap(fileName);
            _pixmap.setDevicePixelRatio(dpr);

            _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio,Qt::SmoothTransformation));

            Q_EMIT dataUpdated(0);
            qreal dpr = _label->window()->windowHandle()->devicePixelRatio();

            return true;
        } else if (event->type() == QEvent::Resize) {
            if (!_pixmap.isNull())
                _pixmap.setDevicePixelRatio(dpr);

                _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio,Qt::SmoothTransformation));
        }
    }


    return false;
}

NodeDataType ImageLoaderModel::dataType(PortType const, PortIndex const) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> ImageLoaderModel::outData(PortIndex)
{
    return std::make_shared<PixmapData>(_pixmap);
}

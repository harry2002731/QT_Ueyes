#ifndef IMAGEGRAYMODEL_H
#define IMAGEGRAYMODEL_H

#include "qlabel.h"
#include <QtNodes/NodeDelegateModel>
#include <QtNodes/NodeDelegateModelRegistry>
#include "PixmapData.hpp"
#include "qmainwindow.h"
#include "qpushbutton.h"


using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class ImageGrayModel: public NodeDelegateModel
{
    Q_OBJECT
public:
    ImageGrayModel();

public:
    QString caption() const override { return QString("ImageGrayModel"); }
    QString name() const override { return QString("ImageGrayModel"); }

public:
    void createDebugWidget();

    virtual QString modelName() const { return QString("ImageGrayModel"); }

    unsigned int nPorts(PortType const portType) const override;

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setDebugWin(QMainWindow & debugWin) override {_debugWin = &debugWin;};
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex const port) override;
    void setOutData();

    QWidget *embeddedWidget() override { return _imgShowLabel; }
    QWidget *embeddedButton() override { return _debugLabel; }
    bool resizable() const override { return true; }

    QImage binaryImage(QImage &orin_img, int threshold , QString func);
    void updateLabel();

    int thres = 0;
protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QMainWindow *_debugWin ;

    QLabel *_imgShowLabel;
    QLabel *_debugLabel;

    QPushButton *_button;
    bool hasImage =false;
    QPixmap _pixmap;
    QImage inImage;

    std::shared_ptr<NodeData> _nodeData;

public slots:
    void onSliderValueChanged(int value);
};

#endif // IMAGEGRAYMODEL_H

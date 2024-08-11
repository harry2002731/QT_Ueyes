#ifndef NODEIMGDELEGATEMODEL_H
#define NODEIMGDELEGATEMODEL_H
#include "qtmetamacros.h"
#include <QtNodes/NodeDelegateModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class NodeImgDelegateModel: public NodeDelegateModel
{
    Q_OBJECT
public:
    NodeImgDelegateModel();
};

#endif // NODEIMGDELEGATEMODEL_H

#pragma once

#include "BasicGraphicsScene.hpp"
#include "DataFlowGraphModel.hpp"
#include "Export.hpp"
#include "QMainWindow"
namespace QtNodes {

/// @brief An advanced scene working with data-propagating graphs.
/**
 * The class represents a scene that existed in v2.x but built wit the
 * new model-view approach in mind.
 */
class NODE_EDITOR_PUBLIC DataFlowGraphicsScene : public BasicGraphicsScene
{
    Q_OBJECT
public:
    DataFlowGraphicsScene(DataFlowGraphModel &graphModel, QMainWindow &debugWin, QObject *parent = nullptr);

    ~DataFlowGraphicsScene() = default;
    QMainWindow &win_ ;

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent* event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void createLine(const QPointF &pt);
public:
    std::vector<NodeId> selectedNodes() const;

public:
    QMenu *createSceneMenu(QPointF const scenePos) override;

public Q_SLOTS:
    bool save() const;

    bool load();

Q_SIGNALS:
    void sceneLoaded();

private:
    DataFlowGraphModel &_graphModel;
};

} // namespace QtNodes

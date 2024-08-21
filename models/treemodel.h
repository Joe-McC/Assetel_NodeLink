#ifndef QML_TREEVIEW_TREE_MODEL_H
#define QML_TREEVIEW_TREE_MODEL_H

#include <QAbstractItemModel>

#include "treeitem.h"

/*!
 * Generic Tree Model.
 */
class TreeModel : public QAbstractItemModel
{
   Q_OBJECT

public:
   explicit TreeModel(QObject* parent = nullptr);
   ~TreeModel() override;

   int rowCount(const QModelIndex& index) const override;
   int columnCount(const QModelIndex& index) const override;

   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& childIndex) const override;

   QVariant data(const QModelIndex& index, int role = 0) const override;
   bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

   //! Add an item to the top level.
   void addTopLevelItem(std::shared_ptr<TreeItem> topLevelItem);

   //! Add the item child to the parent node.
   void addItem(std::shared_ptr<TreeItem> parent, std::shared_ptr<TreeItem> child);

   //! Remove the item and all its children.
   void removeItem(std::shared_ptr<TreeItem> item);

   //! Return the root item.
   std::shared_ptr<TreeItem> rootItem() const;

   //! Return the root Model Index. Needed for the QML side.
   Q_INVOKABLE QModelIndex rootIndex();

   //! Return the depth of the item for the selected index.
   Q_INVOKABLE int depth(const QModelIndex& index) const;

   //! Remove all the elements from the tree.
   Q_INVOKABLE void clear();

public slots:

   //void handleTopLevelNodeAdded(const int &nodeId, const std::string &nodeTitle);
   //void handleChildNodeAdded(const int &nodeId, const std::string &nodeTitle, const int &parentNodeId);
   //void handleClearNodes();

   void handleNodeAdded (QString nodeID);

private:
   //TreeItem* internalPointer(const QModelIndex& index) const;
   std::shared_ptr<TreeItem> internalPointer(const QModelIndex& index) const;

   //TreeItem* _rootItem;
   std::shared_ptr<TreeItem> _rootItem;

   std::map<int, std::shared_ptr<TreeItem>> _nodeList;
};

#endif // QML_TREEVIEW_TREE_MODEL_H

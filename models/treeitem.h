#ifndef QML_TREEVIEW_TREE_ITEM_H
#define QML_TREEVIEW_TREE_ITEM_H

#include <QVariant>

/*!
 * This class represents a node of the TreeModel.
 * TreeItem can be used to set and retreive information about the node,
 * insertion and removal is meant to be deal by the model.
 */
class TreeItem : public std::enable_shared_from_this<TreeItem>
{
   friend class TreeModel;

public:
   //! Instance a tree item with empty data.
   TreeItem();

   //! Instance a tree with the input data.
   explicit TreeItem(const QVariant& data);

   //! Destroy the item and all its children.
   ~TreeItem();

   //! Return the internal data.
   const QVariant& data() const;

   //! Set the internal data.
   void setData(const QVariant& data);

   //! Return the number of children of the item.
   int childCount() const;

   //! Return the number of the row referred to the parent item.
   int row() const;

   //! Return true if the item has no children.
   bool isLeaf() const;

   //! Return the depth of the item in the hierarchy.
   int depth() const;

private:
   std::shared_ptr<TreeItem> parentItem();
   void setParentItem(std::shared_ptr<TreeItem>parentItem);

   void appendChild(std::shared_ptr<TreeItem> item);
   void removeChild(std::shared_ptr<TreeItem> item);

   std::shared_ptr<TreeItem> child(int row);

private:
   QVariant _itemData;
   std::shared_ptr<TreeItem> _parentItem;
   QVector<std::shared_ptr<TreeItem>> _childItems;
};

#endif // QML_TREEVIEW_TREE_ITEM_H

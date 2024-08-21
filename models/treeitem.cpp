#include "treeitem.h"
#include <iostream>

TreeItem::TreeItem()
   : _itemData(),
     _parentItem(nullptr)
{
}

TreeItem::TreeItem(const QVariant& data)
   : _itemData(data),
     _parentItem(nullptr)
{
}

TreeItem::~TreeItem()
{
   //qDeleteAll(_childItems);
}

std::shared_ptr<TreeItem> TreeItem::parentItem()
{
   return _parentItem;
}

void TreeItem::setParentItem(std::shared_ptr<TreeItem> parentItem)
{
   _parentItem = parentItem;
}

void TreeItem::appendChild(std::shared_ptr<TreeItem> item)
{

   std::cout << "TreeItem::appendChild " << std::endl;
   if(item && !_childItems.contains(item)){
       std::cout << "TreeItem::appendChild CHILD APPENDED " << std::endl;
      _childItems.append(item);
   }
}

void TreeItem::removeChild(std::shared_ptr<TreeItem> item)
{
   if(item){
      _childItems.removeAll(item);
   }
}

std::shared_ptr<TreeItem> TreeItem::child(int row)
{
   return _childItems.value(row);
}

int TreeItem::childCount() const
{
   return _childItems.count();
}

const QVariant& TreeItem::data() const
{
   return _itemData;
}

void TreeItem::setData(const QVariant& data)
{
   _itemData = data;
}

bool TreeItem::isLeaf() const
{
   return _childItems.isEmpty();
}

int TreeItem::depth() const
{
   int depth = 0;
   //auto ancestor = std::make_shared<TreeItem>(_parentItem);
   auto ancestor = _parentItem;
   //TreeItem* anchestor = _parentItem;
   while(ancestor){
      ++depth;
      ancestor = ancestor->parentItem();
   }

   return depth;
}

int TreeItem::row() const
{
   if (_parentItem){
      //return _parentItem->_childItems.indexOf(const_cast<TreeItem* >(this));
      //return _parentItem->_childItems.indexOf(std::make_shared<TreeItem>(this));
       return _parentItem->_childItems.indexOf(shared_from_this());
   }

   return 0;
}

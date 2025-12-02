#pragma once

#include <QAbstractItemModel>
#include <QMap>
#include <QList>
#include <QDateTime>

#include "BaseTraceViewModel.h"
#include <core/CanMessage.h>
#include <driver/CanInterface.h>

#include "AggregatedTraceViewItem.h"

class CanTrace;

class AggregatedTraceViewModel : public BaseTraceViewModel
{
    Q_OBJECT

public:
    typedef uint64_t unique_key_t;
    typedef QMap<unique_key_t, AggregatedTraceViewItem*> CanIdMap;
    typedef QDateTime Timestamp;

public:
    AggregatedTraceViewModel(Backend &backend);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;

private:
    CanIdMap _map;
    AggregatedTraceViewItem *_rootItem;
    QList<CanMessage> _pendingMessageUpdates;
    QMap<unique_key_t, CanMessage> _pendingMessageInserts;

    unique_key_t makeUniqueKey(const CanMessage &msg) const;
    void createItem(const CanMessage &msg, AggregatedTraceViewItem *item, unique_key_t key);

    double getTimeDiff(const QDateTime &t1, const QDateTime &t2) const;

protected:
    virtual QVariant data_DisplayRole(const QModelIndex &index, int role) const;
    virtual QVariant data_TextColorRole(const QModelIndex &index, int role) const;

private slots:
    void createItem(const CanMessage &msg);
    void updateItem(const CanMessage &msg);
    void onUpdateModel();
    void onSetupChanged();

    void beforeAppend(int num_messages);
    void beforeClear();
    void afterClear();
};

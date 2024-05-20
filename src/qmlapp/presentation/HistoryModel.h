#pragma once

#include <QtCore/QAbstractListModel>

#include <domain/entity/History.h>
#include <domain/entity/Entity.h>


class HistoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        DataRole = Qt::UserRole + 1,
        TimestampRole,
        TypeRole
    };
    Q_ENUM(Roles)

    HistoryModel(QObject * parent = nullptr);

public:
    void addHistoryItem(const QString &data, domain::QrCode::Type type);
    void removeHistoryItem(size_t index);
    void clearHistory();

public slots:
    void setSources(domain::HistoryListPtr histry_source);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    domain::HistoryListPtr m_history_source;
};

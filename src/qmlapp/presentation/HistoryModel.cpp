#include "HistoryModel.h"


HistoryModel::HistoryModel(QObject *parent) : QAbstractListModel(parent)
{
}

void HistoryModel::setSources(domain::HistoryListPtr history_sorce)
{
    if (history_sorce)
    {
        beginResetModel();
        m_history_source = history_sorce;
        endResetModel();
    }
}

void HistoryModel::addHistoryItem(const QString &data, domain::QrCode::Type type)
{
    beginInsertRows(QModelIndex(), m_history_source->size(), m_history_source->size());
    m_history_source->insert(m_history_source->cbegin(), {data, QDateTime::currentDateTime(), type});
    endInsertRows();
}

void HistoryModel::removeHistoryItem(size_t index)
{
    if (index < 0 || index > m_history_source->size() - 1)
    {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_history_source->erase(m_history_source->begin() + index);
    endRemoveRows();
}

void HistoryModel::clearHistory()
{
    beginResetModel();
    m_history_source->clear();
    endResetModel();
}

int HistoryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (!m_history_source)
    {
        return 0;
    }
    return static_cast<int>(m_history_source->size());
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const
{
    size_t indx = index.row();
    if (indx >= m_history_source->size())
    {
        return {};
    }
    switch (role)
    {
    case DataRole:
        return m_history_source->at(indx).data;
    case TimestampRole:
        return m_history_source->at(indx).timestamp;
    case TypeRole:
        return m_history_source->at(indx).type;
    }
    return {};
}

QHash<int, QByteArray> HistoryModel::roleNames() const
{
    return {
        {Roles::DataRole, QByteArrayLiteral("data")},
        {Roles::TimestampRole, QByteArrayLiteral("timestamp")},
        {Roles::TypeRole, QByteArrayLiteral("type")}
    };
}

#pragma once

#include <domain/entity/Entity.h>

#include <QtCore/QObject>
#include <QtCore/QDateTime>

#include <vector>

namespace domain
{

struct HistoryItem {
    QString data;
    QDateTime timestamp;
    QrCode::Type type;
};

using HistoryList = std::vector<HistoryItem>;
using HistoryListPtr = std::shared_ptr<std::vector<HistoryItem>>;
using HistoryListUnq = std::unique_ptr<std::vector<HistoryItem>>;


} // namespace domain

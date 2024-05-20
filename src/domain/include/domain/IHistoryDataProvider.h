#pragma once

#include <QtCore/QObject>

#include <memory>

#include "entity/History.h"


namespace domain
{

class IHistoryDataProvider : public QObject
{
	Q_OBJECT

public:
    virtual ~IHistoryDataProvider() = default;
    virtual void load() = 0;
    virtual void save(HistoryListPtr historyList) const = 0;
    virtual void clear() const = 0;

signals:
    void dataLoaded(HistoryListPtr historyList);
};

using IHistoryDataProviderPtr = std::shared_ptr<IHistoryDataProvider>;

} // namespace domain

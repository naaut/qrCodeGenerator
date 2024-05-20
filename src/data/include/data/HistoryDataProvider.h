#pragma once

#include <QtCore/QObject>
#include <domain/IHistoryDataProvider.h>
#include <QtConcurrent/QtConcurrent>


namespace data {

class HistoryDataProvider : public domain::IHistoryDataProvider
{
    Q_OBJECT

public:
    void load() override;
    void save(domain::HistoryListPtr historyList) const override;
    void clear() const override;

private:
    domain::HistoryListPtr loadImpl();
    void saveToFile(const QJsonArray &jsonArray) const;

private:
    QFuture<void> load_future;

};

} // namespace data

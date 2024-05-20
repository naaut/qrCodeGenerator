#pragma once

#include <domain/IHistoryDataProvider.h>
#include <domain/entity/History.h>
#include <QtCore/QObject>

#include <memory>


class HistoryUsecase : public QObject {
    Q_OBJECT

public:
    explicit HistoryUsecase(domain::IHistoryDataProviderPtr provider);

    void saveHistory() const;
    domain::HistoryListPtr getHistory() const;

signals:
    void historyLoaded();

private:
    domain::IHistoryDataProviderPtr m_data_provider;
    domain::HistoryListPtr m_history_list;
};

using HistoryUsecaseUnq = std::unique_ptr<HistoryUsecase>;

#include "HistoryUsecase.h"

#include <QtCore/QDateTime>


HistoryUsecase::HistoryUsecase(domain::IHistoryDataProviderPtr provider)
    : m_data_provider(std::move(provider))
{
    connect(m_data_provider.get(), &domain::IHistoryDataProvider::dataLoaded, this, [this](domain::HistoryListPtr historyList) {
        m_history_list = historyList;
        emit historyLoaded();
    });
    m_data_provider->load();
}

void HistoryUsecase::saveHistory() const
{
    m_data_provider->save(m_history_list);
}

domain::HistoryListPtr HistoryUsecase::getHistory() const
{
    return m_history_list;
}

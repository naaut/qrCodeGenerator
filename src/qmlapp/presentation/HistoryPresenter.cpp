#include "HistoryPresenter.h"


HistoryPresenter::HistoryPresenter(HistoryUsecaseUnq history_usecase)
    : QObject()
    , m_history_usecase(std::move(history_usecase))
    , m_history_model(new HistoryModel(this))
{
    Q_ASSERT(m_history_usecase);

    connect(m_history_usecase.get(), &HistoryUsecase::historyLoaded, this, [this](){
        m_history_model->setSources(m_history_usecase->getHistory());
    });
    m_history_model->setSources(m_history_usecase->getHistory());
}

void HistoryPresenter::addHistoryItem(const QString &data, domain::QrCode::Type type)
{
    m_history_model->addHistoryItem(data, type);
    m_history_usecase->saveHistory();
}

void HistoryPresenter::removeHistoryItem(size_t index)
{
    m_history_model->removeHistoryItem(index);
    m_history_usecase->saveHistory();
}

void HistoryPresenter::clearHistory()
{
    m_history_model->clearHistory();
    m_history_usecase->saveHistory();
}

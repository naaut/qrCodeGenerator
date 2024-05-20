#pragma once

#include <QtCore/QObject>

#include <usecase/HistoryUsecase.h>
#include <presentation/HistoryModel.h>
#include <domain/entity/Entity.h>


class HistoryPresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel * historyModel MEMBER m_history_model CONSTANT FINAL)

public:
    explicit HistoryPresenter(HistoryUsecaseUnq history_usecase);

    Q_INVOKABLE void addHistoryItem(const QString &data, domain::QrCode::Type type);
    Q_INVOKABLE void removeHistoryItem(size_t index);
    Q_INVOKABLE void clearHistory();

private:
    HistoryUsecaseUnq m_history_usecase;
    HistoryModel * m_history_model;
};

using HistoryPresenterUnq = std::unique_ptr<HistoryPresenter>;

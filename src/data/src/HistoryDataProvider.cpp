#include <data/HistoryDataProvider.h>

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include <domain/entity/Entity.h>


namespace data {

void HistoryDataProvider::load()
{
    if (load_future.isRunning())
    {
        load_future.cancel();
        qDebug() << "load histry future canceled";
    }
    load_future = QtConcurrent::run([this]() {
        auto historyList = HistoryDataProvider::loadImpl();
        emit dataLoaded(historyList);
    });
}

void HistoryDataProvider::save(domain::HistoryListPtr historyList) const
{
    QJsonArray jsonArray;
    for (auto value : *historyList) {
        QJsonObject obj {
            { "data", value.data },
            { "timestamp", value.timestamp.toString(Qt::ISODate) },
            { "type", value.type }
        };
        jsonArray.append(obj);
    }
    saveToFile(jsonArray);
}

void HistoryDataProvider::clear() const
{
    saveToFile(QJsonArray());
}

domain::HistoryListPtr HistoryDataProvider::loadImpl()
{
    domain::HistoryListPtr historyList = std::make_shared<domain::HistoryList>();

    QFile file("history.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        return historyList;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray jsonArray = doc.array();
    historyList->reserve(jsonArray.size());

    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();
        historyList->push_back({
            obj["data"].toString(),
            QDateTime::fromString(obj["timestamp"].toString(), Qt::ISODate),
            static_cast<domain::QrCode::Type>(obj["type"].toInt())
        });
    }
    file.close();

    return historyList;
}

void HistoryDataProvider::saveToFile(const QJsonArray &historyList) const
{
    QFile file("history.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }
    QJsonDocument doc(historyList);
    file.write(doc.toJson());
    file.close();
}

} // namespace data


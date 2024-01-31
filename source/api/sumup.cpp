/*
 * Created by janis on 2024-01-27
 */

#include "sumup.h"

#include <functional>

#include <QNetworkReply>
#include <QJsonDocument>

namespace ag {
    void SumupApi::set_key(std::string&& key) {
        this->api_key = key;
    }

    void SumupApi::transactions_history(const QDateTime& oldest, const QDateTime& newest, const std::function<void(std::vector<Transaction>&&)>& callback) {
        std::string args;
        args += "oldest_time=" + std::string(oldest.toUTC().toString(Qt::DateFormat::ISODate).toUtf8().constData()) + "&";
        args += "newest_time=" + std::string(newest.toUTC().toString(Qt::DateFormat::ISODate).toUtf8().constData()) + "&";
        args += "limit=10&order=ascending";

        transactions_recurse(args, [=](QJsonArray&& items){
            if (auto res = try_parse_transactions(std::move(items)); res.has_value()) {
                callback(std::move(*res));
            }
        });
    }

    void SumupApi::transactions_recurse(const std::string& args, const std::function<void(QJsonArray&&)>& callback) {
        QNetworkRequest req;
        req.setUrl(QUrl((this->api_url + "me/transactions/history?" + args).c_str()));
        std::string auth_header = "Bearer " + this->api_key;
        req.setRawHeader("Authorization", QString(auth_header.c_str()).toUtf8());

        QNetworkReply* resp = this->network_manager.get(req);
        connect(resp, &QNetworkReply::finished, this, [=, this](){
            QByteArray data = resp->readAll();
            QJsonDocument json_data = QJsonDocument::fromJson(data);
            QJsonObject root = json_data.object();
            QJsonArray items = root["items"].toArray();
            QJsonArray links = root["links"].toArray();

            if (!links.empty()) {
                this->transactions_recurse(links[0].toObject()["href"].toString().toUtf8().constData(), [=]([[maybe_unused]] QJsonArray&& next){
                    QJsonArray arr = items;
                    for (QJsonValue val : next) {
                        arr.append(val);
                    }
                    callback(std::move(arr));
                });
            } else {
                callback(std::move(items));
            }
        });
    }
}
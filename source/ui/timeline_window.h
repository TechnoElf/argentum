/*
 * Created by janis on 2024-01-26
 */

#pragma once

#include <QDockWidget>
#include <QListView>
#include <QStringListModel>
#include <QDate>

namespace ag {
    struct TimelineWindow : public QDockWidget {
        QDate start = QDate::currentDate();
        QDate end = QDate::currentDate();

    Q_OBJECT

    public:
        explicit TimelineWindow(QWidget* parent = nullptr);

        TimelineWindow(const TimelineWindow& other) = delete;
        TimelineWindow& operator=(const TimelineWindow& other) = delete;
        TimelineWindow(TimelineWindow&& other) = delete;
        TimelineWindow& operator=(TimelineWindow&& other) = delete;

    private:
        QStringList dates_list = QStringList();
        QStringListModel model = QStringListModel(this);

        QListView list_view = QListView(this);

    signals:
        void selection_changed();
    };
}
/*
 * Created by janis on 2024-01-26
 */

#include "timeline_window.h"

namespace ag {
    TimelineWindow::TimelineWindow(QWidget* parent) : QDockWidget("Timeline", parent) {
        QDate date = QDate::currentDate();
        for (int i = 0; i < 100; i++) {
            this->dates_list.append(date.toString(Qt::ISODate));
            date = date.addDays(-1);
        }

        this->model.setStringList(this->dates_list);
        this->list_view.setModel(&this->model);
        this->list_view.setSelectionMode(QAbstractItemView::ContiguousSelection);
        this->list_view.setEditTriggers(QAbstractItemView::NoEditTriggers);

        connect(this->list_view.selectionModel(), &QItemSelectionModel::selectionChanged, this, [&](){
            QItemSelection selection = this->list_view.selectionModel()->selection();
            QModelIndex top = selection.first().topLeft();
            QModelIndex bottom = selection.first().topLeft();
            for (QItemSelectionRange range : selection) {
                if (range.topLeft().row() < top.row()) { top = range.topLeft(); }
                if (range.bottomRight().row() > bottom.row()) { bottom = range.bottomRight(); }
            }
            this->start = this->model.data(bottom).toDate();
            this->end = this->model.data(top).toDate();

            emit selection_changed();
        });

        this->setWidget(&this->list_view);
    }
}
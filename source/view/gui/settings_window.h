#pragma once


#include <QMainWindow>


#include "controller/viewer.h"


namespace view::gui {


class ColorWidget: public QWidget {
public:
    explicit ColorWidget(QColor color  = Qt::red, QWidget *parent = nullptr);

    QColor getBackgroundColor() const;

private:
    void mousePressEvent(QMouseEvent *event) override;
    void setBackgroundColor(QColor const &color);

    QColor m_color;
};


class CSettingsWindow: public QMainWindow {
    Q_OBJECT
public:
    typedef QSharedPointer<CSettingsWindow> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }
    
    CSettingsWindow(controller::IViewer::TPtr const &editor_controller);
    virtual ~CSettingsWindow() = default;

private:
    void closeEvent(QCloseEvent *event) override;

    controller::IViewer::TPtr m_viewer_controller;
};


} // view::gui

#pragma once


#include <QMainWindow>


#include "model/cylinder.h"
#include "view/settings.h"


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


class CSettingsWindow: public QMainWindow, public ISettings {
    Q_OBJECT
    Q_INTERFACES(view::ISettings)
public:
    typedef QSharedPointer<CSettingsWindow> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }
    
    CSettingsWindow();
    virtual ~CSettingsWindow() = default;

signals:
    void onSceneUpdated     (model::IScene::TPtr    const &scene)       override;
    void onCylinderUpdated  (model::ICylinder::TPtr const &cylinder)    override;

private:
    void closeEvent(QCloseEvent *event) override;
};


} // view::gui

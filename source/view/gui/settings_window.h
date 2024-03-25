#pragma once


#include <QMainWindow>


#include "model/implementation/cylinder.h"
#include "model/implementation/scene.h"

#include "view/settings.h"


namespace view::gui {


class ColorWidget: public QWidget {
    Q_OBJECT
public:
    explicit ColorWidget(QColor color  = Qt::red, QWidget *parent = nullptr);

signals:
    void onColorChanged(const QColor &color);

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

    void onSpinBoxValueChanged(int const &value);
    void onColorChanged(const QColor &color);
    void onComboBoxIndexChanged(int const &value);

// models, coule be initialized outside this class
    model::implementation::CScene::TPtr     m_scene;
    model::implementation::CCylinder::TPtr  m_cylynder;
};


} // view::gui

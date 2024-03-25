#pragma once


#include "controller/scene.h"

#include "view/settings.h"
#include "view/view.h"

#include <QObject>


namespace controller::implementation {


class CScene: public QObject /*: public IScene*/ {
    Q_OBJECT
public:
    typedef QSharedPointer<CScene> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }

    CScene(view::ISettings *settings, view::IViewer *viewer);
    virtual ~CScene() = default;

private:
    view::ISettings *m_settings;
    view::IViewer   *m_viewer;
};


} // controller::implementation

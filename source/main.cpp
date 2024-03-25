// Приложение на Qt, состоит из 2-х окон:
// Правое окно - openGL с вращающимся цилиндром
// Левое окно - параметры:
//   1) число вершин цилиндра,
//   2) выбор оси вращения,
//   3) выбор цвета цилиндра
// Изменение параметров должно мгновенно отображаться в окне openGL
// Как организован ввод параметров - на ваше усмотрение.


#include <QApplication>

#include "controller/implementation/scene.h"
#include "view/gui/settings_window.h"
#include "view/gui/view_window.h"


using view::gui::CViewWindow;
using view::gui::CSettingsWindow;
using controller::implementation::CScene;


int main(int argc, char *argv[]) {
    QApplication    app(argc, argv);

    auto view_window         = CViewWindow::create();
    auto settings_window     = CSettingsWindow::create();

    auto controller          = CScene::create
        (settings_window.get(), view_window.get());

    settings_window->show();

    // tile windows to vertical borders
    {
        auto pos = settings_window->pos();

        // bugfix for linux desktops
        if (pos == QPoint(0, 0)) {
            pos.setX(1);
            pos.setY(1);
            settings_window->move(pos);
        }

        pos.setX(pos.x() + settings_window->width());

        view_window->move(pos);
    }

    view_window->show();

    return app.exec(); // ----->
}

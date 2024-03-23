// Приложение на Qt, состоит из 2-х окон:
// Правое окно - openGL с вращающимся цилиндром
// Левое окно - параметры:
//   1) число вершин цилиндра,
//   2) выбор оси вращения,
//   3) выбор цвета цилиндра
// Изменение параметров должно мгновенно отображаться в окне openGL
// Как организован ввод параметров - на ваше усмотрение.


#include <QApplication>

#include "controller/implementation/viewer.h"
#include "view/gui/settings_window.h"
#include "view/gui/view_window.h"


using controller::implementation::CViewer;
using view::gui::CViewWindow;
using view::gui::CSettingsWindow;


int main(int argc, char *argv[]) {
    QApplication    app(argc, argv);
    auto            viewer_controller   = CViewer::create();
    auto            view_window         = CViewWindow::create       (viewer_controller);
    auto            settings_window     = CSettingsWindow::create   (viewer_controller);

    settings_window->show();

    view_window->move(settings_window->pos().x() + settings_window->width(), settings_window->pos().y());
    view_window->show();

    return app.exec(); // ----->
}

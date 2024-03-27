#include "settings_window.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QStatusBar>
#include <QLabel>
#include <QSpinBox>
#include <QTreeView>
#include <QColorDialog>
#include <QMouseEvent>
#include <QTreeWidget>
#include <QComboBox>
#include <QCoreApplication>
#include <QFontDatabase>


namespace view::gui {


static int  const DEFAULT_WINDOW_WIDTH                  = 300;
static int  const DEFAULT_WINDOW_HEIGHT                 = 480;
static int  const DEFAULT_TREE_WIDGET_COLUMN1_WIDTH     = 150;
static char const DEFAULT_TREE_WIDGET_COLUMN1_NAME[]    = "Name";
static char const DEFAULT_TREE_WIDGET_COLUMN2_NAME[]    = "Value";
static char const DEFAULT_VERTICES_COUNT_FIELD_NAME[]   = "Vertices";
static char const DEFAULT_COLOR_CHOOSING_FIELD_NAME[]   = "Color";
static char const DEFAULT_AXIS_CHOOSING_FIELD_NAME[]    = "Rotation Axis";
static char const DEFAULT_WINDOW_TITLE[]                = "Settings";
static char const DEFAULT_WINDOW_COLOR_DIALOG_TITLE[]   = "Choose Color";
static char const DEFAULT_NAME_AXIS_X[]                 = "Axis X";
static char const DEFAULT_NAME_AXIS_Y[]                 = "Axis Y";
static char const DEFAULT_NAME_AXIS_Z[]                 = "Axis Z";


ColorWidget::ColorWidget(QColor color, QWidget *parent)
:
    QLabel(parent),
    m_color(color)
{
    setBackgroundColor(color);
}


void ColorWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QColor color = QColorDialog::getColor(m_color, this, tr(DEFAULT_WINDOW_COLOR_DIALOG_TITLE));
        if (color.isValid())
            setBackgroundColor(color);
    }
}


void ColorWidget::setBackgroundColor(QColor const &color) {
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, color);
    setAutoFillBackground(true);
    this->setPalette(palette);
    this->show();

    setStyleSheet(QString("background-color: %0; border-radius: 5px;").arg(color.name()));

    m_color = color;

    qDebug() << color;

    emit onColorChanged(m_color);
}



CSettingsWindow::CSettingsWindow()
:
    m_scene     (model::implementation::CScene::create()),
    m_cylynder  (model::implementation::CCylinder::create())
{
    // window font
    {
        QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
        font.setPointSize(10);

        setFont(font);
    }

    auto *central_widget     = new QWidget(this);
    auto *vbox               = new QVBoxLayout(central_widget);

    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);

    // tree widget
    {
        auto tree_widget = new QTreeWidget();
        tree_widget->setHeaderLabels(
            QStringList{tr(DEFAULT_TREE_WIDGET_COLUMN1_NAME), tr(DEFAULT_TREE_WIDGET_COLUMN2_NAME)});
        tree_widget->setColumnWidth(0, DEFAULT_TREE_WIDGET_COLUMN1_WIDTH);
        tree_widget->setUniformRowHeights(true);

        // vertices count
        {
            QTreeWidgetItem *tree_widget_item   = new QTreeWidgetItem(tree_widget);
            tree_widget_item->setText(0, tr(DEFAULT_VERTICES_COUNT_FIELD_NAME));

            QSpinBox        *spin_box           = new QSpinBox(tree_widget);
            spin_box->setRange(3, 100); // todo: get from model
            spin_box->setValue(static_cast<int>(m_cylynder->getVerticesNumber()));

            tree_widget->setItemWidget(tree_widget_item, 1, spin_box);

            connect(spin_box, &QSpinBox::valueChanged, this, &CSettingsWindow::onSpinBoxValueChanged);
        }

        // color choosing
        {
            QTreeWidgetItem *tree_widget_item   = new QTreeWidgetItem(tree_widget);
            tree_widget_item->setText(0, tr(DEFAULT_COLOR_CHOOSING_FIELD_NAME));
            ColorWidget     *color_widget       = new ColorWidget(m_cylynder->getColor(), tree_widget);

            tree_widget->setItemWidget(tree_widget_item, 1, color_widget);

            connect(color_widget, &ColorWidget::onColorChanged, this, &CSettingsWindow::onColorChanged);
        }

        // axises
        {
            QTreeWidgetItem *tree_widget_item   = new QTreeWidgetItem(tree_widget);
            tree_widget_item->setText(0, tr(DEFAULT_AXIS_CHOOSING_FIELD_NAME));

            QComboBox       *combo_box          = new QComboBox(tree_widget);
            combo_box->addItem(tr(DEFAULT_NAME_AXIS_X), QVariant(1));
            combo_box->addItem(tr(DEFAULT_NAME_AXIS_Y), QVariant(2));
            combo_box->addItem(tr(DEFAULT_NAME_AXIS_Z), QVariant(3));
            combo_box->setCurrentIndex(static_cast<int>(m_scene->getRotationAxys()));

            tree_widget->setItemWidget(tree_widget_item, 1, combo_box);

            connect(combo_box, &QComboBox::currentIndexChanged, this, &CSettingsWindow::onComboBoxIndexChanged);
        }

        // // align text to left
        // {
        //     QTreeWidgetItemIterator widget_item_iterator(tree_widget);
        //     while (*widget_item_iterator) {
        //         QTreeWidgetItem *tree_widget_item = *widget_item_iterator;
        //         for (int column = 0; column < tree_widget_item->columnCount(); ++column)
        //             tree_widget_item->setTextAlignment(column, Qt::AlignLeft | Qt::AlignVCenter);
        //         ++widget_item_iterator;
        //     }
        // }

        vbox->addWidget(tree_widget);
    }

    // close button
    {
        auto *close_button = new QPushButton(tr("Close"));

        vbox->addWidget(close_button);

        connect(close_button, &QPushButton::clicked, this, &CSettingsWindow::close);
    }

    setCentralWidget(central_widget);

    statusBar()->showMessage(tr(""));
    setWindowTitle(tr(DEFAULT_WINDOW_TITLE));
    resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

    signal:
    onSceneUpdated(m_scene);
    onCylinderUpdated(m_cylynder);
}


void CSettingsWindow::closeEvent(QCloseEvent *event) {
    QCoreApplication::quit();
    QMainWindow::closeEvent(event);
}


void CSettingsWindow::onSpinBoxValueChanged(int const &value) {
    m_cylynder->setVerticesNumber(value);
    qDebug() << "CSettingsWindow::onSpinBoxValueChanged";
    signal: onCylinderUpdated(m_cylynder);
}


void CSettingsWindow::onColorChanged(const QColor &color) {
    m_cylynder->setColor(color);
    qDebug() << "CSettingsWindow::onColorChanged";
    signal: onCylinderUpdated(m_cylynder);
}


void CSettingsWindow::onComboBoxIndexChanged(int const &value) {
    model::IScene::TRotationAxis rotation_axis = static_cast<model::IScene::TRotationAxis>(value);
    m_scene->setRotationAxys(rotation_axis);
    signal: onSceneUpdated(m_scene);
    qDebug() << "CSettingsWindow::onComboBoxIndexChanged";
}


} // view::gui

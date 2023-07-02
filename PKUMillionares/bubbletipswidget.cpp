#include "BubbleTipsWidget.h"
#include "ui_BubbleTipsWidget.h"
#include <QPainter>

BubbleTipsWidget::BubbleTipsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BubbleTipsWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    setBackColor(121, 0, 0,0);
    setDirect(DIRECT::DIRECT_BOTTOM, 0.75);

    QFont f;
    f.setFamily("Microsoft YaHei UI");
    f.setPixelSize(14);
    setContentFont(f);
    setContent("I am a default text");

    setLeftTopMargin();
}

BubbleTipsWidget::~BubbleTipsWidget()
{
    delete ui;
}

void BubbleTipsWidget::setBackColor(int r, int g, int b, int a)
{
    m_backColor = QColor(r, g, b, a);
}

void BubbleTipsWidget::setDirect(DIRECT direct, double size)
{
    m_direct = direct;
    m_posSize = size;
}

void BubbleTipsWidget::setContentFont(QFont font)
{
    ui->label->setFont(font);
}

void BubbleTipsWidget::setContent(const QString &content, QColor color)
{
    ui->label->setText(content);
    ui->label->setStyleSheet(QString("color: rgb(%1, %2, %3)")
                             .arg(color.red())
                             .arg(color.green())
                             .arg(color.blue()));
}

void BubbleTipsWidget::setLeftTopMargin(int leftMargin, int topMargin)
{
    m_leftMargin = leftMargin;
    m_topMargin = topMargin;
    this->setContentsMargins(m_leftMargin + TRANSPARENT_LENGTH,
                             m_topMargin + TRANSPARENT_LENGTH,
                             m_leftMargin + TRANSPARENT_LENGTH,
                             m_topMargin + TRANSPARENT_LENGTH);
}

void BubbleTipsWidget::set_background_rootplace(const QString pic_root_place){
    this->pic_root=pic_root_place;
}
void BubbleTipsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);


    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backColor);

    //相对于当前布局的起点坐标
    painter.drawRoundedRect(TRANSPARENT_LENGTH, TRANSPARENT_LENGTH,
                            width() - TRANSPARENT_LENGTH * 2,
                            height() - TRANSPARENT_LENGTH * 2, 4, 4);

    if(pic_root!=""){
        QPixmap pic;
        pic.load(pic_root);
        painter.drawPixmap(ui->widget->pos().x(),ui->widget->pos().y(),ui->widget->width(),ui->widget->height(),pic);
        qDebug()<<ui->widget->pos().x()<<" "<<ui->widget->pos().y()<<" "<<ui->widget->x();
        qDebug()<<ui->widget->pos();
    }


    QPointF points[3];

    switch (m_direct) {
    case DIRECT::DIRECT_LEFT: {
        points[0] = QPointF(TRANSPARENT_LENGTH,
                            height() * m_posSize - DEF_TRIANGLE_HEIGHT);
        points[1] = QPointF(TRANSPARENT_LENGTH - DEF_TRIANGLE_HEIGHT,
                            height() * m_posSize);
        points[2] = QPointF(TRANSPARENT_LENGTH,
                            height() * m_posSize + DEF_TRIANGLE_HEIGHT);
        break;
    }

    case DIRECT::DIRECT_TOP: {
        points[0] = QPointF(width() * m_posSize - DEF_TRIANGLE_HEIGHT,
                            TRANSPARENT_LENGTH);
        points[1] = QPointF(width() * m_posSize,
                            TRANSPARENT_LENGTH - DEF_TRIANGLE_HEIGHT);
        points[2] = QPointF(width() * m_posSize + DEF_TRIANGLE_HEIGHT,
                            TRANSPARENT_LENGTH);
        break;
    }

    case DIRECT::DIRECT_RIGHT: {
        points[0] = QPointF(width() - TRANSPARENT_LENGTH,
                            height() * m_posSize - DEF_TRIANGLE_HEIGHT);
        points[1] = QPointF(width() - DEF_TRIANGLE_HEIGHT, height() * m_posSize);
        points[2] = QPointF(width() - TRANSPARENT_LENGTH,
                            height() * m_posSize + DEF_TRIANGLE_HEIGHT);
        break;
    }

    case DIRECT::DIRECT_BOTTOM: {
        points[0] = QPointF(width() * m_posSize - DEF_TRIANGLE_HEIGHT,
                            height() - TRANSPARENT_LENGTH);
        points[1] = QPointF(width() * m_posSize, height() - DEF_TRIANGLE_HEIGHT);
        points[2] = QPointF(width() * m_posSize + DEF_TRIANGLE_HEIGHT,
                            height() - TRANSPARENT_LENGTH);
        break;
    }

    default:
        break;
    }

    painter.drawPolygon(points, 3);
}


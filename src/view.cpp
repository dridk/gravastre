#include "engine.cpp"
#include "view.h"
#include <QDebug>

view::Universe::Universe(eng::Engine& engine, QWidget* parent) :
    engine(engine), QWidget(parent) {
    this->placement_line.setLine(0,0,0,0);
    this->setMouseTracking(true);
    this->selected_mass = 1e3;
    this->selected_speed = 1e-1;
    this->is_drag_placement = false;  // true when a new Astre is in placement
    this->is_drag_translation = false;  // true when holding right button pressed
    this->space_ref = QPointF(0,0);
    this->drag_translation= QPointF(0,0);
    // configure the timer
    connect(&this->update_call, SIGNAL(timeout()), this, SLOT(update_engine()));
    update_call.start(1);
    update_engine();
}


void view::Universe::update_engine() {
    this->engine.update();
    update();
}


void view::Universe::paintEvent(QPaintEvent*) {
    QPen default_pen(Qt::transparent);
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing	);
    painter.setBrush(QBrush(Qt::black));  // fill color
    painter.setPen(default_pen);  // outline color
    painter.drawRect(rect());
    painter.translate(this->drag_translation);

    if(this->is_drag_placement) {
        painter.setPen(QPen(Qt::blue));
        painter.drawLine(this->placement_line);
        painter.setPen(default_pen);
    }

    // print astres
    QPoint astre_center;
    eng::Engine::AstreIterator it = this->engine.begin();
    for(; it != this->engine.end() ; it++) {
        astre_center.setX(unit::au_to_pixel((*it)->getX()));
        astre_center.setY(unit::au_to_pixel((*it)->getY()));
        painter.setBrush(QBrush((*it)->getColor()));
        painter.drawEllipse(
                    astre_center,
                    (int)(*it)->getRadius(),
                    (int)(*it)->getRadius()
                    );
    }
}


void view::Universe::mousePressEvent(QMouseEvent* event) {
    //std::cout << "Clic detected at:" << std::endl
    //<< "\tevent->pos():" << event->pos().x() << ";" << event->pos().y() << std::endl
    //<< "\tevent->localPos():" << event->localPos().x() << ";" << event->localPos().y() << std::endl
    //<< "\tevent->globalPos():" << event->globalPos().x() << ";" << event->globalPos().y() << std::endl
    //<< "\tevent->screenPos():" << event->screenPos().x() << ";" << event->screenPos().y() << std::endl
    //<< "\tevent->windowPos():" << event->windowPos().x() << ";" << event->windowPos().y() << std::endl
    //<< "\tEND"  << std::endl;
    if(event->button() == Qt::LeftButton) {
        this->placement_line.setP1(event->pos());
        this->placement_line.setP2(event->pos());
        this->is_drag_placement = true;
    } else if(event->button() == Qt::RightButton) {
        this->is_drag_translation = true;
        this->space_ref = event->pos();
        update();
    }
}


void view::Universe::mouseMoveEvent(QMouseEvent* event) {
    if(this->is_drag_placement) {
        this->placement_line.setP2(Universe::global_to_relative(event->pos()));
        update();
    } else if(this->is_drag_translation) {

        this->drag_translation += event->pos() - this->space_ref;
        this->space_ref = event->pos();

    }
}


void view::Universe::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        double speed_x = this->placement_line.x2() - this->placement_line.x1();
        double speed_y = this->placement_line.y2() - this->placement_line.y1();
        this->engine.add_astre(
                    this->selected_mass,
                    unit::pixel_to_au(this->placement_line.x1()),
                    unit::pixel_to_au(this->placement_line.y1()),
                    this->selected_speed * speed_x,
                    this->selected_speed * speed_y
                    );
        this->placement_line.setLine(0,0,0,0);
        this->is_drag_placement = false;
        update();
    } else if(event->button() == Qt::RightButton) {
        this->is_drag_translation = false;
    }
}


void view::Universe::keyPressEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_E) {
        this->selected_mass *= 10;
        qDebug() << "selected mass increased to " << this->selected_mass ;
    } else if(event->key() == Qt::Key_I) {
        this->selected_mass /= 10;
        qDebug()<< "selected mass decreased to " << this->selected_mass ;
    } else if(event->key() == Qt::Key_D) {
        qDebug() << "universe cleared !" ;
        this->engine.clear_all();
    } else if(event->key() == Qt::Key_O) {
        this->selected_speed *= 10;
        qDebug()<< "selected speed increased to " << this->selected_speed ;
    } else if(event->key() == Qt::Key_P) {
        this->selected_speed /= 10;
        qDebug() << "selected speed decreased to " << this->selected_speed;
    } else if(event->key() == Qt::Key_Space) {
        this->drag_translation.setX(0);
        this->drag_translation.setY(0);

        qDebug() << "universe centered !";
    }
}


QPoint view::Universe::global_to_relative(const QPoint& point) const {
    return QPoint(point + this->drag_translation.toPoint());
}
QPoint view::Universe::global_to_relative(const QPointF& point) const {
    return QPoint(point.toPoint() + this->drag_translation.toPoint());
}

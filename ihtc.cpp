/*
Copyright (C) 2008/09 Thomas Luebking <thomas.luebking@web.de>

This software is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public
License version 2 as published by the Free Software Foundation.

This software is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
*/

#include <QChildEvent>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <Plasma/Containment>
#include "ihtc.h"

#include <QtDebug>

using namespace Plasma;

static QMap<Containment*,IHTC*>instance;

IHTC::IHTC(QObject *parent, const QVariantList &args) : Applet(parent, args)
{
}

IHTC::~IHTC()
{
    if (Containment *desktop = instance.key(this, 0))
    {
        if (instance.value(desktop, 0) == this)
        {
            instance.remove(desktop);
            reanimateCashew();
        }
    }
}

void
IHTC::init()
{
    Applet::init();
    setAcceptHoverEvents(true);
    setGeometry(QApplication::desktop()->screenGeometry());
    hide();

    Containment *desktop = containment();
    if (!desktop || instance.contains(desktop))
    {
        qWarning("BESPIN IHTC, You cannot kill the cashew twice ;-)");
        deleteLater();
    }

    instance.insert(desktop, this);

    setAspectRatioMode(IgnoreAspectRatio);
    if ((_cashew = cashew()))
        _cashew->hide();

    setFlag(ItemClipsToShape, false);
    setFlag(ItemClipsChildrenToShape, false);
    connect(this, SIGNAL(zoomOut()), containment(), SLOT(zoomOut()));
    connect (this, SIGNAL(destroyed()), this, SLOT(reanimateCashew()));
}
#if 0
void
IHTC::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    QTransform trans;
    trans = trans.translate(-rect().width(), -rect().height());
    trans = trans.scale(3.0, 3.0);
    setTransform(trans);
}

void
IHTC::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setTransform(QTransform());
}
#endif
void
IHTC::paint(QPainter *p, const QStyleOptionGraphicsItem */*opt*/, QWidget */*widget*/)
{
    QRectF r = rect();
    p->save();
    p->setRenderHint(QPainter::Antialiasing);
    if (isUnderMouse())
    {
        p->setBrush(QColor(255,255,255,64));
        p->setPen(QColor(255,255,255,128));
        p->drawEllipse(rect());
        float dx = r.width()/3.0;
        float dy = r.height()/3.0;
        r.adjust(dx, dy, -dx, -dy);
    }
    p->setBrush(QColor(255,255,255,64));
    p->setPen(Qt::NoPen);
    p->drawEllipse(r);
    p->restore();
}

QGraphicsItem *
IHTC::cashew()
{
    Containment *desktop = containment();
    if (!desktop || desktop->containmentType() != Containment::DesktopContainment)
        return 0;

    QObject *o;
    foreach (QGraphicsItem *kid, desktop->childItems())
    {
        o = dynamic_cast<QObject*>(kid);
        if (o && o->inherits("Plasma::ToolBox") || o->inherits("Plasma::DesktopToolBox"))
            return kid;
    }
    return 0;
}

void
IHTC::reanimateCashew()
{
    if (QGraphicsItem *c = cashew())
        c->show();
    else if (_cashew) // dangerous?!
        _cashew->show();
}


K_EXPORT_PLASMA_APPLET(ihatethecashew, IHTC)

#include "ihtc.moc"

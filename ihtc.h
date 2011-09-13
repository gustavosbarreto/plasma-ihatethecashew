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

#ifndef DTI_H
#define DTI_H


#include <Plasma/Applet>

class IHTC : public Plasma::Applet
{
   Q_OBJECT
public:
    IHTC(QObject *parent, const QVariantList &args);
    ~IHTC();
    void init();
    virtual void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *widget = 0);

// signals:
//     void zoomIn();
//     void zoomOut();
//     void addActivity();

// protected:
//     virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
//     virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QGraphicsItem *_cashew;
    QGraphicsItem *cashew();
private slots:
    void reanimateCashew();
};

#endif //DTI_H

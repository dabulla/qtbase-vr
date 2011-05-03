/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QICON_H
#define QICON_H

#include <QtCore/qglobal.h>
#include <QtCore/qsize.h>
#include <QtCore/qlist.h>
#include <QtGui/qpixmap.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class QIconPrivate;
class QIconEngine;
class QIconEngineV2;

class Q_GUI_EXPORT QIcon
{
public:
    enum Mode { Normal, Disabled, Active, Selected };
    enum State { On, Off };

    QIcon();
    QIcon(const QPixmap &pixmap);
    QIcon(const QIcon &other);
    explicit QIcon(const QString &fileName); // file or resource name
    explicit QIcon(QIconEngine *engine);
    explicit QIcon(QIconEngineV2 *engine);
    ~QIcon();
    QIcon &operator=(const QIcon &other);
#ifdef Q_COMPILER_RVALUE_REFS
    inline QIcon &operator=(QIcon &&other)
    { qSwap(d, other.d); return *this; }
#endif
    inline void swap(QIcon &other) { qSwap(d, other.d); }

    operator QVariant() const;

    QPixmap pixmap(const QSize &size, Mode mode = Normal, State state = Off) const;
    inline QPixmap pixmap(int w, int h, Mode mode = Normal, State state = Off) const
        { return pixmap(QSize(w, h), mode, state); }
    inline QPixmap pixmap(int extent, Mode mode = Normal, State state = Off) const
        { return pixmap(QSize(extent, extent), mode, state); }

    QSize actualSize(const QSize &size, Mode mode = Normal, State state = Off) const;

    QString name() const;

    void paint(QPainter *painter, const QRect &rect, Qt::Alignment alignment = Qt::AlignCenter, Mode mode = Normal, State state = Off) const;
    inline void paint(QPainter *painter, int x, int y, int w, int h, Qt::Alignment alignment = Qt::AlignCenter, Mode mode = Normal, State state = Off) const
        { paint(painter, QRect(x, y, w, h), alignment, mode, state); }

    bool isNull() const;
    bool isDetached() const;
    void detach();

    int serialNumber() const;
    qint64 cacheKey() const;

    void addPixmap(const QPixmap &pixmap, Mode mode = Normal, State state = Off);
    void addFile(const QString &fileName, const QSize &size = QSize(), Mode mode = Normal, State state = Off);

    QList<QSize> availableSizes(Mode mode = Normal, State state = Off) const;

    static QIcon fromTheme(const QString &name, const QIcon &fallback = QIcon());
    static bool hasThemeIcon(const QString &name);

    static QStringList themeSearchPaths();
    static void setThemeSearchPaths(const QStringList &searchpath);

    static QString themeName();
    static void setThemeName(const QString &path);

    Q_DUMMY_COMPARISON_OPERATOR(QIcon)

private:
    QIconPrivate *d;
#if !defined(QT_NO_DATASTREAM)
    friend Q_GUI_EXPORT QDataStream &operator<<(QDataStream &, const QIcon &);
    friend Q_GUI_EXPORT QDataStream &operator>>(QDataStream &, QIcon &);
#endif

public:
    typedef QIconPrivate * DataPtr;
    inline DataPtr &data_ptr() { return d; }
};

Q_DECLARE_SHARED(QIcon)
Q_DECLARE_TYPEINFO(QIcon, Q_MOVABLE_TYPE);

#if !defined(QT_NO_DATASTREAM)
Q_GUI_EXPORT QDataStream &operator<<(QDataStream &, const QIcon &);
Q_GUI_EXPORT QDataStream &operator>>(QDataStream &, QIcon &);
#endif

QT_END_NAMESPACE

QT_END_HEADER

#endif // QICON_H

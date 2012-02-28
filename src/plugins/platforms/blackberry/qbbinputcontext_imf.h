/***************************************************************************
**
** Copyright (C) 2011 - 2012 Research In Motion
** Contact: http://www.qt-project.org/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QBBINPUTCONTEXT_H
#define QBBINPUTCONTEXT_H

#include <QtGui/QPlatformInputContext>

#include <QtCore/QLocale>
#include <QtCore/QMetaType>
#include <QtGui/QPlatformIntegration>

#include "imf/imf_client.h"
#include "imf/input_control.h"

QT_BEGIN_NAMESPACE

class QBBInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    QBBInputContext();
    ~QBBInputContext();

    virtual bool isValid() const;

    virtual bool filterEvent(const QEvent *event);
    virtual void reset();
    virtual void update(Qt::InputMethodQueries);
    bool handleKeyboardEvent(int flags, int sym, int mod, int scan, int cap);

    virtual void showInputPanel();
    virtual void hideInputPanel();
    virtual bool isInputPanelVisible() const;

    virtual QLocale locale() const;

protected:
    // Filters only for IMF events.
    bool eventFilter(QObject *obj, QEvent *event);

private Q_SLOTS:
    void keyboardVisibilityChanged(bool visible);
    void keyboardLocaleChanged(const QLocale &locale);
    void inputItemChanged();

private:
    // IMF Event dispatchers
    bool dispatchFocusEvent(FocusEventId id, int hints = Qt::ImhNone);
    bool dispatchRequestSoftwareInputPanel();
    bool dispatchCloseSoftwareInputPanel();
    int32_t processEvent(event_t *event);

    void closeSession();
    void openSession();
    bool hasSession();
    void endComposition();
    void setComposingText(QString const &composingText);
    bool hasSelectedText();

    // IMF Event handlers - these events will come in from QCoreApplication.
    int32_t onBeginBatchEdit(input_session_t *ic);
    int32_t onClearMetaKeyStates(input_session_t *ic, int32_t states);
    int32_t onCommitText(input_session_t *ic, spannable_string_t *text, int32_t new_cursor_position);
    int32_t onDeleteSurroundingText(input_session_t *ic, int32_t left_length, int32_t right_length);
    int32_t onEndBatchEdit(input_session_t *ic);
    int32_t onFinishComposingText(input_session_t *ic);
    int32_t onGetCursorCapsMode(input_session_t *ic, int32_t req_modes);
    int32_t onGetCursorPosition(input_session_t *ic);
    extracted_text_t *onGetExtractedText(input_session_t *ic, extracted_text_request_t *request, int32_t flags);
    spannable_string_t *onGetSelectedText(input_session_t *ic, int32_t flags);
    spannable_string_t *onGetTextAfterCursor(input_session_t *ic, int32_t n, int32_t flags);
    spannable_string_t *onGetTextBeforeCursor(input_session_t *ic, int32_t n, int32_t flags);
    int32_t onPerformEditorAction(input_session_t *ic, int32_t editor_action);
    int32_t onReportFullscreenMode(input_session_t *ic, int32_t enabled);
    int32_t onSendEvent(input_session_t *ic, event_t *event);
    int32_t onSendAsyncEvent(input_session_t *ic, event_t *event);
    int32_t onSetComposingRegion(input_session_t *ic, int32_t start, int32_t end);
    int32_t onSetComposingText(input_session_t *ic, spannable_string_t *text, int32_t new_cursor_position);
    int32_t onSetSelection(input_session_t *ic, int32_t start, int32_t end);
    int32_t onForceUpdate();

    int m_lastCaretPos;
    bool m_isComposing;
    QString m_composingText;
    bool m_inputPanelVisible;
    QLocale m_inputPanelLocale;
};

Q_DECLARE_METATYPE(extracted_text_t*)

QT_END_NAMESPACE

#endif // QBBINPUTCONTEXT_H

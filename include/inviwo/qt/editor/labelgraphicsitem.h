#ifndef IVW_LABELGRAPHICSITEM_H
#define IVW_LABELGRAPHICSITEM_H

#include <inviwo/qt/editor/inviwoqteditordefine.h>
#include <QGraphicsTextItem>

namespace inviwo {

class IVW_QTEDITOR_API LabelGraphicsItem : public QGraphicsTextItem {

public:
    LabelGraphicsItem(QGraphicsItem* parent);
    ~LabelGraphicsItem();

    QString text() const;
    void setText(const QString &);

protected:
    void keyPressEvent(QKeyEvent* event);
    void focusOutEvent(QFocusEvent* event);

    unsigned int labelHeight_;
};

} // namespace

#endif // IVW_LABELGRAPHICSITEM_H
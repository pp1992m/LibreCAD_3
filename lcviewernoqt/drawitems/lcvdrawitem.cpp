#include "lcvdrawitem.h"
using namespace LCViewer;

LCVDrawItem::LCVDrawItem(lc::entity::CADEntity_CSPtr entity, bool selectable) :
        _selectable(selectable),
        _selected(false) {

}

bool LCVDrawItem::selectable() const {
    return _selectable;
}

bool LCVDrawItem::selected() const {
    return _selected;
}

void LCVDrawItem::selected(bool selected) {
    _selected = selected;
}

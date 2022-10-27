#include "AbstractButton.hpp"

void AbstractButton::onMouseClick(unsigned x, unsigned y) {
    if (isPointInWidget(x, y))
        isActive_ = (isActive_) ? false : true;       
}

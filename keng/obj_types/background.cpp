#include "background.hpp"
#include <gl/gl.h>

using namespace Keng;

TBackground::TBackground(
    unsigned typeId,
    TBasis* base,
    unsigned position)
:   TComponent(
    typeId,
    base,
    position)
{
}

TBackground::TBackground(
    TBasis* base,
    unsigned position)
:   TBackground(
    TBACKGROUND,
    base,
    position)
{
}

void TBackground::update() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(.0f, .0f, .0f, 1.0f);
}

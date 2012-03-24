#include "glsimplewaveformwidget.h"

#include <QPainter>

#include "waveform/renderers/waveformwidgetrenderer.h"
#include "waveform/renderers/waveformrenderbackground.h"
#include "waveform/renderers/glwaveformrenderersimplesignal.h"
#include "waveform/renderers/waveformrendererpreroll.h"
#include "waveform/renderers/waveformrendermark.h"
#include "waveform/renderers/waveformrendermarkrange.h"
#include "waveform/renderers/waveformrenderbeat.h"

GLSimpleWaveformWidget::GLSimpleWaveformWidget( const char* group, QWidget* parent) :
    WaveformWidgetAbstract(group),
    QGLWidget(parent) {

    addRenderer<WaveformRenderBackground>();
    addRenderer<WaveformRenderMarkRange>();
    addRenderer<WaveformRenderMark>();
    addRenderer<GLWaveformRendererSimpleSignal>();
    addRenderer<WaveformRendererPreroll>();
    addRenderer<WaveformRenderBeat>();

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_OpaquePaintEvent);

    setAutoBufferSwap(false);

    makeCurrent();
    init();
}

GLSimpleWaveformWidget::~GLSimpleWaveformWidget(){
    makeCurrent();
}

void GLSimpleWaveformWidget::castToQWidget() {
    m_widget = static_cast<QWidget*>(static_cast<QGLWidget*>(this));
}

void GLSimpleWaveformWidget::paintEvent( QPaintEvent* event) {
    makeCurrent();
    QPainter painter(this);
    draw(&painter,event);
    QGLWidget::swapBuffers();
}


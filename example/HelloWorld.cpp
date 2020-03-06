/*
* Copyright 2017 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#include "HelloWorld.h"

#include "GrContext.h"
#include "SkCanvas.h"
#include "SkGradientShader.h"
#include "SkGraphics.h"

using namespace sk_app;

Application* Application::Create(int argc, char** argv, void* platformData) {
    return new HelloWorld(argc, argv, platformData);
}

HelloWorld::HelloWorld(int argc, char** argv, void* platformData)
        : fBackendType(Window::kNativeGL_BackendType)
        , fRotationAngle(0) {
    SkGraphics::Init();

    fWindow = Window::CreateNativeWindow(platformData);
    fWindow->setRequestedDisplayParams(DisplayParams());

    // register callbacks
    fWindow->pushLayer(this);

    fWindow->attach(fBackendType);
}

HelloWorld::~HelloWorld() {
    fWindow->detach();
    delete fWindow;
}

void HelloWorld::updateTitle() {
    if (!fWindow || fWindow->sampleCount() <= 1) {
        return;
    }

    SkString title("Hello World ");
    title.append(Window::kRaster_BackendType == fBackendType ? "Raster" : "OpenGL");
    fWindow->setTitle(title.c_str());
}

void HelloWorld::onBackendCreated() {
    this->updateTitle();
    fWindow->show();
    fWindow->inval();
}

void HelloWorld::onPaint(SkCanvas* canvas) {
    // Clear background
    canvas->clear(SK_ColorWHITE);

    SkPaint paint;
    paint.setColor(SK_ColorRED);

    // render rect
    {
        // Draw a rectangle with red paint
        SkRect rect = SkRect::MakeXYWH(0, 0, 200, 200);
        canvas->drawRect(rect, paint);
    }

    // render circle
    // Set up a linear gradient and draw a circle
    // 线性渐变的color and 绘制一个圆形
    {
        SkPoint linearPoints[] = { { 0, 0 }, { 100, 100 } };
        SkColor linearColors[] = { SK_ColorWHITE, SK_ColorBLACK };
        paint.setShader(SkGradientShader::MakeLinear(linearPoints, linearColors, nullptr, 2,
                                                     SkShader::kMirror_TileMode));
        paint.setAntiAlias(true); // 画圆，打开抗锯齿，不开的话锯齿非常明显

        canvas->drawCircle(300, 100, 100, paint);

        // Detach shader
        paint.setShader(nullptr);
    }

    // render circle with no anti alias
    // 关闭抗锯齿，画圆
    // Set up a linear gradient and draw a circle
    // 线性渐变的color and 绘制一个圆形
    {
        SkPoint linearPoints[] = { { 0, 0 }, { 200, 200 } };
        SkColor linearColors[] = { SK_ColorWHITE, SK_ColorBLACK };
        paint.setShader(SkGradientShader::MakeLinear(linearPoints, linearColors, nullptr, 2,
                                                     SkShader::kMirror_TileMode));
        paint.setAntiAlias(false); // 锯齿非常明显

        canvas->drawCircle(300, 300, 100, paint);

        // Detach shader
        paint.setShader(nullptr);
    }

    // render text
    // Draw a message with a nice black paint
    {
        paint.setAntiAlias(true);      // 打开抗锯齿
        paint.setSubpixelText(true);   // 打开次像素文字渲染
        paint.setColor(SK_ColorBLACK);
        paint.setTextSize(20);

        canvas->save();
        static const char message[] = "Hello World";

        // Translate and rotate
        canvas->translate(550, 100);
        fRotationAngle += 0.2f;
        if (fRotationAngle > 360) {
            fRotationAngle -= 360;
        }
        canvas->rotate(fRotationAngle);

        // Draw the text
        canvas->drawText(message, strlen(message), 0, 0, paint);

        canvas->restore();
    }

    // render text
    // 观察次像素打开与否的区别. ps：没看出啥区别，应该在分辨率较低的显示器才能观察出来
    // Draw a message with a nice black paint
    {
        paint.setAntiAlias(true);      // 打开抗锯齿
        paint.setSubpixelText(true);   // 打开次像素文字渲染
        paint.setColor(SK_ColorBLACK);
        paint.setTextSize(20);

        canvas->save();
        static const char open_subpixel[]  = "open subpixel with text";
        static const char close_subpixel[] = "close subpixel with text";

        canvas->translate(450, 250);
        canvas->drawText(open_subpixel, strlen(open_subpixel), 0, 0, paint);

        canvas->translate(0, 50);   // translate是叠加的位移，非setTranslate
        canvas->drawText(close_subpixel, strlen(close_subpixel), 0, 0, paint);

        canvas->restore();
    }
}

void HelloWorld::onIdle() {
    // Just re-paint continously
    fWindow->inval();
}

bool HelloWorld::onChar(SkUnichar c, uint32_t modifiers) {
    if (' ' == c) {
        fBackendType = Window::kRaster_BackendType == fBackendType ? Window::kNativeGL_BackendType
                                                                   : Window::kRaster_BackendType;
        if (fBackendType == Window::kNativeGL_BackendType) {
            printf("onChar space. fBackendType is %d, kNativeGL_BackendType\n", fBackendType);
        } else if (fBackendType == Window::kRaster_BackendType) {
            printf("onChar space. fBackendType is %d, kRaster_BackendType\n", fBackendType);
        }
        
        fWindow->detach();
        fWindow->attach(fBackendType);
    }
    return true;
}

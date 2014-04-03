/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 * Version 0.6b
 *
 * Copyright (c) 2014 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Main file authors: Erik Sund�n
 *
 *********************************************************************************/

#ifndef IVW_CANVASGLFW_H
#define IVW_CANVASGLFW_H

#include "modules/glfw/glfwmoduledefine.h"
#include <stdlib.h>
#include "modules/opengl/inviwoopengl.h"
#include "modules/opengl/canvasgl.h"
#include <GLFW/glfw3.h>

namespace inviwo {

class IVW_MODULE_GLFW_API CanvasGLFW : public CanvasGL {
public:
    CanvasGLFW(std::string title, uvec2 dimensions);
    ~CanvasGLFW();

    void initialize();
    void initializeGL();
    void initializeSquare();
    void deinitialize();

    void glSwapBuffers();

    void setWindowTitle(std::string);
    void setWindowSize(uvec2);

    static void closeWindow(GLFWwindow*);
    static int getWindowCount();

    //static void refresh(GLFWwindow*);
    static void reshape(GLFWwindow*, int, int);

    /*static MouseEvent::MouseButton mapMouseButton(const int mouseButtonGLFW);
    static MouseEvent::MouseState mapMouseState(const int mouseStateGLFW);
    static InteractionEvent::Modifier mapModifiers(const int modifiersGLFW);

    static void keyboard(unsigned char key, int x, int y);
    static void mouse(int button, int state, int x, int y);
    static void mouseWheel(int button, int state, int x, int y);
    static void mouseMotion(int x, int y);*/

protected:
    static CanvasGLFW* getCanvasGLFW(GLFWwindow*);

private:
    std::string windowTitle_;
    GLFWwindow* glWindow_;

    MouseEvent::MouseButton mouseButton_;
    MouseEvent::MouseState mouseState_;
    InteractionEvent::Modifier mouseModifiers_;

    static GLFWwindow* sharedContext_;
    static int glfwWindowCount_;
};

} // namespace

#endif // IVW_CANVASGLFW_H

#include "positionwidgetprocessor.h"
#include <inviwo/core/interaction/trackball.h>
#include <inviwo/core/interaction/pickingmanager.h>
#include <inviwo/core/datastructures/geometry/basemeshcreator.h>

namespace inviwo {

ProcessorClassName(PositionWidgetProcessor, "PositionWidget"); 
ProcessorCategory(PositionWidgetProcessor, "Geometry Rendering");
ProcessorCodeState(PositionWidgetProcessor, CODE_STATE_EXPERIMENTAL); 

PositionWidgetProcessor::PositionWidgetProcessor()
    : CompositeProcessorGL(),
      inport_("inport"),
      outport_("outport", COLOR_DEPTH_PICKING),
      widgetType_("widgetType", "Widget Type"),
      position_("position", "Position", vec3(0.0f), vec3(-1.f), vec3(1.f)),
      camera_("camera", "Camera", vec3(0.0f, 0.0f, -2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f))
{
    addPort(inport_);
    addPort(outport_);

    widgetType_.addOption("cube", "Cube");
    widgetType_.addOption("sphere", "Sphere");
    widgetType_.set("sphere");
    addProperty(widgetType_);

    addProperty(position_);
    addProperty(camera_);
    addInteractionHandler(new Trackball(&camera_));

    widgetPickingObject_ = PickingManager::instance()->registerPickingCallback(this, &PositionWidgetProcessor::updateWidgetPositionFromPicking);

    vec3 posLLF = vec3(0.0f);
    vec3 posURB = vec3(1.0f);

    widget_ = new Geometry(BaseMeshCreator::rectangularPrism(posLLF, posURB, posLLF, posURB, vec4(posLLF, 1.f), vec4(posURB, 1.f)));

    modelTranslation_ = vec3(0.f);
    modelMatrix_ = mat4(1.0);
}

PositionWidgetProcessor::~PositionWidgetProcessor() {}

void PositionWidgetProcessor::initialize() {
    CompositeProcessorGL::initialize();

    program_ = new Shader("picking.frag");
    program_->build();
}

void PositionWidgetProcessor::deinitialize() {
    CompositeProcessorGL::deinitialize();

    delete program_;
    program_ = 0;
}

void PositionWidgetProcessor::updateWidgetPositionFromPicking(){
    vec2 move = widgetPickingObject_->getPickingMove();
    if(move.x == 0.f && move.y == 0.f){
        return;
    }
    vec2 pos = widgetPickingObject_->getPickingPosition();
    float depth = widgetPickingObject_->getPickingDepth();
    vec3 startNdc = vec3((2.f*pos.x)-1.f, (2.f*pos.y)-1.f, depth);
    vec3 endNdc = vec3((2.f*(pos.x+move.x))-1.f, (2.f*(pos.y+move.y))-1.f, depth);
    vec3 startWorld = camera_.getWorldPosFromNormalizedDeviceCoords(startNdc);
    vec3 endWorld = camera_.getWorldPosFromNormalizedDeviceCoords(endNdc);
    modelTranslation_ += (endWorld-startWorld);
    modelMatrix_ = glm::translate(modelTranslation_);
    invalidate(INVALID_OUTPUT);
}

void PositionWidgetProcessor::process() {    
    activateAndClearTarget(outport_);

    program_->activate();
    program_->setUniform("pickingColor_", widgetPickingObject_->getPickingColor());

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadMatrixf(glm::value_ptr(camera_.projectionMatrix()));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(glm::value_ptr(camera_.viewMatrix()*modelMatrix_));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    widget_->getRepresentation<GeometryGL>()->render();

    glDepthFunc(GL_LESS);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glLoadIdentity();

    program_->deactivate();

    deactivateCurrentTarget();

    compositePortsToOutport(outport_, inport_);
}

} // namespace

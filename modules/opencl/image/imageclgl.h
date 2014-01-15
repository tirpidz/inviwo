/**********************************************************************
 * Copyright (C) 2013 Scientific Visualization Group - Link�ping University
 * All Rights Reserved.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * No part of this software may be reproduced or transmitted in any
 * form or by any means including photocopying or recording without
 * written permission of the copyright owner.
 *
 * Primary author : Daniel J�nsson
 *
 **********************************************************************/

#ifndef IVW_IMAGECLGL_H
#define IVW_IMAGECLGL_H

#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/datastructures/image/imagerepresentation.h>
#include <modules/opencl/inviwoopencl.h>
#include <modules/opencl/openclmoduledefine.h>
#include <modules/opencl/image/layerclgl.h>

namespace inviwo {

class IVW_MODULE_OPENCL_API ImageCLGL : public ImageRepresentation {

public:
    ImageCLGL();
    ImageCLGL(const ImageCLGL& other);
    virtual ~ImageCLGL();
    virtual std::string getClassName() const { return "ImageCLGL"; }
    virtual ImageCLGL* clone() const;
    virtual void initialize();
    virtual void deinitialize();

    LayerCLGL* getLayerCLGL();
    const LayerCLGL* getLayerCLGL() const;
    
    virtual bool copyAndResizeRepresentation(DataRepresentation*) const;

protected:
    virtual void update(bool);

    LayerCLGL* layerCLGL_;
};

} // namespace

namespace cl {

// Kernel argument specializations for ImageCLGL type
// Will set the color layer as argument.
// (enables calling cl::Queue::setArg with ImageCLGL)
template <>
IVW_MODULE_OPENCL_API cl_int Kernel::setArg(cl_uint index, const inviwo::ImageCLGL& value);

} // namespace cl

#endif // IVW_IMAGECLGL_H
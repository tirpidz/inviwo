/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 * Version 0.6b
 *
 * Copyright (c) 2012-2014 Inviwo Foundation
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
 * Contact: Sathish Kottravel
 *
 *********************************************************************************/

#include <inviwo/core/common/inviwoapplication.h>
#include <inviwo/core/properties/directoryproperty.h>
#include <inviwo/core/properties/fileproperty.h>
#include <inviwo/core/util/urlparser.h>

namespace inviwo {

PropertyClassIdentifier(DirectoryProperty, "org.inviwo.DirectoryProperty");

DirectoryProperty::DirectoryProperty(std::string identifier, std::string displayName,
                                     std::string value, std::string contentType,
                                     PropertyOwner::InvalidationLevel invalidationLevel,
                                     PropertySemantics semantics)
    : TemplateProperty<std::string>(identifier, displayName, value, invalidationLevel, semantics)
    , fileIndexingHandle_(0)
    , contentType_(contentType)
{}

std::vector<std::string> DirectoryProperty::getDirectoryTree() const { return directoryTree_; }

void DirectoryProperty::updateDirectoryTree() { updateWidgets(); }

std::vector<std::string> DirectoryProperty::getFiles(std::string filters) const {
    std::vector<std::string> validFilesWithExtension;
    std::string filterName = URLParser::getFileNameWithoutExtension(filters);
    std::string filterExt = URLParser::getFileExtension(filters);
    bool arbitaryName = (filterName == "*");
    bool arbitaryExt = (filterExt == "*");

    // Matching with star as part of name or ext is not implemented at the moment.
    // Only: *.*, *.ext, name.*, name.ext
    for (size_t i = 0; i < directoryTree_.size(); i++) {
        std::string file = get() + "/";
        file = URLParser::getFileDirectory(file) + directoryTree_[i];

        if (arbitaryName && arbitaryExt) {
            validFilesWithExtension.push_back(file);
            continue;
        }

        std::string fileExt = URLParser::getFileExtension(directoryTree_[i]);

        if (arbitaryName && fileExt == filterExt) {
            validFilesWithExtension.push_back(file);
            continue;
        }

        std::string fileName = URLParser::getFileNameWithoutExtension(directoryTree_[i]);

        if (fileName == filterName && fileExt == filterExt) {
            validFilesWithExtension.push_back(file);
            continue;
        }
    }

    return validFilesWithExtension;
}

void DirectoryProperty::setDirectoryTree(std::vector<std::string> dirTree) {
    directoryTree_ = dirTree;
}


void DirectoryProperty::serialize(IvwSerializer& s) const {
    Property::serialize(s);
    std::string basePath = s.getFileName();
    std::string absoluteFilePath = get();

    if (basePath.empty())
        basePath = InviwoApplication::getPtr()->getPath(
            InviwoApplication::PATH_DATA);  // why workspaces

    std::string relativePath = URLParser::getRelativePath(basePath, absoluteFilePath);
    s.serialize("directory", relativePath);
}

void DirectoryProperty::deserialize(IvwDeserializer& d) {
    Property::deserialize(d);
    std::string relativePath;
    d.deserialize("directory", relativePath);
    std::string basePath = d.getFileName();

    if (basePath.empty())
        basePath = InviwoApplication::getPtr()->getPath(
            InviwoApplication::PATH_DATA);  // why workspaces

    basePath = URLParser::getFileDirectory(basePath);
    set(basePath + relativePath);
}

void DirectoryProperty::setContentType(const std::string& contentType) {
    contentType_ = contentType;
}

std::string DirectoryProperty::getContentType() const { return contentType_; }

}  // namespace

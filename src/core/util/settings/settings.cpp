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
 * Contact: Rickard Englund
 *
 *********************************************************************************/

#include <inviwo/core/util/settings/settings.h>
#include <inviwo/core/util/urlparser.h>
#include <inviwo/core/common/inviwoapplication.h>

namespace inviwo {

Settings::Settings(const std::string &id) : identifier_(id), isDeserializing_(false) {}

Settings::~Settings() {}

void Settings::addProperty(Property* property){
    PropertyOwner::addProperty(property);
    property->onChange(this,&Settings::saveToDisk);
}

void Settings::addProperty(Property& property){
    PropertyOwner::addProperty(property);
    property.onChange(this,&Settings::saveToDisk);
}

std::string Settings::getIdentifier() {
    return identifier_;
}

void Settings::loadFromDisk(){
    std::stringstream ss;
    ss << identifier_ << ".ivs";
    std::string filename = ss.str();
    replaceInString(filename," ","_");
    filename = InviwoApplication::getPtr()->getPath(InviwoApplication::PATH_SETTINGS,filename);

    isDeserializing_ = true;
    if(URLParser::fileExists(filename)){
        IvwDeserializer d(filename);
        deserialize(d);
    }
    isDeserializing_ = false;
}

void Settings::saveToDisk() {
    if (isDeserializing_) return;

    std::stringstream ss;
    ss << identifier_ << ".ivs";
    std::string filename = ss.str();
    replaceInString(filename, " ", "_");
    try {
        IvwSerializer s(
            InviwoApplication::getPtr()->getPath(InviwoApplication::PATH_SETTINGS, filename, true));
        serialize(s);
        s.writeFile();
    } catch (std::exception e) {
        LogWarn("Could not write settings");
    }
}

} // namespace

//
// Created by keldon on 20/12/18.
//

#include "object.hpp"

emcee::Object::Object() : platform_(nullptr) {}
emcee::Object::Object(emcee::Platform &platform) : platform_(&platform) {}
emcee::Object::Object(emcee::Platform *platform) : platform_(platform) {}

//
// Created by Gilbert Gwizdala on 2019-02-03.
//

#include "StaticModel.h"

StaticModel::StaticModel(MashPtr *mashPtr): mashPtr(mashPtr) {

}

MashPtr *StaticModel::getMashPtr() const {
    return mashPtr;
}

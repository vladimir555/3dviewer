#pragma once


#include "controller/viewer.h"


namespace controller::implementation {


class CViewer: public IViewer {
public:
    typedef QSharedPointer<CViewer> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }

    CViewer() = default;
    virtual ~CViewer() = default;

//    void selectObjectType(model::TObjectType const &object_type) override;
};


} // controller::implementation

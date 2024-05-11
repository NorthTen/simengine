#pragma once
#include "ecs/object.hpp"
#include <vector>
#include <boost/smart_ptr.hpp>
namespace Simengine {
    struct Scene {
        private:
            std::vector<boost::shared_ptr<Object>> objects;

        /// Adds an object to the scene.
        /// Very important to note that to make any further changes, use the returned pointer that points to the object you inserted.
        /// Otherwise the changes **won't be reflected in other parts of the code!**
        boost::shared_ptr<Object> addobj(Object *obj){
            obj->id=objects.size()+1;
            objects.push_back(obj->refptr);
            return obj->refptr;
        };

        void delobj(boost::shared_ptr<Object> *obj) {
            for (int i = 0; i < objects.size(); i++) {
                auto ranobj = objects[i];
                if (ranobj->id == obj->get()->id) {
                    objects.erase(objects.begin() + i);
                }
            };
        };

        /// This is typically used when anything hierarichally changes in the object list data structure.
        void update_obj_ids() {
            for (int i = 0; i < objects.size(); i++) {
                auto obj = objects[i];
                if(obj->refptr != obj->lockptr.lock()) {
                    delobj(&obj); // We remove it if someone decides to suddenly delete the object.
                    continue; // Do not cause an error by continuing.
                }

                obj->id=i; // update id to match how many objects are in the game; using a globally random uuid consisting of long characters
                // is unnecessary, and wastes memory
            }
        };
    };
};

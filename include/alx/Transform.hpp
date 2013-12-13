#ifndef ALX_TRANSFORM_HPP
#define ALX_TRANSFORM_HPP


#include <allegro5/allegro.h>
#include "alx/Value.hpp"
#include "alx/Point.hpp"
#include "alx/Rect.hpp"


namespace alx {


/**
    Value-based wrapper around ALLEGRO_TRANSFORM.
 */
class Transform : public Value<ALLEGRO_TRANSFORM> {
public:
    /**
        The default constructor.
     */
    Transform() {
    }

    /**
        constructor from transform.
        @param transform transform.
     */
    Transform(const ALLEGRO_TRANSFORM &transform) {
        al_copy_transform(&get(), &transform);
    }

    /**
        The identity constructor.
     */
    Transform(bool) {
        setIdentity();
    }

    /**
        the copy constructor.
        @param src source object.
     */
    Transform(const Transform &src) {
        al_copy_transform(&get(), &src.get());
    }

    /**
        builds a transformation.
        @param x translation along the x axis.
        @param y translation along the y axis.
        @param sx scale along the x axis.
        @param sy scale along the y axis.
        @param theta rotation angle.
     */
    Transform(float x, float y, float sx, float sy, float theta) {
        set(x, y, sx, sy, theta);
    }

    /**
        Checks the inverse.
        @return tolerance tolerance.
        @return true if invertible, false otherwise.
     */
    bool isInvertible(float tolerance) const {
        return al_check_inverse(&get(), tolerance);
    }

    /**
        Transforms coordinates.
        @param x x.
        @param y y.
     */
    void transform(float &x, float &y) const {
        al_transform_coordinates(&get(), &x, &y);
    }

    /**
        Transforms a point.
        @param pt point.
     */
    void transform(Point<float> &pt) const {
        transform(pt.m_x, pt.m_y);
    }

    /**
        Transforms a rectangle.
        @param rt rectangle.
     */
    void transform(Rect<float> &rt) const {
        transform(rt.m_left, rt.m_top);
        transform(rt.m_right, rt.m_bottom);
    }

    /**
        Uses this transform.
     */
    void setCurrent() {
        al_use_transform(&get());
        _currentTransform() = this;
    }

    /**
        inverts this transform.
     */
    void invert() {
        al_invert_transform(&get());
    }

    /**
        Sets this transform to be the identity transform.
     */
    void setIdentity() {
        al_identity_transform(&get());
    }

    /**
        builds a transformation.
        @param x translation along the x axis.
        @param y translation along the y axis.
        @param sx scale along the x axis.
        @param sy scale along the y axis.
        @param theta rotation angle.
     */
    void set(float x, float y, float sx, float sy, float theta) {
        al_build_transform(&get(), x, y, sx, sy, theta);
    }

    /**
        applies a translation.
        @param x translation along the x axis.
        @param y translation along the y axis.
     */
    void translate(float x, float y) {
        al_translate_transform(&get(), x, y);
    }

    /**
        applies a rotation.
        @param theta rotation angle.
     */
    void rotate(float theta) {
        al_rotate_transform(&get(), theta);
    }

    /**
        applies scaling.
        @param sx scale along the x axis.
        @param sy scale along the y axis.
     */
    void scale(float sx, float sy) {
        al_scale_transform(&get(), sx, sy);
    }

    /**
        returns the current transform.
        @return the current transform.
     */
    static Transform *getCurrent() {
        return _currentTransform();
    }

private:
    //internal current transform
    static Transform*& _currentTransform() {
        static Transform *t = 0;
        return t;
    }
};


} //namespace alx


#endif //ALX_TRANSFORM_HPP

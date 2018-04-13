#ifndef CAMERA_H
#define CAMERA_H

#include "../util/Algebra.h"

class Camera {
    public:
        Camera();
        ~Camera();
        void Orient(Point& eye, Point& focus, Vector& up);
        void Orient(Point& eye, Vector& look, Vector& up);
        void SetViewAngle (double viewAngle);
        void SetNearPlane (double nearPlane);
        void SetFarPlane (double farPlane);
        void SetScreenSize (int screenWidth, int screenHeight);
        void setCameraAxes();

        Matrix GetProjectionMatrix();
        Matrix GetModelViewMatrix();

        void RotateV(double angle);
        void RotateU(double angle);
        void RotateW(double angle);
        void Rotate(Point p, Vector axis, double degree);
        void Translate(const Vector &v);
        void RotateAroundAxis(Vector axis, double angle);

        Point GetEyePoint();
        Vector GetLookVector();
        Vector GetUpVector();
        double GetViewAngle();
        double GetNearPlane();
        double GetFarPlane();
        int GetScreenWidth();
        int GetScreenHeight();
        double getAxisScale(double angle);

        double GetFilmPlanDepth();
        double GetScreenWidthRatio();
    private:
        Point eye;
        Vector up;
        Vector look;
        Vector u, v, w;
        double viewAngle;
        double nearPlane;
        double farPlane;
        double screenWidth;
        double screenHeight;
        double aspectRatio;
        double widthAngle;
        double heightAngle;
};
#endif


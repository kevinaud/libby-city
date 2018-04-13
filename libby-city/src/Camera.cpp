/**
 * Author: Kevin Aud
 * Assignment: Program 2
 */

#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::Orient(Point& eye, Point& focus, Vector& up) {
    this->eye = eye;
    this->look = focus - eye;
    this->up = up;
    setCameraAxes();
}

void Camera::Orient(Point& eye, Vector& look, Vector& up) {
    this->eye = eye;
    this->look = look;
    this->up = up;
    setCameraAxes();
}

void Camera::setCameraAxes() {
    w = -1.0 * normalize(look);
    Vector crossProduct = cross(up, w);
    u = normalize(crossProduct);
    v = cross(w, u);
}

Matrix Camera::GetProjectionMatrix() {

    double xScale = getAxisScale(widthAngle);
    double yScale = getAxisScale(heightAngle);

    // scaling of the x and y axes
    Matrix m2(
        xScale, 0,      0,          0, 
        0,      yScale, 0,          0, 
        0,      0,      1/farPlane, 0, 
        0,      0,      0,          1
    );

    double c = -nearPlane / farPlane;
    // Far scaling of the z axis
    Matrix m1(
        1, 0, 0,        0, 
        0, 1, 0,        0, 
        0, 0, -1/(c+1), c/(c+1), 
        0, 0, -1,       0
    );

    Matrix result = m1 * m2;
    return result;
}

double Camera::getAxisScale(double angle) {
    return 1.0 / (tan(angle / 2) * farPlane);
}

void Camera::SetViewAngle (double viewAngle) {
    this->viewAngle = viewAngle;
    this->widthAngle = DEG_TO_RAD(viewAngle);
    this->heightAngle = DEG_TO_RAD(viewAngle / aspectRatio);
}

void Camera::SetNearPlane (double nearPlane) {
    this->nearPlane = nearPlane;
}

void Camera::SetFarPlane (double farPlane) {
    this->farPlane = farPlane;
}

void Camera::SetScreenSize (int screenWidth, int screenHeight) {
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    this->aspectRatio = screenWidth / screenHeight;
}

Matrix Camera::GetModelViewMatrix() {

    // Rotation Matrix
    Matrix m1(
        u[0], u[1], u[2], 0,
        v[0], v[1], v[2], 0,
        w[0], w[1], w[2], 0,
        0,    0,    0,    1
    );

    // Translation Matrix
    Matrix m2(
        1, 0, 0, -eye[0],
        0, 1, 0, -eye[1],
        0, 0, 1, -eye[2],
        0, 0, 0, 1
    );

    Matrix result = m1 * m2;
    return result;
}

void Camera::RotateV(double angle) {
    RotateAroundAxis(v, angle);
}

void Camera::RotateU(double angle) {
    RotateAroundAxis(u, angle);
}

void Camera::RotateW(double angle) {
    RotateAroundAxis(w, angle);
}

void Camera::RotateAroundAxis(Vector axis, double angle) {
    Matrix rotation = rot_mat(axis, DEG_TO_RAD(angle));
    look = rotation * look;
    up = rotation * up;

    // update u, v, w since the look and up vectors have changed
    setCameraAxes();
}

void Camera::Translate(const Vector &v) {
    eye = eye + v;
}

void Camera::Rotate(Point p, Vector axis, double degrees) {
    Matrix rotation = rot_mat(p, axis, DEG_TO_RAD(degrees));
    eye = rotation * eye;
    look = rotation * look;
    up = rotation * up;

    // update u, v, w since the look and up vectors have changed
    setCameraAxes();
}

Point Camera::GetEyePoint() {
    return eye;
}

Vector Camera::GetLookVector() {
    return look;
}

Vector Camera::GetUpVector() {
    return up;
}

double Camera::GetViewAngle() {
    return viewAngle;
}

double Camera::GetNearPlane() {
    return nearPlane;
}

double Camera::GetFarPlane() {
    return farPlane;
}

int Camera::GetScreenWidth() {
    return screenWidth;
}

int Camera::GetScreenHeight() {
    return screenHeight;
}

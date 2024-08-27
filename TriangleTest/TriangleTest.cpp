#include <iostream>
#include <Eigen/Dense>

using Eigen::Vector3d;
using Eigen::MatrixXd;

// 计算三角形平面的法向量
Vector3d GetTriangleNormal(const Vector3d& a, const Vector3d& b, const Vector3d& c) {
    Vector3d ab = b - a;
    Vector3d ac = c - a;
    return ab.cross(ac).normalized();
}

// 计算点在指定法向量平面上的投影
Vector3d GetProjectionOnPlane(const Vector3d& point, const Vector3d& orientation, const Vector3d& planePoint) {
    // 计算点到原点的距离
    double distanceToOrigin = (point - planePoint).dot(orientation) / orientation.norm();

    // 计算投影点
    Vector3d projection = point - distanceToOrigin * orientation;

    return projection;
}

// 计算重心坐标
Vector3d CalculateBarycentricCoordinates(const Vector3d& p, const Vector3d& a, const Vector3d& b, const Vector3d& c) {
    Vector3d v0 = c - a, v1 = b - a, v2 = p - a;
    double d00 = v0.dot(v0);
    double d01 = v0.dot(v1);
    double d11 = v1.dot(v1);
    double d20 = v2.dot(v0);
    double d21 = v2.dot(v1);
    double denom = d00 * d11 - d01 * d01;
    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;
    return Vector3d(u, v, w);
}

// 检查点是否在三角形内部
bool IsPointInTriangle(const Vector3d& p, const Vector3d& a, const Vector3d& b, const Vector3d& c) {
    Vector3d bary = CalculateBarycentricCoordinates(p, a, b, c);
    return (bary.minCoeff() >= 0.0) && (bary.sum() <= 1.0);
}

int main() {
    // 定义三个三维向量
    Vector3d v0(0.501, 0, 1);
    Vector3d v1(1, 0, 1);
    Vector3d v2(0, 1, 1);

    // 创建一个矩阵来存储这三个点
    MatrixXd points(3, 3);  // 3 行 3 列

    // 将向量存储到矩阵中
    points.row(0) = v0;
    points.row(1) = v1;
    points.row(2) = v2;

    // 输出原始矩阵
    std::cout << "Original points matrix:\n" << points << std::endl;

    // 定义目标三角形的三个顶点
    Vector3d a(0, 0, 0), b(0, 1, 1), c(1, 1, 1);

    // 计算目标三角形平面的法向量
    Vector3d orientation = GetTriangleNormal(a, b, c);

    // 投影到目标三角形所在平面上
    for (int i = 0; i < points.rows(); ++i) {
        Vector3d projectedPoint = GetProjectionOnPlane(points.row(i), orientation, a);
        points.row(i) = projectedPoint;
    }

    // 输出投影后的矩阵
    std::cout << "Projected points matrix:\n" << points << std::endl;

    // 检测投影后的点是否在三角形内部
    for (int i = 0; i < points.rows(); ++i) {
        bool inside = IsPointInTriangle(points.row(i), a, b, c);
        std::cout << "Point " << i + 1 << " is " << (inside ? "inside" : "outside") << " the triangle." << std::endl;
    }

    return 0;
}
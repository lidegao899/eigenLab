#include <Eigen/Dense>
#include <iostream>
#include <vector>

typedef Eigen::Matrix<float, 3, 1> Vec3f;

// 判断线段是否相交的辅助函数
bool SegmentIntersect(const Vec3f& p1, const Vec3f& q1, const Vec3f& p2, const Vec3f& q2) {
    // 使用向量叉乘来检查两线段是否相交
    Vec3f d1 = q1 - p1;
    Vec3f d2 = q2 - p2;
    Vec3f p1_p2 = p1 - p2;
    Vec3f q1_p2 = q1 - p2;

    if (((d1.cross(p1_p2).norm() == 0) && (d2.dot(p1_p2) >= 0)) &&
        ((d2.cross(q1_p2).norm() == 0) && (d1.dot(q1_p2) >= 0))) {
        return true;
    }
    return false;
}

// 判断点是否在三角形内的辅助函数
bool PointInTriangle(const Vec3f& point, const Vec3f& p1, const Vec3f& p2, const Vec3f& p3) {
    // 计算向量
    Vec3f v0 = p1 - point;
    Vec3f v1 = p2 - point;
    Vec3f v2 = p3 - point;

    // 计算法向量
    Vec3f n1 = v1.cross(v2);
    Vec3f n2 = v2.cross(v0);
    Vec3f n3 = v0.cross(v1);

    // 检查点是否在三角形平面上
    if (n1.dot(n2) > 0 && n1.dot(n3) > 0) {
        return true;
    }
    return false;
}

// 判断两个三角形是否相交的函数
bool TrianglesIntersect(const Vec3f& t1v1, const Vec3f& t1v2, const Vec3f& t1v3,
    const Vec3f& t2v1, const Vec3f& t2v2, const Vec3f& t2v3) {
    // 检查三角形的每条边是否相交
    for (int i = 0; i < 3; ++i) {
        Vec3f t1edge1[2] = { t1v1, t1v2 };
        Vec3f t1edge2[2] = { t1v2, t1v3 };
        Vec3f t1edge3[2] = { t1v3, t1v1 };

        Vec3f t2edge1[2] = { t2v1, t2v2 };
        Vec3f t2edge2[2] = { t2v2, t2v3 };
        Vec3f t2edge3[2] = { t2v3, t2v1 };

        if (SegmentIntersect(t1edge1[0], t1edge1[1], t2edge1[0], t2edge1[1]) ||
            SegmentIntersect(t1edge1[0], t1edge1[1], t2edge2[0], t2edge2[1]) ||
            SegmentIntersect(t1edge1[0], t1edge1[1], t2edge3[0], t2edge3[1]) ||
            SegmentIntersect(t1edge2[0], t1edge2[1], t2edge1[0], t2edge1[1]) ||
            SegmentIntersect(t1edge2[0], t1edge2[1], t2edge2[0], t2edge2[1]) ||
            SegmentIntersect(t1edge2[0], t1edge2[1], t2edge3[0], t2edge3[1]) ||
            SegmentIntersect(t1edge3[0], t1edge3[1], t2edge1[0], t2edge1[1]) ||
            SegmentIntersect(t1edge3[0], t1edge3[1], t2edge2[0], t2edge2[1]) ||
            SegmentIntersect(t1edge3[0], t1edge3[1], t2edge3[0], t2edge3[1])) {
            return true;
        }
    }

    // 检查一个三角形的每个顶点是否在另一个三角形内
    if (PointInTriangle(t1v1, t2v1, t2v2, t2v3) ||
        PointInTriangle(t1v2, t2v1, t2v2, t2v3) ||
        PointInTriangle(t1v3, t2v1, t2v2, t2v3) ||
        PointInTriangle(t2v1, t1v1, t1v2, t1v3) ||
        PointInTriangle(t2v2, t1v1, t1v2, t1v3) ||
        PointInTriangle(t2v3, t1v1, t1v2, t1v3)) {
        return true;
    }

    return false;
}

int main() {
    // 定义两个三角形的顶点
    Vec3f t1v1(0.0f, 0.0f, 0.0f);
    Vec3f t1v2(1.0f, 0.0f, 0.0f);
    Vec3f t1v3(0.0f, 1.0f, 0.0f);

    Vec3f t2v1(1.0f, 1.0f, 0.0f);
    Vec3f t2v2(1.0f, 0.0f, 0.0f);
    Vec3f t2v3(0.0f, 1.0f, 0.0f);

    // 判断两个三角形是否相交
    if (TrianglesIntersect(t1v1, t1v2, t1v3, t2v1, t2v2, t2v3)) {
        std::cout << "The triangles intersect." << std::endl;
    }
    else {
        std::cout << "The triangles do not intersect." << std::endl;
    }

    return 0;
}